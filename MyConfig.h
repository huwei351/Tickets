
#ifndef MY_CONFIG_H
#define MY_CONFIG_H
#include <string>
#include <pthread.h>

#include "Config.h"

#define LOCK_AND_SWITH_TO_SECTION(s)   \
    pthread_mutex_lock(&mLock);    \
    if(ChangeSection(s) == false)   \
        AddSection(s)

#define UNLOCK()  pthread_mutex_unlock(&mLock);

#ifdef DLT
const std::string strConfgFileName = "./configs/dltconfig.conf";
#else
const std::string strConfgFileName = "./configs/ssqconfig.conf";
#endif
const std::string strDefaultSection = "default";

/* Global for all working (net) modes */
const std::string KeyNumWeight = "num.weight";
const std::string KeyWuxingWeight = "wuxing.weight";
const std::string KeyStartupMode = "startup.mode";
const std::string KeyIntialSteupMode = "initial.setup.mode";
const std::string KeyCurMode = "current.mode";
const std::string KeyCountryCode = "region.alpha2";
const std::string KeyCertificationAddon = "certification.addon";
const std::string KeyConnectMeAddon = "connect.me.addon";
const std::string keyNearbySenseAddon = "nearby.sense.addon";

/*  configs for mesh related modes */
const std::string KeyMeshSsid = "mesh.mn.ssid";
const std::string KeyMeshBssid = "mesh.mn.bssid";
const std::string KeyMeshKeyMgnt = "mesh.mn.key_mgnt";
const std::string KeyMeshAlgo = "mesh.mn.algo";
const std::string KeyMeshPass = "mesh.mn.password";

const std::string KeyMeshApSsid = "mesh.ap.ssid";
const std::string KeyMeshApBssid = "mesh.ap.bssid";
const std::string KeyMeshApKeyMgnt = "mesh.ap.key_mgnt";
const std::string KeyMeshApAlgo = "mesh.ap.algo";
const std::string KeyMeshApPass = "mesh.ap.password";

const std::string KeyMeshStaSsid = "mesh.sta.ssid";
const std::string KeyMeshStaBssid = "mesh.sta.bssid";
const std::string KeyMeshStaKeyMgnt = "mesh.sta.key_mgnt";
const std::string KeyMeshStaAlgo = "mesh.sta.algo";
const std::string KeyMeshStaPass = "mesh.sta.password";

const std::string KeyMeshTxPwr = "mesh.txpwr.mn"; /* mesh node */
const std::string KeyMeshTxPwrSta = "mesh.txpwr.sta";
const std::string KeyMeshTxPwrAp = "mesh.txpwr.ap";

const std::string KeyExtensionSsid = "extension.ssid";
const std::string KeyExtensionBssid = "extension.bssid";
const std::string KeyExtensionKeyMgnt = "extension.key_mgnt";
const std::string KeyExtensionPass = "extension.password";
const std::string KeyExtensionTxPwrSta = "extension.txpwr.sta";
const std::string KeyExtensionTxPwrAp = "extension.txpwr.ap";
const std::string KeyExtensionChannel = "extension.channel";
const std::string KeyExtensionBandwidth = "extension.bandwidth";
const std::string KeyExtensionGateWay = "extension.gateway";
const std::string KeyExtensionBand = "extension.band";

/* configs for playdriect mode */
const std::string KeyPlayDirectSsid = "playdriect.ssid";
const std::string KeyPlayDirectBssid = "playdriect.bssid";
const std::string KeyPlayDirectKeyMgnt = "playdriect.key_mgnt";
const std::string KeyPlayDirectPass = "playdriect.password";
const std::string KeyPlayDirectTxPwr = "playdriect.txpwr.ap";
const std::string KeyPlayDirectChannel = "playdriect.channel.ap";

/* configs for setup  (i.e WAC ) mode */
const std::string KeyWacPwr = "wac.txpwr.ap";
const std::string KeyWacChannel = "wac.channel.ap";


/* configs for station mode */
const std::string KeyStationTxPwr = "station.txpwr.sta";

/* For each net (ssid, bssid), store following parameters if static ip assign */
const std::string KeyStationIpAssignment = "station.ip.assignment";
const std::string KeyStationStaticIp = "station.staticip";
const std::string KeyStationNetMask = "station.netmask";
const std::string KeyStationGateway = "station.gateway";
const std::string KeyStationDns1 = "station.dns1";
const std::string KeyStationDns2 = "station.dns2";

/* For each net (ssid, bssid), store following parameters if it uses web portal authentication */
const std::string KeyWebPortalGateway = "station.webportal.gateway";
const std::string KeyWebPortalUser = "station.webportal.user";
const std::string KeyWebPortalPass = "station.webportal.password";


class MyConfig : public Config
{

    public:

        MyConfig();
        ~MyConfig();
        void setNumWeight(float weight);
        void setWuxingWeight(float weight);
        void setStartupMode(int mode);
        void setCurMode(int mode);
        void setCountryCode(std::string code);
        void setCertificationAddon(bool state);
        void setConnectMeAddon(bool state);
        void setNearbySenseAddon(bool state);

        void setMeshSsid(const std::string ssid);
        void setMeshBssid(const std::string bssid);
        void setMeshKeyMgnt(int key_mgnt);
        void setMeshAlgo(int algo);
        void setMeshPass(const std::string pass);

        void setMeshApSsid(const std::string ssid);
        void setMeshApBssid(const std::string bssid);
        void setMeshApKeyMgnt(int key_mgnt);
        void setMeshApAlgo(int algo);
        void setMeshApPass(const std::string pass);

        void setMeshStaSsid(const std::string ssid);
        void setMeshStaBssid(const std::string bssid);
        void setMeshStaKeyMgnt(int key_mgnt);
        void setMeshStaAlgo(int algo);
        void setMeshStaPass(const std::string pass);

        void setMeshTxPwr(int pwr);
        void setMeshTxPwrSta(int pwr);
        void setMeshTxPwrAp(int pwr);

        void setExtensionSsid(const std::string);
        void setExtensionBssid(const std::string);
        void setExtensionKeyMgnt(int key_mgnt);
        void setExtensionPass(const std::string);
        void setExtensionTxPwrSta(int pwr);
        void setExtensionTxPwrAp(int pwr);
        void setExtensionChannel(int channel);
        void setExtensionBandwidth(int bandwidth);
        void setExtensionGateWay(const std::string softApIpAddress);
        void setExtensionBand(int band);

        void setPlayDirectSsid(const std::string ssid);
        void setPlayDirectBssid(const std::string bssid);
        void setPlayDirectKeyMgnt(int key_mgnt);
        void setPlayDirectPass(const std::string pass);
        void setPlayDirectTxPwr(int pwr);
        void setPlayDirectChannel(int pwr);

        void setWacPwr(int pwr);
        void setWacChannel(int pwr);

        void setStationTxPwr(int pwr);

        void setStationIpAssignment(const std::string ssid, const std::string bssid, int ipa);
        void setStationStaticIp(const std::string ssid, const std::string bssid, const std::string ip);
        void setStationNetMask(const std::string ssid, const std::string bssid, const std::string mask);
        void setStationGateway(const std::string ssid, const std::string bssid, const std::string ip);
        void setStationDns1(const std::string ssid, const std::string bssid, const std::string ip);
        void setStationDns2(const std::string ssid, const std::string bssid, const std::string ip);

        void setWebPortalGateway(const std::string ssid, const std::string bssid, const std::string ip);
        void setWebPortalUser(const std::string ssid, const std::string bssid, const std::string user);
        void setWebPortalPassword(const std::string ssid, const std::string bssid, const std::string pass);
        void setDeviceName(std::string name);

        float getNumWeight();
        float getWuxingWeight();
        int getStartupMode();
        int getCurMode();
        const std::string getCountryCode();
        bool getCertificationAddon();
        bool getConnectMeAddon();
        bool getNearbySenseAddon();

        const std::string getMeshSsid();
        const std::string getMeshBssid();
        int getMeshKeyMgnt();
        int getMeshAlgo();
        const std::string getMeshPass();

        const std::string getMeshApSsid();
        const std::string getMeshApBssid();
        int getMeshApKeyMgnt();
        int getMeshApAlgo();
        const std::string getMeshApPass();

        const std::string getMeshStaSsid();
        const std::string getMeshStaBssid();
        int getMeshStaKeyMgnt();
        int getMeshStaAlgo();
        const std::string getMeshStaPass();

        int getMeshTxPwr();
        int getMeshTxPwrSta();
        int getMeshTxPwrAp();

        const std::string getExtensionSsid();
        const std::string getExtensionBssid();
        int getExtensionKeyMgnt();
        const std::string getExtensionPass();
        int getExtensionTxPwrSta();
        int getExtensionTxPwrAp();
        int getExtensionChannel();
        int getExtensionBandwidth();
        const std::string getExtensionGateWay();
        int getExtensionBand();

        const std::string getPlayDirectSsid();
        const std::string getPlayDirectBssid();
        int getPlayDirectKeyMgnt();
        const std::string getPlayDirectPass();
        int getPlayDirectTxPwr();
        int getPlayDirectChannel();

        int getWacPwr();
        int getWacChannel();

        int getStationTxPwr();

        int getStationIpAssignment(const std::string ssid, const std::string bssid);
        const std::string getStationStaticIp(const std::string ssid, const std::string bssid);
        const std::string getStationNetMask(const std::string ssid, const std::string bssid);
        const std::string getStationGateway(const std::string ssid, const std::string bssid);
        const std::string getStationDns1(const std::string ssid, const std::string bssid);
        const std::string getStationDns2(const std::string ssid, const std::string bssid);

        const std::string getWebPortalGateway(const std::string ssid, const std::string bssid);
        const std::string getWebPortalUser(const std::string ssid, const std::string bssid);
        const std::string getWebPortalPassword(const std::string ssid, const std::string bssid);

        /* Config saved in android properties */
        void setInitialSetupMode(bool mode);
        bool isInitialSetupMode();

        void setPlayDirectMode(bool on);
        bool isInPlayDirectMode();

        std::string getWifiSsid();
        std::string getDeviceName();
        std::string getSerialNumber();
        std::string getManufacturer();
        std::string getModelName();

        int getRegionCode(std::string region);
        bool isForAirplayCertification();

    private:

        pthread_mutex_t mLock;
};

#endif
