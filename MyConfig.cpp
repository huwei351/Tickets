#include <sys/types.h>
#include <unistd.h>
#include <grp.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <string>
#include <iostream>
#include <cctype>
#include <algorithm>

#include "MyConfig.h"


MyConfig::MyConfig() : Config()
{
    pthread_mutex_init(&mLock, NULL);
    ReadFile(strConfgFileName);
}
MyConfig::~MyConfig()
{
    pthread_mutex_destroy(&mLock);
    printf("Destructor, save to file: %s\n",  strConfgFileName.c_str());
    Save(strConfgFileName);
}

// set functions
void MyConfig::setNumWeight(float weight)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyNumWeight, (float)weight);
    UNLOCK();
}
void MyConfig::setWuxingWeight(float weight)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyWuxingWeight, (float)weight);
    UNLOCK();
}
void MyConfig::setDatabaseTableLength(char* table, int len)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);

    if(strcmp(table, "ssq_result") == 0)
    { Add(KeySsqTableLength, (int)len); }
    else if(strcmp(table, "dlt_result") == 0)
    { Add(KeyDltTableLength, (int)len); }

    UNLOCK();
}
void MyConfig::setStartupMode(int mode)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyStartupMode, (int)mode);
    // Mutex::Autolock lock(mLock);
    // if(ChangeSection("default") == false) {
    //     printf("Add section : %s", strDefaultSection.c_str());
    //     AddSection(strDefaultSection);
    // }
}
void MyConfig::setCurMode(int mode)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyCurMode, (int)mode);
}
void MyConfig::setCountryCode(const std::string code)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyCountryCode, code);
}
void MyConfig::setCertificationAddon(bool state)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyCertificationAddon, state);
}
void MyConfig::setConnectMeAddon(bool state)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyConnectMeAddon, state);
}
void MyConfig::setNearbySenseAddon(bool state)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(keyNearbySenseAddon, state);
}

void MyConfig::setMeshSsid(const std::string ssid)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyMeshSsid, ssid);
}
void MyConfig::setMeshBssid(const std::string bssid)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyMeshBssid, bssid);
}
void MyConfig::setMeshKeyMgnt(int key_mgnt)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyMeshKeyMgnt, key_mgnt);
}
void MyConfig::setMeshAlgo(int algo)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyMeshAlgo, algo);
}
void MyConfig::setMeshPass(const std::string pass)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyMeshPass, pass);
}


void MyConfig::setMeshApSsid(const std::string ssid)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyMeshApSsid, ssid);
}
void MyConfig::setMeshApBssid(const std::string bssid)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyMeshApBssid, bssid);
}
void MyConfig::setMeshApKeyMgnt(int key_mgnt)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyMeshApKeyMgnt, key_mgnt);
}
void MyConfig::setMeshApAlgo(int algo)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyMeshApAlgo, algo);
}
void MyConfig::setMeshApPass(const std::string pass)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyMeshApPass, pass);
}


void MyConfig::setMeshStaSsid(const std::string ssid)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyMeshStaSsid, ssid);
}
void MyConfig::setMeshStaBssid(const std::string bssid)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyMeshStaBssid, bssid);
}
void MyConfig::setMeshStaKeyMgnt(int key_mgnt)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyMeshStaKeyMgnt, key_mgnt);
}
void MyConfig::setMeshStaAlgo(int algo)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyMeshStaAlgo, algo);
}
void MyConfig::setMeshStaPass(const std::string pass)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyMeshStaPass, pass);
}


void MyConfig::setMeshTxPwr(int pwr)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyMeshTxPwr, pwr);
}
void MyConfig::setMeshTxPwrSta(int pwr)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyMeshTxPwrSta, pwr);
}
void MyConfig::setMeshTxPwrAp(int pwr)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyMeshTxPwrAp, pwr);
}

void MyConfig::setExtensionSsid(const std::string ssid)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyExtensionSsid, ssid);
}
void MyConfig::setExtensionBssid(const std::string bssid)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyExtensionBssid, bssid);
}
void MyConfig::setExtensionKeyMgnt(int key_mgnt)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyExtensionKeyMgnt, key_mgnt);
}
void MyConfig::setExtensionPass(const std::string pass)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyExtensionPass, pass);
}
void MyConfig::setExtensionTxPwrSta(int pwr)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyExtensionTxPwrSta, pwr);
}
void MyConfig::setExtensionTxPwrAp(int pwr)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyExtensionTxPwrAp, pwr);
}

void MyConfig::setExtensionChannel(int channel)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyExtensionChannel, channel);
}
void MyConfig::setExtensionBandwidth(int bandwidth)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyExtensionBandwidth, bandwidth);
}
void MyConfig::setExtensionGateWay(const std::string softApIpAddress)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyExtensionGateWay, softApIpAddress);
}
void MyConfig::setExtensionBand(int band)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyExtensionBand, band);
}

void MyConfig::setPlayDirectSsid(const std::string ssid)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyPlayDirectSsid, ssid);
}

void MyConfig::setPlayDirectBssid(const std::string bssid)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyPlayDirectBssid, bssid);
}

void MyConfig::setPlayDirectKeyMgnt(int key_mgnt)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyPlayDirectKeyMgnt, key_mgnt);
}

void MyConfig::setPlayDirectPass(const std::string pass)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyPlayDirectPass, pass);
}

void MyConfig::setPlayDirectTxPwr(int pwr)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyPlayDirectTxPwr, pwr);
}
void MyConfig::setPlayDirectChannel(int chnl)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyPlayDirectChannel, chnl);
}

void MyConfig::setWacPwr(int pwr)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyWacPwr, pwr);
}
void MyConfig::setWacChannel(int chnl)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyWacChannel, chnl);
}

void MyConfig::setStationTxPwr(int pwr)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyStationTxPwr, pwr);
}

void MyConfig::setStationIpAssignment(const std::string ssid, const std::string bssid, int ipa)
{
    LOCK_AND_SWITH_TO_SECTION((ssid + bssid));
    Add(KeyStationIpAssignment, ipa);
}
void MyConfig::setStationStaticIp(const std::string ssid, const std::string bssid, const std::string ip)
{
    LOCK_AND_SWITH_TO_SECTION(ssid + bssid);
    Add(KeyStationStaticIp, ip);
}
void MyConfig::setStationNetMask(const std::string ssid, const std::string bssid, const std::string mask)
{
    LOCK_AND_SWITH_TO_SECTION(ssid + bssid);
    Add(KeyStationNetMask, mask);
}
void MyConfig::setStationGateway(const std::string ssid, const std::string bssid, const std::string ip)
{
    LOCK_AND_SWITH_TO_SECTION(ssid + bssid);
    Add(KeyStationGateway, ip);
}
void MyConfig::setStationDns1(const std::string ssid, const std::string bssid, const std::string ip)
{
    LOCK_AND_SWITH_TO_SECTION(ssid + bssid);
    Add(KeyStationDns1, ip);
}
void MyConfig::setStationDns2(const std::string ssid, const std::string bssid, const std::string ip)
{
    LOCK_AND_SWITH_TO_SECTION(ssid + bssid);
    Add(KeyStationDns2, ip);
}

void MyConfig::setWebPortalGateway(const std::string ssid, const std::string bssid, const std::string ip)
{
    LOCK_AND_SWITH_TO_SECTION(ssid + bssid);
    Add(KeyWebPortalGateway, ip);
}
void MyConfig::setWebPortalUser(const std::string ssid, const std::string bssid, const std::string user)
{
    LOCK_AND_SWITH_TO_SECTION(ssid + bssid);
    Add(KeyWebPortalUser, user);
}

void MyConfig::setWebPortalPassword(const std::string ssid, const std::string bssid, const std::string pass)
{
    LOCK_AND_SWITH_TO_SECTION(ssid + bssid);
    Add(KeyWebPortalPass, pass);
}


// get functions
float MyConfig::getNumWeight()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    float r = 0.5;

    if(KeyExists(KeyNumWeight))
    { r = Read<float>(KeyNumWeight); }

    UNLOCK();
    return r;
}
float MyConfig::getWuxingWeight()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    float r = 0.5;

    if(KeyExists(KeyWuxingWeight))
    { r = Read<float>(KeyWuxingWeight); }

    UNLOCK();
    return r;
}
int MyConfig::getDatabaseTableLength(char* table)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = 0;

    if(strcmp(table, "ssq_result") == 0) {
        if(KeyExists(KeySsqTableLength))
        { r = Read<int>(KeySsqTableLength); }
    } else if(strcmp(table, "dlt_result") == 0) {
        if(KeyExists(KeyDltTableLength))
        { r = Read<int>(KeyDltTableLength); }
    }

    UNLOCK();
    return r;
}
int MyConfig::getStartupMode()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyStartupMode))
    { r = Read<int>(KeyStartupMode); }

    return r;
}
int MyConfig::getCurMode()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyCurMode))
    { r = Read<int>(KeyCurMode); }

    return r;
}
const std::string MyConfig::getCountryCode()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    std::string r = "";

    if(KeyExists(KeyCountryCode))
    { r = Read<std::string>(KeyCountryCode); }

    return r;
}
bool MyConfig::getCertificationAddon()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    bool r = false;

    if(KeyExists(KeyCertificationAddon))
    { r = Read <bool> (KeyCertificationAddon); }

    return r;
}
bool MyConfig::getConnectMeAddon()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    bool r = false;

    if(KeyExists(KeyConnectMeAddon))
    { r = Read <bool> (KeyConnectMeAddon); }

    return r;
}
bool MyConfig::getNearbySenseAddon()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    bool r = false;

    if(KeyExists(keyNearbySenseAddon))
    { r = Read <bool> (keyNearbySenseAddon); }

    return r;
}

const std::string MyConfig::getMeshSsid()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    std::string r = "";

    if(KeyExists(KeyMeshSsid))
    { r = Read<std::string>(KeyMeshSsid); }

    return r;
}
const std::string MyConfig::getMeshBssid()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    std::string r = "";

    if(KeyExists(KeyMeshBssid))
    { r = Read<std::string>(KeyMeshBssid); }

    return r;
}
int MyConfig::getMeshKeyMgnt()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyMeshKeyMgnt))
    { r = Read<int>(KeyMeshKeyMgnt); }

    return r;
}
int MyConfig::getMeshAlgo()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyMeshAlgo))
    { r = Read<int>(KeyMeshAlgo); }

    return r;
}
const std::string MyConfig::getMeshPass()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    std::string r = "";

    if(KeyExists(KeyMeshPass))
    { r = Read<std::string>(KeyMeshPass); }

    return r;
}


const std::string MyConfig::getMeshApSsid()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    std::string r = "";

    if(KeyExists(KeyMeshApSsid))
    { r = Read<std::string>(KeyMeshApSsid); }

    return r;
}
const std::string MyConfig::getMeshApBssid()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    std::string r = "";

    if(KeyExists(KeyMeshApBssid))
    { r = Read<std::string>(KeyMeshApBssid); }

    return r;
}
int MyConfig::getMeshApKeyMgnt()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyMeshApKeyMgnt))
    { r = Read<int>(KeyMeshApKeyMgnt); }

    return r;
}
int MyConfig::getMeshApAlgo()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyMeshApAlgo))
    { r = Read<int>(KeyMeshApAlgo); }

    return r;
}
const std::string MyConfig::getMeshApPass()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    std::string r = "";

    if(KeyExists(KeyMeshApPass))
    { r = Read<std::string>(KeyMeshApPass); }

    return r;
}



const std::string MyConfig::getMeshStaSsid()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    std::string r = "";

    if(KeyExists(KeyMeshStaSsid))
    { r = Read<std::string>(KeyMeshStaSsid); }

    return r;
}
const std::string MyConfig::getMeshStaBssid()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    std::string r = "";

    if(KeyExists(KeyMeshStaBssid))
    { r = Read<std::string>(KeyMeshStaBssid); }

    return r;
}
int MyConfig::getMeshStaKeyMgnt()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyMeshStaKeyMgnt))
    { r = Read<int>(KeyMeshStaKeyMgnt); }

    return r;
}
int MyConfig::getMeshStaAlgo()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyMeshStaAlgo))
    { r = Read<int>(KeyMeshStaAlgo); }

    return r;
}
const std::string MyConfig::getMeshStaPass()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    std::string r = "";

    if(KeyExists(KeyMeshStaPass))
    { r = Read<std::string>(KeyMeshStaPass); }

    return r;
}


int MyConfig::getMeshTxPwr()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyMeshTxPwr))
    { r = Read<int>(KeyMeshTxPwr); }

    return r;
}
int MyConfig::getMeshTxPwrSta()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyMeshTxPwrSta))
    { r = Read<int>(KeyMeshTxPwrSta); }

    return r;
}
int MyConfig::getMeshTxPwrAp()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyMeshTxPwrAp))
    { r = Read<int>(KeyMeshTxPwrAp); }

    return r;
}

const std::string MyConfig::getExtensionSsid()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    std::string r = "";

    if(KeyExists(KeyExtensionSsid))
    { r = Read<std::string>(KeyExtensionSsid); }

    return r;
}
const std::string MyConfig::getExtensionBssid()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    std::string r = "";

    if(KeyExists(KeyExtensionBssid))
    { r = Read<std::string>(KeyExtensionBssid); }

    return r;
}
int MyConfig::getExtensionKeyMgnt()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyExtensionKeyMgnt))
    { r = Read<int>(KeyExtensionKeyMgnt); }

    return r;
}
const std::string MyConfig::getExtensionPass()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    std::string r = "";

    if(KeyExists(KeyExtensionPass))
    { r = Read<std::string>(KeyExtensionPass); }

    return r;
}
int MyConfig::getExtensionTxPwrSta()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyExtensionTxPwrSta))
    { r = Read<int>(KeyExtensionTxPwrSta); }

    return r;
}

int MyConfig::getExtensionTxPwrAp()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyExtensionTxPwrAp))
    { r = Read<int>(KeyExtensionTxPwrAp); }

    return r;
}

int MyConfig::getExtensionChannel()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyExtensionChannel))
    { r = Read<int>(KeyExtensionChannel); }

    return r;
}

int MyConfig::getExtensionBandwidth()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyExtensionBandwidth))
    { r = Read<int>(KeyExtensionBandwidth); }

    return r;
}

const std::string  MyConfig::getExtensionGateWay()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    std::string r = "";

    if(KeyExists(KeyExtensionGateWay))
    { r = Read<std::string>(KeyExtensionGateWay); }

    return r;
}

int MyConfig::getExtensionBand()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyExtensionBand))
    { r = Read<int>(KeyExtensionBand); }

    return r;
}

const std::string MyConfig::getPlayDirectSsid()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    std::string r = "";

    if(KeyExists(KeyPlayDirectSsid))
    { r = Read<std::string>(KeyPlayDirectSsid); }

    return r;
}

const std::string MyConfig::getPlayDirectBssid()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    std::string r = "";

    if(KeyExists(KeyPlayDirectBssid))
    { r = Read<std::string>(KeyPlayDirectBssid); }

    return r;
}

int MyConfig::getPlayDirectKeyMgnt()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyPlayDirectKeyMgnt))
    { r = Read<int>(KeyPlayDirectKeyMgnt); }

    return r;
}

const std::string MyConfig::getPlayDirectPass()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    std::string r = "";

    if(KeyExists(KeyPlayDirectPass))
    { r = Read<std::string>(KeyPlayDirectPass); }

    return r;
}

int MyConfig::getPlayDirectTxPwr()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyPlayDirectTxPwr))
    { r = Read<int>(KeyPlayDirectTxPwr); }

    return r;
}
int MyConfig::getPlayDirectChannel()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyPlayDirectChannel))
    { r = Read<int>(KeyPlayDirectChannel); }

    return r;
}

int MyConfig::getWacPwr()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyWacPwr))
    { r = Read<int>(KeyWacPwr); }

    return r;
}
int MyConfig::getWacChannel()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyWacChannel))
    { r = Read<int>(KeyWacChannel); }

    return r;
}

int MyConfig::getStationTxPwr()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyStationTxPwr))
    { r = Read<int>(KeyStationTxPwr); }

    return r;
}

int MyConfig::getStationIpAssignment(const std::string ssid, const std::string bssid)
{
    LOCK_AND_SWITH_TO_SECTION((ssid + bssid));
    int r = -1;

    if(KeyExists(KeyStationIpAssignment))
    { r = Read<int>(KeyStationIpAssignment); }

    return r;
}
const std::string MyConfig::getStationStaticIp(const std::string ssid, const std::string bssid)
{
    LOCK_AND_SWITH_TO_SECTION(ssid + bssid);
    std::string r = "";

    if(KeyExists(KeyStationStaticIp))
    { r = Read<std::string>(KeyStationStaticIp); }

    return r;
}
const std::string MyConfig::getStationNetMask(const std::string ssid, const std::string bssid)
{
    LOCK_AND_SWITH_TO_SECTION(ssid + bssid);
    std::string r = "";

    if(KeyExists(KeyStationNetMask))
    { r = Read<std::string>(KeyStationNetMask); }

    return r;
}
const std::string MyConfig::getStationGateway(const std::string ssid, const std::string bssid)
{
    LOCK_AND_SWITH_TO_SECTION(ssid + bssid);
    std::string r = "";

    if(KeyExists(KeyStationGateway))
    { r = Read<std::string>(KeyStationGateway); }

    return r;
}
const std::string MyConfig::getStationDns1(const std::string ssid, const std::string bssid)
{
    LOCK_AND_SWITH_TO_SECTION(ssid + bssid);
    std::string r = "";

    if(KeyExists(KeyStationDns1))
    { r = Read<std::string>(KeyStationDns1); }

    return r;
}
const std::string MyConfig::getStationDns2(const std::string ssid, const std::string bssid)
{
    LOCK_AND_SWITH_TO_SECTION(ssid + bssid);
    std::string r = "";

    if(KeyExists(KeyStationDns2))
    { r = Read<std::string>(KeyStationDns2); }

    return r;
}

const std::string MyConfig::getWebPortalGateway(const std::string ssid, const std::string bssid)
{
    LOCK_AND_SWITH_TO_SECTION(ssid + bssid);
    std::string r = "";

    if(KeyExists(KeyWebPortalGateway))
    { r = Read<std::string>(KeyWebPortalGateway); }

    return r;
}
const std::string MyConfig::getWebPortalUser(const std::string ssid, const std::string bssid)
{
    LOCK_AND_SWITH_TO_SECTION(ssid + bssid);
    std::string r = "";

    if(KeyExists(KeyWebPortalUser))
    { r = Read<std::string>(KeyWebPortalUser); }

    return r;
}

const std::string MyConfig::getWebPortalPassword(const std::string ssid, const std::string bssid)
{
    LOCK_AND_SWITH_TO_SECTION(ssid + bssid);
    std::string r = "";

    if(KeyExists(KeyWebPortalPass))
    { r = Read<std::string>(KeyWebPortalPass); }

    return r;
}


void MyConfig::setInitialSetupMode(bool mode)
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    Add(KeyIntialSteupMode, (int)mode);
}

bool MyConfig::isInitialSetupMode()
{
    LOCK_AND_SWITH_TO_SECTION(strDefaultSection);
    int r = -1;

    if(KeyExists(KeyIntialSteupMode))
    { r = Read<int>(KeyIntialSteupMode); }

    return (bool)r;
}
