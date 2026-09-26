// cl: /DNDEBUG /MD /EHsc
// BFME MeshModelClass destructor at 0x0094ED60.  The retail class keeps the
// renderer singleton as a pointer and passes the geometry's SKIN flag through
// the BFME four-argument Reset overload.

class RefCountClass
{
public:
	virtual void Delete_This(void) { delete this; }
	void Release_Ref(void)
	{
		if (--NumRefs == 0)
			Delete_This();
	}

protected:
	virtual ~RefCountClass(void) {}

private:
	int NumRefs;
};

class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass(void);

private:
	void *ListNode;
};

class W3DMPO {};

class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass
{
public:
	virtual ~MeshGeometryClass(void);

	enum FlagsType { SKIN = 0x00000400 };
	int Get_Flag(FlagsType flag) { return Flags & flag; }

private:
	char Prefix[8];
	int Flags;
	char Tail[0x78];
};

class BfmeHolderBY
{
public:
	~BfmeHolderBY(void);
};

class DX8PolygonRendererClass;

template <class T> class MultiListClass
{
public:
	virtual ~MultiListClass(void);

private:
	char Data[0x14];
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
	virtual ~MeshModelClass(void);
	void Reset(int polycount, int vertcount, int passcount, bool skin);

private:
	BfmeHolderBY *DefMatDesc;
	BfmeHolderBY *AlternateMatDesc;
	BfmeHolderBY *CurMatDesc;
	RefCountClass *MatInfo;
	MultiListClass<DX8PolygonRendererClass> PolygonRendererList;
	BfmeHolderBY *GapFiller;
	void *BfmeExtra;
	bool HasBeenInUse;
};

// ??1MeshModelClass@@UAE@XZ
MeshModelClass::~MeshModelClass(void)
{
	if (TheDX8MeshRenderer != 0)
		TheDX8MeshRenderer->Unregister_Mesh_Type(this);

	Reset(0, 0, 0, Get_Flag(SKIN));

	if (MatInfo != 0) {
		MatInfo->Release_Ref();
		MatInfo = 0;
	}

	if (DefMatDesc != 0)
		delete DefMatDesc;
	if (AlternateMatDesc != 0)
		delete AlternateMatDesc;
}
