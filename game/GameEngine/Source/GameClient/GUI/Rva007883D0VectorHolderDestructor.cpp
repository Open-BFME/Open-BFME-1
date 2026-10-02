// cl: /DNDEBUG /MD /EHsc /O2

// Retail VA 0x01126A98: ScalarDeletingDestructors.cpp owns this table.
extern "C" int __identifier("??_7Rva00782DA0Deleting@@6B@")[];
void __cdecl operator delete(void *memory);

// The private STLport pool entry at RVA 0x0082E5F0 is a static __cdecl
// member. Refer to its exact symbol without redeclaring the allocator.
extern "C" void __cdecl __identifier("?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z")(
	void *memory, unsigned int bytes);

class Rva007883D0Base
{
public:
	~Rva007883D0Base()
	{
		m_table = __identifier("??_7Rva00782DA0Deleting@@6B@");
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
				::operator delete(m_begin);
			else
				__identifier("?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z")(m_begin, bytes);
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
