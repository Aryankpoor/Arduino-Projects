int i;
int led[]={2,3,4,5,6,7,8,9,10,11,12,13};

void setup() {
 for(i=0;i<12;i++)
 {pinMode(led[i],OUTPUT);}
}
void loop() {
  for(i=0;i<12;i++)
  {digitalWrite(led[i],HIGH);
  delay(50);
  digitalWrite(led[i],LOW);}
  for(i=11;i>=0;i--)
  {digitalWrite(led[i],HIGH);
  delay(50);
  digitalWrite(led[i],LOW);
}}
