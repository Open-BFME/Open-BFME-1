// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva00894D80Accessor
{
public:
	static unsigned int increment(unsigned int *value);
};

class Rva00894D90Accessor
{
public:
	static unsigned int decrement(unsigned int *value);
};

void bfmeDropA(void *value);

class Rva00893030Ref
{
public:
	Rva00893030Ref(void *value) : m_value(value) {}
	Rva00893030Ref(const Rva00893030Ref &other) : m_value(other.m_value)
	{
		if (m_value)
			Rva00894D80Accessor::increment((unsigned int *)m_value);
	}
	~Rva00893030Ref()
	{
		if (m_value && Rva00894D90Accessor::decrement((unsigned int *)m_value) == 0)
			bfmeDropA(m_value);
	}

	void *m_value;
};

class Rva00893030Manager
{
public:
	void invoke(Rva00893030Ref value, void *first, void *second, void *third);
};

extern Rva00893030Manager *g_rva00893030Manager;

void Rva00893030(Rva00893030Ref value, void *first, void *second, void *third)
{
	g_rva00893030Manager->invoke(value, first, second, third);
}
