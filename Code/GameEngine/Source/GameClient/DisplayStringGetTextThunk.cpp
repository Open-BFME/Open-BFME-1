// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: DisplayString::getText returns UnicodeString member at +4.

class AsciiString;
class UnicodeString;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/string_base.h
//
// BFME's string body lives on StringBase<T>, and UnicodeString's copy
// constructor is an inline forwarder to it -- so retail's `return m_text`
// encodes 0x00888400 = ??0?$StringBase@G@@AAE@ABV0@@Z, not a UnicodeString
// symbol. Spelling UnicodeString with an out-of-line copy constructor emits
// ??0UnicodeString@@QAE@ABV0@@Z and no pin can bridge that: the two addresses
// are different functions.
template <typename T> class StringBase
{
public:
	StringBase();
	~StringBase();

private:
	StringBase(const StringBase &);
	friend class AsciiString;
	friend class UnicodeString;

	T *m_string;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString();
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayString.h
class DisplayString
{
public:
	virtual UnicodeString getText();
private:
	UnicodeString m_text;
};

// ?getText@DisplayString@@UAE?AVUnicodeString@@XZ
UnicodeString DisplayString::getText()
{
	return m_text;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString();
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString();
};

// The seven other 32-byte copies of this shape are NOT copies of getText: they
// encode 0x00887B60 (??0?$StringBase@D@@AAE@ABV0@@Z), the single-byte string
// body, where getText encodes 0x00888400 for the wide one. They are the ASCII
// flavour of the same "return the string member at +4" accessor, and the class
// they belong to is not recovered -- so it is named from the lowest of the
// seven addresses rather than invented.
class Rva00093F40StringAccessor
{
public:
	virtual AsciiString getString();

private:
	AsciiString m_text;
};

// ?getString@Rva00093F40StringAccessor@@UAE?AVAsciiString@@XZ
AsciiString Rva00093F40StringAccessor::getString()
{
	return m_text;
}
