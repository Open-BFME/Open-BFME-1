// Dword setters whose identities are not recovered; each class name is the retail RVA.
// All share the bytes mov eax,[esp+4]; mov [ecx+disp32],eax; ret 4 with a ParticleEmitterDefClass setter.
// Evidence: targets/game/reverse/identity_evidence/particle-emitter-def-vtable.md.

class Rva001065F0
{
public:
	void set(unsigned int value);
	char m_lead[0x20C];
	unsigned int m_value;
};

void Rva001065F0::set(unsigned int value)
{
	m_value = value;
}

class Rva0021A220
{
public:
	void set(unsigned int value);
	char m_lead[0x214];
	unsigned int m_value;
};

void Rva0021A220::set(unsigned int value)
{
	m_value = value;
}

class Rva00253D20
{
public:
	void set(unsigned int value);
	char m_lead[0x218];
	unsigned int m_value;
};

void Rva00253D20::set(unsigned int value)
{
	m_value = value;
}

class Rva0026F930
{
public:
	void set(unsigned int value);
	char m_lead[0x164];
	unsigned int m_value;
};

void Rva0026F930::set(unsigned int value)
{
	m_value = value;
}

class Rva002B6860
{
public:
	void set(unsigned int value);
	char m_lead[0x128];
	unsigned int m_value;
};

void Rva002B6860::set(unsigned int value)
{
	m_value = value;
}

class Rva0035F090
{
public:
	void set(unsigned int value);
	char m_lead[0x13C];
	unsigned int m_value;
};

void Rva0035F090::set(unsigned int value)
{
	m_value = value;
}
