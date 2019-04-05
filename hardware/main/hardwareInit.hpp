
void hardwareinit(){
  pinMode(PB6, INPUT_PULLUP);
  pinMode(PB7, INPUT_PULLUP);
  pinMode(PB8, INPUT_PULLUP);
  Serial1.begin(115200, SERIAL_8N1);
  Serial1.println("Serial1 Start");
  Serial3.begin(115200);
}


