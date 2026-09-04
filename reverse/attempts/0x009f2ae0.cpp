// ?link@PartitionFilter@@QAEPAV1@PAV1@@Z
// partial score=0.99 date=2026-09-04
// ?link@PartitionFilter@@QAEPAV1@PAV1@@Z present-unmatched
// cl: /O2 /Ob2

class PartitionFilter;

struct PartitionFilterLinkView
{
	void *vtable;
	PartitionFilter *m_next;
};

class PartitionFilter
{
public:
	virtual bool allow(void *object) = 0;
	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

PartitionFilter *PartitionFilter::link(PartitionFilter *next)
{
	PartitionFilterLinkView *cursor = 0;
	PartitionFilter *candidate = m_next;
	if (candidate != 0)
	{
		do
		{
			cursor = (PartitionFilterLinkView *)(unsigned int)candidate;
			candidate = cursor->*(&PartitionFilterLinkView::m_next);
		}
		while (candidate != 0);
		cursor->m_next = next;
	}
	else
	{
		m_next = next;
	}
	return this;
}
