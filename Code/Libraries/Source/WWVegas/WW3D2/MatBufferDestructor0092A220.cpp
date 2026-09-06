// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: MatBufferClass::~MatBufferClass at 0x0092A220 (131 B):
// release every VertexMaterialClass element (inline Release_Ref: --NumRefs,
// Delete_This through vtable slot 0, then null the slot), then the inlined
// ShareBufferClass<VertexMaterialClass*> base destructor (its vtable, delete[]
// of the array) and the RefCountClass base vtable store. Layout: vptr,
// NumRefs +4, Array +8, +0xc unused here, Count +0x10.
class VertexMaterialClass
{
public:
	virtual void Delete_This() = 0;
	void Release_Ref()
	{
		if (--NumRefs == 0)
			Delete_This();
	}
	int NumRefs;
};

extern void __cdecl operator delete[](void *) throw();

class RefCountClass
{
public:
	virtual ~RefCountClass() {}
	int NumRefs;
};

template <class T>
class ShareBufferClass : public RefCountClass
{
public:
	virtual ~ShareBufferClass()
	{
		delete[] Array;
	}
	T *Array;
	int m_unused0c;
	int Count;
};

class MatBufferClass : public ShareBufferClass<VertexMaterialClass *>
{
public:
	virtual ~MatBufferClass();
};

MatBufferClass::~MatBufferClass()
{
	for (int i = 0; i < Count; i++)
	{
		if (Array[i])
		{
			Array[i]->Release_Ref();
			Array[i] = 0;
		}
	}
}
