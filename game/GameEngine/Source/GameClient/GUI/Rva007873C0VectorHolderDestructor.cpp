// cl: /DNDEBUG /MD /EHsc /O2

// Retail VA 0x01126A98: ScalarDeletingDestructors.cpp owns this table.
extern "C" int __identifier("??_7Rva00782DA0Deleting@@6B@")[];
void __cdecl operator delete(void *memory);

// Refer to the private STLport pool entry without redeclaring the allocator.
extern "C" void __cdecl __identifier("?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z")(
	void *memory, unsigned int bytes);

class Rva007873C0Base
{
public:
	~Rva007873C0Base() { m_table = __identifier("??_7Rva00782DA0Deleting@@6B@"); }
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
				::operator delete(begin);
			else
				__identifier("?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z")(begin, bytes);
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
