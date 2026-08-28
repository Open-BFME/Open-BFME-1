// cl: /O2 /Ob0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	void set(const UnicodeString &);
};

UnicodeString g_rva0040b150_src;
UnicodeString g_rva0040b150_dst;

void rva0040b150()
{
	g_rva0040b150_dst.set(g_rva0040b150_src);
}
