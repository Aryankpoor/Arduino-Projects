
const int ShiftPWM_latchPin=8;

const bool ShiftPWM_invertOutputs = false;


const bool ShiftPWM_balanceLoad = false;

#include <ShiftPWM.h>  
void oneByOne(void);
void inOutTwoLeds(void);
void inOutAll(void);
void alternatingColors(void);
void hueShiftAll(void);
void randomColors(void);
void fakeVuMeter(void);
void rgbLedRainbow(unsigned long cycleTime, int rainbowWidth);
void printInstructions(void);

unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;
unsigned int numRegisters = 6;
unsigned int numOutputs = numRegisters*8;
unsigned int numRGBLeds = numRegisters*8/3;
unsigned int fadingMode = 0; 

unsigned long startTime = 0; 

void setup(){
  while(!Serial){
    delay(100); 
  }
  Serial.begin(9600);


  ShiftPWM.SetAmountOfRegisters(numRegisters);

  ShiftPWM.SetPinGrouping(1); 
  
  ShiftPWM.Start(pwmFrequency,maxBrightness);
  printInstructions();
}

void loop()
{    
  if(Serial.available()){
    if(Serial.peek() == 'l'){
      
      ShiftPWM.PrintInterruptLoad();
    }
    else if(Serial.peek() == 'm'){
      // Print instructions again
      printInstructions();
    }
    else{
      fadingMode = Serial.parseInt();
      Serial.print("Mode set to "); 
      Serial.print(fadingMode); 
      Serial.print(": ");
      startTime = millis();
      switch(fadingMode){
      case 0:
        Serial.println("All LED's off");
        break;
      case 1:
        Serial.println("Fade in and out one by one");
        break;
      case 2:
        Serial.println("Fade in and out all LED's");
        break;
      case 3:
        Serial.println("Fade in and out 2 LED's in parallel");
        break;
      case 4:
        Serial.println("Alternating LED's in 6 different colors");
        break;
      case 5:
        Serial.println("Hue shift all LED's");
        break;
      case 6:
        Serial.println("Setting random LED's to random color");
        break;
      case 7:
        Serial.println("Fake a VU meter");
        break;
      case 8:
        Serial.println("Display a color shifting rainbow as wide as the LED's");
        break;         
      case 9:
        Serial.println("Display a color shifting rainbow wider than the LED's");
        break;     
      default:
        Serial.println("Unknown mode!");
        break;
      }
    }
    while (Serial.read() >= 0){
      ; 
    }
  }
  switch(fadingMode){
  case 0:
    // Turn all LED's off.
    ShiftPWM.SetAll(0);
    break;
  case 1:
    oneByOne();
    break;
  case 2:
    inOutAll();
    break;
  case 3:
    inOutTwoLeds();
    break;
  case 4:
    alternatingColors();
    break;
  case 5:
    hueShiftAll();
    break;
  case 6:
    randomColors();
    break;
  case 7:
    fakeVuMeter();
    break;
  case 8:
    rgbLedRainbow(3000,numRGBLeds);
    break;
  case 9:
    rgbLedRainbow(10000,5*numRGBLeds);    
    break;   
  default:
    Serial.println("Unknown Mode!");
    delay(1000);
    break;
  }
}

void oneByOne(void){ 
  unsigned char brightness;
  unsigned long fadeTime = 500;
  unsigned long loopTime = numOutputs*fadeTime*2;
  unsigned long time = millis()-startTime;
  unsigned long timer = time%loopTime;
  unsigned long currentStep = timer%(fadeTime*2);

  int activeLED = timer/(fadeTime*2);

  if(currentStep <= fadeTime ){
    brightness = currentStep*maxBrightness/fadeTime; 
  }
  else{
    brightness = maxBrightness-(currentStep-fadeTime)*maxBrightness/fadeTime;
  }
  ShiftPWM.SetAll(0);
  ShiftPWM.SetOne(activeLED, brightness);
}

void inOutTwoLeds(void){ 
  unsigned long fadeTime = 500;
  unsigned long loopTime = numOutputs*fadeTime;
  unsigned long time = millis()-startTime;
  unsigned long timer = time%loopTime;
  unsigned long currentStep = timer%fadeTime;

  int activeLED = timer/fadeTime;
  unsigned char brightness = currentStep*maxBrightness/fadeTime;

  ShiftPWM.SetAll(0);
  ShiftPWM.SetOne((activeLED+1)%numOutputs,brightness);
  ShiftPWM.SetOne(activeLED,maxBrightness-brightness);
}

void inOutAll(void){  
  unsigned char brightness;
  unsigned long fadeTime = 2000;
  unsigned long time = millis()-startTime;
  unsigned long currentStep = time%(fadeTime*2);

  if(currentStep <= fadeTime ){
    brightness = currentStep*maxBrightness/fadeTime; ///fading in
  }
  else{
    brightness = maxBrightness-(currentStep-fadeTime)*maxBrightness/fadeTime; ///fading out;
  }
  ShiftPWM.SetAll(brightness);
}

void alternatingColors(void){ // Alternate LED's in 6 different colors
  unsigned long holdTime = 2000;
  unsigned long time = millis()-startTime;
  unsigned long shift = (time/holdTime)%6;
  for(unsigned int led=0; led<numRGBLeds; led++){
    switch((led+shift)%6){
    case 0:
      ShiftPWM.SetRGB(led,255,0,0);    // red
      break;
    case 1:
      ShiftPWM.SetRGB(led,0,255,0);    // green
      break;
    case 2:
      ShiftPWM.SetRGB(led,0,0,255);    // blue
      break;
    case 3:
      ShiftPWM.SetRGB(led,255,128,0);  // orange
      break;
    case 4:
      ShiftPWM.SetRGB(led,0,255,255);  // turqoise
      break;
    case 5:
      ShiftPWM.SetRGB(led,255,0,255);  // purple
      break;
    }
  }
}

void hueShiftAll(void){  // Hue shift all LED's
  unsigned long cycleTime = 10000;
  unsigned long time = millis()-startTime;
  unsigned long hue = (360*time/cycleTime)%360;
  ShiftPWM.SetAllHSV(hue, 255, 255); 
}

void randomColors(void){  // Update random LED to random color. Funky!
  unsigned long updateDelay = 100;
  static unsigned long previousUpdateTime;
  if(millis()-previousUpdateTime > updateDelay){
    previousUpdateTime = millis();
    ShiftPWM.SetHSV(random(numRGBLeds),random(360),255,255);
  }
}

void fakeVuMeter(void){ // imitate a VU meter
  static unsigned int peak = 0;
  static unsigned int prevPeak = 0;
  static unsigned long currentLevel = 0;
  static unsigned long fadeStartTime = startTime;
  
  unsigned long fadeTime = (currentLevel*2);// go slower near the top

  unsigned long time = millis()-fadeStartTime;
  currentLevel = time%(fadeTime);

  if(currentLevel==peak){
    // get a new peak value
    prevPeak = peak;
    while(abs(peak-prevPeak)<5){
      peak =  random(numRGBLeds); // pick a new peak value that differs at least 5 from previous peak
    }
  }

  if(millis() - fadeStartTime > fadeTime){
    fadeStartTime = millis();
    if(currentLevel<peak){ //fading in
      currentLevel++;
    }
    else{ //fading out
      currentLevel--;
    }
  }
  // animate to new top
  for(unsigned int led=0;led<numRGBLeds;led++){
    if(led<currentLevel){
      int hue = (numRGBLeds-1-led)*120/numRGBLeds; // From green to red
      ShiftPWM.SetHSV(led,hue,255,255); 
    }
    else if(led==currentLevel){
      int hue = (numRGBLeds-1-led)*120/numRGBLeds; // From green to red
      int value;
      if(currentLevel<peak){ //fading in        
        value = time*255/fadeTime;
      }
      else{ //fading out
        value = 255-time*255/fadeTime;
      }
      ShiftPWM.SetHSV(led,hue,255,value);       
    }
    else{
      ShiftPWM.SetRGB(led,0,0,0);
    }
  }
}

void rgbLedRainbow(unsigned long cycleTime, int rainbowWidth){
 
  unsigned long time = millis()-startTime;
  unsigned long colorShift = (360*time/cycleTime)%360; 

  for(unsigned int led=0;led<numRGBLeds;led++){
    int hue = ((led)*360/(rainbowWidth-1)+colorShift)%360; 
    ShiftPWM.SetHSV(led, hue, 255, 255); 
  }
}

void printInstructions(void){
  Serial.println("---- ShiftPWM Non-blocking fades demo ----");
  Serial.println("");
  
  Serial.println("Type 'l' to see the load of the ShiftPWM interrupt (the % of CPU time the AVR is busy with ShiftPWM)");
  Serial.println("");
  Serial.println("Type any of these numbers to set the demo to this mode:");
  Serial.println("  0. All LED's off");
  Serial.println("  1. Fade in and out one by one");
  Serial.println("  2. Fade in and out all LED's");
  Serial.println("  3. Fade in and out 2 LED's in parallel");
  Serial.println("  4. Alternating LED's in 6 different colors");
  Serial.println("  5. Hue shift all LED's");
  Serial.println("  6. Setting random LED's to random color");
  Serial.println("  7. Fake a VU meter");
  Serial.println("  8. Display a color shifting rainbow as wide as the LED's");
  Serial.println("  9. Display a color shifting rainbow wider than the LED's");  
  Serial.println("");
  Serial.println("Type 'm' to see this info again");  
  Serial.println("");
  Serial.println("----");
}