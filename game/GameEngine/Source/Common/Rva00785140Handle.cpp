// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva00785140Target
{
	int m_first;
	unsigned short m_refCount;
	unsigned short m_pad;
};

struct Rva00785140Plain
{
	Rva00785140Target *m_target;
};

class Rva00785140Handle
{
public:
	virtual void dummy();
	Rva00785140Handle(const Rva00785140Plain &other);

	Rva00785140Target *m_target;
};

Rva00785140Handle::Rva00785140Handle(const Rva00785140Plain &other)
{
	Rva00785140Target *target = other.m_target;
	m_target = target;
	if (target)
		++target->m_refCount;
}
