#include <Arduino.h>
//#include <config.h>
//#include <./configs/config.prod.8266_1.h>
//https://nodemcu.readthedocs.io/en/release/modules/mqtt/

void _blinkOnce(int blinkTime) {
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on
  delay(blinkTime);
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
}

void blinkLong(){
  _blinkOnce(1000);
}

void blinkShort(){
  _blinkOnce(400);
}
//TODO: придумать с выводом ошибки во внешний светодиод
void blinkErrorCode(int tens, int units){

  int delayBeetweenBlink = 200;
  //Отмигиваем десятки, длинные
  for (int i = 1; i <= tens; i++)
  {
    blinkLong();
    delay(delayBeetweenBlink);
  }
  //отмигиваем единички
  for (int s = 1; s <= units; s++ ){
    blinkShort();
    delay(delayBeetweenBlink);
  }
  delay(1000);
}

//2 длинных мигания
void blinkNetworkError(){
  Serial.println("[error 20] NetworkError");
  blinkErrorCode(2, 0);
}

void blinkMqttSendMessageError(){
  Serial.println("[error 30] mqtt send message error");
  blinkErrorCode(3, 0);
}


// 2 длинных и 1 одно короткое мигание
void blinkMqttError(){
  Serial.println("[error 21] mqtt error");
  blinkErrorCode(2, 1);
}

// 5 длинных миганий
void blinkInternalError(String message){
    Serial.println("[error 50] internal error");
    Serial.println(message);
    blinkErrorCode(5, 0);
}

void blinkBmeError(){
  Serial.println("[error 51] bme280 error");
  blinkErrorCode(5, 1);
}

//Одно мигание
void blinkAllIsOk(){
  blinkErrorCode(0, 1);
}

/*
@blinkTime - время свечения светодиода
@count - количество миганий
@delayTime-задержка между миганиями*/
void blink(int count, int blinkTime = 200, int delayTime = 200) {
  for (int i = 1; i <= count; i++) {
    _blinkOnce(blinkTime);
    if (i != count) { //чтобы после последнего мигания не было задержки
      delay(delayTime);
    }
  }
}

