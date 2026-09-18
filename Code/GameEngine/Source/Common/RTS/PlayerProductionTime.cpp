// BFME Player::getProductionTimeChangePercent, retail 0x000DA030 / 35 bytes.
// ThingTemplate::calcTimeToBuild calls this body with its Player receiver and
// ThingTemplate name.  The retail body looks up the name in the Player map at
// +0x1D8, returns the matched record's float at +8, and returns the global zero
// on a miss.  The local layout keeps that BFME map position independent of the
// shorter Zero Hour Player header.

typedef float Real;

class AsciiString
{
};

extern "C" const Real bfmeKEZC;

struct BfmeResEZC
{
	unsigned char m_bfmeHead[8];
	Real m_bfmeF;
};

class BfmeSubEZC
{
public:
	BfmeResEZC *bfmeFindEZC(void *a);
};

class Player
{
public:
	Real getProductionTimeChangePercent(const AsciiString &buildTemplateName) const;

private:
	unsigned char m_bfmeHead[0x1D8];
	mutable BfmeSubEZC m_productionTimeChanges;
};

Real Player::getProductionTimeChangePercent(const AsciiString &buildTemplateName) const
{
	BfmeResEZC *productionTimeChange = m_productionTimeChanges.bfmeFindEZC(
		(void *)&buildTemplateName);
	if (productionTimeChange)
		return productionTimeChange->m_bfmeF;
	return bfmeKEZC;
}
