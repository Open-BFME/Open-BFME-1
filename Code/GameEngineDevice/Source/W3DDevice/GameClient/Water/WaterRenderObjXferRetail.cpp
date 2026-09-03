// cl: /DNDEBUG /MD /EHsc
// Clean BFME reconstruction of WaterRenderObjClass::xfer at 0x0079FC10.

typedef signed int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

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

struct WaterMeshData
{
	float height;
	float velocity;
	UnsignedByte status;
	UnsignedByte preferredHeight;
};

class WaterRenderObjClass
{
public:
	virtual void slot0(void) = 0;

protected:
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer);

	char beforeMeshData[0x254];
	WaterMeshData *m_meshData;
	UnsignedInt m_meshDataSize;
	char beforeGridCells[0x40];
	Int m_gridCellsX;
	Int m_gridCellsY;
};

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
