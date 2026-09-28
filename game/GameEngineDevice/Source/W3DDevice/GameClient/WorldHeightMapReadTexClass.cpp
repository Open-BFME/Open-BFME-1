// BFME WorldHeightMap::readTexClass; retail range [0x0074BBB0, 0x0074BCBE) (270B).
// Retail ret 8 is at +0x10B; INT3 padding starts at +0x10E.
// Keep this dedicated TU separate from WorldHeightMap.cpp's broad Zero Hour
// headers: the target uses the out-of-line StringBase copy constructor for its
// by-value terrain name.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
#include "StringInline.h"
#include <stdio.h>

class TileData;
class TerrainType
{
public:
    __declspec(noinline) AsciiString getTexture() { return m_texture; }
private:
    char m_poolState[4];
    AsciiString m_name;
    AsciiString m_texture;
};
class TerrainTypeCollection
{
public:
    TerrainType *findTerrain(AsciiString name);
};
extern TerrainTypeCollection *TheTerrainTypes;

class File
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual void close();
    virtual int read(void *buffer, int count);
    virtual void slot4();
    virtual void seek(int offset, int origin);
};
class FileSystem
{
public:
    File *openFile(const char *name, int mode);
};
extern FileSystem *TheFileSystem;

class InputStream
{
public:
    virtual int read(void *buffer, int count) = 0;
};
class GDIFileStream : public InputStream
{
public:
    GDIFileStream(File *file) : m_file(file) {}
    virtual int read(void *buffer, int count) { return m_file->read(buffer, count); }
private:
    File *m_file;
};

struct TXTextureClass
{
    int globalTextureClass;
    int firstTile;
    int numTiles;
    int width;
    int isBlendEdgeTile;
    AsciiString name;
};

class WorldHeightMap
{
protected:
    void readTexClass(TXTextureClass *texClass, TileData **tileData);
public:
    static int countTiles(InputStream *stream, bool *halfTile = 0);
    static bool readTiles(InputStream *stream, TileData **tiles, int numRows);
};

void WorldHeightMap::readTexClass(TXTextureClass *texClass, TileData **tileData)
{
    File *file = 0;
    TerrainType *terrain = TheTerrainTypes->findTerrain(texClass->name);
    char texturePath[260];
    if (!terrain)
    {
        file = TheFileSystem->openFile(texClass->name.str(), 0x41);
    }
    else
    {
        sprintf(texturePath, "%s%s", "Art/Terrain/", terrain->getTexture().str());
        file = TheFileSystem->openFile(texturePath, 0x41);
    }
    if (file)
    {
        GDIFileStream stream(file);
        InputStream *input = &stream;
        int numTiles = WorldHeightMap::countTiles(input);
        file->seek(0, 0);
        if (numTiles >= texClass->numTiles)
        {
            numTiles = texClass->numTiles;
            int width;
            for (width = 16; width >= 1; --width)
            {
                if (numTiles >= width * width)
                {
                    numTiles = width * width;
                    break;
                }
            }
            WorldHeightMap::readTiles(input, tileData + texClass->firstTile, width);
        }
        file->close();
    }
}
