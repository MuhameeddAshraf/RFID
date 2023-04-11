#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define RST_PIN         3         // Configurable, see typical pin layout above
#define SS_PIN          2        // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
LiquidCrystal_I2C lcd(0x27,20,4);
String uid1 = "63 5F 42 A7";
String uid2 = "00 00 00 00";
String uid3 = "00 00 00 00";
String uid4 = "00 00 00 00";

void setup() 
{
  lcd.init();                      
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop() 
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("    Scan Tag    ");
 // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  lcd.clear();
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == uid1) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("     ***********    ");
    lcd.setCursor(0, 1);
    lcd.print("   Access Granted  !");
    lcd.setCursor(0, 2);
    lcd.print(" The Arm is opening ");
    lcd.setCursor(0, 3);
    lcd.print("     ***********    ");
    delay(3000);
  }

/*
 else if (content.substring(1) == uid2) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    lcd.setCursor(0,0);
    lcd.print("Tag 02");
    lcd.setCursor(0,1);
    lcd.print("Authorized access");
    delay(3000);
  }

 else if (content.substring(1) == uid3) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    lcd.setCursor(0,0);
    lcd.print("Tag 03");
    lcd.setCursor(0,1);
    lcd.print("Authorized access");
    delay(3000);
  }
  
 else if (content.substring(1) == uid4) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    lcd.setCursor(0,0);
    lcd.print("Tag 04");
    lcd.setCursor(0,1);
    lcd.print("Authorized access");
    delay(3000);
    lcd.clear();
  }
  */
 else   {
    Serial.println(" Access Denied");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("     **********     ");
    lcd.setCursor(0, 1);
    lcd.print("</>    <SORRY>   </>");
    lcd.setCursor(0, 2);
    lcd.print("    Access Denied!  ");
    lcd.setCursor(0, 3);
    lcd.print("     **********");
    delay(3000);
  }
} 
