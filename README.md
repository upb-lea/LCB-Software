
# Programming with Code Composer Studio (CCS)
## Code Composer Studio: Settings for code from this repository
For equal code indentations, perform the following steps:
 * `Window` -> `Preferences` -> `Show advanced settings`
 * `Window` -> `Preferences` -> `C/C++` -> `Code Style` -> `Formatter` -> `Edit ...` -> `Tab size: 2` -> `Apply` -> `OK` -> `Apply and Close`

## Code Composer Studio: Import software project and adapt it to your computer filepaths
 * `Project` -> `Import CCS Projects...` -> Choose your project to import
 * In `Select search-directory` browse to your project (e.g. `.../LEA_control_board/software/01_Control_boards/F28386D_GPIO/`
 * Press `Finish`

## Code Composer Studio: Change C2000Ware version and compiler version
This steps are necessary if the original project was developed with different versions for the C2000Ware and compilers. Both steps needs to be done for `RAM` and for `FLASH`. Select between both modes with the arrow at the `hammer`-symbol.

### Adapt C2000ware version
 * right click on project -> `Properties` -> `General` -> `Products`
 * Select `C2000Ware` and click `Edit`
 * Select your installed C2000Ware version in the right drop-down menu

### Adapt compiler version
 * right click on project -> `Properties` -> `General` -> `Projects`
 * Select your installed compiler version 
 
## C2000 Dual-Core-Debugging
This section describes the simultaneous debugging of two cores of a Texas Instruments C2000 DualCore processor.

 * __Step 1:__ Chose target configuration for `CPU1` oder `CPU2` -> `right click` -> `Launch Selected Configuration`
 * __Step 2:__ `right click` on `Debug-Probe CPU1` -> `Connect Target` -> `Run` -> `Load` -> `Load Program…` -> `Browse project…` -> `CPU 1-Projekt` -> `FLASH` or `RAM` -> chose `.out-file` -> `OK` -> `OK`
 * __Step 3:__ `right click` on `Debug-Probe CPU2` -> `Connect Target` -> `Run` -> `Load` -> `Load Program…` -> `Browse project…` -> `CPU 2-Projekt` -> `FLASH` or `RAM` -> chose `.out-file` -> `OK` -> `OK`
 * __Step 4:__ click on `Debug-Probe CPU1` -> `Resume (Start)` -> click on `Debug-Probe CPU2` -> `Resume (Start)`
 * __Step 5:__ For debugging (read/write registers/global variables) the respective debug sample (`CPU 1` or `CPU 2`) must be clicked. The registers/variables of the other CPU are not active during this.

# Debugger
## Flash XDS100 Firmware to FTDI Chip:
 * Watch this [video](https://www.youtube.com/watch?v=vZaF5ckf3OQ) first
 * Download FT Prog [here](https://ftdichip.com/utilities/)
 * Load the configuration file for XDS100v2 programmer: `File` -> `Open template` -> [Modified template](/debugger_configuration/XDS100v2_UART.xml)
 * Right click on `Device: 0` -> right click -> `Apply Template` -> `Template: XDS100v2_UART.xml`
 * Flash file: `Programm Devices` -> `Program`
 
Note: 
It is very important to click on `Apply Template` as shown in the video. Otherwise the controller will not be programmed correctly!

Note: 
The modified file has the `Virtual COM Port` enabled to provide UART communication. This is not implemented as in the video. To enable this, see the figure. 
![](/documentation/virtual_com_port.png)
