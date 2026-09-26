// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00239580, complete 101-byte boundary.
//
// The entry has no named caller or recovered vtable owner in the current
// reverse data.  Its boundary and raw ABI are nevertheless clear: ECX is a
// containing object, one four-byte stack argument is retained by `ret 4`, and
// the body walks the circular list at this-0xAC.  Each payload supplies the
// signed key at +0x74.  The map-like tree at this+0x30 is searched for the
// first key which is not less than that value; an equal result is discarded.
// Only a strictly greater tree entry causes the payload's position helper to
// be called.

#define _STLP_NO_EXCEPTIONS 1
#include <map>

struct Rva00239580ListNode
{
	Rva00239580ListNode *m_next;
	Rva00239580ListNode *m_previous;
	void *m_payload;
};

struct Rva00239580Payload
{
	unsigned char m_unreconstructed_000[0x74];
	int m_key;
};

typedef _STL::map<int, Rva00239580Payload *> Rva00239580Map;

// The instruction stream calls the existing 0x001621B ILT.  That ILT lands
// in the already matched BfmeHostTP::bfmeSetPositionTP body at 0x001D0520;
// keep the call target as the generated thunk rather than assigning either
// of the unrelated historical names pinned to that ILT.
extern void j_0001621b(void);

class Rva00239580PositionCall
{
public:
	void apply(const void *position, bool flag);
};

static __forceinline void callRva00239580Position(
	Rva00239580Payload *payload, void *position)
{
	typedef void (Rva00239580PositionCall::*Function)(const void *, bool);
	union
	{
		void (*raw)(void);
		Function member;
	} thunk;
	thunk.raw = j_0001621b;
	(reinterpret_cast<Rva00239580PositionCall *>(payload)->*thunk.member)(
		position, false);
}

class Rva00239580Owner
{
public:
	void walk(void *position);
	char m_unreconstructed_000[0x30];
	Rva00239580Map m_tree;
};

void Rva00239580Owner::walk(void *position)
{
	int key;
	Rva00239580ListNode *entry =
		(*(Rva00239580ListNode **)((char *)this - 0xac))->m_next;
	if (entry == *(Rva00239580ListNode **)((char *)this - 0xac))
		return;

	for (;;)
	{
		Rva00239580Payload *payload =
			(Rva00239580Payload *)entry->m_payload;
		key = payload->m_key;
		if (m_tree.find(key) == m_tree.end())
			callRva00239580Position(payload, position);

		entry = entry->m_next;
		if (entry == *(Rva00239580ListNode **)((char *)this - 0xac))
			break;
	}
}
