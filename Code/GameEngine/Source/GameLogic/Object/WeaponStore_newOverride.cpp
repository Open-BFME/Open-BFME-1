// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME5: WeaponStore::newOverride, retail 0x001E9AF0 size 268.
// parseWeaponTemplateDefinition already names this callee (ecx left holding
// TheWeaponStore). BFME allocates a 0x53C WeaponTemplate, copy-assigns, links
// next at +4, marks +0x528, then replaces any same-nameKey entry in the
// vector at +8. Source with +0x528 set is refused. Focused TU.
//
// STLport erase inlines as memmove(pos, pos+1, finish-(pos+1)) then --finish.
// MSVC 7.1 CSEs the finish load against the walk's cached ecx; retail still
// emits `mov ecx, [edi+4]`. A volatile source / plain dest forces that reload
// without moving the count out of ecx.

#include <vector>

extern "C" void *(__cdecl *bfme_memmove_ptr)(void *, const void *, unsigned int);
#define memmove (*bfme_memmove_ptr)

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

struct WeaponTemplateVec
{
	WeaponTemplate **_M_start;
	WeaponTemplate **_M_finish;
	WeaponTemplate **_M_end_of_storage;

	void erase(WeaponTemplate **pos)
	{
		WeaponTemplate **last = *(WeaponTemplate ** volatile *)&_M_finish;
		WeaponTemplate **next = pos + 1;
		if (last != next)
			memmove(pos, next, (char *)last - (char *)next);
		--_M_finish;
	}
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
			((WeaponTemplateVec *)&items)->erase(it);
			break;
		}
	}
	items.push_back(wt);
	return wt;
}
