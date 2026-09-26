// cl: /O2 /MD /Igame/Libraries/Source/WWVegas/WWLib
#include "mpmath.h"

extern digit g_bfmeRva0134F9A0Buffer[64];

void bfmeRva00C6E2E0InitializeMultiprecisionBuffer()
{
    XMP_Init(g_bfmeRva0134F9A0Buffer, 0, 64);
}
