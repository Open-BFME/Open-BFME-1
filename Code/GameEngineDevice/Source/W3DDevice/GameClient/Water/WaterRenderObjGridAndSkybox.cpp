// cl: /DNDEBUG /MD /EHsc
// readable body of ?reset@WaterRenderObjClass@@QAEXXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWater.cpp
// readable body of ?xfer@WaterRenderObjClass@@MAEXPAVXfer@@@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWater.cpp
// readable body of ?replaceSkyboxTexture@WaterRenderObjClass@@QAEXABVAsciiString@@0@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWater.cpp
//
// The three bodies that reach into WaterRenderObjClass's own storage: reset
// (0x007A1390) clears the height grid, xfer (0x0079FC10) saves and loads it,
// and replaceSkyboxTexture (0x007A2670) swaps the skybox handle. They had three
// copies of the class between them, none of which could see the other two's
// fields, and two of the three did not even agree on whether the object has a
// vtable pointer.
//
// It does -- xfer is a virtual, and its copy is the only one that said so. Once
// the vtable pointer is in, the other two copies line up exactly with it:
// reset's `m_beforeWaterTracks[0x254]` and replaceSkyboxTexture's
// `m_padding[0x250]` are the same run measured from +0x00 instead of +0x04, and
// all three land m_meshData at +0x258 and m_skyBox at +0x250. That is the union
// stated once below.
//
// The virtuals keep their declaration order (slot0, crc, xfer): xfer's own slot
// index is what dispatches it, and reordering them would move it.

typedef int Int;
typedef char Char;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DWaterTracks.h
class WaterTracksRenderSystem
{
public:
	void reset(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DWater.h
struct WaterMeshData
{
	float height;
	float velocity;
	UnsignedByte status;
	UnsignedByte preferredHeight;
};

enum XferMode
{
	XFER_INVALID = 0,
	XFER_SAVE,
	XFER_LOAD,
	XFER_CRC
};

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Xfer.h
class Xfer
{
public:
	virtual void slot0(void) = 0;
	virtual void slot1(void) = 0;
	virtual void slot2(void) = 0;
	virtual void slot3(void) = 0;
	virtual Bool isLightCRC(void) = 0;
	virtual void slot5(void) = 0;
	virtual void slot6(void) = 0;
	virtual void slot7(void) = 0;
	virtual void slot8(void) = 0;
	virtual void slot9(void) = 0;
	virtual void xferVersion(XferVersion *version) = 0;
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
	virtual void xferReal(float *value) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void xferInt(Int *value) = 0;
	virtual void slot31(void) = 0;
	virtual void slot32(void) = 0;
	virtual void xferByte(UnsignedByte *value) = 0;
	virtual void slot34(void) = 0;
	virtual void xferBool(UnsignedInt *value) = 0;
};

struct XferException
{
	void *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);
extern int g_guardTargetTypeThrowInfo;

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DWater.h
class WaterRenderObjClass
{
public:
	virtual void slot0(void) = 0;

	void reset(void);
	void replaceSkyboxTexture(const AsciiString &oldTexName,
		const AsciiString &newTextName);
	void clampSkyboxSubobject(BfmeSkyBoxRenderObjClass *object);

protected:
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer);

private:
	void updateMapOverrides(void);

	char m_beforeSkyBox[0x250 - 0x04];		// +0x04, the vtable pointer is +0x00
	BfmeSkyBoxRenderObjClass *m_skyBox;		// +0x250
	WaterTracksRenderSystem *m_waterTrackSystem;	// +0x254
	WaterMeshData *m_meshData;			// +0x258
	UnsignedInt m_meshDataSize;			// +0x25C
	Bool m_meshInMotion;				// +0x260
	char m_beforeGridCells[0x2A0 - 0x261];
	Int m_gridCellsX;				// +0x2A0
	Int m_gridCellsY;				// +0x2A4
};

// ?reset@WaterRenderObjClass@@QAEXXZ
void WaterRenderObjClass::reset(void)
{
	updateMapOverrides();

	if (m_meshData != 0)
	{
		const int mx = m_gridCellsX + 1;
		const int my = m_gridCellsY + 1;
		WaterMeshData *data = m_meshData;

		for (int y = 0; y < my + 2; ++y)
		{
			for (int x = 0; x < mx + 2; ++x)
			{
				data->velocity = 0.0f;
				data->height = 0.0f;
				data->preferredHeight = 0;
				data->status = 0;
				++data;
			}
		}

		m_meshInMotion = false;
	}

	if (m_waterTrackSystem != 0)
		m_waterTrackSystem->reset();
}

// ?xfer@WaterRenderObjClass@@MAEXPAVXfer@@@Z
void WaterRenderObjClass::xfer(Xfer *xfer)
{
	if (xfer->isLightCRC())
		return;

	XferVersion version = { 1, 1 };
	xfer->xferVersion(&version);

	Int cellsX = m_gridCellsX;
	xfer->xferInt(&cellsX);
	if (cellsX != m_gridCellsX) {
		XferException error;
		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	Int cellsY = m_gridCellsY;
	xfer->xferInt(&cellsY);
	if (cellsY != m_gridCellsY) {
		XferException error;
		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	for (Int i = 0; i < m_meshDataSize; ++i) {
		xfer->xferReal(&m_meshData[i].height);
		xfer->xferReal(&m_meshData[i].velocity);
		xfer->xferByte(&m_meshData[i].status);
		xfer->xferByte(&m_meshData[i].preferredHeight);
	}
}

// ?replaceSkyboxTexture@WaterRenderObjClass@@QAEXABVAsciiString@@0@Z
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
