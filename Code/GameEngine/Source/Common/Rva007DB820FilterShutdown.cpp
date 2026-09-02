// cl: /O2 /Ob0

class Rva007DB820ComRef
{
public:
	virtual long __stdcall QueryInterface() = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};

class Rva007DB820
{
public:
	int shutdown();

private:
	void *m_vptr;
	Rva007DB820ComRef *m_04;
	Rva007DB820ComRef *m_08;
	Rva007DB820ComRef *m_0C;
	unsigned char m_pad10[0x08];
	Rva007DB820ComRef *m_18;
	Rva007DB820ComRef *m_1C;
	unsigned char m_pad20[0x24];
	Rva007DB820ComRef *m_44;
	Rva007DB820ComRef *m_48;
	Rva007DB820ComRef *m_4C;
	Rva007DB820ComRef *m_50;
};

int Rva007DB820::shutdown()
{
	if (m_04) m_04->Release();
	if (m_08) m_08->Release();
	if (m_0C) m_0C->Release();
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	if (m_1C) m_1C->Release();
	m_1C = 0;
	if (m_18) m_18->Release();
	m_18 = 0;
	if (m_4C) m_4C->Release();
	m_4C = 0;
	if (m_44) m_44->Release();
	m_44 = 0;
	if (m_50) m_50->Release();
	m_50 = 0;
	if (m_48) m_48->Release();
	m_48 = 0;
	return 1;
}
