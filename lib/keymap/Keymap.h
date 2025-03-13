#include <Arduino.h>
#include "HID_Keyboard.h"
#include "Keyboard.h"
#include "Key.h"

// Layers
#define DEF   0x00 // done 
#define NUM   0x01 // done
#define SYM   0x02 // done
#define ARR   0x03 // done
#define FUN   0x04 // done
#define MOS   0x05

// Special Keys
#define RAN   0x01  
#define HTS   0x02

Key layers[][48] = {// Default
                    {Key(KEY_ESC),        Key(KEY_q),        Key(KEY_w),    Key(KEY_e),    Key(KEY_r),     Key(KEY_t),    Key(KEY_y),    Key(KEY_u),    Key(KEY_i),     Key(KEY_o),    Key(KEY_p),         Key(KEY_BACKSPACE),
                     Key(KEY_TAB),        Key(KEY_a),        Key(KEY_s),    Key(KEY_d),    Key(KEY_f),     Key(KEY_g),    Key(KEY_h),    Key(KEY_j),    Key(KEY_k),     Key(KEY_l),    Key(KEY_SMCOL),     Key(KEY_SQU),
                     Key(KEY_LEFT_SHIFT), Key(KEY_z),        Key(KEY_x),    Key(KEY_c),    Key(KEY_v),     Key(KEY_b),    Key(KEY_n),    Key(KEY_m),    Key(KEY_COM),   Key(KEY_DOT),  Key(KEY_FS),        Key(KEY_RIGHT_SHIFT),
                     Key(KEY_LEFT_CTRL),  Key(KEY_LEFT_ALT), Key(KEY_NONE), LayerKey(SYM), Key(KEY_SPACE), Key(KEY_NONE), LayerKey(MOS), LayerKey(ARR), LayerKey(NUM),  LayerKey(FUN), Key(KEY_RIGHT_GUI), Key(KEY_RETURN)},
                    
                    // NUM
                    {Key(KEY_ESC),        Key(KEY_1),        Key(KEY_2),    Key(KEY_3),    Key(KEY_4),     Key(KEY_5),    Key(KEY_6),    Key(KEY_7),    Key(KEY_8),     Key(KEY_9),    Key(KEY_0),         Key(KEY_BACKSPACE),
                     Key(KEY_NONE),       Key(KEY_NONE),     Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE),  Key(KEY_NONE), Key(KEY_NONE), Key(KEY_4),    Key(KEY_5),     Key(KEY_6),    Key(KEY_0),         Key(KEY_RETURN),
                     Key(KEY_LEFT_SHIFT), Key(KEY_NONE),     Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE),  Key(KEY_NONE), Key(KEY_NONE), Key(KEY_1),    Key(KEY_2),     Key(KEY_3),    Key(KEY_0),         Key(KEY_NONE),
                     Key(KEY_LEFT_CTRL),  Key(KEY_LEFT_ALT), Key(KEY_NONE), Key(KEY_NONE), Key(KEY_SPACE), Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE), LayerKey(NUM),  Key(KEY_NONE), Key(KEY_NONE),      Key(KEY_RETURN)},
                        
                    // SYM     
                    {Key(KEY_ESC),        Key(KEY_EX),       Key(KEY_AT),   Key(KEY_POUND),Key(KEY_DS),    Key(KEY_PER),  Key(KEY_EXP),  Key(KEY_PLUS), Key(KEY_MIN),   Key(KEY_LB),   Key(KEY_RB),        Key(KEY_DELETE),
                     Key(KEY_CAPS_LOCK),  Key(KEY_NONE),     Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE),  Key(KEY_NONE), Key(KEY_AST),  Key(KEY_EQ),   Key(KEY_UND),   Key(KEY_LP),   Key(KEY_RP),        Key(KEY_RETURN),
                     Key(KEY_LEFT_SHIFT), Key(KEY_NONE),     Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE),  Key(KEY_NONE), Key(KEY_PER),  Key(KEY_AMP),  Key(KEY_BAR),   Key(KEY_LCUR), Key(KEY_RCUR),      Key(KEY_NONE),
                     Key(KEY_LEFT_CTRL),  Key(KEY_LEFT_ALT), Key(KEY_NONE), LayerKey(SYM), Key(KEY_SPACE), Key(KEY_NONE), Key(KEY_NONE), Key(KEY_FS),   Key(KEY_BS),    Key(KEY_NONE), Key(KEY_NONE),      Key(KEY_RETURN)},
                    
                    // ARROW
                    {Key(KEY_ESC),        Key(KEY_NONE),     Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE),  Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE), Key(KEY_UPA),   Key(KEY_NONE), Key(KEY_NONE),      Key(KEY_DELETE),
                     Key(KEY_TAB),        Key(KEY_NONE),     Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE),  Key(KEY_NONE), Key(KEY_NONE), Key(KEY_LA),   Key(KEY_DNA),   Key(KEY_RA),   Key(KEY_NONE),      Key(KEY_RETURN),
                     Key(KEY_LEFT_SHIFT), Key(KEY_NONE),     Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE),  Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE), Key(KEY_DNA),   Key(KEY_NONE), Key(KEY_NONE),      Key(KEY_NONE),
                     Key(KEY_LEFT_CTRL),  Key(KEY_LEFT_ALT), Key(KEY_NONE), Key(KEY_NONE), Key(KEY_SPACE), Key(KEY_NONE), Key(KEY_NONE), LayerKey(ARR), Key(KEY_NONE),  Key(KEY_NONE), Key(KEY_NONE),      Key(KEY_RETURN)},
                    
                    // FUNC
                    {Key(KEY_ESC),        Key(KEY_F1),       Key(KEY_F2),   Key(KEY_F3),   Key(KEY_F4),    Key(KEY_F5),   Key(KEY_F6),   Key(KEY_F7),   Key(KEY_F8),    Key(KEY_F9),   Key(KEY_F10),       Key(KEY_DELETE),
                     Key(KEY_TAB),        Key(KEY_F11),      Key(KEY_F12),  Key(KEY_NONE), Key(KEY_NONE),  Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE),  Key(KEY_NONE), Key(KEY_NONE),      Key(KEY_RETURN),
                     Key(KEY_LEFT_SHIFT), Key(KEY_NONE),     Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE),  Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE),  Key(KEY_NONE), Key(KEY_NONE),      Key(KEY_NONE),
                     Key(KEY_LEFT_CTRL),  Key(KEY_LEFT_ALT), Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE),  Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE),  LayerKey(FUN), Key(KEY_NONE),      Key(KEY_RETURN)},
                    
                    // MOUS
                    {Key(KEY_ESC),        Key(KEY_NONE),     Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE),  Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE),  Key(KEY_NONE), Key(KEY_NONE),      SpecialKey(RAN),
                     Key(KEY_TAB),        Key(KEY_NONE),    Key(KEY_NONE),  Key(KEY_NONE), Key(KEY_NONE),  Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE),  Key(KEY_NONE), Key(KEY_NONE),      SpecialKey(HTS),
                     Key(KEY_LEFT_SHIFT), Key(KEY_NONE),     Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE),  Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE),  Key(KEY_NONE), Key(KEY_NONE),      Key(KEY_NONE),
                     Key(KEY_LEFT_CTRL),  Key(KEY_LEFT_ALT), Key(KEY_NONE), Key(KEY_NONE), Key(KEY_NONE),  Key(KEY_NONE), LayerKey(MOS), Key(KEY_NONE), Key(KEY_NONE),  Key(KEY_NONE), Key(KEY_NONE),      Key(KEY_RETURN)},
                    };
                                
short analogCutoffs[48]    = {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
                              1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
                              1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
                              1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};