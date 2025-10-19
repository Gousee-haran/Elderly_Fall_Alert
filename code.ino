int pirPin = 2;     
int tiltPin = 3;     
int buzzerPin = 8;   

unsigned long lastActivityTime = 0;
unsigned long inactivityLimit = 30000;  

void setup() {
  pinMode(pirPin, INPUT);           
  pinMode(tiltPin, INPUT_PULLUP);    
  pinMode(buzzerPin, OUTPUT);        

  Serial.begin(9600);
  Serial.println("Elderly Fall & Activity Alert System Ready...");
}

void loop() {
  int motion = digitalRead(pirPin);  
  int tilt = digitalRead(tiltPin);  
  if (motion == HIGH) {
    Serial.println("Activity detected!");
    lastActivityTime = millis(); 
  }
  if (tilt == LOW) {
    Serial.println("⚠️ Fall detected!");
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH);
    delay(2000);  
  } else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
  }
  if (millis() - lastActivityTime > inactivityLimit) {
    Serial.println("⚠️ No movement for long time!");
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(2000);
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
    lastActivityTime = millis();
  }
  delay(200);
}
