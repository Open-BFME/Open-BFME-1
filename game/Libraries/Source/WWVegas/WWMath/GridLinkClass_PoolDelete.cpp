// cl: /DNDEBUG /MD /EHsc

// 20-byte null-guarded pool free at retail 0x008DDEB0.
// The scalar operator delete of the pooled GridLinkClass that gridcull.cpp
// allocates: null passes through, anything else goes to the matched
// Free_Object_Memory pool free at 0x008DDA50, reached through the pinned
// ?Free_Object_Memory@ObjectPool@@QAEXPAX@Z view of that body with the
// GridLinkClass pool object at 0x0133D1AC as `this`.
// Address-derived opaque name keeps the address token.

class ObjectPool
{
public:
	void Free_Object_Memory(void *obj);
};

extern ObjectPool g_pool008DDA50;

// ?dup_008ddeb0@@YAXPAX@Z
void __cdecl dup_008ddeb0(void *memory)
{
	if (memory == 0) {
		return;
	}
	g_pool008DDA50.Free_Object_Memory(memory);
}
