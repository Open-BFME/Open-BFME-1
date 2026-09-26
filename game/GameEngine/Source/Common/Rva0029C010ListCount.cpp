// Retail 0x0029C010: count matching entries in the linked list at +0x08.
// The caller supplies the helper's this pointer as the sole stack argument;
// the helper is kept address-derived because retail ILT 0x0003E80B has
// several incompatible candidate names in the additive symbol ledger.

struct Rva0029C010Node
{
	unsigned char m_pad00[4];
	int m_state;
	void *m_value;
	unsigned char m_pad0c[0x30];
	Rva0029C010Node *m_next;
};

class Rva0029C010
{
public:
	int count(void *helperThis);

private:
	unsigned char m_pad00[8];
	Rva0029C010Node *m_head;
};

extern void j_0003e80b();

struct Rva0029C010PredicateView
{
	bool test(void *value);
};

typedef bool (Rva0029C010PredicateView::*Rva0029C010PredicateCall)(void *);

static __forceinline bool rva0029C010Test(void *helperThis, void *value)
{
	union { void (*raw)(); Rva0029C010PredicateCall member; } fn;
	fn.raw = j_0003e80b;
	return (reinterpret_cast<Rva0029C010PredicateView *>(helperThis)->*fn.member)(value);
}

int Rva0029C010::count(void *helperThis)
{
	Rva0029C010Node *node = m_head;
	int count = 0;

	if (node != 0) {
		do {
			if (node->m_state == 1 || node->m_state == 3) {
				if (rva0029C010Test(helperThis, node->m_value))
					++count;
			}
			node = node->m_next;
		} while (node != 0);
	}

	return count;
}
