#include <LiquidCrystal_I2C.h>
#include <time.h> //Para la semilla del random
#define pinInicioBus 5
#define pinBtnUp 3
#define pinBtnDown 2
#define pinBtnSel 4
#define tLetra 300 //tiempo para desplazar las letras

bool btnUp;
bool btnDown;
bool btnSel;

LiquidCrystal_I2C lcd(39, 16, 2);
short state = 0;
String q; //pregunta elegida aleatoriamente
short numSel=1; //numero elegido
String questions[5] = {
  "... de que cuentes un secreto?",
  "... de que bailes?",
  "... de que grites algo vergonzoso?",
  "... de que llames a tu ex?",
  "... de que pases CUV?"
};

byte signo[8] = { //signo de pregunta ¿
  0b00100,
  0b00000,
  0b00100,
  0b01000,
  0b10000,
  0b10001,
  0b01110,
  0b00000
};

unsigned long t0; //timer para mostrar mensajes
uint8_t iLetra; //indice para mostrar mensajes

void writeToDisplay(short n, bool display){ /*Pone un numero en 
                                              uno de los dispays
                                              7 segmentos*/
  for (int i = 0; i < 4; i++){
    digitalWrite(i + pinInicioBus + 4*display, (n >> i&1));
  }
}

void mostrarInicio(){
  lcd.write(0);
  lcd.print("Que probabilid-");
  lcd.setCursor(0, 1);
  lcd.print("ad hay...");
  writeToDisplay(12, 0);
  writeToDisplay(12, 1);
}

void setup() {
  Serial.begin(9600);
  pinMode(pinBtnUp, INPUT);
  pinMode(pinBtnDown, INPUT);
  pinMode(pinBtnSel, INPUT);

  for (int i = pinInicioBus; i < pinInicioBus + 8; i++){
    pinMode(i, OUTPUT);
  }
  
  lcd.createChar(0, signo);
  lcd.init();
  lcd.backlight();
  mostrarInicio();

  srand(time(NULL));
}

void loop() {
  if (state == 0){ //Se espera a iniciar el juego con un botoó

    if (digitalRead(pinBtnSel)){
      Serial.println("Presionado");
      btnSel = true;
    } else if (btnSel){
      Serial.println("Soltado");
      btnSel = false;
      int i = rand() % 5;
      q = questions[i]; //Se elige pregunta al azar
      lcd.clear();
      writeToDisplay(1, 0); //Se escribe 1 en el primer display
      state = 1; //Se cambia al siguiente estado
    }
  }

  else if (state == 1){ /*Se procede a mostrar la pregunta y esperar 
                    la selección del numero*/
    if ((millis() - t0) >= tLetra){ //Se desplazan las letras
      lcd.setCursor(0, 0);
      Serial.print(q.substring(iLetra) + "                ");
      lcd.print(q.substring(iLetra) + "                ");
      iLetra++;
      if (iLetra == q.length()) iLetra = 0;
      t0 = millis();
    }
    
    if (digitalRead(pinBtnUp)){
      Serial.println("Presionado");
      btnUp = true;
    } else if (btnUp){
      Serial.println("Soltado");
      btnUp = false;
      if (numSel < 6) numSel++;
      writeToDisplay(numSel, 0);
    }
    if (digitalRead(pinBtnDown)){
      Serial.println("Presionado");
      btnDown = true;
    } else if (btnDown){
      Serial.println("Soltado");
      btnDown = false;
      if (numSel > 1) numSel--;
      writeToDisplay(numSel, 0);
    }
    if (digitalRead(pinBtnSel)){
      btnSel = true;
    } else if (btnSel){
      btnSel = false;
      state = 2;
      for (int i = 1; i < 6*5; i++){/*El segundo display muestra
                                      números rápidamente*/
        writeToDisplay(i%6, 1);
        delay(80);
      }
      short numRand = (rand() % 6) + 1; 
      writeToDisplay(numRand, 1); //mostrar random en el segundo display
      
      lcd.clear();
      if (numSel == numRand) lcd.print("Haz el reto!");
      else lcd.print("Trata otra vez!");
      lcd.setCursor(0, 1);
      lcd.print("Push to reset...");
      state = 2;
    }
  }
  else if (state == 2){ //Esperar boton para volver a empezar
    if (digitalRead(pinBtnSel)){
      btnSel = true;
    } else if (btnSel){
      btnSel = false;
      state = 0;
      
      lcd.clear(); 
      mostrarInicio();
    }
  }
}


