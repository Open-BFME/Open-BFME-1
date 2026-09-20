// cl: /DNDEBUG /MD
// stlport

#include <vector>

class Rva001605F0
{
	void *m_00;
	char m_padding[0x08];
	void *m_0c;
	void *m_10;

public:
	int test(Rva001605F0 *other);
};

// ?test@Rva001605F0@@QAEHPAV1@@Z
int Rva001605F0::test(Rva001605F0 *other)
{
	if (other->m_00 == this || m_0c || m_10)
		return 1;
	return 0;
}

class Rva001D5CD0Prefix
{
private:
	char m_padding[0x20];
};

struct Gen_t_001d2940_p16cd
{
	int a[4];
	Gen_t_001d2940_p16cd();
	Gen_t_001d2940_p16cd(const Gen_t_001d2940_p16cd &);
	~Gen_t_001d2940_p16cd();
	Gen_t_001d2940_p16cd &operator=(const Gen_t_001d2940_p16cd &);
};

class Rva001D5CD0Owner : public Rva001D5CD0Prefix
{
public:
	void clear();

private:
	_STL::vector<Gen_t_001d2940_p16cd> m_resources;
};

// ?clear@Rva001D5CD0Owner@@QAEXXZ
void Rva001D5CD0Owner::clear()
{
	_STL::vector<Gen_t_001d2940_p16cd> *resources = &m_resources;
	resources->erase(resources->begin(), resources->end());
}
