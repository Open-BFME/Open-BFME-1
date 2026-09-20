// ?link@Rva007C2E50@@QAEXPAV?$vector@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@PAVRva007C2E50Resource@@@Z
// partial score=0.15 date=2026-09-20
// cl: /DNDEBUG /MD /EHsc
// stlport
// Carved body at retail RVA 0x007C2E50 (161 B). Reverse symbols pin the ILT
// as the BfmeVolumetricShadowBufferOwner constructor: createShadow at
// 0x007C3260 passes the manager field at this+8 plus a BfmeShadowResource.
// The body calls resource vtable slots 3 (0xc), 5 (0x14), 27 (0x6c) and
// 29 (0x74), inserts a returned pointer into a vector<Object*> (real
// _M_insert_overflow instantiation, pinned at 0x004486bc), and recurses on
// itself through ILT thunk 0x0002A2F2 for each child the resource vtable
// slot 29 yields.  No proven resource vtable ABI or vector layout beyond
// what the bytes themselves show; every name below is address-derived and
// the vtable is walked through a raw-slot virtual class.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

class Object;

class Rva007C2E50Resource
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual Object *slot03();
	virtual void slot04();
	virtual Object *slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21();
	virtual void slot22(); virtual void slot23(); virtual void slot24(); virtual void slot25();
	virtual void slot26();
	virtual int slot27();
	virtual void slot28();
	virtual Object *slot29(int index);
};

class Rva007C2E50
{
public:
	void link(_STL::vector<Object *> *vec, Rva007C2E50Resource *resource);
};

// ?link@Rva007C2E50@@QAEXPAV?$vector@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@PAVRva007C2E50Resource@@@Z
void Rva007C2E50::link(_STL::vector<Object *> *vec, Rva007C2E50Resource *resource)
{
	if (!resource->slot03())
	{
		Object *created = resource->slot05();
		vec->push_back(created);
	}

	int count = resource->slot27();

	for (int i = count; i > 0; --i)
	{
		Object *child = resource->slot29(i - 1);
		if (child)
		{
			((Rva007C2E50 *)vec)->link((_STL::vector<Object *> *)vec, (Rva007C2E50Resource *)child);

			unsigned int *childWords = (unsigned int *)child;
			if (--childWords[1] == 0)
			{
				((Rva007C2E50Resource *)child)->slot00();
			}
		}
	}
}
