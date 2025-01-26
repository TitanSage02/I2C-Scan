#include <Wire.h>

const int I2C_SDA = 21;  // GPIO21
const int I2C_SCL = 22;  // GPIO22

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_SDA, I2C_SCL);
  
  Serial.println("\nDémarrage du scanner I2C...");
  delay(2000);
}

void loop() {
  byte error;
  byte address;
  int devices = 0;

  Serial.println("Scanning...");

  for(address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Périphérique trouvé à l'adresse 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println(" !");

      devices++;
    }
    else if (error == 4) {
      Serial.print("Erreur à l'adresse 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }    
  }

  if (devices == 0)
    Serial.println("Aucun périphérique trouvé !");
  else
    Serial.println("Scan terminé !\n");

  delay(5000); // Rescan toutes les 5 secondes
}