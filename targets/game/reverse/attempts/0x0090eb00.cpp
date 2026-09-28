// ?d_0090eb00@@YAXXZ
// partial score=0.96 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep /Iinputs/toolchains/dx81/include
// BFME chunk texture loader at RVA 0x0090EB00. The reference algorithm is
// GeneralsMD/WW3D2/texture.cpp Load_Texture; BFME returns an owning handle.
// Code ends at 0x0090EE2F; the following dispatch/index tables are data.
#include "chunkio.h"
#include "texture.h"
#include "w3d_file.h"
#include <string.h>
class Gen_00920a60 { public: void m(int); };
class ShroudFilter : public Gen_00920a60 {
public:
    char before0C[0x0c];
    int field0C;
    int field10;
    void set0C(int value) { field0C=value; }
    void set10(int value) { field10=value; }
};
class ShroudTexture { public: ShroudFilter *getFilter(); };
class BFMEWaterTrackTextureHandle {
public:
    TextureClass *m_texture;
    BFMEWaterTrackTextureHandle() : m_texture(0) {}
    BFMEWaterTrackTextureHandle(const BFMEWaterTrackTextureHandle &v) : m_texture(v.m_texture) {
        if (m_texture) m_texture->Add_Ref();
    }
    ~BFMEWaterTrackTextureHandle() { if (m_texture) m_texture->Release_Ref(); }
};
BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char *,int,int);
bool Render_Obj_Exists(const char *);
class W3DRadarFormatCaps {
public:
    char before13C[0x13c];
    bool field13C;
    bool supportTextureFormat(WW3DFormat);
};
extern W3DRadarFormatCaps *TheW3DRadarFormatCaps;
extern bool g_rva00F4050C;

BFMEWaterTrackTextureHandle Load_Texture(ChunkLoadClass &cload)
{
    char name[256];
    if (cload.Open_Chunk() && cload.Cur_Chunk_ID() == W3D_CHUNK_TEXTURE) {
        W3dTextureInfoStruct texinfo;
        bool hastexinfo = false;
        name[0] = 0;
        while (cload.Open_Chunk()) {
            switch (cload.Cur_Chunk_ID()) {
            case W3D_CHUNK_TEXTURE_NAME:
                cload.Read(name, cload.Cur_Chunk_Length()); break;
            case W3D_CHUNK_TEXTURE_INFO:
                cload.Read(&texinfo,sizeof(texinfo)); hastexinfo = true; break;
            }
            cload.Close_Chunk();
        }
        cload.Close_Chunk();
        char *extension = strrchr(name,'.');
        if (extension && !_strcmpi(extension,".tga")) {
            char alternative[256];
            strcpy(alternative,name);
            char *newextension=alternative+(extension-name);
            strcpy(newextension,".dds");
            if (Render_Obj_Exists(alternative)) strcpy(name,alternative);
            else {
                strcpy(newextension,".jpg");
                if (Render_Obj_Exists(alternative)) strcpy(name,alternative);
            }
        }
        if (hastexinfo) {
            int mipcount;
            bool no_lod = ((texinfo.Attributes&W3DTEXTURE_NO_LOD)==W3DTEXTURE_NO_LOD);
            if (no_lod) mipcount=1;
            else switch (texinfo.Attributes&W3DTEXTURE_MIP_LEVELS_MASK) {
                case W3DTEXTURE_MIP_LEVELS_ALL: mipcount=0; break;
                case W3DTEXTURE_MIP_LEVELS_2: mipcount=2; break;
                case W3DTEXTURE_MIP_LEVELS_3: mipcount=3; break;
                case W3DTEXTURE_MIP_LEVELS_4: mipcount=4; break;
                default: mipcount=0; break;
            }
            int format=0;
            if ((texinfo.Attributes&W3DTEXTURE_TYPE_MASK)==W3DTEXTURE_TYPE_BUMPMAP) {
                if (g_rva00F4050C && TheW3DRadarFormatCaps->field13C) {
                    mipcount=1;
                    if (TheW3DRadarFormatCaps->supportTextureFormat((WW3DFormat)60)) format=60;
                    else if (TheW3DRadarFormatCaps->supportTextureFormat((WW3DFormat)62)) format=62;
                    else if (TheW3DRadarFormatCaps->supportTextureFormat((WW3DFormat)61)) format=61;
                }
            }
            BFMEWaterTrackTextureHandle texture=BFMEGetWaterTrackTexture(name,mipcount,format);
            if (no_lod) ((ShroudTexture*)&texture)->getFilter()->m(0);
            bool u_clamp=((texinfo.Attributes&W3DTEXTURE_CLAMP_U)!=0);
            ((ShroudTexture*)&texture)->getFilter()->set0C(u_clamp?1:0);
            bool v_clamp=((texinfo.Attributes&W3DTEXTURE_CLAMP_V)!=0);
            ((ShroudTexture*)&texture)->getFilter()->set10(v_clamp?1:0);
            return texture;
        }
        return BFMEGetWaterTrackTexture(name,0,0);
    }
    return BFMEWaterTrackTextureHandle();
}
