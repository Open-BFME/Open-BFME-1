// ?d_0074f1f0@@YAXXZ
// partial score=0.17 date=2026-09-20
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// BFME WorldHeightMap::ParseBlendTileData at retail 0x0074F1F0.

#include <string.h>
#include "windows.h"

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef float Real;

class Rva0074F1F0AsciiString
{
public:
	~Rva0074F1F0AsciiString();
	void *m_data;
};

class Rva0074F1F0UnicodeString
{
public:
	void set(const Rva0074F1F0AsciiString &source);
	void *m_data;
	void *m_aux;
};

class DataChunkInput
{
public:
	Int readInt(void);
	Real readReal(void);
	UnsignedByte readByte(void);
	Rva0074F1F0AsciiString readAsciiString(void);
	void readArrayOfBytes(char *ptr, Int len);
};

struct DataChunkInfo
{
	char m_header[8];
	UnsignedShort version;
};

struct Rva0074F1F0GlobalData
{
	char m_padding[0x40];
	Bool m_use3WayTerrainBlends;
};

class Rva0074F1F0GameEngine
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void serviceWindowsOS(void) = 0;
};

class Rva0074F1F0ByteVector
{
public:
    void resize(unsigned int count, UnsignedByte value);

	UnsignedByte *m_start;
	UnsignedByte *m_finish;
	UnsignedByte *m_end;
};

class Rva0074F1F0ShortVector
{
public:
	Rva0074F1F0ShortVector(unsigned int count);
	~Rva0074F1F0ShortVector();

	UnsignedShort *begin(void) { return m_start; }
	UnsignedShort *end(void) { return m_finish; }

	UnsignedShort *m_start;
	UnsignedShort *m_finish;
	UnsignedShort *m_end;
};

void *operator new[](unsigned int size);
void operator delete(void *ptr);

Int *rva0074F1F0ShortToIntCopy(UnsignedShort *first, UnsignedShort *last,
	Int *result);

struct Rva0074F1F0BlendTile
{
	Int blendNdx;
	UnsignedByte horiz;
	UnsignedByte vert;
	UnsignedByte rightDiagonal;
	UnsignedByte leftDiagonal;
	UnsignedByte inverted;
	UnsignedByte longDiagonal;
	UnsignedByte m_padding0a[2];
	Int customBlendEdgeClass;
};

class Rva0074F1F0BlendVector
{
public:
	Rva0074F1F0BlendTile *begin(void) { return m_start; }
	Rva0074F1F0BlendTile *end(void) { return m_finish; }
	unsigned int size(void) const
	{
		return (unsigned int)(m_finish - m_start);
	}

	void fillInsert(Rva0074F1F0BlendTile *position, unsigned int count,
		const Rva0074F1F0BlendTile &value);

	void resize(unsigned int count)
	{
		Rva0074F1F0BlendTile value = Rva0074F1F0BlendTile();
		if (count < size())
		{
			Rva0074F1F0BlendTile *dest = m_start + count;
			m_finish = dest;
		}
		else
		{
			fillInsert(end(), count - size(), value);
		}
	}

	Rva0074F1F0BlendTile *m_start;
	Rva0074F1F0BlendTile *m_finish;
	Rva0074F1F0BlendTile *m_end;
};

struct Rva0074F1F0CliffInfo
{
	Real u0;
	Real v0;
	Real u1;
	Real v1;
	Real u2;
	Real v2;
	Real u3;
	Real v3;
	UnsignedByte flip;
	UnsignedByte mutant;
	UnsignedShort tileIndex;
};

class Rva0074F1F0CliffVector
{
public:
	void resize(unsigned int count);

	Rva0074F1F0CliffInfo *m_start;
	Rva0074F1F0CliffInfo *m_finish;
	Rva0074F1F0CliffInfo *m_end;
};

struct Rva0074F1F0TextureClass
{
	Int globalTextureClass;
	Int firstTile;
	Int numTiles;
	Int width;
	char m_padding10[4];
	Rva0074F1F0UnicodeString name;
	char m_padding1c[12];
};

class Rva0074F1F0TileData;

class WorldHeightMap
{
public:
	void readTexClass(Rva0074F1F0TextureClass *textureClass,
		Rva0074F1F0TileData **tiles);

	char m_base[8];
	Int m_width;
	Int m_height;
	Int m_borderSize;
	char m_boundaries[12];
	Int m_dataSize;
	UnsignedByte *m_data;
	Rva0074F1F0ByteVector m_vector28;
	Int m_flipStateWidth;
	Rva0074F1F0ByteVector m_vector38;
	Rva0074F1F0ByteVector m_vector44;
	Rva0074F1F0ByteVector m_vector50;
	Rva0074F1F0ByteVector m_vector5c;
	Rva0074F1F0ByteVector m_vector68;
	Rva0074F1F0ByteVector m_vector74;
	Rva0074F1F0ByteVector m_vector80;
	unsigned short *m_tileNdxes;
	Int *m_blendTileNdxes;
	Int *m_cliffInfoNdxes;
	Int *m_extraBlendTileNdxes;
	Int m_numBitmapTiles;
	Int m_numEdgeTiles;
	Rva0074F1F0TileData *m_sourceTiles[0x1000];
	Rva0074F1F0TileData *m_edgeTiles[0x1000];
	Rva0074F1F0BlendVector m_blendedTiles;
	Rva0074F1F0CliffVector m_cliffInfo;
	Int m_numTextureClasses;
	Rva0074F1F0TextureClass m_textureClasses[0x200];
	Int m_numEdgeTextureClasses;
	Rva0074F1F0TextureClass m_edgeTextureClasses[0x200];

	protected:
	void initCliffFlagsFromHeights(void);
	Bool ParseBlendTileData(DataChunkInput &file, DataChunkInfo *info);
};

#pragma comment(linker, "/alternatename:?readInt@DataChunkInput@@QAEHXZ=?j_0003a805@@YAXXZ")
#pragma comment(linker, "/alternatename:?readReal@DataChunkInput@@QAEMXZ=?j_0002e5e1@@YAXXZ")
#pragma comment(linker, "/alternatename:?readByte@DataChunkInput@@QAEDXZ=?j_0000c234@@YAXXZ")
#pragma comment(linker, "/alternatename:?readArrayOfBytes@DataChunkInput@@QAEXPADH@Z=?j_00026972@@YAXXZ")
#pragma comment(linker, "/alternatename:?readAsciiString@DataChunkInput@@QAE?AVRva0074F1F0AsciiString@@XZ=?j_000041c9@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva0074F1F0AsciiString@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")
#pragma comment(linker, "/alternatename:?set@Rva0074F1F0UnicodeString@@QAEXABVRva0074F1F0AsciiString@@@Z=?set@UnicodeString@@QAEXABV1@@Z")
#pragma comment(linker, "/alternatename:?resize@Rva0074F1F0ByteVector@@QAEXIE@Z=?j_0001656d@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva0074F1F0ShortVector@@QAE@I@Z=?j_0001eba5@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva0074F1F0ShortVector@@QAE@XZ=?j_0003dd11@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0074F1F0ShortToIntCopy@@YAPAHPAF0PAH@Z=?j_00036778@@YAXXZ")
#pragma comment(linker, "/alternatename:?fillInsert@Rva0074F1F0BlendVector@@QAEXPAURva0074F1F0BlendTile@@IABU2@@Z=?j_00012efe@@YAXXZ")
#pragma comment(linker, "/alternatename:?resize@Rva0074F1F0CliffVector@@QAEXI@Z=?j_0000f42a@@YAXXZ")
#pragma comment(linker, "/alternatename:?readTexClass@WorldHeightMap@@QAEXPAURva0074F1F0TextureClass@@PAPAVRva0074F1F0TileData@@@Z=?j_00042537@@YAXXZ")
#pragma comment(linker, "/alternatename:?initCliffFlagsFromHeights@WorldHeightMap@@QAEXXZ=?j_00008085@@YAXXZ")

static __forceinline Rva0074F1F0GlobalData *rvaGlobalData(void)
{
	return *reinterpret_cast<Rva0074F1F0GlobalData **>(0x012ED5C8);
}

static __forceinline Rva0074F1F0GameEngine *rvaGameEngine(void)
{
	return *reinterpret_cast<Rva0074F1F0GameEngine **>(0x012ED524);
}

static __forceinline void rvaServiceWindowsOS(void)
{
	::Sleep(0);
	Rva0074F1F0GameEngine *engine = rvaGameEngine();
	if (engine != 0)
		engine->serviceWindowsOS();
}

extern void __declspec(noreturn) __stdcall _CxxThrowException(void *, void *);

static __forceinline void rvaThrowCorrupt(void)
{
	Int error = 0xDEAD0005;
	_CxxThrowException(&error, (void *)0x011E0004);
}

Bool WorldHeightMap::ParseBlendTileData(
	DataChunkInput &file, DataChunkInfo *info)
{
	Int i;
	Int j;
	Int len = file.readInt();
	if (m_dataSize != len)
		rvaThrowCorrupt();

	m_tileNdxes = (UnsignedShort *)operator new[]((unsigned int)(m_dataSize * 2));
	m_cliffInfoNdxes = (Int *)operator new[]((unsigned int)(m_dataSize * 4));
	m_blendTileNdxes = (Int *)operator new[]((unsigned int)(m_dataSize * 4));
	m_extraBlendTileNdxes = (Int *)operator new[]((unsigned int)(m_dataSize * 4));

	Int numBytesX = (m_width + 7) / 8;
	Int numBytesY = m_height;
	Int byteCount = numBytesX * numBytesY;
	m_flipStateWidth = numBytesX;
	m_vector28.resize(byteCount, 0);
	m_vector38.resize(byteCount, 0);
	m_vector5c.resize(byteCount, 0);
	m_vector68.resize(byteCount, 0);
	m_vector74.resize(byteCount, 0);
	m_vector80.resize(byteCount, 0);
	rvaServiceWindowsOS();
	m_vector44.resize(byteCount, 0);
	m_vector50.resize(byteCount, 0xff);

	file.readArrayOfBytes((char *)m_tileNdxes, m_dataSize * 2);
	if (info->version >= 12)
	{
		file.readArrayOfBytes((char *)m_blendTileNdxes, m_dataSize * 4);
		file.readArrayOfBytes((char *)m_extraBlendTileNdxes, m_dataSize * 4);
	}
	else
	{
		Rva0074F1F0ShortVector source(m_dataSize);
		file.readArrayOfBytes((char *)source.begin(), m_dataSize * 2);
		rva0074F1F0ShortToIntCopy(source.begin(), source.end(), m_blendTileNdxes);
		if (info->version >= 6)
		{
			file.readArrayOfBytes((char *)source.begin(), m_dataSize * 2);
			rva0074F1F0ShortToIntCopy(source.begin(), source.end(), m_extraBlendTileNdxes);
		}
	}

	if (rvaGlobalData()->m_use3WayTerrainBlends == false)
		memset(m_extraBlendTileNdxes, 0, m_dataSize * 4);
	rvaServiceWindowsOS();

	if (info->version >= 14)
	{
		file.readArrayOfBytes((char *)m_cliffInfoNdxes, m_dataSize * 4);
	}
	else if (info->version >= 5)
	{
		Rva0074F1F0ShortVector source(m_dataSize);
		file.readArrayOfBytes((char *)source.begin(), m_dataSize * 2);
		rva0074F1F0ShortToIntCopy(source.begin(), source.end(), m_cliffInfoNdxes);
	}

	rvaServiceWindowsOS();

	if (info->version >= 7)
	{
		if (info->version == 7)
		{
			Int byteWidth = (m_width + 1) / 8;
			file.readArrayOfBytes((char *)m_vector38.m_start, m_height * byteWidth);
		}
		else
		{
			file.readArrayOfBytes((char *)m_vector38.m_start,
				m_height * m_flipStateWidth);
		}
	}
	if (info->version < 9)
		initCliffFlagsFromHeights();
	if (info->version >= 11)
		file.readArrayOfBytes((char *)m_vector68.m_start,
			m_height * m_flipStateWidth);
	if (info->version >= 10)
		file.readArrayOfBytes((char *)m_vector5c.m_start,
			m_height * m_flipStateWidth);
	if (info->version >= 13)
		file.readArrayOfBytes((char *)m_vector74.m_start,
			m_height * m_flipStateWidth);
	if (info->version >= 15)
		file.readArrayOfBytes((char *)m_vector80.m_start,
			m_height * m_flipStateWidth);

	m_numBitmapTiles = file.readInt();
	Int numBlendedTiles = file.readInt();
	Int numCliffInfo = (info->version >= 5) ? file.readInt() : 1;
	m_numTextureClasses = file.readInt();

	for (i = 0; i < m_numTextureClasses; ++i)
	{
		m_textureClasses[i].globalTextureClass = -1;
		m_textureClasses[i].firstTile = file.readInt();
		m_textureClasses[i].numTiles = file.readInt();
		m_textureClasses[i].width = file.readInt();
		Rva0074F1F0AsciiString name = file.readAsciiString();
		m_textureClasses[i].name.set(name);
		readTexClass(&m_textureClasses[i], m_sourceTiles);
	}
	rvaServiceWindowsOS();

	m_numEdgeTextureClasses = 0;
	m_numEdgeTiles = 0;
	if (info->version >= 4)
	{
		m_numEdgeTiles = file.readInt();
		m_numEdgeTextureClasses = file.readInt();
		for (i = 0; i < m_numEdgeTextureClasses; ++i)
		{
			m_edgeTextureClasses[i].globalTextureClass = -1;
			m_edgeTextureClasses[i].firstTile = file.readInt();
			m_edgeTextureClasses[i].numTiles = file.readInt();
			m_edgeTextureClasses[i].width = file.readInt();
			Rva0074F1F0AsciiString name = file.readAsciiString();
			m_edgeTextureClasses[i].name.set(name);
			readTexClass(&m_edgeTextureClasses[i], m_edgeTiles);
		}
	}
	rvaServiceWindowsOS();

	m_blendedTiles.resize(numBlendedTiles);
	for (i = 1; i < numBlendedTiles; ++i)
	{
		Rva0074F1F0BlendTile &tile = m_blendedTiles.m_start[i];
		tile.blendNdx = file.readInt();
		tile.horiz = file.readByte();
		tile.vert = file.readByte();
		tile.rightDiagonal = file.readByte();
		tile.leftDiagonal = file.readByte();
		tile.inverted = file.readByte();
		if (!rvaGlobalData()->m_use3WayTerrainBlends)
			tile.inverted &= (UnsignedByte)~2;
		if (info->version >= 3)
			tile.longDiagonal = file.readByte();
		else
			tile.longDiagonal = 0;
		if (info->version >= 4)
			tile.customBlendEdgeClass = file.readInt();
		else
			tile.customBlendEdgeClass = -1;
		if (file.readInt() != (Int)0x7ADA0000)
			rvaThrowCorrupt();
	}
	rvaServiceWindowsOS();

	m_cliffInfo.resize(numCliffInfo);
	if (info->version >= 5)
	{
		for (i = 1; i < numCliffInfo; ++i)
		{
			Rva0074F1F0CliffInfo &cliff = m_cliffInfo.m_start[i];
			cliff.tileIndex = (UnsignedShort)file.readInt();
			cliff.u0 = file.readReal();
			cliff.v0 = file.readReal();
			cliff.u1 = file.readReal();
			cliff.v1 = file.readReal();
			cliff.u2 = file.readReal();
			cliff.v2 = file.readReal();
			cliff.u3 = file.readReal();
			cliff.v3 = file.readReal();
			cliff.flip = file.readByte();
			cliff.mutant = file.readByte();
		}
	}

	if (info->version == 1)
	{
		Int newWidth = (m_width + 1) / 2;
		Int newHeight = (m_height + 1) / 2;
		for (i = 0; i < newHeight; ++i)
		{
			for (j = 0; j < newWidth; ++j)
			{
				m_tileNdxes[i * newWidth + j] =
					m_tileNdxes[2 * i * m_width + 2 * j];
				m_blendTileNdxes[i * newWidth + j] = 0;
				m_extraBlendTileNdxes[i * newWidth + j] = 0;
				m_cliffInfoNdxes[i * newWidth + j] = 0;
			}
		}
		m_width = newWidth;
		m_height = newHeight;
		m_dataSize = m_width * m_height;
	}
	return true;
}
