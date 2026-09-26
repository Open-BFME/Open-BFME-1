// ?rva008937A0GetField18@@YAHPAX@Z
// Address-derived: the assigned 62-byte window actually spans two adjacent
// functions (0x008937A0 size 0x20, 0x008937C0 size 0x1E). This is the first:
// look up p via Rva008930C0AptLookup, then walk obj->m_50->m_18,
// returning -1 if either pointer is null.
class BfmeNestedBE;
extern BfmeNestedBE *Rva008930C0AptLookup(int value);

int rva008937A0GetField18(void* p)
{
	typedef BfmeNestedBE* (__cdecl* Fn)(void*);
	void* obj = ((Fn)Rva008930C0AptLookup)(p);
	if (obj)
	{
		void* f50 = *(void**)((char*)obj + 0x50);
		if (f50)
			return *(int*)((char*)f50 + 0x18);
	}
	return -1;
}
