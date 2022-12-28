Firmware package for ST-Link/V2-1 platform (Nucleo-like).
Please read carefully the license agreement (software_license_agreement_image_v2.pdf).
By using this package you accept the mentionned conditions.

DFU_Appli.bin DFU_Appli.hex: bootstrap code to program on ST-Link/V2-1 platform
(Nucleo-like). Do not use on ST-Link/V2 platforms: uncompatible hardware. See Nucleo
schematics: http://www.st.com/st-web-ui/static/active/en/resource/technical/layouts_and_diagrams/schematic_pack/nucleo_64pins_sch.zip.

Then restart the board in order to make the bootstrap code running.

Then program the USB-updatable firmware by launching progSTLink.bat (which is using ST-LinkUpgrade.exe and
STLinkUSBDriver.dll).

This batch file might be customized:

- the name of the mass storage volume can be modified (defaulted to "TEST"), respecting the following constraints:
  1. Must not exceed 11 characters
  2. Must not use ST-reserved names (starting by NUCLEO, NODE, DISCO, EVAL)

- the maximum of current asked by the device to the host during the USB enumeration (-usb_max_current) was
  defaulted to 300mA. It is recommended to define a value as close as possible to the real board consumption:

  1. if less than required is declared, the device is out of USB specification and the behaviour depends on
     the host implementation (tolerant or not to over-consumption, depending on the whole USB-tree context)

  2. if more than required is declared, it is possible that the host refuses the connection even in conditions
     where it should have been possible

  Note that the USB specification does not allow a device to use more than 100mA from the USB bus before host's
  acknowledgment.

- by default the board is not "mbed-enabled" (no mbed.htm file). To make it mbed-enabled, you need:
  1. to get an mbed-boardId from ARM (four digits string: XXXX)
  2. add in the command line of progSTLink.bat: -board XXXX


Notes:
1. Do not use ST-LinkUpgrade.exe in graphical mode for the initial programming: the mass storage volume name won't
be programmed correctly. When launched in graphical mode after the initial programming, ST-LinkUpgrade.exe
automatically updates the firmware without modifying the parameters given during the initial (command-line)
programming.

2. The volume name, usb_max_current and boardId parameters might be modified after the initial programming, by launching
the batch file again (note that this also reprograms the whole firmware). The mbed boardId can be removed with the parameter
"-deleteB".

3. In the life time of the product, the firmware may be updated by launching more recent versions of ST-LinkUpgrade,
available at st.com (from any NUCLEO page for instance). It is not recommended to communicate to end users the batch
file parameters, because any change in such parameters might affect the support efficiency.