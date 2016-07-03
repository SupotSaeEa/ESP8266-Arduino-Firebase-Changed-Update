
/*
 *  This sketch gets data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <FirebaseChange.h>

ESP8266WiFiMulti WiFiMulti;

String firebaseProject = "https://<Project URI>/";
// SHA1 fingerprint
String thumbPrint = "xx xx xx xx xx xx xx xx xx xx xx xx xx xx xx xx xx xx xx xx";

FirebaseChange fc;

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println("Begin...");
  
	WiFiMulti.addAP("ssid","password");

	fc.begin(firebaseProject, thumbPrint);

}

int value = 0;

void loop() {
  delay(1000);
  ++value;

  if(WiFiMulti.run() == WL_CONNECTED){
  	Serial.printf("[%d] Connect to firebase database. ", value);

    String parent = "<parent>";   // name of element's parent
    String element = "<element>"; // name of element that getting value

		if(fc.available(parent)){
      Serial.print(" GET payload: " +fc.payload());
      String elementValue = fc.getString(element);
      Serial.println(" " + element + " : " + elementValue);
		} else {
			Serial.println(fc.status());
		}
  }
}
