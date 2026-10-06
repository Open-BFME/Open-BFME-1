#include <string.h>

// Open-BFME: 20-byte slot ring insert, retail 0x008A0890.

class BfmeRingRef0890
{
public:
	virtual void addRef();
	// Matched ring clear at 0x008A07D0 calls this no-argument slot
	// through the same record +0x10 value pointer. No vtable is emitted here.
	virtual void slot04();

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
	void removeRva008A09D0(BfmeRingRef0890 *value);
	BfmeRingSlot0890 *nextSlot(BfmeRingSlot0890 *slot) const;

	BfmeRingSlot0890 *m_begin;
	BfmeRingSlot0890 *m_write;
	BfmeRingSlot0890 *m_read;
	char m_gap[0x12b0 - 0x0c];
	int m_capacity;
};

// ?nextSlot@BfmeRing008A0890@@QBEPAVBfmeRingSlot0890@@PAV2@@Z
// 0x008A0610, the first of two bodies in one 61-byte dump (int3 run at +0x1E):
// steps a slot pointer forward through the same m_begin/m_capacity ring as
// insert(), wrapping to m_begin at the end. The second body, 0x008A0630, is
// the backward step insert() does inline, but retail spells its decrement
// `add eax,-14h` where every C form tried here gives `sub eax,14h`.
BfmeRingSlot0890 *BfmeRing008A0890::nextSlot(BfmeRingSlot0890 *slot) const
{
	++slot;
	if (slot == m_begin + m_capacity)
		slot = m_begin;
	return slot;
}

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

// Retail [0x008A09D0, 0x008A0AF3): ECX is the same manager loaded from
// 0x013377D8 by the matched insert caller; one value pointer, ret 4.
// Removes the first matching kind-zero record from the 20-byte circular range.
// The first-slot branch only advances the write pointer, as retail does.
// The true member spelling is unproved, so its name retains the address.
void BfmeRing008A0890::removeRva008A09D0(BfmeRingRef0890 *value)
{
    BfmeRingSlot0890 *head = m_write;
    BfmeRingSlot0890 *tail = m_read;
    BfmeRingSlot0890 *slot = m_write;
    while (slot != m_read) {
        if (slot->m_zero == 0 && slot->m_ref == value) {
            if (slot < tail) {
                value->slot04();
                memmove(slot, slot + 1, (m_read - slot - 1) * sizeof(*slot));
                BfmeRingSlot0890 *previous = m_read - 1;
                if (previous < m_begin)
                    previous = m_begin + m_capacity - 1;
                m_read = previous;
                return;
            }
            if (slot > head) {
                value->slot04();
                memmove(m_write + 1, m_write, (slot - m_write) * sizeof(*slot));
                m_write = nextSlot(m_write);
                return;
            }
            if (slot == head) {
                m_write = nextSlot(head);
                return;
            }
        }
        slot = nextSlot(slot);
    }
}
