int s1 = 10;
int s2 = 9;
int s3 = 8;
int s4 = 7;
int b = 11;
int bs;
long r;


void setup ()
{
  pinMode (s1, OUTPUT);
  pinMode (s2, OUTPUT);
  pinMode (s3, OUTPUT);
  pinMode (s4, OUTPUT);
  pinMode (b, INPUT);
  randomSeed(analogRead(0));
}

void loop()
{
  bs = digitalRead(b);
  
  if (bs == LOW)
  {
    r = random(1, 7);
    shuffle();
    if (r == 1)
    {
      one();
    }
    if (r == 2)
    {
      two();
    }
    if (r == 3)
    {
      three();
    }
    if (r == 4)
    {
      four();
    }
    if (r == 5)
    {
      five();
    }
   if (r == 6)
    {
      six();
    }
    delay(3000);
  }
  else
  {
  digitalWrite (s1, LOW);
  digitalWrite (s2, LOW);
  digitalWrite (s3, LOW);
  digitalWrite (s4, LOW);
  }
}
void off()
{
  digitalWrite (s1, LOW);
  digitalWrite (s2, LOW);
  digitalWrite (s3, LOW);
  digitalWrite (s4, LOW);
}
void shuffle()
{
  one();
  delay(100);
  off();
  delay(100);
  two();
  delay(100);
  off();
  delay(100);
  three();
  delay(100);
  off();
  delay(100);
  four();
  delay(100);
  off();
  delay(100);
  five();
  delay(100);
  off();
  delay(100);
  six();
  delay(100);
  off();
  delay(200);
}
void one()
{
  digitalWrite (s4, HIGH);
}
void two()
{
  digitalWrite (s2, HIGH);
}
void three()
{
  digitalWrite (s4, HIGH);
  digitalWrite (s2, HIGH);
}
void four()
{
  digitalWrite (s1, HIGH);
  digitalWrite (s3, HIGH);
}
void five()
{
  digitalWrite (s1, HIGH);
  digitalWrite (s3, HIGH);
  digitalWrite (s4, HIGH);
}
void six()
{
  digitalWrite (s1, HIGH);
  digitalWrite (s2, HIGH);
  digitalWrite (s3, HIGH);
}

