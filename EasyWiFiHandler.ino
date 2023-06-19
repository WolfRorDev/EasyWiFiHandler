/*
This script was created to support a Wi-Fi module (e.g. ESP8266) in conjunction with other devices such as STM32 or Arduino. 
It allows you to quickly and easily connect to a Wi-Fi network and send a GET request, the value of which will be returned to the microcontroller (e.g. STM32, Arduino)

Author: Domninik Krzywański
Website: wolfror.com
-------------------------

Ten skrypt został stworzony w celu obsługi modułu Wi-Fi (np. ESP8266) w połączeniu z innymi urządzeniami, takimi jak STM32 czy Arduino.
Umożliwia szybkie i łatwe nawiązywanie połączeń z siecią Wi-Fi oraz wysłanie zapytania GET, którego wartość zostanie zwrócona do mikrokontrolowe (np. STM32, Arduino)

Autor: Dominik Krzywański
Strona internetowa: wolfror.com
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


String getValue(String data, char separator, int index);
void setConf(String data);
boolean connect();
void getSettings();

String ssid = ""; 
String pass = "";
String hostname = "ESP";
boolean autoReconnect = false;
int numberTries = 10;

void setup() {
  Serial.begin(115200);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  if(WiFi.status() == WL_CONNECTED)
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }

  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    data.trim();
    if(WiFi.status() == WL_CONNECTED)
    {
      if (data.startsWith("http://") || data.startsWith("https://")) 
      {
        HTTPClient http;
        WiFiClient clientt;

        http.begin(clientt,data);

        int httpCode = http.GET();
        if (httpCode > 0) 
        {
          String response = http.getString();
          Serial.println(response);
        }
        else
        {
          Serial.println("WE4: HTTP request error");
        }
        http.end();
      }
      else if(strcmp(data.c_str(), "ip") == 0)
      {
        Serial.println("WS4: IP: " + WiFi.localIP().toString());
      }
      else if(strcmp(data.c_str(), "close") == 0)
      {
        WiFi.disconnect();
        Serial.println("WS3: Wi-Fi Disconnected");
      }
      else if(data.startsWith("get"))
      {
        getSettings();
      }
      else if(strcmp(data.c_str(), "ssid") == 0)
      {
        Serial.println("WS4: SSID: " + ssid);
      }
      else if(data.startsWith("state"))
      {
        Serial.print("WS1: ");
        Serial.println(WiFi.status() == WL_CONNECTED ? "True" : "False");
      }
      else
      {
        Serial.println("WE3: Invalid command");
      }
    }
    else if(data.startsWith("set"))
    {
      setConf(data);
    }
    else if(data.startsWith("get"))
    {
      getSettings();
    }
    else if(data.startsWith("state"))
    {
      Serial.print("WS1: ");
      Serial.println(WiFi.status() == WL_CONNECTED ? "True" : "False");
    }
    else if(data.startsWith("conn"))
    {
      connect();
    }
    else
    {
      Serial.println("WE2: No connection to Wi-Fi");
    }
  }
}

void setConf(String data)
{
  if(WiFi.status() == WL_CONNECTED)
  {
    Serial.println("WE5: Cannot change parameters. Wi-Fi connection is active");
    return;  
  }
  String tempSsid = getParameter(data, "-ssid");
  String tempNt = getParameter(data, "-nt");
  String tempPass = getParameter(data, "-pass");
  String tempHostname = getParameter(data, "-hostname");
  String tempAr = getParameter(data, "-ar");
  
  if(strcmp(tempSsid.c_str(), "") != 0)
  {
    ssid = tempSsid;
  }

  if(strcmp(tempNt.c_str(), "") != 0)
  {
    numberTries = tempNt.toInt();
  }

  if(strcmp(tempPass.c_str(), "") != 0)
  {
    pass = tempPass;
  }

  if(strcmp(tempHostname.c_str(), "") != 0)
  {
    hostname = tempHostname;
  }

  if(strcmp(tempAr.c_str(), "") != 0)
  {
    autoReconnect = tempAr.toInt() == 1 ? true : false;
  }
  Serial.println("WS3: Parameters has been set");

}

boolean connect()
{
  if(strcmp(ssid.c_str(), "") == 0 || strcmp(pass.c_str(), "") == 0)
  {
    Serial.println("WE6: Parameters to connect are missing");
  }

  WiFi.mode(WIFI_STA);

  WiFi.setAutoReconnect(autoReconnect);
  WiFi.hostname(hostname);
  WiFi.begin(ssid, pass);

  int tries = 0;

  while (WiFi.status() != WL_CONNECTED) {

    if(tries >= numberTries)
    {
      Serial.println("WE1: Failed to connect");
      return false;
    }

    delay(500);
    Serial.print(".");
    tries++;
  }

  Serial.println("WS3: Connected to a Wi-Fi network");

  getSettings();

  return true;
}


void getSettings()
{
  Serial.println("");
  Serial.println("WS2:");
  Serial.println("SSID: " + ssid);
  Serial.print("Auto reconnect: ");
  Serial.println(autoReconnect ? "True" : "False");
  Serial.println("IP address: " + WiFi.localIP().toString());
  Serial.println("Mac: " + WiFi.macAddress());
  Serial.println("Hostname: " + hostname);

}

String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

String getParameter(String data, String startTag) {
  int startIndex = data.indexOf(startTag);
  if (startIndex != -1) {
    startIndex += startTag.length() + 1;
    int endIndex = data.indexOf(" -", startIndex);
    if (endIndex == -1) {
      endIndex = data.indexOf('\n', startIndex);
    }
    if (endIndex == -1) {
      endIndex = data.indexOf('\r', startIndex);
    }
    if(endIndex == -1)
    {
      endIndex = data.length();
    }
    if (endIndex != -1) {
      return data.substring(startIndex, endIndex);
    }
  }
  return "";
}
