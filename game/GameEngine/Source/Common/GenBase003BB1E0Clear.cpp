// stlport
#include <set>
#include <vector>

// Open-BFME5: GenBase003BB1E0::clear, retail 0x003B9450.
// The vector element layout is proven by the 0x14-byte stride in retail and
// by the owning class destructor in V4StringMemberEhDtors.cpp.

class BfmeRefObject003B9450
{
public:
	virtual void destroy();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void detach();

	int m_refs;
};

struct Gen_t_00234730_m4pod
{
	int m_value;
};

bool operator<(const Gen_t_00234730_m4pod &left,
	const Gen_t_00234730_m4pod &right);

struct Mem003BB060Element
{
	int m_at00;
	BfmeRefObject003B9450 *m_at04;
	_STL::set<Gen_t_00234730_m4pod> m_at08;
};

typedef char Mem003BB060ElementMustBe20[
	sizeof(Mem003BB060Element) == 0x14 ? 1 : -1];

class GenBase003BB1E0
{
public:
	void clear();

private:
	char m_pad00[0x14];
	_STL::vector<Mem003BB060Element> m_at14;
	bool m_at20;
};

void GenBase003BB1E0::clear()
{
	for (_STL::vector<Mem003BB060Element>::iterator it = m_at14.begin();
		it != m_at14.end(); ++it)
	{
		BfmeRefObject003B9450 *object = it->m_at04;
		if (object)
		{
			object->detach();
			object = it->m_at04;
			if (--object->m_refs == 0)
				object->destroy();
			it->m_at04 = 0;
		}

		it->m_at08.clear();
	}

	m_at20 = false;
}
