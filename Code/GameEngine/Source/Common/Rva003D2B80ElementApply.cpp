// cl: /O2 /Ob0 /EHsc
// stlport

#include <vector>

struct Rva003D2E00Region
{
	float loX;
	float loY;
	float loZ;
	float hiX;
	float hiY;
	float hiZ;
};

class Rva003D2B80Source;

extern void j_00020af4(void);
extern void j_0004afcf(void);
extern const float g_rva003D2B80NegHalf;
extern void rva003D2B80ReleaseRaw(void);

struct Gen003D1380Elem
{
	char m_body[0x3c];

	Gen003D1380Elem();
	Gen003D1380Elem(const Gen003D1380Elem &);
	~Gen003D1380Elem();
	Gen003D1380Elem &operator=(const Gen003D1380Elem &);
};

typedef _STL::vector<Gen003D1380Elem> Rva003D2B80Entries;

class Rva003D2B80Child
{
public:
	char m_pad00[8];
	char m_entries[sizeof(Rva003D2B80Entries)];
	void *m_source;
	int m_count;

	static void *operator new(unsigned int size);
	Rva003D2B80Child(Rva003D2B80Source *, float *);
};

class Rva003D2B80Source
{
public:
	char m_pad00[0x0c];
	volatile float m_step;
};

class Rva003D2E00ElementCall
{
public:
	void apply(const Rva003D2E00Region *extent);

	char m_pad00[0x10];
	Rva003D2B80Child *m_children[4];
	Rva003D2B80Source *m_source;
};

void Rva003D2E00ElementCall::apply(const Rva003D2E00Region *)
{
	for (unsigned int i = 0; i < 4; ++i)
	{
		Rva003D2B80Child *child = m_children[i];
		if (child != 0)
		{
			union
			{
				void (*raw)(void);
				void (Rva003D2B80Entries::*member)();
			} dtor;
			dtor.raw = j_00020af4;
			(((Rva003D2B80Entries *)&child->m_entries)->*dtor.member)();
			union
			{
				void (*raw)(void);
				void (*member)(void *);
			} release;
			release.raw = rva003D2B80ReleaseRaw;
			release.member(child);
		}
		float corner[2];
		if (i == 0 || i == 2)
			corner[0] = 0.0f;
		else
 			corner[0] = g_rva003D2B80NegHalf * m_source->m_step;

		if (i == 0 || i == 1)
			corner[1] = 0.0f;
		else
 			corner[1] = g_rva003D2B80NegHalf * m_source->m_step;

		m_children[i] = new Rva003D2B80Child(m_source, corner);
	}

	union
	{
		void (*raw)(void);
		void (Rva003D2B80Child::*member)(Rva003D2B80Child *, Rva003D2B80Child *, Rva003D2B80Child *);
	} update;
	update.raw = j_0004afcf;
	(m_children[0]->*update.member)(m_children[1], m_children[2], m_children[3]);
	(m_children[1]->*update.member)(m_children[0], m_children[3], m_children[2]);
	(m_children[2]->*update.member)(m_children[3], m_children[0], m_children[1]);
	(m_children[3]->*update.member)(m_children[2], m_children[1], m_children[0]);
}
