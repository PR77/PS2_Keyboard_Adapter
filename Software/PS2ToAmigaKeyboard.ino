#include <Arduino.h>
#include <PS2KeyAdvanced.h>

// --- Local Defines

#define KEYFLAGS_CTRL         0x01
#define KEYFLAGS_LEFT_AMIGA   0x02
#define KEYFLAGS_RIGHT_AMIGA  0x04
#define KEYFLAGS_KEY_RELEASED 0x80

// --- Local Constants / PIN Configurations

const int PS2DataPin = 0;
const int PS2IRQpin =  2;
const int AmigaDataPin = 3;
const int AmigaClkPin = 4;
const int AmigaResetPin = 1;

unsigned char translationTable[255];

// --- Prototypes

void amigaKeyboardWrite(uint8_t value, bool pressed);
void setupTranslationTable(void);

// --- Objects

PS2KeyAdvanced keyboard;

// --- Functions

void setupTranslationTable(void)
{
  for (uint8_t i = 0; i < 255; i++) {
    translationTable[i] = 0xff;  
  }
  
  translationTable[PS2_KEY_PAUSE] = 0x5f;
  translationTable[PS2_KEY_L_SHIFT] = 0x60;
  translationTable[PS2_KEY_R_SHIFT] = 0x61;
  translationTable[PS2_KEY_L_CTRL] = 0x63;
  translationTable[PS2_KEY_R_CTRL] = 0x63;
  translationTable[PS2_KEY_L_ALT] = 0x64;
  translationTable[PS2_KEY_R_ALT] = 0x65;
  translationTable[PS2_KEY_L_GUI] = 0x66;
  translationTable[PS2_KEY_R_GUI] = 0x67;
  
  translationTable[PS2_KEY_L_ARROW] = 0x4f;
  translationTable[PS2_KEY_R_ARROW] = 0x4e;
  translationTable[PS2_KEY_UP_ARROW] = 0x4c;
  translationTable[PS2_KEY_DN_ARROW] = 0x4d;

  translationTable[PS2_KEY_DELETE] = 0x46;
  
  translationTable[PS2_KEY_ESC] = 0x45;
  translationTable[PS2_KEY_BS] = 0x41;
  translationTable[PS2_KEY_TAB] = 0x42;
  translationTable[PS2_KEY_ENTER] = 0x44;
  translationTable[PS2_KEY_SPACE] = 0x40;
  
  translationTable[PS2_KEY_KP0] = 0x0f;
  translationTable[PS2_KEY_KP1] = 0x1d;
  translationTable[PS2_KEY_KP2] = 0x1e;
  translationTable[PS2_KEY_KP3] = 0x1f;
  translationTable[PS2_KEY_KP4] = 0x2d;
  translationTable[PS2_KEY_KP5] = 0x2e;
  translationTable[PS2_KEY_KP6] = 0x2f;
  translationTable[PS2_KEY_KP7] = 0x3d;
  translationTable[PS2_KEY_KP8] = 0x3e;
  translationTable[PS2_KEY_KP9] = 0x3f;
  translationTable[PS2_KEY_KP_DOT] = 0x3c;
  translationTable[PS2_KEY_KP_ENTER] = 0x43;
  translationTable[PS2_KEY_KP_PLUS] = 0x5e;
  translationTable[PS2_KEY_KP_MINUS] = 0x4a;
  translationTable[PS2_KEY_KP_TIMES] = 0x5d;
  translationTable[PS2_KEY_KP_DIV] = 0x5c;
  
  translationTable[PS2_KEY_0] = 0x0a;
  translationTable[PS2_KEY_1] = 0x01;
  translationTable[PS2_KEY_2] = 0x02;
  translationTable[PS2_KEY_3] = 0x03;
  translationTable[PS2_KEY_4] = 0x04;
  translationTable[PS2_KEY_5] = 0x05;
  translationTable[PS2_KEY_6] = 0x06;
  translationTable[PS2_KEY_7] = 0x07;
  translationTable[PS2_KEY_8] = 0x08;
  translationTable[PS2_KEY_9] = 0x09;
  
  translationTable[PS2_KEY_APOS] = 0x2a;
  translationTable[PS2_KEY_COMMA] = 0x38;
  translationTable[PS2_KEY_MINUS] = 0x0b;
  translationTable[PS2_KEY_DOT] = 0x39;
  translationTable[PS2_KEY_DIV] = 0x3a;
  
  translationTable[PS2_KEY_SINGLE] = 0x00;
  
  translationTable[PS2_KEY_A] = 0x20;
  translationTable[PS2_KEY_B] = 0x35;
  translationTable[PS2_KEY_C] = 0x33;
  translationTable[PS2_KEY_D] = 0x22;
  translationTable[PS2_KEY_E] = 0x12;
  translationTable[PS2_KEY_F] = 0x23;
  translationTable[PS2_KEY_G] = 0x24;
  translationTable[PS2_KEY_H] = 0x25;
  translationTable[PS2_KEY_I] = 0x17;
  translationTable[PS2_KEY_J] = 0x26;
  translationTable[PS2_KEY_K] = 0x27;
  translationTable[PS2_KEY_L] = 0x28;
  translationTable[PS2_KEY_M] = 0x37;
  translationTable[PS2_KEY_N] = 0x36;
  translationTable[PS2_KEY_O] = 0x18;
  translationTable[PS2_KEY_P] = 0x19;
  translationTable[PS2_KEY_Q] = 0x10;
  translationTable[PS2_KEY_R] = 0x13;
  translationTable[PS2_KEY_S] = 0x21;
  translationTable[PS2_KEY_T] = 0x14;
  translationTable[PS2_KEY_U] = 0x16;
  translationTable[PS2_KEY_V] = 0x34;
  translationTable[PS2_KEY_W] = 0x11;
  translationTable[PS2_KEY_X] = 0x32;
  translationTable[PS2_KEY_Y] = 0x15;
  translationTable[PS2_KEY_Z] = 0x31;
  
  translationTable[PS2_KEY_SEMI] = 0x29;
  translationTable[PS2_KEY_BACK] = 0x2b;
  translationTable[PS2_KEY_OPEN_SQ] = 0x1a;
  translationTable[PS2_KEY_CLOSE_SQ] = 0x1b;
  translationTable[PS2_KEY_EQUAL] = 0x0c;
  translationTable[PS2_KEY_KP_COMMA] = 0x38;

  translationTable[PS2_KEY_F1] = 0x50;
  translationTable[PS2_KEY_F2] = 0x51;
  translationTable[PS2_KEY_F3] = 0x52;
  translationTable[PS2_KEY_F4] = 0x53;
  translationTable[PS2_KEY_F5] = 0x54;
  translationTable[PS2_KEY_F6] = 0x55;
  translationTable[PS2_KEY_F7] = 0x56;
  translationTable[PS2_KEY_F8] = 0x57;
  translationTable[PS2_KEY_F9] = 0x58;
  translationTable[PS2_KEY_F10] = 0x59;
}

void amigaKeyboardWrite(uint8_t value, bool pressed)
{ 
  //      _____   ___   ___   ___   ___   ___   ___   ___   _________
  // KCLK      \_/   \_/   \_/   \_/   \_/   \_/   \_/   \_/
  //      ___________________________________________________________
  // KDAT    \_____X_____X_____X_____X_____X_____X_____X_____/
  //           (6)   (5)   (4)   (3)   (2)   (1)   (0)   (7)
  //
  //          First                                     Last
  //          sent                                      sent
  
  uint8_t z = 0x80; 
  uint8_t result = (value << 1);
  
  result |= (pressed == true) ? 0x00 : 0x01; 
  
  digitalWrite(AmigaDataPin, HIGH);
  pinMode(AmigaDataPin, OUTPUT);
  digitalWrite(AmigaClkPin, HIGH);
  
  for (uint8_t i = 0; i < 8; i++)
  {
    if (!(result & z))
      digitalWrite(AmigaDataPin, HIGH);
    else
      digitalWrite(AmigaDataPin, LOW); 
    
    delayMicroseconds(20);
    digitalWrite(AmigaClkPin, LOW);
    delayMicroseconds(20);
    digitalWrite(AmigaClkPin, HIGH);
    delayMicroseconds(20) ;
    
    z = z >> 1 ;
  }
  
  pinMode(AmigaDataPin, INPUT);
  digitalWrite(AmigaClkPin, HIGH);
  
  delayMicroseconds(200);
}

// --- Setup

void setup()
{
  keyboard.begin(PS2DataPin, PS2IRQpin);
  keyboard.setNoBreak(0);

  pinMode(AmigaDataPin, OUTPUT);
  pinMode(AmigaClkPin, OUTPUT);
  pinMode(AmigaResetPin, OUTPUT);
  digitalWrite(AmigaDataPin, HIGH);
  digitalWrite(AmigaClkPin, HIGH);
  digitalWrite(AmigaResetPin, LOW);

  setupTranslationTable();
}

// --- Loop

void loop()
{
  static uint8_t keyFlags = 0;
  
  if (keyboard.available())
  {
    uint16_t c = keyboard.read();

    if (c)
    {
      if (PS2_BREAK == (c & PS2_BREAK))
        keyFlags |= KEYFLAGS_KEY_RELEASED;
      else
        keyFlags &= ~KEYFLAGS_KEY_RELEASED;
      
      if (PS2_KEY_L_CTRL == (c & 0xff))
      {
        if (KEYFLAGS_KEY_RELEASED != ((keyFlags & KEYFLAGS_KEY_RELEASED)))
          keyFlags |= KEYFLAGS_CTRL;
        else
          keyFlags &= ~KEYFLAGS_CTRL;
      }

      if (PS2_KEY_L_GUI == (c & 0xff))
      {
        if (KEYFLAGS_KEY_RELEASED != ((keyFlags & KEYFLAGS_KEY_RELEASED)))
          keyFlags |= KEYFLAGS_LEFT_AMIGA;
        else
          keyFlags &= ~KEYFLAGS_LEFT_AMIGA;
      }

      if (PS2_KEY_R_GUI == (c & 0xff))
      {
        if (KEYFLAGS_KEY_RELEASED != ((keyFlags & KEYFLAGS_KEY_RELEASED)))
          keyFlags |= KEYFLAGS_RIGHT_AMIGA;
        else
          keyFlags &= ~KEYFLAGS_RIGHT_AMIGA;
      }

      if ((KEYFLAGS_CTRL | KEYFLAGS_LEFT_AMIGA | KEYFLAGS_RIGHT_AMIGA) == (keyFlags & (KEYFLAGS_CTRL | KEYFLAGS_LEFT_AMIGA | KEYFLAGS_RIGHT_AMIGA)))
        digitalWrite(AmigaResetPin, HIGH);
      else
        digitalWrite(AmigaResetPin, LOW);

      amigaKeyboardWrite(translationTable[c & 0xff], (keyFlags & KEYFLAGS_KEY_RELEASED) ? false : true);
    }
  }
}
