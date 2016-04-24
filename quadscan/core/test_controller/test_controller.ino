#define pot A2

void setup() {
  // put your setup code here, to run once:
  pinMode(pot, INPUT);
  
  pinMode(3, OUTPUT); //throttle
  pinMode(5, OUTPUT); //roll
  pinMode(6, OUTPUT); //pitch
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int x = analogRead(pot) / 4;
//  
  Serial.println(x == 255 ? 254 : x);

  analogWrite(3, x == 255 ? 254 : x);
  analogWrite(5, x == 255 ? 254 : x);
  analogWrite(6, x == 255 ? 254 : x);
  analogWrite(9, x == 255 ? 254 : x);
//  analogWrite(10, 198); //equls to Flight mode 1
  ///  analogWrite(10, x);
  analogWrite(11, x == 255 ? 254 : x);


//  //CENTER
//  analogWrite(3, 127);
//  analogWrite(5, 127);
//  analogWrite(6, 127);
//  analogWrite(9, 127);
//  analogWrite(10, 127);
//  analogWrite(11, 127);
//
//  //MAX
//  analogWrite(3, 254);
//  analogWrite(5, 254);
//  analogWrite(6, 254);
//  analogWrite(9, 254);
//  analogWrite(10, 254);
//  analogWrite(11, 254);
}
