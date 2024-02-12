#include <Arduino.h>

double NOTEC = 1047;
double NOTECs = 1109;
double NOTED = 1175;
double NOTEEb = 1245;
double NOTEE = 1319;
double NOTEF = 1397;
double NOTEFs = 1480;
double NOTEG = 1568;
double NOTEGs = 1661;
double NOTEA = 1760;
double NOTEBb = 1865;
double NOTEB = 1976;
double REST = 1;

#define button 16
#define buzzer 22 

//Camila Cabello - Havana
double Song[] = {NOTEBb,NOTED,NOTED,NOTEBb,NOTEBb,NOTEG, NOTED,NOTEC,NOTED,NOTEEb,NOTED,NOTEC 
                  ,NOTEBb,NOTED,NOTED,NOTEBb,NOTEBb,NOTEG, NOTED,NOTEC,NOTED,NOTEEb,NOTED,NOTEC
                  ,NOTEBb,NOTED,NOTED,NOTEBb,NOTEBb,NOTEG, NOTED,NOTEC,NOTED,NOTEEb,NOTED,NOTEC
                  ,NOTEBb,NOTED,NOTEBb,NOTED,NOTEC,NOTED,NOTEC,NOTEBb,NOTED,NOTEA};

double melody[] = {1,1,1,1,1,2, 1,1,1,1,1,1, 1,1,1,1,1,2, 1,1,1,1,1,1, 1,1,1,1,1,2, 1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,2};

hw_timer_t *My_timer = NULL;

// This is the Timer ISR. It is automatically called 
// on a timer alarm event.
void IRAM_ATTR onTimer(){
  digitalWrite(buzzer, !digitalRead(buzzer)); 
}

int songspeed = 0;
double speed[] = {0.75, 1, 1.25, 1.5, 1.75}; 

void IRAM_ATTR Pushbutton(){
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if(interrupt_time - last_interrupt_time >500){
    songspeed += 1;
  }
  last_interrupt_time = interrupt_time; 
}

void setup() {
  pinMode(button, INPUT);
  pinMode(buzzer, OUTPUT); 
  attachInterrupt(button, &Pushbutton, FALLING);
  My_timer = timerBegin(0, 80, true);  // use tiemr 0 and set prescale to 80 so 1 tick is 1 uSec
  timerAttachInterrupt(My_timer, &onTimer, true); // point to the ISR
  //timerAlarmWrite(My_timer, 1000, true);  // set alarm every 1 sec
  //timerAlarmEnable(My_timer);  // enable the alarm
}

double Notepirate;
double durations;
int Playspeed;

void loop() {
  int Size = sizeof(melody)/sizeof(melody[0]);
  for(int i = 0; i < Size ; i+=1){
    Playspeed = songspeed%(sizeof(speed)/sizeof(speed[0]));
    Notepirate = 1000000/(2*Song[i]);
    durations = (melody[i]*300)/((speed[Playspeed]));

    timerAlarmWrite(My_timer, Notepirate, true);
    delay(durations);

    timerAlarmWrite(My_timer, 800000, true);
    delay(durations * 0.05);

    timerAlarmEnable(My_timer);
  }
}

