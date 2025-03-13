﻿# BasicKeyboard
Still in progress.

Maybe check back in a week or two.

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