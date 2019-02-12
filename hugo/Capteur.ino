int percentage;
float volts;
    
#define MG_PIN (A8)
#define DC_GAIN (8.5)
#define READ_SAMPLE_INTERVAL (50)
#define READ_SAMPLE_TIMES (5)
#define ZERO_POINT_VOLTAGE (2.4/6.9)
#define REACTION_VOLTGAE (0.033)

float CO2Curve[3] = {2.602, ZERO_POINT_VOLTAGE, (REACTION_VOLTGAE/(2.602-3))};

void setup() {
   Serial.begin(9600);
   Serial.print("MG-811 Demostration\n");                
}

void loop() {
    volts = MGRead(MG_PIN);
    Serial.print("Tension:");
    Serial.print(volts); 
    Serial.println("V");

    percentage = MGGetPercentage(volts, CO2Curve);
    Serial.print("CO2:");
    if (percentage == -1) {
        Serial.print(" <400 ");
    } else {
        Serial.print(percentage);
    }
    Serial.print("ppm");
    delay(500);
}

float MGRead(int mg_pin) {
    int i;
    float v=0;
    for (i=0;i<READ_SAMPLE_TIMES;i++) {
        v += analogRead(mg_pin);
        delay(READ_SAMPLE_INTERVAL);
    }
    v = (v/READ_SAMPLE_TIMES) *5/1024 ;
    return v;  
}

int  MGGetPercentage(float volts, float *pcurve) {
   if ((volts/DC_GAIN ) >= ZERO_POINT_VOLTAGE) {
      return -1;
   } else { 
      return pow(10, ((volts/DC_GAIN)-pcurve[1])/pcurve[2]+pcurve[0]);
   }
}
