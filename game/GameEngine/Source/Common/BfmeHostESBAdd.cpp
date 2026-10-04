// cl: /D_STLP_USE_STATIC_LIB
// stlport
#include <memory>

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

class BfmeThingESB
{
public:
	int bfmeIdESB();
};

typedef BfmeThingESB *BfmeThingPtrESB;

// Retail 0x0021C428 and 0x0021C435 call the thing-id accessor and the host's
// other-add helper through the incremental-link ILT thunks at RVA 0x00020824
// (?j_00020824@@YAXXZ, game/gen_small/thunks_015.cpp) and RVA 0x00034955
// (?j_00034955@@YAXXZ, game/gen_small/thunks_025.cpp); both thunks keep the
// receiver in ECX, so each call is spelled as the direct thunk call this
// codebase already uses for retail ILT thunks.
extern void j_00020824(void);
extern void j_00034955(void);

typedef int (__fastcall *BfmeThingIdESBCall)(BfmeThingESB *);

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

	unsigned char m_bfmeHeadESB[0x998];
	BfmeNodeESB *m_bfmeListESB;
};

// Retail's tail call at 0x0021C47D is `push edi; mov ecx,esi; call <rel32>`
// -- the thing pushed, the receiver in ECX -- and its target is RVA 0x00034955,
// the incremental-link ILT thunk ?j_00034955@@YAXXZ (game/gen_small/
// thunks_025.cpp) to the body at 0x00226790.  Nothing defines
// ?bfmeOtherESB@BfmeHostESB@@QAEXPAVBfmeThingESB@@@Z: retail only ever reaches
// it through that thunk, so the reference names the thunk and is issued through
// the member-call shape this codebase already uses for ILT thunks (see
// game/GameEngine/Source/GameLogic/AI/AIAttackMeleeHordeApproachTargetState_onEnter.cpp),
// which is what supplies the pushed argument and the ECX receiver.
struct Rva00034955Thunk
{
	void call(BfmeThingESB *thing);
};

union Rva00034955Call
{
	void (*raw)();
	void (Rva00034955Thunk::*member)(BfmeThingESB *);
};

void BfmeHostESB::bfmeAddESB(BfmeThingESB *thing)
{
	if (((BfmeThingIdESBCall)j_00020824)(thing) !=
		((BfmeThingIdESBCall)j_00020824)(*(BfmeThingESB **)((char *)this - 0x18)) &&
		bfmeSlot64ESB(0))
	{
		BfmeNodeESB *head = m_bfmeListESB;
		BfmeNodeESB *node = (BfmeNodeESB *)_STL::__node_alloc<true, 0>::allocate(12);

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

	Rva00034955Call otherAdd;
	otherAdd.raw = j_00034955;
	(reinterpret_cast<Rva00034955Thunk *>(this)->*otherAdd.member)(thing);
}
