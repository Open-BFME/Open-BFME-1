// ?findOrCreateIndex@Rva00359330StringRecordTable@@AAEHPAVAsciiString@@@Z
// partial score=0.55 date=2026-09-08
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// The string-record addNode methods at 0x0035CC50 and 0x0035CD20 call this
// sorted-index allocator.  Their matched release and findRecordIndex siblings
// fix the 20-byte record layout and the two linked lists used below.
// The vector shells retain the retail three-pointer layout at each table offset.

template <typename Type>
struct StringInlineData
{
	int m_refCount;
	int m_length;
	Type m_text[1];
};

template <typename Type>
class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<Type> &other);
	~StringBase();

	StringInlineData<Type> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	int compare(const AsciiString &other) const;
	void set(const AsciiString &other);
};

#pragma comment(linker, "/alternatename:?compare@AsciiString@@QBEHABV1@@Z=?j_000220c5@@YAXXZ")
#pragma comment(linker, "/alternatename:?set@AsciiString@@QAEXABV1@@Z=?set@UnicodeString@@QAEXABV1@@Z")
#pragma comment(linker, "/alternatename:?releaseBuffer@AsciiString@@AAEXXZ=?releaseBuffer@BFMERetailAsciiString@@AAEXXZ")

class Open2Rec355050;
void Open2Construct355050(Open2Rec355050 *destination,
	const Open2Rec355050 &value);

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
void _Construct(Type *destination, const Type &value);

template <class Type>
__forceinline void BfmeElementConstruct(Type *destination,
	const Type &value)
{
	_Construct(destination, value);
}

template <class Type, class Allocator>
class vector
{
public:
	__forceinline void push_back(const Type *value)
	{
		if (_M_finish != _M_end_of_storage)
		{
			BfmeElementConstruct(_M_finish, *value);
			++_M_finish;
		}
		else
		{
			_M_insert_overflow(_M_finish, *value,
				reinterpret_cast<const __false_type &>(value), 1, true);
		}
	}

	public:
	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd);

	public:
	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};

struct Rva0035AFC0Element;

template <>
__forceinline void BfmeElementConstruct(
	Rva0035AFC0Element *destination,
	const Rva0035AFC0Element &value)
{
	Open2Construct355050(
		reinterpret_cast<Open2Rec355050 *>(destination),
		reinterpret_cast<const Open2Rec355050 &>(value));
}

}

struct Rva0035AFC0Element
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	void *m_nodes;
};

class Rva00359330IndexVector
{
public:
	void reserve(unsigned int count);
	int *insert(int *position, const int &value);

	int *m_begin;
	int *m_end;
	int *m_capacity;
};

#pragma comment(linker, "/alternatename:?reserve@Rva00359330IndexVector@@QAEXI@Z=?j_0001c1e8@@YAXXZ")
#pragma comment(linker, "/alternatename:?insert@Rva00359330IndexVector@@QAEPAHPAHABH@Z=?j_000462c7@@YAXXZ")

class Rva00359330StringRecordTable : public Rva00359330IndexVector
{
	private:
	int findOrCreateIndex(AsciiString *name);
	int findNameIndexThunk(AsciiString *name);

	_STL::vector<Rva0035AFC0Element,
		_STL::allocator<Rva0035AFC0Element> > m_records;
	int m_freeHead;
	int m_activeTail;
};

#pragma comment(linker, "/alternatename:?findNameIndexThunk@Rva00359330StringRecordTable@@AAEHPAVAsciiString@@@Z=?j_000329fc@@YAXXZ")

int Rva00359330StringRecordTable::findOrCreateIndex(AsciiString *name)
{
	unsigned int nameIndex = (unsigned int)findNameIndexThunk(name);
	int *nameIndexesBegin = m_begin;
	int *nameIndexesEnd = m_end;
	int nameCount = (int)(nameIndexesEnd - nameIndexesBegin);
	if (nameIndex < (unsigned int)nameCount)
	{
		int recordIndex = nameIndexesBegin[nameIndex];
		Rva0035AFC0Element *record = m_records._M_start + recordIndex;
		if (record->m_name.compare(*name) == 0)
		{
			if (!record->m_released)
				return -1;
			goto activate;
		}
	}

	{
		unsigned int required = nameIndex + 1;
		if (required > (unsigned int)(m_capacity - m_begin))
			reserve(required + required / 2 + 8);
	}

	int recordIndex;
	if (m_freeHead == -1)
	{
		recordIndex = (int)(m_records._M_finish - m_records._M_start);
		Rva0035AFC0Element record;
		record.m_nodes = 0;
		if (m_records._M_finish != m_records._M_end_of_storage)
		{
			Open2Construct355050(
				reinterpret_cast<Open2Rec355050 *>(m_records._M_finish),
				reinterpret_cast<const Open2Rec355050 &>(record));
			++m_records._M_finish;
		}
		else
		{
			m_records._M_insert_overflow(m_records._M_finish, record,
				reinterpret_cast<const _STL::__false_type &>(name),
				1, true);
		}
		m_records._M_finish[-1].m_previous = -1;
		m_freeHead = recordIndex;
	}

	recordIndex = m_freeHead;
	Rva0035AFC0Element *record = m_records._M_start + recordIndex;
	record->m_name.set(*name);
		insert(m_begin + nameIndex, recordIndex);

	int activeTail = m_activeTail;
	m_freeHead = record->m_previous;
	if (activeTail != -1)
	{
		m_records._M_start[activeTail].m_next = recordIndex;
		record->m_previous = m_activeTail;
	}
	record->m_next = -1;
	m_activeTail = recordIndex;
	record->m_references = 0;

activate:
	++record->m_references;
	record->m_released = 0;
	return recordIndex;
}
