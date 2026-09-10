// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// stlport
// TransportContainModuleData, retail 0x0021FC80, 216 bytes.
// BFME stores an interned object-filter handle at +0x114, rather than
// the Generals source's inline allow/deny masks. The setter takes two
// six-word masks by value and releases/replaces that handle.
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

// ??0TransportContainModuleData@@QAE@XZ
TransportContainModuleData::TransportContainModuleData()
{
    m_filter.setMasks(Rva0021FC80Mask(8), Rva012ED8B8NoneMask);
    m_flag170 = false;
    m_flag168 = false;
    m_flag171 = false;
    m_initialPayloadCount = 0;
    m_scalar16c = 1.0f;
}
typedef char VerifyMaskSize[sizeof(Rva0021FC80Mask) == 24 ? 1 : -1];
typedef char VerifyBaseSize[sizeof(OpenContainModuleData) == 0x168 ? 1 : -1];
typedef char VerifyObjectSize[sizeof(TransportContainModuleData) == 0x17c ? 1 : -1];
