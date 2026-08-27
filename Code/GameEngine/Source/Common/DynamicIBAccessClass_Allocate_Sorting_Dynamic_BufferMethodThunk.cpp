// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

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

class IndexBufferClass : public W3DMPO, public RefCountClass
{
protected:
    virtual ~IndexBufferClass();

    int engine_refs;
    unsigned short index_count;
    unsigned type;
};

class SortingIndexBufferClass : public IndexBufferClass
{
public:
    SortingIndexBufferClass(unsigned short index_count);

protected:
    unsigned short *index_buffer;
};

class DynamicIBAccessClass : public W3DMPO
{
public:
    void Allocate_Sorting_Dynamic_Buffer();

private:
    unsigned Type;
    unsigned short IndexCount;
    unsigned short IndexBufferOffset;
    IndexBufferClass *IndexBuffer;
};

#define DEFAULT_IB_SIZE 5000

static bool _DynamicSortingIndexArrayInUse = false;
static SortingIndexBufferClass *_DynamicSortingIndexArray;
static unsigned short _DynamicSortingIndexArraySize = 0;
static unsigned short _DynamicSortingIndexArrayOffset = 0;

#define REF_PTR_RELEASE(x) { if (x) { x->Release_Ref(); x = 0; } }
#define REF_PTR_SET(dst, src) { if (src) (src)->Add_Ref(); if (dst) (dst)->Release_Ref(); (dst) = (src); }

// ?Allocate_Sorting_Dynamic_Buffer@DynamicIBAccessClass@@QAEXXZ
void DynamicIBAccessClass::Allocate_Sorting_Dynamic_Buffer()
{
    _DynamicSortingIndexArrayInUse = true;

    unsigned new_index_count = _DynamicSortingIndexArrayOffset + IndexCount;
    if (new_index_count > _DynamicSortingIndexArraySize) {
        REF_PTR_RELEASE(_DynamicSortingIndexArray);
        _DynamicSortingIndexArraySize = new_index_count;
        if (_DynamicSortingIndexArraySize < DEFAULT_IB_SIZE) {
            _DynamicSortingIndexArraySize = DEFAULT_IB_SIZE;
        }
    }

    if (!_DynamicSortingIndexArray) {
        _DynamicSortingIndexArray = new SortingIndexBufferClass(_DynamicSortingIndexArraySize);
        _DynamicSortingIndexArrayOffset = 0;
    }

    REF_PTR_SET(IndexBuffer, _DynamicSortingIndexArray);
    IndexBufferOffset = _DynamicSortingIndexArrayOffset;
}
