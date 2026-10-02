// Retail table 0x011051EC is the vftable of Rva011051ECSkirmishField, the
// defining name recorded for that address in dir32_addresses.csv. The old
// _bfmeVftTC spelling had no definition anywhere, so this extern is bound to
// the exact defining symbol.
extern "C" unsigned char *__identifier("??_7Rva011051ECSkirmishField@@6B@")[];
#define g_bfmeRva011051ECVt __identifier("??_7Rva011051ECSkirmishField@@6B@")

extern "C" void __identifier("?j_00021ffd@@YAXXZ")(void);

class BfmeThingTC
{
public:
	BfmeThingTC *bfmeInitTC(void *what);
	void *m_bfmeVft;
	unsigned char m_bfmeGap[8];
	void *m_bfmeWhat;
};

BfmeThingTC *BfmeThingTC::bfmeInitTC(void *what)
{
	__identifier("?j_00021ffd@@YAXXZ")();
	m_bfmeWhat = what;
	m_bfmeVft = g_bfmeRva011051ECVt;
	return this;
}
