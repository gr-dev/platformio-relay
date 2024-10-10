//Под капотом .cpp файло использует LED_BUILTIN. Возможно, нужно передавать эту переменную извне

//2 длинных мигания
void blinkNetworkError();

// 2 длинных и 1 одно короткое мигание
void blinkMqttError();

// 3 длинных
void blinkMqttSendMessageError();

// 5 длинных миганий
void blinkInternalError(char *message);

//Одно короткое мигание
void blinkAllIsOk();

//Отмигать пользовательский код - первый параметр десятки, второй - единицы
void blinkErrorCode(int tens, int units);

//ошибка bme280
void blinkBmeError();
