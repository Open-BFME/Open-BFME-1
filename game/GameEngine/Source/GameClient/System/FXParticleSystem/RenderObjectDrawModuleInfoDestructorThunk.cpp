// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RenderObjectDrawModuleInfo dtor. Buffers @+0x10/+0x20/+0x30.

// Retail destroys this member with a direct call to
// StringBase<char>::releaseBuffer (0x00887940) -- the member is a retail
// AsciiString, not the WWLib Buffer whose own destructor is the 40-byte
// body at 0x009E1E30, so name it the way the other lifted ModuleData
// destructors already do.
class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();

private:
	unsigned char m_pad[4];
};

namespace FXParticleSystem
{

class RenderObjectDrawModuleInfoBase
{
public:
	virtual ~RenderObjectDrawModuleInfoBase() {}

private:
	unsigned char m_pad[0xc];
};

class __declspec(novtable) RenderObjectDrawModuleInfo
	: public RenderObjectDrawModuleInfoBase
{
public:
	virtual ~RenderObjectDrawModuleInfo();

private:
	BFMERetailAsciiString m_a;
	unsigned char m_gap1[0xc];
	BFMERetailAsciiString m_b;
	unsigned char m_gap2[0xc];
	BFMERetailAsciiString m_c;
};

// ??1RenderObjectDrawModuleInfo@FXParticleSystem@@UAE@XZ
RenderObjectDrawModuleInfo::~RenderObjectDrawModuleInfo()
{
}

}
