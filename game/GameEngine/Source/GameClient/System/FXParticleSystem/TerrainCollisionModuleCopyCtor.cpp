// cl: /EHsc
// The retail constructor at 0x005ED110 copies the 0x005ECE20 base, copies a
// 16-bit subbase, restores three construction vtables, and copies
// TerrainCollisionModuleInfo.
// The matched TerrainCollisionModule constructor at 0x005FD550 writes the
// same final vtables and places the copied fields at +0x3C and +0x40.

namespace FXParticleSystem
{
class TerrainCollisionModuleInfo
{
public:
	TerrainCollisionModuleInfo(const TerrainCollisionModuleInfo &);
	virtual ~TerrainCollisionModuleInfo();
	char m_data[0x18];
};
}

class TerrainCollisionModuleNodeHead
{
public:
	virtual ~TerrainCollisionModuleNodeHead() {}
	char m_data[0x10];
};

class TerrainCollisionModuleSecondBase
{
public:
	virtual void slot();
};

class TerrainCollisionModuleThirdBase
{
public:
	virtual void slot();
};

class Rva005ECE20 : public TerrainCollisionModuleNodeHead,
	public TerrainCollisionModuleSecondBase,
	public TerrainCollisionModuleThirdBase
{
public:
	Rva005ECE20(const Rva005ECE20 &);
};

class TerrainCollisionModuleShortBase
{
public:
	TerrainCollisionModuleShortBase(const TerrainCollisionModuleShortBase &other)
		: m_value(other.m_value) {}
	unsigned short m_value;
	unsigned short m_padding;
};

class TerrainCollisionModuleHead : public Rva005ECE20,
	public TerrainCollisionModuleShortBase
{
public:
	TerrainCollisionModuleHead(const TerrainCollisionModuleHead &other)
		: Rva005ECE20(other), TerrainCollisionModuleShortBase(other) {}
};

namespace FXParticleSystem
{

class TerrainCollisionModule : public TerrainCollisionModuleHead,
	public TerrainCollisionModuleInfo
{
public:
	TerrainCollisionModule(const TerrainCollisionModule &);
	int m_eventFrame;
	unsigned char m_pending;
};

TerrainCollisionModule::TerrainCollisionModule(
	const TerrainCollisionModule &other)
	: TerrainCollisionModuleHead(other), TerrainCollisionModuleInfo(other),
	  m_eventFrame(other.m_eventFrame), m_pending(other.m_pending)
{
}

}
