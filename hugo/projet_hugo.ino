#define PAR A8
#define VOL 52

float tens;
int ppm;
float CO2Curve[3] = {2.602, 0.22, (0.03/(2.602-3))};

void setup() {
  Serial.begin(9600);
  Serial.println("Démarage du systeme...");
  digitalWrite(VOL, HIGH);
}

void loop() {
  tens = TRead(PAR);
  Serial.print("Tension: ");
  Serial.print(tens);
  Serial.println(" mV");
  ppm = getPPM(tens, CO2Curve);
  Serial.print("CO2: ");
  if (ppm == -1) {
    Serial.print( "<400" );
  } else {
    Serial.print(ppm);
  }
  Serial.println(" PPM");
}

float TRead(int pin) {
  float tens_ = 0;
  for (int i=0; i<49; i++) {
    tens_+=analogRead(pin);
    delay(10);
  }
  tens_ = (tens_/50)*5/1024;
  return tens_;
}

int getPPM(float tens, float* pcurve) {
  if (tens/8.5 >= 0.22) {
    return -1;
  } else {
    return pow(10, ((tens/8.5)-pcurve[1])/pcurve[2]+pcurve[0]);
  }
  
}

