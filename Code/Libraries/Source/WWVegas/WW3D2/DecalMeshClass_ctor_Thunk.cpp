// cl: /DNDEBUG /MD /EHs-c-
// readable body of ??0DecalMeshClass@@QAE@PAVMeshClass@@PAVDecalSystemClass@@@Z: Code/Libraries/Source/WWVegas/WW3D2/decalmsh.cpp
// Open-BFME5: DecalMeshClass::DecalMeshClass, retail 0x000FC2E0,
// zh_sweep packet 000fc2e0.
//
// The reference body is two member initialisers and two asserts that vanish
// under NDEBUG. Compiled inside decalmsh.cpp it reproduced every byte but one
// immediate: retail writes 0 to [this+4] where the vendored RefCountClass
// initialises NumRefs to 1.
//
// That is worth stating carefully, because it is NOT a blanket BFME change to
// RefCountClass: W3DShadowGeometry's constructor is already matched in this
// tree from real C++ with NumRefs(1), and it derives from RefCountClass too.
// So either BFME's DecalMeshClass has a different base, or the word at +4 is
// not the reference count for this class. The bytes prove the value and the
// offset; they do not name the field, so it is carried as an unnamed word.
//
// Everything else is unchanged and confirms the rest of the layout: the vptr
// is at +0x00, Parent at +0x08 and DecalSystem at +0x0C, with the base
// initialiser running before the derived vptr store -- which is also why only
// one vtable is stamped.

class MeshClass;
class DecalSystemClass;

// The base as retail spells it: one word at +0x04, zero-initialised, ahead of
// the derived class's own vptr.
class DecalMeshBase
{
public:
	DecalMeshBase(void) : m_word_04(0) {}

protected:
	int m_word_04;											///< +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/decalmsh.h
class DecalMeshClass : public DecalMeshBase
{
public:
	DecalMeshClass(MeshClass *parent, DecalSystemClass *system);

	virtual ~DecalMeshClass(void) {}						///< places the vptr at +0x00

protected:
	MeshClass *Parent;										///< +0x08
	DecalSystemClass *DecalSystem;							///< +0x0C
};

// ??0DecalMeshClass@@QAE@PAVMeshClass@@PAVDecalSystemClass@@@Z
DecalMeshClass::DecalMeshClass(MeshClass * parent,DecalSystemClass * system) :
	Parent(parent),
	DecalSystem(system)
{
}
