// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Dict::DictPair::setNameAndType, retail 0x00068120, 102 bytes.
//
// The pair releases whatever it was holding before it takes the new name, and
// only when the type actually changes: `cmp eax, edi` against the incoming
// type with a je straight to the store is the `oldType != type` guard, ahead
// of the switch's own `cmp eax, 4` range check.
//
// The five-entry table then says what the old types are. Bool, Int and Real
// zero the value word; DICT_ASCIISTRING releases through the narrow string
// destructor and DICT_UNICODESTRING through the wide one, neither of them
// zeroing anything, which is how the two string cases are told apart from the
// three scalar ones and from each other. Each arm carries its own copy of the
// tail that packs the new key, so the body is four returns rather than one.

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

		void setNameAndType(NameKeyType key, DataType type);
	};
};

void Dict::DictPair::setNameAndType(NameKeyType key, DataType type)
{
	DataType oldType = getType();
	if (oldType != type)
	{
		switch (oldType)
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
	m_key = createKey(key, type);
}
