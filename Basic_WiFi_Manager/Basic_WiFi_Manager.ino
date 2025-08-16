/*
* This Will Auto Save Wifi SSID and PASSWORD (no need to do anything)
*/
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
WiFiManager wm; // global wm instance

void setup() {
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP  
  Serial.begin(115200);

  Serial.println("\n Starting");

   //set title
  wm.setTitle("Clock Wifi Setup");
  wm.setSaveParamsCallback(saveParamCallback);

  // invert theme, dark
  wm.setDarkMode(true);

  // menu tokens, "wifi","wifinoscan","info","param","close","sep","erase","restart","exit" (sep is seperator) (if param is in menu, params will not show up in wifi page!)
  // const char* menu[] = {"wifi","info","param","sep","restart","exit"}; 
  // wm.setMenu(menu,6);
  std::vector<const char *> menu = {"wifi","sep","exit"}; //sep is line
  wm.setMenu(menu);


  wm.setConnectTimeout(20); // how long to try to connect for before continuing

  bool res;
  // res = wm.autoConnect(); // auto generated AP name from chipid
//   res = wm.autoConnect("Clock_Wifi"); // anonymous ap
    res = wm.startConfigPortal("OnDemandAP");
//  res = wm.autoConnect("AutoConnectAP","password"); // password protected ap

  if(!res) {
    Serial.println("Failed to connect or hit timeout");
    // ESP.restart();
  } 
  else {
    //if you get here you have connected to the WiFi    
    Serial.println("connected...yeey :)");
  }
}

void loop() {
  
}

void saveParamCallback(){
  Serial.println("[CALLBACK] saveParamCallback fired");
  wm.stopConfigPortal();
}
