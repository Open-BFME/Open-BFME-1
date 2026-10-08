// VA 0x0112B4E8: the "NUM-LOBBIES" key defined in BfmeConv803BF0.cpp.
extern char g_bfmeNumLobbies803BF0[];

class BfmeOtherDFC
{
};

// Retail body at 0x007E8900 is BfmeThingRF::bfmeGoRF; declared here (no real
// header owns it) so this call spells its defining mangled name.
class BfmeThingRF
{
public:
	void *bfmeGoRF(void *info, void *fallback);
};

class BfmeThingDFC
{
public:
	BfmeThingDFC *bfmeGoDFC(BfmeOtherDFC *other);
	void *m_bfmeVal;
};

BfmeThingDFC *BfmeThingDFC::bfmeGoDFC(BfmeOtherDFC *other)
{
	m_bfmeVal = reinterpret_cast<BfmeThingRF *>(other)->bfmeGoRF((void *)g_bfmeNumLobbies803BF0, 0);
	return this;
}
