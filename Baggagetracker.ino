#include <SoftwareSerial.h>

#include <TinyGPS.h>

Float gpslat, gpslon;

TinyGPS gps;

SoftwareSerial sgps(13, 12); //GPS interface

SoftwareSerial sgsm(2, 3);   //GSM interface

int cnt = 0;

void setup() 

{

  Serial.begin(9600);

  sgps.begin(9600);

  sgsm.begin(9600);

  delay(100);

}

void loop() 

{

  while (sgps.available()>0)

  {

    int c = sgps.read();

    if (gps.encode(c))

    {

      gps.f_get_position(&gpslat, &gpslon);

    }

  }

  Serial.println("Latitude :");

  Serial.println(gpslat, 6);

  Serial.println("Longitude:");

   Serial.println(gpslon, 6);

   sendsms();

   cnt = 0;

   delay(1000);

}//end of loop

void sendsms()

{

  cnt++;

  if(cnt == 1)

  {

      Serial.println("sending SMS to mobile no.");

      sgsm.print("\r");

      delay(1000);

      sgsm.print("AT+CMGF=1\r");

      delay(1000);

      sgsm.print("AT+CMGS=\"+918074911338\"\r");

      delay(1000);

      sgsm.print("laguage tracking location details");

      sgsm.print("Latitude :");

      sgsm.println(gpslat, 6);

      sgsm.print("Longitude:");

      sgsm.println(gpslon, 6);

      delay(1000);

      sgsm.write(0x1A);

  }

}
