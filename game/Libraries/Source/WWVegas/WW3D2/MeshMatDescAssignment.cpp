// cl: /DNDEBUG /MD /EHsc
// Recovered from the Zero Hour MeshMatDescClass::operator= algorithm in
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshmatdesc.cpp.
// Copyright 2025 Electronic Arts Inc. Licensed under GPL-3.0-or-later.
//
// BFME layout is corroborated by the matched copy constructor at 0x0092C0D0,
// which calls this body at 0x0092BB00. Textures are owning one-pointer handles:
// assignment retains the low-word texture count and calls TextureBaseClass's
// out-of-line release. Each texture-array copy calls the owning-element
// ShareBuffer constructor at 0x00929EA0, then installs TexBufferClass's vtable
// at VA 0x0113C340; there is no second per-element retain loop. Material arrays
// retain raw pointers through RawBuffer, as in the matched MatBuffer copy.
// These declarations are local ABI views, leaving shared headers unchanged.
void *operator new(unsigned int size);
void operator delete(void *block);
class RefCountClass
{
public:
    void Add_Ref() { ++NumRefs; }
    void Release_Ref() { if (--NumRefs == 0) Delete_This(); }
    virtual void Delete_This();
protected:
    virtual ~RefCountClass();
    int NumRefs;
};
class TextureBaseClass : public RefCountClass
{
public:
    void Add_Ref() { ++*(unsigned short *)((char *)this + 4); }
    void Release_Ref();
};
class TextureClass : public TextureBaseClass {};
template<class T> class RefCountPtr
{
public:
    const RefCountPtr &operator=(const RefCountPtr &rhs)
    {
        if (rhs.Referent) rhs.Referent->Add_Ref();
        if (Referent) Referent->Release_Ref();
        Referent = rhs.Referent;
        return *this;
    }
private:
    T *Referent;
};
class ShaderClass { unsigned int ShaderBits; };
class VertexMaterialClass : public RefCountClass {};
template<class T> class ShareBufferClass : public RefCountClass
{
public:
    ShareBufferClass(const ShareBufferClass &);
protected:
    virtual ~ShareBufferClass();
    T *RawBuffer;
    T *Array;
    int Count;
    int Alignment;
};
class TexBufferClass : public ShareBufferClass<RefCountPtr<TextureClass> >
{
public:
    TexBufferClass(const TexBufferClass &that) : ShareBufferClass<RefCountPtr<TextureClass> >(that) {}
    virtual ~TexBufferClass();
};
class MatBufferClass : public ShareBufferClass<VertexMaterialClass *>
{
public:
    MatBufferClass(const MatBufferClass &that) : ShareBufferClass<VertexMaterialClass *>(that)
    {
        for (int i = 0; i < Count; ++i)
            if (RawBuffer[i]) RawBuffer[i]->Add_Ref();
    }
    virtual ~MatBufferClass();
};
class UVBufferClass : public RefCountClass {};
class MeshMatDescClass
{
public:
    MeshMatDescClass &operator=(const MeshMatDescClass &that);
private:
    enum { MAX_PASSES = 4, MAX_TEX_STAGES = 2, MAX_UV_ARRAYS = 8, MAX_COLOR_ARRAYS = 2 };
    int PassCount, VertexCount, PolyCount; // 0x00, 0x04, 0x08
    UVBufferClass *UV[MAX_UV_ARRAYS];
    int UVSource[MAX_PASSES][MAX_TEX_STAGES];
    ShareBufferClass<unsigned> *ColorArray[2];
    int DCGSource[MAX_PASSES], DIGSource[MAX_PASSES];
    RefCountPtr<TextureClass> Texture[MAX_PASSES][MAX_TEX_STAGES];
    ShaderClass Shader[MAX_PASSES];
    VertexMaterialClass *Material[MAX_PASSES];
    TexBufferClass *TextureArray[MAX_PASSES][MAX_TEX_STAGES];
    MatBufferClass *MaterialArray[MAX_PASSES];
    ShareBufferClass<ShaderClass> *ShaderArray[MAX_PASSES];
};
#define REF_PTR_SET(dst, src) { if (src) (src)->Add_Ref(); if (dst) (dst)->Release_Ref(); (dst) = (src); }
#define REF_PTR_RELEASE(p) { if (p) { (p)->Release_Ref(); (p) = 0; } }
#define NEW_REF(type, args) new type args

MeshMatDescClass &
MeshMatDescClass::operator = (const MeshMatDescClass & that)
{
	if (this != &that) {

		PassCount = that.PassCount;
		VertexCount = that.VertexCount;
		PolyCount = that.PolyCount;

		for (int array=0; array<MAX_COLOR_ARRAYS; array++) {
			REF_PTR_SET(ColorArray[array],that.ColorArray[array]);
		}

		for (int uvarray=0; uvarray<MAX_UV_ARRAYS; uvarray++) {
			REF_PTR_SET(UV[uvarray],that.UV[uvarray]);
		}

		for (int pass=0; pass<MAX_PASSES; pass++) {
			for (int stage=0; stage < MAX_TEX_STAGES; stage++) {
				UVSource[pass][stage] = that.UVSource[pass][stage];
				Texture[pass][stage] = that.Texture[pass][stage];

				// make our own array of texture pointers.
				REF_PTR_RELEASE(TextureArray[pass][stage]);
				if (that.TextureArray[pass][stage]) {
					TextureArray[pass][stage] = NEW_REF(TexBufferClass,(*that.TextureArray[pass][stage]));
				}
			}

			DCGSource[pass] = that.DCGSource[pass];
			DIGSource[pass] = that.DIGSource[pass];

			Shader[pass] = that.Shader[pass];
			REF_PTR_SET(Material[pass],that.Material[pass]);

			// make our own arrays of shaders and vertex material pointers
			// NOTE: We don't just add-ref these arrays, we make our own copies.
			// The only time we add-ref these arrays are when we make alternate material
			// representations within this mesh... Then we re-use the same arrays in different
			// passes...
			REF_PTR_RELEASE(MaterialArray[pass]);
			if (that.MaterialArray[pass]) {
				MaterialArray[pass] = NEW_REF(MatBufferClass,(*that.MaterialArray[pass]));
			}
			REF_PTR_RELEASE(ShaderArray[pass]);
			if (that.ShaderArray[pass]) {
				ShaderArray[pass] = NEW_REF(ShareBufferClass<ShaderClass>,(*that.ShaderArray[pass]));
			}
		}
	}
	return *this;
}

