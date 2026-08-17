#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// =====================================================
// WIFI
// =====================================================

const char* ssid = "WIFI";
const char* password = "PASSWIFI";


// =====================================================
// MQTT
// =====================================================

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;


// =====================================================
// MQTT TOPICS
// =====================================================

const char* topicSensor  = "esp/sensor";
const char* topicControl = "esp/control";
const char* topicStatus  = "esp/status";


// =====================================================
// PIN
// =====================================================

// DHT11
#define DHTPIN 4
#define DHTTYPE DHT11

// Rain Sensor AO
const int rainPin = 34;

// LED quạt
const int fanPin = 18;

// LED máy sưởi
const int heaterPin = 19;


// =====================================================
// RAIN THRESHOLD
// =====================================================

// Giá trị này cần chỉnh theo cảm biến thực tế
// Giá trị càng thấp thường càng ướt
const int rainThreshold = 2000;


// =====================================================
// OBJECT
// =====================================================

DHT dht(DHTPIN, DHTTYPE);

WiFiClient espClient;

PubSubClient mqttClient(espClient);


// =====================================================
// TRẠNG THÁI THIẾT BỊ
// =====================================================

bool fanState = false;
bool heaterState = false;


// =====================================================
// WIFI
// =====================================================

void setupWiFi()
{
  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


// =====================================================
// GỬI TRẠNG THÁI THIẾT BỊ
// =====================================================

void publishStatus(const char* device, bool state)
{
  char statusData[100];

  snprintf(
    statusData,
    sizeof(statusData),
    "{\"device\":\"%s\",\"state\":%s}",
    device,
    state ? "true" : "false"
  );

  mqttClient.publish(
    topicStatus,
    statusData
  );

  Serial.print("Status sent: ");
  Serial.println(statusData);
}


// =====================================================
// MQTT CALLBACK
// =====================================================

void mqttCallback(
  char* topic,
  byte* payload,
  unsigned int length
)
{
  String message = "";

  for (unsigned int i = 0; i < length; i++)
  {
    message += (char)payload[i];
  }

  Serial.println();
  Serial.println("========== MQTT MESSAGE ==========");

  Serial.print("Topic: ");
  Serial.println(topic);

  Serial.print("Message: ");
  Serial.println(message);


  // ===================================================
  // CHỈ XỬ LÝ ESP/CONTROL
  // ===================================================

  if (String(topic) == topicControl)
  {

    // -----------------------------------------------
    // XÁC ĐỊNH THIẾT BỊ
    // -----------------------------------------------

    bool isLight = message.indexOf("\"device\":\"light\"") >= 0;

    bool isFan = message.indexOf("\"device\":\"fan\"") >= 0;


    // -----------------------------------------------
    // XÁC ĐỊNH TRẠNG THÁI
    // -----------------------------------------------

    bool stateOn = message.indexOf("\"state\":true") >= 0;


    // ===============================================
    // MÁY SƯỞI
    // device = light
    // ===============================================

    if (isLight)
    {
      if (stateOn)
      {
        heaterState = true;

        digitalWrite(
          heaterPin,
          HIGH
        );

        Serial.println("HEATER: ON");
      }
      else
      {
        heaterState = false;

        digitalWrite(
          heaterPin,
          LOW
        );

        Serial.println("HEATER: OFF");
      }

      publishStatus(
        "light",
        heaterState
      );
    }


    // ===============================================
    // QUẠT
    // device = fan
    // ===============================================

    if (isFan)
    {
      if (stateOn)
      {
        fanState = true;

        digitalWrite(
          fanPin,
          HIGH
        );

        Serial.println("FAN: ON");
      }
      else
      {
        fanState = false;

        digitalWrite(
          fanPin,
          LOW
        );

        Serial.println("FAN: OFF");
      }

      publishStatus(
        "fan",
        fanState
      );
    }
  }

  Serial.println("==================================");
}


// =====================================================
// MQTT RECONNECT
// =====================================================

void reconnectMQTT()
{
  while (!mqttClient.connected())
  {
    Serial.print("Connecting to MQTT...");

    String clientID = "ESP32-PetCage-";

    clientID += String(
      (uint32_t)ESP.getEfuseMac(),
      HEX
    );


    if (mqttClient.connect(clientID.c_str()))
    {
      Serial.println(" connected!");


      // Subscribe esp/control
      mqttClient.subscribe(
        topicControl
      );


      // Khi kết nối lại:
      // tắt thiết bị để đảm bảo an toàn

      fanState = false;
      heaterState = false;

      digitalWrite(
        fanPin,
        LOW
      );

      digitalWrite(
        heaterPin,
        LOW
      );


      // Gửi trạng thái hiện tại
      publishStatus(
        "fan",
        false
      );

      publishStatus(
        "light",
        false
      );
    }

    else
    {
      Serial.print(" failed, rc=");
      Serial.print(mqttClient.state());

      Serial.println(
        " -> retry in 5 seconds"
      );

      delay(5000);
    }
  }
}


// =====================================================
// SETUP
// =====================================================

void setup()
{
  Serial.begin(115200);


  // ===================================================
  // GPIO
  // ===================================================

  pinMode(
    fanPin,
    OUTPUT
  );

  pinMode(
    heaterPin,
    OUTPUT
  );

  pinMode(
    rainPin,
    INPUT
  );


  // Tắt thiết bị khi khởi động

  digitalWrite(
    fanPin,
    LOW
  );

  digitalWrite(
    heaterPin,
    LOW
  );


  // ===================================================
  // ADC
  // ===================================================

  analogReadResolution(12);


  // ===================================================
  // DHT11
  // ===================================================

  dht.begin();


  // ===================================================
  // WIFI
  // ===================================================

  setupWiFi();


  // ===================================================
  // MQTT
  // ===================================================

  mqttClient.setServer(
    mqtt_server,
    mqtt_port
  );

  mqttClient.setCallback(
    mqttCallback
  );


  Serial.println();
  Serial.println("==============================");
  Serial.println("ESP32 PET CAGE SYSTEM");
  Serial.println("==============================");
}


// =====================================================
// LOOP
// =====================================================

void loop()
{
  // ===================================================
  // MQTT
  // ===================================================

  if (!mqttClient.connected())
  {
    reconnectMQTT();
  }

  mqttClient.loop();


  // ===================================================
  // DHT11
  // ===================================================

  float temperature =
    dht.readTemperature();

  float humidity =
    dht.readHumidity();


  // ===================================================
  // RAIN SENSOR
  // ===================================================

  int rainValue =
    analogRead(rainPin);


  // Giá trị rain gửi Node-RED
  int rainStatus;

  if (rainValue < rainThreshold)
  {
    rainStatus = 1;
  }
  else
  {
    rainStatus = 0;
  }


  // ===================================================
  // SERIAL MONITOR
  // ===================================================

  Serial.println();

  if (isnan(temperature) ||
      isnan(humidity))
  {
    Serial.println(
      "ERROR: Cannot read DHT11!"
    );
  }
  else
  {
    Serial.print(
      "Temperature: "
    );

    Serial.print(
      temperature
    );

    Serial.println(" C");


    Serial.print(
      "Humidity: "
    );

    Serial.print(
      humidity
    );

    Serial.println(" %");
  }


  Serial.print(
    "Rain sensor raw: "
  );

  Serial.println(
    rainValue
  );


  Serial.print(
    "Rain status: "
  );

  if (rainStatus == 1)
  {
    Serial.println(
      "CO MUA"
    );
  }
  else
  {
    Serial.println(
      "KHONG MUA"
    );
  }


  // ===================================================
  // GỬI DỮ LIỆU MQTT
  // ===================================================

  if (!isnan(temperature) &&
      !isnan(humidity))
  {
    char sensorData[150];

    snprintf(
      sensorData,
      sizeof(sensorData),
      "{\"temperature\":%.2f,\"humidity\":%.2f,\"rain\":%d}",
      temperature,
      humidity,
      rainStatus
    );


    mqttClient.publish(
      topicSensor,
      sensorData
    );


    Serial.print(
      "MQTT sensor: "
    );

    Serial.println(
      sensorData
    );
  }


  Serial.println(
    "------------------------------"
  );


  // DHT11 nên đọc khoảng 2-3 giây/lần
  delay(3000);
}