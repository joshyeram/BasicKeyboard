#include "Keyboard.h"

#define KEY_NONE  0x00
#define KEY_SPACE 0x20          // SPACE
#define KEY_EX	  0x21          // !
#define KEY_QUOTE 0x22          // "
#define KEY_POUND 0x23          // #
#define KEY_DS	  0x24          // $
#define KEY_PER	  0x25          // %
#define KEY_AMP	  0x26          // &
#define KEY_SQU	  0x27          // '
#define KEY_LP	  0x28          // (
#define KEY_RP	  0x29          // )
#define KEY_AST	  0x2A          // *
#define KEY_PLUS  0x2B          // +
#define KEY_COM	  0x2C          // ,
#define KEY_MIN	  0x2D          // -
#define KEY_DOT	  0x2E          // .
#define KEY_FS	  0x2F          // /
#define KEY_0	  0x30          // 0
#define KEY_1	  0x31          // 1
#define KEY_2	  0x32          // 2
#define KEY_3	  0x33          // 3
#define KEY_4	  0x34          // 4
#define KEY_5	  0x35          // 5
#define KEY_6	  0x36          // 6
#define KEY_7	  0x37          // 7
#define KEY_8	  0x38          // 8
#define KEY_9	  0x39          // 9
#define KEY_COL	  0x3A          // :
#define KEY_SMCOL 0x3B          // ;
#define KEY_LESS  0x3C          // <
#define KEY_EQ	  0x3D          // =
#define KEY_GRET  0x3E          // >
#define KEY_QUES  0x3F          // ?
#define KEY_AT	  0x40          // @
#define KEY_A	  0x41          // A
#define KEY_B	  0x42          // B
#define KEY_C	  0x43          // C
#define KEY_D	  0x44          // D
#define KEY_E	  0x45          // E
#define KEY_F	  0x46          // F
#define KEY_G	  0x47          // G
#define KEY_H	  0x48          // H
#define KEY_I	  0x49          // I
#define KEY_J	  0x4A          // J
#define KEY_K	  0x4B          // K
#define KEY_L	  0x4C          // L
#define KEY_M	  0x4D          // M
#define KEY_N	  0x4E          // N
#define KEY_O	  0x4F          // O
#define KEY_P	  0x50          // P
#define KEY_Q	  0x51          // Q
#define KEY_R	  0x52          // R
#define KEY_S	  0x53          // S
#define KEY_T	  0x54          // T
#define KEY_U	  0x55          // U
#define KEY_V	  0x56          // V
#define KEY_W	  0x57          // W
#define KEY_X	  0x58          // X
#define KEY_Y	  0x59          // Y
#define KEY_Z	  0x5A          // Z
#define KEY_LB	  0x5B          // [
#define KEY_BS	  0x5C          // bslash
#define KEY_RB	  0x5D          // ]
#define KEY_EXP	  0x5E          // ^
#define KEY_UND	  0x5F          // _
#define KEY_GRAV  0x60          // `
#define KEY_a	  0x61          // a
#define KEY_b	  0x62          // b
#define KEY_c	  0x63          // c
#define KEY_d	  0x64          // d
#define KEY_e	  0x65          // e
#define KEY_f	  0x66          // f
#define KEY_g	  0x67          // g
#define KEY_h	  0x68          // h
#define KEY_i	  0x69          // i
#define KEY_j	  0x6A          // j
#define KEY_k	  0x6B          // k
#define KEY_l	  0x6C          // l
#define KEY_m	  0x6D          // m
#define KEY_n	  0x6E          // n
#define KEY_o	  0x6F          // o
#define KEY_p	  0x70          // p
#define KEY_q	  0x71          // q
#define KEY_r	  0x72          // r
#define KEY_s	  0x73          // s
#define KEY_t	  0x74          // t
#define KEY_u	  0x75          // u
#define KEY_v	  0x76          // v
#define KEY_w	  0x77          // w
#define KEY_x	  0x78          // x
#define KEY_y	  0x79          // y
#define KEY_z	  0x7A          // z
#define KEY_LCUR  0x7B          // {
#define KEY_BAR	  0x7C          // |
#define KEY_RCUR  0x7D          // }
#define KEY_EH	  0x7E          // ~
#define KEY_DEL	  0x7F          // DEL

#define KEY_UPA   0xDA
#define KEY_DNA   0xD9
#define KEY_LA    0xD8
#define KEY_RA    0xD7

class Key
{
    public:
        Key(int keyCode);
        Key() = default;
        
        int keyCode;
        bool isLayer;
        bool isSpecial;
};

class LayerKey: public Key
{
    public:
        LayerKey(int layer); 
};

class SpecialKey: public Key
{
    public:
        SpecialKey(int layer); 
};