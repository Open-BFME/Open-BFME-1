// cl: /O2 /Ob0

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString adds no members of its own to StringBase<char> and this
// file only copies one, which retail encodes as a direct call to the base copy
// ctor at 0x00887B60. This TU is compiled /Ob0, so nothing here may rely on a
// forwarder being inlined away: the member is spelled as the base it copies.
template <typename T>
class StringBase
{
public:
	StringBase(const StringBase<T> &src);

private:
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
