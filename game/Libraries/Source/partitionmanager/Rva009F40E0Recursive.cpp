// cl: /O2 /Ob2 /G6 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
#include <vector>

struct Gen009F5040Node;
struct Gen009F5040Counter
{
    int m_value;
    Gen009F5040Node *m_head;
};
typedef _STL::vector<Gen009F5040Counter> Rva009F4ED0Vector;

struct Rva009F4ED0ListNode
{
	unsigned char m_pad00[0x0c];
	Rva009F4ED0ListNode *m_next;
	void **m_slot;
};

class Rva009F40E0Owner
{
public:
	void run(void **slot, unsigned int count);
	void Rva009F4ED0();

private:
	unsigned char m_pad00[0x18];
	Rva009F4ED0Vector m_vectors[17];
	Rva009F4ED0ListNode *m_list;
};


// ?run@Rva009F40E0Owner@@QAEXPAPAXI@Z
void Rva009F40E0Owner::run(void **slot, unsigned int count)
{
	if (*slot == 0)
		return;

	*slot = 0;
	unsigned int childCount = count;
	slot += 2;
	childCount >>= 2;
	unsigned int stride = count * 8;
	unsigned int remaining = 4;
	while (remaining != 0)
	{
		run(slot, childCount);
		slot = (void **)((char *)slot + stride);
		--remaining;
	}
}

// ?Rva009F4ED0@Rva009F40E0Owner@@QAEXXZ
// Open BFME 2: Code/Libraries/Source/partitionmanager/partitionmanager_impl.cpp.
void Rva009F40E0Owner::Rva009F4ED0()
{
    for (Rva009F4ED0ListNode *node = m_list; node; node = node->m_next) {
        *node->m_slot = 0;
        node->m_slot = 0;
    }
    if (m_vectors[0].size() != 0) {
        for (int i = 0; i < 17; ++i)
            run((void **)m_vectors[i].begin(), m_vectors[0].size() / 4);
    }
}
