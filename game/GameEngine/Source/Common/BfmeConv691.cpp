// The info key is the FESL "PID" field name, the string literal retail
// holds at VA 0x0112B554.

class BfmeOtherDFJ
{
};

// Retail body at 0x007E8900 is BfmeThingRF::bfmeGoRF; declared here (no real
// header owns it) so this call spells its defining mangled name.
class BfmeThingRF
{
public:
	void *bfmeGoRF(void *info, void *fallback);
};

class BfmeThingDFJ
{
public:
	BfmeThingDFJ *bfmeGoDFJ(BfmeOtherDFJ *other);
	void *m_bfmeVal;
};

BfmeThingDFJ *BfmeThingDFJ::bfmeGoDFJ(BfmeOtherDFJ *other)
{
	m_bfmeVal = reinterpret_cast<BfmeThingRF *>(other)->bfmeGoRF((void *)"PID", 0);
	return this;
}
