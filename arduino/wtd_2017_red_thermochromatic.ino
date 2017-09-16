/* 
 ESP8266 MQTT example for controlling thermochromatic material.
 (c) 2017 Team R.E.D. @ Cybus WTD Hackathon

 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library and some simple control logic to ensure appropriate
 behaviour of thermochromatic material.

 To handle the hackathon use case with thermochromatic textiles appropriately
 we need to trigger the "on" signal once (heat-up) and reset (cool-donw) 
 immediately for some seconds to avoid unwanted physical effects and
 to be able to cool down the thermochromatic material as fast as possible.

 This needs to be created non-blocking, so we use simple duration checks
 and accept another "on"-state only after the time required to cool down.

 It connects to an MQTT server then:
  - publishes the "connnection state" to a topic every every two seconds
  - subscribes to a device-specific alert topic accepting 1 or 0 for an active or disabled alert state.
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Parameters for Wifi and MQTT Broker
const char* ssid = "..."; // WLAN-SSID
const char* password = "..."; // WLAN Passwort
const char* mqtt_server = "..."; // IP des MQTT-Servers
const char* mqtt_username = "...";
const char* mqtt_password = "...";
const String topicPrefix = "io/cybus/energie-campus/red/";

// Parameters for device control
const String deviceId = "0324"; //String(random(0xffff), HEX);
const long delaySignalCheck = 3000;
const long delayOnState = 2000;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

bool acceptNewSignals = false;
long lastSignalCheck = 0;
long lastOnSignalCheck = 0;
char lastSignal = '0';

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Trigger state switch in main loop if a 1 was received as first character
  lastSignal = (char)payload[0];
  if (lastSignal != '0') {
    lastSignal = '1'; // normalize to '1', if values != '0' are set
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), "wtd17.red.thermo", "thermored")) {
      Serial.println("connected");
      // Once connected, publish an state sginal...
      String connectStatusTopic = topicPrefix;
      connectStatusTopic.concat(deviceId);
      connectStatusTopic.concat("/connected");
      client.publish(connectStatusTopic.c_str(), "smart device connected.");
      
      // subscribe to an alert topic to control the smart device
      String alertTopic = topicPrefix;
      alertTopic.concat(deviceId);
      alertTopic.concat("/alert");
      client.subscribe(alertTopic.c_str());
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(D2, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();

  if (now - lastOnSignalCheck > delaySignalCheck) {
    acceptNewSignals = true;
  }
  
  if (now - lastSignalCheck > delayOnState) {
    lastSignalCheck = now;
    if (acceptNewSignals == false || lastSignal == '0') {
      digitalWrite(D2, LOW);
    } else if (acceptNewSignals == true && lastSignal == '1') {
      // signal 1, start delay
      lastOnSignalCheck = now;
      acceptNewSignals = false;
      digitalWrite(D2, HIGH); // reset this after 1 second at the latest
    }
  }
  
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "smart device connected #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
  }
}
