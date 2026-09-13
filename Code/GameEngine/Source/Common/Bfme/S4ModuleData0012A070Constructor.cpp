// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// stlport
// Open-BFME: S4ModuleData0012A070::S4ModuleData0012A070, retail 0x00129F80,
// 189 bytes.
//
// Same OpenContain + interned filter-handle shape as
// TransportContainModuleData at 0x0021FC80. After the base constructor this
// class stores 1.0f at +0x168 and sets the +0x114 handle from KINDOF_INFANTRY
// (bit 8) against KINDOFMASK_NONE. The factory
// s4newModuleData0012A070 (0x0012A070) is the named caller; the vftable at
// 0x0108F020 is installed only here.
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

class S4ModuleData0012A070 : public OpenContainModuleData
{
public:
	S4ModuleData0012A070();
	virtual ~S4ModuleData0012A070();

	float m_fraction;
};

// ??0S4ModuleData0012A070@@QAE@XZ
S4ModuleData0012A070::S4ModuleData0012A070()
{
	m_fraction = 1.0f;
	m_filter.setMasks(Rva0021FC80Mask(8), Rva012ED8B8NoneMask);
}

typedef char VerifyMaskSize[sizeof(Rva0021FC80Mask) == 24 ? 1 : -1];
typedef char VerifyBaseSize[sizeof(OpenContainModuleData) == 0x168 ? 1 : -1];
typedef char VerifyObjectSize[sizeof(S4ModuleData0012A070) == 0x16c ? 1 : -1];
