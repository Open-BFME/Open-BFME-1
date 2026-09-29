// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// Retail 0x007657F0, 568 bytes, ending in ret 0x0c. Unknown BFME owner:
// keep the address identity. Retail proves AsciiString at +8 and float at +0x10.
// Builds prefix[number].name[number], retries prefix.name, then caches the
// duration from HAnimClass virtual slots +0x10/+0x14. The duration calculation
// has a ZH W3DAnimationInfo::getAnimHandle twin, but BFME's extra arguments and
// shifted fields do not independently establish that class identity.
// Calls use StringBase<char>'s existing definitions and the independently
// matched bfmeHasVNV/Get_HAnim family. Real hanim.h supplies the virtual ABI.
// Keep handle's declaration after name construction: declaring it above that
// block swaps ESI/EDI and changes null-test selection under MSVC 7.1.
#include "ascii_string.h"
#include "hanim.h"
#include <stdio.h>
#include <string.h>
#pragma intrinsic(strlen)

template<> inline bool StringBase<char>::isEmpty() const { return !m_data || m_data->length == 0; }
template<> inline void StringBase<char>::concat(char c) { concat(&c, 1); }
template<> inline void StringBase<char>::concat(const char *s) { concat(s, s ? strlen(s) : 0); }
template<> inline void StringBase<char>::concat(const StringBase<char> &s) { concat(s.str(), s.getLength()); }

char __cdecl bfmeHasVNV(const char *);
HAnimClass *__cdecl Get_HAnim(const char *);

class Rva007657F0 {
public:
    char pad00[8];
    AsciiString at08;
    char pad0c[4];
    float at10;
    HAnimClass *resolve(const AsciiString &prefix, bool numbered, int number);
};

HAnimClass *Rva007657F0::resolve(const AsciiString &prefix, bool numbered, int number)
{
    AsciiString name("");

    if (!prefix.isEmpty()) {
        name = prefix;
        char buffer[64];
        sprintf(buffer, "%d", number);
        if (numbered) name.concat(buffer);
        name.concat('.');
        name.StringBase<char>::concat(at08);
        if (numbered) name.concat(buffer);
    } else {
        name = at08;
    }
    HAnimClass *handle = 0;
    if (bfmeHasVNV(name.str())) handle = Get_HAnim(name.str());
    if (!handle && numbered && !prefix.isEmpty()) {
        name = prefix;
        name.concat('.');
        name.StringBase<char>::concat(at08);
        if (bfmeHasVNV(name.str()))
            handle = Get_HAnim(name.str());
    }
    if (handle && at10 < 0.0f)
        at10 = handle->Get_Num_Frames() * 1000.0f / handle->Get_Frame_Rate();
    return handle;
}
