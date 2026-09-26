// ?Reset_All_Texture_Mappers@@YAXPAVRenderObjClass@@_N@Z
// BFME's RenderObjClass vtable has a mesh-self slot and compact child slots;
// keep this view local so the shared WW3D2 headers remain untouched.

class MaterialInfoClass;
class MeshClass;

class RenderObjClass
{
public:
	virtual void Delete_This(void);
	virtual void slot1(void);
	virtual void slot2(void);
	virtual int Class_ID(void);
	virtual void slot4(void);
	virtual MeshClass *Mesh_Self(void);
	virtual void slot6(void);
	virtual void slot7(void);
	virtual void slot8(void);
	virtual void slot9(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	virtual void slot23(void);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual void slot26(void);
	virtual int Get_Num_Sub_Objects(void);
	virtual void slot28(void);
	virtual RenderObjClass *Get_Sub_Object(int index);
	virtual void slot30(void);
	virtual void slot31(void);
	virtual void slot32(void);
	virtual void slot33(void);
	virtual void slot34(void);
	virtual void slot35(void);
	virtual void slot36(void);
	virtual void slot37(void);
	virtual void slot38(void);
	virtual void slot39(void);
	virtual void slot40(void);
	virtual void slot41(void);
	virtual void slot42(void);
	virtual void slot43(void);
	virtual void slot44(void);
	virtual void slot45(void);
	virtual void slot46(void);
	virtual void slot47(void);
	virtual void slot48(void);
	virtual void slot49(void);
	virtual void slot50(void);
	virtual void slot51(void);
	virtual void slot52(void);
	virtual void slot53(void);
	virtual void slot54(void);
	virtual void slot55(void);
	virtual void slot56(void);
	virtual void slot57(void);
	virtual void slot58(void);
	virtual void slot59(void);
	virtual void slot60(void);
	virtual void slot61(void);
	virtual void slot62(void);
	virtual void slot63(void);
	virtual void slot64(void);
	virtual void slot65(void);
	virtual void slot66(void);
	virtual void slot67(void);
	virtual void slot68(void);
	virtual void slot69(void);
	virtual void slot70(void);
	virtual void slot71(void);
	virtual void slot72(void);
	virtual void slot73(void);
	virtual void slot74(void);
	virtual void slot75(void);
	virtual void slot76(void);
	virtual void slot77(void);
	virtual void slot78(void);
	virtual void slot79(void);
	virtual void slot80(void);
	virtual void slot81(void);
	virtual void slot82(void);
	virtual void slot83(void);
	virtual MaterialInfoClass *Get_Material_Info(void);

	int m_refs;

	void Release_Ref(void)
	{
		if (--m_refs == 0)
			Delete_This();
	}
};

class MeshClass
{
public:
	void Make_Unique(bool force_meshmdl_clone);
};

class MaterialInfoClass
{
public:
	virtual void Delete_This(void);
	int m_refs;

	bool Has_Time_Variant_Texture_Mappers(void);
	void Make_Vertex_Materials_Unique(void);
	void Reset_Texture_Mappers(void);

	void Release_Ref(void)
	{
		if (--m_refs == 0)
			Delete_This();
	}
};

void Reset_All_Texture_Mappers(RenderObjClass *robj, bool make_unique)
{
	if (robj->Class_ID() == 0) {
		MeshClass *mesh = robj->Mesh_Self();
		MaterialInfoClass *minfo = robj->Get_Material_Info();
		if (minfo && minfo->Has_Time_Variant_Texture_Mappers()) {
			if (make_unique) {
				mesh->Make_Unique(false);
				minfo->Make_Vertex_Materials_Unique();
			}
			minfo->Reset_Texture_Mappers();
			minfo->Release_Ref();
		}
	} else {
		int num_obj = robj->Get_Num_Sub_Objects();
		for (int i = 0; i < num_obj; ++i) {
			RenderObjClass *sub_obj = robj->Get_Sub_Object(i);
			if (sub_obj) {
				Reset_All_Texture_Mappers(sub_obj, make_unique);
				sub_obj->Release_Ref();
			}
		}
	}
}
