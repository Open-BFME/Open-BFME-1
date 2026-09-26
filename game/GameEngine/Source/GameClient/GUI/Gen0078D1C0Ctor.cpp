// cl: /O2 /Ob1 /GF /Gy /MD /EHsc /GR /DNDEBUG /DWIN32 /D_WINDOWS

class Gen0078D1C0Base
{
public:
	~Gen0078D1C0Base();
};

class Gen0078D1C0Registry
{
public:
	Gen0078D1C0Registry();
	virtual ~Gen0078D1C0Registry();

private:
	char m_unreconstructed[ 0xC8 ];
};

class Gen0078D1C0 : public Gen0078D1C0Base
{
public:
	Gen0078D1C0();
	virtual ~Gen0078D1C0();

private:
	Gen0078D1C0Registry m_registry;
	int m_first;
	int m_second;
	unsigned int m_color;
	bool m_firstFlag;
	bool m_secondFlag;
};

Gen0078D1C0::Gen0078D1C0()
{
	m_second = 0;
	m_first = 0;
	m_firstFlag = false;
	m_secondFlag = false;
	m_color = 0x00FFFFFF;
}
