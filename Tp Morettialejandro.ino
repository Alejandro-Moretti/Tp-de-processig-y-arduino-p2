int boton1 = 3;
int boton2 = 2;
int led1 = 12;
int led2 = 13;

bool estadoAnterior1 = 1;
bool estadoAnterior2 = 1;

void setup() {
  Serial.begin(9600);
  pinMode(boton1, INPUT);
  pinMode(boton2, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  int estado1 = digitalRead(boton1);
  int estado2 = digitalRead(boton2);

  // --- BOTONES FÍSICOS ---
  if (estado1 == 0 && estadoAnterior1 == 1) { 
    Serial.write('C');          
    digitalWrite(led1, HIGH);   
    delay(100);
    digitalWrite(led1, LOW);    
  }

  if (estado2 == 0 && estadoAnterior2 == 1) {
    Serial.write('D');          
    digitalWrite(led2, HIGH);   
    delay(100);
    digitalWrite(led2, LOW);    
  }

  estadoAnterior1 = estado1;
  estadoAnterior2 = estado2;

  // --- DATOS DESDE PROCESSING ---
  if (Serial.available() > 0) {
    char dato = Serial.read();

    if (dato == 'A') {
      digitalWrite(led1, HIGH);
      delay(300);
      digitalWrite(led1, LOW);
    }

    if (dato == 'B') {
      digitalWrite(led2, HIGH);
      delay(300);
      digitalWrite(led2, LOW);
    }
  }
}
/*import processing.serial.*; 

Serial Mipuerto; // Declara el objeto Serial

color ColorCuadrados1 = color(0,0,0);
color ColorCuadrados2 = color(0,0,0);
color ColorCuadrados3 = color(0,0,0);
color ColorCuadrados4 = color(0,0,0);

void setup() {
  size(700, 700); // Se necesita una ventana de visualización en Processing
  
  // Imprime una lista de los puertos disponibles para verificar
  println(Serial.list());
  
  // Crea el objeto 'Mipuerto', seleccionando el primer puerto de la lista
  Mipuerto = new Serial(this, Serial.list()[0], 9600); 
  
  // Configuración del texto
  textAlign(CENTER, CENTER);
  textSize(42);
  fill(0); // color del texto
}

void draw() {
  background(155);
  fill(ColorCuadrados1);
  rect(100,150,200,100); // 1

  fill(ColorCuadrados2);
  rect(400,150,200,100); // 2

  fill(ColorCuadrados3);
  rect(100,350,200,100); // 3

  fill(ColorCuadrados4);
  rect(400,350,200,100); // 4

  // Etiquetas de los rectángulos superiores
  fill(0); // color del texto
  text("E1", 200, 200);
  text("E2", 500, 200); 
  text("L1", 200, 400);
  text("L2", 500, 400);
  
   // Leer datos desde Arduino
  if (Mipuerto.available() > 0) {
    char dato = Mipuerto.readChar();
    println("Recibido: " + dato);

    if (dato == 'C') {
      ColorCuadrados3 = color(255, 255, 255); // L1 en blanco
      delay(300);
      ColorCuadrados3 = color(0, 0, 0);
    }
    if (dato == 'D') {
      ColorCuadrados4 = color(255, 255, 255); // L2 en blanco
      delay(300);
      ColorCuadrados4 = color(0, 0, 0);
    }
  }
}
void mousePressed(){
  if ((mouseX>100)&&(mouseX<300)&&(mouseY>150)&&(mouseY<250)){
    Mipuerto.write('A'); // envía una señal al Arduino
    ColorCuadrados1 =color(255,255,255);
    println("Enviado: A"); 
  }
  if ((mouseX>400)&&(mouseX<600)&&(mouseY>150)&&(mouseY<250)){
    Mipuerto.write('B'); // envía una señal diferente
    println("Enviado: B"); 
    ColorCuadrados2 =color(255,255,255);
}
}
void mouseReleased(){
  ColorCuadrados1 =color(0,0,0);
  ColorCuadrados2 =color(0,0,0);   
}
