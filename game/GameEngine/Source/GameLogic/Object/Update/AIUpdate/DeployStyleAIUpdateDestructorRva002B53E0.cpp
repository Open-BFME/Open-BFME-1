// ??1DeployStyleAIUpdateRva002B53E0@@UAE@XZ
// Open-BFME5: clean C++ recovery of the 113-byte destructor at 0x002B53E0.
// The address-derived class identity is intentional: this destructor's
// member/base identities are not yet named in the ledger.
// cl: /DNDEBUG /MD /EHsc

class Object;

class GiantBirdAIBase
{
public:
	virtual ~GiantBirdAIBase();
	unsigned int m_04;
	Object *m_object;
};

class __declspec(novtable) DeployStyleAIUpdateIface1D
{
public: virtual void anchor1();
};

class __declspec(novtable) DeployStyleAIUpdateIface2D
{
public:
	virtual void anchor2();
	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
};

class __declspec(novtable) DeployStyleAIUpdateIface3D
{
public: virtual void anchor3();
};

class __declspec(novtable) DeployStyleAIUpdateIface4D
{
public:
	virtual void anchor4();
	unsigned char m_body[0x318];
};

class GiantBirdMemberA
{
public:
	~GiantBirdMemberA();
	unsigned char m_body[0xa0];
};

class DeployStyleAIUpdateRva002B53E0 : public GiantBirdAIBase,
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
