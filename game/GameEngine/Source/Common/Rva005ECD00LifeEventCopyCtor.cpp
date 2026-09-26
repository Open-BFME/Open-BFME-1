// cl: /EHsc
// The retail constructor at 0x005ECD00 copies the Rva005ECE20 base, copies a
// 16-bit subbase, restores three vtable slots, and copies LifeEventModuleInfo.
// The existing Rva005ECE20 and LifeEventModuleInfo constructors prove the two
// calls.  The 0x1c subbase and the trailing fields come from the retail offsets.

namespace FXParticleSystem
{
class LifeEventModuleInfo
{
public:
	LifeEventModuleInfo(const LifeEventModuleInfo &);
	virtual ~LifeEventModuleInfo();
	char m_data[0x14];
};
}

class Rva005ECD00NodeHead
{
public:
	virtual ~Rva005ECD00NodeHead() {}
	char m_data[0x10];
};

class Rva005ECD00SecondBase
{
public:
	virtual void slot();
};

class Rva005ECD00ThirdBase
{
public:
	virtual void slot();
};

class Rva005ECE20 : public Rva005ECD00NodeHead,
	public Rva005ECD00SecondBase, public Rva005ECD00ThirdBase
{
public:
	Rva005ECE20(const Rva005ECE20 &);
};

class Rva005ECD00ShortBase
{
public:
	Rva005ECD00ShortBase(const Rva005ECD00ShortBase &other)
		: m_value(other.m_value) {}
	unsigned short m_value;
	unsigned short m_padding;
};

class Rva005ECD00Head : public Rva005ECE20, public Rva005ECD00ShortBase
{
public:
	Rva005ECD00Head(const Rva005ECD00Head &other)
		: Rva005ECE20(other), Rva005ECD00ShortBase(other) {}
};

class Rva005ECD00 : public Rva005ECD00Head,
	public FXParticleSystem::LifeEventModuleInfo
{
public:
	Rva005ECD00(const Rva005ECD00 &);
	int m_value;
	unsigned char m_flag;
};

Rva005ECD00::Rva005ECD00(const Rva005ECD00 &other)
	: Rva005ECD00Head(other), FXParticleSystem::LifeEventModuleInfo(other),
	  m_value(other.m_value), m_flag(other.m_flag)
{
}
