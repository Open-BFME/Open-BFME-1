// ?rva008A5250@@YAPAVAptValue@@PAXH@Z
// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc
// Retail 0x008A5250 (130 bytes, three ret paths then int3 padding): an Apt
// (void *, int count) callback that answers whether the last packed key
// (Rva008A5250LastKey, 0x013387AC) is a key event whose code equals the
// integer on top of the Apt stack.  Printable codes 0x20..0x7E compare upper
// case; codes below 0x14 map through Rva008A5250KeyTable (0x011364B0).  No
// caller, data reference or slot names it, so the name keeps the address
// (Open-BFME-2's Code/Libraries/Source/Apt/AptObject/AptKeyLookup.cpp covers
// the Key object family; it is a lead, not BFME 1 identity evidence).
//
// Shape: map the code first, then ONE `Create(code == toInteger())`; VC7.1
// duplicates that tail into both mapping arms with retail's sete al.  Two
// written compare calls leave the second as sete cl (2 bytes off).

class AptValue
{
public:
	int toInteger() const;
};

class AptBoolean
{
public:
	static AptBoolean *Create(bool value);
};

// 0x01338748: the Apt stack, as in Rva008C6800.cpp and
// Rva008C6AD0BooleanCoerce.cpp.
struct Rva008AE770Stack
{
	int m_count;
	int m_rva0133874C;
	AptValue **m_rva01338750;
};
extern Rva008AE770Stack Rva008AE770TheStack;
// The old bank's g_bfmeArr1233 (0x01338750) and g_bfmeCount1233
// (0x01338748) were only dir32 pins; both are fields of the stack object
// above, read through one reference as the sibling callbacks do.
#define g_bfmeCount1233 (Rva008AE770TheStack.m_count)
#define g_bfmeArr1233 (Rva008AE770TheStack.m_rva01338750)

extern unsigned int Rva008A5250LastKey;
extern const int Rva008A5250KeyTable[0x14];
extern "C" int __cdecl toupper(int);

AptValue *rva008A5250(void *, int)
{
	Rva008AE770Stack &stack = Rva008AE770TheStack;
	AptValue *value = stack.m_rva01338750[stack.m_count - 1];
	unsigned int key = Rva008A5250LastKey;
	if ((key & 3) == 1)
	{
		int code = key >> 17;
		if (code >= 32 && code <= 126)
			code = toupper(code);
		else if (code < 20)
			code = Rva008A5250KeyTable[code];
		return reinterpret_cast<AptValue *>(AptBoolean::Create(code == value->toInteger()));
	}
	return reinterpret_cast<AptValue *>(AptBoolean::Create(false));
}
