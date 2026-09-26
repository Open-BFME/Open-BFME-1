// Native model-name selection at RVA 0x005F6B60 (692 bytes, hidden-sret RET4).
// RenderObjectDrawModule's matched constructor at 0x005F7820 installs primary
// vtable 0x01112F80; slot 5 reaches this body through ILT 0x0004652E.
// The named DefaultParticleModule caller/factory at 0x005E59C0/0x005E89C0
// installs 0x01111EA4 with the same slot. The original method name is unknown.
// This TU-scoped owner view keeps the proven offsets without changing headers.
// Three independent string lifetimes reproduce retail's shared cleanup tail.
// The null-first fallback expression also preserves retail's branch order.
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath
#include "ascii_string.h"
#include "wwmath.h"
#include <stdio.h>
#include <string.h>
#pragma intrinsic(strlen)

inline AsciiString::~AsciiString()
{
    ((StringBase<char> *)this)->releaseBuffer();
}

template<> inline void StringBase<char>::concat(const char *str)
{
    concat(str, str ? strlen(str) : 0);
}

class ParticleSystemZA
{
public:
    const AsciiString &nameAt10() const { return name; }
private:
    unsigned char prefix[0x10];
    AsciiString name;
};
ParticleSystemZA *bfmeNullSystemZA();

struct Rva005F6B60Choice
{
    AsciiString name;
    int count;
    float threshold;
    int field0C;
};

class Rva005F6B60Owner
{
public:
    AsciiString selectModelNameAt005F6B60();
    void *vtable;
    ParticleSystemZA *system;
    unsigned char padding08[0x1c];
    bool field24;
    unsigned char padding25[3];
    Rva005F6B60Choice choices[3];
    int field58;
};

AsciiString Rva005F6B60Owner::selectModelNameAt005F6B60()
{
    if (field24) {
        float chance = WWMath::Random_Float() * 100.0f;
        if (chance <= choices[0].threshold) {
            field58 = choices[0].field0C;
            AsciiString name(choices[0].name);
            for (int i = 0; i < 6; ++i)
                name.removeLastChar();
            float variantCount = (float)choices[0].count;
            char suffix[4];
            sprintf(suffix, "%02d", (int)(WWMath::Random_Float() * (variantCount - 1.0f) + 1.5f));
            name.concat(suffix);
            name.concat(".w3d");
            return name;
        } else if (chance <= choices[1].threshold) {
            field58 = choices[1].field0C;
            AsciiString name(choices[1].name);
            for (int i = 0; i < 6; ++i)
                name.removeLastChar();
            float variantCount = (float)choices[1].count;
            char suffix[4];
            sprintf(suffix, "%02d", (int)(WWMath::Random_Float() * (variantCount - 1.0f) + 1.5f));
            name.concat(suffix);
            name.concat(".w3d");
            return name;
        } else {
            field58 = choices[2].field0C;
            AsciiString name(choices[2].name);
            for (int i = 0; i < 6; ++i)
                name.removeLastChar();
            float variantCount = (float)choices[2].count;
            char suffix[4];
            sprintf(suffix, "%02d", (int)(WWMath::Random_Float() * (variantCount - 1.0f) + 1.5f));
            name.concat(suffix);
            name.concat(".w3d");
            return name;
        }
    }
    return (!system ? bfmeNullSystemZA() : system)->nameAt10();
}
