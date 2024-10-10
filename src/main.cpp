#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <blinkHelper.h>
#include <./configs/8266_2.h>

const char *ssid = Conf_WiFiSsid;
const char *password = Conf_WiFiPassword;
const uint8_t relay = RELAY;

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi()
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    blinkNetworkError();
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String message;
  message.reserve(sizeof(payload));
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
    message += (char)payload[i];
  }
  if (message == "on")
  {
    digitalWrite(relay, LOW);
  }
  else if (message == "off")
  {
    digitalWrite(relay, HIGH);
  }
    Serial.println("");
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(Conf_DeviceId, Conf_DeviceId, Conf_DeviceId))
    {
      Serial.println("connected");
      client.subscribe(Conf_Mqtt_Prefix Conf_DeviceId "/main");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      blinkMqttError();
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(relay, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(relay, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  setup_wifi();
  client.setServer(Conf_MqttServer, Conf_MqttPort);
  client.setCallback(callback);
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
}