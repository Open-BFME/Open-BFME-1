// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

__declspec(dllimport) void __cdecl operator delete(void *, unsigned int);

class Rva008C5B70Buf
{
public:
	void clear();

private:
	int m_pad;
	unsigned int m_count;
	void *m_ptr;
};

void Rva008C5B70Buf::clear()
{
	if (m_ptr)
		operator delete(m_ptr, m_count * sizeof(unsigned int));
	m_count = 0;
	m_pad = 0;
	m_ptr = 0;
}

class Rva008C5C40Buf
{
public:
	void clear();

private:
	int m_pad;
	unsigned int m_count;
	void *m_ptr;
};

void Rva008C5C40Buf::clear()
{
	if (m_ptr)
		operator delete(m_ptr, m_count * sizeof(unsigned int));
	m_count = 0;
	m_pad = 0;
	m_ptr = 0;
}

class Rva008C5D00Buf
{
public:
	void clear();

private:
	int m_pad;
	unsigned int m_count;
	void *m_ptr;
};

void Rva008C5D00Buf::clear()
{
	if (m_ptr)
		operator delete(m_ptr, m_count * sizeof(unsigned int));
	m_count = 0;
	m_pad = 0;
	m_ptr = 0;
}

class Rva008C5DC0Buf
{
public:
	void clear();

private:
	int m_pad;
	unsigned int m_dim1;
	unsigned int m_dim2;
	void *m_ptr;
};

void Rva008C5DC0Buf::clear()
{
	if (m_ptr)
		operator delete(m_ptr, (m_dim2 * m_dim1) * sizeof(unsigned int));
	m_dim1 = 0;
	m_dim2 = 0;
	m_pad = 0;
	m_ptr = 0;
}
