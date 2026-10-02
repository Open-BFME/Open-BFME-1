// cl: /O2 /Ob0

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString adds no members of its own to StringBase<char> and this
// file only copies one, which retail encodes as a direct call to the base copy
// ctor at 0x00887B60. This TU is compiled /Ob0, so nothing here may rely on a
// forwarder being inlined away: the member is spelled as the base it copies.
// The base copy ctor's object symbol is
// ??0?$StringBase@D@@AAE@ABV0@@Z (game/Libraries/Source/string/StringBase.cpp,
// pinned 0x00887B60). MSVC 7.1 mangles a *private* member reached through a
// friend declaration with that same protected code, and mangles a protected one
// as private, so this copy mirrors the real string_base.h: the constructor is
// private and this class is its friend.
class Rva003877A0;

template <typename T>
class StringBase
{
private:
	StringBase(const StringBase<T> &src);
	friend class Rva003877A0;

	void *m_data;
};

typedef StringBase<char> AsciiString;

class Rva003877A0
{
	AsciiString m_str;
	short m_04;

public:
	Rva003877A0(const Rva003877A0 &other);
};

Rva003877A0::Rva003877A0(const Rva003877A0 &other)
	: m_str(other.m_str)
	, m_04(other.m_04)
{
}
