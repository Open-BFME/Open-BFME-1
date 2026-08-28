// cl: /DNDEBUG /MD /EHsc
// readable body of ?getAsciiString@Dict@@: Code/GameEngine/Source/Common/Dict.cpp
// Open-BFME: Dict::getAsciiString, retail 0x00068580, 96 bytes.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum NameKeyType { NAMEKEY_INVALID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &that);
	~AsciiString();

	static AsciiString TheEmptyString;			// retail 0x00F36E50

private:
	char *m_text;
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

	AsciiString getAsciiString(NameKeyType key, Bool *exists = 0) const;

private:
	enum DictPairKeyType { DICTPAIRKEY_ILLEGAL = 0 };

	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Dict.h
	struct DictPair
	{
		DictPairKeyType m_key;					// this+0x00, type in the low byte
		void *m_value;						// this+0x04

		inline static DataType getTypeFromKey(DictPairKeyType nk)
		{
			return (DataType)(((UnsignedInt)nk) & 0xff);
		}

		inline AsciiString *asAsciiString() { return (AsciiString *)&m_value; }
	};

	DictPair *findPairByKey(NameKeyType key) const;		// ILT 0x0003451D

	void *m_data;
};

AsciiString Dict::getAsciiString(NameKeyType key, Bool *exists /*=NULL*/) const
{
	DictPair *pair = findPairByKey(key);
	if (pair && DictPair::getTypeFromKey(pair->m_key) == DICT_ASCIISTRING)
	{
		if (exists) *exists = true;
		return *pair->asAsciiString();
	}
	if (exists) *exists = false;
	return AsciiString::TheEmptyString;
}
