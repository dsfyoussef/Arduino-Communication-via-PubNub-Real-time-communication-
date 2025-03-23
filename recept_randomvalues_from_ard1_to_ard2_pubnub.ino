#include <ArduinoJson.h>
#include <SPI.h>
#include <Ethernet.h>
#include <PubNub.h>
// Prendre l'adresse MAC indiquée sur la carte ou prendre
// une adresse MAC arbitraire (voir l'enseignant)
//Entrer ici l'adresse MAC de la carte (indiquée sur celle-ci ou imposée)
byte mac[] = {0x90, 0xA2, 0xDA, 0x11, 0x00, 0x35};

// Mettre vos clés, ne pas utiliser celles-ci
char pubkey[] = "pub-c-22a8c323-51b8-4372-ab41-a9cc87d6f140";
char subkey[] = "sub-c-4b1e35c2-bc6b-4225-a6ff-35c3bd07a80c";
char channel[] = "CanalMTI6";
void setup()
{
 //Initialisation du moniteur série
 Serial.begin(9600);
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
//Ethernet.maintain();//Demande au serveur DHCP de maintenir l'adresse IP
EthernetClient *client;
Serial.println("ARDUINO 2 attend la réception d'un message");
PubSubClient *pclient = PubNub.subscribe(channel);
if (!pclient)
{
Serial.println("subscription error");
delay(1000);
return;
}
String Message = "";
StaticJsonDocument<256> doc;

while (pclient->wait_for_data())
{

char c = pclient->read();
// message = message.toString();
Message.concat(c);
}

pclient->stop();
deserializeJson(doc, Message);

serializeJsonPretty(doc, Serial);
//Serial.print(Message);
Serial.println(Message);
delay(500);
}

