// ?Rva008FEF60Method@@YA_NPAVRenderObjClass@@PAPAVTextureClass@@H@Z
// partial score=0.19 date=2026-09-21
// ?d_008fef60@@YAXXZ
// cl: /DNDEBUG /MD /EHsc
//
// Address-derived method; the retail owner class is unknown, so the owning
// class and the ebx/index arguments keep the address token.  edi (this) is
// used only through RenderObjClass's proven vtable -- slot 0x150 is
// Get_Material_Info(), matched by the RenderObjClass layout in
// Rva008FEB90MaterialUnique.cpp/Rva00739B30RenderObjectUnique.cpp -- so this
// body swaps a MaterialInfoClass's texture at a given index for a caller-
// supplied TextureClass*, skipping the swap when the material's own bound
// field (+0x30) does not clear the index and reusing the neighbouring
// Bfme5TextureArray::bfmeSetSlot shape (Bfme5ReadyQueue.cpp) for the actual
// slot store.  The TextureClass** argument arrives in ebx with no stack
// load and no save/restore in the body -- a private register convention
// (docs/shape_levers.md); ebx is left address-derived here too.

class MeshClass;
class MaterialInfoClass;

class RefCountClass
{
public:
	virtual void Delete_This();
	int m_ref_count;
};

// Exact copy of the proven RenderObjClass layout (85 virtuals, Get_Material_Info
// at +0x150) from the already-landed Rva008FEB90MaterialUnique.cpp.
class RenderObjClass : public RefCountClass
{
public:
	virtual void _bfme_ro_v1();
	virtual void _bfme_ro_v2();
	virtual int Class_ID() const;
	virtual void _bfme_ro_v4();
	virtual MeshClass *Mesh_Self();
	virtual void _bfme_ro_v6();
	virtual void _bfme_ro_v7();
	virtual void _bfme_ro_v8();
	virtual void _bfme_ro_v9();
	virtual void _bfme_ro_v10();
	virtual void _bfme_ro_v11();
	virtual void _bfme_ro_v12();
	virtual void _bfme_ro_v13();
	virtual void _bfme_ro_v14();
	virtual void _bfme_ro_v15();
	virtual void _bfme_ro_v16();
	virtual void _bfme_ro_v17();
	virtual void _bfme_ro_v18();
	virtual void _bfme_ro_v19();
	virtual void _bfme_ro_v20();
	virtual void _bfme_ro_v21();
	virtual void _bfme_ro_v22();
	virtual void _bfme_ro_v23();
	virtual void _bfme_ro_v24();
	virtual void _bfme_ro_v25();
	virtual void _bfme_ro_v26();
	virtual int Get_Num_Sub_Objects() const;
	virtual void _bfme_ro_v28();
	virtual RenderObjClass *Get_Sub_Object(int index) const;
	virtual void _bfme_ro_v30();
	virtual void _bfme_ro_v31();
	virtual void _bfme_ro_v32();
	virtual void _bfme_ro_v33();
	virtual void _bfme_ro_v34();
	virtual void _bfme_ro_v35();
	virtual void _bfme_ro_v36();
	virtual void _bfme_ro_v37();
	virtual void _bfme_ro_v38();
	virtual void _bfme_ro_v39();
	virtual void _bfme_ro_v40();
	virtual void _bfme_ro_v41();
	virtual void _bfme_ro_v42();
	virtual void _bfme_ro_v43();
	virtual void _bfme_ro_v44();
	virtual void _bfme_ro_v45();
	virtual void _bfme_ro_v46();
	virtual void _bfme_ro_v47();
	virtual void _bfme_ro_v48();
	virtual void _bfme_ro_v49();
	virtual void _bfme_ro_v50();
	virtual void _bfme_ro_v51();
	virtual void _bfme_ro_v52();
	virtual void _bfme_ro_v53();
	virtual void _bfme_ro_v54();
	virtual void _bfme_ro_v55();
	virtual void _bfme_ro_v56();
	virtual void _bfme_ro_v57();
	virtual void _bfme_ro_v58();
	virtual void _bfme_ro_v59();
	virtual void _bfme_ro_v60();
	virtual void _bfme_ro_v61();
	virtual void _bfme_ro_v62();
	virtual void _bfme_ro_v63();
	virtual void _bfme_ro_v64();
	virtual void _bfme_ro_v65();
	virtual void _bfme_ro_v66();
	virtual void _bfme_ro_v67();
	virtual void _bfme_ro_v68();
	virtual void _bfme_ro_v69();
	virtual void _bfme_ro_v70();
	virtual void _bfme_ro_v71();
	virtual void _bfme_ro_v72();
	virtual void _bfme_ro_v73();
	virtual void _bfme_ro_v74();
	virtual void _bfme_ro_v75();
	virtual void _bfme_ro_v76();
	virtual void _bfme_ro_v77();
	virtual void _bfme_ro_v78();
	virtual void _bfme_ro_v79();
	virtual void _bfme_ro_v80();
	virtual void _bfme_ro_v81();
	virtual void _bfme_ro_v82();
	virtual void _bfme_ro_v83();
	virtual MaterialInfoClass *Get_Material_Info() const;
};

class TextureClass
{
public:
	void Release_Ref(void);

	int m_bfme00;
	unsigned short m_bfmeRefCount;
};

// Same BfmeHandleCX-shaped ref-counted smart pointer Bfme5FiftyOne.cpp
// documents for Gen_007A0340::bfmeGet(), but specialised over TextureClass:
// the destructor here calls TextureClass::Release_Ref() (0x009EB7A0) rather
// than decrementing a raw field, so it keeps its own local copy.
class BfmeHandleCX
{
public:
	BfmeHandleCX(void) { m_bfmeThing = 0; }
	~BfmeHandleCX(void)
	{
		if (m_bfmeThing)
			m_bfmeThing->Release_Ref();
	}

	TextureClass *m_bfmeThing;			// +0x00
};

class MaterialInfoClass : public RefCountClass
{
public:
	virtual void _bfme_mi_v1();
	virtual void _bfme_mi_v2();
	virtual void _bfme_mi_v3();
	virtual void _bfme_mi_v4();
	virtual void *_bfme_mi_slot14();

	BfmeHandleCX Get_Texture(int index) const;

	char m_pad_08[0x30 - 8];
	int m_bfme30;
};

// The trampoline this body reaches through the material's mystery slot 5:
// same shape as Rva0092C3E0::invoke() in IndirectMemberTailThunks.cpp, but
// THIS call site pushes two stack arguments the plain no-arg invoke() there
// does not model, so it keeps its own address-derived declaration.
class Rva0092C3E0Trampoline
{
public:
	void invoke(BfmeHandleCX *out, TextureClass **src);
};

// Reuses the already-landed Bfme5TextureArray::bfmeSetSlot body (Bfme5ReadyQueue.cpp);
// MaterialInfoClass's own Textures vector is layout-compatible at the offset that call reaches.
class Bfme5TextureArray
{
public:
	void bfmeSetSlot(int i, TextureClass **src);
};

// The TextureClass** argument arrives in ebx with no stack load and no
// save/restore -- a private register convention (docs/shape_levers.md).
// A static function with one TU-local, absent-from-retail caller lets
// MSVC 7.1 choose that convention for the extra parameter.
static bool Rva008FEF60Method(RenderObjClass *self, TextureClass **src, int index)
{
	if (!self)
		return false;
	if (!*src)
		return false;

	MaterialInfoClass *material = self->Get_Material_Info();
	if (!material)
		return false;

	if (material->m_bfme30 <= index)
		return false;

	Rva0092C3E0Trampoline *sink = (Rva0092C3E0Trampoline *)material->_bfme_mi_slot14();

	BfmeHandleCX handle = material->Get_Texture(index);
	if (handle.m_bfmeThing == *src)
	{
		if (--material->m_ref_count == 0)
			material->Delete_This();

		return false;
	}

	sink->invoke(&handle, src);

	((Bfme5TextureArray *)material)->bfmeSetSlot(index, src);

	if (--material->m_ref_count == 0)
		material->Delete_This();

	return true;
}

// absent from retail: forces MSVC 7.1's single-call-site register choice
extern "C" bool __fastcall Rva008FEF60Caller(RenderObjClass *self, TextureClass **src, int index)
{
	return Rva008FEF60Method(self, src, index);
}
