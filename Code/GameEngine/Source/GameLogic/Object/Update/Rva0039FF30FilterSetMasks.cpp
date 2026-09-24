// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// stlport
// Open-BFME5: object-filter handle setter, retail 0x0039FF30, 549 bytes, called
// through ILT 0x0004699D by the TransportContainModuleData ctor at 0x0021FC80.
// Releases the pool handle, builds a kind-2 attribute entry from two by-value
// six-word masks and interns it; an empty first mask falls back to the kind-1
// setter at ILT 0x0000D3E1 (retail 0x0039FBA0, ret 0x30) with the none mask.
#include <bitset>
#include "StringInline.h"

struct Rva0021FC80Mask
{
    std::bitset<192> bits;
    Rva0021FC80Mask() {}
    explicit Rva0021FC80Mask(unsigned int bit) { bits.set(bit); }
};
extern const Rva0021FC80Mask Rva012ED8B8NoneMask;

struct Rva0039FF30Filter
{
    void setMasks(Rva0021FC80Mask, Rva0021FC80Mask);
    unsigned int handle;
};

class OpenContainModuleData
{
public:
    OpenContainModuleData();
    virtual ~OpenContainModuleData();
protected:
    unsigned char m_beforeFilter[0x110];
    Rva0039FF30Filter m_filter;
    unsigned char m_beforeFlag168[0x50];
};

class TransportContainModuleData : public OpenContainModuleData
{
public:
    TransportContainModuleData();
    virtual ~TransportContainModuleData();
private:
    bool m_flag168;
    unsigned char m_padding169[3];
    float m_scalar16c;
    bool m_flag170;
    bool m_flag171;
    unsigned char m_padding172[2];
    AsciiString m_initialPayloadName;
    int m_initialPayloadCount;
};

typedef unsigned int UnsignedInt;

enum { BFME_NO_ATTRIBUTE_HANDLE = 0xFFFFFFFF };

struct BfmeAttributePlainBlock
{
    void set(const Rva0021FC80Mask &mask)
    {
        const UnsignedInt *words =
            reinterpret_cast<const UnsignedInt *>(&mask);
        m_values[0] |= words[0];
        m_values[1] |= words[1];
        m_values[2] |= words[2];
        m_values[3] |= words[3];
        m_values[4] |= words[4];
        m_values[5] |= words[5];
    }

    UnsignedInt m_values[6];
};

class Gen00043699
{
public:
    Gen00043699();
    ~Gen00043699();

    unsigned char m_head[0x48];
    BfmeAttributePlainBlock m_firstPlain;
    BfmeAttributePlainBlock m_secondPlain;
    UnsignedInt m_kind;
    UnsignedInt m_index;
    bool m_enabled;
    unsigned char m_pad[3];
    UnsignedInt m_useCount;
};

struct BfmeAttributePool
{
    Gen00043699 *m_bfmeStart;
    Gen00043699 *m_bfmeFinish;
};

extern BfmeAttributePool TheBfmeAttributePool;
extern UnsignedInt bfmeInternAttributeEntry(Gen00043699 *entry);

struct RespawnPolicy
{
    UnsignedInt values[6];
};

class RespawnPolicyMember
{
public:
    void setPolicies(RespawnPolicy first, RespawnPolicy second);
};

// ?setMasks@Rva0039FF30Filter@@QAEXURva0021FC80Mask@@0@Z
void Rva0039FF30Filter::setMasks(Rva0021FC80Mask first,
    Rva0021FC80Mask second)
{
    if (handle != BFME_NO_ATTRIBUTE_HANDLE)
    {
        if (handle <= (UnsignedInt)(TheBfmeAttributePool.m_bfmeFinish
                - TheBfmeAttributePool.m_bfmeStart))
        {
            --TheBfmeAttributePool.m_bfmeStart[handle].m_useCount;
            handle = BFME_NO_ATTRIBUTE_HANDLE;
        }
    }

    Gen00043699 entry;
    entry.m_enabled = false;
    entry.m_kind = 2;
    entry.m_firstPlain.set(first);
    entry.m_secondPlain.set(second);

    if (first.bits.any())
    {
        entry.m_enabled = true;
        handle = bfmeInternAttributeEntry(&entry);
        return;
    }
    reinterpret_cast<RespawnPolicyMember *>(this)->setPolicies(
        *reinterpret_cast<const RespawnPolicy *>(&Rva012ED8B8NoneMask),
        *reinterpret_cast<const RespawnPolicy *>(&Rva012ED8B8NoneMask));
}

typedef char VerifyMaskSize[sizeof(Rva0021FC80Mask) == 24 ? 1 : -1];
typedef char VerifyBaseSize[sizeof(OpenContainModuleData) == 0x168 ? 1 : -1];
typedef char VerifyObjectSize[sizeof(TransportContainModuleData) == 0x17c ? 1 : -1];
typedef char VerifyEntrySize[sizeof(Gen00043699) == 0x88 ? 1 : -1];
