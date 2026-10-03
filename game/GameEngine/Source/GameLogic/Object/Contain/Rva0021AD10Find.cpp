// cl: /DNDEBUG /MD /EHsc
// Retail 0x0021AD10, 110 bytes. Circular list search with predicate: the
// find call result returns at once; otherwise walk the node list at
// this+0x9BC, running the ask call per payload -- a non-null ask result goes
// through virtual slot 6 with the argument, and a true answer returns that
// payload, else the null find result. Found-keep shape: retail keeps the
// find result in EBP across the walk (returning it at exhaustion/empty), so
// the source reuses `found` for the chk-true arm (found = chk; break) with a
// single return instead of an early return that lets MSVC fold it to xor.
// The walk advances the node at the loop bottom and inlines the payload
// into the ask call, reproducing retail's EDI/ESI schedule. Owner and
// method name are address-derived. The two direct calls reach their bodies
// through the ILT stubs 0x00012224 (-> 0x002493A0, the matched
// Rva002493A0::find list search) and 0x00036C05 (-> 0x00248AE0, the matched
// bfmeAskDG query); those stubs are referenced by their ledger names
// ?j_00012224@@YAXXZ and ?j_00036c05@@YAXXZ through a union thiscall cast
// (thiscall, one stack slot, EAX out).

struct BfmeNodeAD10
{
	BfmeNodeAD10 *m_next;			// +0x00
	char m_pad[4];				// +0x04
	void *m_payload;				// +0x08
};

class BfmeCheckAD10
{
public:
	virtual void bfmeV00(); virtual void bfmeV01(); virtual void bfmeV02();
	virtual void bfmeV03(); virtual void bfmeV04(); virtual void bfmeV05();
	virtual bool bfmeV06(void *a);
};

// The two direct calls reach their bodies through the ILT stubs the ledger
// defines as ?j_00012224@@YAXXZ (game/gen_small/thunks_008.cpp) and
// ?j_00036c05@@YAXXZ (game/gen_small/thunks_026.cpp).  Reference those stub
// names through the thiscall cast so the emitted calls are unchanged.
extern void j_00012224();
extern void j_00036c05();

class Gen_0021AD10
{
public:
	void *bfmeFind(void *a);
};

// ?bfmeFind@Gen_0021AD10@@QAEPAXPAX@Z
void *Gen_0021AD10::bfmeFind(void *a)
{
	union { void (*plain)(void); void *(Gen_0021AD10::*find)(void *); } findCall;
	findCall.plain = j_00012224;
	void *found = (this->*findCall.find)(a);

	if (found == 0) {
		BfmeNodeAD10 *n = (*(BfmeNodeAD10 **)((char *)this + 0x9BC))->m_next;

		if (n != *(BfmeNodeAD10 **)((char *)this + 0x9BC)) {
			do {
				union { void (*plain)(void); void *(Gen_0021AD10::*ask)(void *); } askCall;
				askCall.plain = j_00036c05;
				void *chk = (this->*askCall.ask)(n->m_payload);

				if (chk != 0) {
					BfmeCheckAD10 *c = (BfmeCheckAD10 *)chk;
					if (c->bfmeV06(a)) {
						found = chk;
						break;
					}
				}

				n = n->m_next;
			} while (n != *(BfmeNodeAD10 **)((char *)this + 0x9BC));
		}
	}

	return found;
}
