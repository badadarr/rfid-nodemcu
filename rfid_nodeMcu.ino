#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 2 //d4
#define RST_PIN 0 //d3

MFRC522 mfrc522(SS_PIN, RST_PIN);   // mendefinisikan pin diatas

void setup() 
{
  Serial.begin(9600);   // menghubungkan baud serial monitor
  SPI.begin();      // komunikasi nodemcu dan rfid
  mfrc522.PCD_Init();   // inisiasi modul rfid
  Serial.println("Put your card to the reader...");
}

void loop() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) // memindai kartu 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) // membaca kartu yang sudah di pindai
  {
    return;
  }
  
  //menampilkan Tulisan "UID tag" di serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  
  for (byte i = 0; i < mfrc522.uid.size; i++) // mengkonversi tipe data kartu menjadi angka yang mudah dibaca
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  Serial.println();
  Serial.print("Pesan : ");
  content.toUpperCase();
  if (content.substring(1) == "09 C7 69 99"){ //ID Kartu yang akan di scan
    Serial.println("Kartu Cocok");
    Serial.println();
    delay(500);
  }
  
  else if (content.substring(1) == "79 D0 24 A3"){
    Serial.println(" Kartu Cocok");
    Serial.println();
    delay(500);
   
  } else {
    Serial.println("Kartu Tidak Cocok");
    delay(500);
  }  
}
