// cl: /O2 /G7 /DNDEBUG /MD
class PartitionFilter
{
public:
    PartitionFilter *link(PartitionFilter *next);
    unsigned int m_vptr;
    PartitionFilter *m_next;
};

// ?link@PartitionFilter@@QAEPAV1@PAV1@@Z
// Open BFME 2: Code/Libraries/Source/partitionmanager/partitionmanager_filter.cpp.
PartitionFilter *PartitionFilter::link(PartitionFilter *next)
{
    PartitionFilter *cur;
    for (cur = this; cur->m_next; cur = cur->m_next)
        ;
    cur->m_next = next;
    return this;
}
