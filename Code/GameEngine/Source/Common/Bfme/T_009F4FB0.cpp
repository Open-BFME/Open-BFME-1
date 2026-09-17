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

class Gen_dtor_009f2600
{
public:
	void cleanup();
};

class BfmeThing912C
{
public:
	void bfmeDo912C(BfmeNode912C *node);
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
	((Gen_dtor_009f2600 *)self)->cleanup();

	self->m_values = *value;

	float first = self->m_values.value[3] - self->m_values.value[0];
	float second = self->m_values.value[4] - self->m_values.value[1];
	if (!(first > second))
		first = second;
	self->m_scale = g_bfmeDefaultBU / first;

	BfmeNode912C *node = self->m_head;
	while (node != 0) {
		((BfmeThing912C *)self)->bfmeDo912C(node);
		node = node->m_next;
	}
}
