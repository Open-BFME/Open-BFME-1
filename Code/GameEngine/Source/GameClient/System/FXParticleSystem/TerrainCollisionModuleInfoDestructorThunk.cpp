// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: TerrainCollisionModuleInfo dtor. SEH BFMERetailAsciiString @+0x4 PropagandaTower pattern.

// Retail destroys this member with a direct call to
// StringBase<char>::releaseBuffer (0x00887940) -- the member is a retail
// AsciiString, not the WWLib Buffer whose own destructor is the 40-byte
// body at 0x009E1E30. The matched constructor and copy constructor call this
// member m_eventName at the same +0x04 offset.
class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
};

namespace FXParticleSystem
{

class TerrainCollisionModuleInfoBase
{
public:
	virtual ~TerrainCollisionModuleInfoBase() {}
};

class __declspec(novtable) TerrainCollisionModuleInfo : public TerrainCollisionModuleInfoBase
{
public:
	virtual ~TerrainCollisionModuleInfo();
private:
	BFMERetailAsciiString m_eventName;
};

// ??1TerrainCollisionModuleInfo@FXParticleSystem@@UAE@XZ
TerrainCollisionModuleInfo::~TerrainCollisionModuleInfo()
{
}

} // namespace FXParticleSystem
