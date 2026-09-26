// ?findOrCreateIndex@Rva0035D2B0StringRecordTable@@AAEHPAVAsciiString@@@Z
// partial score=0.65 date=2026-09-10
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Retail 0x0035C620 is the sorted-name insertion helper reached through the
// 0x0004599E ILT by the matched 0x0035D1E0/0x0035D2B0 string-record addNode
// overloads and by the matched 0x0035D3E0 node-transfer helper.  The caller
// family fixes the table ABI; the retail body fixes the 20-byte record and
// the released/free/active-list fields below.

class AsciiString
{
public:
	~AsciiString();

	void *m_data;
};

// These TU-local declarations name the exact retail thunks observed at the
// target call sites.  Their object layout is the established one-word
// AsciiString view; the distinct names keep the linker from selecting the
// out-of-line bodies when the retail site calls the incremental-link thunks.
class Rva0035D2B0AsciiString
{
public:
	~Rva0035D2B0AsciiString();
	int compare(const Rva0035D2B0AsciiString &other) const;
	void set(const Rva0035D2B0AsciiString &other);
	void *m_data;
};

class Rva0035D2B0StringRecordTable;

// The body at 0x000072F7 is the established lower-bound search used by the
// second string-record table.  This table has the same three index pointers,
// so calling the named matched method preserves the retail ILT and ABI.
class Rva00359530StringRecordTable
{
	friend class Rva0035D2B0StringRecordTable;

	private:
	int findNameIndex(AsciiString *name);
};

class Rva0035D2B0FindNameTable
{
public:
	int findNameIndex(AsciiString *name);
};

class Open2Rec3550F0;
void Open2Construct3550F0(Open2Rec3550F0 *destination,
	const Open2Rec3550F0 &value);
void Rva0035D2B0Open2Construct(Open2Rec3550F0 *destination,
	const Open2Rec3550F0 &value);

namespace _STL
{

struct __false_type
{
};

struct Rva0035B130Element
{
	~Rva0035B130Element();

	int m_previous;
	int m_next;
	Rva0035D2B0AsciiString m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	void *m_nodes;
};

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
	friend class ::Rva0035D2B0StringRecordTable;

public:
	void reserve(unsigned int count);
	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;

	protected:
	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd);
};

}

class Rva0035D2B0IndexVector
{
public:
	void reserve(unsigned int count);
	int *insert(int *position, const int &value);

	int *m_begin;
	int *m_end;
	int *m_capacity;
};

class Rva0035D2B0StringRecordTable : public Rva0035D2B0IndexVector
{
private:
	int findOrCreateIndex(AsciiString *name);

	_STL::vector<_STL::Rva0035B130Element,
		_STL::allocator<_STL::Rva0035B130Element> > m_records;
	int m_freeHead;
	int m_activeTail;
};

int Rva0035D2B0StringRecordTable::findOrCreateIndex(AsciiString *name)
{
	unsigned int nameIndex = (unsigned int)
		reinterpret_cast<Rva0035D2B0FindNameTable *>(this)->
		findNameIndex(name);
	int *nameIndexesBegin = m_begin;
	int *nameIndexesEnd = m_end;
	int nameCount = (int)(nameIndexesEnd - nameIndexesBegin);
	if (nameIndex < (unsigned int)nameCount)
	{
		int recordIndex = nameIndexesBegin[nameIndex];
		_STL::Rva0035B130Element *record = m_records._M_start + recordIndex;
		if (record->m_name.compare(
			*reinterpret_cast<Rva0035D2B0AsciiString *>(name)) == 0)
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
		_STL::Rva0035B130Element record;
		record.m_nodes = 0;
		if (m_records._M_finish != m_records._M_end_of_storage)
		{
			Rva0035D2B0Open2Construct(
				reinterpret_cast<Open2Rec3550F0 *>(m_records._M_finish),
				reinterpret_cast<const Open2Rec3550F0 &>(record));
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
	_STL::Rva0035B130Element *record = m_records._M_start + recordIndex;
	record->m_name.set(
		*reinterpret_cast<Rva0035D2B0AsciiString *>(name));
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
