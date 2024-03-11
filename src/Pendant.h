// Main Pendant declarations for FluidNC Pendant
//
#include <Arduino.h>

// Config file contains Wi-Fi connection details and FluidNC hostname/port

#include <Wifi.h>
#include <FluidNC_WebSocket.h>

#include <Wire.h>
//include <RotaryEncoder.h>
//#include <AceButton.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
//#include <EEPROM.h>
#include <esp_wifi.h>

//using namespace ace_button;

//#define EEPROM_SIZE 1



//RotaryEncoder *encoderA = nullptr;

// I/O pin definitions
#define PIN_REM1 GPIO_NUM_15
#define PIN_REM2 GPIO_NUM_13
#define PIN_JSX 0//GPIO_NUM_32
#define PIN_JSY //GPIO_NUM_33
#define PIN_REMS GPIO_NUM_2
#define PIN_YELLOW 1//GPIO_NUM_25
#define PIN_GREEN 4//GPIO_NUM_26
#define PIN_RED 3//GPIO_NUM_27
#define PIN_JS_VCC GPIO_NUM_17
#define PIN_BATT 34
#define ADC_EN  14


#define MAX_JOGSTR 50
#define MAX_STATUSSTR 50
#define POWEROFF_TIME 300
#define LINEHEIGHT_DEF  22

enum pendantstate {
  Menu,
  MenuConfirm,
  Pendant,
  RotateChoice,
  MenuSpindleSpeed,
  MenuBrightness
};

enum menuOptions {
  poweroff,
  spindlespeed,
  spindleonoff,
  steps,
  quit,
  home,
  setwxy0,
  setwz0,
  probe,
  gawxy0,
  unlock,
  resetgrbl,
  brightness
};

enum rotorDestin  {
  RotXaxis,
  RotYaxis,
  RotZaxis,
  RotSpindlespeed,
  RotJogspeed,
  RotOvfeed,
  RotOvspeed,
  RotOvrapid
};

enum joystickDestin {
  jsXYaxis,
  jsZaxis
};

volatile pendantstate pState = Pendant;
volatile menuOptions menuState = quit;
volatile rotorDestin rState = RotJogspeed;
volatile joystickDestin jState = jsXYaxis;

const int maxMenu = 12;
const int jogSpeedMax = 5000; //dit moet gelijk lopen met de settings in config.yaml
static char mStateStr[][11] { "? ?", "ALARM", "IDLE", "JOG", "HOME", "CHECK", "RUN", "CYCLE", "HOLD", "SAFE", "SLEEP" };
const int powerOffTime = 60;
volatile bool powerOffNow = false;

String name = "FluidNC";


#define DEBUG_SERIAL Serial

char statusStr[MAX_STATUSSTR];
volatile char g_sbuf[128];
volatile byte menuChoice = 0, backLight = 1;
volatile unsigned long lastJogCmdXYZ = 0, lastStepCmdXYZ = 0;
unsigned long tExec = 1000;
unsigned long statusUpdateInterval = 1000;
const int updateInterval = 198;
volatile float distX = 0, distY = 0, distZ = 0;
volatile int battVolt;
unsigned long sinceStart, lastGrblState;
int rdX = 0, rdY = 0, rdZ = 0, multXYZ = 0;
int calibrateX, calibrateY;
//float mX, mY, mZ;  //Machine positions
//float wX, wY, wZ;  //Work positions
RTC_DATA_ATTR int jogSpeed = 1000; //Overleeft een herstart vanuit sleep
int jogSpeedDisp = 0, setSpindleSpeed = 3000, spindleDisp = -1;
//int reportedSpindleSpeed = 0;
//int ovSpeed = 0, ovFeed = 0, ovRapid = 0;
//bool spindleOn = false;
volatile bool smallSteps = false;
volatile int stepXYZ = 0;
//AceButton buttonREMS, buttonGREEN, buttonYELLOW, buttonRED;

// Predeclare functions
void ConnectWiFi(void);
void otaLoop(void);
IRAM_ATTR void checkPositionA(void);
void forceEndJog(void);
void waitEndJog(void);
int readJSX(void);
int readJSY(void);
int checkJoystick(void);
void checkRotateA(void);
void checkBattery(void);
void printAxisCoords(float m, float w, byte row);
void printCircleBlue (byte x, byte y);

void activeTimer(bool reset);
void getGrblState(bool full);

