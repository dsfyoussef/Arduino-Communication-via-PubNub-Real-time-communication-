#include <SPI.h>
#include <Ethernet.h>
#include <PubNub.h>
#include <ArduinoJson.h>
// Prendre l'adresse MAC indiquée sur la carte ou prendre
// une adresse MAC arbitraire (voir le sujet de TP)
byte mac[] = { 0x90, 0xA2, 0xDA, 0x11, 0x00, 0x26 };
// Mettre vos clés, ne pas utiliser celles-ci
// Mettre vos clés, ne pas utiliser celles-ci
char pubkey[] = "pub-c-22a8c323-51b8-4372-ab41-a9cc87d6f140"; 
char subkey[] = "sub-c-4b1e35c2-bc6b-4225-a6ff-35c3bd07a80c"; 
char channel[] = "CanalMTI6";
JsonDocument doc;
String Message;
void setup()
{
//Initialisation du moniteur série
Serial.begin(9600);
while (!Serial);
//Initialisation d'Internet
while (!Ethernet.begin(mac))
{
Serial.println("Ethernet setup error");
delay(1000);
}
Serial.println("Parametrage d'Ethernet");
//Initialisation de Pubnub
PubNub.begin(pubkey, subkey);
Serial.println("Parametrage de PubNub");
}
void loop()
{
EthernetClient *client;
Serial.println("Serialisation");
JsonObject BME680 = doc["BME680"].to<JsonObject>();
// Affectation avec des valeurs arbitraires car pas assez de place mémoire
// pour utiliser la bibliothèque du BME680
BME680["Temperature"] = 23.85;
BME680["Pression"] = 1013.65;
BME680["Humidite"] = 33.8;
BME680["Pollution"] = 14.189;
// Génére le Json dans un string
serializeJson(doc, Message);
// Génère le Json sur le port Série avec mise en forme
serializeJsonPretty(doc, Serial);
Serial.println();
//Publication du message sur PUBNUB avec transformation du String en const char *
client = PubNub.publish(channel, Message.c_str());
if (!client) {
//Serial.println("publishing error");
delay(1000);
return;
}
// Récupération de la chaine de retour de la plateforme PubNub
while (client->connected()) {
while (client->connected() && !client->available()) ; // wait
char c = client->read();
Serial.print(c);
}
client->stop();
Serial.println();
delay(10000);
}