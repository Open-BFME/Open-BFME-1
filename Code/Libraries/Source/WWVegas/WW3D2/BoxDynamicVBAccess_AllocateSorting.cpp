// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x0091F040, 274 bytes. Same shape as the already-matched
// DynamicIBAccessClass::Allocate_Sorting_Dynamic_Buffer at 0x0091D6B0, with
// the vertex-buffer layout (count at +0x10, offset at +0x12, buffer at +0x14)
// and a 0x20-byte SortingVertexBufferClass instead of the 0x18-byte index
// sibling. The BoxDynamicVBAccessClass constructor calls this when Type is
// not BUFFER_TYPE_DYNAMIC_DX8 (2).
//
// Identity: ZH Allocate_Sorting_Dynamic_Buffer; the matched constructor at
// 0x0091F730 names this callee, and the 274B body is instruction-identical
// to the IB twin aside from those offsets and the allocation size.

class W3DMPO
{
};

class RefCountClass
{
public:
	RefCountClass() : NumRefs(1) {}

	void Add_Ref() const
	{
		++NumRefs;
	}

	void Release_Ref() const
	{
		--NumRefs;
		if (NumRefs == 0) {
			const_cast<RefCountClass *>(this)->Delete_This();
		}
	}

	virtual void Delete_This();

protected:
	virtual ~RefCountClass();

private:
	mutable int NumRefs;
};

class VertexBufferClass : public W3DMPO, public RefCountClass
{
protected:
	virtual ~VertexBufferClass();

	int engine_refs;
	unsigned short vertex_count;
	unsigned type;
	void *fvf_info;
	unsigned bfme_field18;
};

class SortingVertexBufferClass : public VertexBufferClass
{
public:
	SortingVertexBufferClass(unsigned short vertex_count);

protected:
	void *vertex_buffer;
};

class BoxDynamicVBAccessClass
{
public:
	void Allocate_Sorting_Dynamic_Buffer();

private:
	unsigned unused[4];
	unsigned short VertexCount;
	unsigned short VertexBufferOffset;
	VertexBufferClass *VertexBuffer;
};

#define DEFAULT_VB_SIZE 5000

static bool _DynamicSortingVertexArrayInUse = false;
static SortingVertexBufferClass *_DynamicSortingVertexArray;
static unsigned short _DynamicSortingVertexArraySize = 0;
static unsigned short _DynamicSortingVertexArrayOffset = 0;

#define REF_PTR_RELEASE(x) { if (x) { x->Release_Ref(); x = 0; } }
#define REF_PTR_SET(dst, src) { if (src) (src)->Add_Ref(); if (dst) (dst)->Release_Ref(); (dst) = (src); }

void BoxDynamicVBAccessClass::Allocate_Sorting_Dynamic_Buffer()
{
	_DynamicSortingVertexArrayInUse = true;

	unsigned new_vertex_count = _DynamicSortingVertexArrayOffset + VertexCount;
	if (new_vertex_count > _DynamicSortingVertexArraySize) {
		REF_PTR_RELEASE(_DynamicSortingVertexArray);
		_DynamicSortingVertexArraySize = new_vertex_count;
		if (_DynamicSortingVertexArraySize < DEFAULT_VB_SIZE) {
			_DynamicSortingVertexArraySize = DEFAULT_VB_SIZE;
		}
	}

	if (!_DynamicSortingVertexArray) {
		_DynamicSortingVertexArray = new SortingVertexBufferClass(_DynamicSortingVertexArraySize);
		_DynamicSortingVertexArrayOffset = 0;
	}

	REF_PTR_SET(VertexBuffer, _DynamicSortingVertexArray);
	VertexBufferOffset = _DynamicSortingVertexArrayOffset;
}
