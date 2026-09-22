// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// 0x008958D0 -- Rva00893030Manager::find008958D0
//
// Receiver.  Both retail call sites (0x00895A00+0x2E, 0x00895D30+0x2A and
// +0xAF) forward their OWN `this` in ECX (`mov ebp,ecx` / `mov ebx,ecx` then
// `mov ecx,ebx`), so this is a __thiscall member of the class those bodies
// belong to.  That class owns a singly linked list whose head is at +0x00:
// the matched ?remove@Gen_00895200@@QAEXPAX@Z at 0x00895200 loads the head
// with `mov eax,[ecx]`, compares its void* argument against `[node+0x00]`,
// and relinks through `[node+0x04]` -- the same head and the same
// {payload,next} node this walk uses.  The matched ??1BfmeDropObjectA@@QAE@XZ
// at 0x00895260 calls that remove with ECX loaded from
// ?g_rva00893030Manager@@3PAVRva00893030Manager@@A (0x013377D4) and `this` as
// the argument, which is what types the node payload at +0x00 as
// BfmeDropObjectA* and what supplies the (address-derived) receiver name.
//
// Key parameter.  0x00895D30 builds the second argument in place at +0x9E
// with the matched ?bfmeSetVKI@BfmeStrVKI@@QAEXPBD@Z (0x0089E680), passes its
// address at +0xA3, and releases it at +0xB4 with `dec word ptr [eax]` on
// [key] -- so the key is a BfmeStrVKI holding a pooled string-data pointer
// whose refcount is the WORD at +0x00.  ??1BfmeDropObjectA releases the same
// kind of data from BfmeDropObjectA+0x04 (`mov eax,[esi+4]`,
// `dec word ptr [eax]`, pool release via ?g_bfmeStringPool1284), which places
// the string member at +0x04.  The length at +0x02 and the characters at
// +0x08 are witnessed only by this body's own bytes (`movzx ebx,[ebp+2]`,
// `lea esi,[ebp+8]`).
//
// BfmeDropObjectA.  The refcount is the DWORD at +0x00 and the object is 0x18
// bytes: the matched ?Rva00895430Copy@@YAPAPAVBfmeDropObjectA@@PAPAV1@00@Z at
// 0x00895430 does `dec dword ptr [eax]`, then ??1BfmeDropObjectA at 0x00895260
// and `push 0x18` into TheBfmeFree.  This body's found path is the matching
// acquire (`mov ecx,[edx]`, `inc ecx`, `mov [edx],ecx`).
//
// The method name stays address-derived: both callers are still anonymous
// ?d_ dump rows, and no vtable slot or string literal names this body.
//
// ABI: this is NOT a void out-parameter lookup.  It returns a one-pointer
// refcounted handle BY VALUE.  Each call site pushes the key first and the
// sret slot second (`lea eax,[esp+..]; push eax`), so the hidden sret pointer
// is the FIRST stack argument and `ret 8` covers sret + key; the caller then
// reads the single returned word straight back out of that slot
// (0x00895A00+0x33, 0x00895D30+0x2F), null-tests it and dereferences it.
// MSVC must leave the sret pointer in EAX on every exit, which is exactly why
// retail reloads [esp+0x18] into EAX in both exit blocks and falls back to ECX
// for the refcount scratch.  The handle's destructor is what puts the dead
// `mov dword ptr [esp+0x10], 0` cleanup flag in the prologue.  The matched
// ?bfmeGet@Gen_00895650@@QBE?AVBfmeHolderDB@@XZ at 0x00895650
// (Bfme5ThirtyFour.cpp) is the same shape seen from the other side: sret taken
// from [esp+8], one pointer stored, `inc dword ptr [ecx]`, same dead flag.
//
// Shape: the candidate's string member is bound to a const reference and
// `s.m_data` is read three times through it.  That is what leaves retail's
// split address at +0x20..+0x25 (`mov eax,[edx]` / `add eax,4` /
// `mov eax,[eax]`); caching the member in a local -- or any of the folded
// spellings listed in docs/shape_levers.md, "Read the member again instead of
// caching it in a local" -- collapses those three instructions to
// `mov eax,[eax+4]` and shifts the rest of the body.
extern "C" int memcmp(const void *a, const void *b, unsigned int n);

#pragma intrinsic(memcmp)

struct BfmeStringData3AF0
{
public:
	unsigned short m_word0;
	unsigned short m_length;
	unsigned short m_word4;
	unsigned short m_word6;
	char m_data[1];
};

class BfmeStrVKI
{
public:
	BfmeStringData3AF0 *m_data;
};

class BfmeString3AF0
{
public:
	BfmeStringData3AF0 *m_data;
};

class BfmeDropObjectA
{
public:
	int m_refCount;						// +0x00
	BfmeString3AF0 m_string;				// +0x04
};

class Rva00893030Node
{
public:
	BfmeDropObjectA *m_object;				// +0x00
	Rva00893030Node *m_next;				// +0x04
};

class RefHandle008958D0
{
public:
	RefHandle008958D0(void)
	{
		m_object = 0;
	}

	RefHandle008958D0(BfmeDropObjectA *o)
	{
		m_object = o;

		if (o != 0)
			++o->m_refCount;
	}

	~RefHandle008958D0(void)
	{
		if (m_object != 0)
			--m_object->m_refCount;
	}

	BfmeDropObjectA *m_object;				// +0x00
};

class Rva00893030Manager
{
public:
	RefHandle008958D0 find008958D0(BfmeStrVKI *key);

private:
	Rva00893030Node *m_head;				// +0x00
};

// ?find008958D0@Rva00893030Manager@@QAE?AVRefHandle008958D0@@PAVBfmeStrVKI@@@Z
RefHandle008958D0 Rva00893030Manager::find008958D0(BfmeStrVKI *key)
{
	Rva00893030Node *n = m_head;

	if (n != 0)
	{
		BfmeStringData3AF0 *k = key->m_data;
		int len = k->m_length;

		do
		{
			const BfmeString3AF0 &s = n->m_object->m_string;

			if (len == s.m_data->m_length)
			{
				if (k == s.m_data ||
					memcmp(k->m_data, s.m_data->m_data, len) == 0)
					return RefHandle008958D0(n->m_object);
			}

			n = n->m_next;
		}
		while (n != 0);
	}

	return RefHandle008958D0();
}
