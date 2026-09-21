// ?d_007a0960@@YAXXZ
// partial score=0.33 date=2026-09-21
// ?d_007a0960@@YAXPAVMeshClass@@@Z [retail body 0x007A0960, 249 bytes]
// Address-derived: called from WaterRenderObjClass::replaceSkyboxTexture and
// WaterRenderObjClass::init (per brief).  BFME variant of the ZH
// replaceSkyboxTexture texture-clamp loop:
//   for (i=0;i<material->Texture_Count();i++)
//     if (material->Peek_Texture(i))
//       material->Peek_Texture(i)->Get_Filter().Set_U_Addr_Mode(CLAMP);
//       material->Peek_Texture(i)->Get_Filter().Set_V_Addr_Mode(CLAMP);
// but using a ref-counted BfmeHandleCX-returning Get_Texture(i) (pinned
// MaterialInfoClass::Get_Texture) instead of Peek_Texture, needing explicit
// Release_Ref calls, and treating the handle itself as a ShroudTexture with
// a getFilter() method.
// cl: /DNDEBUG /DWIN32 /MD /EHsc

typedef bool Bool;
typedef int Int;

class TextureClass
{
public:
	void Release_Ref(void);
};

class ShroudFilter
{
public:
	char m_pad[0xc];
	int m_uAddrMode;
	int m_vAddrMode;
};

class BfmeHandleCX
{
public:
	~BfmeHandleCX()
	{
		if (m_releaseCount)
			m_texture->Release_Ref();
	}

	ShroudFilter *getFilter(void) throw();

	TextureClass *m_texture;
	Int m_releaseCount;
};

class MaterialInfoClass
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52();

	BfmeHandleCX Get_Texture(Int index);

	Int m_refCount;
	char m_pad08[0x28];
	Int m_textureCount;
};

class MeshClass
{
public:
	virtual void mv00();
	virtual void mv01();
	virtual void mv02();
	virtual void mv03();
	virtual void mv04();
	virtual void mv05();
	virtual void mv06();
	virtual void mv07();
	virtual void mv08();
	virtual void mv09();
	virtual void mv10();
	virtual void mv11();
	virtual void mv12();
	virtual void mv13();
	virtual void mv14();
	virtual void mv15();
	virtual void mv16();
	virtual void mv17();
	virtual void mv18();
	virtual void mv19();
	virtual void mv20();
	virtual void mv21();
	virtual void mv22();
	virtual void mv23();
	virtual void mv24();
	virtual void mv25();
	virtual void mv26();
	virtual void mv27();
	virtual void mv28();
	virtual void mv29();
	virtual void mv30();
	virtual void mv31();
	virtual void mv32();
	virtual void mv33();
	virtual void mv34();
	virtual void mv35();
	virtual void mv36();
	virtual void mv37();
	virtual void mv38();
	virtual void mv39();
	virtual void mv40();
	virtual void mv41();
	virtual void mv42();
	virtual void mv43();
	virtual void mv44();
	virtual void mv45();
	virtual void mv46();
	virtual void mv47();
	virtual void mv48();
	virtual void mv49();
	virtual void mv50();
	virtual void mv51();
	virtual void mv52();
	virtual void mv53();
	virtual void mv54();
	virtual void mv55();
	virtual void mv56();
	virtual void mv57();
	virtual void mv58();
	virtual void mv59();
	virtual void mv60();
	virtual void mv61();
	virtual void mv62();
	virtual void mv63();
	virtual void mv64();
	virtual void mv65();
	virtual void mv66();
	virtual void mv67();
	virtual void mv68();
	virtual void mv69();
	virtual void mv70();
	virtual void mv71();
	virtual void mv72();
	virtual void mv73();
	virtual void mv74();
	virtual void mv75();
	virtual void mv76();
	virtual void mv77();
	virtual void mv78();
	virtual void mv79();
	virtual void mv80();
	virtual void mv81();
	virtual void mv82();
	virtual void mv83();

	MaterialInfoClass *Get_Material_Info(void);
};

void d_007a0960(MeshClass *mesh)
{
	if (!mesh)
		return;

	MaterialInfoClass *material = mesh->Get_Material_Info();

	for (Int i = 0; i < material->m_textureCount; i++) {
		BfmeHandleCX check = material->Get_Texture(i);
		if (check.m_texture) {
			{
				BfmeHandleCX texU = material->Get_Texture(i);
				texU.getFilter()->m_uAddrMode = 1;
			}
			{
				BfmeHandleCX texV = material->Get_Texture(i);
				texV.getFilter()->m_vAddrMode = 1;
			}
		}
	}

	if (--material->m_refCount == 0)
		material->v00();
}
