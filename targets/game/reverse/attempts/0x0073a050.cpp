// ?rva0073a050@Rva00739C70@@QAE_NIIIII_N@Z
// partial score=1.0 date=2026-10-09
// cl: /DNDEBUG /MD /O2 /Ob2

class TextureBaseClass;
class VirtualReleaser00739E00
{
public:
    virtual void v0();
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
};

enum WW3DFormat { WW3D_FORMAT_UNKNOWN_0073A050 };
enum _D3DPOOL { D3DPOOL_DEFAULT_0073A050 };

// The private four-byte view is measured evidence. Shared-header adoption is unresolved.
class SurfaceClass
{
public:
    VirtualReleaser00739E00 *m_obj;
    SurfaceClass(unsigned, unsigned, WW3DFormat, _D3DPOOL);
    ~SurfaceClass();
    void Unlock();
};

class W3DRadarResetSurface
{
public:
    ~W3DRadarResetSurface();
    // ??4W3DRadarResetSurface@@QAEAAV0@ABV0@@Z absent-from-retail
    W3DRadarResetSurface &operator=(const W3DRadarResetSurface &other)
    {
        if (other.m_obj)
            other.m_obj->AddRef();
        if (m_obj)
            m_obj->Release();
        m_obj = other.m_obj;
        return *this;
    }
    // ??4W3DRadarResetSurface@@QAEAAV0@ABVSurfaceClass@@@Z absent-from-retail
    W3DRadarResetSurface &operator=(const SurfaceClass &other)
    {
        if (other.m_obj)
            other.m_obj->AddRef();
        if (m_obj)
            m_obj->Release();
        m_obj = other.m_obj;
        return *this;
    }
    VirtualReleaser00739E00 *m_obj;
};

class Rva006D6050
{
public:
    void init(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);
};

class W3DRadarResetTexture
{
public:
    W3DRadarResetSurface getSurfaceLevel();
};

struct TexturePtr
{
    TextureBaseClass *m_ptr;
};

class Rva00739C70
{
public:
    bool rva0073a050(unsigned, unsigned, unsigned, unsigned, unsigned, bool);
    void reset();
    TextureBaseClass *update(int);
    void cleanup()
    {
        if (m_flags & 1) {
            reinterpret_cast<SurfaceClass *>(&m_member0c)->Unlock();
            m_flags &= ~1;
        }
    }
    int m_int0;
    int m_int4;
    TexturePtr m_ptr08;
    W3DRadarResetSurface m_member0c;
    int m_flags;
};

// ?rva0073a050@Rva00739C70@@QAE_NIIIII_N@Z present-unmatched
bool Rva00739C70::rva0073a050(unsigned width, unsigned height,
    unsigned logicalWidth, unsigned logicalHeight, unsigned format, bool flag)
{
    m_int0 = logicalWidth;
    m_int4 = logicalHeight;
    if (flag) {
        m_flags = 4;
        m_member0c = SurfaceClass(width, height, static_cast<WW3DFormat>(format), D3DPOOL_DEFAULT_0073A050);
        int pitch;
        if (!update(reinterpret_cast<int>(&pitch))) {
            reset();
            return false;
        }
        cleanup();
        return true;
    } else {
        m_flags = 0;
        reinterpret_cast<Rva006D6050 *>(&m_ptr08)->init(width, height, format, 1, 1, 0);
        if (m_ptr08.m_ptr) {
            m_member0c = reinterpret_cast<W3DRadarResetTexture *>(&m_ptr08)->getSurfaceLevel();
            int pitch;
            if (update(reinterpret_cast<int>(&pitch))) {
                cleanup();
                return true;
            }
            reset();
            return false;
        }
        return false;
    }
}
