// Open-BFME: 20-byte slot ring insert, retail 0x008A0890.

class BfmeRingRef0890
{
public:
	virtual void addRef();

	char m_pad[0x4c];
	unsigned char *m_mid;
};

class BfmeRingSlot0890
{
public:
	int m_zero;
	int m_arg3;
	int m_mid28;
	int m_arg1;
	BfmeRingRef0890 *m_ref;
};

class BfmeRing008A0890
{
public:
	void insert(int arg1, BfmeRingRef0890 *arg2, int arg3);

	BfmeRingSlot0890 *m_begin;
	BfmeRingSlot0890 *m_write;
	BfmeRingSlot0890 *m_read;
	char m_gap[0x12b0 - 0x0c];
	int m_capacity;
};

void BfmeRing008A0890::insert(int arg1, BfmeRingRef0890 *arg2, int arg3)
{
	BfmeRing008A0890 *self = this;
	BfmeRingSlot0890 *slot = self->m_write - 1;
	if (slot < self->m_begin)
		slot = self->m_begin + self->m_capacity - 1;
	if (slot == self->m_read)
		return;
	self->m_write = slot;
	slot->m_mid28 = *(int *)(arg2->m_mid + 0x28);
	self->m_write->m_zero = 0;
	self->m_write->m_arg1 = arg1;
	self->m_write->m_ref = arg2;
	arg2->addRef();
	self->m_write->m_arg3 = arg3;
}

class BfmeN1034
{
public:
	virtual void addRef();
};

class BfmeRouteManager1282
{
public:
	void bfmeSubmit1282(void *entry, BfmeN1034 *node, int zero, int encoded);
	void produce(void *entry, BfmeN1034 *node, int zero, int encoded);

	BfmeRingSlot0890 *m_begin;
	BfmeRingSlot0890 *m_write;
	BfmeRingSlot0890 *m_read;
	char m_gap[0x12b0 - 0x0c];
	int m_capacity;
};

void BfmeRouteManager1282::bfmeSubmit1282(void *entry, BfmeN1034 *node, int zero, int encoded)
{
	BfmeRouteManager1282 *self = this;
	BfmeRingSlot0890 *slot = self->m_write - 1;
	if (slot < self->m_begin)
		slot = self->m_begin + self->m_capacity - 1;
	if (slot == self->m_read)
		return;
	self->m_write = slot;
	self->m_write->m_zero = 1;
	self->m_write->m_arg3 = encoded;
	self->m_write->m_mid28 = (int)entry;
	((BfmeN1034 *)self->m_write->m_mid28)->addRef();
	self->m_write->m_arg1 = (int)node;
	((BfmeN1034 *)self->m_write->m_arg1)->addRef();
	self->m_write->m_ref = (BfmeRingRef0890 *)zero;
}

void BfmeRouteManager1282::produce(void *entry, BfmeN1034 *node, int zero, int encoded)
{
	BfmeRouteManager1282 *self = this;
	int capacity = self->m_capacity;
	BfmeRingSlot0890 *cur = self->m_read;
	BfmeRingSlot0890 *begin = self->m_begin;
	BfmeRingSlot0890 *next = cur + 1;
	if (next == begin + capacity)
		next = begin;
	if (next == self->m_write)
		return;
	cur->m_zero = 1;
	self->m_read->m_arg3 = encoded;
	self->m_read->m_mid28 = (int)entry;
	((BfmeN1034 *)self->m_read->m_mid28)->addRef();
	self->m_read->m_arg1 = (int)node;
	((BfmeN1034 *)self->m_read->m_arg1)->addRef();
	self->m_read->m_ref = (BfmeRingRef0890 *)zero;
	self->m_read = next;
}
