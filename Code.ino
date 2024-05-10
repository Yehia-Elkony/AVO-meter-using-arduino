#include   <Wire.h> 
#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7);   //rs,e,d4,d5,d6,d7



float Vm = 0.0; // unknown voltage
float R2=0; // unknown resistor

///Voltameter
void calculate_voltage() 
{ 

float r1= 10000.0;
float r2= 1000.0;
float v_ref=5.00;
int sensorValue =0.0;
float vin=0.0;
float r_ratio= (r2/(r1+r2));


for(int i=0;i<30;i++){
sensorValue = sensorValue +analogRead(A1);
delay(3);
}

sensorValue= sensorValue/30;
vin=((sensorValue*v_ref)/1023.0);
Vm=vin/r_ratio;
  
}

//////////////////////////////////////////////////////////////////////

//Ohmmeter
int analogPin= 0;
int V_measured= 0;
int Vin= 5;
float Vout= 0;


float buffer= 0;

int ch2K = 10;
int ch20K = 9;
int ch200K = 8;


int Scale2k=13  ;
int Scale20k=12;
int Scale200k=11;


}
void fn2kscale () 
{ 
    if (digitalRead(Scale2k)) 
    { 
  
  
      pinMode(ch2K,OUTPUT); 
      pinMode(ch20K,INPUT); 
      pinMode(ch200K,INPUT); 
      digitalWrite(ch2K,LOW); 
      
      float R1= 2.15; // Set this values to the value of the used resistor in 
      K ohms 
      V_measured= analogRead(analogPin);
      buffer= V_measured * Vin; 
      Vout= (buffer)/1024.0; //in volts 
      buffer= (Vin/Vout) −1; 
      R2= R1 * buffer*1000; //*1000 because we express it in ohms 
      
      if (R2 > 2200) 
      { 
      lcd.setCursor(0,1); 
      lcd.print(" Increase/insert"); 
      delay(1000); 
      lcd.clear(); 
      } 
      
      
      if (R2 < 2200) 
      { 
      lcd.setCursor(0,1); 
      lcd.print("R1: "); 
      lcd.print(R2); 
      lcd.setCursor(13,1); 
      lcd.print("Ohm"); 
      delay(1000); 
      } 
    }
}
void fn20kscale() { 
  if (digitalRead(Scale20k)) 
  { 
    pinMode(ch2K,INPUT); 
    pinMode(ch20K,OUTPUT); 
    pinMode(ch200K,INPUT); 
    digitalWrite(ch20K,LOW); 
    
    float R1= 21.3; // Set this values to the value of the used resistor in 
    K ohms 
    V_measured= analogRead(analogPin); //in 8bits 
    
    buffer= V_measured * Vin; 
    Vout= (buffer)/1024.0; //in volts 
    buffer= (Vin/Vout) −1; 
    R2= R1 * buffer; 
    
    if (R2 > 22) 
    { 
      lcd.setCursor(0,1); 
      lcd.print(" Increase/insert"); 
      delay(1000); 
      lcd.clear(); 
    } 
    
    
    if (R2 <22) 
    { 
    
    
      lcd.setCursor(0,1); 
      lcd.print("R2: "); 
      lcd.print(R2); 
      delay(1000); 
      lcd.setCursor(12,1); 
      lcd.print("Kohm"); 
      delay(1000); 
      } 
  } 
}
void fn200kscale(){ 
  if (digitalRead(Scale200k)) 
  { 
  
  
    pinMode(ch2K,INPUT); 
    pinMode(ch20K,INPUT); 
    pinMode(ch200K,OUTPUT); 
    
    digitalWrite(ch200K,LOW); 
    
    float R1= 275; // Set this values to the value of the used resistor in K 
    ohms 
    V_measured= analogRead(analogPin); //in 8bits 
    
    buffer= V_measured * Vin;
    Vout= (buffer)/1024.0; //in volts 
    buffer= (Vin/Vout) −1; 
    R2= R1 * buffer; 
    
    if (R2 > 300) 
      { 
      lcd.setCursor(0,1); 
      lcd.print("Insert Res."); 
      delay(1000); 
      lcd.clear(); 
      } 
    
    
    if (R2 < 300) 
      { 
      lcd.setCursor(0,1); 
      lcd.print("R3: "); 
      lcd.print(R2); 
      delay(1000); 
      lcd.setCursor(12,1); 
      lcd.print("Kohm"); 
      delay(1000); 
      } 
    } 
}
  

void resistance_calc(){
  ///////////////////-2k-/////////////////////
if (digitalRead(13))
{  

   fun2kscale();
}

///////////////////-20k-/////////////////////
else if (digitalRead(12))
{ 

 fun20kscale();
}


///////////////////-200k-/////////////////////
else if (digitalRead(11))
{ 
  fun200kscale();
}


if ( (digitalRead(Scale2k)==LOW) && (digitalRead(Scale20k)==LOW) && ( digitalRead(Scale200k)==LOW) ) 
  { 
  lcd.setCursor(0,1); 
  lcd.print("ScaleAndResistor"); 
  delay(1000); 
  } 

}


void setup() {

  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(V_measured,INPUT); 
  pinMode(analogPin,INPUT);

   //Detect the range mode (0-1kK; 10k-100k; 100k-1M)
  pinMode(Scale2k,INPUT);
  pinMode(Scale20k,INPUT);
  pinMode(Scale200k,INPUT);
 

//We set this pins as input for now. 
  pinMode(ch2K,INPUT);
  pinMode(ch20K,INPUT);
  pinMode(ch200K,INPUT);

}


void loop() {
  calculate_voltage();
  lcd.setCursor(0,0);
  lcd.print("V= ");
  lcd.print(Vm);
  lcd.setCursor(9,0);
  lcd.print("Volts");
  delay(10); 
  resistance_calc();

}