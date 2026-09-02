// cl: /DNDEBUG /MD /EHsc /O2

extern int bfmeVtable007873C0[];
void __cdecl bfmeFreeLarge007873C0(void *memory);
void __cdecl bfmeFreeSmall007873C0(void *memory, unsigned int bytes);

class Rva007873C0Base
{
public:
	~Rva007873C0Base() { m_table = bfmeVtable007873C0; }
	void *m_table;
};

class Rva007873C0Vector
{
public:
	struct Element { int m_words[6]; };

	~Rva007873C0Vector()
	{
		Element *begin = m_begin;
		if (begin != 0) {
			unsigned int bytes = (unsigned int)(m_capacityEnd - begin) * sizeof(Element);
			if (bytes > 0x80)
				bfmeFreeLarge007873C0(begin);
			else
				bfmeFreeSmall007873C0(begin, bytes);
		}
	}

	Element *m_begin;
	Element *m_end;
	Element *m_capacityEnd;
};

class Rva007873C0Holder : public Rva007873C0Base
{
public:
	~Rva007873C0Holder();
	int m_pad04;
	Rva007873C0Vector m_vector;
};

// @??1Rva007873C0Holder@@QAE@XZ 0x007873C0
Rva007873C0Holder::~Rva007873C0Holder()
{
}
