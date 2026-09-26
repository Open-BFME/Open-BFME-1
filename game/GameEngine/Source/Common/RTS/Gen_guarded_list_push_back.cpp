// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: four anonymous retail bodies converted from game/gen_asm naked
// dumps to real C++.  All four are the same one-liner --
//
//     if (x == NULL) return;  m_list.push_back(x);
//
// over a _STL::list of 4-byte elements, differing only in which member the
// list is (retail this+0x170, +0x04, +0x08, +0x04) and therefore in size
// (53, 50, 50, 50 bytes).
//
// None of the four is identified and none can be: each is reachable only
// through one ILT thunk, and that thunk has no reference anywhere in the image
// -- no call, no jump, no vtable slot -- so they are linker-retained dead
// code with zero identity evidence.  The names are address-derived on purpose.
//
// The lever that makes this shape reproducible is _STLP_NO_EXCEPTIONS; see
// ResourceGatheringManager_addSupply.cpp in this directory for the mechanism.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <algorithm>

// ?m@Gen_004ae7a0@@QAEXPAX@Z  -- 0x004AE7A0, 53 bytes, list at this+0x170
struct Gen_004ae7a0
{
	void m(void *x);
	char m_slice_pad[0x170];
	_STL::list<void *> m_list;
};

void Gen_004ae7a0::m(void *x)
{
	if (x == NULL)
		return;

	m_list.push_back(x);
}

// ?m@Gen_0048b350@@QAEXPAX@Z  -- 0x0048B350, 50 bytes, list at this+0x04
struct Gen_0048b350
{
	void m(void *x);
	void *m_slice_vtbl;
	_STL::list<void *> m_list;
};

void Gen_0048b350::m(void *x)
{
	if (x == NULL)
		return;

	m_list.push_back(x);
}

// ?m@Gen_00581350@@QAEXPAX@Z  -- 0x00581350, 50 bytes, list at this+0x08
struct Gen_00581350
{
	void m(void *x);
	void *m_slice_vtbl;
	void *m_slice_word1;
	_STL::list<void *> m_list;
};

void Gen_00581350::m(void *x)
{
	if (x == NULL)
		return;

	m_list.push_back(x);
}

// ?m@Gen_00581390@@QAEXPAX@Z  -- 0x00581390, 50 bytes, list at this+0x04
struct Gen_00581390
{
	void m(void *x);
	void *m_slice_vtbl;
	_STL::list<void *> m_list;
};

void Gen_00581390::m(void *x)
{
	if (x == NULL)
		return;

	m_list.push_back(x);
}

// ?m@Gen_000d2240@@QAEXPAX@Z  -- 0x000D2240, 66 bytes, list at this+0x288.
// Same family, one step up: an add-if-absent.  The linear scan is a written-out
// loop with an early `return`, not _STL::find -- find leaves a redundant
// re-test of the result against end() and compares `*it == x` (cmp mem,reg)
// where retail has `x == *it` (cmp reg,mem).
struct Gen_000d2240
{
	void m(void *x);
	char m_slice_pad[0x288];
	_STL::list<void *> m_list;
};

void Gen_000d2240::m(void *x)
{
	_STL::list<void *>::iterator it;
	for (it = m_list.begin(); it != m_list.end(); ++it)
		if (x == *it)
			return;

	m_list.push_back(x);
}

// ?m@Gen_002e0dd0@@QAEXPAX@Z  -- 0x002E0DD0, 71 bytes, list at this+0x08.
// The other add-if-absent, and the counterpart of Gen_000d2240 above: this one
// really is _STL::find, which is what the redundant post-find re-test against
// end() and the `cmp mem,reg` element test name.  The find result must be
// held in a NAMED iterator and compared afterwards -- folding the call into
// the `if` condition makes MSVC reuse the entry-loaded sentinel for the
// re-test and reload for the insert, which is retail's two loads in the
// opposite order.
struct Gen_002e0dd0
{
	void m(void *x);
	char m_slice_pad[0x08];
	_STL::list<void *> m_list;
};

void Gen_002e0dd0::m(void *x)
{
	_STL::list<void *>::iterator it = _STL::find(m_list.begin(), m_list.end(), x);
	if (it == m_list.end())
		m_list.push_back(x);
}
