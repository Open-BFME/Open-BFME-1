// ?Load_Texture@@YA?AVBfmeHandleCX@@AAVChunkLoadClass@@@Z
// partial score=0.83 date=2026-09-15
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ibuild/toolchains/dx81/include
/*
** Copyright 2025 Electronic Arts Inc.
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

// BFME Load_Texture, retail RVA 0x0090EB00, retail boundary 800 bytes.
// The BFME mesh loader names this return as BfmeHandleCX and calls it twice
// from MeshModelClass::read_textures (0x0096EC40).  Unlike the upstream
// pointer-returning helper, this body obtains the texture through the
// owning BFME water-track handle and then transfers one reference to the
// caller's BfmeHandleCX.
#include "w3d_file.h"
#include "texturefilter.h"

extern "C" __declspec(dllimport) char * __cdecl strrchr(const char *, int);
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

class ChunkLoadClass
{
public:
    bool Open_Chunk(void);
    unsigned long Cur_Chunk_ID(void);
    unsigned long Cur_Chunk_Length(void);
    unsigned long Read(void *, unsigned long);
    bool Close_Chunk(void);
};

class TextureClass
{
public:
    void Add_Ref(void)
    {
        ++*(unsigned short *)((char *)this + 4);
    }
    void Release_Ref(void);
};

class BFMEWaterTrackTextureHandle
{
public:
    TextureClass *m_texture;

    ~BFMEWaterTrackTextureHandle(void)
    {
        if (m_texture)
            m_texture->Release_Ref();
    }
};

class BfmeHandleCX
{
public:
    BfmeHandleCX(void) : p(0) {}

    BfmeHandleCX(const BfmeHandleCX &other) : p(other.p)
    {
        if (p)
            p->Add_Ref();
    }

    BfmeHandleCX(const BFMEWaterTrackTextureHandle &other)
        : p(other.m_texture)
    {
        if (p)
            p->Add_Ref();
    }

    ~BfmeHandleCX(void)
    {
        if (p)
            p->Release_Ref();
    }

    BfmeHandleCX &operator=(const BfmeHandleCX &other)
    {
        if (other.p)
            other.p->Add_Ref();
        if (p)
            p->Release_Ref();
        p = other.p;
        return *this;
    }

    TextureClass *p;
};

// This is the established water-track helper declaration.  Its BFME handle
// return is converted to the mesh-loader handle at the two return paths.
extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
    char *name, int mipCount, int format);

enum WW3DFormat
{
    WW3D_FORMAT_UNKNOWN = 0
};

class W3DRadarFormatCaps
{
public:
    bool supportTextureFormat(WW3DFormat format);
};

// Retail reads the DX8 caps pointer at 0x01340578 and uses the radar-format
// method through that object.  Keep the established data symbol spelling so
// the relocation resolves to that pointer, rather than inventing a second
// typed global.
extern unsigned char *BfmeCurrentCaps;
extern bool Render_Obj_Exists(const char *name);

class Gen_00920a60
{
public:
    void m(int value);
};

class ShroudFilter : public Gen_00920a60
{
};

class ShroudTexture
{
public:
    ShroudFilter *getFilter(void);

    void *m_texture;
};

static void copy_texture_name(char *destination, const char *source)
{
    unsigned int i = 0;
    do {
        destination[i] = source[i];
    } while (source[i++]);
}

BfmeHandleCX Load_Texture(ChunkLoadClass &cload)
{
    W3dTextureInfoStruct texinfo;
    char name[256];
    char candidate[256];

    if (!cload.Open_Chunk() || cload.Cur_Chunk_ID() != W3D_CHUNK_TEXTURE)
        return BfmeHandleCX();

    bool hastexinfo = false;
    name[0] = 0;
    while (cload.Open_Chunk()) {
        switch (cload.Cur_Chunk_ID()) {
        case W3D_CHUNK_TEXTURE_NAME:
            cload.Read(name, cload.Cur_Chunk_Length());
            break;
        case W3D_CHUNK_TEXTURE_INFO:
            cload.Read(&texinfo, sizeof(W3dTextureInfoStruct));
            hastexinfo = true;
            break;
        }
        cload.Close_Chunk();
    }
    cload.Close_Chunk();

    // Retail tries the BFME texture suffixes when a TGA render object is
    // named but not present in the registry.  The two five-byte globals
    // are the shipped suffix literals at 0x0112030C and 0x01120304.
    char *extension = strrchr(name, '.');
    if (extension && _strcmpi(extension, (const char *)0x0109416c) == 0) {
        copy_texture_name(candidate, name);
        char *candidate_extension = candidate + (extension - name);
        *(unsigned long *)candidate_extension =
            *(const unsigned long *)0x0112030c;
        candidate_extension[4] = *(const unsigned char *)0x01120310;
        if (Render_Obj_Exists(candidate)) {
            copy_texture_name(name, candidate);
        } else {
            *(unsigned long *)candidate_extension =
                *(const unsigned long *)0x01120304;
            candidate_extension[4] = *(const unsigned char *)0x01120308;
            if (Render_Obj_Exists(candidate))
                copy_texture_name(name, candidate);
        }
    }

    if (!hastexinfo) {
        return BFMEGetWaterTrackTexture(name, 0, 0);
    }

    {
    MipCountType mipcount;
    bool no_lod = (texinfo.Attributes & W3DTEXTURE_NO_LOD) == W3DTEXTURE_NO_LOD;
    if (no_lod) {
        mipcount = MIP_LEVELS_1;
    } else {
        switch (texinfo.Attributes & W3DTEXTURE_MIP_LEVELS_MASK) {
        case W3DTEXTURE_MIP_LEVELS_ALL:
            mipcount = MIP_LEVELS_ALL;
            break;
        case W3DTEXTURE_MIP_LEVELS_2:
            mipcount = MIP_LEVELS_2;
            break;
        case W3DTEXTURE_MIP_LEVELS_3:
            mipcount = MIP_LEVELS_3;
            break;
        case W3DTEXTURE_MIP_LEVELS_4:
            mipcount = MIP_LEVELS_4;
            break;
        default:
            mipcount = MIP_LEVELS_ALL;
            break;
        }
    }

    int format = WW3D_FORMAT_UNKNOWN;
    if ((texinfo.Attributes & W3DTEXTURE_TYPE_MASK) == W3DTEXTURE_TYPE_BUMPMAP) {
        if (*(const unsigned char *)0x0134050c && BfmeCurrentCaps[0x13c]) {
            mipcount = MIP_LEVELS_1;
            if (reinterpret_cast<W3DRadarFormatCaps *>(BfmeCurrentCaps)->supportTextureFormat((WW3DFormat)0x3c))
                format = 0x3c;
            else if (reinterpret_cast<W3DRadarFormatCaps *>(BfmeCurrentCaps)->supportTextureFormat((WW3DFormat)0x3e))
                format = 0x3e;
            else if (reinterpret_cast<W3DRadarFormatCaps *>(BfmeCurrentCaps)->supportTextureFormat((WW3DFormat)0x3d))
                format = 0x3d;
        }
    }

    BFMEWaterTrackTextureHandle texture =
        BFMEGetWaterTrackTexture(name, mipcount, format);
    if (no_lod)
        reinterpret_cast<ShroudTexture *>(&texture)->getFilter()->m(0);

    // The filter subobject is at +0x1C of the texture returned by the handle.
    // Keep the two address flags as retail DWORD stores.
    ShroudFilter *filter =
        reinterpret_cast<ShroudTexture *>(&texture)->getFilter();
    *(int *)((char *)filter + 0x0c) =
        (texinfo.Attributes & W3DTEXTURE_CLAMP_U) != 0;
    filter = reinterpret_cast<ShroudTexture *>(&texture)->getFilter();
    *(int *)((char *)filter + 0x10) =
        (texinfo.Attributes & W3DTEXTURE_CLAMP_V) != 0;

    return BfmeHandleCX(texture);
    }
}
