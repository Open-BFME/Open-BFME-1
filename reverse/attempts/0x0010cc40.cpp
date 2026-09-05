// ?xferBlob_0010CC40@@YAXPAVXfer@@PAX@Z
// partial score=0.75 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/Common/System
//
// Open-BFME5: convert d_0010cc40 (dump Code/gen_asm/d_00104e40.asm) to standalone C++.
//
// Identity: Xfer::xferUpgradeMask(UpgradeMaskType*) -- shape matches
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/System/Xfer.cpp
// (Xfer::xferUpgradeMask, line 732) exactly: hardcoded version tag, IsStoring() branch,
// a count-then-names double loop over TheUpgradeCenter's linked upgrade-template list on
// save, and a count-then-findUpgrade loop with a formatted-text/_CxxThrowException throw
// on an unresolved name while loading. BFME represents UpgradeMaskType as a raw bit array
// (bit index read from UpgradeTemplate+0x20) rather than ZH's testForAll()/set() class, and
// UpgradeTemplate's name sits at +8, its list-next pointer at +0x108 (both raw fields, not
// calls, in the retail disassembly).
//
// Callees:
//   Xfer::Version pattern (see Rva0010D090SaveInfoXfer.cpp neighbour) for the version tag.
//   Xfer::IsStoring() -- vtable slot 8 (offset 2 in xfer.h).
//   0x0002F5BD -> Gen_0010a6d0::m() (Code/gen_small/fun_003.cpp), TheUpgradeCenter's
//     first-upgrade-template getter (matched @ 0x0010A6D0).
//   0x0002F95A -> UpgradeCenter::findUpgrade(const AsciiString&) (pinned in
//     reverse/symbols.csv).
//   0x00887C90 -> UnicodeString::set folded target, reused for the AsciiString copy.
//   0x00887940 -> AsciiString::releaseBuffer (string_base.cpp), fired via ~AsciiString.
//   0x009D6220 -> bfmeFormatText (Gen009D6220.cpp).
//   0x009F6D00 -> _CxxThrowException; ThrowInfo is the already-pinned
//     g_rva005c5100ThrowInfo (0x011DFE5C), reused verbatim from XferArray3.cpp's pattern.
//   0x012EF188 -> TheUpgradeCenter.

#include "xfer.h"

class UnicodeString {
public:
    char *m_text;
    void set(const UnicodeString &s);
};

class AsciiString {
public:
    AsciiString() : m_text(0) {}
    ~AsciiString() { releaseBuffer(); }
    char *m_text;
private:
    void releaseBuffer();
};

struct XferException { void *text; int tag; };
extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);
__declspec(noreturn) void __stdcall _CxxThrowException(void *object, void *throwInfo);
extern int g_rva005c5100ThrowInfo;

// TheUpgradeCenter's first-upgrade-template getter, already matched @ 0x0010A6D0.
struct Gen_0010a6d0 { void *m(); };

class UpgradeTemplate;
class UpgradeCenter {
public:
    const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;

void xferBlob_0010CC40(Xfer *xfer, void *upgradeMaskDataV)
{
    Xfer::Version version;
    version.data[0] = 1;
    version.data[1] = 1;
    *xfer == version;

    if (xfer->IsStoring())
    {
        unsigned short count = 0;
        char *upgradeTemplate = (char *)((Gen_0010a6d0 *)TheUpgradeCenter)->m();
        if (upgradeTemplate)
        {
            unsigned int *upgradeMaskData = (unsigned int *)upgradeMaskDataV;
            do
            {
                unsigned int bit = *(unsigned int *)(upgradeTemplate + 0x20);
                if (upgradeMaskData[bit >> 5] & (1u << (bit & 0x1f)))
                    ++count;
                upgradeTemplate = *(char **)(upgradeTemplate + 0x108);
            } while (upgradeTemplate);
        }
        *xfer == count;

        upgradeTemplate = (char *)((Gen_0010a6d0 *)TheUpgradeCenter)->m();
        if (upgradeTemplate)
        {
            unsigned int *upgradeMaskData = (unsigned int *)upgradeMaskDataV;
            do
            {
                unsigned int bit = *(unsigned int *)(upgradeTemplate + 0x20);
                if (upgradeMaskData[bit >> 5] & (1u << (bit & 0x1f)))
                {
                    AsciiString upgradeName;
                    ((UnicodeString *)&upgradeName)->set(*(UnicodeString *)(upgradeTemplate + 8));
                    *xfer == upgradeName;
                }
                upgradeTemplate = *(char **)(upgradeTemplate + 0x108);
            } while (upgradeTemplate);
        }
    }
    else
    {
        unsigned short count;
        *xfer == count;

        unsigned int *upgradeMaskData = (unsigned int *)upgradeMaskDataV;
        upgradeMaskData[0] = 0;
        upgradeMaskData[1] = 0;
        upgradeMaskData[2] = 0;
        upgradeMaskData[3] = 0;
        upgradeMaskData[4] = 0;
        upgradeMaskData[5] = 0;

        if (count > 0)
        {
            unsigned short i = 0;
            do
            {
                AsciiString upgradeName;
                *xfer == upgradeName;

                const UpgradeTemplate *found = TheUpgradeCenter->findUpgrade(upgradeName);
                if (!found)
                {
                    XferException error;
                    bfmeFormatText(&error, 0, 0);
                    _CxxThrowException(&error, &g_rva005c5100ThrowInfo);
                }

                unsigned int bit = *(unsigned int *)((const char *)found + 0x20);
                unsigned int *word = &upgradeMaskData[bit >> 5];
                *word = *word | (1u << (bit & 0x1f));
                ++i;
            } while (i < count);
        }
    }
}
