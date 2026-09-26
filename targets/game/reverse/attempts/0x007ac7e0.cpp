// ?loadTracks@WaterTracksRenderSystemLoadTracksShim@@QAEXXZ
// partial score=0.417391304348 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/asciistring8outofline /Ireference/shims/terrainlogic /Ireference/shims/water /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define Matrix4x4 Matrix4
#include "PreRTS.h"
#include "sphere.h"
#include "aabox.h"
#include "dx8vertexbuffer.h"
#include "dx8indexbuffer.h"
#include "texture.h"
#include "shader.h"
#include "rinfo.h"
#define WaterTracksRenderSystem WaterTracksRenderSystemLoadTracksShim
#include "W3DDevice/GameClient/W3DWaterTracks.h"
#undef WaterTracksRenderSystem
#include <set>
#include <stdio.h>
#include <string.h>

class BFMETerrainLogic
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual AsciiString getSourceFilename() = 0;
};

extern BFMETerrainLogic *TheTerrainLogic;
extern void *bfmeGoEMEb(void *);

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key, _STL::less<Rva001408C0Key>,
	_STL::allocator<Rva001408C0Key> > Rva001408C0Set;

struct Rva001408C0LocalSet
{
	Rva001408C0Set m_set;
	int m_zero;
	bool m_one;

	Rva001408C0LocalSet() : m_zero(0), m_one(true) {}
};

enum waveType
{
	WaveTypeFirst,
	WaveTypePond = WaveTypeFirst,
	WaveTypeOcean,
	WaveTypeCloseOcean,
	WaveTypeCloseOceanDouble,
	WaveTypeRadial,
	WaveTypeLast = WaveTypeRadial,
	WaveTypeStationary,
	WaveTypeMax
};

struct waveInfo
{
	float m_finalWidth;
	float m_finalHeight;
	float m_waveDistance;
	float m_initialVelocity;
	int m_fadeMs;
	float m_initialWidthFraction;
	float m_initialHeightWidthFraction;
	int m_timeToCompress;
	int m_secondWaveTimeOffset;
	char *m_textureName;
	char *m_waveTypeName;
};

#define TheTerrainLogic (*(BFMETerrainLogic **)0x012EF4CC)
#define TheFileSystem (*(FileSystem **)0x0134CB48)
#define TheWaterTracksRenderSystem (*(WaterTracksRenderSystemLoadTracksShim **)0x01306D94)
#define waveTypeInfo (*(waveInfo (*)[WaveTypeMax])0x012BBC28)

class File
{
public:
	enum access { READ = 0x0001, BINARY = 0x0040 };
	enum seekMode { START, CURRENT, END };

	virtual ~File();
	virtual bool open(const char *filename, int access);
	virtual void close(void);
	virtual int read(void *buffer, int bytes);
	virtual int write(const void *buffer, int bytes);
	virtual int seek(int bytes, int mode);
	virtual void nextLine(char *buffer, int bytes);
	virtual bool scanInt(int &value);
	virtual bool scanReal(float &value);
	virtual bool scanString(AsciiString &value);
	virtual bool print(const char *format, ...);
	virtual int size(void);
	virtual int position(void);
	virtual char *readEntireAndClose(void);
	virtual File *convertToRAMFile(void);
	virtual void lock(void);
	virtual void unlock(void);
};

class FileSystem
{
public:
	File *openFile(const char *filename, int access);
};

static const char *bfmeSourceFilename(const AsciiString &fileName)
{
	const char *data = *(const char **)&fileName;
	return data ? data + 8 : (const char *)0x0107388B;
}

void WaterTracksRenderSystemLoadTracksShim::loadTracks(void)
{
	WaterTracksRenderSystemLoadTracksShim *volatile self = this;
	BFMETerrainLogic *terrain = TheTerrainLogic;
	if (!terrain)
		return;

	AsciiString fileName = terrain->getSourceFilename();
	char path[256];

	strcpy(path, bfmeSourceFilename(fileName));
	int len = strlen(path);
	FileSystem *fileSystem = TheFileSystem;
	strcpy(path + len - 4, ".wak");

	File *file = fileSystem->openFile(path, File::READ | File::BINARY);
	WaterTracksObj *umod = 0;
	int trackCount = 0;
	volatile int flipU = 0;
	Vector2 startPos, endPos;
	waveType wtype;
	Rva001408C0LocalSet assets;

	if (file)
	{
		file = file->convertToRAMFile();
		file->seek(-4, File::END);
		file->read(&trackCount, sizeof(trackCount));
		file->seek(0, File::START);
		for (int i = 0; i < trackCount; i++)
		{
		tryagain:
			file->read(&startPos, sizeof(startPos));
			file->read(&endPos, sizeof(endPos));
			file->read(&wtype, sizeof(wtype));
			if (self->findTrack(startPos, endPos, wtype))
			{
				i++;
				goto tryagain;
			}

			umod = TheWaterTracksRenderSystem->bindTrack(wtype);
			if (umod)
			{
				flipU ^= 1;
				umod->init(waveTypeInfo[wtype].m_finalHeight,
					waveTypeInfo[wtype].m_finalWidth, startPos, endPos,
					waveTypeInfo[wtype].m_textureName, 0);
				if (waveTypeInfo[wtype].m_textureName)
				{
					if (assets.m_set.insert((Rva001408C0Key)bfmeGoEMEb(
						waveTypeInfo[wtype].m_textureName)).second)
						assets.m_one = true;
				}
				umod->m_flipU = flipU;

				if (waveTypeInfo[wtype].m_secondWaveTimeOffset)
				{
					umod = TheWaterTracksRenderSystem->bindTrack(wtype);
					if (umod)
					{
						umod->init(waveTypeInfo[wtype].m_finalHeight,
							waveTypeInfo[wtype].m_finalWidth, startPos, endPos,
							waveTypeInfo[wtype].m_textureName,
							waveTypeInfo[wtype].m_secondWaveTimeOffset);
						umod->m_flipU = !flipU;
					}
				}
			}
	}
	file->close();
}
}
