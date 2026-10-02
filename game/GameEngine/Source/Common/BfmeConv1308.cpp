// Open-BFME5 conversions.

class BfmeGetterTCA
{
};

// Retail body at 0x007E8900 is BfmeThingRF::bfmeGoRF; declared here (no real
// header owns it) so this call spells its defining mangled name.
class BfmeThingRF
{
public:
	void *bfmeGoRF(void *key, void *fallback);
};

class BfmeSinkTCA
{
public:
	void bfmeUseTCA(void *v);
};

class BfmeHostTCA
{
public:
	void bfmeGoTCA(BfmeGetterTCA *r);
	char m_bfmePad[0x18];
	BfmeSinkTCA *m_bfmeSink;
};

void BfmeHostTCA::bfmeGoTCA(BfmeGetterTCA *r)
{
	m_bfmeSink->bfmeUseTCA(reinterpret_cast<BfmeThingRF *>(r)->bfmeGoRF((void *)"TID", 0));
}

