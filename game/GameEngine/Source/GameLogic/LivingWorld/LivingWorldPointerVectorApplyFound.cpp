// cl: /DNDEBUG /MD /EHsc
// Living-world pointer-vector lookup/apply bridge at retail 0x003B8260.

class BfmeLwcmFindResult
{
public:
	void applyPointer(void **elem);
};

class BfmeLivingWorldCampaignManager
{
public:
	BfmeLwcmFindResult *findByKey(void *key);
};

extern BfmeLivingWorldCampaignManager *TheLivingWorldCampaignManager;

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
	BfmeLwcmFindResult *found = TheLivingWorldCampaignManager->findByKey(key);
	if (!found)
		return;
	for (i = 0; i < self->m_entries.size(); ++i)
		found->applyPointer(self->m_entries.slot(i));
}
