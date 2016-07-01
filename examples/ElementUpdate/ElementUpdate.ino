
/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
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

int loopCount = 0;

void loop() {
  delay(1000);
  ++loopCount;

  if(WiFiMulti.run() == WL_CONNECTED){
  	Serial.printf("[%d] Connect to firebase database. ", loopCount);

    String parent = "<parent>";   // name of element's parent 
    String element = "<element>"; // name of element
    String value = "<value>";     // value of element

    if(fc.update(parent, element, value)){

      Serial.println(" GET payload: " +fc.payload());
      String updateValue = fc.getString(element);
      Serial.println(element + " : " + updateValue);

    } else {
      Serial.println(fc.status());
    }
  }
}
