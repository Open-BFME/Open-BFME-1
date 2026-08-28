// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString(const UnicodeString &);

private:
	void *m_data;
};

class Rva0054D5A0
{
	UnicodeString m_str;
	unsigned m_4;

public:
	Rva0054D5A0(const UnicodeString &s, const unsigned *p);
};

Rva0054D5A0::Rva0054D5A0(const UnicodeString &s, const unsigned *p)
	: m_str(s)
{
	m_4 = *p;
}
