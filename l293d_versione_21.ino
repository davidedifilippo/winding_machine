const int enable = 11;
const int controllo_ramo_A = 8; //Devono sempre essere uno il complemento dell'altro
const int controllo_ramo_B = 7;

const int progButton = 5;
const int upButton = 4;
const int downButton = 3;

int cw = 1; //variabile di controllo della direzione -> orario predefinito
int numeroSpire = 5000;
int giriMinuto = 0;

long int tempoAvvio = 0;
int giriEffettuati = 0;



void setup()
{
	pinMode(enable,OUTPUT);
  	pinMode(controllo_ramo_A, OUTPUT);
    pinMode(controllo_ramo_B, OUTPUT);
  
    pinMode(progButton,INPUT);
  	pinMode(upButton, INPUT);
    pinMode(downButton, INPUT);
  
    Serial.begin(9600);
  
    Serial.println("Ready");
  
   //se non si preme prg si rest nel loop di interrogazione dei pulsanti up e down
  
   if(cw != 0)
   {digitalWrite(controllo_ramo_A, HIGH);
    digitalWrite(controllo_ramo_B, LOW);
   }
   else
   {digitalWrite(controllo_ramo_A, LOW);
    digitalWrite(controllo_ramo_B,HIGH);
   }
  
    //avvio il motore con la velocità e il verso impostati
  
    int pot = analogRead(A0);
  
  	giriMinuto = (analogRead(A0)/1023.0)*1000;
    
  	tempoAvvio = millis();
    
    Serial.println(giriMinuto);
    Serial.println((giriMinuto/1000.0)*255);
    
  	analogWrite(enable, (giriMinuto/1000.0)*255);
  
  
}

void loop()
{
  giriEffettuati = (giriMinuto/60.0) * ((millis()-tempoAvvio)/1000.0);
  Serial.println(giriEffettuati);
  if(giriEffettuati >= numeroSpire)
  {
    analogWrite(enable,0);
   setup();
  }
 
}
