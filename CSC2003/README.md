# CSC2003 : Embedded Systems & Sensor Programming

For this attempt will be in MSP432. <br>
MSP432 is done in doubles



*.elf file is for debugging  <br>
*.uf2 file is a usb flashing format

# Setup process

vscode  <br>
Extension required  <br>
CMake <br>
CMake Tools 

 <br>

vscode > command palette

```> CMake: Configure```


.vscode > settings.json
 ``` JSON
 {
    "cmake.environment": {
      "PICO_SDK_PATH":"<replace-with-pico-sdk-dir>"
    },
    "C_Cpp.default.configurationProvider": "ms-vscode.cmake-tools",
    "cmake.exportCompileCommandsFile": true,
    "cmake.generator": "Unix Makefiles",
    "cmake.sourceDirectory": "${workspaceFolder}/CSC2003"
}
  
 ```

 # Lab Information

| Lab   | Information                    | Others                  |
| ----- |:------------------------------:| ----------------------- |
| Lab01 | Basic & Setup                  | With LED onboard blink - Week 1 not required for submission  |
| Lab02 | Configuring pin as Output (LED)| With LED onboard blink (RGB) with S1 and S2 button press |
