// ??1DeployStyleAIUpdateRva002B53E0@@UAE@XZ
// partial score=0.99 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

class Object;

class BehaviorModule2B53E0
{
public:
	virtual ~BehaviorModule2B53E0();
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

class DeployStyleAIUpdateMemberD
{
public:
	~DeployStyleAIUpdateMemberD();
	unsigned char m_body[0xa0];
};

class DeployStyleAIUpdateBaseD : public BehaviorModule2B53E0
{
public: virtual ~DeployStyleAIUpdateBaseD();
};

class DeployStyleAIUpdateRva002B53E0 : public DeployStyleAIUpdateBaseD,
	public DeployStyleAIUpdateIface1D,
	public DeployStyleAIUpdateIface2D,
	public DeployStyleAIUpdateIface3D,
	public DeployStyleAIUpdateIface4D
{
public:
	virtual ~DeployStyleAIUpdateRva002B53E0();

private:
	DeployStyleAIUpdateMemberD m_member;
};

// @??1DeployStyleAIUpdateRva002B53E0@@UAE@XZ 0x002B53E0
DeployStyleAIUpdateRva002B53E0::~DeployStyleAIUpdateRva002B53E0()
{
}
