// cl: /DNDEBUG /MD /EHsc
// Retail 0x005E23D0, 100 bytes. The matched RenderObjectDrawModule
// constructor and concrete module factories establish the class identity;
// its base layout comes from the three target vftable stores and the matched
// RenderObjectDrawModuleInfo field layout. The two pre-info base names remain
// opaque because their exact identities are not established here.

struct GenOwner_006fa270;

struct GenNode_006fa270
{
	GenOwner_006fa270 *m_owner;
	GenNode_006fa270 *m_prev;
	GenNode_006fa270 *m_next;

	void unlink(void) throw();
	~GenNode_006fa270(void) { unlink(); }
};

class V3NodeHead
{
public:
	virtual ~V3NodeHead() {}
	GenNode_006fa270 m_node;
	int m_unreconstructed_10;
};

class V3Vt0110F97C
{
public:
	virtual void slot0();
	virtual ~V3Vt0110F97C() {}
};

class BfmeRMiddle : public V3NodeHead, public V3Vt0110F97C
{
};

namespace FXParticleSystem
{
class __declspec(novtable) RenderObjectDrawModuleInfo
{
public:
	virtual ~RenderObjectDrawModuleInfo();

private:
	unsigned char m_pad[0x3c];
};

class __declspec(novtable) RenderObjectDrawModule
	: public ::BfmeRMiddle,
	  public RenderObjectDrawModuleInfo
{
public:
	virtual ~RenderObjectDrawModule();

private:
	unsigned int m_field58;
};

RenderObjectDrawModule::~RenderObjectDrawModule()
{
}
}
