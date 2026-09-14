// ?Rva00739900Forward@@YA_NPAXM@Z
// partial score=0.97 date=2026-09-08
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// The retail body walks a RenderObj tree and sets each vertex material's
// opacity. The material-info and sub-object vtable slots, the callers at
// 0x0061CD80 and 0x006FCBD0, and the sibling diffuse walk identify this body.

class VertexMaterialClass
{
public:
	virtual void Delete_This(void);
	int NumRefs;

	void Add_Ref(void)
	{
		NumRefs++;
	}

	void Release_Ref(void)
	{
		NumRefs--;
		if (NumRefs == 0)
			Delete_This();
	}

	void Set_Opacity(float opacity);
};

class MaterialInfoClass
{
public:
	virtual void Delete_This(void);
	int NumRefs;
	int VectorVtable;
	VertexMaterialClass **Vector;
	int VectorMax;
	int VectorFlags;
	int ActiveCount;

	void Release_Ref(void)
	{
		NumRefs--;
		if (NumRefs == 0)
			Delete_This();
	}

	int Vertex_Material_Count(void) const
	{
		return ActiveCount;
	}

	VertexMaterialClass *Get_Vertex_Material(int index)
	{
		if (Vector[index])
			Vector[index]->Add_Ref();
		return Vector[index];
	}
};

class RenderObjClass
{
public:
	virtual void Delete_This(void);
	virtual void v01(void);
	virtual void v02(void);
	virtual void v03(void);
	virtual void v04(void);
	virtual void v05(void);
	virtual void v06(void);
	virtual void v07(void);
	virtual void v08(void);
	virtual void v09(void);
	virtual void v10(void);
	virtual void v11(void);
	virtual void v12(void);
	virtual void v13(void);
	virtual void v14(void);
	virtual void v15(void);
	virtual void v16(void);
	virtual void v17(void);
	virtual void v18(void);
	virtual void v19(void);
	virtual void v20(void);
	virtual void v21(void);
	virtual void v22(void);
	virtual void v23(void);
	virtual void v24(void);
	virtual void v25(void);
	virtual void v26(void);
	virtual int Get_Num_Sub_Objects(void) const;
	virtual void v28(void);
	virtual RenderObjClass *Get_Sub_Object(int index) const;
	virtual void v30(void);
	virtual void v31(void);
	virtual void v32(void);
	virtual void v33(void);
	virtual void v34(void);
	virtual void v35(void);
	virtual void v36(void);
	virtual void v37(void);
	virtual void v38(void);
	virtual void v39(void);
	virtual void v40(void);
	virtual void v41(void);
	virtual void v42(void);
	virtual void v43(void);
	virtual void v44(void);
	virtual void v45(void);
	virtual void v46(void);
	virtual void v47(void);
	virtual void v48(void);
	virtual void v49(void);
	virtual void v50(void);
	virtual void v51(void);
	virtual void v52(void);
	virtual void v53(void);
	virtual void v54(void);
	virtual void v55(void);
	virtual void v56(void);
	virtual void v57(void);
	virtual void v58(void);
	virtual void v59(void);
	virtual void v60(void);
	virtual void v61(void);
	virtual void v62(void);
	virtual void v63(void);
	virtual void v64(void);
	virtual void v65(void);
	virtual void v66(void);
	virtual void v67(void);
	virtual void v68(void);
	virtual void v69(void);
	virtual void v70(void);
	virtual void v71(void);
	virtual void v72(void);
	virtual void v73(void);
	virtual void v74(void);
	virtual void v75(void);
	virtual void v76(void);
	virtual void v77(void);
	virtual void v78(void);
	virtual void v79(void);
	virtual void v80(void);
	virtual void v81(void);
	virtual void v82(void);
	virtual void v83(void);
	virtual MaterialInfoClass *Get_Material_Info(void);

	void Release_Ref(void)
	{
		NumRefs--;
		if (NumRefs == 0)
			Delete_This();
	}

	int NumRefs;
};

typedef unsigned char (*ByteForward)(void *, volatile int);

unsigned char Rva00739900Forward(register void *object, volatile int value)
{
	RenderObjClass *robj = (RenderObjClass *)object;
	if (!robj)
		return false;

	register unsigned char result = 0;
	MaterialInfoClass *minfo = robj->Get_Material_Info();
	if (minfo)
	{
		for (int i = 0; i < minfo->Vertex_Material_Count(); i++)
		{
			VertexMaterialClass *mat = minfo->Get_Vertex_Material(i);
			if (mat)
			{
				mat->Set_Opacity(*(float *)&value);
				mat->Release_Ref();
				result = 1;
			}
		}
		minfo->Release_Ref();
		__assume(result == 0 || result == 1);
		return result;
	}

	int count = robj->Get_Num_Sub_Objects();
	for (int i = 0; i < count; i++)
	{
		RenderObjClass *sub = robj->Get_Sub_Object(i);
		register unsigned char child = ((ByteForward)Rva00739900Forward)(sub, value);
		if (result || child)
			result = 1;
		if (sub)
			sub->Release_Ref();
	}
	__assume(result == 0 || result == 1);
	return result;
}
