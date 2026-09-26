// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
// Retail's UnicodeString derives from StringBase<unsigned short> and holds
// nothing of its own, so copying one encodes the base body at 0x00888400
// (??0?$StringBase@G@@AAE@ABV0@@Z). This TU is built /Ob0, where no forwarder
// can be inlined away, so the member is spelled as the base it copies.
template <typename T>
class StringBase
{
public:
	StringBase(const StringBase<T> &src);

private:
	T *m_str;
};

class UnicodeString
{
public:
	UnicodeString(const UnicodeString &);

private:
	void *m_data;
};

class Rva0054D5A0
{
	StringBase<unsigned short> m_str;
	unsigned m_4;

public:
	Rva0054D5A0(const UnicodeString &s, const unsigned *p);
};

Rva0054D5A0::Rva0054D5A0(const UnicodeString &s, const unsigned *p)
	: m_str(*(const StringBase<unsigned short> *)&s)
{
	m_4 = *p;
}
