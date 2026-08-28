// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BFME ShareBufferClass copy-constructor instantiations.

void *operator new[](unsigned int size);

// BFME ShareBufferClass<T> layout (see sharebuf.h): RefCountClass base (vtbl
// + NumRefs), then RawBuffer, Array, Count, and Alignment.  The copy
// constructor allocates a fresh buffer and preserves the aligned view used by
// the retail UInt and VertexMaterial pointer instantiations.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
    RefCountClass(void) : NumRefs(1) {}
    RefCountClass(const RefCountClass &) : NumRefs(1) {}
    void Add_Ref(void) { NumRefs++; }
    void Release_Ref(void);
    int Num_Refs(void) { return NumRefs; }
    virtual void Delete_This(void);

protected:
    virtual ~RefCountClass(void) {}

private:
    int NumRefs;
};

class VertexMaterialClass;

template <class Type>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/sharebuf.h
class ShareBufferClass : public RefCountClass
{
public:
    ShareBufferClass(const ShareBufferClass &);

protected:
    Type *RawBuffer;
    Type *Array;
    int Count;
    int Alignment;
};

template <class Type>
ShareBufferClass<Type>::ShareBufferClass(const ShareBufferClass<Type> &that) :
    Count(that.Count)
{
    Alignment = that.Alignment;
    void *raw;
    if (Alignment == 0) {
        raw = ::operator new[](Count * sizeof(Type));
        Array = (Type *)raw;
    } else {
        raw = ::operator new[](Count * sizeof(Type) + Alignment);
        Array = (Type *)(((unsigned int)raw + Alignment - 1) & ~(unsigned int)(Alignment - 1));
    }
    RawBuffer = (Type *)raw;
    for (int i = 0; i < Count; i++) {
        Array[i] = that.Array[i];
    }
}

template ShareBufferClass<unsigned int>::ShareBufferClass(
    const ShareBufferClass<unsigned int> &);

template ShareBufferClass<VertexMaterialClass *>::ShareBufferClass(
    const ShareBufferClass<VertexMaterialClass *> &);
