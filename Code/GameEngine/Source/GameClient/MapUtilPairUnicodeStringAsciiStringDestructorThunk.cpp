// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: exact C++ __emit port of MapUtil_pair_UnicodeString_AsciiString_dtor.asm.

class UnicodeString;
class AsciiString;

namespace _STL
{
template <class First, class Second>
class pair
{
public:
	~pair();
};

// ??1?$pair@$$CBVUnicodeString@@VAsciiString@@@_STL@@QAE@XZ
template <>
class pair<UnicodeString const, AsciiString>
{
public:
	~pair();
};

__declspec(naked) pair<UnicodeString const, AsciiString>::~pair()
{
	__asm {
		__emit 0x6a
		__emit 0xff
		__emit 0x68
		__emit 0xe8
		__emit 0x74
		__emit 0xff
		__emit 0x00
		__emit 0x64
		__emit 0xa1
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0x64
		__emit 0x89
		__emit 0x25
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x51
		__emit 0x56
		__emit 0x8b
		__emit 0xf1
		__emit 0x89
		__emit 0x74
		__emit 0x24
		__emit 0x04
		__emit 0x8d
		__emit 0x4e
		__emit 0x04
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x10
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xe8
		__emit 0x93
		__emit 0xdd
		__emit 0x7d
		__emit 0x00
		__emit 0x8b
		__emit 0xce
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x10
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xe8
		__emit 0x14
		__emit 0xe6
		__emit 0x7d
		__emit 0x00
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x08
		__emit 0x5e
		__emit 0x64
		__emit 0x89
		__emit 0x0d
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x10
		__emit 0xc3
	}
}
}
