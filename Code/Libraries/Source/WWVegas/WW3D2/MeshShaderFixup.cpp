// cl: /DNDEBUG /MD /EHsc
// Open-BFME: BFME mesh shader fixup, retail 0x00739690.

class ShaderClass
{
public:
	__forceinline ShaderClass(int bits) { m_bfmeBits = bits; }
	__forceinline ShaderClass(const ShaderClass &other) { m_bfmeBits = other.m_bfmeBits; }

	int m_bfmeBits;
};

class MeshMatDescClass
{
public:
	void Set_Single_Shader(ShaderClass shader, int pass);

	unsigned char m_unmodelled_00[0x94];
	int m_shaderBits;
};

class MeshModelClass
{
public:
	virtual void releaseModel();

	int m_refCount;
	unsigned char m_unmodelled_08[0x94];
	MeshMatDescClass *m_materialDescription;

	MeshMatDescClass *getMaterialDescription() const
	{
		return m_materialDescription;
	}
};

class MeshClass;

char bfmeFixupThunk(MeshClass *mesh);
extern void j_0002c43a();

#pragma comment(linker, "/alternatename:?bfmeFixupThunk@@YADPAVMeshClass@@@Z=?j_0002c43a@@YAXXZ")

class MeshClass
{
public:
	virtual void releaseMesh();
	virtual void v04();
	virtual void v08();
	virtual int isMultiMesh();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3c();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual void v4c();
	virtual void v50();
	virtual void v54();
	virtual void v58();
	virtual void v5c();
	virtual void v60();
	virtual void v64();
	virtual void v68();
	virtual int getSubMeshCount();
	virtual void v70();
	virtual MeshClass *getSubMesh(int index);

	void Make_Unique(bool forceClone);
	MeshModelClass *Get_Model();

	int m_refCount;
};

// ?bfmeFixup@@YADPAVMeshClass@@@Z
char bfmeFixup(MeshClass *mesh)
{
	if (mesh == 0)
		return 0;
	else
	{
		if (mesh->isMultiMesh() == 0)
		{
			mesh->Make_Unique(false);

			MeshModelClass *model = mesh->Get_Model();

			if (model == 0)
				return 0;

			int shaderBits = *(int *)((unsigned char *)model->getMaterialDescription() + 0x94);

			model->m_materialDescription->Set_Single_Shader(
				ShaderClass((shaderBits & 0xffff7f3f) | 0x4020), 0);

			if (--model->m_refCount == 0)
				model->releaseModel();

			return 1;
		}

		int count = mesh->getSubMeshCount();
		char fixed = 0;

		for (int index = 0; index < count; index++)
		{
			MeshClass *subMesh = mesh->getSubMesh(index);

			if (bfmeFixupThunk(subMesh))
				fixed = 1;

			if (subMesh != 0 && --subMesh->m_refCount == 0)
				subMesh->releaseMesh();
		}

		return fixed;
	}
}
