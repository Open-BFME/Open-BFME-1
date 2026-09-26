// cl: /DNDEBUG /MD /EHsc

// The no-argument constructor at retail 0x0036CDD0. The body is right; the name
// it carried was not.
//
// It was claimed as CastleMemberBehavior's two-argument constructor through an
// object-symbol note that spelled a no-argument one. Neither is this body: it
// takes no arguments, writes one vftable pointer, fills +0x08..+0x14 with
// 0xFFFFFFFE and then plants the constants 11, 12 and 10 - the shape of a
// module data constructor laying down INI defaults, not of a module. The
// pin baseline agrees, offering it as a candidate for six different
// *ModuleData no-argument constructors and resolving none of them.
//
// So the class keeps the layout the bytes prove and gives up the name it could
// not support. CastleMemberBehaviorModuleData's real two-argument constructor is
// 0x0036CEA0, eighty-four bytes, converted separately.

class CastleMemberBehaviorModuleData
{
public:
	CastleMemberBehaviorModuleData();
	virtual ~CastleMemberBehaviorModuleData();

private:
	unsigned int m_gap4;
	unsigned int m_08;
	unsigned int m_0c;
	unsigned int m_10;
	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
	unsigned int m_20;
	unsigned int m_24;
	unsigned char m_28;
	unsigned char m_29;
};

// ??0CastleMemberBehaviorModuleData@@QAE@XZ
CastleMemberBehaviorModuleData::CastleMemberBehaviorModuleData()
{
	unsigned int n = 0xfffffffeu;
	m_08 = n;
	m_0c = n;
	m_10 = n;
	m_14 = n;
	m_18 = 0xb;
	m_1c = 0xc;
	m_20 = 0xa;
	m_24 = 0;
	m_28 = 0;
	m_29 = 0;
}