// ?Load_Texture@@YA?AVBfmeHandleCX@@AAVChunkLoadClass@@@Z  retail 0x0090EB00, 1029 bytes.
// Boundary [0x0090EB00, 0x0090EF05): the sole normal return is `c3` at +0x32E
// (0x0090EE2E), padded with one `90`, then the compiler-emitted switch data the
// same source produced: the four 4-byte case pointers at +0x330 (0x0090EE30,
// DIR32 to the +0x1BE/+0x1C5/+0x1CC/+0x1D3 arms) and the 0xC1-byte (mask 0..0xC0)
// dispatch-index table at +0x344 (0x0090EE44..0x0090EF04). probe.py compares all
// 1029 bytes EXACT (45 relocation slots, 0 non-relocation differences) and
// tools/build.py claimed_boundary_issue() reports none.
// Identity: symbols.csv pins this name at this address; the matched caller
// MeshModelClass::read_textures (0x0096EC40) consumes the returned owning handle,
// and the loader's calls at +0x247/+0x302 reach 0x0090E910
// (?BFMEGetWaterTrackTexture@@YA?AVBFMEWaterTrackTextureHandle@@PADHH@Z).
// BFME retargets GeneralsMD's TextureClass* texture reader to a 4-byte owning
// handle: hidden result pointer, Add_Ref on the copy into the caller's result,
// Release_Ref on the temporary.  The two suffix probes run against a local
// `alternative` buffer and the two suffix copies must be spelled inline as
// `strcpy(alternative+(extension-name), ".dds"/".jpg")`; caching the
// destination pointer in a local made VC7.1 schedule the copies differently
// from retail (first drift +0xFC), and any spelling of a second handle class
// for the same 4 bytes grows the frame by 4 and re-colours the whole body.
// The object therefore emits the callee's canonical spelling of the one class
// (?Load_Texture@@YA?AVBFMEWaterTrackTextureHandle@@AAVChunkLoadClass@@@Z) and
// binds through object-symbol= in the ledger; every caller compiled against
// ?AVBfmeHandleCX@@ resolves through the row name and the symbols.csv pin.
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep /Iinputs/toolchains/dx81/include

#include "texturefilter.h"
#include "chunkio.h"
#include "w3d_file.h"
#include <string.h>
class TextureClass {
public:
    void Add_Ref() { ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4); }
    void Release_Ref();
};
class ShroudFilter {
public:
    char before0C[0x0c];
    int field0C;
    int field10;
    void set0C(int value) { field0C=value; }
    void set10(int value) { field10=value; }
};
class ShroudTexture { public: ShroudFilter *getFilter(); };
enum WW3DFormat { WW3D_FORMAT_UNKNOWN = 0 };
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
extern bool g_0134050C;

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
        if (extension && !_stricmp(extension,".tga")) {
            char alternative[256];
            strcpy(alternative,name);
            strcpy(alternative+(extension-name),".dds");
            if (Render_Obj_Exists(alternative)) strcpy(name,alternative);
            else {
                strcpy(alternative+(extension-name),".jpg");
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
                if (g_0134050C && TheW3DRadarFormatCaps->field13C) {
                    mipcount=1;
                    if (TheW3DRadarFormatCaps->supportTextureFormat((WW3DFormat)60)) format=60;
                    else if (TheW3DRadarFormatCaps->supportTextureFormat((WW3DFormat)62)) format=62;
                    else if (TheW3DRadarFormatCaps->supportTextureFormat((WW3DFormat)61)) format=61;
                }
            }
            BFMEWaterTrackTextureHandle texture=BFMEGetWaterTrackTexture(name,mipcount,format);
            if (no_lod) reinterpret_cast<TextureFilterClass *>(((ShroudTexture*)&texture)->getFilter())->Set_Mip_Mapping(TextureFilterClass::FILTER_TYPE_NONE);
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
