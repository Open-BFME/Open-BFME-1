// cl: /DNDEBUG /MD /EHsc

class Matrix3D
{
public:
	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;
};

class Drawable
{
public:
	const Matrix3D *getTransformMatrix() const;
};

class Shadow
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void release();
};

class RenderObjClass
{
public:
	virtual void Delete_This();
	int m_refCount;
	char m_pad08[0x10];
	Matrix3D m_transform;

	virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10();
	virtual void s11(); virtual void s12(); virtual void s13();
	virtual void s14(); virtual void s15(); virtual void s16();
	virtual void s17(); virtual void s18(); virtual void s19();
	virtual void Validate_Transform() const;
	virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26();
	virtual void s27(); virtual void s28(); virtual void s29();
	virtual void s30(); virtual void s31(); virtual void s32();
	virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38();
	virtual void s39(); virtual void s40(); virtual void s41();
	virtual void s42(); virtual void s43(); virtual void s44();
	virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50();
	virtual void s51(); virtual void s52(); virtual void s53();
	virtual void s54(); virtual void s55(); virtual void s56();
	virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62();
	virtual void s63(); virtual void s64(); virtual void s65();
	virtual void s66(); virtual void s67(); virtual void s68();
	virtual void s69(); virtual void s70(); virtual void s71();
	virtual void s72(); virtual void s73(); virtual void s74();
	virtual void s75(); virtual void s76(); virtual void s77();
	virtual void s78(); virtual void s79(); virtual void s80();
	virtual void s81(); virtual void s82(); virtual void s83();
	virtual void s84(); virtual void s85(); virtual void s86();
	virtual void s87(); virtual void s88(); virtual void s89();
	virtual void s90(); virtual void s91(); virtual void s92();
	virtual void s93(); virtual void s94(); virtual void s95();
	virtual void s96(); virtual void s97(); virtual void s98();
	virtual void s99(); virtual void s100(); virtual void s101();
	virtual void s102(); virtual void s103(); virtual void s104();
	virtual void s105(); virtual void s106(); virtual void s107();
	virtual void s108(); virtual void s109(); virtual void s110();
	virtual void s111(); virtual void s112(); virtual void s113();
	virtual void s114(); virtual void s115(); virtual void s116();
	virtual void s117(); virtual void s118(); virtual void s119();
	virtual void s120(); virtual void s121();
	virtual bool predicate01E8();
};

class SceneClass
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void Remove_Render_Object(RenderObjClass *obj);
};

extern SceneClass *g_Va012F8058;

class W3DModelDraw
{
private:
	void nukeCurrentRender(Matrix3D *out);

private:
	char m_pad00[8];
	Drawable *m_drawable;
	char m_pad0C[0x28];
	RenderObjClass *m_obj;
	char m_pad38[4];
	Shadow *m_shadow;
	Shadow *m_terrainDecal;
	char m_pad44[0x21];
	bool m_pauseAnimation;
};

// ?nukeCurrentRender@W3DModelDraw@@AAEXPAVMatrix3D@@@Z
void W3DModelDraw::nukeCurrentRender(Matrix3D *out)
{
	m_pauseAnimation = false;

	if (m_shadow)
		m_shadow->release();
	m_shadow = 0;

	if (m_terrainDecal)
		m_terrainDecal->release();
	m_terrainDecal = 0;

	RenderObjClass *obj = m_obj;
	if (obj)
	{
		if (out)
		{
			obj->Validate_Transform();
			out->m00 = obj->m_transform.m00; out->m01 = obj->m_transform.m01;
			out->m02 = obj->m_transform.m02; out->m03 = obj->m_transform.m03;
			out->m10 = obj->m_transform.m10; out->m11 = obj->m_transform.m11;
			out->m12 = obj->m_transform.m12; out->m13 = obj->m_transform.m13;
			out->m20 = obj->m_transform.m20; out->m21 = obj->m_transform.m21;
			out->m22 = obj->m_transform.m22; out->m23 = obj->m_transform.m23;
		}
		if (m_obj->predicate01E8())
			g_Va012F8058->Remove_Render_Object(m_obj);
		obj = m_obj;
		if (obj)
		{
			if (--obj->m_refCount == 0)
				obj->Delete_This();
			m_obj = 0;
		}
		m_obj = 0;
	}
	else if (out)
	{
		const Matrix3D *src = m_drawable->getTransformMatrix();
		out->m00 = src->m00; out->m01 = src->m01; out->m02 = src->m02; out->m03 = src->m03;
		out->m10 = src->m10; out->m11 = src->m11; out->m12 = src->m12; out->m13 = src->m13;
		out->m20 = src->m20; out->m21 = src->m21; out->m22 = src->m22; out->m23 = src->m23;
	}
}
