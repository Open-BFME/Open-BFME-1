// cl: /O2 /Ob1
// stlport

#include <vector>

struct Gen_p12pod { int a[3]; };

class Rva007D85C0ComRef
{
public:
	virtual long __stdcall QueryInterface() = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};

class Rva007D85C0
{
public:
	int shutdown();

private:
	void *m_vptr;
	Rva007D85C0ComRef *m_04;
	unsigned char m_pad08[0x08];
	_STL::vector<Gen_p12pod> m_vec;
	Rva007D85C0ComRef *m_1C;
	Rva007D85C0ComRef *m_20;
	Rva007D85C0ComRef *m_24;
	Rva007D85C0ComRef *m_28;
};

int Rva007D85C0::shutdown()
{
	if (m_04) m_04->Release();
	m_04 = 0;
	m_vec.clear();
	if (m_24) m_24->Release();
	m_24 = 0;
	if (m_1C) m_1C->Release();
	m_1C = 0;
	if (m_28) m_28->Release();
	m_28 = 0;
	if (m_20) m_20->Release();
	m_20 = 0;
	return 1;
}
