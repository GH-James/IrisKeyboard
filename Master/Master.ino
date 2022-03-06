#include <HID.h>
#include <Wire.h>
#include "KeyCodes.h"

#define rows 5
#define cols 6
#define extraCols 6

int rowPins[rows] = {15, 14, 16, 10, 5};
int colPins[cols] = {A2, A1, 9, 8, 7, 6};

bool mouseUp = false;
bool mouseDown = false;
bool mouseLeft = false;
bool mouseRight = false;
bool mouseScrollUp = false;
bool mouseScrollDown = false;
int lastMouseMove = 0;

int prevScan[rows][cols + extraCols] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
int currScan[rows][cols + extraCols] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

uint16_t keebLayout[rows][cols + extraCols] = {{}, {}, {}, {}, {}};
uint16_t prevLayout[rows][cols + extraCols] = {{}, {}, {}, {}, {}};

uint16_t alphaLayer[rows][cols + extraCols] = {
  {KEY_ESC , KEY_GRAVE, MEDIA_PREV, MEDIA_PLAY_PAUSE, MEDIA_NEXT, KEY_F2      ,/*     */KEY_F5      , MEDIA_VOL_DOWN, MEDIA_VOL_MUTE, MEDIA_VOL_UP, KEY_PRINT_SCREEN, KEY_DELETE},
  {KEY_TAB , KEY_Q    , KEY_W     , KEY_E           , KEY_R     , KEY_T       ,/*     */KEY_Y       , KEY_U         , KEY_I         , KEY_O       , KEY_P           , KEY_BACKSLASH},
  {KEY_ALT , KEY_A    , KEY_S     , KEY_D           , KEY_F     , KEY_G       ,/*     */KEY_H       , KEY_J         , KEY_K         , KEY_L       , KEY_SEMICOLON   , KEY_APOSTROPHE},
  {KEY_CTRL, KEY_Z    , KEY_X     , KEY_C           , KEY_V     , KEY_B       ,/*     */KEY_N       , KEY_M         , KEY_COMMA     , KEY_DOT     , KEY_SLASH       , HOLD_LAYER_3},
  {KEY_NONE, KEY_NONE , KEY_META  , KEY_BACKSPACE   , KEY_SHIFT , HOLD_LAYER_1,/*     */HOLD_LAYER_2, KEY_SPACE     , KEY_ENTER     , KEY_ALT     , KEY_NONE        , KEY_NONE}
};

uint16_t symbolLayer[rows][cols + extraCols] = {
  {KEY_F1         , KEY_F2          , KEY_F3        , KEY_F4        , KEY_F5          , KEY_F6      ,/*     */KEY_F7    , KEY_F8          , KEY_F9            , KEY_F10   , KEY_F11       , KEY_F12},
  {TOGGLE_LAYER_4 , KEY_EXCLAMATION , KEY_2         , KEY_3         , KEY_4           , KEY_5       ,/*     */KEY_6     , KEY_7           , KEY_8             , KEY_9     , KEY_0         , KEY_DELETE},
  {KEY_TAB        , KEY_LESS        , KEY_GREATER   , KEY_LEFT_CURLY, KEY_RIGHT_CURLY , KEY_AT      ,/*     */KEY_DOLLAR, KEY_LEFT_BRACKET, KEY_RIGHT_BRACKET , KEY_COLON , KEY_SEMICOLON , KEY_CARET},
  {KEY_CTRL       , KEY_SLASH       , KEY_UNDERSCORE, KEY_LEFTBRACE , KEY_RIGHTBRACE  , KEY_HASH    ,/*     */KEY_MINUS , KEY_AMPERSAND   , KEY_PIPE          , KEY_PLUS  , KEY_ASTERISK  , KEY_MODULO},
  {KEY_NONE       , KEY_NONE        , KEY_META      , KEY_BACKSPACE , KEY_SHIFT       , HOLD_LAYER_0,/*     */KEY_NONE  , KEY_SPACE       , KEY_ENTER         , KEY_ALT   , KEY_NONE      , KEY_NONE}
};

uint16_t numLayer[rows][cols + extraCols] = {
  {KEY_ESC  , KEY_NONE    , KEY_NONE, KEY_NONE      , KEY_NONE  , KEY_NONE,/*     */KEY_NONE      , KEY_NONE  , KEY_NUMLOCK , KEY_NONE, KEY_NONE    , KEY_DELETE},
  {KEY_TAB  , KEY_PAGEUP  , KEY_NONE, KEY_UP        , KEY_NONE  , KEY_HOME,/*     */KEY_KPSLASH   , KEY_KP7   , KEY_KP8     , KEY_KP9 , KEY_KPMINUS , KEY_NONE},
  {KEY_TAB  , KEY_PAGEDOWN, KEY_LEFT, KEY_DOWN      , KEY_RIGHT , KEY_END ,/*     */KEY_KP0       , KEY_KP4   , KEY_KP5     , KEY_KP6 , KEY_KPPLUS  , KEY_EQUAL},
  {KEY_NONE , KEY_NONE    , KEY_NONE, KEY_NONE      , KEY_NONE  , KEY_NONE,/*     */KEY_KPASTERISK, KEY_KP1   , KEY_KP2     , KEY_KP3 , KEY_KPDOT   , KEY_NONE},
  {KEY_NONE , KEY_NONE    , KEY_META, KEY_BACKSPACE , KEY_SHIFT , KEY_NONE,/*     */HOLD_LAYER_0  , KEY_SPACE , KEY_ENTER   , KEY_ALT , KEY_NONE    , KEY_NONE}
};

uint16_t mouseLayer[rows][cols + extraCols] = {
  {KEY_NONE, KEY_NONE, KEY_NONE , KEY_NONE, KEY_NONE, KEY_NONE,/*     */KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
  {KEY_NONE, KEY_NONE, KEY_NONE , 0x03    , KEY_NONE, KEY_NONE,/*     */KEY_NONE, KEY_NONE, 0x07    , KEY_NONE, KEY_NONE, KEY_NONE},
  {KEY_NONE, KEY_NONE, 0x05     , 0x04    , 0x06    , KEY_NONE,/*     */KEY_NONE, KEY_NONE, 0x08    , KEY_NONE, KEY_NONE, KEY_NONE},
  {KEY_NONE, KEY_NONE, KEY_NONE , KEY_NONE, KEY_NONE, KEY_NONE,/*     */KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, HOLD_LAYER_0},
  {KEY_NONE, KEY_NONE, KEY_NONE , 0x0b    , 0x01    , KEY_NONE,/*     */KEY_NONE, 0x02    , 0x0c    , KEY_NONE, 0x00    , KEY_NONE}
};

uint16_t gameLayer[rows][cols + extraCols] = {
  {KEY_ESC  , KEY_1   , KEY_2   , KEY_3     , KEY_4     , KEY_5         ,/*     */ MEDIA_VOL_DOWN , MEDIA_VOL_MUTE, MEDIA_VOL_UP, MEDIA_PREV, MEDIA_PLAY_PAUSE, MEDIA_NEXT},
  {KEY_TAB  , KEY_Q   , KEY_W   , KEY_E     , KEY_R     , KEY_T         ,/*     */ KEY_Y          , KEY_U         , KEY_I       , KEY_O     , KEY_P           , KEY_BACKSLASH},
  {KEY_ALT  , KEY_A   , KEY_S   , KEY_D     , KEY_F     , KEY_G         ,/*     */ KEY_H          , KEY_J         , KEY_K       , KEY_L     , KEY_SEMICOLON   , KEY_APOSTROPHE},
  {KEY_CTRL , KEY_Z   , KEY_X   , KEY_C     , KEY_V     , KEY_B         ,/*     */ KEY_N          , KEY_M         , KEY_COMMA   , KEY_DOT   , KEY_SLASH       , KEY_NONE},
  {KEY_NONE , KEY_NONE, KEY_META, KEY_SPACE , KEY_SHIFT , TOGGLE_LAYER_0,/*     */ KEY_NONE       , KEY_BACKSPACE , KEY_ENTER   , KEY_ALT   , KEY_NONE        , KEY_NONE}
};

typedef struct
{
  uint8_t modifiers;
  uint8_t reserved;
  uint8_t keys[6];
} KeyReport;

typedef union {
  // Every usable Consumer key possible, up to 4 keys presses posibsle
  uint8_t whole8[0];
  uint16_t whole16[0];
  uint32_t whole32[0];
  uint16_t keys[4];
} ConsumerReport;

typedef struct
{
  uint8_t button;
  uint8_t x;
  uint8_t y;
  uint8_t wheel;
} MouseReport;

MouseReport mouse;
KeyReport report;
ConsumerReport conReport;

void setup() {
  Wire.begin(4);
  Wire.onReceive(receiveEvent);

  initialiseHID_IDs();

  for (int i = 0; i < rows; i++) {
    pinMode(rowPins[i], OUTPUT);

    digitalWrite(rowPins[i], HIGH);
  }
  for (int i = 0; i < cols; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }
  memmove( keebLayout, alphaLayer, sizeof(keebLayout) );
  memmove( prevLayout, alphaLayer, sizeof(keebLayout) );
  
}

void loop() {
  for (int i = 0; i < rows; i++) {
    digitalWrite(rowPins[i], LOW);
    delay(1);
    for (int j = 0; j < cols; j++) {
      currScan[i][j] = digitalRead(colPins[j]);
    }
    digitalWrite(rowPins[i], HIGH);

  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols + extraCols; j++) {
      if (currScan[i][j] != prevScan[i][j]) {
        if (keebLayout[i][j] >= HOLD_LAYER_0 && keebLayout[i][j] <= HOLD_LAYER_6 ) { //check here for keys that will change the layer while HELD
          if (currScan[i][j] == 0) {
            memmove(prevLayout, keebLayout, sizeof(keebLayout));
            if (keebLayout[i][j] == HOLD_LAYER_0) {
              memmove(keebLayout, alphaLayer, sizeof(keebLayout));
            }
            else if ( keebLayout[i][j] == HOLD_LAYER_1) {
              memmove(keebLayout, symbolLayer, sizeof(keebLayout));
            }
            else if (keebLayout[i][j] == HOLD_LAYER_2) {
              memmove(keebLayout, numLayer, sizeof(keebLayout));
            }
            else if (keebLayout[i][j] == HOLD_LAYER_3) {
              memmove(keebLayout, mouseLayer, sizeof(keebLayout));
            }
            else if (keebLayout[i][j] == HOLD_LAYER_4) {
              memmove(keebLayout, gameLayer, sizeof(keebLayout));
            }
            releaseAllKeys();
          }
          else {
            memmove(keebLayout, prevLayout, sizeof(keebLayout));
            releaseAllKeys();
          }
        }
        else if (keebLayout[i][j] >= TOGGLE_LAYER_0 && keebLayout[i][j] <= TOGGLE_LAYER_6 ) { //check here for keys that will TOGGLE the layer
          if (currScan[i][j] == 0) {
            if (keebLayout[i][j] == TOGGLE_LAYER_0) {
              memmove(keebLayout, alphaLayer, sizeof(keebLayout));
            }
            else if ( keebLayout[i][j] == TOGGLE_LAYER_1) {
              memmove(keebLayout, symbolLayer, sizeof(keebLayout));
            }
            else if (keebLayout[i][j] == TOGGLE_LAYER_2) {
              memmove(keebLayout, numLayer, sizeof(keebLayout));
            }
            else if (keebLayout[i][j] == TOGGLE_LAYER_3) {
              memmove(keebLayout, mouseLayer, sizeof(keebLayout));
            }
            else if (keebLayout[i][j] == TOGGLE_LAYER_4) {
              memmove(keebLayout, gameLayer, sizeof(keebLayout));
            }
            //should not switch back on release of other layer key
            memmove(prevLayout, keebLayout, sizeof(keebLayout));
            releaseAllKeys();
          }
        }
        else if (keebLayout[i][j] > BEGIN_MEDIA && keebLayout[i][i] < END_MEDIA) {
          if (currScan[i][j] == 0) {
            pressKeyConsumer(keebLayout[i][j]);
          }
          else {
            releaseKeyConsumer(keebLayout[i][j]);
          }
        }
        else if (keebLayout[1][3] == mouseLayer[1][3]) {
          if (currScan[i][j] == 0) {
            switch (keebLayout[i][j]) {
              case 1:
                mouseClick(1);
                break;
              case 2:
                mouseClick(2);
                break;
              case 3:
                mouseDown = false;
                mouseUp = true;
                break;
              case 4:
                mouseUp = false;
                mouseDown = true;
                break;
              case 5:
                mouseRight = false;
                mouseLeft = true;
                break;
              case 6:
                mouseLeft = false;
                mouseRight = true;
                break;
              case 7:
                mouseScrollDown = false;
                mouseScrollUp = true;
                break;
              case 8:
                mouseScrollUp = false;
                mouseScrollDown = true;
                break;
              case 11:
                mouseClick(8);
                break;
              case 12:
                mouseClick(16);
                break;
            }
          }
          else {
            switch (keebLayout[i][j]) {
              case 1:
                mouseUnClick(1);
                break;
              case 2:
                mouseUnClick(2);
                break;
              case 3:
                mouseUp = false;
                break;
              case 4:
                mouseDown = false;
                break;
              case 5:
                mouseLeft = false;
                break;
              case 6:
                mouseRight = false;
                break;
              case 7:
                mouseScrollUp = false;
                break;
              case 8:
                mouseScrollDown = false;
                break;
              case 11:
                mouseUnClick(8);
                break;
              case 12:
                mouseUnClick(16);
                break;
            }
          }
        }
        else if (currScan[i][j] == 0) {
          pressKey(keebLayout[i][j]);
        }
        else {
          releaseKey(keebLayout[i][j]);
        }
        prevScan[i][j] = currScan[i][j];
      }
    }
  }
  MouseLoop();
}





void sendReport(KeyReport *keys)
{
  HID().SendReport(1, keys, sizeof(KeyReport));
}

void pressKey(uint16_t key) {
  if (key > 0xf000) {
    key = key - 0xf000;
  }
  if (key >= 0xff) {
    key = key - 0xf00;
    pressKey(0x81);
    delay(10);
    pressKey(key);
    delay(5);
    releaseKey(key);
    delay(5);
    releaseKey(0x81);
    delay(5);
  }
  else if (key >= 0x80) {
    key ^= 0x80;
    key = 1 << key;
    report.modifiers |= key;
  }
  else {
    for (int z = 0; z < 6; z++) {
      if (report.keys[z] == 0x00) {
        report.keys[z] = key;
        break;
      }
    }
  }
  sendReport(&report);
}

void releaseKey(uint16_t key) {
  if (key > 0xf000) {
    key = key - 0xf000;
  }
  if (key >= 0xf00) {
    
  }
  else if (key >= 0x80) {
    key ^= 0x80;
    key = 1 << key;
    report.modifiers ^= key;
  }
  else {
    for (int z = 0; z < 6; z++) {
      if (report.keys[z] == key) {
        report.keys[z] = 0x00;
        break;
      }
    }
  }
  sendReport(&report);
}

void pressKeyConsumer(uint16_t key) {
  for (int z = 0; z < 4; z++) {
    if (conReport.keys[z] == 0x0000) {
      conReport.keys[z] = key;
      break;
    }
  }

  sendReportConsumer(&conReport);
}

void releaseKeyConsumer(uint16_t key) {
  for (int z = 0; z < 4; z++) {
    if (conReport.keys[z] == key) {
      conReport.keys[z] = 0x00;
      break;
    }
  }
  sendReportConsumer(&conReport);
}

void sendReportConsumer(ConsumerReport* keys)
{
  HID().SendReport(2, keys, sizeof(ConsumerReport));
}

void releaseAllKeys() {
  for (int i = i; i < 4; i++) {
    conReport.keys[i] = 0x0;
  }
  for (int i = i; i < 6; i++) {
    report.keys[i] = 0x0;
  }
  report.modifiers = 0x00;
  mouse.x = 0;
  mouse.y = 0;
  mouse.wheel = 0;
  mouse.button = 0;
  mouseUp = false;
  mouseDown = false;
  mouseLeft = false;
  mouseRight = false;
  mouseScrollUp = false;
  mouseScrollDown = false;

  sendReportMouse();
  sendReportConsumer(&conReport);
  sendReport(&report);
}

void MouseLoop() {
  if (millis() - lastMouseMove > 5 && keebLayout[1][3] == mouseLayer[1][3]) {
    mouseMove();
    lastMouseMove = millis();
  }
}

void sendReportMouse()
{
  HID().SendReport(3, &mouse, sizeof(MouseReport));
}

void mouseClick(uint8_t b) {
  mouse.button |= b;
  mouse.x = 0;
  mouse.y = 0;
  mouse.wheel = 0;
  sendReportMouse();
}
void mouseUnClick(uint8_t b) {
  mouse.button ^= b;
  mouse.x = 0;
  mouse.y = 0;
  mouse.wheel = 0;
  sendReportMouse();
}
void mouseMove() {
  mouse.x = 0;
  mouse.y = 0;
  mouse.wheel = 0;
  if (mouseLeft)mouse.x = -10;
  if (mouseRight)mouse.x = 10;
  if (mouseUp)mouse.y = -10;
  if (mouseDown)mouse.y = 10;
  if (mouseScrollUp)mouse.wheel = 1;
  if (mouseScrollDown)mouse.wheel = -1;
  sendReportMouse();
}

void receiveEvent(int fuckoff)
{
  int col, row, set;
  row = Wire.read();
  col = Wire.read();
  col += cols;
  set = Wire.read();
  currScan[row][col] = set;
}

void initialiseHID_IDs()
{
  static const uint8_t _hidReportDescriptor[] PROGMEM = {

    //  Keyboard
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)  // 47
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x85, 0x01,                    //   REPORT_ID (1)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)

    0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)

    0x95, 0x08,                    //   REPORT_COUNT (8)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)

    0x95, 0x06,                    //   REPORT_COUNT (6)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x73,                    //   LOGICAL_MAXIMUM (115)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)

    0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x73,                    //   USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    0xc0,
  };
  static const uint8_t _hidReportDescriptorConsumer[] PROGMEM = {

    //  Keyboard
    0x05, 0x0C,                  /* usage page (consumer device) */
    0x09, 0x01,                 /* usage -- consumer control */
    0xA1, 0x01,                 /* collection (application) */
    0x85, 0x02,     /* report id */
    /* 4 Media Keys */
    0x15, 0x00,                 /* logical minimum */
    0x26, 0xFF, 0x03,               /* logical maximum (3ff) */
    0x19, 0x00,                 /* usage minimum (0) */
    0x2A, 0xFF, 0x03,               /* usage maximum (3ff) */
    0x95, 0x04,                 /* report count (4) */
    0x75, 0x10,                 /* report size (16) */
    0x81, 0x00,                 /* input */
    0xC0 /* end collection */
  };

  static const uint8_t _hidReportDescriptorMouse[] PROGMEM = {

    //  Mouse
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)  // 54
    0x09, 0x02,                    // USAGE (Mouse)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x09, 0x01,                    //   USAGE (Pointer)
    0xa1, 0x00,                    //   COLLECTION (Physical)
    0x85, 0x03,                    //     REPORT_ID (1)
    0x05, 0x09,                    //     USAGE_PAGE (Button)
    0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
    0x29, 0x03,                    //     USAGE_MAXIMUM (Button 3)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    0x95, 0x03,                    //     REPORT_COUNT (3)
    0x75, 0x01,                    //     REPORT_SIZE (1)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x75, 0x05,                    //     REPORT_SIZE (5)
    0x81, 0x03,                    //     INPUT (Cnst,Var,Abs)
    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,                    //     USAGE (X)
    0x09, 0x31,                    //     USAGE (Y)
    0x09, 0x38,                    //     USAGE (Wheel)
    0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
    0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x03,                    //     REPORT_COUNT (3)
    0x81, 0x06,                    //     INPUT (Data,Var,Rel)
    0xc0,                          //   END_COLLECTION
    0xc0,                          // END_COLLECTION
  };

  static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
  HID().AppendDescriptor(&node);
  static HIDSubDescriptor node2(_hidReportDescriptorConsumer, sizeof(_hidReportDescriptorConsumer));
  HID().AppendDescriptor(&node2);
  static HIDSubDescriptor node3(_hidReportDescriptorMouse, sizeof(_hidReportDescriptorMouse));
  HID().AppendDescriptor(&node3);

}
