// cl: /DNDEBUG /MD /EHsc
// readable body of ?Invalidate@DX8MeshRendererClass@@QAEX_N@Z: Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.cpp
// Open-BFME5: BFME renderer invalidation with its intrusive registered-mesh list.

class MeshModelClass
{
	char prefix[0xbc];

public:
	MeshModelClass **registered_mesh_prev;
	MeshModelClass *registered_mesh_next;
};

class RegisteredMeshList
{
public:
	MeshModelClass *head;

	__forceinline void Reset_List()
	{
		while (head != 0) {
			MeshModelClass *mesh = head;
			MeshModelClass **previous = mesh->registered_mesh_prev;
			if (previous != 0) {
				*previous = mesh->registered_mesh_next;
				if (mesh->registered_mesh_next != 0) {
					mesh->registered_mesh_next->registered_mesh_prev = mesh->registered_mesh_prev;
				}
				mesh->registered_mesh_prev = 0;
			}
		}
	}
};

static RegisteredMeshList _RegisteredMeshList;

class MultiListNodeClass
{
public:
	MultiListNodeClass *prev;
	MultiListNodeClass *next;
	MultiListNodeClass *next_list;
	void *object;
	void *list;

	MultiListNodeClass()
	{
		prev = next = next_list = 0;
		object = 0;
		list = 0;
	}
};

class MultiListObjectClass;

class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();
};

class GenericMultiListClass
{
public:
	virtual ~GenericMultiListClass();
	GenericMultiListClass()
	{
		head.next = head.prev = &head;
		head.object = 0;
		head.next_list = 0;
	}

protected:
	MultiListNodeClass head;
	MultiListObjectClass *Internal_Remove_List_Head();
};

class DX8FVFCategoryContainer : public MultiListObjectClass
{
public:
	virtual ~DX8FVFCategoryContainer();
};

class FVFCategoryList : public GenericMultiListClass
{
public:
	DX8FVFCategoryContainer *Remove_Head()
	{
		return static_cast<DX8FVFCategoryContainer *>(Internal_Remove_List_Head());
	}
};

class SimpleDynVecFVFLists
{
public:
	virtual ~SimpleDynVecFVFLists();
	virtual bool Resize(int size);

	FVFCategoryList **vector;
	int vector_max;
	int active_count;

	int Count() const
	{
		return active_count;
	}

	FVFCategoryList *operator[](int index)
	{
		return vector[index];
	}

	void Delete_All(bool allow_shrink = true)
	{
		active_count = 0;
		if (allow_shrink && active_count < vector_max / 4) {
			Resize(active_count);
		}
	}
};

class CameraClass;

class DX8MeshRendererClass
{
public:
	void Invalidate(bool shutdown = false);

protected:
	bool enable_lighting;
	CameraClass *camera;
	SimpleDynVecFVFLists texture_category_container_lists_rigid;
	FVFCategoryList *texture_category_container_list_skin;
};

static __forceinline void Invalidate_FVF_Category_Container_List(FVFCategoryList &list)
{
	DX8FVFCategoryContainer *container;
	while ((container = list.Remove_Head()) != 0) {
		delete container;
	}
}

void DX8MeshRendererClass::Invalidate(bool shutdown)
{
	_RegisteredMeshList.Reset_List();

	for (int i = 0; i < texture_category_container_lists_rigid.Count(); ++i) {
		Invalidate_FVF_Category_Container_List(*texture_category_container_lists_rigid[i]);
		delete texture_category_container_lists_rigid[i];
	}

	if (texture_category_container_list_skin != 0) {
		Invalidate_FVF_Category_Container_List(*texture_category_container_list_skin);
		delete texture_category_container_list_skin;
		texture_category_container_list_skin = 0;
	}

	if (!shutdown) {
		texture_category_container_list_skin = new FVFCategoryList;
	}

	texture_category_container_lists_rigid.Delete_All();
}
