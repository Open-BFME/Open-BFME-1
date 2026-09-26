// cl: /DNDEBUG /MD /EHsc
// BFME DX8MeshRendererClass::Unregister_Mesh_Type at 0x00945F20.  Polygon
// renderers are drained first, then the mesh is removed from the renderer's
// intrusive registered-mesh chain.  BFME has no Zero Hour GapFiller teardown.

class MultiListObjectClass
{
};

class GenericMultiListClass
{
protected:
	MultiListObjectClass *Internal_Remove_List_Head(void);
	char Data[0x18];
};

template <class T> class MultiListClass : public GenericMultiListClass
{
public:
	T *Remove_Head(void)
	{
		return reinterpret_cast<T *>(Internal_Remove_List_Head());
	}
};

class DX8PolygonRendererClass : public MultiListObjectClass
{
public:
	virtual ~DX8PolygonRendererClass(void);
};

class MeshModelClass
{
public:
	char Prefix[0xA4];
	MultiListClass<DX8PolygonRendererClass> PolygonRendererList;
	MeshModelClass **RegisteredPrevLink;
	MeshModelClass *RegisteredNext;
};

class DX8MeshRendererClass
{
public:
	void Unregister_Mesh_Type(MeshModelClass *mesh);
};

// ?Unregister_Mesh_Type@DX8MeshRendererClass@@QAEXPAVMeshModelClass@@@Z
void DX8MeshRendererClass::Unregister_Mesh_Type(MeshModelClass *mesh)
{
	while (DX8PolygonRendererClass *renderer = mesh->PolygonRendererList.Remove_Head())
		delete renderer;

	if (mesh->RegisteredPrevLink != 0) {
		*mesh->RegisteredPrevLink = mesh->RegisteredNext;
		if (mesh->RegisteredNext != 0)
			mesh->RegisteredNext->RegisteredPrevLink = mesh->RegisteredPrevLink;
		mesh->RegisteredPrevLink = 0;
	}
}
