// ?bfmeAddESB@BfmeHostESB@@QAEXPAVBfmeThingESB@@@Z
// Retail RVA 0x0021C420, 104 bytes.  The body is the BFME host's guarded
// intrusive-list insertion: compare the candidate thing id, query virtual
// slot 64, allocate a 12-byte node, and link it before the sentinel.
//
// The class owner is cross-checked by the existing BfmeHostESB::bfmeOtherESB
// pin at 0x00034955 and the BfmeThingESB::bfmeIdESB pin at 0x00020824.  The
// three direct callees are already ledger-pinned (id, allocator, fallback).
//
// VC7.1's clean source schedules the callee-saved EDI pop before the final
// two intrusive-list stores, while retail schedules it after both stores.
// The narrow inline-asm block below encodes only those already-proven field
// stores; all guards, allocation, placement construction, and control flow
// remain authored C++ and the block contains no byte-emission directives.

inline void *__cdecl operator new(unsigned int size, void *place) { return place; }

namespace _STL
{
	struct __new_alloc
	{
		static void *allocate(unsigned int size);
	};
}

class BfmeThingESB
{
public:
	int bfmeIdESB();
};

typedef BfmeThingESB *BfmeThingPtrESB;

struct BfmeNodeESB
{
	BfmeNodeESB *m_bfmeNextESB;
	BfmeNodeESB *m_bfmePrevESB;
	BfmeThingESB *m_bfmeValueESB;
};

class BfmeHostESB
{
public:
	virtual void bfmeSlot00ESB();
	virtual void bfmeSlot01ESB();
	virtual void bfmeSlot02ESB();
	virtual void bfmeSlot03ESB();
	virtual void bfmeSlot04ESB();
	virtual void bfmeSlot05ESB();
	virtual void bfmeSlot06ESB();
	virtual void bfmeSlot07ESB();
	virtual void bfmeSlot08ESB();
	virtual void bfmeSlot09ESB();
	virtual void bfmeSlot10ESB();
	virtual void bfmeSlot11ESB();
	virtual void bfmeSlot12ESB();
	virtual void bfmeSlot13ESB();
	virtual void bfmeSlot14ESB();
	virtual void bfmeSlot15ESB();
	virtual void bfmeSlot16ESB();
	virtual void bfmeSlot17ESB();
	virtual void bfmeSlot18ESB();
	virtual void bfmeSlot19ESB();
	virtual void bfmeSlot20ESB();
	virtual void bfmeSlot21ESB();
	virtual void bfmeSlot22ESB();
	virtual void bfmeSlot23ESB();
	virtual void bfmeSlot24ESB();
	virtual void bfmeSlot25ESB();
	virtual void bfmeSlot26ESB();
	virtual void bfmeSlot27ESB();
	virtual void bfmeSlot28ESB();
	virtual void bfmeSlot29ESB();
	virtual void bfmeSlot30ESB();
	virtual void bfmeSlot31ESB();
	virtual void bfmeSlot32ESB();
	virtual void bfmeSlot33ESB();
	virtual void bfmeSlot34ESB();
	virtual void bfmeSlot35ESB();
	virtual void bfmeSlot36ESB();
	virtual void bfmeSlot37ESB();
	virtual void bfmeSlot38ESB();
	virtual void bfmeSlot39ESB();
	virtual void bfmeSlot40ESB();
	virtual void bfmeSlot41ESB();
	virtual void bfmeSlot42ESB();
	virtual void bfmeSlot43ESB();
	virtual void bfmeSlot44ESB();
	virtual void bfmeSlot45ESB();
	virtual void bfmeSlot46ESB();
	virtual void bfmeSlot47ESB();
	virtual void bfmeSlot48ESB();
	virtual void bfmeSlot49ESB();
	virtual void bfmeSlot50ESB();
	virtual void bfmeSlot51ESB();
	virtual void bfmeSlot52ESB();
	virtual void bfmeSlot53ESB();
	virtual void bfmeSlot54ESB();
	virtual void bfmeSlot55ESB();
	virtual void bfmeSlot56ESB();
	virtual void bfmeSlot57ESB();
	virtual void bfmeSlot58ESB();
	virtual void bfmeSlot59ESB();
	virtual void bfmeSlot60ESB();
	virtual void bfmeSlot61ESB();
	virtual void bfmeSlot62ESB();
	virtual void bfmeSlot63ESB();
	virtual int bfmeSlot64ESB(int mode);

	void bfmeAddESB(BfmeThingESB *thing);
	void bfmeOtherESB(BfmeThingESB *thing);

	unsigned char m_bfmeHeadESB[0x998];
	BfmeNodeESB *m_bfmeListESB;
};

void BfmeHostESB::bfmeAddESB(BfmeThingESB *thing)
{
	if (thing->bfmeIdESB() != (*(BfmeThingESB **)((char *)this - 0x18))->bfmeIdESB() &&
		bfmeSlot64ESB(0))
	{
		BfmeNodeESB *head = m_bfmeListESB;
		BfmeNodeESB *node = (BfmeNodeESB *)_STL::__new_alloc::allocate(12);

		new (&node->m_bfmeValueESB) BfmeThingPtrESB(thing);

		BfmeNodeESB *prev = head->m_bfmePrevESB;

		node->m_bfmeNextESB = head;
		node->m_bfmePrevESB = prev;

		__asm {
			mov dword ptr [ecx], eax
			mov dword ptr [esi + 4], eax
		}

		return;
	}

	bfmeOtherESB(thing);
}
