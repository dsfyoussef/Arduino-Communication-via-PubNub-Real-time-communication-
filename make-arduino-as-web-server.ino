//Largement inspiré du programme écrit par David A. Mellis
#include <SPI.h> //Bibliothèque Standard
#include <Ethernet.h>
// L'installer si non présente
//Entrer ici l'adresse MAC de la carte (indiquée sur celle-ci ou imposée)
byte mac[] = {0xxx, 0xxx, 0xxx, 0xxx, 0xxx, 0xxx};
// Entrer ici l'adresse IP associée à l'adresse MAC
IPAddress ip(xxx, xxx, xxx, xx); // IP perso, voir l’IP associé à la boîte
//Initialisation de la bibliothèque du serveur Ethernet
// Port 80 par défaut pour Http
EthernetServer server(80);
void setup()
{
 // Open serial communications and wait for port to open:
 Serial.begin(9600);
 while (!Serial)
 {
 // wait for serial port to connect
 // Uniquement pour les cartes Leonardo
 }
 // Demarre la connexion Ethernet et le serveur
 Ethernet.begin(mac, ip);
 server.begin();
 //Sortie vers le moniteur série
 Serial.print("server is at ");
 Serial.println(Ethernet.localIP());
}
void loop()
{
 // Ecoute des données qui arrivent
 EthernetClient client = server.available();
 if (client)
 {
 Serial.println("new client");
 // an http request ends with a blank line
 boolean currentLineIsBlank = true;
 while (client.connected()) {
 if (client.available()) {
 char c = client.read();
 Serial.write(c);
 // if you've gotten to the end of the line (received a newline
 // character) and the line is blank, the http request has ended,
 // so you can send a reply
 if (c == '\n' && currentLineIsBlank) {
 // Réponse html Standard
 client.println("HTTP/1.1 200 OK");
 client.println("Content-Type: text/html");
 // the connection will be closed after completion of the response
 client.println("Connection: close");
 // refresh the page automatically every 5 sec
 client.println("Refresh: 5");
 client.println();
Page 44 sur 78
Parcours MTI : De l’objet connecté au Cloud et Nouvelles Technologies pour l’Industrie
 client.println("<!DOCTYPE HTML>");
 client.println("<html>");
 client.println("<br><br>");
 client.println("Le serveur est en ordre, la carte Arduino est reconnue sur le reseau !");
 client.println("<br><br>");
 client.println("<b>VOUS POUVEZ POURSUIVRE LE TP !<b>");
 client.println("</html>");
 break;
 }
 if (c == '\n')
 {
 // you're starting a new line
 currentLineIsBlank = true;
 }
 else if (c != '\r')
 {
 // you've gotten a character on the current line
 currentLineIsBlank = false;
 }
 }
 }
 // give the web browser time to receive the data
 delay(1);
 // close the connection:
 client.stop();
 Serial.println("client disconnected");
 }
}