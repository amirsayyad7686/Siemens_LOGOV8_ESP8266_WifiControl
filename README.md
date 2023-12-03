# Siemens_LOGOV8_ESP8266_WifiControl
Connection between LOGOV8 and control with ESP8266 over WIFI

![19869_2](https://github.com/amirsayyad7686/Siemens_LOGOV8_ESP8266_WifiControl/assets/78236642/6e04f102-e3b9-4c08-89ae-749672574f20)

## Get start

At first should program PLC and assign IP address and variables register address with following example

1- Download example file to LOGO (2x OUTPUT 1x timer for reading delay time)
![1](https://github.com/amirsayyad7686/Siemens_LOGOV8_ESP8266_WifiControl/assets/78236642/9357f927-f6b1-44af-aea4-9184242d0065)

2- Set timer parameter as a register address (in this example is address is 0)
![2](https://github.com/amirsayyad7686/Siemens_LOGOV8_ESP8266_WifiControl/assets/78236642/2ba40dd5-d132-4d11-81cc-ae3a72a025e9)

3- This is LOGO v8 register table as you can see coils addresses start with 8193(Q1 = 8192)
and also there is 4 parameters that accessible on Modbus communications and in Arduino library
![3](https://github.com/amirsayyad7686/Siemens_LOGOV8_ESP8266_WifiControl/assets/78236642/67a904d3-b190-49bf-a53c-41423b14ca69)

4- After setup LOGO we going to ESP8266 and coding for Modbus interface 
in Arduino Modbus library there is different functions for Read and Write on register addresses as you can see in below image

For Reading registers
![4](https://github.com/amirsayyad7686/Siemens_LOGOV8_ESP8266_WifiControl/assets/78236642/d3d8d8b9-0caf-4bc9-86ba-5f19fc279ef9)

For Write registers
![4](https://github.com/amirsayyad7686/Siemens_LOGOV8_ESP8266_WifiControl/assets/78236642/1a5d3928-f597-4ed2-b545-e6f433340492)


> [!IMPORTANT]
> Attention to R/W registers 
> Only Coil and Holding Register are able to write

`readIsts (Arduino) => Discrete Input (LOGO)`

`readHreg,writeHreg (Arduino) => Holding Register (LOGO)`

`readCoil,writeCoil (Arduino) => Coil (LOGO)`

`readIreg (Arduino) => Input Register (LOGO)`


5- Compile example code on esp8266 and remember to change remote IP address to LOGO IP 
and here is example for a coil that turing off and on with cycle 2secs

`const int REG = 8192; //its for Q1`

`trans = mb.writeCoil(remote, REG, false);//for off`

`trans = mb.writeCoil(remote, REG, true);//for on`

and read holding register that we defined before in LOGO for timer value

`trans = mb.readHreg(remote, 0, &Timer); // 0 is register address`
