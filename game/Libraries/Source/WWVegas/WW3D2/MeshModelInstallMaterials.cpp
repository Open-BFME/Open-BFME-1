// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// BFME MeshModelClass::install_materials, retail RVA 0x0096E7C0 (316 bytes).
// The neighboring mesh chunk readers establish the BFME load-context layout.
// This slice keeps the owning texture handle used by the retail material
// transfer and the inlined MaterialInfo vector append, rather than relying on
// the older GeneralsMD pointer-only declarations in meshmdlio.cpp.

class TextureClass
{
public:
	void Add_Ref(void)
	{
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
	}
	void Release_Ref(void);
};

class BfmeHandleCX
{
public:
	TextureClass *p;

	BfmeHandleCX(void) : p(0) {}
	BfmeHandleCX(const BfmeHandleCX &other) : p(other.p)
	{
		if (p) {
			p->Add_Ref();
		}
	}
	~BfmeHandleCX(void)
	{
		if (p) {
			p->Release_Ref();
		}
	}
};

class VertexMaterialClass
{
public:
	virtual void Delete_This(void);
	void Add_Ref(void) { ++RefCount; }

private:
	int RefCount;
};

class MeshModelClass;

class MeshLoadContextClass
{
	friend class MeshModelClass;

	BfmeHandleCX Peek_Texture(int index);
	int Texture_Count(void) const { return TextureCount; }
	VertexMaterialClass *Peek_Vertex_Material(int index) const
	{
		return VertexMaterials[index];
	}
	int Vertex_Material_Count(void) const { return VertexMaterialCount; }

private:
	char BeforeVertexMaterials[0xc8];
	VertexMaterialClass **VertexMaterials;
	int VertexMaterialMax;
	unsigned char VertexMaterialValid;
	unsigned char VertexMaterialAllocated;
	unsigned char VertexMaterialPadding[2];
	int VertexMaterialCount;
	int VertexMaterialGrowth;
	char BeforeTextureCount[0x104 - 0xdc];
	int TextureCount;
};

class MeshMatDescClass
{
public:
	void Post_Load_Process(bool lighting_enabled, MeshModelClass *mesh);
};

class BfmeSubBJE
{
public:
	bool bfmeDoBJE(void *what);
};

class BfmeThingBJE
{
public:
	void *bfmeGoBJE(void *what);
};

class MaterialVector
{
private:
	struct Dispatch
	{
		virtual void DestructorSlot(void);
		virtual void EqualitySlot(void);
		virtual bool Resize(int newsize, VertexMaterialClass **array);
	};

public:
	bool Add(VertexMaterialClass *const &value)
	{
		if (ActiveCount >= VectorMax) {
			if ((!IsAllocated && VectorMax) || GrowthStep <= 0) {
				return false;
			}
			if (!((Dispatch *)this)->Resize(VectorMax + GrowthStep, 0)) {
				return false;
			}
		}
		int index = ActiveCount++;
		Vector[index] = value;
		return true;
	}

private:
	unsigned int Vtable;
	VertexMaterialClass **Vector;
	int VectorMax;
	unsigned char Valid;
	unsigned char IsAllocated;
	unsigned char Padding[2];
	int ActiveCount;
	int GrowthStep;
};

class MaterialInfoClass
{
public:
	virtual void Delete_This(void);

	void Add_Texture(const BfmeHandleCX &texture)
	{
		((BfmeThingBJE *)this)->bfmeGoBJE((void *)&texture);
	}

	void Add_Vertex_Material(VertexMaterialClass *material)
	{
		if (material) {
			material->Add_Ref();
		}
		VertexMaterials.Add(material);
	}

private:
	int RefCount;
	MaterialVector VertexMaterials;
};

class MeshModelClass
{
private:
	char BeforeFlags[0x18];
	int Flags;
	char BeforeDescriptors[0x94 - 0x1c];
	MeshMatDescClass *DefMatDesc;
	MeshMatDescClass *AlternateMatDesc;
	char BeforeMaterialInfo[0xa0 - 0x9c];
	MaterialInfoClass *MatInfo;

	protected:
	void install_alternate_material_desc(MeshLoadContextClass *context);
	int Get_Flag(int flag) const { return Flags & flag; }

	// ?install_materials@MeshModelClass@@IAEXPAVMeshLoadContextClass@@@Z
	void install_materials(MeshLoadContextClass *context);
};

void MeshModelClass::install_materials(MeshLoadContextClass *context)
{
	int i;

	install_alternate_material_desc(context);

	bool lighting_enabled = true;
	if (Get_Flag(0x2000)) {
		lighting_enabled = false;
	}
	DefMatDesc->Post_Load_Process(lighting_enabled, this);
	if (AlternateMatDesc != 0) {
		AlternateMatDesc->Post_Load_Process(lighting_enabled, this);
	}

	for (i = 0; i < context->Texture_Count(); i++) {
		MatInfo->Add_Texture(context->Peek_Texture(i));
	}

	for (i = 0; i < context->Vertex_Material_Count(); i++) {
		MatInfo->Add_Vertex_Material(context->Peek_Vertex_Material(i));
	}
}
