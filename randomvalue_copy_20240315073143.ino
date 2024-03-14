#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
// Potentiometer is connected to GPIO 34 (Analog ADC1_CH6) 
int mydata=0;

// variable for storing the potentiometer value
int potValue = 0;
/* define the characteristic and it's propeties */
BLECharacteristic customCharacteristic(
  BLEUUID((uint16_t)0x1A00),
  BLECharacteristic::PROPERTY_READ |
  BLECharacteristic::PROPERTY_NOTIFY
);

/* define the UUID that our custom service will use */
#define serviceID BLEUUID((uint16_t)0x1700)

/* This function handles server callbacks */
bool deviceConnected = false;
class ServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* MyServer) {
      deviceConnected = true;
    };
    void onDisconnect(BLEServer* MyServer) {
      deviceConnected = false;
    }
};

void setup() {
  Serial.begin(115200);
  BLEDevice::init("MyESP32"); // Name your BLE Device
  BLEServer *MyServer = BLEDevice::createServer();  //Create the BLE Server
  MyServer->setCallbacks(new ServerCallbacks());  // Set the function that handles server callbacks
  BLEService *customService = MyServer->createService(serviceID); // Create the BLE Service
  customService->addCharacteristic(&customCharacteristic);  // Create a BLE Characteristic
  customCharacteristic.addDescriptor(new BLE2902());  // Create a BLE Descriptor
  MyServer->getAdvertising()->addServiceUUID(serviceID);  // Configure Advertising
  customService->start(); // Start the service  
  MyServer->getAdvertising()->start();  // Start the server/advertising
  
  Serial.println("Waiting for a client to connect....");
}
void loop() {

  // Reading potentiometer value
  mydata=random(0,1000);
  Serial.println(mydata);
  delay(500);

      
        char buffer[20];
        dtostrf(mydata,1,0,buffer);
       customCharacteristic.setValue((char*)&buffer);
        customCharacteristic.notify();
        

      }
    