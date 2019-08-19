//#include<Arduino.h>
//
//#include <TheThingsNetwork.h>
//
//#define loraSerial Serial1
//#define freqPlan TTN_FP_EU868
//
//const char *appEui = "0000000000000000";
//const char *appKey = "00000000000000000000000000000000";
//
////TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);
//
//void setup_envio() {
//  loraSerial.begin(57600);
//  ttn.showStatus();
//  ttn.join(appEui, appKey);
//}
//
//void envio(){
//  ttn.sendBytes(Datos, sizeof(Datos));
//}
