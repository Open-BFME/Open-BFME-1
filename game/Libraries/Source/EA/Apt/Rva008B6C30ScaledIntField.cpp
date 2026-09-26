// cl: /DNDEBUG /MD /EHsc
// RVA 0x008B6C30: package the magnitude of field 0x60 scaled by 60.
#include <math.h>
#pragma intrinsic(abs)
class AptInteger
{
public:
    static AptInteger *Create(int value);
};

AptInteger *aptScaledMagnitudeAt008B6C30(void *self, int argc)
{
    int value = *(int *)((char *)self + 0x60);
    return AptInteger::Create(abs(value) * 60);
}
