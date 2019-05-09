//mosquitto_pub -h 192.168.100.60 -t "test" -m "0" for led turn off
//mosquitto_pub -h 192.168.100.60 -t "test" -m "1"  for led turn on

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
// Define NodeMCU D3 pin  connect to LED

// Update these with values suitable for your network.
const char* ssid = "ssl5";
const char* password = "$$Lwebteam2017#";
const char* mqtt_server = "192.168.100.60";
//const char* mqtt_server = "iot.eclipse.org";



String topic = "test";
int led = D3;
int inputPin = D7;
int lastPirValue = LOW;

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

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
    } else {
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
  client.setServer(mqtt_server, 1883);
 digitalWrite(led,LOW);
  pinMode(inputPin, INPUT);
  pinMode(led,OUTPUT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int pirValue = digitalRead(inputPin);
  digitalWrite(led,LOW);
  
    if (pirValue == HIGH) {
      String message = String(pirValue);
      client.publish(topic.c_str(), message.c_str());
      digitalWrite(led,HIGH);
      delay(1000);
    }

    if (pirValue == LOW) {
      String message = String(pirValue);
      client.publish(topic.c_str(), message.c_str());
      digitalWrite(led,LOW);
      delay(1000);
    }
    Serial.println(pirValue);
    

    delay( 1000);
  
}
