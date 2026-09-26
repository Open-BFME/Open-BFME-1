// cl: /DNDEBUG /MD /EHsc
// BFME MeshModelClass assignment at 0x0094DA40.  Unlike the Zero Hour donor,
// the retail BFME body has no GapFiller member-copy tail; its renderer global
// is a nullable pointer.

class MeshGeometryClass
{
public:
	MeshGeometryClass &operator=(const MeshGeometryClass &that);

private:
	char Data[0x94];
};

class MeshMatDescClass
{
public:
	MeshMatDescClass(const MeshMatDescClass &that);
	~MeshMatDescClass(void);
	MeshMatDescClass &operator=(const MeshMatDescClass &that);

private:
	char Data[0xF4];
};

class MeshModelClass;

class DX8MeshRendererClass
{
public:
	void Unregister_Mesh_Type(MeshModelClass *mesh);
};

extern DX8MeshRendererClass *TheDX8MeshRenderer;

class MeshModelClass : public MeshGeometryClass
{
public:
	MeshModelClass &operator=(const MeshModelClass &that);

protected:
	void clone_materials(const MeshModelClass &that);

	MeshMatDescClass *DefMatDesc;
	MeshMatDescClass *AlternateMatDesc;
	MeshMatDescClass *CurMatDesc;
	void *MatInfo;
	char PolygonRendererList[0x18];
	void *GapFiller;
	void *BfmeExtra;
	bool HasBeenInUse;
};

// ??4MeshModelClass@@QAEAAV0@ABV0@@Z
MeshModelClass &MeshModelClass::operator=(const MeshModelClass &that)
{
	if (this != &that) {
		if (TheDX8MeshRenderer != 0)
			TheDX8MeshRenderer->Unregister_Mesh_Type(this);

		MeshGeometryClass::operator=(that);
		*DefMatDesc = *that.DefMatDesc;
		CurMatDesc = DefMatDesc;

		if (AlternateMatDesc != 0) {
			delete AlternateMatDesc;
			AlternateMatDesc = 0;
		}

		if (that.AlternateMatDesc != 0)
			AlternateMatDesc = new MeshMatDescClass(*that.AlternateMatDesc);

		clone_materials(that);
	}
	return *this;
}
