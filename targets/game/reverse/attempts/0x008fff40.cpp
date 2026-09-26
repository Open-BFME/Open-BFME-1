// ?Rva008FFF40@Rva00900FF0@@UAEXXZ
// partial score=0.16 date=2026-09-23
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// Rva00900FF0 vtable slot 3 at retail RVA 0x008FFF40.
// The owner and member offsets are witnessed by the matched constructor and destructor.

class TextureClass
{
public:
	void Release_Ref(void);
};

class BFMEWaterTrackTextureHandle
{
public:
	BFMEWaterTrackTextureHandle() : m_texture(0) {}
	TextureClass *m_texture;
	~BFMEWaterTrackTextureHandle()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
	char *name, int mipCount, int format);

class Rva00900FF0InnerVector
{
public:
	char *m_start;
	char *m_finish;
	char *m_endOfStorage;
};

class Rva00900FF0VecOfVec
{
public:
	Rva00900FF0VecOfVec(const Rva00900FF0VecOfVec &source);
	~Rva00900FF0VecOfVec();
	void process(Rva00900FF0VecOfVec *other, class RenderObjClass *object,
		int value);

	Rva00900FF0InnerVector *m_start;
	Rva00900FF0InnerVector *m_finish;
	Rva00900FF0InnerVector *m_endOfStorage;
};

#pragma comment(linker, "/alternatename:??0Rva00900FF0VecOfVec@@QAE@ABV0@@Z=?d_008ffb80@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva00900FF0VecOfVec@@QAE@XZ=?j_0000b109@@YAXXZ")
#pragma comment(linker, "/alternatename:?process@Rva00900FF0VecOfVec@@QAEXPAV0@PAVRenderObjClass@@H@Z=?d_008ff0f0@@YAXXZ")

class Rva00900FF0VectorHolder
{
public:
	void **m_start;
	void **m_finish;
	void **m_endOfStorage;
};

class RenderObjClass
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual int slot07(int value);
	virtual void slot08(void);
	virtual void slot09(void);
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
	virtual void slot84(void);
	virtual void slot85(void);
	virtual void slot86(void);
	virtual void slot87(void);
	virtual void slot88(void);
	virtual void slot89(void);
	virtual void slot90(void);
	virtual void slot91(float value);
	virtual void slot92(void);
	virtual void slot93(void);
	virtual void slot94(void);
	virtual void slot95(void);
	virtual void slot96(void);
	virtual void slot97(void);
	virtual void slot98(void);
	virtual void slot99(void);
	virtual void slot100(void);
	virtual void slot101(void);
	virtual void slot102(void);
	virtual void slot103(void);
	virtual void slot104(void);
	virtual void slot105(void);
	virtual void slot106(void);
	virtual void slot107(int value);
	virtual void slot108(void);
	virtual void slot109(void);
	virtual void slot110(void);
	virtual void slot111(void);
	virtual void slot112(void);
	virtual void slot113(void);
	virtual void slot114(void);
	virtual void slot115(void);
	virtual void slot116(void);
	virtual void slot117(void);
	virtual void slot118(void);
	virtual void slot119(void);
	virtual void slot120(void);
	virtual void slot121(void);
	virtual void slot122(void);
	virtual void slot123(void);
	virtual void slot124(void);
	virtual void replaceTexture(const BFMEWaterTrackTextureHandle &oldTexture,
		const BFMEWaterTrackTextureHandle &newTexture);
	virtual void slot126(int value);
};

extern RenderObjClass *Create_Render_Obj(const char *name);
extern void Rva008FEB90(RenderObjClass *object);

void Rva008FF060(char *name, int value);
void Rva008FF6A0(RenderObjClass *object, Rva00900FF0InnerVector *first,
	Rva00900FF0InnerVector *second, void *source);

#pragma comment(linker, "/alternatename:?Rva008FF060@@YAXPADH@Z=?d_008ff060@@YAXXZ")
#pragma comment(linker, "/alternatename:?Rva008FF6A0@@YAXPAVRenderObjClass@@PAVRva00900FF0InnerVector@@1PAX@Z=?d_008ff6a0@@YAXXZ")

class Rva00900FF0Base
{
public:
	virtual int slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	char m_base[0x10];
};

class Rva00900FF0 : public Rva00900FF0Base
{
public:
	virtual void Rva008FFF40(void);

private:
	char *m_str14;
	char *m_str18;
	Rva00900FF0VecOfVec m_vec1c;
	Rva00900FF0VecOfVec m_vec28;
	Rva00900FF0VecOfVec m_vec34;
	Rva00900FF0VecOfVec m_vec40;
	Rva00900FF0VecOfVec m_vec4c;
	Rva00900FF0VectorHolder m_vector58;
	float m_field64;
	int m_field68;
	int m_field6c;
	RenderObjClass *m_render70;
};

void Rva00900FF0::Rva008FFF40(void)
{
	m_render70 = Create_Render_Obj(m_str18);
	if (m_render70 == 0)
		return;
	RenderObjClass *object = m_render70;

	int value = slot00();
	object->slot07(value);
	union
	{
		float real;
		unsigned int bits;
	} magnitude;
	magnitude.real = m_field64 - *(const float *)0x01075334;
	magnitude.bits &= 0x7fffffff;
	bool close = true;
	if (magnitude.real > *(const float *)0x01076c24)
		close = false;
	bool hasFlags = (m_field68 & 0x00ffffff) != 0;
	bool hasBoth = m_vec1c.m_start != m_vec1c.m_finish &&
		m_vec28.m_start != m_vec28.m_finish;
	if (close)
		object->slot91(m_field64);
	if (!close && !hasFlags && !hasBoth &&
		m_vec40.m_start == m_vec40.m_finish)
		return;

	if (m_vec28.m_start != m_vec28.m_finish &&
		m_vec1c.m_start == m_vec1c.m_finish)
	{
		Rva008FEB90(object);
		if (m_vec34.m_start != m_vec34.m_finish)
		{
			Rva00900FF0VecOfVec first(m_vec34);
			Rva00900FF0VecOfVec second(m_vec28);
			first.process(&second, object, m_field6c);
		}
		else
		{
			Rva00900FF0InnerVector *last = m_vec28.m_finish - 1;
			Rva008FF060(last->m_start, m_field6c);
			if (object->Get_Num_Sub_Objects() > 0)
			{
				for (int index = 0;
					index < object->Get_Num_Sub_Objects(); ++index)
				{
					RenderObjClass *sub = object->Get_Sub_Object(index);
					if (sub != 0)
					{
						Rva008FF060(last->m_start, m_field6c);
						if (--*(int *)((char *)sub + 4) == 0)
							sub->slot00();
					}
				}
			}
		}
	}

	else
	{
		if (m_vec40.m_start != m_vec40.m_finish)
		{
			Rva008FEB90(object);
			int count = (int)(m_vec40.m_finish - m_vec40.m_start);
			for (int index = 0; index < count; ++index)
			{
				Rva008FF6A0(object, m_vec40.m_start + index,
					m_vec4c.m_start + index, m_vector58.m_start[index]);
			}
		}

		if (hasBoth)
		{
			Rva008FEB90(object);
			Rva00900FF0InnerVector *last1 = m_vec28.m_finish - 1;
			Rva00900FF0InnerVector *last2 = m_vec1c.m_finish - 1;
			BFMEWaterTrackTextureHandle first = BFMEGetWaterTrackTexture(
				last1->m_start, 0, 0);
			BFMEWaterTrackTextureHandle second = BFMEGetWaterTrackTexture(
				last2->m_start, 0, 2);
			object->replaceTexture(first, second);
		}
	}

	if (hasFlags)
	{
		Rva008FEB90(object);
		object->slot126(m_field68);
	}
}
