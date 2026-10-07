// Open-BFME5 conversions.

char *Rva007EBCA0(const char *record, const char *tag);
// Decimal parse with default: matched C function _Rva007EE720 (0x007EE720,
// DirtySock/Y4TextToValue.c), which the pin for this call names.
extern "C" int Rva007EE720(const char *text, int defaultValue);
static inline int bfmeApplyVMQ(char *p, int n) { return Rva007EE720(p, n); }

class BfmeThingVMQ
{
public:
	bool bfmeGoVMQ(const char *name, char flag);
	char m_bfmePad00[0x10];
	const char *m_bfme10;
};

bool BfmeThingVMQ::bfmeGoVMQ(const char *name, char flag)
{
	int n1 = (flag != 0);
	char *p = Rva007EBCA0(m_bfme10, name);
	int n2;

	if (p == 0)
		n2 = n1;
	else
		n2 = bfmeApplyVMQ(p, n1);
	return n2 != 0;
}
