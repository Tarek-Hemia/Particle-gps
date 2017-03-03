// This #include statement was automatically added by the Particle IDE.

//particle electron with GPS 
#include <TinyGPS++.h>




static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;

String identifier = "38E01B-Z67BA7PZ";
char publishString[255];


void setup() {
    Serial1.begin(GPSBaud);
    Serial.begin(115200);
    Particle.function("Ide", changeName);
}


void loop() {


    String lat =  String(gps.location.lat());
    String lng = String(gps.location.lng());
    String hour = String(gps.time.hour());
    String minute = String(gps.time.minute());
    String second = String(gps.time.second());
    String alt = String(gps.altitude.meters());
    String vit = String(gps.speed.knots());

    sprintf(publishString, "{\"Identifiant\" : \"%s\", \"Alt\" : \"%s\", \"Vit\" : \"%s\", \"Lat\" : \"%s\", \"Lon\" : \"%s\", \"Heures\" : \"%s\", \"Minutes\" : \"%s\", \"Secondes\" : \"%s\"}",identifier.c_str(),alt.c_str(), vit.c_str(), lat.c_str(), lng.c_str(), hour.c_str(), minute.c_str(), second.c_str());
    Serial.println(publishString);

    bool success;
    success = Particle.publish("data1", publishString);
    if (!success){
        Serial.print("erreur");
    }

    smartDelay(1000);

    if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));

}


int changeName(String NewName){
    identifier = NewName;
    return 0;
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (Serial1.available())
      gps.encode(Serial1.read());
  } while (millis() - start < ms);
}


			 //device ID 360033001951343334363036 avec GPS
			 //device ID 510034001451343334363036 Sans GPS
