#include <Arduino.h>
#include <Keymap.h>
#include "Keyboard.h"

#define DEBOUNCE 12
#define KEY_COUNT 48
#define DEBUG true
#define DEBUG_STOP_PRESSES false

boolean* prevMatrix;
int* debounceLast;
int* rawAnalog;
int currentLayer;

boolean* scanHandler();
void debounceHandler(boolean* prev , boolean* curr);
void layerHandler(boolean* prev , boolean* curr);
void keyPressHandler(boolean* prev , boolean* curr);
void specialKeyHandler(int keycode);

void clearMatrix(boolean* matrix);
void clearMatrix(int* matrix);
void printMatrix(boolean* matrix);
void printMatrix(int* matrix);

void setup() 
{
  pinMode(D7, OUTPUT); // Selector Pins
  pinMode(D8, OUTPUT);
  pinMode(D9, OUTPUT);
  pinMode(D10, OUTPUT);

  pinMode(A0, INPUT_PULLDOWN); // Read Pins pulled down
  pinMode(A1, INPUT_PULLDOWN); // Seeed operates at 3.3
  pinMode(A2, INPUT_PULLDOWN);

  randomSeed(analogRead(A3));  // Set up random usage
  pinMode(A3, INPUT_PULLDOWN); // Unused analog pin

  if(DEBUG)
  {
    Serial.begin(19200);
  }

  Keyboard.begin();      // Init keyboard essentials
  Keyboard.releaseAll(); // Clear all just in case

  prevMatrix = new boolean[KEY_COUNT]; // Init keyboard essentials
  debounceLast = new int[KEY_COUNT];
  rawAnalog = new int[KEY_COUNT];
  currentLayer = DEF;

  clearMatrix(prevMatrix);
  clearMatrix(debounceLast);
  clearMatrix(rawAnalog);
}

void loop() 
{
  unsigned long startTime = micros();       // Start microsecond timer only used for debug

  boolean* currMatrix = scanHandler();      // 1. Scan matrix

  debounceHandler(prevMatrix, currMatrix);  // 2. Process debounce keys for pressed keys

  layerHandler(prevMatrix, currMatrix);     // 3. Shift layers
  
  keyPressHandler(prevMatrix , currMatrix); // 4. Process keys

  delete prevMatrix;                        // Make previous boolean matrix current and loop
  prevMatrix = currMatrix;

  if(DEBUG)
  {
    unsigned long end = micros() - startTime;
    double hertz = 1000000/end;
    Serial.print("Microseconds: ");
    Serial.println(end);
    Serial.print("Hz: ");
    Serial.println(hertz);
    Serial.print("Current Layer: ");
    Serial.println(currentLayer);
    Serial.println("Post Matrix Scan:");
    printMatrix(currMatrix);
    Serial.println("Debounce Matrix:");
    printMatrix(debounceLast);
    Serial.println("Raw Analog:");
    printMatrix(rawAnalog);
    Serial.println();
    delay(1000);
  }
}

boolean* scanHandler()
{
  for(int key = 0; key < 16; key++)
  {
    digitalWrite(D10, bitRead(key,0)); // Set selector pins
    digitalWrite(D9, bitRead(key,1));
    digitalWrite(D7, bitRead(key,2));
    digitalWrite(D8, bitRead(key,3));

    rawAnalog[key]      = analogRead(A0); // Read values from switches
    rawAnalog[key + 16] = analogRead(A1);
    rawAnalog[key + 32] = analogRead(A2);
  }

  boolean* currMatrix = new boolean[KEY_COUNT];

  for(int i = 0; i < KEY_COUNT; i++)
  {
    if (rawAnalog[i] > analogCutoffs[i]) // Insert HE switch logic/SOCD logic here
    { 
      currMatrix[i] = true;
    }
    else
    {
      currMatrix[i] = false;
    }
  }
 return currMatrix;
}

void debounceHandler(boolean *prev, boolean *curr)
{
  for(int i = 0; i < KEY_COUNT; i++)
  {
    if(prev[i])
    {
      debounceLast[i]++;
    }
    if(prev[i] && !curr[i])
    {
      if(debounceLast[i] > DEBOUNCE) 
      {
        debounceLast[i] = 0;
      }
      else
      {
        curr[i] = true; // Hold the key until debounce is true
      }
    }
  }
}

void layerHandler(boolean *prev, boolean *curr)
{
  for(int key = 0; key < KEY_COUNT; key++)
  { 
    if(!layers[currentLayer][key].isLayer || layers[currentLayer][key].keyCode == 0) // Check to see if you need to process a layer key
    {
      continue;
    }
    
    if (!prev[key] && !curr[key])
    {
      // not pressed. do nothing
      continue;
    }
    else if (prev[key] && curr[key])
    {
      // continued press. do nothing
      continue;
    }
    else if (prev[key] && !curr[key])
    {
      // released layer
      // release all keys and go back down to default
      Keyboard.releaseAll();
      currentLayer = DEF;
    }
    else if(!prev[key] && curr[key])
    {
      // pressed layer
      // release all keys and go to layer
      Keyboard.releaseAll();
      currentLayer = layers[currentLayer][key].keyCode;
    }
  }
}

void keyPressHandler(boolean* prev , boolean* curr)
{
  for(int key = 0; key < KEY_COUNT; key++)
  {
    if(layers[currentLayer][key].isLayer || layers[currentLayer][key].keyCode == 0) // Check to see if you need to process this key
    {
      continue;
    }
    if(!prev[key] && curr[key])
    {
      if(DEBUG)
      {
        char str2[] = "Pressed: ";
        Serial.print(str2);
        Serial.println(layers[currentLayer][key].keyCode);
      }
      if(layers[currentLayer][key].isSpecial)
      {
        specialKeyHandler(layers[currentLayer][key].keyCode); // If this key is a Special key, do not let it go as a normal key
      }
      else if(!DEBUG_STOP_PRESSES)
      {
        Keyboard.press(layers[currentLayer][key].keyCode);
      }
    }
    else if(prev[key] && !curr[key])
    {
      if(DEBUG)
      {
        char str2[] = "Released: ";
        Serial.print(str2);
        Serial.println(layers[currentLayer][key].keyCode);
      }

      if(layers[currentLayer][key].isSpecial)
      {
        // skip
      }
      else if(!DEBUG_STOP_PRESSES)
      {
        Keyboard.release(layers[currentLayer][key].keyCode);
      }
      debounceLast[key] = 0;
    }
    else if((prev[key] && curr[key]) || (!prev[key] && !curr[key]))
    {
      continue; // We should only act if the key event state changes (on the loop that presses or releases and nothing in between)
    }
  }
}

void specialKeyHandler(int keyCode)
{
  // If you want special keys, you can implent new ones here
  double r = 0;
  switch(keyCode)
  {
    case RAN: // generate a random float between 0 (mayve inclusive?) and 1 (exclusive)
      r = random(1000000)/1000000.0;
      Keyboard.print(r,6);            
      break;
    case HTS: // flip a coin
      if(random(3) == 1)              
      {
        Keyboard.write('H');
      }
      else
      {
        Keyboard.write('T');
      }
      break;
  }
}

void clearMatrix(boolean* matrix)
{
  for(int i = 0; i < KEY_COUNT; i++)
  {
    matrix[i] = false;
  }
}

void clearMatrix(int* matrix)
{
  for(int i = 0; i < KEY_COUNT; i++)
  {
    matrix[i] = 0;
  }
}

void printMatrix(boolean* matrix)
{
  char buffer[4];
  for(int i = 0; i < KEY_COUNT; i++)
  {
    sprintf(buffer, "%4d ", matrix[i]);
    Serial.print(buffer);
    if((i + 1) % 12 == 0)
    {
      Serial.println();
    }
  }
}

void printMatrix(int* matrix)
{
  char buffer[4];
  for(int i = 0; i < KEY_COUNT; i++)
  {
    sprintf(buffer, "%4d ", matrix[i]);
    Serial.print(buffer);
    if((i + 1) % 12 == 0)
    {
      Serial.println();
    }
  }
}

