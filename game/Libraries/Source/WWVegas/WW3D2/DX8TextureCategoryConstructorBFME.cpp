// cl: /DNDEBUG /MD /EHsc
// BFME DX8TextureCategoryClass constructor at 0x00946460.  The list hierarchy
// follows WWLib/multilist.h; its chained node initialization and successive
// Generic/MultiList vtable stamps account for retail's exact store ordering.

class MultiListObjectClass;
class GenericMultiListClass;

class MultiListNodeClass
{
public:
	MultiListNodeClass()
	{
		Prev = Next = NextList = 0;
		Object = 0;
		List = 0;
	}
	MultiListNodeClass *Prev;
	MultiListNodeClass *Next;
	MultiListNodeClass *NextList;
	MultiListObjectClass *Object;
	GenericMultiListClass *List;
};

class MultiListObjectClass
{
public:
	MultiListObjectClass() : ListNode(0) {}
	virtual ~MultiListObjectClass();
private:
	MultiListNodeClass *ListNode;
};

class GenericMultiListClass
{
public:
	GenericMultiListClass()
	{
		Head.Next = Head.Prev = &Head;
		Head.Object = 0;
		Head.NextList = 0;
	}
	virtual ~GenericMultiListClass();
private:
	MultiListNodeClass Head;
};

template <class T> class MultiListClass : public GenericMultiListClass
{
public:
	MultiListClass() {}
	virtual ~MultiListClass();
};

class TextureClass
{
public:
	virtual void Delete_This() = 0;
	void Add_Ref() { ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4); }
	void Release_Ref();
};

template <class T> class RefCountPtr
{
public:
	RefCountPtr();
	~RefCountPtr()
	{
		if (Referent != 0) {
			Referent->Release_Ref();
			Referent = 0;
		}
	}
	T *Referent;
};

class VertexMaterialClass
{
public:
	virtual void Delete_This() = 0;
	void Add_Ref() { ++NumRefs; }
	int NumRefs;
};

class DX8PolygonRendererClass;
class DX8FVFCategoryContainer;
class ShaderClass { public: unsigned ShaderBits; };

class DX8TextureCategoryClass : public MultiListObjectClass
{
public:
	DX8TextureCategoryClass(int pass_, TextureClass **textures_, ShaderClass shader_,
		VertexMaterialClass *material_, DX8FVFCategoryContainer *container_);
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

// ??0DX8TextureCategoryClass@@QAE@HPAPAVTextureClass@@VShaderClass@@PAVVertexMaterialClass@@PAVDX8FVFCategoryContainer@@@Z
DX8TextureCategoryClass::DX8TextureCategoryClass(int pass_, TextureClass **textures_,
	ShaderClass shader_, VertexMaterialClass *material_, DX8FVFCategoryContainer *container_)
	: container(container_), shader(shader_), material(material_), pass(pass_), render_task_head(0)
{
	for (int index = 0; index < 2; ++index) {
		if (textures_[index] != 0)
			textures_[index]->Add_Ref();
		if (textures[index].Referent != 0)
			textures[index].Referent->Release_Ref();
		textures[index].Referent = textures_[index];
	}
	if (material != 0)
		material->Add_Ref();
}
