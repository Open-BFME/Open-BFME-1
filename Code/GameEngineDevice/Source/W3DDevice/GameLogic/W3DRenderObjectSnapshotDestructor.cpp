// cl: /DNDEBUG /MD /EHsc

class Snapshot
{
public:
	virtual void anchor();
	~Snapshot();
};

class Gen_dtor_009eb9e0
{
public:
	~Gen_dtor_009eb9e0();
};

class W3DRenderObjectSnapshot : public Snapshot
{
public:
	virtual ~W3DRenderObjectSnapshot();

private:
	void *m_debugName;
	Gen_dtor_009eb9e0 *m_renderObject;
};

W3DRenderObjectSnapshot::~W3DRenderObjectSnapshot()
{
	delete m_renderObject;
}
