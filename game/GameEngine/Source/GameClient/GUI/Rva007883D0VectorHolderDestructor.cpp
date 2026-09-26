// cl: /DNDEBUG /MD /EHsc /O2

extern int bfmeVtable007883D0[];
void __cdecl bfmeFreeLarge007883D0(void *memory);
void __cdecl bfmeFreeSmall007883D0(void *memory, unsigned int bytes);

class Rva007883D0Base
{
public:
	~Rva007883D0Base()
	{
		m_table = bfmeVtable007883D0;
	}

	void *m_table;
};

class Rva007883D0Vector
{
public:
	struct Element
	{
		int m_words[4];
	};

	~Rva007883D0Vector()
	{
		if (m_begin != 0) {
			unsigned int bytes = (unsigned int)(m_capacityEnd - m_begin) * sizeof(Element);
			if (bytes > 0x80)
				bfmeFreeLarge007883D0(m_begin);
			else
				bfmeFreeSmall007883D0(m_begin, bytes);
		}
	}

	Element *m_begin;
	Element *m_end;
	Element *m_capacityEnd;
};

class Rva007883D0Holder : public Rva007883D0Base
{
public:
	~Rva007883D0Holder();

	char m_pad04[8];
	Rva007883D0Vector m_vector;
};

// @??1Rva007883D0Holder@@QAE@XZ 0x007883D0
Rva007883D0Holder::~Rva007883D0Holder()
{
}
