// Retail .rdata VA 0x0112B554 holds "PID" NUL (between UID at 0x0112B550 and
// UGID at 0x0112B558): the lookup key bfmeGoRF receives.
extern "C" unsigned char bfmeInfoDFI[] = "PID";

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
