// cl: /DNDEBUG /MD /EHsc
// readable body of ?releaseData@Dict@@: Code/GameEngine/Source/Common/Dict.cpp
// Open-BFME: Dict::releaseData, retail 0x000681C0, 156 bytes. The body carried
// no ledger row; its name sat on a 5-byte thunk.
//
// The reference's four lines, with DictPair::clear inlined into the loop, and
// the shared header laid out by the code: the reference count is the halfword
// at +0, the used-pair count the halfword at +4, and peek() is the header plus
// six. The freeing is plain free through the import table, not the reference's
// dynamic-memory allocator.
//
// The five-entry jump table is clear()'s switch: the three scalar types zero
// the value word, DICT_ASCIISTRING releases through the narrow string's
// destructor and DICT_UNICODESTRING through the wide one.

extern "C" __declspec(dllimport) void __cdecl free(void *memblock);

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum NameKeyType { NAMEKEY_INVALID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();
private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	~UnicodeString();
private:
	unsigned short *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Dict.h
class Dict
{
public:
	enum DataType
	{
		DICT_NONE = -1,
		DICT_BOOL,
		DICT_INT,
		DICT_REAL,
		DICT_ASCIISTRING,
		DICT_UNICODESTRING
	};

	enum DictPairKeyType { DICTPAIRKEY_ILLEGAL = 0 };

	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Dict.h
	struct DictPair
	{
		DictPairKeyType m_key;					// this+0x00, type in the low byte
		void *m_value;						// this+0x04

		inline static DictPairKeyType createKey(NameKeyType keyVal, DataType nt)
		{
			return (DictPairKeyType)((((UnsignedInt)(keyVal)) << 8) | ((UnsignedInt)nt));
		}

		inline static DataType getTypeFromKey(DictPairKeyType nk)
		{
			return (DataType)(((UnsignedInt)nk) & 0xff);
		}

		inline DataType getType() const { return getTypeFromKey(m_key); }
		inline AsciiString *asAsciiString() { return (AsciiString *)&m_value; }
		inline UnicodeString *asUnicodeString() { return (UnicodeString *)&m_value; }

		inline void clear()
		{
			switch (getType())
			{
				case DICT_BOOL:
				case DICT_INT:
				case DICT_REAL:
					m_value = 0;
					break;
				case DICT_ASCIISTRING:
					asAsciiString()->~AsciiString();
					break;
				case DICT_UNICODESTRING:
					asUnicodeString()->~UnicodeString();
					break;
			}
		}
	};

	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Dict.h
	struct DictPairData
	{
		unsigned short m_refCount;				// this+0x00
		unsigned short m_numPairsAllocated;			// this+0x02
		unsigned short m_numPairsUsed;				// this+0x04

		inline DictPair *peek() { return (DictPair *)(this + 1); }
	};

private:
	void releaseData();

	DictPairData *m_data;
};

void Dict::releaseData()
{
	if (m_data)
	{
		if (--m_data->m_refCount == 0)
		{
			DictPair *src = m_data->peek();
			for (Int i = 0; i < m_data->m_numPairsUsed; ++i, ++src)
				src->clear();
			free(m_data);
		}
		m_data = 0;
	}
}
