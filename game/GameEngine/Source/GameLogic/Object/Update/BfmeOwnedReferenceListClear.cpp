// cl: /DNDEBUG /MD /EHsc

class Overridable
{
public:
	Overridable *deleteOverrides();
};

class BfmeOwnedReference
{
public:
	virtual ~BfmeOwnedReference();

	Overridable *m_reference;
	bool m_owned;
};

class BfmeOwnedReferenceList
{
public:
	void clearEntries();

private:
	unsigned char m_pad[8];
	BfmeOwnedReference **m_begin;
	BfmeOwnedReference **m_end;
};

void BfmeOwnedReferenceList::clearEntries()
{
	for (BfmeOwnedReference **it = m_begin; it != m_end; ++it) {
		BfmeOwnedReference *entry = *it;
		if (entry != 0) {
			if (entry->m_owned) {
				delete entry;
			} else if (entry->m_reference != 0) {
				entry->m_reference = entry->m_reference->deleteOverrides();
			}
		}
	}
}
