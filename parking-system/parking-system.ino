#include <Servo.h>



Servo servo;



int trigPin = 11;

int echoPin = 12;



long duration;

int distance;



void setup() 

{

  servo.attach(13);

  servo.write(180);

 delay(2000);

  

// Output

pinMode(trigPin, OUTPUT);

//  Input 

pinMode(echoPin, INPUT);

}

void loop() 

{

// Clear trigPin

digitalWrite(trigPin, LOW);

delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds

digitalWrite(trigPin, HIGH);

delayMicroseconds(10);

digitalWrite(trigPin, LOW);


duration = pulseIn(echoPin, HIGH);

// Calculating the distance

distance= duration*0.034/2;

// Prints the distance on the Serial Monitor

Serial.print("Distance: ");

Serial.println(distance);

if ( distance <= 25   ) // Change Distance according to Ultrasonic Sensor Placement

 {



servo.write(180);

delay(3000);

 } 

else 

{

servo.write(90);



 }



}