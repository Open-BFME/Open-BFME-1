// cl: /O2 /Ob0

class Rva007D6B70ComRef
{
public:
	virtual long __stdcall QueryInterface() = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};

class Rva007D6B70
{
public:
	int shutdown();

private:
	void *m_vptr;
	Rva007D6B70ComRef *m_04;
	Rva007D6B70ComRef *m_08;
	Rva007D6B70ComRef *m_0C;
	unsigned char m_pad10[0x08];
	Rva007D6B70ComRef *m_18;
	Rva007D6B70ComRef *m_1C;
	unsigned char m_pad20[0x18];
	Rva007D6B70ComRef *m_38;
	Rva007D6B70ComRef *m_3C;
	Rva007D6B70ComRef *m_40;
	Rva007D6B70ComRef *m_44;
};

int Rva007D6B70::shutdown()
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
	if (m_40) m_40->Release();
	m_40 = 0;
	if (m_38) m_38->Release();
	m_38 = 0;
	if (m_44) m_44->Release();
	m_44 = 0;
	if (m_3C) m_3C->Release();
	m_3C = 0;
	return 1;
}
