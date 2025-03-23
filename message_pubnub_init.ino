
#include <SPI.h>
#include <Ethernet.h>
#include <PubNub.h>
// Prendre l'adresse MAC indiquée sur la carte ou prendre
// une adresse MAC arbitraire (voir l'enseignant)
//Entrer ici l'adresse MAC de la carte (indiquée sur celle-ci ou imposée)
byte mac[] = {0x90, 0xA2, 0xDA, 0x11, 0x00, 0x27};

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
 Serial.println("Publication d'un Message");
 Serial.println("{\"BONJOUR\": \"Je suis l'Arduino 1 qui publie\"}");
 client = PubNub.publish(channel, "{\"BONJOUR\": \"Je suis l'Arduino 1 qui publie\"}");
 if (!client) {
 Serial.println("publishing error");
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
