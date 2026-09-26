// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// 0x0019A2D0: keyed append into a 32-slot table at this+0x66C (0x1C-byte
// slots: NameKeyType key then two STLport vectors of the 140-byte element).
// The first scan looks for the requested key; failing that, the second scan
// claims the first slot still holding the "UNASSIGNED" key (re-resolved via
// TheNameKeyGenerator on every iteration) and stamps the new key into it.
// The list selector 0/1 picks which vector receives the inlined push_back.
// Sole caller is the chunk parser at 0x0019A470. Owning class is not recovered.

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);	///< ILT 0x0003ADD7
};

extern NameKeyGenerator *TheNameKeyGenerator;	///< retail [0x012ED600]

struct Rva001999C0Element
{
	char m_body[140];
};

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type>
void __cdecl BfmeElementConstruct(Type *destination, const Type &value);

template <class Type, class Allocator>
class vector
{
public:
	void push_back(const Type &value)
	{
		if (_M_finish != _M_end_of_storage)
		{
			BfmeElementConstruct(_M_finish, value);
			++_M_finish;
		}
		else
		{
			__false_type tag;
			_M_insert_overflow(_M_finish, value, tag, 1, true);
		}
	}

protected:
	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd);

	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};
}

typedef _STL::vector<Rva001999C0Element, _STL::allocator<Rva001999C0Element> > Rva001999C0Vector;

struct Rva0019A2D0Slot
{
	NameKeyType m_key;
	Rva001999C0Vector m_list0;
	Rva001999C0Vector m_list1;
};

class Rva0019A2D0Table
{
public:
	void appendKeyed(NameKeyType key, const Rva001999C0Element *element, int list);

private:
	char m_body0000[0x66C];
	Rva0019A2D0Slot m_slots[32];
};

void Rva0019A2D0Table::appendKeyed(NameKeyType key, const Rva001999C0Element *element, int list)
{
	int i;
	for (i = 0; i < 32; ++i)
	{
		if (m_slots[i].m_key == key)
		{
			if (list == 0)
				m_slots[i].m_list0.push_back(*element);
			else if (list == 1)
				m_slots[i].m_list1.push_back(*element);
			return;
		}
	}
	for (i = 0; i < 32; ++i)
	{
		if (m_slots[i].m_key == TheNameKeyGenerator->nameToKey("UNASSIGNED"))
		{
			m_slots[i].m_key = key;
			if (list == 0)
				m_slots[i].m_list0.push_back(*element);
			else if (list == 1)
				m_slots[i].m_list1.push_back(*element);
			return;
		}
	}
}
