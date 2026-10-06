// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Igame/Libraries/Source/WWVegas/WWLib
void * __cdecl operator new[](unsigned int);
void __cdecl operator delete[](void *);

// This file implements GameLogic::loadAmbientLightMap and TerrainLogic::loadAmbientLightMap.
// The GameLogic method selects the TGA path. The TerrainLogic method loads its pixels.

#include "Common/AsciiString.h"
#include "string_base.h"

#include <stdio.h>
#include <string.h>

// Retail inlines ~AsciiString: temporaries are released by a direct call to
// StringBase<char>::releaseBuffer (0x00887940), not the ??1AsciiString stub.
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

typedef unsigned long DWORD;

extern "C" __declspec(dllimport) void __stdcall Sleep(DWORD);

class __declspec(novtable) GameEngine
{
public:
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void serviceWindowsOS() = 0;
};

extern GameEngine *TheGameEngine;

static inline void loadAmbientLightMapYieldToOS()
{
    Sleep(0);
    if (TheGameEngine)
        TheGameEngine->serviceWindowsOS();
}

class MapCache;
extern MapCache *TheMapCache;

class GameState
{
public:
    bool isInSaveDirectory(const AsciiString &) const;

    struct SaveGameInfo
    {
        AsciiString saveGameMapName;
        AsciiString pristineMapName;
    };

    SaveGameInfo *getSaveGameInfo()
    {
        return &m_gameInfo;
    }

private:
    char m_unrecovered[0x18];
    SaveGameInfo m_gameInfo;
};

extern GameState *TheGameState;

class File
{
public:
	enum { READ = 0x01, BINARY = 0x40 };
	virtual ~File();
	virtual bool open(const char *filename, int access);
	virtual void close(void);
	virtual int read(void *buffer, int bytes);
};

class FileSystem
{
public:
	bool doesFileExist(const char *) const;
	File *openFile(const char *filename, int access);
};

extern FileSystem *TheFileSystem;

class TerrainLogic
{
public:
	void loadAmbientLightMap(AsciiString);
	void clearAmbientLightMap();
};
extern TerrainLogic *TheTerrainLogic;

extern void j_00010c8f();
extern void j_00002ae5();

class GameLogic
{
public:
    void loadAmbientLightMap(AsciiString);
};

void GameLogic::loadAmbientLightMap(AsciiString mapName)
{
    if (!TheMapCache)
        return;

    char filename[260];
    char fullFledgeFilename[260];
    memset(filename, 0, sizeof(filename));
    strcpy(filename, mapName.str());

    loadAmbientLightMapYieldToOS();
    if (TheGameState->isInSaveDirectory(filename))
        strcpy(filename, TheGameState->getSaveGameInfo()->pristineMapName.str());

    int length = strlen(filename);
    if (length < 4)
        return;

    char *extension = filename + length - 4;
    while ((extension > filename) && (*extension != '\\') && (*extension != '/'))
        --extension;
    *extension = 0;

    sprintf(fullFledgeFilename, "%s\\ambientlightmap.tga", filename);
    if (TheFileSystem->doesFileExist(fullFledgeFilename))
    {
		typedef void (TerrainLogic::*LoadAmbientLightMapCall)(AsciiString);
        union
        {
            void (*generic)();
            LoadAmbientLightMapCall typed;
        } loadAmbientLightMap;
        loadAmbientLightMap.generic = j_00010c8f;
		(reinterpret_cast<TerrainLogic *>(TheTerrainLogic)->*
			loadAmbientLightMap.typed)(AsciiString(fullFledgeFilename));
    }
    else
    {
		typedef void (TerrainLogic::*ClearAmbientLightMapCall)();
        union
        {
            void (*generic)();
            ClearAmbientLightMapCall typed;
        } clearAmbientLightMap;
        clearAmbientLightMap.generic = j_00002ae5;
		(reinterpret_cast<TerrainLogic *>(TheTerrainLogic)->*
			clearAmbientLightMap.typed)();
	}
}

class TerrainLogicAmbientLightMapState
{
public:
	unsigned char m_pad00[0x18];
	unsigned char *m_at18;
	unsigned int m_at1C;
	unsigned int m_at20;
};

class BfmeAwakenLog
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual BfmeAwakenLog *slot4C(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68();
	virtual BfmeAwakenLog *slot6C(int first, int second);
};

extern void *g_Rva00F36E5C; // VA 01336E5C debug manager cell (data_rows.csv owner)
#define TheBfmeAwakenDebug (static_cast<BfmeAwakenDebug *>(g_Rva00F36E5C))
extern bool _bfme_debugReportingEnabled(void);
extern void _bfme_debugRecordCallsite(int kind);

static __forceinline void reportDamagedAmbientLightMap(const AsciiString &filename)
{
	if (!_bfme_debugReportingEnabled())
		return;
	_bfme_debugRecordCallsite(1);
	TheBfmeAwakenDebug->slot60();
	reinterpret_cast<BfmeAwakenLog &>(operator<<(
		*reinterpret_cast<Debug *>(TheBfmeAwakenDebug->slot6C(0, 0)),
		*reinterpret_cast<const StringBase<char> *>(&filename)))
		.slot38(" is damaged")->slot4C(2);
}

static __forceinline void reportInvalidAmbientLightMap(const AsciiString &filename)
{
	if (!_bfme_debugReportingEnabled())
		return;
	_bfme_debugRecordCallsite(1);
	TheBfmeAwakenDebug->slot60();
	reinterpret_cast<BfmeAwakenLog &>(operator<<(
		*reinterpret_cast<Debug *>(TheBfmeAwakenDebug->slot6C(0, 0)),
		*reinterpret_cast<const StringBase<char> *>(&filename)))
		.slot38(" is no valid 24 bit RGB TGA")->slot4C(2);
}

struct Rva001A9110TargaHeader
{
	unsigned char idLength;
	unsigned char colorMapType;
	unsigned char imageType;
	unsigned char colorMap[5];
	unsigned short xOrigin;
	unsigned short yOrigin;
	unsigned short width;
	unsigned short height;
	unsigned char pixelDepth;
	unsigned char imageDescriptor;
};

static __forceinline unsigned int rowBytesForWidth(unsigned int width)
{
	return width * 3;
}

// ?loadAmbientLightMap@TerrainLogic@@QAEXVAsciiString@@@Z
void TerrainLogic::loadAmbientLightMap(AsciiString filename)
{
	Rva001A9110TargaHeader header;
	delete[] reinterpret_cast<TerrainLogicAmbientLightMapState *>(this)->m_at18;
	reinterpret_cast<TerrainLogicAmbientLightMapState *>(this)->m_at18 = 0;
	File *file;
	file = TheFileSystem->openFile(
		filename.str(), File::READ | File::BINARY);
	if (!file)
		return;
	TerrainLogicAmbientLightMapState *state =
		reinterpret_cast<TerrainLogicAmbientLightMapState *>(this);
	if (file->read(&header, sizeof(header)) != sizeof(header))
	{
		reportDamagedAmbientLightMap(filename);
		file->close();
		return;
	}
	if (header.idLength != 0 || header.colorMapType != 0 ||
		header.imageType != 2 || header.pixelDepth != 24)
	{
		file->close();
		reportInvalidAmbientLightMap(filename);
		return;
	}
	state->m_at1C = header.width;
	state->m_at20 = header.height;
	state->m_at18 = new unsigned char[
		state->m_at1C * state->m_at20 * 3];
	file->read(state->m_at18,
		*(volatile unsigned int *)&state->m_at1C * state->m_at20 * 3);
	file->close();
	if ((header.imageDescriptor & 0x20) != 0)
	{
		for (unsigned int row = 0; row < state->m_at20 / 2; ++row)
		{
			unsigned char *top =
				state->m_at18 + row * state->m_at1C * 3;
			unsigned char *bottom =
				state->m_at18 + (state->m_at20 - row - 1) *
				state->m_at1C * 3;
			unsigned int rowBytes = rowBytesForWidth(state->m_at1C);
			if (rowBytes != 0)
			{
				unsigned int remaining = rowBytes;
				do
				{
					unsigned char pixel = *top;
					unsigned char other = *bottom;
					*top = other;
					++top;
					*bottom = pixel;
					++bottom;
				} while (--remaining != 0);
			}
		}
	}
}
