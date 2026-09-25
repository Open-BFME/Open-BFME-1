// ?loadAmbientLightMap@TerrainLogic@@QAEXVAsciiString@@@Z
// partial score=0.7 date=2026-09-24
// cl: /ICode/GameEngine/Include /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/GameEngine/Source/Common/System /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// The matched GameLogic caller reaches this method through ILT 0x00010C8F.

#include "PreRTS.h"
#include "Common/AsciiString.h"
#include "Common/FileSystem.h"
#include "GameLogic/TerrainLogic.h"
#include "string_base.h"

class File
{
public:
	enum { READ = 0x01, BINARY = 0x40 };
	virtual ~File();
	virtual Bool open(const char *filename, Int access);
	virtual void close(void);
	virtual Int read(void *buffer, Int bytes);
};

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

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
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

void TerrainLogic::loadAmbientLightMap(AsciiString filename)
{
	Rva001A9110TargaHeader header;
	delete[] reinterpret_cast<TerrainLogicAmbientLightMapState *>(this)->m_at18;
	reinterpret_cast<TerrainLogicAmbientLightMapState *>(this)->m_at18 = 0;
	File *file = TheFileSystem->openFile(
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
	file->read(state->m_at18, state->m_at1C * state->m_at20 * 3);
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
			unsigned int rowBytes = state->m_at1C * 3;
			for (unsigned int byte = 0; byte < rowBytes; ++byte)
			{
				unsigned char pixel = top[byte];
				top[byte] = bottom[byte];
				bottom[byte] = pixel;
			}
		}
	}
}
