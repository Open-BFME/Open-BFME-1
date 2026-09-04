// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponTemplateSet::clear, retail 0x001EB3E0 size 97.
// Focused TU: WeaponSet.cpp keeps ZH WEAPONSLOT_COUNT==3 and one KindOf
// preferred array. BFME walks 4 slots and clears two 24-byte KindOf masks
// per slot (preferred at +0x28, share/extra at +0x88).

#include <string.h>

class WeaponTemplate;

struct KindOfMask
{
	int bits[6];
};

class WeaponTemplateSet
{
public:
	void clear();

private:
	const void *m_thingTemplate;
	unsigned int m_types;
	const WeaponTemplate *m_template[4];
	unsigned int m_autoChooseMask[4];
	KindOfMask m_preferredAgainst[4];
	KindOfMask m_shareAgainst[4];
	unsigned char m_isReloadTimeShared;
	unsigned char m_isWeaponLockSharedAcrossSets;
};

// ?clear@WeaponTemplateSet@@QAEXXZ
void WeaponTemplateSet::clear()
{
	m_isReloadTimeShared = 0;
	m_isWeaponLockSharedAcrossSets = 0;
	m_types = 0;
	KindOfMask *share = m_shareAgainst;
	unsigned int *mask = m_autoChooseMask;
	int n = 4;
	do
	{
		mask[-4] = 0;
		*mask = 0xffffffff;
		memset((char *)share - 0x60, 0, sizeof(KindOfMask));
		memset(share, 0, sizeof(KindOfMask));
		++mask;
		++share;
		--n;
	}
	while (n);
}
