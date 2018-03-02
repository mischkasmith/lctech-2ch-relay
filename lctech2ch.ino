/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server communicates with the relay board via the Serial port
 *    http://server_ip/1/on will turn the relay 1 on
 *    http://server_ip/1/off will turn the relay 1 off
 *    http://server_ip/2/on will turn the relay 2 on
 *    http://server_ip/2/off will turn the relay 2 off
 *    There are no Serial.print lines of code
 */

#include <ESP8266WiFi.h>

  const char* ssid = "..........";
  const char* password = "...........";
  WiFiServer server (80);

  //Hex command to send to serial for close relay
  byte relON[]  = {0xA0, 0x01, 0x01, 0xA2};

  //Hex command to send to serial for open relay
  byte relOFF[] = {0xA0, 0x01, 0x00, 0xA1};

  //Hex command to send to serial for close relay
  byte rel2ON[]  = {0xA0, 0x02, 0x01, 0xA3};

  //Hex command to send to serial for open relay
  byte rel2OFF[] = {0xA0, 0x02, 0x00, 0xA2};
void setup () 
{
  delay (10);
  Serial.begin (115200);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  // Start the server
  server.begin();
  delay(50);
}

void loop() {
  int val;


  // Check if a client has connected
  WiFiClient client = server.available();
  if ( ! client ) {
    return;
  }
  
  // Wait until the client sends some data
  while ( ! client.available () )
  {
    delay (100);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil ('\r');
  client.flush ();
  
  // Match the request
  if (req.indexOf ("/1/on") != -1)
  {
    Serial.write (relON, sizeof(relON)); 
    val = 1; // if you want feedback see below
  } else if (req.indexOf ("/1/off") != -1) {
      Serial.write (relOFF, sizeof(relOFF)); 
      val = 0; // if you want feedback
  } else if (req.indexOf ("/2/on") != -1) {
      Serial.write (rel2ON, sizeof(rel2ON)); 
      val = 1; // if you want feedback see below
  } else { 
    if (req.indexOf ("/2/off") != -1)
      Serial.write (rel2OFF, sizeof(rel2OFF)); 
      val = 0; // if you want feedback
  }

  client.flush ();
  
  // only if you want feedback - see above
  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nRelay is now ";
  s += (val)?"on":"off";
  s += "</html>\n";
  
  // Send the response to the client
  client.print (s);
  delay (10);
}

