// Open-BFME: Set_MeshModel_Flag, retail 0x0092D390.
// The BFME RenderObjClass vtable returns the mesh object from slot 5, and
// MeshClass stores its MeshModelClass pointer at +0xC8.

typedef int Int;

class RenderObjClass
{
public:
	virtual void deleteThis(void) = 0;
	virtual void slot1(void) = 0;
	virtual void slot2(void) = 0;
	virtual int classId(void) = 0;
	virtual void slot4(void) = 0;
	virtual RenderObjClass *asMesh(void) = 0;
	virtual void slot6(void) = 0;
	virtual void slot7(void) = 0;
	virtual void slot8(void) = 0;
	virtual void slot9(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual int getNumSubObjects(void) = 0;
	virtual void slot28(void) = 0;
	virtual RenderObjClass *getSubObject(int index) = 0;

	int m_refs;

	void releaseRef(void)
	{
		if (--m_refs == 0)
			deleteThis();
	}
};

class RefCountClass
{
public:
	virtual void deleteThis(void) = 0;
	int m_refCount;

	void addRef(void)
	{
		++m_refCount;
	}

	void releaseRef(void)
	{
		if (--m_refCount == 0)
			deleteThis();
	}
};

class MeshGeometryClass : public RefCountClass
{
public:
	unsigned char m_prefix[0x10];
	unsigned int m_flags;

	void setFlag(Int flag, Int onoff)
	{
		if (onoff)
			m_flags |= flag;
		else
			m_flags &= ~flag;
	}
};

class MeshModelClass : public MeshGeometryClass
{
};

class MeshClass : public RenderObjClass
{
	public:
	unsigned char m_prefix[0xC0];
	MeshModelClass *m_model;

	MeshModelClass *getModel(void)
	{
		if (m_model)
			m_model->addRef();
		return m_model;
	}
};

void Set_MeshModel_Flag(RenderObjClass *robj, Int flag, Int onoff)
{
	if (robj->classId() == 0)
	{
		MeshClass *mesh = (MeshClass *)robj->asMesh();
		MeshModelClass *model = mesh->getModel();
		model->setFlag(flag, onoff);
		model->releaseRef();
	}
	else
	{
		Int count = robj->getNumSubObjects();
		for (Int index = 0; index < count; ++index)
		{
			RenderObjClass *subObject = robj->getSubObject(index);
			if (subObject)
			{
				Set_MeshModel_Flag(subObject, flag, onoff);
				subObject->releaseRef();
			}
		}
	}
}
