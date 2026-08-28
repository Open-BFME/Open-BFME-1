// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Standalone TU for Dict::DictPair::clear (retail jump-table switch).
// Types: DICT_BOOL=0, DICT_INT=1, DICT_REAL=2, DICT_ASCIISTRING=3, DICT_UNICODESTRING=4.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	void clear();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	void clear();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Dict.h
class Dict
{
public:
	enum DataType
	{
		DICT_BOOL = 0,
		DICT_INT = 1,
		DICT_REAL = 2,
		DICT_ASCIISTRING = 3,
		DICT_UNICODESTRING = 4
	};

	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Dict.h
	class DictPair
	{
	public:
		void clear();
		DataType getType() const;

	private:
		unsigned int m_key;
		void *m_value;

		AsciiString *asAsciiString() { return (AsciiString *)&m_value; }
		UnicodeString *asUnicodeString() { return (UnicodeString *)&m_value; }
	};
};

// getType: type is low byte of m_key
inline Dict::DataType Dict::DictPair::getType() const
{
	return (DataType)(m_key & 0xff);
}

// ?clear@DictPair@Dict@@QAEXXZ
void Dict::DictPair::clear()
{
	switch (getType())
	{
	case DICT_BOOL:
	case DICT_INT:
	case DICT_REAL:
		m_value = 0;
		break;
	case DICT_ASCIISTRING:
		asAsciiString()->clear();
		break;
	case DICT_UNICODESTRING:
		asUnicodeString()->clear();
		break;
	}
}
