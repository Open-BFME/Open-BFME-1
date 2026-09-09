// cl: /DNDEBUG /MD /EHsc

// BFME's W3DTerrainVisual is a 0x20-byte multiple-inheritance object.  The
// generated queue pointed at 0x0073104B, five bytes before this destructor's
// EH prologue.  The callable body starts at 0x00731050 and ends at ret at
// +0xFC; the following bytes are INT3 padding.

class Xfer;

class AsciiString
{
public:
	~AsciiString();

private:
	char *m_data;
};

class BfmeSnapshotBase
{
public:
	~BfmeSnapshotBase() {}

protected:
	virtual void crc(Xfer *) = 0;
	virtual void xfer(Xfer *) = 0;
	virtual void loadPostProcess() = 0;
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;

private:
	AsciiString m_name;
};

class W3DTerrainVisualBase : public BfmeSnapshotBase, public SubsystemInterface
{
public:
	virtual ~W3DTerrainVisualBase();

private:
	AsciiString m_filenameString;
};

class RefCountClass
{
public:
	virtual void Delete_This(void) = 0;

	void Release_Ref(void)
	{
		if (--NumRefs == 0)
			Delete_This();
	}

	int NumRefs;
};

class BaseHeightMapRenderObjClass : public RefCountClass
{
};

class WorldHeightMap : public RefCountClass
{
};

class TerrainTracksRenderObjClassSystem
{
public:
	~TerrainTracksRenderObjClassSystem();
};

class W3DShadowManager
{
public:
	~W3DShadowManager();
};

class SmudgeManager
{
public:
	virtual ~SmudgeManager();
};

class W3DSmudgeManager : public SmudgeManager
{
public:
	virtual ~W3DSmudgeManager();
};

class WaterRenderObjClassBase
{
public:
	virtual ~WaterRenderObjClassBase() {}
};

// BFME's water object has a leading polymorphic base.  RefCountClass is the
// secondary base at +4, which is why retail adjusts the +0x14 member through
// EAX before entering Release_Ref.
class WaterRenderObjClass : public WaterRenderObjClassBase, public RefCountClass
{
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
extern TerrainTracksRenderObjClassSystem *TheTerrainTracksRenderObjClassSystem;
extern W3DShadowManager *TheW3DShadowManager;
extern SmudgeManager *TheSmudgeManager;
extern WaterRenderObjClass *TheWaterRenderObj;

class W3DTerrainVisual : public W3DTerrainVisualBase
{
public:
	virtual ~W3DTerrainVisual();

private:
	BaseHeightMapRenderObjClass *m_terrainRenderObject;
	WaterRenderObjClass *m_waterRenderObject;
	WorldHeightMap *m_logicHeightMap;
	bool m_isWaterGridRenderingEnabled;
};

W3DTerrainVisual::~W3DTerrainVisual()
{
	if (TheTerrainRenderObject == m_terrainRenderObject)
		TheTerrainRenderObject = 0;

	if (TheTerrainTracksRenderObjClassSystem) {
		delete TheTerrainTracksRenderObjClassSystem;
		TheTerrainTracksRenderObjClassSystem = 0;
	}

	if (TheW3DShadowManager) {
		delete TheW3DShadowManager;
		TheW3DShadowManager = 0;
	}

	if (TheSmudgeManager) {
		delete TheSmudgeManager;
		TheSmudgeManager = 0;
	}

	if (m_waterRenderObject) {
		m_waterRenderObject->Release_Ref();
		m_waterRenderObject = 0;
	}
	TheWaterRenderObj = 0;

	if (m_terrainRenderObject) {
		m_terrainRenderObject->Release_Ref();
		m_terrainRenderObject = 0;
	}

	if (m_logicHeightMap) {
		m_logicHeightMap->Release_Ref();
		m_logicHeightMap = 0;
	}
}
