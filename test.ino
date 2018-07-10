

void setup() {
    Serial.begin(9600);
    cli();
    DDRB |= (1 << 5);
    
    sei();
}

void loop() {


}
