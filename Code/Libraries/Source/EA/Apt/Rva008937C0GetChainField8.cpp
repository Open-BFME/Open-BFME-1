// ?rva008937C0GetChainField8@@YAHPAX@Z
// Address-derived: second half of the merged 62-byte window (real boundary
// 0x008937C0 size 0x1E). Look up p via Rva008930C0AptLookup,
// then walk obj->m_50->m_c->m_8, returning 0 if obj is null.
class BfmeNestedBE;
extern BfmeNestedBE *Rva008930C0AptLookup(int value);

int rva008937C0GetChainField8(void* p)
{
	typedef BfmeNestedBE* (__cdecl* Fn)(void*);
	void* obj = ((Fn)Rva008930C0AptLookup)(p);
	if (obj)
	{
		void* c = *(void**)((char*)obj + 0x50);
		void* d = *(void**)((char*)c + 0xc);
		return *(int*)((char*)d + 8);
	}
	return 0;
}
