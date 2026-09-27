// cl: /DNDEBUG /MD /EHsc

// 20-byte null-guarded pool free at retail 0x009DBF40.
// The scalar operator delete of the pooled MultiListNodeClass that the
// GenericMultiListClass in multilist.cpp allocates: null passes through,
// anything else goes to the matched Free_Object_Memory pool free at
// 0x009DBEB0, reached through the pinned ?Free_Object_Memory@ObjectPool@@QAEXPAX@Z
// view of that body with the pool object at 0x0134ECD4 as `this`.
// Address-derived opaque name keeps the address token.

class ObjectPool
{
public:
	void Free_Object_Memory(void *obj);
};

extern ObjectPool g_pool009DBEB0;

// ?dup_009dbf40@@YAXPAX@Z
void __cdecl dup_009dbf40(void *memory)
{
	if (memory == 0) {
		return;
	}
	g_pool009DBEB0.Free_Object_Memory(memory);
}
