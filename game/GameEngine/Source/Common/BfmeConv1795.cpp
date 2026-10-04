// Retail spells this sweep's three callees under their defining names:
// ?getFinalOverride@Overridable@@QBEPBV1@XZ (public const, upstream
// Overridable.h; same TU-local stand-in convention as BfmeConv1002.cpp),
// ?findWeaponTemplateSet@ThingTemplate@@QBEPBVWeaponTemplateSet@@ABV?$BitFlags@$0BB@@@@Z
// (public const; the mask travels by reference so the call pushes the same
// address), and ?handle@Gen001C9A10@@QAEXH@Z (same stand-in as
// TargetFlags001F8080.cpp). The sweep's node/holder classes stay layout
// views; only the call targets take the defining names.
class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

template <int NUMBITS>
class BitFlags;

class WeaponTemplateSet;

class ThingTemplate
{
public:
	const WeaponTemplateSet *findWeaponTemplateSet(const BitFlags<0x11> &flags) const;

	int m_bfmeSpareLP;
	Overridable *m_bfmeInnerLP;
};

class Gen001C9A10
{
public:
	void handle(int player);
};

class BfmeHolderLP
{
public:
	int m_bfmeSpareLP;
	ThingTemplate *m_bfmeThingLP;
};

class BfmeNodeLP
{
public:
	BfmeNodeLP *m_bfmeNextLP;
	int m_bfmeSpareLP;
	BfmeHolderLP *m_bfmeHolderLP;
};

class BfmeOwnerLP
{
public:
	void bfmeSweepLP(unsigned int bit);

	int m_bfmeSpareLP;
	BfmeNodeLP *m_bfmeListLP;
};

void BfmeOwnerLP::bfmeSweepLP(unsigned int bit)
{
	BfmeNodeLP *node;

	for (node = m_bfmeListLP->m_bfmeNextLP; node != m_bfmeListLP; node = node->m_bfmeNextLP)
	{
		BfmeHolderLP *holder = node->m_bfmeHolderLP;
		unsigned int mask = 1 << (bit & 0x1f);
		ThingTemplate *thing = holder->m_bfmeThingLP;

		if (thing && thing->m_bfmeInnerLP)
			thing = (ThingTemplate *)thing->m_bfmeInnerLP->getFinalOverride();

		if (thing->findWeaponTemplateSet((const BitFlags<0x11> &)mask))
			((Gen001C9A10 *)holder)->handle(bit);
	}
}
