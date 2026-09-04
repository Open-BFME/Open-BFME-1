// ?applyFound@BfmeLwcmPointerVectorOwner@@QAEXPAX@Z
// partial score=0.9 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: retail 0x003B8260 (82B). Looks up a record on
// TheLivingWorldCampaignManager (0x012F1024) via ILT 0x0000D422 -> 0x003B4590,
// then for each pointer in this object's vector at +0x0C/+0x10 calls
// ILT 0x00026EA9 -> 0x003A95D0 on the found record.

class BfmeLwcmFindResult
{
public:
	void applyPointer(void **elem);	// ILT 0x00026EA9
};

class BfmeLivingWorldCampaignManager
{
public:
	BfmeLwcmFindResult *findByKey(void *key);	// ILT 0x0000D422
};

extern BfmeLivingWorldCampaignManager *TheLivingWorldCampaignManager; // 0x012F1024

class BfmeLwcmPointerVectorOwner
{
public:
	void applyFound(void *key);

private:
	char m_pad[0x0C];
	void **m_begin;
	void **m_end;
};

void BfmeLwcmPointerVectorOwner::applyFound(void *key)
{
	BfmeLwcmPointerVectorOwner *self = this;
	BfmeLwcmFindResult *found = TheLivingWorldCampaignManager->findByKey(key);
	if (!found)
		return;
	for (unsigned i = 0; i < (unsigned)(self->m_end - self->m_begin); ++i)
		found->applyPointer(self->m_begin + i);
}
