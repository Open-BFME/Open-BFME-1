// BFME stores the texture stages as one-word owning wrappers.  Keeping that
// layout local avoids changing the later vendored MaterialPassClass header,
// while allowing MSVC to emit the retail array-destructor cleanup sequence.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	RefCountClass() : NumRefs(1) {}

	void Release_Ref()
	{
		if (--NumRefs == 0)
			Delete_This();
	}

	virtual void Delete_This() = 0;

protected:
	virtual ~RefCountClass() {}

private:
	int NumRefs;
};

class MaterialPassStage
{
public:
	MaterialPassStage();
	~MaterialPassStage();

private:
	void *Pointer;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/matpass.h
class MaterialPassClass : public RefCountClass
{
public:
	virtual ~MaterialPassClass();

private:
	MaterialPassStage Stages[8];
	int Shader;
	RefCountClass *Material;
	bool EnableOnTranslucentMeshes;
	int CullVolume;
};

MaterialPassClass::~MaterialPassClass()
{
	if (Material)
	{
		Material->Release_Ref();
		Material = 0;
	}
}
