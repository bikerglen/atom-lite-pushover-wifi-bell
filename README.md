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
