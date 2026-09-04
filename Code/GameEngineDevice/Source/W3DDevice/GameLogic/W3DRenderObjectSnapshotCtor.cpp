// ??0W3DRenderObjectSnapshot@@QAE@XZ
// cl: /DNDEBUG /MD /EHsc

class BfmeBase1134
{
public:
	BfmeBase1134();
	virtual ~BfmeBase1134();

private:
	int m_value;
};

class Gen_dtor_009eb9e0
{
public:
	Gen_dtor_009eb9e0();
	~Gen_dtor_009eb9e0();

private:
	char m_data[0x1F4];
};

class W3DRenderObjectSnapshot : public BfmeBase1134
{
public:
	W3DRenderObjectSnapshot();
	virtual ~W3DRenderObjectSnapshot();

private:
	Gen_dtor_009eb9e0 *m_renderObject;
};

W3DRenderObjectSnapshot::W3DRenderObjectSnapshot()
{
	m_renderObject = new Gen_dtor_009eb9e0;
}
