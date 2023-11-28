#ifndef DEF_CnlWiFi
#define DEF_CnlWiFi

#include <Arduino.h>
#include <WiFi.h>

namespace cnl
{
  void dummyLogger(const char *s)
  {
  }

  struct WiFiConfig
  {
    String ssid;
    String pass;
    String ip;
    String gateway;
    String subnet; // subnet mask
    void setWiFiConfig()
    {
      IPAddress ipIp;
      IPAddress ipGateway;
      IPAddress ipSubnet(255, 255, 255, 0);

      if (ip != "")
      {
        ipIp.fromString(ip);
      }
      else
      {
        // do not call WiFi.config()
        return;
      }
      if (gateway != "")
      {
        ipGateway.fromString(gateway);
      }
      else
      {
        ipGateway = ipIp;
      }
      if (subnet != "")
      {
        ipSubnet.fromString(subnet);
      }
      ::WiFi.config(ipIp, ipGateway, ipSubnet);
    }
  };

  class WiFi
  {
  private:
    bool bOK;
    void (*logger)(const char *s);

  public:
    WiFiServer server;
    WiFiClient client;

    WiFi(void (*f)(const char *s))
    {
      logger = (f == nullptr) ? dummyLogger : f;
      bOK = false;
      server = WiFiServer(80);
    }

    WiFi() : WiFi(nullptr) {}

    ~WiFi() {}

    void log(const char *s)
    {
      logger(s);
    }

    void log(String str)
    {
      log(str.c_str());
    }

    void logln(const char *s)
    {
      log(s);
      log("\n");
    }

    void logln(String str)
    {
      log(str);
      log("\n");
    }

    bool connected()
    {
      return bOK;
    }

    // get the agent IP
    String getIP()
    {
      return ::WiFi.localIP().toString();
    }

    // connect to the WiFi router specified by conf
    bool connectWiFi(WiFiConfig &conf)
    {
      const int limit = 5;
      const int wait = 500;
      String s;
      int i;

      logln("");
      ::WiFi.begin(conf.ssid, conf.pass);
      delay(1000);
      logln("Connecting to " + conf.ssid);

      for (i = 0; (i < limit) && (::WiFi.status() != WL_CONNECTED); i++)
      {
        delay(wait);
        log(".");
      }
      if (::WiFi.status() == WL_CONNECTED)
      {
        conf.setWiFiConfig();
        logln(" Connected");
        log("IP address: ");
        logln(::WiFi.localIP().toString());
        server.begin();
        return true;
      }
      else
      {
        ::WiFi.disconnect();
        logln(" Failed");
        return false;
      }
    }

    // scan WiFi routers on the list
    bool scan(WiFiConfig clist[], int size)
    {
      const int loop = 3;
      bOK = false;
      for (int i = 0; i < loop; i++)
      {
        for (int i = 0; i < size; i++)
        {
          if (connectWiFi(clist[i]))
          {
            return bOK = true;
          }
        }
        return bOK;
      }
      return bOK;
    }

    WiFiClient &listen()
    {
      // listen for incoming clients
      client = server.available();
      return client;
    }
  };
};
#endif
