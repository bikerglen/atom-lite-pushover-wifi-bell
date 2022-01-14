//---------------------------------------------------------------------------------------------
// M5Stack Atom Lite / pushover.net Wi-Fi Door Bell
//
// Add your Wi-Fi SSID, Wi-Fi password, pushover API token, and pushover user ID to the 
// char / string variables below then compile and download to an M5Stack Atom Lite.
//
// Each time the button on top of the Atom Lite is pressed, a push notification should be 
// received on the user's device(s) running the pushover.net app.
//
// Warning: remote host certificate validation is turned off for the purposes of this
// quick demonstration. To prevent Eve from Eavesdropping, the pushover certificate needs
// to be downloaded and compiled into the code. See the WiFiClientSecure github repo
// for instructions and examples.
//
// The webclient.connect call will only work once with the 2.0.2 version of the ESP32
// WiFiClientSecure library. Replacing it with 2.0.1 will work. Waiting for a new
// version of the WiFiClientSecure library for the issue to be fixed.
//---------------------------------------------------------------------------------------------

#include <SPI.h>
#include <WiFi.h>
#include <WiFiClientSecure.h> 

const char*  ssid     = "YOUR_WIFI_SSID";      // Wi-Fi Network SSID
const char*  password = "YOUR_WIFI_PASSWORD";  // Wi-Fi Network Password

const char*  server = "api.pushover.net";
const String doorBellMessage = "{\"token\":\"YOUR_PUSHOVER_API_TOKEN\",\"user\":\"YOUR_PUSHOVER_USERID_TOKEN\",\"message\":\"ding dong!\"}";

WiFiClientSecure webclient;

void SendDoorBellMessage (void);

void setup (void)
{
  // open serial port
  Serial.begin (115200);

  // initialize gpio
  pinMode (39, INPUT);
  pinMode (22, OUTPUT);
  pinMode (19, OUTPUT);
  pinMode (23, OUTPUT);
  pinMode (33, OUTPUT);
  digitalWrite (22, LOW);
  digitalWrite (19, LOW);
  digitalWrite (23, LOW);
  digitalWrite (33, LOW);

  // wait a bit
  delay (250);

  // display hello world
  Serial.println ("Hello, world!");

  // connect to Wi-Fi
  WiFi.begin (ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // display mac and ip
  Serial.println("");
  Serial.println("Wi-Fi connected!");
  Serial.println("");
  Serial.print("MAC address: ");
  Serial.println (WiFi.macAddress());
  Serial.print("IP address:  ");
  Serial.println(WiFi.localIP()); 
}


bool lastButton = false;
bool thisButton = false;

void loop (void)
{
	thisButton = digitalRead (39) ? false : true;
	
	if (thisButton && !lastButton) {
		SendDoorBellMessage ();
	}

	lastButton = thisButton;

	delay (20);
}


void SendDoorBellMessage (void)
{
  Serial.println("\nStarting connection to server...");
  webclient.setInsecure();//skip verification
  if (!webclient.connect(server, 443)) {
    Serial.println("Connection failed!");
  } else {
    Serial.println("Connected to server!");
    // Make a HTTP request:
    webclient.println("POST /1/messages.json HTTP/1.1");
    webclient.println("Host: api.pushover.net");
    webclient.println("Accept: */*");
    webclient.println("Content-Type: application/json");
    webclient.print  ("Content-Length: ");
    webclient.println (doorBellMessage.length());
    webclient.println("Connection: close");
    webclient.println ();
    webclient.println (doorBellMessage);

    while (webclient.connected()) {
      String line = webclient.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("headers received");
        break;
      }
    }
    // if there are incoming bytes available
    // from the server, read them and print them:
    while (webclient.available()) {
      char c = webclient.read();
      Serial.write(c);
    }

    webclient.stop();
  }
}
