// cl: /O2 /DNDEBUG /MD /EHsc

// The state constructor passes six values to T_009f4fb0::m at retail
// 0x009F4FB0, and the body updates the same state fields and linked nodes.

struct Rva009F5970StateInit
{
	float value[6];
};

struct BfmeNode912C
{
	char m_pad00[0x0c];
	BfmeNode912C *m_next;
};

// The cleanup call at 0x009F4FB0+0x04 goes to 0x009F4ED0, which the ledger
// defines as the gen-dump body ?d_009f4ed0@@YAXXZ in
// game/gen_asm/d_009f2f00.asm.  It is a free body, not a member of the state
// class, so it is called as one; `this` already sits in ecx and the call takes
// no argument, exactly as the member call did.
extern void d_009f4ed0();

// The loop call at 0x009F4FB0+0x73 goes to 0x009F4D80, which the ledger
// defines as PartitionManagerImpl::_InsertObjectIntoTree in
// game/Libraries/Source/partitionmanager/Gen009F5040Handle.cpp; the node
// argument is spelled with that function's own node type.
struct Gen009F5040Node;

class PartitionManagerImpl
{
public:
	void _InsertObjectIntoTree(Gen009F5040Node *node);
};

extern float g_bfmeDefaultBU;

class T_009f4fb0
{
public:
	void m(Rva009F5970StateInit *value);

	Rva009F5970StateInit m_values;
	char m_pad18[0xcc];
	BfmeNode912C *m_head;
	float m_scale;
	int m_flags;
	void *m_tail;
};

void T_009f4fb0::m(Rva009F5970StateInit *value)
{
	T_009f4fb0 *self = this;
	d_009f4ed0();

	self->m_values = *value;

	float first = self->m_values.value[3] - self->m_values.value[0];
	float second = self->m_values.value[4] - self->m_values.value[1];
	if (!(first > second))
		first = second;
	self->m_scale = g_bfmeDefaultBU / first;

	BfmeNode912C *node = self->m_head;
	while (node != 0) {
		((PartitionManagerImpl *)self)->_InsertObjectIntoTree(
			reinterpret_cast<Gen009F5040Node *>(node));
		node = node->m_next;
	}
}
