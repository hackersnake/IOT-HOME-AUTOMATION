#include <Servo.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>

#define DHTPIN 2 
#define DHTTYPE DHT22   

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "HappyHomeWireless";
const char* password = "Test@1234";
const char* mqtt_server = "192.168.1.100";

WiFiClient espClient;
PubSubClient client(espClient);
SoftwareSerial bluetoothSerial(10, 11); // RX, TX - replace with your actual pins

char Incoming_value = 0;
Servo myservo;

void setup() {
  Serial.begin(9600);
  bluetoothSerial.begin(9600);

  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);

  myservo.attach(3);

  dht.begin();

  setupWiFi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  if (Serial.available() > 0) {
    Incoming_value = Serial.read();
    Serial.print(Incoming_value);
    handleSerialCommand(Incoming_value);
  }

  if (bluetoothSerial.available() > 0) {
    Incoming_value = bluetoothSerial.read();
    Serial.print("Bluetooth command: ");
    Serial.println(Incoming_value);
    handleSerialCommand(Incoming_value);
  }

  if (!client.connected()) {
    reconnect();
  }

  client.loop();
}

void handleSerialCommand(char command) {
  switch (command) {
    case 'a':
      digitalWrite(13, HIGH);
      client.publish("home/automation", "Device A ON");
      break;

    case 'b':
      digitalWrite(12, HIGH);
      client.publish("home/automation", "Device B ON");
      break;

    case 'c':
      digitalWrite(11, HIGH);
      client.publish("home/automation", "Device C ON");
      break;

    case 'd':
      digitalWrite(10, HIGH);
      client.publish("home/automation", "Device D ON");
      break;

    case 'e':
      digitalWrite(9, HIGH);
      client.publish("home/automation", "Device E ON");
      break;

    case 'f':
      digitalWrite(8, HIGH);
      client.publish("home/automation", "Device F ON");
      break;

    case 'g':
      digitalWrite(7, HIGH);
      client.publish("home/automation", "Device G ON");
      break;

    case 'h':
      digitalWrite(6, HIGH);
      client.publish("home/automation", "Device H ON");
      break;

    case 'i':
      digitalWrite(5, HIGH);
      client.publish("home/automation", "Device I ON");
      break;

    case 'j':
      digitalWrite(4, HIGH);
      client.publish("home/automation", "Device J ON");
      break;

    case 'k':
      digitalWrite(2, HIGH);
      client.publish("home/automation", "Device K ON");
      break;

    case 'l':
      digitalWrite(2, LOW);
      client.publish("home/automation", "Device K OFF");
      break;

    case 'm':
      digitalWrite(4, LOW);
      client.publish("home/automation", "Device J OFF");
      break;

    case 'n':
      digitalWrite(5, LOW);
      client.publish("home/automation", "Device I OFF");
      break;

    case 'o':
      digitalWrite(6, LOW);
      client.publish("home/automation", "Device H OFF");
      break;

    case 'p':
      digitalWrite(7, LOW);
      client.publish("home/automation", "Device G OFF");
      break;

    case 'q':
      digitalWrite(8, LOW);
      client.publish("home/automation", "Device F OFF");
      break;

    case 'r':
      digitalWrite(9, LOW);
      client.publish("home/automation", "Device E OFF");
      break;

    case 's':
      digitalWrite(10, LOW);
      client.publish("home/automation", "Device D OFF");
      break;

    case 't':
      digitalWrite(11, LOW);
      client.publish("home/automation", "Device C OFF");
      break;

    case 'u':
      digitalWrite(12, LOW);
      client.publish("home/automation", "Device B OFF");
      break;

    case 'v':
      digitalWrite(13, LOW);
      client.publish("home/automation", "Device A OFF");
      break;
  }
}

void setupWiFi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Failed to connect to WiFi. Please check your credentials.");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
