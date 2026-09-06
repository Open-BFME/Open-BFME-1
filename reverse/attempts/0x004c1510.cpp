// ?d_004c1510@@YAXXZ
// partial score=0.75 date=2026-09-06
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva004C1510RefCounted
{
public:
	virtual void release(int deletingFlag);
};

class Rva004C1510Ref
{
public:
	Rva004C1510Ref &operator=(Rva004C1510RefCounted *value);

	Rva004C1510RefCounted *m_value;
};

class Rva004C1510ReleaseGuard
{
public:
	Rva004C1510ReleaseGuard(Rva004C1510RefCounted *value) : m_value(value) {}
	~Rva004C1510ReleaseGuard()
	{
		if (m_value != 0)
			m_value->release(1);
	}

	Rva004C1510RefCounted *m_value;
};

Rva004C1510Ref &Rva004C1510Ref::operator=(Rva004C1510RefCounted *value)
{
	{
		Rva004C1510ReleaseGuard guard(m_value);
	}
	m_value = value;
	return *this;
}
