#include <ti/getcsc.h>
#include <ti/screen.h>
#include <stdio.h>
#include <graphx.h>
#include <compression.h>

#include "gfx/gfx.h"

/* Set maximum size of input and output buffers */
#define INPUT_SIZE  10
#define RESP_SIZE   20

void PrintCentered(const char *str);
void PrintPos(const char *str, const int x, const int y);

static unsigned char font8x8[128 * 8];
static unsigned char font8x8_spacing[128];

int main(void)
{
    char inputBuffer[INPUT_SIZE];
    char response[RESP_SIZE];

    gfx_Begin();
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    zx7_Decompress(gfx_vram, background_compressed);
    gfx_SetFontData(font8x8);
    gfx_SetFontSpacing(font8x8_spacing);

    PrintCentered("Press Any Button");

    while (!os_GetCSC());

    zx7_Decompress(gfx_vram, background_compressed);
    PrintCentered("Waiting for Connection");

    bool Connected = false;
    while (!Connected){
        if (os_GetCSC()){
            break;
        };
    };

    gfx_End();

    if (Connected == false){
        os_ClrHome();
        sprintf(response, "Aborting Connection");
        os_ClrHome();
        os_PutStrFull(response);
        while (!os_GetCSC());
        return 0;
    };

    bool Running = true;
    while (Running){
        os_ClrHome();
        os_GetStringInput("Enter Equation:", inputBuffer, INPUT_SIZE);
        if (inputBuffer[0] == '\0'){
            Running = false;
            break;
        } else {
            
        }
        sprintf(response, "Sending Equation: %s.", inputBuffer);
        os_ClrHome();
        os_PutStrFull(response);

        /* Waits for a key */
        while (!os_GetCSC());
    }

    return 0;
}

void PrintCentered(const char *str)
{
    gfx_PrintStringXY(str,
                      (GFX_LCD_WIDTH - gfx_GetStringWidth(str)) / 2,
                      (GFX_LCD_HEIGHT - 8) / 2);
}

void PrintPos(const char *str, const int x, const int y){
    gfx_PrintStringXY(str,x,y);
}

static unsigned char font8x8_spacing[128] =
{
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
};

static unsigned char font8x8[128 * 8] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 000 (.)
	0x20, 0x7e, 0x81, 0xa5, 0x81, 0xbd, 0x99, 0x81,	// Char 001 (.)
	0x7e, 0x7e, 0xff, 0xdb, 0xff, 0xc3, 0xe7, 0xff,	// Char 002 (.)
	0x7e, 0x6c, 0xfe, 0xfe, 0xfe, 0x7c, 0x38, 0x10,	// Char 003 (.)
	0x00, 0x10, 0x38, 0x7c, 0xfe, 0x7c, 0x38, 0x10,	// Char 004 (.)
	0x00, 0x38, 0x7c, 0x38, 0xfe, 0xfe, 0x7c, 0x38,	// Char 005 (.)
	0x7c, 0x10, 0x10, 0x38, 0x7c, 0xfe, 0x7c, 0x38,	// Char 006 (.)
	0x7c, 0x00, 0x00, 0x18, 0x3c, 0x3c, 0x18, 0x00,	// Char 007 (.)
	0x00, 0xff, 0xff, 0xe7, 0xc3, 0xc3, 0xe7, 0xff,	// Char 008 (.)
	0xff, 0x00, 0x3c, 0x66, 0x42, 0x42, 0x66, 0x3c,	// Char 009 (.)
	0x00, 0xff, 0xc3, 0x99, 0xbd, 0xbd, 0x99, 0xc3,	// Char 010 (.)
	0xff, 0x0f, 0x07, 0x0f, 0x7d, 0xcc, 0xcc, 0xcc,	// Char 011 (.)
	0x78, 0x3c, 0x66, 0x66, 0x66, 0x3c, 0x18, 0x7e,	// Char 012 (.)
	0x18, 0x3f, 0x33, 0x3f, 0x30, 0x30, 0x70, 0xf0,	// Char 013 (.)
	0xe0, 0x7f, 0x63, 0x7f, 0x63, 0x63, 0x67, 0xe6,	// Char 014 (.)
	0xc0, 0x99, 0x5a, 0x3c, 0xe7, 0xe7, 0x3c, 0x5a,	// Char 015 (.)
	0x99, 0x80, 0xe0, 0xf8, 0xfe, 0xf8, 0xe0, 0x80,	// Char 016 (.)
	0x00, 0x02, 0x0e, 0x3e, 0xfe, 0x3e, 0x0e, 0x02,	// Char 017 (.)
	0x00, 0x18, 0x3c, 0x7e, 0x18, 0x18, 0x7e, 0x3c,	// Char 018 (.)
	0x18, 0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x66,	// Char 019 (.)
	0x00, 0x7f, 0xdb, 0xdb, 0x7b, 0x1b, 0x1b, 0x1b,	// Char 020 (.)
	0x00, 0x3e, 0x63, 0x38, 0x6c, 0x6c, 0x38, 0xcc,	// Char 021 (.)
	0x78, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x7e, 0x7e,	// Char 022 (.)
	0x00, 0x18, 0x3c, 0x7e, 0x18, 0x7e, 0x3c, 0x18,	// Char 023 (.)
	0xff, 0x18, 0x3c, 0x7e, 0x18, 0x18, 0x18, 0x18,	// Char 024 (.)
	0x00, 0x18, 0x18, 0x18, 0x18, 0x7e, 0x3c, 0x18,	// Char 025 (.)
	0x00, 0x00, 0x18, 0x0c, 0xfe, 0x0c, 0x18, 0x00,	// Char 026 (.)
	0x00, 0x00, 0x30, 0x60, 0xfe, 0x60, 0x30, 0x00,	// Char 027 (.)
	0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xfe, 0x00,	// Char 028 (.)
	0x00, 0x00, 0x24, 0x66, 0xff, 0x66, 0x24, 0x00,	// Char 029 (.)
	0x00, 0x00, 0x18, 0x3c, 0x7e, 0xff, 0xff, 0x00,	// Char 030 (.)
	0x00, 0x00, 0xff, 0xff, 0x7e, 0x3c, 0x18, 0x00,	// Char 031 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 032 ( )
	0x00, 0x30, 0x78, 0x78, 0x30, 0x30, 0x00, 0x30,	// Char 033 (!)
	0x00, 0x6c, 0x6c, 0x6c, 0x00, 0x00, 0x00, 0x00,	// Char 034 (")
	0x00, 0x6c, 0x6c, 0xfe, 0x6c, 0xfe, 0x6c, 0x6c,	// Char 035 (#)
	0x00, 0x30, 0x7c, 0xc0, 0x78, 0x0c, 0xf8, 0x30,	// Char 036 ($)
	0x00, 0x00, 0xc6, 0xcc, 0x18, 0x30, 0x66, 0xc6,	// Char 037 (%)
	0x00, 0x38, 0x6c, 0x38, 0x76, 0xdc, 0xcc, 0x76,	// Char 038 (&)
	0x00, 0x60, 0x60, 0xc0, 0x00, 0x00, 0x00, 0x00,	// Char 039 (')
	0x00, 0x18, 0x30, 0x60, 0x60, 0x60, 0x30, 0x18,	// Char 040 (()
	0x00, 0x60, 0x30, 0x18, 0x18, 0x18, 0x30, 0x60,	// Char 041 ())
	0x00, 0x00, 0x66, 0x3c, 0xff, 0x3c, 0x66, 0x00,	// Char 042 (*)
	0x00, 0x00, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x00,	// Char 043 (+)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30,	// Char 044 (,)
	0x60, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00,	// Char 045 (-)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30,	// Char 046 (.)
	0x00, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x80,	// Char 047 (/)
	0x00, 0xfe, 0x86, 0x8e, 0xd2, 0xe2, 0xc2, 0xfe,	// Char 048 (0)
	0x00, 0x10, 0x10, 0x10, 0x30, 0x30, 0x30, 0x30,	// Char 049 (1)
	0x00, 0x3c, 0x46, 0x06, 0x0c, 0x30, 0x60, 0x7e,	// Char 050 (2)
	0x00, 0x3c, 0x46, 0x06, 0x1c, 0x02, 0x62, 0x7c,	// Char 051 (3)
	0x00, 0x4c, 0x4c, 0x44, 0x44, 0x7c, 0x0c, 0x0c,	// Char 052 (4)
	0x00, 0x7e, 0x40, 0x7c, 0x02, 0x02, 0x62, 0x7c,	// Char 053 (5)
	0x00, 0x3c, 0x66, 0x40, 0x7c, 0x62, 0x62, 0x3c,	// Char 054 (6)
	0x00, 0x7c, 0x0c, 0x04, 0x04, 0x0c, 0x0c, 0x0c,	// Char 055 (7)
	0x00, 0x3c, 0x46, 0x46, 0x3c, 0x62, 0x62, 0x3c,	// Char 056 (8)
	0x00, 0x3c, 0x46, 0x46, 0x3e, 0x02, 0x62, 0x3c,	// Char 057 (9)
	0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30,	// Char 058 (:)
	0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30,	// Char 059 (;)
	0x60, 0x18, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x18,	// Char 060 (<)
	0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0xfc, 0x00,	// Char 061 (=)
	0x00, 0x60, 0x30, 0x18, 0x0c, 0x18, 0x30, 0x60,	// Char 062 (>)
	0x00, 0x78, 0xcc, 0x0c, 0x18, 0x30, 0x00, 0x30,	// Char 063 (?)
	0x00, 0x7c, 0xc6, 0xde, 0xde, 0xde, 0xc0, 0x78,	// Char 064 (@)
	0x00, 0x7e, 0x46, 0x42, 0x42, 0x7e, 0x62, 0x62,	// Char 065 (A)
	0x00, 0x7c, 0x4c, 0x44, 0x7e, 0x62, 0x62, 0x7e,	// Char 066 (B)
	0x00, 0x7e, 0x46, 0x40, 0x60, 0x60, 0x62, 0x7e,	// Char 067 (C)
	0x00, 0x7c, 0x46, 0x46, 0x42, 0x62, 0x62, 0x7c,	// Char 068 (D)
	0x00, 0x7e, 0x46, 0x40, 0x78, 0x60, 0x62, 0x7e,	// Char 069 (E)
	0x00, 0x7e, 0x46, 0x40, 0x78, 0x60, 0x60, 0x60,	// Char 070 (F)
	0x00, 0x7e, 0x46, 0x40, 0x4e, 0x62, 0x62, 0x7e,	// Char 071 (G)
	0x00, 0x4c, 0x4c, 0x44, 0x7c, 0x64, 0x64, 0x64,	// Char 072 (H)
	0x00, 0x10, 0x10, 0x10, 0x18, 0x18, 0x18, 0x18,	// Char 073 (I)
	0x00, 0x06, 0x06, 0x02, 0x02, 0x62, 0x62, 0x7e,	// Char 074 (J)
	0x00, 0x46, 0x46, 0x4c, 0x78, 0x64, 0x62, 0x62,	// Char 075 (K)
	0x00, 0x40, 0x40, 0x40, 0x60, 0x60, 0x60, 0x7e,	// Char 076 (L)
	0x00, 0xc6, 0xee, 0xbe, 0x92, 0xd2, 0xc2, 0xc2,	// Char 077 (M)
	0x00, 0x46, 0x46, 0x62, 0x52, 0x6a, 0x66, 0x62,	// Char 078 (N)
	0x00, 0x7e, 0x46, 0x46, 0x62, 0x62, 0x62, 0x7e,	// Char 079 (O)
	0x00, 0x7e, 0x46, 0x46, 0x7e, 0x60, 0x60, 0x60,	// Char 080 (P)
	0x00, 0x7e, 0x46, 0x46, 0x62, 0x62, 0x7e, 0x1c,	// Char 081 (Q)
	0x04, 0x7e, 0x46, 0x46, 0x7c, 0x68, 0x64, 0x62,	// Char 082 (R)
	0x00, 0x7e, 0x46, 0x60, 0x18, 0x06, 0x62, 0x7e,	// Char 083 (S)
	0x00, 0x7e, 0x16, 0x10, 0x18, 0x18, 0x18, 0x18,	// Char 084 (T)
	0x00, 0x46, 0x46, 0x42, 0x62, 0x62, 0x62, 0x7e,	// Char 085 (U)
	0x00, 0x46, 0x46, 0x46, 0x42, 0x64, 0x38, 0x10,	// Char 086 (V)
	0x00, 0x86, 0x86, 0x82, 0xd2, 0xfa, 0xee, 0xc6,	// Char 087 (W)
	0x00, 0x86, 0x86, 0x4c, 0x30, 0x68, 0xe4, 0xc2,	// Char 088 (X)
	0x00, 0x46, 0x46, 0x42, 0x3c, 0x18, 0x18, 0x18,	// Char 089 (Y)
	0x00, 0xfe, 0x06, 0x08, 0x10, 0x20, 0xc0, 0xfe,	// Char 090 (Z)
	0x00, 0x78, 0x60, 0x60, 0x60, 0x60, 0x60, 0x78,	// Char 091 ([)
	0x00, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x02,	// Char 092 (\)
	0x00, 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78,	// Char 093 (])
	0x00, 0x10, 0x38, 0x6c, 0xc6, 0x00, 0x00, 0x00,	// Char 094 (^)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 095 (_)
	0xff, 0x30, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00,	// Char 096 (`)
	0x00, 0x00, 0x00, 0x7e, 0x06, 0x7e, 0x62, 0x7e,	// Char 097 (a)
	0x00, 0x40, 0x40, 0x40, 0x7e, 0x62, 0x62, 0x7e,	// Char 098 (b)
	0x00, 0x00, 0x00, 0x7e, 0x46, 0x60, 0x60, 0x7e,	// Char 099 (c)
	0x00, 0x06, 0x06, 0x02, 0x7e, 0x62, 0x62, 0x7e,	// Char 100 (d)
	0x00, 0x00, 0x00, 0x7e, 0x46, 0x7e, 0x60, 0x7e,	// Char 101 (e)
	0x00, 0x0c, 0x1c, 0x20, 0x78, 0x60, 0x60, 0x60,	// Char 102 (f)
	0x00, 0x00, 0x00, 0x7e, 0x46, 0x42, 0x7e, 0x06,	// Char 103 (g)
	0x78, 0x40, 0x40, 0x40, 0x7e, 0x62, 0x62, 0x62,	// Char 104 (h)
	0x00, 0x10, 0x00, 0x10, 0x10, 0x18, 0x18, 0x18,	// Char 105 (i)
	0x00, 0x0c, 0x00, 0x0c, 0x04, 0x04, 0x64, 0x64,	// Char 106 (j)
	0x7c, 0x40, 0x40, 0x46, 0x4c, 0x78, 0x64, 0x62,	// Char 107 (k)
	0x00, 0x10, 0x10, 0x10, 0x10, 0x18, 0x18, 0x18,	// Char 108 (l)
	0x00, 0x00, 0x00, 0xfe, 0x96, 0x96, 0xd2, 0xd2,	// Char 109 (m)
	0x00, 0x00, 0x00, 0x7e, 0x46, 0x62, 0x62, 0x62,	// Char 110 (n)
	0x00, 0x00, 0x00, 0x7e, 0x46, 0x62, 0x62, 0x7e,	// Char 111 (o)
	0x00, 0x00, 0x00, 0x7e, 0x46, 0x42, 0x7e, 0x60,	// Char 112 (p)
	0x60, 0x00, 0x00, 0x7e, 0x46, 0x42, 0x7e, 0x02,	// Char 113 (q)
	0x02, 0x00, 0x00, 0x7e, 0x46, 0x60, 0x60, 0x60,	// Char 114 (r)
	0x00, 0x00, 0x00, 0x7c, 0x40, 0x7c, 0x04, 0x7c,	// Char 115 (s)
	0x00, 0x10, 0x10, 0x3c, 0x10, 0x10, 0x18, 0x1c,	// Char 116 (t)
	0x00, 0x00, 0x00, 0x46, 0x46, 0x62, 0x62, 0x7e,	// Char 117 (u)
	0x00, 0x00, 0x00, 0x46, 0x46, 0x66, 0x34, 0x18,	// Char 118 (v)
	0x00, 0x00, 0x00, 0x86, 0x96, 0xd2, 0xfe, 0x6c,	// Char 119 (w)
	0x00, 0x00, 0x00, 0x46, 0x2c, 0x18, 0x34, 0x62,	// Char 120 (x)
	0x00, 0x00, 0x00, 0x46, 0x46, 0x62, 0x7e, 0x02,	// Char 121 (y)
	0x7c, 0x00, 0x00, 0x7e, 0x0c, 0x18, 0x30, 0x7e,	// Char 122 (z)
	0x00, 0x1c, 0x30, 0x30, 0xe0, 0x30, 0x30, 0x1c,	// Char 123 ({)
	0x00, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18,	// Char 124 (|)
	0x00, 0xe0, 0x30, 0x30, 0x1c, 0x30, 0x30, 0xe0,	// Char 125 (})
	0x00, 0x76, 0xdc, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 126 (~)
	0x00, 0x00, 0x10, 0x38, 0x6c, 0xc6, 0xc6, 0xfe,	// Char 127 (.)
};