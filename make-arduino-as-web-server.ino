#include <SPI.h> 
#include <Ethernet.h>
byte mac[] = {0xxx, 0xxx, 0xxx, 0xxx, 0xxx, 0xxx};
IPAddress ip(xxx, xxx, xxx, xx);

EthernetServer server(80);
void setup()
{
 Serial.begin(9600);
 while (!Serial)
 {
 
 }
 Ethernet.begin(mac, ip);
 server.begin();
 Serial.print("server is at ");
 Serial.println(Ethernet.localIP());
}
void loop()
{
 EthernetClient client = server.available();
 if (client)
 {
 Serial.println("new client");
 boolean currentLineIsBlank = true;
 while (client.connected()) {
 if (client.available()) {
 char c = client.read();
 Serial.write(c);

 if (c == '\n' && currentLineIsBlank) {

 client.println("HTTP/1.1 200 OK");
 client.println("Content-Type: text/html");
 client.println("Connection: close");
 client.println("Refresh: 5");
 client.println();

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
 currentLineIsBlank = true;
 }
 else if (c != '\r')
 {
 currentLineIsBlank = false;
 }
 }
 }
 delay(1);
 client.stop();
 Serial.println("client disconnected");
 }
}