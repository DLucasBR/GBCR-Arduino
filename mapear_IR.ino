/*Mapear pulsos de IR
 * Baseado em codigo de dominio publico ladyada.net 
*/
 
#define IRpin_PIN PIND
#define IRpin 2
 
#define MAXPULSE 65000
#define RESOLUTION 20
 
uint16_t pulses[250][2]; 
uint8_t currentpulse = 0;
 
void setup(void) {
  Serial.begin(9600);
}
 
void loop(void) {
  uint16_t highpulse, lowpulse; 
  highpulse = lowpulse = 0;
 
  while (IRpin_PIN & _BV(IRpin)) {
    highpulse++;
    delayMicroseconds(RESOLUTION);
  
    if ((highpulse >= MAXPULSE) && (currentpulse != 0)) {
      printpulses();
      currentpulse=0;
      return;
    }
}

pulses[currentpulse][0] = highpulse;
 
  while (! (IRpin_PIN & _BV(IRpin))) {
    lowpulse++;
    delayMicroseconds(RESOLUTION);
    if ((lowpulse >= MAXPULSE) && (currentpulse != 0)) {
      printpulses();
      currentpulse=0;
      return;
    }
  }
  
  pulses[currentpulse][1] = lowpulse;
  currentpulse++;
}
 
void printpulses(void) {

  for (uint8_t i = 0; i < currentpulse; i++) {
    Serial.print("delayMicroseconds(");
    Serial.print(pulses[i][0] * RESOLUTION, DEC);
    Serial.print(");\n");
    Serial.print("pulsoIR(");
    Serial.print(pulses[i][1] * RESOLUTION, DEC);
    Serial.print(");\n");
  }
}
