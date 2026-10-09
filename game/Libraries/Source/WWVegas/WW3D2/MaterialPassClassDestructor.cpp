// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// Retail ILT110D6 and ILT30652 call the matched BfmeHandleCX ctor/dtor.
// BFME stores the texture stages as one-word owning wrappers.  Keeping that
// layout local avoids changing the later vendored MaterialPassClass header,
// while allowing MSVC to emit the retail array-destructor cleanup sequence.

// Canonical RefCountClass: a local redeclaration with a pure Delete_This emits a
// __purecall vftable under the same COMDAT name as retail's two-slot table.
#include "refcount.h"

class BfmeHandleCX
{
public:
	BfmeHandleCX();
	~BfmeHandleCX();

private:
	void *Pointer;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/matpass.h
class MaterialPassClass : public RefCountClass
{
public:
	MaterialPassClass();
	virtual ~MaterialPassClass();

private:
	BfmeHandleCX Stages[8];
	int Shader;
	RefCountClass *Material;
	bool EnableOnTranslucentMeshes;
	int CullVolume;
};

// ??0MaterialPassClass@@QAE@XZ
MaterialPassClass::MaterialPassClass()
{
	Shader = 0;
	Material = 0;
	CullVolume = 0;
	EnableOnTranslucentMeshes = true;
}

MaterialPassClass::~MaterialPassClass()
{
	if (Material)
	{
		Material->Release_Ref();
		Material = 0;
	}
}

void Force_MaterialPass_Deleting_Destructor(MaterialPassClass *material_pass)
{
	delete material_pass;
}
