/*
  localHost.ino - This is basic local host example.
  Created by Yasin Kaya (selengalp), August 18, 2018.

*/

#include "CellularIoT.h"

CellularIoT node;

char your_ip[] = "40.68.172.187"; // change with your ip
char your_port[] = "8891"; // change with your port

// setup
void setup() {

  Serial.begin(115200);
  /*while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
    }*/
  Serial.println("start");

  node.init();
  node.changeBaudRate(9600);

  node.getIMEI();
  node.getFirmwareInfo();
  node.getHardwareInfo();

  node.setIPAddress(your_ip);
  node.setPort(your_port);

  //node.setGSMBand(GSM_sli900);
  //node.setCATM1Band(LTE_B5);
  //node.setNBIoTBand(LTE_B20);
  //node.getBandConfiguration();
  node.setMode(CATNB1_MODE);
  //node.setMode(GSM_MODE);

  node.selectOperator(20601);
  node.setPDPContextProximus();

  node.connectToOperator();
  node.getSignalQuality();
  node.getQueryNetworkInfo();

  node.deactivateContext();
  node.activateContext();
  node.closeConnection();
  node.startUDPService();

  node.sendDataATT("y8HCg0RqXXa47tI46mdlwccK","maker:4JSt6bR2Sibzm0lqFyIDRS5If0RQ22bTDqMTYra","gps","{\"latitude\":51.2565, \"longitude\":7.751654}");

  node.turnOnGNSS();
  //node.postDataHTTP();
}

// loop
void loop() {
  node.setTimeout(200);
  float lat, lon;
  node.getFixedLocation(&lat, &lon);

  char payloadValue[64];

  int lat1 = floor(lat);
  int lon1 = floor(lon);
  unsigned int lat2 = abs(round((lat - lat1) * 10000));
  unsigned int lon2 = abs(round((lon - lon1) * 10000));

  sprintf(payloadValue, "{\"latitude\":%d.%04d, \"longitude\":%d.%04d}", lat1, lat2, lon1, lon2);
  Serial.println(payloadValue);

  node.sendDataATT("y8HCg0RqXXa47tI46mdlwccK", "maker:4JSt6bR2Sibzm0lqFyIDRS5If0RQ22bTDqMTYra", "gps", payloadValue);

  delay(5000);

}
