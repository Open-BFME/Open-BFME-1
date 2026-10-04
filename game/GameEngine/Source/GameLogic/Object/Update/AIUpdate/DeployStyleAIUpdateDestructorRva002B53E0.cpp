// ??1DeployStyleAIUpdateRva002B53E0@@UAE@XZ
// Open-BFME5: clean C++ recovery of the 113-byte destructor at 0x002B53E0.
// The address-derived class identity is intentional: this destructor's
// derived-class identity is not yet named in the ledger.
// cl: /DNDEBUG /MD /EHsc
//
// Retail's dtor stores five vftable addresses into `this` at +0x00, +0x0C,
// +0x10, +0x20 and +0x24 and makes two direct calls:
//   0x00008B61  a scalar member destructor (the 0x340 subobject)
//   0x0001C774  the base-class destructor, whose ILT routes to
//               ??1AIUpdateInterface@@UAE@XZ (0x0027EF60, the ledger row in
//               game/GameEngine/Source/GameLogic/Object/Update/
//               AIUpdateInterfaceDestructors.cpp). The base was spelled
//               GiantBirdAIBase here, a name nothing defines, so the object
//               did not link; respelling it to AIUpdateInterface keeps the
//               same thiscall and the same slot offsets.
//
// The four interface bases carry a single pure virtual each. They exist only
// to give the derived class one vtable slot per base, so the derived class
// emits one secondary vftable per base, exactly as retail does. They were
// spelled as open (undefined) virtuals `anchor1..anchor4`, which left four
// undefined symbols in the object's vftables and blocked the link. Pure
// virtual slots fill with the CRT's _purecall entry instead, so no symbol is
// referenced. The dtor body itself is unchanged: it only stores the vftable
// addresses, and those relocations are masked.
class Object;

// Retail's 0x0027EF60 body; declared, never defined here, so the link picks
// up AIUpdateInterfaceDestructors.cpp's matched row.
class AIUpdateInterface
{
public:
	virtual ~AIUpdateInterface();
	unsigned int m_04;
	Object *m_object;
};

class __declspec(novtable) DeployStyleAIUpdateIface1D
{
public: virtual void anchor1() = 0;
};

class __declspec(novtable) DeployStyleAIUpdateIface2D
{
public: virtual void anchor2() = 0;
	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
};

class __declspec(novtable) DeployStyleAIUpdateIface3D
{
public: virtual void anchor3() = 0;
};

class __declspec(novtable) DeployStyleAIUpdateIface4D
{
public: virtual void anchor4() = 0;
	unsigned char m_body[0x318];
};

class GiantBirdMemberA
{
public:
	~GiantBirdMemberA();
	unsigned char m_body[0xa0];
};

class DeployStyleAIUpdateRva002B53E0 : public AIUpdateInterface,
	public DeployStyleAIUpdateIface1D,
	public DeployStyleAIUpdateIface2D,
	public DeployStyleAIUpdateIface3D,
	public DeployStyleAIUpdateIface4D
{
public:
	virtual ~DeployStyleAIUpdateRva002B53E0();

private:
	GiantBirdMemberA m_member;
};

// @??1DeployStyleAIUpdateRva002B53E0@@UAE@XZ 0x002B53E0
DeployStyleAIUpdateRva002B53E0::~DeployStyleAIUpdateRva002B53E0()
{
}