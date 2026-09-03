// cl: /DNDEBUG /MD /EHsc
// Exact C++ reconstruction of the generated destructor at retail 0x001A7350.
// The recovered layout is deliberately local: a vptr, an unknown word, the
// AsciiString at +8, and the owned polymorphic member at +0x8c.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class Gen_dtor_001a87f0_Owned
{
public:
	virtual ~Gen_dtor_001a87f0_Owned();
};

class Gen_dtor_001a87f0
{
public:
	virtual ~Gen_dtor_001a87f0();

private:
	unsigned char m_unknown04[4];
	AsciiString m_name;
	unsigned char m_unknown0c[0x80];
	Gen_dtor_001a87f0_Owned *m_owned;
};

Gen_dtor_001a87f0::~Gen_dtor_001a87f0()
{
	if (m_owned) {
		delete m_owned;
		m_owned = 0;
	}
}
