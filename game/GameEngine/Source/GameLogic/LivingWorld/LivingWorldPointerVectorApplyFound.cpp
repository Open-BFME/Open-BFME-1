// cl: /DNDEBUG /MD /EHsc
// Living-world pointer-vector lookup/apply bridge at retail 0x003B8260.

class BfmeLwcmFindResult
{
};

// Retail reaches 0x003A95D0 (ledger BfmeLwcmFindResult::containsName003A95D0)
// through ILT 0x00026EA9; nothing defines a BfmeLwcmFindResult::applyPointer.
extern void j_00026ea9();

class BfmeLivingWorldCampaignManager
{
public:
	BfmeLwcmFindResult *findByKey(void *key);
};

// Retail 0x012F1024: use the existing data owner; retain the local pointee view.
extern class LivingWorldCampaignManager *TheLivingWorldCampaignManager;

class BfmePointerVector
{
public:
	unsigned size() const { return (unsigned)(m_end - m_begin); }
	void **slot(unsigned i) { return m_begin + i; }

private:
	void **m_begin;
	void **m_end;
};

class BfmeLwcmPointerVectorOwner
{
public:
	void applyFound(void *key);

private:
	char m_pad[0x0C];
	BfmePointerVector m_entries;
};

void BfmeLwcmPointerVectorOwner::applyFound(void *key)
{
	unsigned i;
	BfmeLwcmPointerVectorOwner *self = this;
	BfmeLwcmFindResult *found = reinterpret_cast<BfmeLivingWorldCampaignManager *>(TheLivingWorldCampaignManager)->findByKey(key);
	if (!found)
		return;
	for (i = 0; i < self->m_entries.size(); ++i)
	{
		typedef void (BfmeLwcmFindResult::*ApplyFn)(void **elem);
		union { void (*fn)(); ApplyFn call; } apply = { j_00026ea9 };
		(found->*apply.call)(self->m_entries.slot(i));
	}
}
