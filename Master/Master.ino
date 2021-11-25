#include <HID.h>
#include <Wire.h>

#define rows 5
#define cols 6
#define extraCols 6

int rowPins[rows] = {15, 14, 16, 10, 5};
int colPins[cols] = {A2, A1, 9, 8,7,6};

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

uint16_t alphaLayer[rows][cols + extraCols] = {{0x29, 0x35, 0xea, 0xe2, 0xe9, 0x3b, 0x3e, 0xb6, 0xcd, 0xb5, 0x46, 0x4c},
                                                {0x2b, 0x14, 0x1a, 0x08, 0x15, 0x17, 0x1c, 0x18, 0x0c, 0x12, 0x13, 0x31},
                                                {0x82, 0x04, 0x16, 0x07, 0x09, 0x0a, 0x0b, 0x0d, 0x0e, 0x0f, 0x33, 0x34},
                                                {0x80, 0x1d, 0x1b, 0x06, 0x19, 0x05, 0x11, 0x10, 0x36, 0x37, 0x38, 0xf3},
                                                {0x00, 0x00, 0x83, 0x2a, 0x81, 0xf1, 0xf2, 0x2c, 0x28, 0x86, 0x00, 0x00}
};

uint16_t symbolLayer[rows][cols + extraCols] = {{0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45},
                                                {0xf4, 0xf01e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x2a},
                                                {0x2b, 0xf36, 0xf37, 0xf2f, 0xf30, 0xf1f, 0xf21, 0xf26, 0xf27, 0xf33, 0x33, 0xf23},
                                                {0x80, 0x38, 0xf2d, 0xf02f, 0x30, 0xf20, 0x2d, 0xf24, 0xf31, 0xf2e, 0xf25, 0xf22},
                                                {0x0, 0x0, 0x83, 0x2a, 0x81, 0xf0, 0xf2, 0x2c, 0x28, 0x86, 0x0, 0x0}
};

uint16_t numLayer[rows][cols + extraCols] = {{0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x53, 0x00, 0x00, 0x4c},
                                            {0x00, 0x4b, 0xf26, 0x52, 0x27, 0x4a, 0x54, 0x5f, 0x60, 0x61, 0x56, 0x00},
                                            {0x2b, 0x4e, 0x50, 0x51, 0x4f, 0x4d, 0x62, 0x5c, 0x5d, 0x5e, 0x57, 0x2e},
                                            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x59, 0x5a, 0x5b, 0x37, 0x00},
                                            {0x0, 0x0, 0x83, 0x2a, 0x81, 0xf1, 0xf0, 0x2c, 0x28, 0x86, 0x0, 0x0}
};

uint16_t mouseLayer[rows][cols + extraCols] = {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
                                                {0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00},
                                                {0x00, 0x00, 0x05, 0x04, 0x06, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00},
                                                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0},
                                                {0x00, 0x00, 0x00, 0x0b, 0x01, 0xf1, 0xf2, 0x02, 0x0c, 0x00, 0x00, 0x00}
};

uint16_t gameLayer[rows][cols + extraCols] = {{0x29, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0xea, 0xe2, 0xe9, 0xb6, 0xcd, 0xb5},
                                              {0x2b, 0x14, 0x1a, 0x08, 0x15, 0x17, 0x1c, 0x18, 0x0c, 0x12, 0x13, 0x43},
                                              {0x82, 0x04, 0x16, 0x07, 0x09, 0x0a, 0x0b, 0x0d, 0x0e, 0x0f, 0x33, 0x34},
                                              {0x80, 0x1d, 0x1b, 0x06, 0x19, 0x05, 0x11, 0x10, 0x36, 0x37, 0x38, 0xf3},
                                              {0x00, 0x00, 0x83, 0x2c, 0x81, 0xf0, 0xf2, 0x2a, 0x28, 0x86, 0x00, 0x00}
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
        if (keebLayout[i][j] >= 0xf0 && keebLayout[i][j] <= 0xff ) { //check here for keys that will change the layer
          if(currScan[i][j] == 0){
            memmove(prevLayout, keebLayout, sizeof(keebLayout));
            if (keebLayout[i][j] == 0xf0) {
              memmove(keebLayout, alphaLayer, sizeof(keebLayout));
            }
            else if ( keebLayout[i][j] == 0xf1) {
              memmove(keebLayout, symbolLayer, sizeof(keebLayout));
            }
            else if (keebLayout[i][j] == 0xf2) {
              memmove(keebLayout, numLayer, sizeof(keebLayout));
            }
            else if (keebLayout[i][j] == 0xf3) {
              memmove(keebLayout, mouseLayer, sizeof(keebLayout));
            }
            else if (keebLayout[i][j] == 0xf4) {    
              memmove(keebLayout, gameLayer, sizeof(keebLayout));
            }
            releaseAllKeys();
          }
          else{ 
            if (keebLayout[0][1] != gameLayer[0][1] && keebLayout[0][1] != alphaLayer[0][1]) {
              memmove(keebLayout, alphaLayer, sizeof(keebLayout));
            }
            releaseAllKeys();
          }
        }
        else if (keebLayout[i][j] > 0x88 && keebLayout[i][i] < 0xf0) {
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
    pressKey(key);
    releaseKey(key);
    releaseKey(0x81);
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
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols + extraCols; j++) {
      //prevScan[i][j] = 1;
    }
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
