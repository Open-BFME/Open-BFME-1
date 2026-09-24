// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Retail 0x003BF580/139: source-shape bank, not a verified conversion.
// 0x0052B8A0 matched caller proves the CampaignManager receiver, hidden
// AsciiString result and int argument. This body uses its +0x28 resolver and
// +0x30 key, as independently matched isMissionObjectiveIndexed does.
// Target 0x00887B60 is the canonical StringBase<char> copy constructor;
// tools/callees.py can surface a GameSpyGroupRoom C++ alias at this same body.
// Retail second return instead calls AsciiString copy ILT 0x000416AF; this
// bank does NOT, so it must not be landed without that relocation correction.
// Reading secondEnd before index subtraction and secondBegin after it removes
// all six earlier register/scheduling differences: 139/139 instruction bytes
// now match, but the second copy still calls the wrong physical body.
#include "ascii_string.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
struct Rva003BF580Span {
    AsciiString *m_begin;
    AsciiString *m_end;
    unsigned size() const { return unsigned(m_end - m_begin); }
    AsciiString &operator[](unsigned index) const { return m_begin[index]; }
};
class LivingWorldRegion {
public:
    char m_pad00[0x54];
    Rva003BF580Span m_first;
    char m_pad5C[4];
    Rva003BF580Span m_second;
};
class LivingWorldRegionManager {
public:
    LivingWorldRegion *rva003C8A50(const AsciiString &key);
};
extern AsciiString Rva01336E50EmptyString;
class CampaignManager {
public:
    AsciiString rva003BF580(int index);
private:
    char m_pad00[0x28];
    LivingWorldRegionManager *m_resolver;
    char m_pad2C[4];
    AsciiString m_key;
};
AsciiString CampaignManager::rva003BF580(int index)
{
    if (m_resolver && index >= 0) {
        LivingWorldRegion *region = m_resolver->rva003C8A50(m_key);
        if (region) {
            AsciiString *firstBegin = region->m_first.m_begin;
            _ReadWriteBarrier();
            unsigned firstSize = unsigned(region->m_first.m_end - firstBegin);
            if ((unsigned)index < firstSize)
                return *(firstBegin + index);
            AsciiString *secondEnd = region->m_second.m_end;
            index -= firstSize;
            AsciiString *secondBegin = region->m_second.m_begin;
            unsigned secondSize = unsigned(secondEnd - secondBegin);
            if ((unsigned)index < secondSize)
                return secondBegin[index];
        }
    }
    return Rva01336E50EmptyString;
}
