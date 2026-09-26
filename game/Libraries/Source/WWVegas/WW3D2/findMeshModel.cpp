// ?findMeshModel@@YAPAVBfmeRva00945870Object@@PAV1@PAVBfmeRva00945870Model@@@Z
// Clean reconstruction of retail RVA 0x00945870.  The retail body walks a
// RenderObjClass tree, returns the matching mesh object, and releases each
// retained child after the recursive search.  The view is local because the
// BFME vtable inserts two slots before the mesh-self dispatch and the complete
// shared class declaration is not safe to alter for this body.

class BfmeRva00945870Model
{
};

class BfmeRva00945870Mesh;

class BfmeRva00945870Object
{
public:
	virtual void Delete_This(void);
	virtual void slot1(void);
	virtual void slot2(void);
	virtual int Class_ID(void);
	virtual void slot4(void);
	virtual BfmeRva00945870Mesh *Mesh_Self(void);
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
	virtual BfmeRva00945870Object *Get_Sub_Object(int index);

	int m_refs;

	void Release_Ref(void)
	{
		if (--m_refs == 0)
			Delete_This();
	}
};

class BfmeRva00945870Mesh : public BfmeRva00945870Object
{
public:
	char m_pad[0xc0];
	BfmeRva00945870Model *m_model;
};

BfmeRva00945870Object *findMeshModel(
	BfmeRva00945870Object *object,
	BfmeRva00945870Model *model)
{
	if (object == 0 || model == 0)
		return 0;

	if (object->Class_ID() == 0) {
		BfmeRva00945870Mesh *mesh = object->Mesh_Self();
		if (mesh->m_model == model)
			return mesh;
	}

	for (int index = 0; index < object->Get_Num_Sub_Objects(); ++index) {
		BfmeRva00945870Object *child = object->Get_Sub_Object(index);
		BfmeRva00945870Object *result = findMeshModel(child, model);
		if (child != 0)
			child->Release_Ref();
		if (result != 0)
			return result;
	}

	return 0;
}
