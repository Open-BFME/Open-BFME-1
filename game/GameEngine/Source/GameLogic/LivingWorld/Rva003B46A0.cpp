// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail RVA 0x003B46A0: 263 bytes, ret 4 at +0x104 followed by INT3.
// The containing class and this method's identity remain unproven.
// Xfer's witnessed virtual slots identify IsLightCRC (+0x10), IsLoading
// (+0x04), Version (+0x28), AsciiString (+0x68), and Bool (+0x8c).
// Each 32-byte vector element has a Snapshot vptr and an AsciiString at +4;
// its DoXfer dispatch is at +0x0c. Loading resolves the string through the
// independently matched findIndex body at 0x003B40A0, via ILT 0x0000577C,
// with receiver this-8. These relations place this TU beside that lookup
// without assigning its containing class a speculative identity.

#include <vector>
#include "ascii_string.h"
#include "../../Common/System/xfer.h"
#include "../../Common/System/snapshot.h"

class BfmeLivingWorldCampaignManager
{
public:
    int findIndex(void *key);
};

struct Rva003B46A0Record : Snapshot
{
    AsciiString m_at04;
    char m_at08[0x18];
};

class Rva003B46A0
{
public:
    void method(Xfer *xfer);

private:
    unsigned int m_at00;
    int m_at04;
    _STL::vector<Rva003B46A0Record> m_at08;
    bool m_at14;
    bool m_at15;
};

// ?method@Rva003B46A0@@QAEXPAVXfer@@@Z
void Rva003B46A0::method(Xfer *xfer)
{
    if (xfer->IsLightCRC())
        return;

    // The version occupies a dword stack slot in retail. Giving its storage
    // dword alignment also preserves the two string locals' stack placement.
    union { Xfer::Version version; unsigned int storage; };
    version.data[0] = 1;
    version.data[1] = 1;
    *xfer == version;

    if (xfer->IsLoading())
    {
        AsciiString name;
        *xfer == name;
        m_at04 = ((BfmeLivingWorldCampaignManager *)((char *)this - 8))->findIndex(&name);
        m_at08[m_at04].DoXfer(*xfer);
    }
    else
    {
        AsciiString name(m_at08[m_at04].m_at04);
        *xfer == name;
        m_at08[m_at04].DoXfer(*xfer);
    }

    *xfer == m_at14;
    *xfer == m_at15;
}
