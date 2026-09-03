// cl: /DNDEBUG /MD /EHsc
// BFME retail WaterRenderObjClass::replaceSkyboxTexture at 0x007A2670.

typedef int Int;
typedef char Char;

class BFMEWaterTrackTexture
{
public:
	void Release_Ref(void);
};

class BFMEWaterTrackTextureHandle
{
public:
	BFMEWaterTrackTexture *m_texture;

	~BFMEWaterTrackTextureHandle(void)
	{
		if (m_texture)
			m_texture->Release_Ref();
	}
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
	Char *name, Int mipCount, Int format);

class AsciiString
{
public:
	Char *m_data;

	Char *str(void) const
	{
		if (m_data)
			return m_data + 8;
		return (Char *)0x0107388b;
	}
};

class BfmeSkyBoxRenderObjClass
{
public:
	virtual void destroy(void);
	virtual void slot001(void);
	virtual void slot002(void);
	virtual Int classId(void);
	virtual void slot004(void);
	virtual void slot005(void);
	virtual void slot006(void);
	virtual void slot007(void);
	virtual void slot008(void);
	virtual void slot009(void);
	virtual void slot010(void);
	virtual void slot011(void);
	virtual void slot012(void);
	virtual void slot013(void);
	virtual void slot014(void);
	virtual void slot015(void);
	virtual void slot016(void);
	virtual void slot017(void);
	virtual void slot018(void);
	virtual void slot019(void);
	virtual void slot020(void);
	virtual void slot021(void);
	virtual void slot022(void);
	virtual void slot023(void);
	virtual void slot024(void);
	virtual void slot025(void);
	virtual void slot026(void);
	virtual Int subObjectCount(void);
	virtual void slot028(void);
	virtual BfmeSkyBoxRenderObjClass *subObject(Int index);
	virtual void slot030(void);
	virtual void slot031(void);
	virtual void slot032(void);
	virtual void slot033(void);
	virtual void slot034(void);
	virtual void slot035(void);
	virtual void slot036(void);
	virtual void slot037(void);
	virtual void slot038(void);
	virtual void slot039(void);
	virtual void slot040(void);
	virtual void slot041(void);
	virtual void slot042(void);
	virtual void slot043(void);
	virtual void slot044(void);
	virtual void slot045(void);
	virtual void slot046(void);
	virtual void slot047(void);
	virtual void slot048(void);
	virtual void slot049(void);
	virtual void slot050(void);
	virtual void slot051(void);
	virtual void slot052(void);
	virtual void slot053(void);
	virtual void slot054(void);
	virtual void slot055(void);
	virtual void slot056(void);
	virtual void slot057(void);
	virtual void slot058(void);
	virtual void slot059(void);
	virtual void slot060(void);
	virtual void slot061(void);
	virtual void slot062(void);
	virtual void slot063(void);
	virtual void slot064(void);
	virtual void slot065(void);
	virtual void slot066(void);
	virtual void slot067(void);
	virtual void slot068(void);
	virtual void slot069(void);
	virtual void slot070(void);
	virtual void slot071(void);
	virtual void slot072(void);
	virtual void slot073(void);
	virtual void slot074(void);
	virtual void slot075(void);
	virtual void slot076(void);
	virtual void slot077(void);
	virtual void slot078(void);
	virtual void slot079(void);
	virtual void slot080(void);
	virtual void slot081(void);
	virtual void slot082(void);
	virtual void slot083(void);
	virtual void slot084(void);
	virtual void slot085(void);
	virtual void slot086(void);
	virtual void slot087(void);
	virtual void slot088(void);
	virtual void slot089(void);
	virtual void slot090(void);
	virtual void slot091(void);
	virtual void slot092(void);
	virtual void slot093(void);
	virtual void slot094(void);
	virtual void slot095(void);
	virtual void slot096(void);
	virtual void slot097(void);
	virtual void slot098(void);
	virtual void slot099(void);
	virtual void slot100(void);
	virtual void slot101(void);
	virtual void slot102(void);
	virtual void slot103(void);
	virtual void slot104(void);
	virtual void slot105(void);
	virtual void slot106(void);
	virtual void slot107(void);
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

	void release(void)
	{
		if (--m_refCount == 0)
			destroy();
	}

private:
	Int m_refCount;
};

class WaterRenderObjClass
{
public:
	void replaceSkyboxTexture(const AsciiString &oldTexName,
		const AsciiString &newTextName);
	void clampSkyboxSubobject(BfmeSkyBoxRenderObjClass *object);

private:
	char m_padding[0x250];
	BfmeSkyBoxRenderObjClass *m_skyBox;
};

void WaterRenderObjClass::replaceSkyboxTexture(
	const AsciiString &oldTexName, const AsciiString &newTextName)
{
	if (m_skyBox)
	{
		m_skyBox->replaceTexture(
			BFMEGetWaterTrackTexture(oldTexName.str(), 0, 0),
			BFMEGetWaterTrackTexture(newTextName.str(), 0, 0));

		if (m_skyBox->classId() == 0x19)
		{
			for (Int index = 0; index < m_skyBox->subObjectCount(); ++index)
			{
				BfmeSkyBoxRenderObjClass *object =
					m_skyBox->subObject(index);
				if (object)
				{
					if (!object->classId())
						clampSkyboxSubobject(object);
					object->release();
				}
			}
		}
		else if (!m_skyBox->classId())
		{
			clampSkyboxSubobject(m_skyBox);
		}
	}
}
