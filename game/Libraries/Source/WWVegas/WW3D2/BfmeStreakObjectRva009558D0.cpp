// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// Constructor 009566D0 installs VA0113D5E0; slot76 contains VA00D558D0.
// The reconciled RenderObj interface and neighboring LOD slots establish
// float const-thiscall/no-args. The exact method identity stays address-named.
// Retail is FLD [VA0113BD7C]; RET at9558D6; the next bytes are INT3.
// Both baseline and Ghidra read 0x7F7FFFFF at the referenced constant.
#include "rendobj.h"

class BfmeStreakObject : public RenderObjClass
{
public:
    float rva009558D0() const;
};

float BfmeStreakObject::rva009558D0() const
{
    return AT_MIN_LOD;
}
