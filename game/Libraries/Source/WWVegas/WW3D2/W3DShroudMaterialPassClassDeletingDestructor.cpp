// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
//
// Open-BFME: protected scalar-deleting destructor for W3DShroudMaterialPassClass.
// Vtable 0x00D209C8 slots name this class (?Install_Materials@W3DShroudMaterialPassClass@@UBEXXZ); its slot zero routes
// through ILT 0x0003CA15 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00016DC9 reaches cleanup body 0x00933420.

// ??1W3DShroudMaterialPassClass@@UAE@XZ (retail 0x00702580, 5 B) is the
// implicit destructor: a bare `jmp ??1MaterialPassClass@@UAE@XZ` (0x00933420)
// with no vtable re-seat, so the class declares no destructor of its own and
// derives from MaterialPassClass, whose virtual destructor is matched in
// MaterialPassClassDestructor.cpp.
// Retail's ??_7MaterialPassClass (0x0113C884) has four slots: Delete_This,
// the deleting destructor, Install_Materials and UnInstall_Materials. A
// one-slot private view emitted a different COMDAT ahead of the canonical
// one in MaterialPassClassDestructor.cpp, so declare the same virtuals.
#include "refcount.h"

class MaterialPassClass : public RefCountClass
{
public:
	MaterialPassClass();
	virtual ~MaterialPassClass();
	virtual void Install_Materials(void) const;
	virtual void UnInstall_Materials(void) const { }

private:
	void *Stages[8];
	int Shader;
	RefCountClass *Material;
	bool EnableOnTranslucentMeshes;
	int CullVolume;
};

class W3DShroudMaterialPassClass : public MaterialPassClass
{
private:
	friend void forceW3DShroudMaterialPassClassDeletingDestructor();
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceW3DShroudMaterialPassClassDeletingDestructor(const W3DShroudMaterialPassClass &that)
{
	W3DShroudMaterialPassClass value(that);
}
