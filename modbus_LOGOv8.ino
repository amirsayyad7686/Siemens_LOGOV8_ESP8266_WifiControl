#if defined(ESP8266)
 #include <ESP8266WiFi.h>
#elif defined(ESP32)
 #include <WiFi.h>
#else
#error "Unsupported platform"
#endif
#include <ModbusTCP.h>

const int REG = 8192;               // Modbus register offset for Q coil 8193-8212 in LOGOv8.3 (8192 is Q1)
IPAddress remote(192, 168, 1, 3);  // Address of Modbus Slave device

ModbusTCP mb;  //ModbusTCP object

void setup() {
  Serial.begin(115200);
 
  WiFi.begin("ssid", "pass");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mb.client();
}

uint16_t trans;
uint16_t Timer;
void loop() {
  if (mb.isConnected(remote)) {   // Check if connection to Modbus Slave is established
    trans = mb.writeCoil(remote, REG, true);  //Write Coil - remote:LOGO ip , REG:regsiter address , true for on false for off
    delay(2000);
    trans = mb.readHreg(remote, 0, &Timer);// Initiate Read Hreg from Modbus Server -on delay timer value is in 0 register address
    Serial.println("ON Delay Timer Value:");
    Serial.println(Timer);
    trans = mb.writeCoil(remote, REG, false);  // Initiate Read Hreg from Modbus Server
    delay(2000);

//this is a simple 2 secs timer for off and on cycle Q1 coil in LOGO


    while(mb.isTransaction(trans)) {  // Check if transaction is active
      mb.task();
      delay(10);
    }
  } else {
    mb.connect(remote);           // Try to connect if no connection
  }
  delay(100);

}