// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// partial score=0.977 date=2026-09-17
// stlport



extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)



// The BFME field table reaches this callback through the ILT at 0x0000EE71.
// Its owner is not named by a live caller, so the symbol keeps the proven
// retail address while the callback signature and parser role are explicit.

typedef unsigned int UnsignedInt;

struct FieldParse;
class GenItem;

class INI
{
public:
	const char *getNextTokenOrNull(const char *previous);
	void initFromINI(void *instance, const FieldParse *fieldParse);
};

class BFMERetailAsciiString
{
protected:
	BFMERetailAsciiString() : m_data(0) {}
	void releaseBuffer();

	void *m_data;
};

class AsciiString : private BFMERetailAsciiString
{
public:
	AsciiString() : BFMERetailAsciiString() {}
	~AsciiString()
	{
		BFMERetailAsciiString::releaseBuffer();
	}
	AsciiString &operator=(const char *text);
};

class UnicodeString
{
public:
	void set(const UnicodeString &source);

	void *m_data;
};

struct Gen000140D8
{
	UnsignedInt m_words[10];

	bool handle(GenItem *item, bool *first, bool *second);
};

struct Rva0077CC10Element
{
	Rva0077CC10Element();
	Rva0077CC10Element(const Rva0077CC10Element &source);
	~Rva0077CC10Element();

	UnicodeString m_name;
	unsigned char m_tail[188 - sizeof(UnicodeString)];
};

struct Rva0077D150ElementSlot
{
	volatile unsigned int m_stackPad0;
	volatile unsigned int m_stackPad1;
	Rva0077CC10Element value;
};

struct Gen_t_00776240_p128pod
{
	UnsignedInt m_words[47];

	Gen_t_00776240_p128pod();
	Gen_t_00776240_p128pod(const Gen_t_00776240_p128pod &source);
	~Gen_t_00776240_p128pod();
	Gen_t_00776240_p128pod &operator=(const Gen_t_00776240_p128pod &source);
};

inline void *operator new(unsigned int bytes, void *where) throw()
{
	return where;
}

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
__forceinline void BfmeElementConstruct(Type *destination, const Type &source)
{
	new (destination) Type(source);
}

template <>
__forceinline void BfmeElementConstruct(Rva0077CC10Element *destination,
	const Rva0077CC10Element &source)
{
	new (destination) Rva0077CC10Element(source);
}

template <class Type, class Allocator>
class vector
{
public:
	typedef Type *iterator;

	iterator begin()
	{
		return m_start;
	}

	iterator insert(iterator position, const Type &value);

	void push_back(const Type &value)
	{
		Type *finish = m_finish;
		Type *end = m_end_of_storage;
		Type *destination = finish;
		if (finish != end)
		{
			if (destination != 0)
				BfmeElementConstruct(destination, value);
			finish = m_finish;
			++finish;
			m_finish = finish;
		}
		else
		{
			_STL::__false_type tag;
			_M_insert_overflow(finish, value, tag, 1, true);
		}
	}

	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &tag, unsigned int fillLength, bool atEnd);

	Type *m_start;
	Type *m_finish;
	Type *m_end_of_storage;
};
}

typedef _STL::vector<Rva0077CC10Element,
	_STL::allocator<Rva0077CC10Element> > Rva0077D150Vector;
typedef _STL::vector<Gen_t_00776240_p128pod,
	_STL::allocator<Gen_t_00776240_p128pod> > Gen00776240Vector;

// ?parseConditionState0077D150@@YAXPAVINI@@PAX1PBX@Z
void parseConditionState0077D150(INI *ini, void *instance, void *store,
	const void *userData)
{
	register UnsignedInt mode = (UnsignedInt)userData;
	*(reinterpret_cast<UnsignedInt *>(0x012BB658)) = mode;

	Rva0077D150ElementSlot elementSlot;
	Rva0077CC10Element &element = elementSlot.value;
	Gen000140D8 conditions = { };
	_ReadWriteBarrier();
	AsciiString stateName;

	if (mode == 0)
	{
		bool second = false;
		bool first = false;
		const char *token = ini->getNextTokenOrNull(0);
		while (token != 0)
		{
			if (!conditions.handle(reinterpret_cast<GenItem *>(const_cast<char *>(token)),
				&second, &first))
			{
				break;
			}
			token = ini->getNextTokenOrNull(0);
		}
	}
	else if (mode != 1 && mode == 2)
	{
		const char *token = ini->getNextTokenOrNull(0);
		if (token != 0)
			stateName = token;
	}

	reinterpret_cast<UnicodeString &>(element).set(
		reinterpret_cast<const UnicodeString &>(stateName));
	*reinterpret_cast<Gen000140D8 *>(reinterpret_cast<unsigned char *>(&element) + 4) =
		conditions;
	ini->initFromINI(&element,
		reinterpret_cast<const FieldParse *>(0x012BB650));

	if (mode == 1)
	{
		Gen00776240Vector *states = reinterpret_cast<Gen00776240Vector *>(
			reinterpret_cast<unsigned char *>(instance) + 0x24);
		states->insert(states->begin(),
			reinterpret_cast<const Gen_t_00776240_p128pod &>(element));
	}
	else
	{
		Rva0077D150Vector *states = reinterpret_cast<Rva0077D150Vector *>(
			reinterpret_cast<unsigned char *>(instance) + 0x24);
		Rva0077CC10Element *finish = states->m_finish;
		if (finish != states->m_end_of_storage)
		{
			elementSlot.m_stackPad0 = (unsigned int)finish;
			elementSlot.m_stackPad1 = (unsigned int)finish;
			if (elementSlot.m_stackPad0 != 0)
				new (finish) Rva0077CC10Element(element);
			++states->m_finish;
		}
		else
		{
			_STL::__false_type tag;
			states->_M_insert_overflow(finish, element, tag, 1, true);
		}
	}

}
