#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <DHT.h>


// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "Hoa Luc"
#define WIFI_PASSWORD "0814897423"

// For the following credentials, see examples/Authentications/SignInAsUser/EmailPassword/EmailPassword.ino

/* 2. Define the API Key */


/* 3. Define the RTDB URL */
#define DATABASE_URL "myweb-e69aa-default-rtdb.firebaseio.com" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app



// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;
#define BUZZER D0
#define LED D1
#define DHTPIN 14    // Chân dữ liệu của DHT 11 , với NodeMCU chân D5 GPIO là 14
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);


bool buzzerOn = false;
bool den1 = false;

unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;

void setup()
{

  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  pinMode(BUZZER, OUTPUT);
  

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to Wi-Fi");
  unsigned long ms = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }

  dht.begin();
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  config.signer.test_mode = true;
  
  fbdo.setBSSLBufferSize(4096 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);
  Firebase.begin(&config, &auth);

}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (millis() - sendDataPrevMillis > 2000 )
  {
    sendDataPrevMillis = millis();

    // Serial.print("Nhiet do: ");
    // Serial.print(t);
    // Serial.print("*C "); 
    Serial.printf("Nhiet do: %f°C \n", t);
    Serial.printf("Set float... %s\n", Firebase.setFloat(fbdo, "/nghean/nhietdo", t) ? "ok" : fbdo.errorReason().c_str());
    // Serial.print("Do am: ");
    // Serial.print(h);
    // Serial.print("% ");
    Serial.printf("Do am: %f \n", h);
    Serial.printf("Set float... %s\n", Firebase.setFloat(fbdo, "/nghean/doam", h) ? "ok" : fbdo.errorReason().c_str());

  }

    Serial.printf("Set bool... %s\n", Firebase.getBool(fbdo, F("/booking/book"), &den1) ? "ok" : fbdo.errorReason().c_str());

  if(den1){
      digitalWrite(LED, HIGH);
      Serial.printf("Lamp: ON\n");
  }
  else {
      digitalWrite(LED, LOW);
      Serial.printf("Lamp: OFF\n");
  }
   Serial.printf("Set bool... %s\n", Firebase.getBool(fbdo, F("/hotline/dienthoai"), &buzzerOn) ? "ok" : fbdo.errorReason().c_str());
  
  // Tùy thuộc vào giá trị đọc được từ Firebase, bật hoặc tắt buzzer
  if (buzzerOn) {
    // Bật buzzer
    tone(BUZZER,3100);
    
    
  } else {
    // Tắt buzzer
    noTone(BUZZER);
    
  }
}