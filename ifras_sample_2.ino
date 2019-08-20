#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>


#define fire 25
#define police 27
#define sens 26
#define smoke 15
#define reset_button 35
#define extra_pin 36
int buzzer_pin=2;

int buttonstate_fire = 0; 
int buttonstate_police = 0; 
int buttonstate_sens = 0; 
int buttonstate_smoke=0;
int reset_state=0;

const char* ssid = "ssl-e";
//const char* ssid = "gourab";
const char* password =  "O1713O4771$";
//const char* password =  "123123123";
const char* mqttServer = "192.168.86.111";
const int mqttPort = 1883;

 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  pinMode(fire, INPUT);
  pinMode(police, INPUT);
  pinMode (sens, INPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode (reset_button, INPUT);
  pinMode(extra_pin, OUTPUT);
  
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
    }
 
  Serial.println("Connected to the WiFi network");
  client.setServer(mqttServer, mqttPort);
  while (!client.connected()) {
      Serial.println("Connecting to MQTT...");
      String clientId = "ESP32Client-";
      clientId += String(random(0xffff), HEX);
      
      
       if (client.connect(clientId.c_str())) {
         Serial.println("connected");
         } 
    
       else {
         delay(200);
         }
   }
 
 
}

void buzzer(){
if(buttonstate_fire ==1 || buttonstate_police ==1 ||buttonstate_sens ==1 || buttonstate_smoke ==1 ){
    if(reset_state == 0){
    digitalWrite(buzzer_pin, HIGH);
    }
   
  
  }
if(reset_state == 1){
   digitalWrite(buzzer_pin, LOW);
   }
  
}

void JsonModule(){
  StaticJsonBuffer<300> JSONbuffer;
  JsonObject& JSONencoder = JSONbuffer.createObject();

  JSONencoder["police_btn"] = buttonstate_police;
  JSONencoder["fire_btn"] = buttonstate_fire;
 
  JSONencoder["flame_sensor"] = buttonstate_sens;
  JSONencoder["smoke_sensor"] = buttonstate_smoke;
  JSONencoder["reset_stat"] = reset_state;
  JSONencoder["device_id"] = "ifras-01";
  
  char JSONmessageBuffer[100];
  JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  Serial.println("Sending message to MQTT topic..");
  Serial.println(JSONmessageBuffer);
 
  if (client.publish("ifras/devices", JSONmessageBuffer) == true) {
    Serial.println("Success sending message");
    } 
  else {
    Serial.println("Error sending message");
    }
 

  Serial.println("-------------");
  delay(10);
}

void loop() {
  client.loop();
  
  client.publish("esp/test", "Hello from test");
  buttonstate_fire = digitalRead(fire);
  buttonstate_police = digitalRead(police);
  buttonstate_sens = digitalRead(sens);
  buttonstate_smoke=digitalRead(smoke);
  reset_state=digitalRead(reset_button);

  //Buzzer control module
  buzzer();

  //json module
  JsonModule();
  
  delay(100);
  
}
