#include <Arduino.h>
#include "CnlWiFi.h"
#include "config.h"

void log(const char *s)
{
  Serial.print(s);
}

cnl::WiFi wifi(log);
HardwareSerial &serial = Serial2;

void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial2.begin(9600);

  int csize = sizeof(configs) / sizeof(cnl::WiFiConfig);
  if (wifi.scan(configs, csize))
  {
    log("WiFi OK\n");
  }
  else
  {
    log("Failed all\n");
  }
}

void loop()
{
  if (wifi.connected())
  {
    WiFiClient client = wifi.listen();
    if (client.connected())
    {
      client.printf("Hello new client\n");
      client.printf("Me = %s\n", wifi.getIP().c_str());
    }

    while (client.connected())
    {
      if (client.available())
      {
        String s = client.readString();
        if (s.startsWith("cnl:quit"))
        {
          client.stop();
          break;
        }
        serial.print(s);
      }
      if (serial.available())
      {
        String s = serial.readString();
        client.print(s);
      }
    }
  }
}
