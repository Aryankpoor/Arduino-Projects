#define MIC A0

int sig = 0;

void setup() {
 pinMode(2, OUTPUT);
 pinMode(3, OUTPUT);
 pinMode(4, OUTPUT);
 pinMode(5, OUTPUT);
 pinMode(6, OUTPUT);
 pinMode(7, OUTPUT);
 pinMode(8, OUTPUT);
 pinMode(9, OUTPUT);
 pinMode(10, OUTPUT);
 pinMode(11, OUTPUT);
}

void led() {
 sig = analogRead(MIC)*50;

 if (sig>1)  {digitalWrite(2, HIGH);} else {digitalWrite(2, LOW);}
 if (sig>200) {digitalWrite(3, HIGH);} else {digitalWrite(3, LOW);}
 if (sig>300) {digitalWrite(4, HIGH);} else {digitalWrite(4, LOW);}
 if (sig>400) {digitalWrite(5, HIGH);} else {digitalWrite(5, LOW);}
 if (sig>500) {digitalWrite(5, HIGH);} else {digitalWrite(6, LOW);}
 if (sig>600) {digitalWrite(5, HIGH);} else {digitalWrite(7, LOW);}
 if (sig>700) {digitalWrite(5, HIGH);} else {digitalWrite(8, LOW);}
 if (sig>800) {digitalWrite(5, HIGH);} else {digitalWrite(9, LOW);}
 if (sig>900) {digitalWrite(5, HIGH);} else {digitalWrite(10, LOW);}
 if (sig>950) {digitalWrite(5, HIGH);} else {digitalWrite(11, LOW);}
}
void loop() {
 led();
}
