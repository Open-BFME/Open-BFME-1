// cl: /DNDEBUG /MD /EHsc
// BFME's four-argument MeshModelClass::Reset ABI slice.

class MeshGeometryClass
{
	char m_base[0x94];

public:
	void Reset_Geometry(int polycount, int vertcount, bool skin);
};

class MeshMatDescClass
{
public:
	void Reset(int polycount, int vertcount, int passcount);
};

class MeshModelClass;

class MaterialInfoClass
{
	private:
	void Free(void);
	friend class MeshModelClass;
};

class BfmeHolderBY
{
public:
	~BfmeHolderBY(void);
};

class DX8MeshRendererClass
{
public:
	void Unregister_Mesh_Type(MeshModelClass *mesh);
};

extern DX8MeshRendererClass *TheDX8MeshRenderer;

class MeshModelClass : public MeshGeometryClass
{
	MeshMatDescClass *DefMatDesc;
	BfmeHolderBY *AlternateMatDesc;
	MeshMatDescClass *CurMatDesc;
	MaterialInfoClass *MatInfo;
	char PolygonRendererList[0x18];
	BfmeHolderBY *GapFiller;
	bool HasBeenInUse;

public:
	void Reset(int polycount, int vertcount, int passcount, bool skin);
};

// ?Reset@MeshModelClass@@QAEXHHH_N@Z
void MeshModelClass::Reset(int polycount, int vertcount, int passcount, bool skin)
{
	Reset_Geometry(polycount, vertcount, skin);

	if (TheDX8MeshRenderer != 0)
		TheDX8MeshRenderer->Unregister_Mesh_Type(this);

	MatInfo->Free();
	DefMatDesc->Reset(polycount, vertcount, passcount);
	if (AlternateMatDesc != 0) {
		delete AlternateMatDesc;
		AlternateMatDesc = 0;
	}
	CurMatDesc = DefMatDesc;
}
