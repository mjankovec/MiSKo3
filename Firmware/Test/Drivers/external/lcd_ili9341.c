/*
 * Komunikacija s krmilnikom Ili9341. Za nadrobnejši opis datotek glej glavo datoteke `lcd.c'.
 * (C) 2022 Nejc Bertoncelj <nbertoncelj afna student.uni-lj.si>
 * (C) 2021 STMicroelectronics, MCD Application Team
 */

#include "lcd_ili9341.h"

//! @brief Tabela orientacij. Izbrano vrednost se pošlje na naslov "Memory Data Access Control".
static uint32_t orientations[4] = {
	0x00U, /* Portrait orientation choice of LCD screen               */
	0xC0U, /* Portrait rotated 180° orientation choice of LCD screen  */
	0xA0U, /* Landscape orientation choice of LCD screen              */
	0x60U, /* Landscape rotated 180° orientation choice of LCD screen */
};

//! @brief Glavni atributi zaslona
static struct LCD_Attributes {
	uint32_t width;
	uint32_t height;
	uint32_t orientation;
} LCD;

/*!
 * @brief Nastavi spominski naslov enote FSMC
 * @param address želen naslov
 * @internal
 */
static inline void FMC_BANK1_SetAddress (LCD_IO_Data_t address)
{
	*(LCD_IO_Data_t *)(FMC_BANK1_REG) = address;

	// Počakaj na sinhronizacijo pomnilnika
	__DSB();
}

/*!
 * @brief Piši v register enote FSMC
 * @param data želen podatek
 * @internal
 */
static inline void FMC_BANK1_WriteData(LCD_IO_Data_t data)
{
	*(LCD_IO_Data_t *)(FMC_BANK1_MEM) = data;

	// Počakaj na sinhronizacijo pomnilnika
	__DSB();
}

/*!
 * @brief Preberi podatek iz registra enote FSMC
 * @internal
 *
 * @note Register mora biti prej naslovljen s funkcijo `FMC_BANK1_SetAddress()'!
 */
static inline uint16_t FMC_BANK1_ReadData(void)
{
	return *(LCD_IO_Data_t *)(FMC_BANK1_MEM);
}

/*!
 * @brief Podaj spominski naslov LCD krmilniku
 * @param *address *naslov* spremenljivke, v kateri je zapisan ukaz (register)
 */
void ILI9341_SetAddress(LCD_IO_Data_t *address)
{

#ifdef ILI9341_USEDMA
	ILI9341_WaitTransfer();
#endif
	// Ukazni register je le eden, zato podajanje dolžine podatka ni potrebno
	FMC_BANK1_SetAddress(*address);
}

/*!
 * @brief Piši tabelo v grafični pomnilnik (GRAM) LCD krmilnika
 * @param *data  *naslov* tabele, v kateri so zapisani podatki
 * @param length dolžina tabele podatkov
 */
void ILI9341_SendData(LCD_IO_Data_t *data, uint32_t length)
{
	uint8_t increment = LCD_IO_DATA_WRITE_CYCLES;

	for (uint32_t i = 0; i < (length/increment); i += increment)
		FMC_BANK1_WriteData(data[i]);
}

/*!
 * @brief Večkrat zapiši isti podatek v grafični pomnilnik (GRAM) LCD krmilnika
 * @param data spremenljivka s podatkom
 * @param num_copies število kopij, ki se pošljejo
 */
void ILI9341_SendRepeatedData(LCD_IO_Data_t data, uint32_t num_copies)
{
	uint8_t increment = LCD_IO_DATA_WRITE_CYCLES;

	for (uint32_t i = 0; i < (num_copies/increment); i += increment)
		FMC_BANK1_WriteData(data);
}

#ifdef ILI9341_USEDMA
/*!
  * @brief  Piši tabelo v grafični pomnilnik (GRAM) LCD krmilnika prek DMA
  * @param  *data  *naslov* tabele, v kateri so zapisani podatki
  * @param  length dolžina tabele podatkov
  * @return koda napake (1 = ERROR, 0 = SUCCESS)
  */
int32_t ILI9341_SendDataDMA(LCD_IO_Data_t *data, uint32_t length)
{
	uint32_t len,transfer,pdata;

	switch (hLCDDMA.Init.PeriphDataAlignment)
	{
		case DMA_PDATAALIGN_WORD:
			len = (length / (2*LCD_IO_DATA_WRITE_CYCLES));
			break;
		case DMA_PDATAALIGN_BYTE:
			len = 2*length/LCD_IO_DATA_WRITE_CYCLES;
			break;
		default:
		case DMA_PDATAALIGN_HALFWORD:
			len = (length / LCD_IO_DATA_WRITE_CYCLES);
			break;
	}



	ILI9341_WaitTransfer();
	HAL_DMA_DeInit(&hLCDDMA);
	hLCDDMA.Init.PeriphInc = DMA_PINC_ENABLE;	//increment source address
	HAL_DMA_Init(&hLCDDMA);
	pdata = data;
	do
	{
		ILI9341_WaitTransfer();
		if (len > 65535)
		{
			len -= 65535;
			transfer = 65535;
		}
		else
		{
			transfer = len;
			len = 0;
		}
		if (transfer == 0) return 1;
		if (HAL_DMA_Start_IT(&hLCDDMA, pdata, (uint32_t) FMC_BANK1_MEM, transfer) != HAL_OK) return 1;
		pdata += transfer;
	}
	while (len);

	return 0;
}


/*!
 * @brief Večkrat zapiši isti podatek v grafični pomnilnik (GRAM) LCD krmilnika
 * @param data spremenljivka s podatkom
 * @param num_copies število kopij, ki se pošljejo
 */
int32_t ILI9341_SendRepeatedDataDMA(LCD_IO_Data_t data, uint32_t num_copies)
{

	uint32_t len, transfer;

	switch (hLCDDMA.Init.PeriphDataAlignment)
	{
		case DMA_PDATAALIGN_WORD:
			len = (num_copies / (2*LCD_IO_DATA_WRITE_CYCLES));
			break;
		case DMA_PDATAALIGN_BYTE:
			len = 2*num_copies/LCD_IO_DATA_WRITE_CYCLES;
			break;
		default:
		case DMA_PDATAALIGN_HALFWORD:
			len = (num_copies / LCD_IO_DATA_WRITE_CYCLES);
			break;
	}

	ILI9341_WaitTransfer();
	HAL_DMA_DeInit(&hLCDDMA);
	hLCDDMA.Init.PeriphInc = DMA_PINC_DISABLE;	// dont increment source address
	HAL_DMA_Init(&hLCDDMA);

	do
	{
		ILI9341_WaitTransfer();
		if (len > 65535)
		{
			len -= 65535;
			transfer = 65535;
		}
		else
		{
			transfer = len;
			len = 0;
		}
		if (transfer == 0) return 1;
		if (HAL_DMA_Start_IT(&hLCDDMA, (uint32_t) &data, (uint32_t)FMC_BANK1_MEM, transfer) != HAL_OK) return 1;
	}
	while (len);

	return 0;
}

#endif

/*!
 * @brief Preberi podatek iz naslova grafičnega pomnilnika (GRAM)
 * @param *address *naslov* tabele, kamor se bodo zapisali podatki
 * @param length   dolžina tabele podatkov
 */
void ILI9341_RecvData(LCD_IO_Data_t *address, uint32_t length)
{
	FMC_BANK1_SetAddress(*address);

	for (uint32_t i = 0; i < length; i++)
		address[i] = FMC_BANK1_ReadData();
}

/*!
  * @brief  Nastavi orientacijo zaslona.
  * @param  orientation zasuk zaslona, podan v obliki ILI9341_MISKO_ROTATE_{0,90,180,270}
  */
void ILI9341_SetOrientation(uint32_t orientation)
{
	ILI9341_Data_t command   = ILI9341_MAC; /* Memory Access Control */
	ILI9341_Data_t parameter = (ILI9341_Data_t)orientations[orientation];

	ILI9341_SetAddress(&command);
	ILI9341_SendData(&parameter, 1);

	switch (orientation) {
	case ILI9341_MISKO_ROTATE_0:
	case ILI9341_MISKO_ROTATE_270:
		LCD.width  = ILI9341_HEIGHT;
		LCD.height = ILI9341_WIDTH;
		break;
	default:
	case ILI9341_MISKO_ROTATE_90:
	case ILI9341_MISKO_ROTATE_180:
		LCD.width  = ILI9341_WIDTH;
		LCD.height = ILI9341_HEIGHT;
		break;
	}
	LCD.orientation = orientation;
}

/*!
  * @brief  Nastavi okno zapisovanja podatkov zaslona
  * @param  Xpos   x koordinata izhodišča
  * @param  Ypos   y koordinata izhodišča
  * @param  Height višina okna
  * @param  Width  širina okna
  */
void ILI9341_SetDisplayWindow(uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height)
{
	ILI9341_Data_t command;
	ILI9341_Data_t parameter[4];

	/* Column addr set, 4 args, no delay: XSTART = Xpos, XEND = (Xpos + Width - 1) */
	command = ILI9341_CASET;
	parameter[0] = (ILI9341_Data_t)(Xpos >> 8U);
	parameter[1] = (ILI9341_Data_t)(Xpos & 0xFFU);
	parameter[2] = (ILI9341_Data_t)((Xpos + Width - 1U) >> 8U);
	parameter[3] = (ILI9341_Data_t)((Xpos + Width - 1U) & 0xFFU);
	ILI9341_SetAddress(&command);
	ILI9341_SendData(parameter, 4);

	/* Row addr set, 4 args, no delay: YSTART = Ypos, YEND = (Ypos + Height - 1) */
	command = ILI9341_RASET;
	parameter [0] = (ILI9341_Data_t)(Ypos >> 8U);
	parameter [1] = (ILI9341_Data_t)(Ypos & 0xFFU);
	parameter [2] = (ILI9341_Data_t)((Ypos + Height - 1U) >> 8U);
	parameter [3] = (ILI9341_Data_t)((Ypos + Height - 1U) & 0xFFU);
	ILI9341_SetAddress(&command);
	ILI9341_SendData(parameter, 4);

	// Zapusti nastavitev okna v načinu za vpis barve v GRAM
	command = ILI9341_GRAM;
	ILI9341_SetAddress(&command);
}

/*!
  * @brief  Inicializacija krmilnika Ili9341
  * @param  color_space želen barvni prostor (ILI9341_COLORSPACE_RBG{565,666})
  * @param  orientation orientacija zaslona
  * @internal
  */
void ILI9341_Init(uint32_t color_space, uint32_t orientation)
{
	ILI9341_Data_t command;
	ILI9341_Data_t parameter[5];

	ILI9341_SetOrientation(orientation);
	ILI9341_SetDisplayWindow(0U, 0U, LCD.width, LCD.height);

	// Sleep out
	command = ILI9341_SLEEP_OUT;
	ILI9341_SetAddress(&command);
	HAL_Delay(200);

	// Display Normal mode
	command = ILI9341_NORMAL_MODE_ON;
	ILI9341_SetAddress(&command);
	HAL_Delay(100);

	// Pixel Format
	command = ILI9341_PIXEL_FORMAT;
	parameter[0] = color_space;
	ILI9341_SetAddress(&command);
	ILI9341_SendData(parameter, 1);
	HAL_Delay(100);

	// Update Interface control
	command = ILI9341_INTERFACE;
	parameter[0] = 0x49;
	parameter[1] = 0;
	parameter[2] = 0x20;
	ILI9341_SetAddress(&command);
	ILI9341_SendData(parameter, 3);

#ifdef LCD_TE_ENABLE
	// Enable TE
	command = ILI9341_TEON;
	parameter[0] = 1; /* VSYNC + HSYNC */
	ILI9341_SetAddress(&command);
	ILI9341_SendData(parameter, 1);
	HAL_Delay(100);


	// Enable TE scan line
	command = ILI9341_SET_TEAR_SCANLINE;
	parameter[0] = 0;
	parameter[1] = 0;
	ILI9341_SetAddress(&command);
	ILI9341_SendData(parameter, 2);
	HAL_Delay(100);
#endif
}

//! @brief Počakaj na prenos podatka FSMC->Ili9341.
void ILI9341_WaitTransfer()
{
#ifdef ILI9341_USEDMA
	while (HAL_DMA_GetState(&hLCDDMA) != HAL_DMA_STATE_READY);
#endif
}

//! @brief Strojno omogoči zaslon
void ILI9341_DisplayOn()
{
	ILI9341_Data_t command = ILI9341_DISPLAY_ON;
	ILI9341_SetAddress(&command);
}

//! @brief Strojno onemogoči zaslon - celoten zaslon postane bel
void ILI9341_DisplayOff()
{
	ILI9341_Data_t command = ILI9341_DISPLAY_OFF;
	ILI9341_SetAddress(&command);
}

//! @brief Zasuk barv zaslona
void ILI9341_InvertDisplay(uint8_t invert)
{
	ILI9341_Data_t command;

	command = (invert) ? ILI9341_DINVON : ILI9341_DINVOFF;
	ILI9341_SetAddress(&command);
}

//! @brief Postavi zaslon v spanje - celoten postane bel
void ILI9341_SetSleep(uint8_t state)
{
	ILI9341_Data_t command;

	command = (state) ? ILI9341_SLEEP : ILI9341_SLEEP_OUT;
	ILI9341_SetAddress(&command);
}

/*!
 * @brief Nastavitev območja strojnega zamika slike
 * @param start_pos začetna x koordinata
 * @param end_pos   končna x koordinata
 */
void ILI9341_SetScrollArea(uint16_t start_pos, uint16_t end_pos)
{
	ILI9341_Data_t command;
	ILI9341_Data_t parameter[6];

	// Ili9341 sprejema odmik od stranice, ne pa pikselske vrednosti!

	command = ILI9341_VSCRDEF;
	parameter[0] = (ILI9341_Data_t)(start_pos >> 8U);                    // Odmik z leve
	parameter[1] = (ILI9341_Data_t)(start_pos & 0xFFU);
	parameter[2] = (ILI9341_Data_t)((end_pos - start_pos) >> 8U);        // Širina polja
	parameter[3] = (ILI9341_Data_t)((end_pos - start_pos) & 0xFFU);
	parameter[4] = (ILI9341_Data_t)((ILI9341_HEIGHT - end_pos) >> 8U);
	parameter[5] = (ILI9341_Data_t)((ILI9341_HEIGHT - end_pos) & 0xFFU); // Odmik z desne
	ILI9341_SetAddress(&command);
	ILI9341_SendData(parameter, 6);
}

/*!
 * @brief Strojni pomik slike zaslona
 * @param position vrednost zamika slike
 * @param direction smer zamika (SCROLL_LEFT, SCROLL_RIGHT)
 */
void ILI9341_ScrollScreen(uint16_t position, uint8_t direction)
{
	ILI9341_Data_t command;
	ILI9341_Data_t parameter[2];

	command = ILI9341_VSCRSADD;

	if(direction == SCROLL_LEFT) {
		parameter[0] = (ILI9341_Data_t)(position >> 8U);
		parameter[1] = (ILI9341_Data_t)(position & 0xFFU);
	} else /* SCROLL_RIGHT */ {
		parameter[0] = (ILI9341_Data_t)((ILI9341_WIDTH - position) >> 8U);
		parameter[1] = (ILI9341_Data_t)((ILI9341_WIDTH - position) & 0xFFU);
	}

	ILI9341_SetAddress(&command);
	ILI9341_SendData(parameter, 2);
}

/*!
 * @brief Pridobi parameter zaslona
 * @param param parameter iz enumeratorja `LCD_Param'
 *
 * Možne opcije: LCD_WIDTH, LCD_HEIGHT, LCD_AREA, LCD_ORIENTATION.
 * @warning Zaslon mora biti predhodno inicializiran s funkcijo `LCD_Init()'!
 */
uint32_t ILI9341_GetParam(LCD_Param_t param)
{
	uint32_t value = 0;

	switch (param) {
	case LCD_WIDTH:
		value = LCD.width;
		break;
	case LCD_HEIGHT:
		value = LCD.height;
		break;
	case LCD_AREA:
		value = ILI9341_AREA;
		break;
	case LCD_ORIENTATION:
		value = LCD.orientation;
		break;
	default:
		break;
	}

	return value;
}
