// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: BFME WeaponTemplateSet constructor at retail 0x00141E70, 48 bytes.
// The constructor initializes its flag and mask members before it calls clear().
// Retail calls ILT 0x0001AD98, which resolves to WeaponTemplateSet::clear at 0x001EB3E0.

#include <string.h>

template <int Dwords>
class BitFlags
{
public:
	BitFlags()
	{
		memset(m_bits, 0, sizeof(m_bits));
	}

private:
	unsigned int m_bits[Dwords];
};

typedef BitFlags<1> WeaponSetFlags;
typedef BitFlags<6> KindOfMaskType;

class WeaponTemplate;

class WeaponTemplateSet
{
public:
	WeaponTemplateSet();
	void clear();

private:
	const void *m_thingTemplate;
	WeaponSetFlags m_types;
	const WeaponTemplate *m_template[4];
	unsigned int m_autoChooseMask[4];
	KindOfMaskType m_preferredAgainst[4];
	KindOfMaskType m_shareAgainst[4];
	unsigned char m_isReloadTimeShared;
	unsigned char m_isWeaponLockSharedAcrossSets;
};

WeaponTemplateSet::WeaponTemplateSet()
{
	clear();
}
