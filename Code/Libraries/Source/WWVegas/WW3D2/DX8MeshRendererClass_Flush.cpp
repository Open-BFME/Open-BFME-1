// cl: /DNDEBUG /MD /GR-
// readable body of ?Flush@DX8MeshRendererClass@@QAEXXZ: Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.cpp
// ?Flush@DX8MeshRendererClass@@QAEXXZ
// Retail 0x00949DD0 size 193. BFME Flush: rigid then skin FVF lists via
// inlined MultiList iteration (Render at vtable+4, delayed at +0x18), then
// Set_Vertex_Buffer/Set_Index_Buffer(NULL,0), Apply_Render_State_Changes,
// Invalidate_Cached_Render_States. TheDX8MeshRenderer is a pointer in BFME.

class VertexBufferClass;
class IndexBufferClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.h
class DX8FVFCategoryContainer
{
public:
	virtual ~DX8FVFCategoryContainer();
	virtual void Render(void);
	virtual void Add_Mesh(void);
	virtual void Log(void);
	virtual void Check_If_Mesh_Fits(void);
	virtual void Add_Delayed_Visible_Material_Pass(void);
	virtual void Render_Delayed_Procedural_Material_Passes(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h
class MultiListNodeClass
{
public:
	MultiListNodeClass *Prev;
	MultiListNodeClass *Next;
	MultiListNodeClass *NextList;
	DX8FVFCategoryContainer *Object;
};

class FVFCategoryList
{
public:
	virtual ~FVFCategoryList();
	MultiListNodeClass Head;
};

class SimpleDynVecFVFLists
{
public:
	virtual ~SimpleDynVecFVFLists();
	FVFCategoryList **Vector;
	int VectorMax;
	int ActiveCount;
	int Count(void) const { return ActiveCount; }
	FVFCategoryList *operator[](int index) { return Vector[index]; }
};

class CameraClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static void Set_Vertex_Buffer(const VertexBufferClass *vb, unsigned stream);
	static void Set_Index_Buffer(const IndexBufferClass *ib, unsigned short index);
	static void Apply_Render_State_Changes(void);
	static void Invalidate_Cached_Render_States(void);
	static void Apply_Default_State(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.h
class DX8MeshRendererClass
{
public:
	void Log_Statistics_String(bool only_visible);
	void Flush(void);

	bool enable_lighting;
	CameraClass *camera;
	SimpleDynVecFVFLists texture_category_container_lists_rigid;
	FVFCategoryList *texture_category_container_list_skin;
};

void DX8MeshRendererClass::Flush(void)
{
	int i;

	if (!camera)
		return;
	Log_Statistics_String(true);

	for (i = 0; i < texture_category_container_lists_rigid.Count(); ++i) {
		FVFCategoryList *p = texture_category_container_lists_rigid[i];
		MultiListNodeClass *node = p->Head.Next;
		MultiListNodeClass *head = &p->Head;
		if (node != head) {
			do {
				node->Object->Render();
				node = node->Next;
			} while (node != head);
		}
	}

	{
		FVFCategoryList *p = texture_category_container_list_skin;
		MultiListNodeClass *node = p->Head.Next;
		MultiListNodeClass *head = &p->Head;
		if (node != head) {
			do {
				node->Object->Render();
				node = node->Next;
			} while (node != head);
		}
	}

	for (i = 0; i < texture_category_container_lists_rigid.Count(); ++i) {
		FVFCategoryList *p = texture_category_container_lists_rigid[i];
		MultiListNodeClass *node = p->Head.Next;
		MultiListNodeClass *head = &p->Head;
		if (node != head) {
			do {
				node->Object->Render_Delayed_Procedural_Material_Passes();
				node = node->Next;
			} while (node != head);
		}
	}

	DX8Wrapper::Set_Vertex_Buffer(0, 0);
	DX8Wrapper::Set_Index_Buffer(0, 0);
	DX8Wrapper::Apply_Render_State_Changes();
	DX8Wrapper::Invalidate_Cached_Render_States();
	DX8Wrapper::Apply_Default_State();
}
