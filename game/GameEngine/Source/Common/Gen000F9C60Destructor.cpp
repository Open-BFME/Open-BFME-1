// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail RVA 0x000CFA40, 77 bytes: nonvirtual destructor of the opaque
// 28-byte Gen_000F9C60 record copied by the matched 0x000F9C60 body.
// The +0 dword is data (copy/zero/xfer evidence), not a vptr. Native
// destruction releases the AsciiString at +0x18, then UnicodeString +0x14.
// Proof: targets/game/reverse/identity_evidence/000cfa40-gen000f9c60-destructor.md

#include "ascii_string.h"
#include "unicode_string.h"

// Keep the canonical 5-byte UnicodeString forwarder visible so VC7.1
// calls its actual StringBase<unsigned short> release body at 0x008881D0.
inline UnicodeString::~UnicodeString()
{
    ((StringBase<unsigned short> *)this)->releaseBuffer();
}

class Gen_000F9C60
{
public:
    ~Gen_000F9C60();

private:
    char m_head[0x14];
    UnicodeString m_bfmeText;
    AsciiString m_bfmeName;
};

// ??1Gen_000F9C60@@QAE@XZ
Gen_000F9C60::~Gen_000F9C60()
{
}
