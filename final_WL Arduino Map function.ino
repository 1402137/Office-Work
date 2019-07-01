#define echopin 2
#define trigpin 3

long duration, distance;
int numPins = 10;
int ledPins[] = { 4, 5, 6, 7, 8, 9, 10,11,12,13};
//int ledStates[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode (trigpin, OUTPUT);
  pinMode (echopin, INPUT );

  int i = 0;
  for(i=0; i < numPins; i++) {
      pinMode(ledPins[i], OUTPUT);
  }

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

    
    
    if (30 <= distance && distance < 35){
          Serial.println("Water level is high: Tank is full ");
          delay(100);
          //    digitalWrite(motor,LOW);
          //    delay(10);
          }


          
      else if (35<= distance && distance <= 45){
          Serial.println("Water level is medium: Tank is Normal");
          delay(100);
  
          int  outputValue = map(distance, 35,44,0,9);
          Serial.println(outputValue);
  
          for(int i=0;i<=outputValue;i++){
              digitalWrite(ledPins[i],HIGH);
              delay(100);
               
              if(i==outputValue){
                    delay(2000);
  
                  for(int j=i;j>-1;j--)
                      {
                      digitalWrite(ledPins[j],LOW);
                            delay(100);
                            }
                  
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
              }
  
  
        }
  
  }



    //digitalWrite(ledPins[outputValue],HIGH);
    //delay(1000);
    //digitalWrite(ledPins[outputValue],LOW);
    //delay(1000);
    



  
    else if (45 < distance ){
          Serial.println("Water level is low: Tank is empty ");
          delay(100);
          //    digitalWrite(motor,HIGH);
          ////    delay(10);
          }
    
}
