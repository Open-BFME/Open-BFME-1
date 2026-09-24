// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/Common/System /ICode/Libraries/Source/WWVegas/WWLib
// Xfer::xferUpgradeMask (reference Xfer.cpp) as BFME's cdecl helper taking the Xfer and
// a 192-bit upgrade mask; UpgradeTemplate keeps its name at +8, bit index at +0x20, next at +0x108.

#include "xfer.h"
#include "ascii_string.h"
#include <string.h>

// Version passed to the Xfer as a 4-byte local, which is what decides retail's frame packing.
union Rva0010CC40XferVersion
{
    Xfer::Version m_fields;
    unsigned int m_value;
};

struct XferException { void *text; int tag; };
extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);
__declspec(noreturn) void __stdcall _CxxThrowException(void *object, void *throwInfo);
extern int g_rva005c5100ThrowInfo;

// UpgradeCenter::firstUpgradeTemplate, matched under its generated name at 0x0010A6D0.
struct Gen_0010a6d0 { int m(); };

class UpgradeTemplate;
class UpgradeCenter {
public:
    const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;

void xferBlob_0010CC40(Xfer *xfer, void *upgradeMaskDataV)
{
    unsigned int *upgradeMaskData = (unsigned int *)upgradeMaskDataV;
    {
        Rva0010CC40XferVersion version;
        version.m_fields.data[0] = 1;
        version.m_fields.data[1] = 1;
        *xfer == version.m_fields;
    }

    if (xfer->IsStoring())
    {
        AsciiString upgradeName;
        unsigned short count = 0;
        char *upgradeTemplate;
        for (upgradeTemplate = (char *)((Gen_0010a6d0 *)TheUpgradeCenter)->m(); upgradeTemplate; upgradeTemplate = *(char **)(upgradeTemplate + 0x108))
        {
            unsigned int bit = *(unsigned int *)(upgradeTemplate + 0x20);
            unsigned int word = upgradeMaskData[bit >> 5];
            if (word & (1u << (bit & 0x1f)))
                count++;
        }
        *xfer == count;

        for (upgradeTemplate = (char *)((Gen_0010a6d0 *)TheUpgradeCenter)->m(); upgradeTemplate; upgradeTemplate = *(char **)(upgradeTemplate + 0x108))
        {
            unsigned int bit = *(unsigned int *)(upgradeTemplate + 0x20);
            unsigned int word = upgradeMaskData[bit >> 5];
            if (word & (1u << (bit & 0x1f)))
            {
                upgradeName = *(AsciiString *)(upgradeTemplate + 8);
                *xfer == upgradeName;
            }
        }
    }
    else
    {
        AsciiString upgradeName;
        unsigned short count;
        *xfer == count;

        memset(upgradeMaskData, 0, 24);

        for (unsigned short i = 0; i < count; ++i)
        {
            *xfer == upgradeName;
            const UpgradeTemplate *found = TheUpgradeCenter->findUpgrade(upgradeName);
            if (found == 0)
            {
                XferException error;
                bfmeFormatText(&error, 0, 0);
                _CxxThrowException(&error, &g_rva005c5100ThrowInfo);
            }
            unsigned int bit = *(unsigned int *)((const char *)found + 0x20);
            upgradeMaskData[bit >> 5] |= 1u << (bit & 0x1f);
        }
    }
}
