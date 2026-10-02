extern "C" unsigned char bfmeInfoDFI[];

class BfmeOtherDFI
{
};

// Retail body at 0x007E8900 is BfmeThingRF::bfmeGoRF; declared here (no real
// header owns it) so this call spells its defining mangled name.
class BfmeThingRF
{
public:
	void *bfmeGoRF(void *info, void *fallback);
};

class BfmeThingDFI
{
public:
	BfmeThingDFI *bfmeGoDFI(BfmeOtherDFI *other);
	void *m_bfmeVal;
};

BfmeThingDFI *BfmeThingDFI::bfmeGoDFI(BfmeOtherDFI *other)
{
	m_bfmeVal = reinterpret_cast<BfmeThingRF *>(other)->bfmeGoRF(bfmeInfoDFI, 0);
	return this;
}
