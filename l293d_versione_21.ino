const int enablePin = 11;

const int pinControllo_ramo_sx = 8; 
const int pinControllo_ramo_dx = 7;

const int progButton = 4;
const int upButton = 3;
const int downButton = 2;

int cw = 1; //variabile di controllo della direzione -> orario predefinito
int numeroSpire = 5000;

int giriMinuto = 0;

long int tempoAvvio = 0;
int giriEffettuati = 0;



void setup()
{
    pinMode(enablePin,OUTPUT);
    pinMode(pinControllo_ramo_sx, OUTPUT);
    pinMode(pinControllo_ramo_dx, OUTPUT);
  
    pinMode(progButton,INPUT);
    pinMode(upButton, INPUT);
    pinMode(downButton, INPUT);
  
  
    Serial.begin(9600);
    Serial.println("Setup macchina avvolgitrice! ");
 
   //se non si preme prg si resta nel loop di interrogazione 
   //dei pulsanti up e down
   Serial.println("Setup numero avvolgimenti: ");
 
  while(!digitalRead(progButton)){
    if (digitalRead(upButton)) { //se premo up
      numeroSpire = numeroSpire +100;
      Serial.println(numeroSpire);
    } 
    if (digitalRead(downButton)) { //se premo down
      numeroSpire = numeroSpire -100;
      Serial.println(numeroSpire);
    }
    delay(100);
  }
  delay(100); //evita di saltare il blocco successivo a causa dei rimbalzi del pulsante prog
 
  Serial.println("Setup verso di rotazione: ");
  while(!digitalRead(progButton)){
    if (digitalRead(upButton)) { //se premo up
      cw = 0; //verso antiorario
      Serial.println(cw);
    } 
    if (digitalRead(downButton)) { //se premo down
      cw=1;	//verso orario
      Serial.println(cw);
    }
    delay(100);
  }
  
  
   if(cw != 0)
   {digitalWrite(pinControllo_ramo_sx, HIGH);
    digitalWrite(pinControllo_ramo_dx, LOW);
   }
   else
   {
    digitalWrite(pinControllo_ramo_sx, LOW);
    digitalWrite(pinControllo_ramo_dx,HIGH);
   }
  
    //avvio il motore con la velocità e il verso impostati
  
    int pot = analogRead(A0);
    Serial.print(pot); //imposto al 50% ad esempio
  
    delay(2000);
  
    giriMinuto = (pot/1023.0)*1000; //suppongo 1000 rpm velocità massima di rotazione 
    
    int duty = (giriMinuto/1000.0)*255; 
   
    //Il duty cycle del segnale PWM determina la tensione di alimentazione motore: 
    //duty = 255 ->motore 1000 rpm
    //duty = 128 -> motore 500 rpm
    
    Serial.print("giriMinuto: ");
    Serial.println(giriMinuto);
    Serial.print("Duty Cycle: ");
    Serial.println(duty);
    
    delay(1000);
    
    analogWrite(enablePin, (giriMinuto/1000.0)*255); //Imposto il pwm al valore desiderato
  	tempoAvvio = millis();  
    
}

void loop()
{
  giriEffettuati = (giriMinuto/60.0) * ((millis()-tempoAvvio)/1000.0); //giri/secondo * secondi = giri fino ad ora
  Serial.println(giriEffettuati);
  if(giriEffettuati >= numeroSpire)
  {
    analogWrite(enablePin,0); //Ho finito. Arresto motore cc
    delay(1000);
    setup(); //Torno all'inizio
  }
 
}
