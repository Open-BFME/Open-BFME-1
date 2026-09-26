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
	Real bfmeReadReal();
	Byte bfmeReadByte();
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
	void bfmeUpdateMacroTexture(AsciiString textureName, Bool force);
	void bfmeUpdateTexture(AsciiString textureName);

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

#pragma comment(linker, "/alternatename:?bfmeReadReal@DataChunkInput@@QAEMXZ=?j_0002e5e1@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeReadByte@DataChunkInput@@QAEEXZ=?j_0000c234@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeReadAsciiString@DataChunkInput@@QAE?AVAsciiString@@XZ=?j_000041c9@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeUpdateMacroTexture@BaseHeightMapRenderObjClass@@QAEXVAsciiString@@_N@Z=?j_00003ce2@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeUpdateTexture@BaseHeightMapRenderObjClass@@QAEXVAsciiString@@@Z=?j_00003b66@@YAXXZ")

Bool BaseHeightMapRenderObjClass::ParseEnvironmentData(
	DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	Bool force = false;
	Real first = TheTerrainRenderObject->m_environmentFirst;
	Real second = TheTerrainRenderObject->m_environmentSecond;

	if (info->version >= 3)
	{
		first = file.bfmeReadReal();
		second = file.bfmeReadReal();
	}

	TheTerrainRenderObject->m_environmentFirst = first;
	TheTerrainRenderObject->m_environmentSecond = second;

	if (info->version >= 2)
		force = file.bfmeReadByte();

	AsciiString textureName = file.bfmeReadAsciiString();
	TheTerrainRenderObject->bfmeUpdateMacroTexture(textureName, force);
	textureName = file.bfmeReadAsciiString();
	TheTerrainRenderObject->bfmeUpdateTexture(textureName);
	return true;
}
