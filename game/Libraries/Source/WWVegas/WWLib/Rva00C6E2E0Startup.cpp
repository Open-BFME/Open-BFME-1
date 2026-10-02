// cl: /O2 /MD /Igame/Libraries/Source/WWVegas/WWLib
#include "mpmath.h"
#include "int.h"

void bfmeRva00C6E2E0InitializeMultiprecisionBuffer()
{
    XMP_Init(Int<64>::Remainder, 0, 64);
}
