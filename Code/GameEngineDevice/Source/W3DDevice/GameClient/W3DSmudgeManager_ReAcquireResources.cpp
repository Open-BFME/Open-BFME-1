// cl: /DNDEBUG /MD /EHsc

// W3DSmudgeManager::ReAcquireResources, retail 0x00722200, 297 bytes.
// Port of GeneralsMD W3DSmudge.cpp, adapted to BFME's by-value
// W3DRadarResetSurface back-buffer wrapper and 0x18-byte DX8IndexBufferClass.

#define SMUDGE_DRAW_SIZE 500

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.h
class SurfaceClass
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.h
	struct SurfaceDescription
	{
		unsigned Format;
		unsigned Width;
		unsigned Height;
	};

	void Get_Description(SurfaceDescription &surface_desc);
};

class W3DRadarResetSurface : public SurfaceClass
{
public:
	~W3DRadarResetSurface();

private:
	void *m_surface;
};

W3DRadarResetSurface getBackBufferSurface006e(int index);

void W3DRadarResetLock(void);
void W3DRadarResetUnlock(void);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8indexbuffer.h
class IndexBufferClass
{
public:
	class WriteLockClass
	{
		IndexBufferClass *index_buffer;
		unsigned short *indices;

	public:
		WriteLockClass(IndexBufferClass *index_buffer, int flags = 0);
		~WriteLockClass();

		unsigned short *Get_Index_Array() { return indices; }
	};
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8indexbuffer.h
class DX8IndexBufferClass
{
	unsigned char m_bfmeBody[0x18];

public:
	enum UsageType
	{
		USAGE_DEFAULT = 0
	};

	DX8IndexBufferClass(unsigned short index_count, UsageType usage = USAGE_DEFAULT);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Smudge.h
class SmudgeManager
{
public:
	virtual ~SmudgeManager();
	virtual void init(void);
	virtual void reset(void);
	virtual void ReleaseResources(void);
	virtual void ReAcquireResources(void);

private:
	char m_smudgeManagerPad[0x20];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DSmudge.h
class W3DSmudgeManager : public SmudgeManager
{
public:
	void ReAcquireResources(void);

	void *m_smudgeGroup;
	void *m_posBuffer;
	void *m_RGBABuffer;
	void *m_sizeBuffer;
	DX8IndexBufferClass *m_indexBuffer;
	int m_backBufferWidth;
	int m_backBufferHeight;
	unsigned int m_probeColor;
};

class BfmeRadarResetLock
{
public:
	BfmeRadarResetLock() { W3DRadarResetLock(); }
	~BfmeRadarResetLock() { W3DRadarResetUnlock(); }
};

void W3DSmudgeManager::ReAcquireResources(void)
{
	ReleaseResources();

	BfmeRadarResetLock lock;

	W3DRadarResetSurface surface = getBackBufferSurface006e(0);
	SurfaceClass::SurfaceDescription surface_desc;
	surface.Get_Description(surface_desc);

	m_backBufferWidth = (int)surface_desc.Width;
	m_backBufferHeight = (int)surface_desc.Height;

	m_indexBuffer = new DX8IndexBufferClass((unsigned short)(SMUDGE_DRAW_SIZE * 4 * 3));

	{
		IndexBufferClass::WriteLockClass lockIdxBuffer((IndexBufferClass *)m_indexBuffer);
		unsigned short *ib = lockIdxBuffer.Get_Index_Array();
		int vbCount = 0;
		for (int i = 0; i < SMUDGE_DRAW_SIZE; i++)
		{
			ib[0] = (unsigned short)vbCount;
			ib[1] = (unsigned short)(vbCount + 4);
			ib[2] = (unsigned short)(vbCount + 3);
			ib[3] = (unsigned short)(vbCount + 3);
			ib[4] = (unsigned short)(vbCount + 4);
			ib[5] = (unsigned short)(vbCount + 2);
			ib[6] = (unsigned short)(vbCount + 2);
			ib[7] = (unsigned short)(vbCount + 4);
			ib[8] = (unsigned short)(vbCount + 1);
			ib[9] = (unsigned short)(vbCount + 1);
			ib[10] = (unsigned short)(vbCount + 4);
			ib[11] = (unsigned short)(vbCount + 0);

			vbCount += 5;
			ib += 12;
		}
	}
}
