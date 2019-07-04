#define echopin D0
#define trigpin D1

long duration, distance;
int numPins = 8;
int ledPins[] = { D2,D3,D4,D5,D6,D7,D8,D9};
//int ledStates[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
#define motor D10

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  pinMode (trigpin, OUTPUT);
  pinMode (echopin, INPUT );
  pinMode (motor, OUTPUT);
  digitalWrite(motor,LOW);
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
          digitalWrite(motor,LOW);
          Serial.println("Water level is high: Tank is full ");
          delay(100);
          for(int i=0;i<=7;i++){
              digitalWrite(ledPins[i],HIGH);
              delay(10)
          }
            
             
          //    delay(10);
          }


          
      else if (35<= distance && distance <= 45){
          Serial.println("Water level is medium: Tank is Normal");
          delay(100);
  
          int  outputValue = map(distance, 36,43,0,7);
          Serial.println(outputValue);
  
          for(int i=0;i<=outputValue;i++){
              digitalWrite(ledPins[i],HIGH);
              delay(100);
               
//              if(i==outputValue){
//                    delay(2000);
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
//              }
  
  
        }
  
  }



    //digitalWrite(ledPins[outputValue],HIGH);
    //delay(1000);
    //digitalWrite(ledPins[outputValue],LOW);
    //delay(1000);
    



  
    else if (45 < distance ){
          digitalWrite(motor,HIGH);
          Serial.println("Water level is low: Tank is empty ");
          delay(100);
          for(int i=0;i<=7;i++){
              digitalWrite(ledPins[i],LOW);
              delay(10)
          }  
          ////    delay(10);
          }
    
}
