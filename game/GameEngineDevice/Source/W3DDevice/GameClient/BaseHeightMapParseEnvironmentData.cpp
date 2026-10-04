// cl: /Igame/Libraries/Source/WWVegas/WWLib
// BaseHeightMapRenderObjClass::ParseEnvironmentData, retail 0x00749C20.
// The BEnvironmentData registration at 0x0074B09E passes thunk 0x00008706,
// which targets this callback.  Retail reads the terrain floats, force flag,
// macro texture name, and default texture name into the BaseHeightMap layout.

typedef float Real;
typedef unsigned char Byte;
typedef bool Bool;

#include "string_base.h"

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(other);
		return *this;
	}
};

class DataChunkInput
{
public:
	// Returns AsciiString through the hidden return pointer.  Retail copy-
	// initialises the local straight from that pointer (no default
	// constructor runs), which no call through a member-pointer typedef
	// reproduces: a raw/out-pointer call default-constructs the local and
	// emits two extra zero stores, and a plain union member cannot be passed
	// by value (C2621).  So this one call keeps its linker mapping.
	AsciiString bfmeReadAsciiString();
};

struct DataChunkInfo
{
	char m_padding[8];
	unsigned short version;
};

class BaseHeightMapRenderObjClass
{
public:
	static Bool ParseEnvironmentData(DataChunkInput &file, DataChunkInfo *info, void *userData);

	char m_padding00[0x3018];
	Real m_environmentFirst;
	Real m_environmentSecond;
	char m_padding3020[0x4c];
	Bool m_environmentForce;
	char m_padding306d[3];
	AsciiString m_macroTextureName;
	AsciiString m_defaultTextureName;
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

// Retail calls go through incremental-link thunks; call those directly.
extern void j_0002e5e1();
extern void j_0000c234();
extern void j_000041c9();
extern void j_00003ce2();
extern void j_00003b66();

#pragma comment(linker, "/alternatename:?bfmeReadAsciiString@DataChunkInput@@QAE?AVAsciiString@@XZ=?j_000041c9@@YAXXZ")

Bool BaseHeightMapRenderObjClass::ParseEnvironmentData(
	DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	typedef Real (DataChunkInput::*ReadReal)();
	typedef Byte (DataChunkInput::*ReadByte)();
	typedef void (BaseHeightMapRenderObjClass::*UpdateMacroTexture)(AsciiString, Bool);
	typedef void (BaseHeightMapRenderObjClass::*UpdateTexture)(AsciiString);
	union { void (*fn)(); ReadReal call; } readReal = { j_0002e5e1 };
	union { void (*fn)(); ReadByte call; } readByte = { j_0000c234 };
	union { void (*fn)(); UpdateMacroTexture call; } updateMacroTexture = { j_00003ce2 };
	union { void (*fn)(); UpdateTexture call; } updateTexture = { j_00003b66 };

	Bool force = false;
	Real first = TheTerrainRenderObject->m_environmentFirst;
	Real second = TheTerrainRenderObject->m_environmentSecond;

	if (info->version >= 3)
	{
		first = (file.*readReal.call)();
		second = (file.*readReal.call)();
	}

	TheTerrainRenderObject->m_environmentFirst = first;
	TheTerrainRenderObject->m_environmentSecond = second;

	if (info->version >= 2)
		force = (file.*readByte.call)();

	AsciiString textureName = file.bfmeReadAsciiString();
	(TheTerrainRenderObject->*updateMacroTexture.call)(textureName, force);
	textureName = file.bfmeReadAsciiString();
	(TheTerrainRenderObject->*updateTexture.call)(textureName);
	return true;
}
