/* This code is a modification of the WiFi_LoRa_32FactoryTest example
 * mainly for learning purposes by modifying settings of the LoRa */
#include "Arduino.h"
#include "heltec.h"
#include "WiFi.h"
#include "images.h"

#define BAND    433E6  //you can set band here directly,e.g. 868E6,915E6

String rssi = "RSSI --";
String packSize = "--";
String packet;

unsigned int counter = 0;

bool receiveflag = false; // software flag for LoRa receiver, received data makes it true.

long lastSendTime = 0;        // last send time
int interval = 1000;          // interval between sends
uint64_t chipid;
int16_t RssiDetection = 0;
char incomingByte = 0; // for incoming serial data
bool sendOrReceive = false; // By default receive (1) for send (0)

void logo(){
	Heltec.display -> clear();
	Heltec.display -> drawXbm(0,5,logo_width,logo_height,(const unsigned char *)logo_bits);
	Heltec.display -> display();
}

/*
void WIFISetUp(void)
{
	// Set WiFi to station mode and disconnect from an AP if it was previously connected
	WiFi.disconnect(true);
	delay(100);
	WiFi.mode(WIFI_STA);
	WiFi.setAutoConnect(true);
	WiFi.begin("Your WiFi SSID","Your Password");//fill in "Your WiFi SSID","Your Password"
	delay(100);

	byte count = 0;
	while(WiFi.status() != WL_CONNECTED && count < 10)
	{
		count ++;
		delay(500);
		Heltec.display -> drawString(0, 0, "Connecting...");
		Heltec.display -> display();
	}

	Heltec.display -> clear();
	if(WiFi.status() == WL_CONNECTED)
	{
		Heltec.display -> drawString(0, 0, "Connecting...OK.");
		Heltec.display -> display();
//		delay(500);
	}
	else
	{
		Heltec.display -> clear();
		Heltec.display -> drawString(0, 0, "Connecting...Failed");
		Heltec.display -> display();
		//while(1);
	}
	Heltec.display -> drawString(0, 10, "WIFI Setup done");
	Heltec.display -> display();
	delay(500);
}

void WIFIScan(unsigned int value)
{
	unsigned int i;
    WiFi.mode(WIFI_STA);

	for(i=0;i<value;i++)
	{
		Heltec.display -> drawString(0, 20, "Scan start...");
		Heltec.display -> display();

		int n = WiFi.scanNetworks();
		Heltec.display -> drawString(0, 30, "Scan done");
		Heltec.display -> display();
		delay(500);
		Heltec.display -> clear();

		if (n == 0)
		{
			Heltec.display -> clear();
			Heltec.display -> drawString(0, 0, "no network found");
			Heltec.display -> display();
			//while(1);
		}
		else
		{
			Heltec.display -> drawString(0, 0, (String)n);
			Heltec.display -> drawString(14, 0, "networks found:");
			Heltec.display -> display();
			delay(500);

			for (int i = 0; i < n; ++i) {
			// Print SSID and RSSI for each network found
				Heltec.display -> drawString(0, (i+1)*9,(String)(i + 1));
				Heltec.display -> drawString(6, (i+1)*9, ":");
				Heltec.display -> drawString(12,(i+1)*9, (String)(WiFi.SSID(i)));
				Heltec.display -> drawString(90,(i+1)*9, " (");
				Heltec.display -> drawString(98,(i+1)*9, (String)(WiFi.RSSI(i)));
				Heltec.display -> drawString(114,(i+1)*9, ")");
				//            display.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
				delay(10);
			}
		}

		Heltec.display -> display();
		delay(800);
		Heltec.display -> clear();
	}
}
*/

void setup()
{
	Heltec.begin(true /*DisplayEnable Enable*/, 
	             true /*LoRa Enable*/, 
	             true /*Serial Enable*/, 
	             true /*LoRa use PABOOST*/, 
	             BAND /*LoRa RF working band*/);

	logo();
	delay(300);
	Heltec.display -> clear();

  /*
	WIFISetUp();
	WiFi.disconnect(); //���³�ʼ��WIFI
	WiFi.mode(WIFI_STA);
	delay(100);
 
	WIFIScan(1);
  */

	chipid=ESP.getEfuseMac();//The chip ID is essentially its MAC address(length: 6 bytes).
	Serial.printf("ESP32ChipID=%04X",(uint16_t)(chipid>>32));//print High 2 bytes
	Serial.printf("%08X\n",(uint32_t)chipid);//print Low 4bytes.

  // LoRa config
  LoRa.setFrequency(434250000);
  LoRa.setSpreadingFactor(8);
  LoRa.setCodingRate4(4);
  LoRa.setSignalBandwidth(41700);
  
	LoRa.onReceive(onReceive);
  send();
  LoRa.receive();
  displaySendReceive();
}


void loop()
{ 
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = (char)Serial.read();
  }

  if (incomingByte == 't')
  {
    sendOrReceive = true;
    Serial.println("Now transmiting data");
  }
  else if (incomingByte == 'r')
  {
    sendOrReceive = false;
    Serial.println("Now receiving data");
  }

  if (sendOrReceive) send();

  displaySendReceive();
  delay(1000);
  displaySendReceive();
}

void send()
{
  Serial.println("Sent LoRa packet");
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter++);
  LoRa.endPacket();
}
void displaySendReceive()
{
    Heltec.display -> drawString(0, 50, "Packet " + (String)(counter-1) + " sent done");
    Heltec.display -> drawString(0, 0, "Received Size  " + packSize + " packages:");
    Heltec.display -> drawString(0, 10, packet);
    Heltec.display -> drawString(0, 20, "With " + rssi + "db");
    Heltec.display -> display();
    delay(100);
    Heltec.display -> clear();
}
void onReceive(int packetSize)//LoRa receiver interrupt service
{
  if (!sendOrReceive)
  {
  Serial.println("Received LoRa packet");
	//if (packetSize == 0) return;

	  packet = "";
    packSize = String(packetSize,DEC);

    while (LoRa.available())
    {
		packet += (char) LoRa.read();
    }

    Serial.println(packet);
    rssi = "RSSI: " + String(LoRa.packetRssi(), DEC);
    RssiDetection= abs(LoRa.packetRssi());
    if(RssiDetection < 65)
    {
     digitalWrite(25, HIGH);  
    }
     else
    {
     digitalWrite(25, LOW);  
    }        
    receiveflag = true;    
  }
}
