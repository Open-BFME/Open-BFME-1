// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// BFME's W3DVideoBuffer grew beyond the Zero Hour layout.  The matched
// W3DDisplay::createVideoBuffer(bool) caller allocates 0x4c bytes and calls
// this constructor through ILT 0x0002b733.  Retail's VideoBuffer initializer
// writes the prefix through +0x28; the derived constructor then builds one
// nontrivial 0x14-byte state at +0x2c, points +0x40/+0x44 at it, and clears
// the three flags at +0x48..+0x4a.
//
// The state layout is independently exercised by the matched cleanup family
// at 0x00739c70..0x00739f00: +8 owns a texture reference, +0xc owns a surface
// handle, and +0x10 is its flags word.  Public names for this BFME-only state
// and the Display registration method were not recovered, so their names stay
// address-derived while retaining their proven data and calling ABIs.

class TextureClass;

class W3DVideoSurfaceHandle
{
public:
    ~W3DVideoSurfaceHandle();

private:
    void *m_surface;
};

class Rva00739C70State
{
public:
    Rva00739C70State();
    ~Rva00739C70State();

private:
    int m_value_00;
    int m_value_04;
    TextureClass *m_texture;
    W3DVideoSurfaceHandle m_surface;
    unsigned int m_flags;
};

class VideoBuffer
{
public:
    VideoBuffer(int format);
    virtual ~VideoBuffer();
    virtual bool allocate(unsigned int width, unsigned int height) = 0;
    virtual void free() = 0;
    virtual void *lock() = 0;
    virtual void unlock() = 0;
    virtual bool valid() = 0;

protected:
    unsigned int m_x_pos;
    unsigned int m_y_pos;
    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_texture_width;
    unsigned int m_texture_height;
    unsigned int m_pitch;
    float m_value_20;
    int m_format;
    bool m_flag_28;
};

class Display
{
public:
    void Rva006F2890RegisterVideoBuffer(VideoBuffer *buffer);
};

extern Display *TheDisplay;

class W3DVideoBuffer : public VideoBuffer
{
public:
    W3DVideoBuffer(int format);
    virtual ~W3DVideoBuffer();
    virtual bool allocate(unsigned int width, unsigned int height);
    virtual void free();
    virtual void *lock();
    virtual void unlock();
    virtual bool valid();

private:
    Rva00739C70State m_states[1];
    Rva00739C70State *m_state_40;
    Rva00739C70State *m_state_44;
    bool m_flag_48;
    bool m_flag_49;
    bool m_flag_4a;
};

W3DVideoBuffer::W3DVideoBuffer(int format)
    : VideoBuffer(format),
      m_state_40(m_states),
      m_state_44(m_states),
      m_flag_48(false),
      m_flag_49(false),
      m_flag_4a(false)
{
    if (TheDisplay != 0) {
        TheDisplay->Rva006F2890RegisterVideoBuffer(this);
    }
}
