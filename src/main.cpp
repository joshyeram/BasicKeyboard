#include <Arduino.h>
#include <Keymap.h>
#include "Keyboard.h"

boolean* prevMatrix;
unsigned int* debounceLast;
int* rawAnalog;

int currentLayer;

boolean* scanHandler();
void debounceHandler(boolean* prev , boolean* curr);
void keyPressHandler(boolean* prev , boolean* curr);
void layerHandler(boolean* prev , boolean* curr);
void printMatrix(boolean* matrix);
void printMatrix(int* matrix);

void setup() 
{
  // put your setup code here, to run once:
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  pinMode(D9, OUTPUT);
  pinMode(D10, OUTPUT);

  pinMode(A0, INPUT_PULLDOWN);
  pinMode(A1, INPUT_PULLDOWN);
  pinMode(A2, INPUT_PULLDOWN);

  Serial.begin(19200);
  Keyboard.begin();
  Keyboard.releaseAll();

  prevMatrix = new boolean[48];
  debounceLast = new unsigned int[48];
  rawAnalog = new int[48];
  currentLayer = DEF;
}

void loop() 
{
  unsigned long startTime = micros();
  for(int key = 0; key < 16; key++)
  {
    digitalWrite(D10, bitRead(key,0));
    digitalWrite(D9, bitRead(key,1));
    digitalWrite(D7, bitRead(key,2));
    digitalWrite(D8, bitRead(key,3));

    rawAnalog[key]      = analogRead(A0);
    rawAnalog[key + 16] = analogRead(A1);
    rawAnalog[key + 32] = analogRead(A2);
  }

  boolean* currMatrix = scanHandler();

  debounceHandler(prevMatrix, currMatrix);

  layerHandler(prevMatrix, currMatrix); 
  
  keyPressHandler(prevMatrix , currMatrix);

  delete prevMatrix;
  prevMatrix = currMatrix;

  // unsigned long end = micros() - startTime;
  // double hertz = 1000000/end;
  // Serial.println(end);
  // Serial.println(hertz);

  // printMatrix(currMatrix);
  // printMatrix(rawAnalog);
  // //Serial.println(currentLayer);

  // delay(1000);
}

boolean* scanHandler()
{
  boolean* currMatrix = new boolean[48];

  for(int i = 0; i < 48; i++)
  {
    if (rawAnalog[i] > analogCutoffs[i])
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
  for(int i = 0; i < 48; i++)
  {
    if(prev[i])
    {
      debounceLast[i]++;
    }
    if(prev[i] && !curr[i])
    {
      if(debounceLast[i] > 8)
      {
        debounceLast[i] = 0;
      }
      else
      {
        curr[i] = true;
      }
    }
  }
}

void layerHandler(boolean *prev, boolean *curr)
{
  for(int key = 0; key < 48; key++)
  { 
    if(!layers[currentLayer][key].isLayer || layers[currentLayer][key].keyCode == 0)
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
  for(int key = 0; key < 48; key++)
  {
    if(layers[currentLayer][key].isLayer || layers[currentLayer][key].keyCode == 0)
    {
      continue;
    }
    if(!prev[key] && curr[key])
    {
      //char str2[] = "Pressed: ";
      //Serial.print(str2);
      //Serial.println(layers[currentLayer][key].keyCode);
      Keyboard.press(layers[currentLayer][key].keyCode);
    }
    else if(prev[key] && !curr[key])
    {
     // char str3[] = "Released: ";
      //Serial.print(str3);
      //.println(layers[currentLayer][key].keyCode);
      Keyboard.release(layers[currentLayer][key].keyCode);
      debounceLast[key] = 0;
    }
    else if((prev[key] && curr[key]) || (!prev[key] && !curr[key]))
    {
      continue;
    }
  }
}

void printMatrix(boolean* matrix)
{
  for(int i = 0; i < 48; i++)
  {
    Serial.print(matrix[i]);
    if((i + 1) % 12 == 0)
    {
      Serial.println(' ');
    }
    else
    {
      Serial.print(' ');
    }
  }
}

void printMatrix(int* matrix)
{
  for(int i = 0; i < 48; i++)
  {
    Serial.print(matrix[i]);
    if((i + 1) % 12 == 0)
    {
      Serial.println(' ');
    }
    else
    {
      Serial.print(' ');
    }
  }
}

