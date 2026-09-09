// ?xfer@W3DTerrainVisual@@MAEXPAVXfer@@@Z
// partial score=0.75 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc

// BFME W3DTerrainVisual::xfer, retail RVA 0x007318A0 (259 bytes).
// The primary W3DTerrainVisual vtable at 0x011212F0 points slot 3 through
// its ILT to this body; the secondary view repeats it at slot 15.  Keep this
// reconstruction in a dedicated TU because the shared Zero Hour visual has
// additional skybox members and a different object layout.

typedef bool Bool;

class Snapshot;
class AsciiString;
class UnicodeString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
struct XferReservedTag;

// The BFME Xfer virtual order is shared by the already matched water and
// terrain xfer bodies.  In particular Version is slot 10 (+0x28), bool is
// slot 35 (+0x8c), int is slot 30 (+0x78), raw bytes is slot 9 (+0x24), and
// Snapshot is slot 12 (+0x30).
class Xfer
{
public:
	class Version { public: unsigned char data[2]; };
	Xfer();
	virtual ~Xfer();
	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;
	virtual void ReservedVirtual1();
	virtual void ReservedVirtual2();
	virtual void ReservedVirtual3();
	virtual void SkipBadBlock(Snapshot &, unsigned int);
	virtual Xfer &XferRawBytes(void *, unsigned int);
	virtual Xfer &operator==(bool &);
	virtual Xfer &operator==(char &);
	virtual Xfer &operator==(unsigned char &);
	virtual Xfer &operator==(short &);
	virtual Xfer &operator==(unsigned short &);
	virtual Xfer &operator==(int &);
	virtual Xfer &operator==(unsigned int &);
	virtual Xfer &operator==(__int64 &);
	virtual Xfer &operator==(float &);
	virtual Xfer &operator==(AsciiString &);
	virtual Xfer &operator==(UnicodeString &);
	virtual Xfer &operator==(Coord3DBase &);
	virtual Xfer &operator==(ICoord3D &);
	virtual Xfer &operator==(Region3D &);
	virtual Xfer &operator==(IRegion3D &);
	virtual Xfer &operator==(Coord2D &);
	virtual Xfer &operator==(ICoord2D &);
	virtual Xfer &operator==(Region2D &);
	virtual Xfer &operator==(IRegion2D &);
	virtual Xfer &operator==(RealRange &);
	virtual Xfer &operator==(RGBColor &);
	virtual Xfer &operator==(RGBAColorReal &);
	virtual Xfer &operator==(RGBAColorInt &);
	virtual Xfer &operator==(Snapshot &);
	virtual Xfer &operator==(XferReservedTag &);
	virtual Xfer &operator==(Version &);
	virtual void ReservedVirtual4();
	virtual Xfer &XferEnum(const char *, void *, unsigned int);
};

struct XferException
{
	void *text;
	int tag;
	XferException(int tag, const char *format, ...);
};

extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);
extern int g_guardTargetTypeThrowInfo;

// Existing ILT 0x00040C2D forwards to the BFME base transfer body at
// 0x00602C40.  Its generated declaration has no visible parameter because
// the thunk preserves the caller's ABI; cast only the call expression so the
// Xfer pointer is pushed for that body.
extern void j_00040c2d();

class Snapshot
{
public:
	virtual ~Snapshot() {}
};

class WaterRenderObjClass : public Snapshot
{
};

class WorldHeightMap
{

	public:
	char m_padding0[0x08];
	int m_width;
	int m_height;
	char m_padding10[0x14];
	unsigned short *m_heights;
	unsigned short *getDataPtr(void) { return m_heights; }
	int getXExtent(void) { return m_width; }
	int getYExtent(void) { return m_height; }
};

#define BFME_VIRTUAL_SLOT(n) virtual void slot##n(void);
class HeightMapRenderObjBase
{
	public:
	BFME_VIRTUAL_SLOT(0)   BFME_VIRTUAL_SLOT(1)   BFME_VIRTUAL_SLOT(2)   BFME_VIRTUAL_SLOT(3)
	BFME_VIRTUAL_SLOT(4)   BFME_VIRTUAL_SLOT(5)   BFME_VIRTUAL_SLOT(6)   BFME_VIRTUAL_SLOT(7)
	BFME_VIRTUAL_SLOT(8)   BFME_VIRTUAL_SLOT(9)   BFME_VIRTUAL_SLOT(10)  BFME_VIRTUAL_SLOT(11)
	BFME_VIRTUAL_SLOT(12)  BFME_VIRTUAL_SLOT(13)  BFME_VIRTUAL_SLOT(14)  BFME_VIRTUAL_SLOT(15)
	BFME_VIRTUAL_SLOT(16)  BFME_VIRTUAL_SLOT(17)  BFME_VIRTUAL_SLOT(18)  BFME_VIRTUAL_SLOT(19)
	BFME_VIRTUAL_SLOT(20)  BFME_VIRTUAL_SLOT(21)  BFME_VIRTUAL_SLOT(22)  BFME_VIRTUAL_SLOT(23)
	BFME_VIRTUAL_SLOT(24)  BFME_VIRTUAL_SLOT(25)  BFME_VIRTUAL_SLOT(26)  BFME_VIRTUAL_SLOT(27)
	BFME_VIRTUAL_SLOT(28)  BFME_VIRTUAL_SLOT(29)  BFME_VIRTUAL_SLOT(30)  BFME_VIRTUAL_SLOT(31)
	BFME_VIRTUAL_SLOT(32)  BFME_VIRTUAL_SLOT(33)  BFME_VIRTUAL_SLOT(34)  BFME_VIRTUAL_SLOT(35)
	BFME_VIRTUAL_SLOT(36)  BFME_VIRTUAL_SLOT(37)  BFME_VIRTUAL_SLOT(38)  BFME_VIRTUAL_SLOT(39)
	BFME_VIRTUAL_SLOT(40)  BFME_VIRTUAL_SLOT(41)  BFME_VIRTUAL_SLOT(42)  BFME_VIRTUAL_SLOT(43)
	BFME_VIRTUAL_SLOT(44)  BFME_VIRTUAL_SLOT(45)  BFME_VIRTUAL_SLOT(46)  BFME_VIRTUAL_SLOT(47)
	BFME_VIRTUAL_SLOT(48)  BFME_VIRTUAL_SLOT(49)  BFME_VIRTUAL_SLOT(50)  BFME_VIRTUAL_SLOT(51)
	BFME_VIRTUAL_SLOT(52)  BFME_VIRTUAL_SLOT(53)  BFME_VIRTUAL_SLOT(54)  BFME_VIRTUAL_SLOT(55)
	BFME_VIRTUAL_SLOT(56)  BFME_VIRTUAL_SLOT(57)  BFME_VIRTUAL_SLOT(58)  BFME_VIRTUAL_SLOT(59)
	BFME_VIRTUAL_SLOT(60)  BFME_VIRTUAL_SLOT(61)  BFME_VIRTUAL_SLOT(62)  BFME_VIRTUAL_SLOT(63)
	BFME_VIRTUAL_SLOT(64)  BFME_VIRTUAL_SLOT(65)  BFME_VIRTUAL_SLOT(66)  BFME_VIRTUAL_SLOT(67)
	BFME_VIRTUAL_SLOT(68)  BFME_VIRTUAL_SLOT(69)  BFME_VIRTUAL_SLOT(70)  BFME_VIRTUAL_SLOT(71)
	BFME_VIRTUAL_SLOT(72)  BFME_VIRTUAL_SLOT(73)  BFME_VIRTUAL_SLOT(74)  BFME_VIRTUAL_SLOT(75)
	BFME_VIRTUAL_SLOT(76)  BFME_VIRTUAL_SLOT(77)  BFME_VIRTUAL_SLOT(78)  BFME_VIRTUAL_SLOT(79)
	BFME_VIRTUAL_SLOT(80)  BFME_VIRTUAL_SLOT(81)  BFME_VIRTUAL_SLOT(82)  BFME_VIRTUAL_SLOT(83)
	BFME_VIRTUAL_SLOT(84)  BFME_VIRTUAL_SLOT(85)  BFME_VIRTUAL_SLOT(86)  BFME_VIRTUAL_SLOT(87)
	BFME_VIRTUAL_SLOT(88)  BFME_VIRTUAL_SLOT(89)  BFME_VIRTUAL_SLOT(90)  BFME_VIRTUAL_SLOT(91)
	BFME_VIRTUAL_SLOT(92)  BFME_VIRTUAL_SLOT(93)  BFME_VIRTUAL_SLOT(94)  BFME_VIRTUAL_SLOT(95)
	BFME_VIRTUAL_SLOT(96)  BFME_VIRTUAL_SLOT(97)  BFME_VIRTUAL_SLOT(98)  BFME_VIRTUAL_SLOT(99)
	BFME_VIRTUAL_SLOT(100) BFME_VIRTUAL_SLOT(101) BFME_VIRTUAL_SLOT(102) BFME_VIRTUAL_SLOT(103)
	BFME_VIRTUAL_SLOT(104) BFME_VIRTUAL_SLOT(105) BFME_VIRTUAL_SLOT(106) BFME_VIRTUAL_SLOT(107)
	BFME_VIRTUAL_SLOT(108) BFME_VIRTUAL_SLOT(109) BFME_VIRTUAL_SLOT(110) BFME_VIRTUAL_SLOT(111)
	BFME_VIRTUAL_SLOT(112) BFME_VIRTUAL_SLOT(113) BFME_VIRTUAL_SLOT(114) BFME_VIRTUAL_SLOT(115)
	BFME_VIRTUAL_SLOT(116) BFME_VIRTUAL_SLOT(117) BFME_VIRTUAL_SLOT(118) BFME_VIRTUAL_SLOT(119)
	BFME_VIRTUAL_SLOT(120) BFME_VIRTUAL_SLOT(121) BFME_VIRTUAL_SLOT(122) BFME_VIRTUAL_SLOT(123)
	BFME_VIRTUAL_SLOT(124) BFME_VIRTUAL_SLOT(125) BFME_VIRTUAL_SLOT(126) BFME_VIRTUAL_SLOT(127)
	BFME_VIRTUAL_SLOT(128) BFME_VIRTUAL_SLOT(129) BFME_VIRTUAL_SLOT(130) BFME_VIRTUAL_SLOT(131)
	BFME_VIRTUAL_SLOT(132) BFME_VIRTUAL_SLOT(133) BFME_VIRTUAL_SLOT(134) BFME_VIRTUAL_SLOT(135)
	BFME_VIRTUAL_SLOT(136) BFME_VIRTUAL_SLOT(137)
	virtual void staticLightingChanged(int partialUpdate);

	private:
	char m_padding0[0xc8];
};
#undef BFME_VIRTUAL_SLOT

class BaseHeightMapRenderObjClass : public HeightMapRenderObjBase, public Snapshot
{
};

class BfmeSnapshotBase
{
public:
	virtual void bfmeSlot0(void);

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess(void);
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init(void);

private:
	char *m_name;
};

class W3DTerrainVisualBase : public BfmeSnapshotBase, public SubsystemInterface
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	char *m_filenameString;
};

class W3DTerrainVisual : public W3DTerrainVisualBase
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	BaseHeightMapRenderObjClass *m_terrainRenderObject;
	WaterRenderObjClass *m_waterRenderObject;
	WorldHeightMap *m_logicHeightMap;
	Bool m_isWaterGridRenderingEnabled;
};

// ?xfer@W3DTerrainVisual@@MAEXPAVXfer@@@Z
void W3DTerrainVisual::xfer(Xfer *xfer)
{
	Xfer &receiver = *xfer;
	// Extend the common terrain visual xfer through the base view.
	W3DTerrainVisualBase::xfer(&receiver);

	if (receiver.IsLightCRC())
		return;

	Xfer::Version version;
	version.data[0] = 1;
	version.data[1] = 1;
	receiver == version;

	Bool gridEnabled = m_isWaterGridRenderingEnabled;
	receiver == gridEnabled;
	if (gridEnabled != m_isWaterGridRenderingEnabled) {
		XferException error(5, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	if (gridEnabled)
		receiver == *m_waterRenderObject;

	unsigned short *data = m_logicHeightMap->getDataPtr();
	int len = m_logicHeightMap->getXExtent() * m_logicHeightMap->getYExtent() * 2;
	int xferLen = len;
	receiver == xferLen;
	if (len > xferLen)
		len = xferLen;
	receiver.XferRawBytes(data, len);
	if (receiver.IsLoading())
		m_terrainRenderObject->staticLightingChanged(1);

	if (m_terrainRenderObject != 0) {
		receiver == *m_terrainRenderObject;
	} else {
		Snapshot *snapshot = 0;
		receiver == *snapshot;
	}
}
