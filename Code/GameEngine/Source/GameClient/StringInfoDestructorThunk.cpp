// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: StringInfo dtor. AsciiString @+0 then UnicodeString @+4.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	unsigned char m_pad[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	~UnicodeString();

private:
	unsigned char m_pad[4];
};

class StringInfo
{
public:
	~StringInfo();

private:
	AsciiString m_ascii;
	UnicodeString m_unicode;
};

// ??1StringInfo@@QAE@XZ
StringInfo::~StringInfo()
{
}
