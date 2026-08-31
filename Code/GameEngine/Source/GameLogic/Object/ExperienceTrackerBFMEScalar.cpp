// Byte-matched BFME ExperienceTracker scalar-table helper.

typedef float Real;

class ExperienceTracker;

class BfmeThingEFE
{
public:
	Real bfmeAt(int count);

private:
	void *m_vtable;
	ExperienceTracker *m_tracker;
	Real m_scalar;
	int m_baseCount;
	void *m_vec;

	friend class ExperienceTracker;
};

class ExperienceTracker
{
public:
	void bfmeSetScalarIndex(int index);
	void bfmeSetScalarBaseCount(int count);
	void bfmeResetScalarBaseCount();

private:
	unsigned char m_unreconstructed_000[0x28];
	int m_scalarIndex;
	BfmeThingEFE *m_scalarTable;
};

void ExperienceTracker::bfmeSetScalarIndex(int index)
{
	if (index == 0 || m_scalarIndex == index)
		return;

	m_scalarIndex = index;
	BfmeThingEFE *table = m_scalarTable;
	table->m_scalar = table->bfmeAt(table->m_tracker->m_scalarIndex);
}

void ExperienceTracker::bfmeSetScalarBaseCount(int count)
{
	BfmeThingEFE *table = m_scalarTable;
	table->m_baseCount = count;
	table->m_scalar = table->bfmeAt(count);
}

void ExperienceTracker::bfmeResetScalarBaseCount()
{
	BfmeThingEFE *table = m_scalarTable;
	table->m_baseCount = m_scalarIndex;
	table->m_scalar = table->bfmeAt(table->m_baseCount);
}
