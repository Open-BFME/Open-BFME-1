// ?rva0090CAD0@Rva0090C2F0Inner@@QAE_NXZ
// partial score=0.9928 date=2026-10-10
// cl: /DNDEBUG /MD /EHsc
// The matched Rva0090CD00LoadFromMemory caller supplies this 0x48-byte owner.
// D3D9 slots and explicit releases follow the complete retail body.

struct IDirect3DDevice8;
struct IDirect3DDevice9;
struct IDirect3DSurface9;
struct _D3DXIMAGE_INFO;
typedef _D3DXIMAGE_INFO D3DXIMAGE_INFO;
struct tagPALETTEENTRY;
typedef tagPALETTEENTRY PALETTEENTRY;
struct tagRECT;
typedef tagRECT RECT;
typedef unsigned long DWORD;
typedef unsigned UINT;
enum D3DFORMAT
{
    D3DFMT_UNKNOWN = 0,
    D3DFMT_A8R8G8B8 = 21,
    D3DFMT_A8 = 28,
    D3DFMT_L8 = 50,
    D3DFMT_FORCE_DWORD = 0x7fffffff
};
enum D3DPOOL
{
    D3DPOOL_DEFAULT = 0,
    D3DPOOL_MANAGED = 1,
    D3DPOOL_SYSTEMMEM = 2,
    D3DPOOL_SCRATCH = 3,
    D3DPOOL_FORCE_DWORD = 0x7fffffff
};

struct D3DSURFACE_DESC
{
    D3DFORMAT Format;
    unsigned Type, Usage, Pool, MultiSampleType, MultiSampleQuality, Width, Height;
};

struct D3DLOCKED_RECT
{
    int Pitch;
    void *pBits;
};

struct IDirect3DSurface9
{
    virtual long __stdcall QueryInterface(const void *, void **);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
};

struct IDirect3DBaseTexture9
{
    virtual long __stdcall QueryInterface(const void *, void **);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual void __stdcall s0c(); virtual void __stdcall s10();
    virtual void __stdcall s14(); virtual void __stdcall s18();
    virtual void __stdcall s1c(); virtual void __stdcall s20();
    virtual void __stdcall s24(); virtual void __stdcall s28();
    virtual void __stdcall s2c(); virtual void __stdcall s30();
    virtual unsigned long __stdcall GetLevelCount();
    virtual void __stdcall s38(); virtual void __stdcall s3c();
    virtual void __stdcall s40();
};

struct IDirect3DTexture9 : IDirect3DBaseTexture9
{
    virtual long __stdcall GetLevelDesc(UINT, D3DSURFACE_DESC *);
    virtual long __stdcall GetSurfaceLevel(unsigned, IDirect3DSurface9 **);
    virtual long __stdcall LockRect(unsigned, D3DLOCKED_RECT *, const RECT *, DWORD);
    virtual long __stdcall UnlockRect(unsigned);
};

extern "C" long __stdcall D3DXCreateTexture(IDirect3DDevice9 *, UINT, UINT, UINT,
    DWORD, D3DFORMAT, D3DPOOL, IDirect3DTexture9 **);
extern "C" long __stdcall D3DXLoadSurfaceFromFileInMemory(IDirect3DSurface9 *, const PALETTEENTRY *,
    const RECT *, const void *, UINT, const RECT *, DWORD, DWORD, D3DXIMAGE_INFO *);
extern "C" long __stdcall D3DXCreateTextureFromFileInMemoryEx(IDirect3DDevice9 *, const void *,
    UINT, UINT, UINT, UINT, DWORD, D3DFORMAT, D3DPOOL, DWORD, DWORD,
    DWORD, D3DXIMAGE_INFO *, PALETTEENTRY *, IDirect3DTexture9 **);
extern "C" long __stdcall D3DXFilterTexture(IDirect3DBaseTexture9 *, const PALETTEENTRY *, UINT, DWORD);

class Rva0090C2F0Inner;

class DX8Wrapper
{
    friend class Rva0090C2F0Inner;
protected:
    static IDirect3DDevice8 *D3DDevice;
};

class Rva0090C2F0Inner
{
    void *m_vptr;
    char m_04;
    IDirect3DTexture9 *m_08;
    int m_0C;
    unsigned char *m_10;
    unsigned m_14;
    int m_18;
    unsigned char *m_1C;
    int m_20;
    unsigned m_24;
    unsigned m_28;
    unsigned m_2C;
    unsigned m_30;
    int m_34;
    int m_38;
    int m_3C;
    int m_40;
    int m_44;
public:
    bool rva0090CAD0();
};

// ?rva0090CAD0@Rva0090C2F0Inner@@QAE_NXZ
bool Rva0090C2F0Inner::rva0090CAD0()
{
    if (!m_1C || !m_20)
        return false;

    m_3C = 0x15;
    if (D3DXCreateTexture((IDirect3DDevice9 *)DX8Wrapper::D3DDevice,
        m_24, m_28, m_34, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_08) < 0)
    {
        m_08 = 0;
        return false;
    }

    bool success = false;
    IDirect3DSurface9 *surface;
    if (m_08->GetSurfaceLevel(0, &surface) >= 0)
    {
        IDirect3DTexture9 *alphaTexture;
        if (D3DXLoadSurfaceFromFileInMemory(surface, 0, 0, m_10, m_14, 0, 0xffffffff, 0, 0) >= 0
            && D3DXCreateTextureFromFileInMemoryEx((IDirect3DDevice9 *)DX8Wrapper::D3DDevice,
                m_1C, m_20, m_24, m_28, 1, 0, D3DFMT_A8, D3DPOOL_SYSTEMMEM, 0xffffffff, 0xffffffff,
                0, 0, 0, &alphaTexture) >= 0)
        {
            D3DSURFACE_DESC desc;
            alphaTexture->GetLevelDesc(0, &desc);
            if (desc.Format == D3DFMT_A8 || desc.Format == D3DFMT_L8 || desc.Format == D3DFMT_A8R8G8B8)
            {
                unsigned alphaStride = 1;
                unsigned alphaOffset = 0;
                if (desc.Format == D3DFMT_A8R8G8B8)
                {
                    alphaOffset = 3;
                    alphaStride = 4;
                }
                D3DLOCKED_RECT destination, alpha;
                if (m_08->LockRect(0, &destination, 0, 0) >= 0)
                {
                    if (alphaTexture->LockRect(0, &alpha, 0, 0) >= 0)
                    {
                        success = true;
                        unsigned char *destinationRow = (unsigned char *)destination.pBits;
                        unsigned char *alphaRow = (unsigned char *)alpha.pBits;
                        for (unsigned y = 0; y < m_28; ++y)
                        {
                            unsigned char *sourcePixel = alphaRow + alphaOffset;
                            unsigned char *destinationPixel = destinationRow + 3;
                            for (unsigned x = 0; x < m_24; ++x)
                            {
                                *destinationPixel = *sourcePixel;
                                sourcePixel += alphaStride;
                                destinationPixel += 4;
                            }
                            alphaRow += alpha.Pitch;
                            destinationRow += destination.Pitch;
                        }
                        alphaTexture->UnlockRect(0);
                    }
                    m_08->UnlockRect(0);
                }
            }
            alphaTexture->Release();
        }
        surface->Release();
    }
    if (success)
        D3DXFilterTexture(m_08, 0, 0, 0xffffffff);
    else
    {
        m_08->Release();
        m_08 = 0;
    }
    return m_08 != 0;
}
