# BasicKeyboard (BK or burger king)
This project was inspired by my inability to get QMK's custom matrix scan working. So, I made a simple version that uses only Arduino-based libraries. 

# How is it structured?
As of right now, there are 4 major files:
1. src/main.cpp: This is where the majority of the keyboard functions live
2. src/Keymap.h: This is where you define your keymaps, layers, and analog cutoffs 
3. lib/Key/Key.h: This is where additional keycodes live
4. lib/Key/Key.cpp: This is where the constructors of the different key types live

# Different types of keys
1. Key: a normal key
2. Layer Key: a hold to press layer key
3. Special Key: do whatever you want key

# Note:
I know most of us are probably developing our personal implementations for our keyboards. I just wanted to document my interpretation so that others can see and fit it to their needs.

# Debug
Here is what a debug log looks like:
```
Microseconds: 346
Hz: 2890.00
Current Layer: 0
Post Matrix Scan:
   0    0    0    0    0    0    0    0    0    0    0    0
   0    0    0    0    0    0    0    0    0    0    0    0
   0    0    0    0    0    0    0    0    0    0    0    0
   0    0    0    0    0    0    0    0    0    0    0    0
Debounce Matrix:
   0    0    0    0    0    0    0    0    0    0    0    0
   0    0    0    0    0    0    0    0    0    0    0    0
   0    0    0    0    0    0    0    0    0    0    0    0
   0    0    0    0    0    0    0    0    0    0    0    0
Raw Analog:
  75   72   49   48   21   24   18   23   19   63   25   26
  24   26   27   40   70   92  150  136   77   79   94   87
  43   47   30   34   24   30   28   46   23   33   18   26
  11   20   13   21    7   16    9   18   15   23   25   46
```
It prints out:
1. Microsecond time it took for that loop
2. Hz (calculated from the microsecond count)
3. Current layer (int)
4. Post Matrix (boolean)
5. Debounce Matrix (int)
6. Raw Analog Matrix (int) 
