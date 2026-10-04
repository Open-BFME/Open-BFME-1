// cl: /DNDEBUG /MD /EHsc
// Clean C++ body of the vector assignment that MaterialInfoClass's copy
// constructor calls at retail 0x00930E00 -> 0x0092F810 (249 bytes), replacing
// the 2026-08-11 Open-BFME5 __emit lift that used to hold this address under
// the name ?4?$VectorClass@VProxyClass@@@@QAEAAV0@ABV0@@Z.
//
// The element is upstream WWLib/ref_ptr.h RefCountPtr<TextureClass>: the
// element ctor/dtor pair handed to the CRT array-new helper at 0x009F6EE4 is
// the ILT thunk of ??1?$RefCountPtr@VTextureClass@@ at 0x00030652, the copy
// step is upstream's operator= (Add_Ref on the source, Release_Ref on the
// destination, then the store), and the inlined Add_Ref is the WORD refcount
// increment at [this+4] that BFME's TextureClass carries. The element is four
// bytes, where the repo's own ?Resize@?$VectorClass@VProxyClass@@ (0x00934630)
// and ?Clear@?$VectorClass@VProxyClass@@ (0x00934780) prove ProxyClass costs
// 0x74; the proof is
// targets/game/reverse/identity_evidence/0092f810-refcountptr-texture-element.md.
//
// The shim class reproduces the VectorClass base layout the callers observe:
// vptr at +0, Vector at +4, VectorMax at +8, IsValid at +0xC, IsAllocated at
// +0xD. The four virtuals are the vftable slots the retail table at
// 0x0113C5FC holds (slot 1 operator== 0x0092FC80, slot 2 Resize 0x009302C0,
// slot 3 Clear 0x00930460), so the Clear dispatch lands on the call at +0x2A.

// Retail allocates the element block through the array form (0x00881F70 is
// ??_U@YAPAXI@Z) and unwinds it through 0x00881EF0 (??_V@YAXPAX@Z), so both
// array operators are declared here; without the first, MSVC 7.1 lowers
// `new T[n]` onto the scalar operator new and the shape is right but the
// relocation is not.
void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *) throw();

class TextureClass
{
public:
	__forceinline void Add_Ref() { ++RefCountAndFlags; }
	void Release_Ref();

private:
	void *Vtable;
	unsigned short RefCountAndFlags;
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	RefCountPtr(RefCountPtr<T> const &rhs) : Referent(rhs.Referent)
	{
		if (Referent) {
			Referent->Add_Ref();
		}
	}
	~RefCountPtr()
	{
		if (Referent) {
			Referent->Release_Ref();
		}
	}

	RefCountPtr<T> &operator=(RefCountPtr<T> const &rhs)
	{
		if (rhs.Referent) {
			rhs.Referent->Add_Ref();
		}
		if (Referent) {
			Referent->Release_Ref();
		}
		Referent = rhs.Referent;
		return *this;
	}

private:
	T *Referent;
};

typedef RefCountPtr<TextureClass> TextureVectorCell;

class TextureVectorBaseCtorShim
{
public:
	__declspec(noinline) TextureVectorBaseCtorShim(int, TextureVectorCell const *);
	virtual ~TextureVectorBaseCtorShim();
	virtual bool operator == (TextureVectorBaseCtorShim const &) const;
	virtual bool Resize(int, TextureVectorCell const * = 0);
	virtual void Clear(void);
	TextureVectorBaseCtorShim &operator=(TextureVectorBaseCtorShim const &that);

private:
	TextureVectorCell *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

TextureVectorBaseCtorShim &TextureVectorBaseCtorShim::operator=
	(TextureVectorBaseCtorShim const &that)
{
	if (this != &that) {
		Clear();
		IsValid = false;
		VectorMax = that.VectorMax;
		if (VectorMax) {
			Vector = new TextureVectorCell[VectorMax];
			if (Vector) {
				IsAllocated = true;
				IsValid = true;
				for (int index = 0; index < VectorMax; ++index) {
					Vector[index] = that.Vector[index];
				}
			}
		} else {
			Vector = 0;
			IsAllocated = false;
			IsValid = true;
		}
	}
	return *this;
}
