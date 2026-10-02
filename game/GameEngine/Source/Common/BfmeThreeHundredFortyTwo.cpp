// Retail table 0x011051EC is the vftable of Rva011051ECSkirmishField, the
// defining name recorded for that address in dir32_addresses.csv. The old
// _bfmeVftTC spelling had no definition anywhere, so this extern is bound to
// the exact defining symbol.
extern "C" unsigned char *__identifier("??_7Rva011051ECSkirmishField@@6B@")[];
#define g_bfmeRva011051ECVt __identifier("??_7Rva011051ECSkirmishField@@6B@")

class BfmeThingTC
{
public:
	void bfmeBaseTC();
	BfmeThingTC *bfmeInitTC(void *what);
	void *m_bfmeVft;
	unsigned char m_bfmeGap[8];
	void *m_bfmeWhat;
};

BfmeThingTC *BfmeThingTC::bfmeInitTC(void *what)
{
	bfmeBaseTC();
	m_bfmeWhat = what;
	m_bfmeVft = g_bfmeRva011051ECVt;
	return this;
}
