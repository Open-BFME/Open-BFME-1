// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <list>
#include <vector>

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

	private:
	void releaseBuffer();
	void *m_data;
};

struct Gen00776240Field2C
{
	~Gen00776240Field2C();
	char m_body[0x18];
	unsigned int m_dword44;
};

struct Z1Elem0013BF00
{
	~Z1Elem0013BF00();
	char m_body[0x24];
};

typedef _STL::list<Z1Elem0013BF00> Gen00776240Field50;

class Open2Elem7716A0
{
	public:
	Open2Elem7716A0(const Open2Elem7716A0 &other);
	~Open2Elem7716A0();
	char m_storage[20];
};

typedef _STL::vector<Open2Elem7716A0> Gen00776240Field54;

struct Gen00776240Field60
{
	~Gen00776240Field60();
	char m_body[0x10];
};

struct Gen00776240Field70
{
	~Gen00776240Field70();
	char m_body[0x0c];
};

struct Gen00776240Field7C
{
	~Gen00776240Field7C();
	char m_body[0x0c];
};

struct Gen00776240FieldB0
{
	~Gen00776240FieldB0();
	unsigned int m_body[3];
};

class Gen_t_00776240_p128pod : public BFMERetailAsciiString
{
private:
	char m_raw[0x28];
	Gen00776240Field2C m_field2C;
	BFMERetailAsciiString m_string48;
	unsigned int m_dword4C;
	Gen00776240Field50 m_field50;
	Gen00776240Field54 m_field54;
	Gen00776240Field60 m_field60;
	Gen00776240Field70 m_field70;
	Gen00776240Field7C m_field7C[4];
	unsigned char m_byteAC;
	Gen00776240FieldB0 m_fieldB0;

public:
	~Gen_t_00776240_p128pod();
};

Gen_t_00776240_p128pod::~Gen_t_00776240_p128pod()
{
	Gen00776240Field50 &field50 = m_field50;
	field50.clear();
	Gen00776240Field54 &field54 = m_field54;
	field54.erase(field54.begin(), field54.end());
	m_field2C.m_dword44 = 0;
}
