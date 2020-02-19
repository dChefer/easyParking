#include <NewPing.h>  
#include <LiquidCrystal_I2C.h>   


#define SONAR_NUM   6 // Define o numero de sensores  
#define MAX_DISTANCE 7 // Distancia maxima    
#define PING_INTERVAL 33 
  
unsigned long pingTimer[SONAR_NUM]; 
unsigned int cm[SONAR_NUM];  
uint8_t currentSensor = 0;       

   //vagas
int pinLedRed1 = 6;    
int pinLedBlue1 = 7; 

int pinLedRed2 = 4;  
int pinLedBlue2 = 5; 

int pinLedRed3 = 3;  
int pinLedGreen3 = 2;

int pinLedRed4 = 8;  
int pinLedGreen4 = 9;

int pinLedRed5 = 10;  
int pinLedGreen5 = 11;

int pinLedRed6 = 12;  
int pinLedGreen6 = 13;

  //contador de vagas
int freeVacancies = 6;   
int occupiedVacancies = 0;  
int sensor1 = 0;    
int sensor2 = 0;     
int sensor3 = 0;
int sensor4 = 0;
int sensor5 = 0;
int sensor6 = 0;
   
  //display
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);; 

   //Sensor Ultrasonico
NewPing sonar[SONAR_NUM] =   
{   
   
  NewPing(38, 39, MAX_DISTANCE), 
  NewPing(36, 37, MAX_DISTANCE), 
  NewPing(34, 35, MAX_DISTANCE),
  NewPing(32, 33, MAX_DISTANCE),
  NewPing(30, 31, MAX_DISTANCE), 
  NewPing(28, 29, MAX_DISTANCE), 
};


void setup()   
{    
  lcd.begin(16,2); 
  lcd.clear();   
  pingTimer[0] = millis() + 75;      
  for (uint8_t i = 1; i < SONAR_NUM; i++)   
   pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;  
  
  pinMode(pinLedRed1, OUTPUT);    
  pinMode(pinLedBlue1, OUTPUT);
     
  pinMode(pinLedRed2, OUTPUT);    
  pinMode(pinLedBlue2, OUTPUT);
   
  pinMode(pinLedRed3, OUTPUT);    
  pinMode(pinLedGreen3, OUTPUT); 

  pinMode(pinLedRed4, OUTPUT);    
  pinMode(pinLedGreen4, OUTPUT);
  
  pinMode(pinLedRed5, OUTPUT);    
  pinMode(pinLedGreen5, OUTPUT);

  pinMode(pinLedRed6, OUTPUT);    
  pinMode(pinLedGreen6, OUTPUT);
 }  
   
void loop() 
{  
   
  // Loop entre todos os sensores 
  for (uint8_t i = 0; i < SONAR_NUM; i++) {  
   if (millis() >= pingTimer[i]) {
    pingTimer[i] += PING_INTERVAL * SONAR_NUM;     
    if (i == 0 && currentSensor == SONAR_NUM - 1) oneSensorCycle();   
    sonar[currentSensor].timer_stop();     
    currentSensor = i;               
    cm[currentSensor] = 0;           
    sonar[currentSensor].ping_timer(echoCheck);  
   }  
 }  
    
 //Calcula a quantidade de vagas disponiveis e ocupadas  
 occupiedVacancies = sensor1 + sensor2 + sensor3 + sensor4 + sensor5 + sensor6;  
 freeVacancies = 6 - occupiedVacancies;  
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  
 lcd.print("Vagas Livres = ");  
 lcd.print(freeVacancies);  
 lcd.setCursor(0,1);  
 lcd.print("Vagas Ocupa. = ");  
 lcd.print(occupiedVacancies);  
}  
   
void echoCheck() { //Se receber um sinal (eco), calcula a distancia  
  if (sonar[currentSensor].check_timer())  
   cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;  
 }  
   
void oneSensorCycle() { // Ciclo de leitura do sensor  
  for (uint8_t i = 0; i < SONAR_NUM; i++) {  
   if (cm[0] > 1 && cm[0] < 50)   
   {  
     digitalWrite(pinLedRed1, 1);  
     digitalWrite(pinLedBlue1, 0);  
     sensor1 = 1; 
   }  
   else 
   {  
     digitalWrite(pinLedRed1, 0);  
     digitalWrite(pinLedBlue1, 1);  
     sensor1 = 0; 
   }   
   
   if (cm[1] > 1 && cm[1] < 50) 
   {  
     digitalWrite(pinLedRed2, 1);  
     digitalWrite(pinLedBlue2, 0);  
     sensor2 = 1; 
   }  
   else 
   {  
     digitalWrite(pinLedRed2, 0);  
     digitalWrite(pinLedBlue2, 1);  
     sensor2 = 0; //Marca a vaga 2 como livre  
   }
   if (cm[2] > 1 && cm[2] < 50)   
   {  
     digitalWrite(pinLedRed3, 1);  
     digitalWrite(pinLedGreen3, 0);  
     sensor3 = 1; 
   }  
   else 
   {  
     digitalWrite(pinLedRed3, 0);  
     digitalWrite(pinLedGreen3, 1);  
     sensor3 = 0; //Marca a vaga 1 como livre  
   }
      if (cm[3] > 1 && cm[3] < 50)   
   {  
     digitalWrite(pinLedRed4, 1);  
     digitalWrite(pinLedGreen4, 0);  
     sensor4 = 1; 
   }  
   else 
   {  
     digitalWrite(pinLedRed4, 0);  
     digitalWrite(pinLedGreen4, 1);  
     sensor4 = 0; //Marca a vaga 1 como livre   
   }

   if (cm[4] > 1 && cm[4] < 50)   
   {  
     digitalWrite(pinLedRed5, 1);  
     digitalWrite(pinLedGreen5, 0);  
     sensor5 = 1; 
   }  
   else 
   {  
     digitalWrite(pinLedRed5, 0);  
     digitalWrite(pinLedGreen5, 1);  
     sensor5 = 0; //Marca a vaga 1 como livre   
   }

   if (cm[5] > 1 && cm[5] < 50)   
   {  
     digitalWrite(pinLedRed6, 1);  
     digitalWrite(pinLedGreen6, 0);  
     sensor6 = 1; 
   }  
   else 
   {  
     digitalWrite(pinLedRed6, 0);  
     digitalWrite(pinLedGreen6, 1);  
     sensor6 = 0; //Marca a vaga 1 como livre   
   }
   
   //Imprime os valores 
   Serial.print("Sensor : "); 
   Serial.print(i);   
   Serial.print(" = ");  
   Serial.print(cm[i]);  
   Serial.print(" cm - ");  
  }  
  Serial.println();  
}  
