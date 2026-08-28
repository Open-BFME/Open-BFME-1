// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: _STL::pair<const UnicodeString, AsciiString> dtor.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	~UnicodeString();
private:
	unsigned char m_pad[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();
private:
	unsigned char m_pad[4];
};

namespace _STL
{
template <class _T1, class _T2>
struct pair
{
	~pair();
	_T1 first;
	_T2 second;
};
}

// ??1?$pair@$$CBVUnicodeString@@VAsciiString@@@_STL@@QAE@XZ
_STL::pair<const UnicodeString, AsciiString>::~pair()
{
}
