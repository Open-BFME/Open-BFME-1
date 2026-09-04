// ?newOverride@WeaponStore@@IAEPAVWeaponTemplate@@PAV2@@Z
// partial score=0.97 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME5: WeaponStore::newOverride, retail 0x001E9AF0 size 268.
// parseWeaponTemplateDefinition already names this callee (ecx left holding
// TheWeaponStore). BFME allocates a 0x53C WeaponTemplate, copy-assigns, links
// next at +4, marks +0x528, then replaces any same-nameKey entry in the
// vector at +8. Source with +0x528 set is refused. Focused TU.
//
// Near-miss 265/268: prologue, new, copy-assign, next-link, +0x528 mark, and
// the nameKey walk match. Retail's erase reloads finish from [edi+4] before
// memmove; MSVC 7.1 CSEs that load against the loop's end pointer (ecx),
// dropping three bytes and shifting the later jump offsets. volatile and
// member-function reloads either swap ecx/edx or spill ebx and break the
// prologue.

#include <vector>

class WeaponTemplate
{
public:
	WeaponTemplate();
	WeaponTemplate &operator=(const WeaponTemplate &that);

	void *m_vtable;
	WeaponTemplate *m_nextTemplate;
	char m_pad_008[0x0C - 0x08];
	int m_nameKey;
	char m_pad_010[0x528 - 0x10];
	unsigned char m_copiedOverride;
	char m_pad_529[0x53C - 0x529];
};

class WeaponStore
{
protected:
	WeaponTemplate *newOverride(WeaponTemplate *weaponTemplate);

private:
	void *m_vtable;
	int m_pad_004;
	std::vector<WeaponTemplate *> m_weaponTemplateVector;
};

// ?newOverride@WeaponStore@@IAEPAVWeaponTemplate@@PAV2@@Z
WeaponTemplate *WeaponStore::newOverride(WeaponTemplate *weaponTemplate)
{
	WeaponTemplate *src = weaponTemplate;
	WeaponStore *self = this;
	if (src == 0)
		return 0;
	if (src->m_copiedOverride != 0)
		return 0;

	WeaponTemplate *wt = new WeaponTemplate;
	*wt = *src;
	wt->m_nextTemplate = src;
	wt->m_copiedOverride = 1;

	std::vector<WeaponTemplate *> &items = self->m_weaponTemplateVector;
	int key = wt->m_nameKey;
	WeaponTemplate **it = items.begin();
	WeaponTemplate **fin = items.end();
	for (; it != fin; ++it)
	{
		if ((*it)->m_nameKey == key)
		{
			items.erase(it);
			break;
		}
	}
	items.push_back(wt);
	return wt;
}
