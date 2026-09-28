// cl: /DNDEBUG /DWIN32 /MD /EHsc
// RVA 0x007A0960; established WaterRenderObjClass helper called by init and
// replaceSkyboxTexture. Retail RenderObjClass material-info slot is +0x150.
// Get_Texture returns a four-byte handle (007A0340: output store and ret 8).
// The condition handle lives through the if body; each filter expression has
// a distinct temporary cleanup. getFilter can throw: retain its EH states.
// MaterialInfo: refcount +4 and texture count +0x30, read directly by retail.
// ShroudTexture_getFilter.cpp proves the same single-pointer handle view.

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

class ShroudTexture { public: ShroudFilter *getFilter(); };

class BfmeHandleCX
{
public:
	~BfmeHandleCX()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

	ShroudFilter *getFilter(void) { return ((ShroudTexture *)this)->getFilter(); }

	TextureClass *m_texture;

};

class MaterialInfoClass
{
public:
	virtual void v00();

	BfmeHandleCX Get_Texture(Int index) const;

	Int m_refCount;
	char m_pad08[0x28];
	Int m_textureCount;
};

class RenderObjClass
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

	virtual MaterialInfoClass *Get_Material_Info(void);
};

class WaterRenderObjClass { public: void clamp007A0960(RenderObjClass *mesh); };

void WaterRenderObjClass::clamp007A0960(RenderObjClass *mesh)
{
	if (!mesh)
		return;

	MaterialInfoClass *material = mesh->Get_Material_Info();

	for (Int i = 0; i < material->m_textureCount; i++) {
		BfmeHandleCX check = material->Get_Texture(i);
		if (check.m_texture) {
			{
				material->Get_Texture(i).getFilter()->m_uAddrMode = 1;
			}
			{
				material->Get_Texture(i).getFilter()->m_vAddrMode = 1;
			}
		}
	}

	if (--material->m_refCount == 0)
		material->v00();
}
