
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define echopin D0
#define trigpin D1

int duration, distance;
int numPins = 8;
int ledPins[] = { D2,D3,D4,D5,D6,D7,D8,D9};
//int ledStates[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
#define motor D10


const char* ssid = "ssl-e";
const char* password = "O1713O4771$";
const char* mqtt_server = "192.168.86.111";
//const char* mqtt_server = "iot.eclipse.org";





WiFiClient espClient;
PubSubClient client(espClient);
String topic = "test";

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

 

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}



void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
      Serial.print("Attempting MQTT connection...");
      // Create a random client ID
      String clientId = "ESP8266Client-";
      clientId += String(random(0xffff), HEX);
      // Attempt to connect
     if (client.connect(clientId.c_str())) {
        Serial.println("connected");
    } 
    
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  WiFi.begin(ssid, password);
  client.setServer(mqtt_server, 1883);

  pinMode (trigpin, OUTPUT);
  pinMode (echopin, INPUT );
  pinMode (motor, OUTPUT);
  digitalWrite(motor,HIGH);
  


  int i = 0;
  for(i=0; i < numPins; i++) {
      pinMode(ledPins[i], OUTPUT);
  }

}


 


void loop() {
 if (!client.connected()) {
    reconnect();
  }
////  client.loop();




  
    digitalWrite(trigpin,LOW);
    delayMicroseconds(5);
    
    digitalWrite(trigpin,HIGH);
    delayMicroseconds(10);

    digitalWrite(trigpin,LOW);

    duration=pulseIn (echopin,HIGH);
    
    distance= duration*0.034/2;
    delay (1000);

    Serial.println(distance);
    
    int message1=distance-33;
    String message= String(message1);
    //client.publish(topic.c_str(), "hello");
//    client.publish(topic.c_str(),message.c_str());

    
    
    if (30 <= distance && distance < 35){
          digitalWrite(motor,HIGH);
          Serial.println("Water level is high: Tank is full ");
          client.publish(topic.c_str(), " Tank is Full");
           for(int i=0;i<=7;i++){
              digitalWrite(ledPins[i],HIGH);
              
              
          
           }
          //    delay(10);
          }



          
      else if (35<= distance && distance <= 45){
          Serial.println("Water level is medium: Tank is Normal");
          delay(100);
          client.publish(topic.c_str(), "Tank is Normal");

          
          for(int i=0;i<=7;i++){
              digitalWrite(ledPins[i],LOW);  
          
           }
          
          int  outputValue = map(distance, 36,43,7,0);
          Serial.println(outputValue);
  
          for(int i=0;i<=outputValue;i++){
              digitalWrite(ledPins[i],HIGH);
              delay(100);
               
//              if(i==outputValue){
//                    delay(1000);
//  
//                  for(int j=i;j>-1;j--)
//                      {
//                      digitalWrite(ledPins[j],LOW);
//                            delay(100);
//                            }
                  
                //  digitalWrite(ledPins[0],LOW);
                //  digitalWrite(ledPins[1],LOW);
                //  digitalWrite(ledPins[2],LOW);
                //  digitalWrite(ledPins[3],LOW);
                //  digitalWrite(ledPins[4],LOW);
                //  digitalWrite(ledPins[5],LOW);
                //  digitalWrite(ledPins[6],LOW);
                //  digitalWrite(ledPins[7],LOW);
                //  digitalWrite(ledPins[8],LOW);
                //  digitalWrite(ledPins[9],LOW);
//              /}
  
  
        }
  
  }



    //digitalWrite(ledPins[outputValue],HIGH);
    //delay(1000);
    //digitalWrite(ledPins[outputValue],LOW);
    //delay(1000);
    



  
    else if (45 < distance ){
          digitalWrite(motor,LOW);
          Serial.println("Water level is low: Tank is empty ");
          client.publish(topic.c_str(), "Tank is empty");
          delay(100);
          for(int i=0;i<=7;i++){
              digitalWrite(ledPins[i],LOW);
              delay(0);
          
           }
          ////    delay(10);
          }
  
}
