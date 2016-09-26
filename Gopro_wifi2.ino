#include <GoPro.h>

const int LedPin = 13;
const int BtnPin = 12;

int btnState = 1;
int lastBtnState = 1;
int btnCounter = 0;
boolean activateFunc = false;

// the setup function runs once when you press reset or power the board
void setup() {

pinMode(LedPin, OUTPUT);
pinMode(BtnPin, INPUT_PULLUP);

Serial.begin(115200);
delay(200);
if(connectWiFi()){
  digitalWrite(LedPin, HIGH);
  Serial.println("Wifi connected");
}
}

void loop() {
  // put your main code here, to run repeatedly:
int btnState = digitalRead(BtnPin);

if (btnState != lastBtnState){
  if (btnState == LOW){
  if (btnCounter < 4){
    btnCounter++;
    Serial.println(btnCounter);
  }else{
  btnCounter = 1;
  Serial.println(btnCounter);
  }
  }
  lastBtnState = btnState;
  activateFunc = true;
  delay(50);
}


if(activateFunc){
  switch (btnCounter) {
    case 1:
      WakeOnLan();
      activateFunc = false;
      Serial.println("Wake Camera");
      break;
    case 2:
      httpStartRec();
      activateFunc = false;
      Serial.println("Start recordning");
      break;
    case 3:
      httpStopRec();
      activateFunc = false;
      Serial.println("Stop recordning");
      break;
    case 4:
      httpSleep();
      activateFunc = false;
      Serial.println("Turn of camera");
      break;
  }
}

}
