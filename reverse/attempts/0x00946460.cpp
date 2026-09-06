// ??0DX8TextureCategoryClass@@QAE@HPAPAVTextureClass@@VShaderClass@@PAVVertexMaterialClass@@PAVDX8FVFCategoryContainer@@@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: DX8TextureCategoryClass::~DX8TextureCategoryClass at 0x00946540
// (171 B). Layout: MultiListObjectClass base (vptr, list links to +0xc),
// RefCountPtr<TextureClass> textures[2] at +0xc (destroyed by the CRT vector
// destructor iterator), VertexMaterialClass *material at +0x18 (inline
// Release_Ref), MultiListClass<DX8PolygonRendererClass> PolygonRendererList at
// +0x1c (head node link at +0x20/+0x24). The unregister loop reads the head
// renderer's mesh model (+0xc -> +8) and calls
// TheDX8MeshRenderer.Unregister_Mesh_Type on it.
class MeshModelClass;

class DX8PolygonRendererClass
{
public:
	MeshModelClass *Get_Mesh_Model_Class() const { return mmc; }
	char m_head[8];
	MeshModelClass *mmc;
};

class MultiListNodeClass
{
public:
	MultiListNodeClass() : NextList(0), Next(0), Prev(0), Object(0), List(0) {}
	MultiListNodeClass *Prev;
	MultiListNodeClass *Next;
	MultiListNodeClass *NextList;
	void *Object;
	void *List;
};

class MultiListObjectClass
{
public:
	MultiListObjectClass() : ListNode(0) {}
	virtual ~MultiListObjectClass();
	MultiListNodeClass *ListNode;
};

template <class T>
class MultiListClass
{
public:
	MultiListClass()
	{
		Head.Next = Head.Prev = &Head;
		Head.Object = 0;
		Head.NextList = 0;
	}
	virtual ~MultiListClass();
	T *Get_Head() const
	{
		if (Head.Next == &Head)
			return 0;
		return (T *)Head.Next->Object;
	}
	MultiListNodeClass Head;
};

class TextureClass
{
public:
	virtual void Delete_This() = 0;
	void Add_Ref()
	{
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
	}
	void Release_Ref();
	int NumRefs;
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr();
	void Set(T *referent)
	{
		if (referent != 0)
			referent->Add_Ref();
		if (Referent != 0)
			Referent->Release_Ref();
		Referent = referent;
	}
	~RefCountPtr()
	{
		if (Referent != 0)
		{
			Referent->Release_Ref();
			Referent = 0;
		}
	}
public:
	T *Referent;
};

class VertexMaterialClass
{
public:
	virtual void Delete_This() = 0;
	void Add_Ref() { ++NumRefs; }
	void Release_Ref()
	{
		if (--NumRefs == 0)
			Delete_This();
	}
	int NumRefs;
};

class DX8MeshRendererClass
{
public:
	void Unregister_Mesh_Type(MeshModelClass *mmc);
};
extern DX8MeshRendererClass *TheDX8MeshRenderer;

class DX8FVFCategoryContainer;
class ShaderClass
{
public:
	unsigned int ShaderBits;
};

class DX8TextureCategoryClass : public MultiListObjectClass
{
public:
	DX8TextureCategoryClass(int pass_, TextureClass **texs, ShaderClass shd, VertexMaterialClass *mat,
		DX8FVFCategoryContainer *container_);
	virtual ~DX8TextureCategoryClass();
private:
	DX8FVFCategoryContainer *container;
	RefCountPtr<TextureClass> textures[2];
	ShaderClass shader;
	VertexMaterialClass *material;
	MultiListClass<DX8PolygonRendererClass> PolygonRendererList;
	int pass;
	void *render_task_head;
};

DX8TextureCategoryClass::DX8TextureCategoryClass(int pass_, TextureClass **texs, ShaderClass shd,
	VertexMaterialClass *mat, DX8FVFCategoryContainer *container_)
	: container(container_), shader(shd), material(mat), pass(pass_), render_task_head(0)
{
	for (int a = 0; a < 2; ++a)
	{
		if (texs[a] != 0)
			texs[a]->Add_Ref();
		if (textures[a].Referent != 0)
			textures[a].Referent->Release_Ref();
		textures[a].Referent = texs[a];
	}
	if (material)
		material->Add_Ref();
}

DX8TextureCategoryClass::~DX8TextureCategoryClass()
{
	if (TheDX8MeshRenderer)
	{
		while (DX8PolygonRendererClass *p_renderer = PolygonRendererList.Get_Head())
		{
			TheDX8MeshRenderer->Unregister_Mesh_Type(p_renderer->Get_Mesh_Model_Class());
		}
	}
	if (material)
		material->Release_Ref();
}
