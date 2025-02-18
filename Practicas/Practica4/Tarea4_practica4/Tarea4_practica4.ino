#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>

BLEService accelerometerService("19B10000-E8F2-537E-4F6C-D104768A1214");
BLEFloatCharacteristic accelerometerCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);
BLEByteCharacteristic toggleCharacteristic("19B10002-E8F2-537E-4F6C-D104768A1214", BLEWrite);

bool accelerometerEnabled = true;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!BLE.begin()) {
    Serial.println("Failed to initialize BLE!");
    while (1);
  }

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  BLE.setLocalName("Arduino Nano 33 BLE");
  BLE.setAdvertisedService(accelerometerService);

  accelerometerService.addCharacteristic(accelerometerCharacteristic);
  accelerometerService.addCharacteristic(toggleCharacteristic);
  BLE.addService(accelerometerService);

  accelerometerCharacteristic.setValue(0);
  toggleCharacteristic.setValue(0);

  BLE.advertise();

  Serial.println("BLE Accelerometer Peripheral");
}

void loop() {
  BLEDevice central = BLE.central(); // dispositivo central 

  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());

    while (central.connected()) {
      if (toggleCharacteristic.written()) {
        // numero entero sin signo de 8 bits (almacena valores entre el 0 y 255)
        uint8_t value;
        toggleCharacteristic.readValue(value);

        if (value == 1) {
          accelerometerEnabled = true;
          Serial.println("Accelerometer enabled");
        } else {
          accelerometerEnabled = false;
          Serial.println("Accelerometer disabled");
        }

        toggleCharacteristic.setValue(0);
      }

      if (accelerometerEnabled) {
        float x, y, z;
        if (IMU.accelerationAvailable()) {
          IMU.readAcceleration(x, y, z);

          accelerometerCharacteristic.writeValue(x);
          accelerometerCharacteristic.writeValue(y);
          accelerometerCharacteristic.writeValue(z);

          delay(100);
        }
      }
    }

    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}

