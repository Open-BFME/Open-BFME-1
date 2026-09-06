// Fuzzy twin (tools/fuzzy_twin_scan.py) of Rva007873C0VectorHolderDestructor.cpp: the
// same base-vtable-restore + node-alloc vector free, for 12-byte elements with the
// vector at +0x10 and the BfmeBaseVUQ vtable at 0x01073744. Address-derived names.
// cl: /DNDEBUG /MD /EHsc /O2

extern int bfmeVtable000A1B30[];
void __cdecl bfmeFreeLarge000A1B30(void *memory);
void __cdecl bfmeFreeSmall000A1B30(void *memory, unsigned int bytes);

class Rva000A1B30Base
{
public:
	~Rva000A1B30Base() { m_table = bfmeVtable000A1B30; }
	void *m_table;
};

class Rva000A1B30Vector
{
public:
	struct Element { int m_words[3]; };

	~Rva000A1B30Vector()
	{
		Element *begin = m_begin;
		if (begin != 0) {
			unsigned int bytes = (unsigned int)(m_capacityEnd - begin) * sizeof(Element);
			if (bytes > 0x80)
				bfmeFreeLarge000A1B30(begin);
			else
				bfmeFreeSmall000A1B30(begin, bytes);
		}
	}

	Element *m_begin;
	Element *m_end;
	Element *m_capacityEnd;
};

class Rva000A1B30Holder : public Rva000A1B30Base
{
public:
	~Rva000A1B30Holder();
	int m_pad04;
	int m_pad08;
	int m_pad0C;
	Rva000A1B30Vector m_vector;
};

// @??1Rva000A1B30Holder@@QAE@XZ 0x000A1B30
Rva000A1B30Holder::~Rva000A1B30Holder()
{
}
