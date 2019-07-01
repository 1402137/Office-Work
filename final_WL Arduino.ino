#define echopin 2
#define trigpin 3
long duration, distance;

#define greenled 4
#define yellowled 5
#define redled 6

#define motor 7


void setup() {
// put your setup code here, to run once:

Serial.begin(9600);
pinMode (trigpin, OUTPUT);
pinMode (echopin, INPUT );

pinMode (greenled, OUTPUT);
pinMode (yellowled, OUTPUT);
pinMode (redled, OUTPUT);
pinMode (motor, OUTPUT);

}




void loop() {
  // put your main code here, to run repeatedly:

    digitalWrite(trigpin,LOW);
    delayMicroseconds(5);
    
    digitalWrite(trigpin,HIGH);
    delayMicroseconds(10);

    digitalWrite(trigpin,LOW);

    duration=pulseIn (echopin,HIGH);
    
    distance= duration*0.034/2;
    delay (1000);

    Serial.println(distance);

    
    if (30 <= distance && distance < 33){
        Serial.println("Water level is high: Tank is full ");

        digitalWrite(greenled,HIGH);
        //    delay(10);
        digitalWrite(yellowled,LOW);
        //    delay(10);
        digitalWrite(redled,LOW);
        delay(100);
        digitalWrite(motor,LOW);
        //    delay(10);
      }

      
      else if (33<= distance && distance <= 45){
        Serial.println("Water level is medium: Tank is Normal");
        delay(100);
  
        digitalWrite(yellowled,HIGH);
        //    delay(10);
        digitalWrite(greenled,LOW);
        //    delay(10);
        digitalWrite(redled,LOW);
        //    delay(10);
        }


      //digitalWrite(ledPins[outputValue],HIGH);
      //delay(1000);
      //digitalWrite(ledPins[outputValue],LOW);
      //delay(1000);




  
    else if (45 < distance ){
        Serial.println("Water level is low: Tank is empty ");
        delay(100);
        //    digitalWrite(motor,HIGH);
        digitalWrite(redled,HIGH);
      //    delay(10);
        digitalWrite(greenled,LOW);
      //    delay(10);
        digitalWrite(yellowled,LOW);
      //    delay(10);
      digitalWrite(motor,HIGH);
    //    delay(10);
    ////    delay(10);
  }
    
}
