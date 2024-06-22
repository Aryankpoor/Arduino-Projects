String voice;
int RED = 2;
int GREEN = 3 ;
int BLUE = 4;
int YELLOW = 5;
void RedOn(){
digitalWrite (RED, LOW);
}
void RedOff(){
digitalWrite (RED, HIGH);
}
void GreenOn(){
digitalWrite (GREEN, LOW);
}
void GreenOff(){
digitalWrite (GREEN, HIGH);
}
void BlueOn(){
digitalWrite (BLUE, LOW);
}
void BlueOff(){
digitalWrite (BLUE, HIGH);
}
void YellowOn(){
digitalWrite (YELLOW, LOW);
}
void YellowOff(){
digitalWrite (YELLOW, HIGH);
}
void allon() {
digitalWrite (RED, LOW);
digitalWrite (GREEN, LOW);
digitalWrite (BLUE, LOW);
digitalWrite (YELLOW, LOW);
}
void alloff() {
digitalWrite (RED, HIGH);
digitalWrite (GREEN, HIGH);
digitalWrite (BLUE, HIGH);
digitalWrite (YELLOW, HIGH);
}
void setup() {
Serial.begin(9600);
pinMode(RED, OUTPUT);
pinMode(GREEN, OUTPUT);
pinMode(BLUE, OUTPUT);
pinMode(YELLOW, OUTPUT);
}
void loop() {
while(Serial.available()) {
delay(10);
char c=Serial.read();
if(c=='#')
{break; }
voice += c;
}
if (voice.length() > 0) {
Serial.println(voice);
if (voice == "on" || voice == "all")
{
allon() ;
}
else if (voice == "switch off" || voice=="switch off all")
{
alloff() ;
}
else if(voice =="living room" || voice =="living room on"){
RedOn();
}
else if(voice =="switch off living room" || voice =="living room off"){
RedOff();
}
else if(voice =="kitchen" || voice =="kitchen on"){
YellowOn();
}
else if( voice =="switch off kitchen" || voice =="kitchen off" ){
YellowOff();
}
else if(voice =="study room" || voice =="study room on"){
BlueOn();
}
else if(voice =="switch off study room" || voice =="study room off"){
BlueOff();
}
else if(voice =="fan" || voice =="fan on"){
GreenOn();
}
else if(voice =="switch off fan" || voice =="fan off"){
GreenOff();
}
voice="";
}
}
