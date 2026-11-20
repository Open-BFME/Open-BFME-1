// Open-BFME5 conversions.



// The thunk at 0x00017A12 reaches the matched ThingTemplate row 0x00144DC0.
class AssetList;
class ThingTemplate
{
public:
	void rva00144DC0(AssetList &assets, void *context);
};

class AsciiString;
class BfmeThingFactory
{
public:
    const ThingTemplate *findTemplate(const AsciiString &name);
};

// Retail global 0x012EF1D8 is EA's ThingFactory singleton, defined once in
// Common/Thing/ThingFactory.cpp. Use the rowed factory lookup contract.
class ThingFactory;

extern ThingFactory *TheThingFactory;

struct BfmeStr917F
{
	char m_bfmePad[4];
	unsigned short m_bfmeLen;
};

struct BfmeSubFHH
{
	BfmeStr917F *m_bfmeStr;
};

struct BfmeArg917F
{
	char m_bfmePad[0x14];
	BfmeSubFHH m_bfmeSub;
};

void bfmeGo917F(BfmeArg917F *a, void *b, void *c)
{
	BfmeStr917F *s = a->m_bfmeSub.m_bfmeStr;
	BfmeSubFHH *k = &a->m_bfmeSub;
	if (!s)
		return;
	if (s->m_bfmeLen == 0)
		return;
	const ThingTemplate *r = reinterpret_cast<BfmeThingFactory *>(TheThingFactory)->findTemplate(
        *reinterpret_cast<const AsciiString *>(k));
	if (!r)
		return;
	const_cast<ThingTemplate *>(r)->rva00144DC0(*static_cast<AssetList *>(b), c);
}
