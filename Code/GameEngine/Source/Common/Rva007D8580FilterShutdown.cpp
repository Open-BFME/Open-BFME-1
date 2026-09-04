// cl: /O2 /Ob1
// stlport

#include <vector>

struct Gen_p12pod { int a[3]; };

class Rva007D8580ComRef
{
public:
	virtual long __stdcall QueryInterface() = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};

class Rva007D8580
{
public:
	int shutdown();

private:
	void *m_vptr;
	Rva007D8580ComRef *m_04;
	Rva007D8580ComRef *m_08;
	unsigned char m_pad0C[0x0c];
	_STL::vector<Gen_p12pod> m_vec;
	Rva007D8580ComRef *m_24;
	Rva007D8580ComRef *m_28;
	Rva007D8580ComRef *m_2C;
	Rva007D8580ComRef *m_30;
};

int Rva007D8580::shutdown()
{
	if( m_04 ) m_04->Release();
	if( m_08 ) m_08->Release();
	m_04 = 0;
	m_08 = 0;
	m_vec.clear();
	if( m_2C ) m_2C->Release();
	m_2C = 0;
	if( m_24 ) m_24->Release();
	Rva007D8580ComRef **slot24 = &m_24;
	*slot24 = 0;
	if( m_28 ) m_28->Release();
	m_28 = 0;
	if( m_30 ) m_30->Release();
	m_30 = 0;
	return 1;
}
