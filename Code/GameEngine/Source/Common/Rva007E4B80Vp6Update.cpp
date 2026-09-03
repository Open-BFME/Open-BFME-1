// ?update@Rva007E4B80Vp6Stream@@QAEHH@Z [retail body 0x007E4B80]
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class Rva007E4820FrameClock
{
public:
    int frame(int flags);
};

class Rva007E4AD0Vp6Stream
{
public:
    void update(void);
};

class Rva007E4B80Nested
{
public:
    virtual void release(void);
};

struct Rva007E4B80Locals
{
    int period;
    int rate;
    int flag4;
    int frame;
};

class Rva007E4B80Vp6Stream
{
public:
    virtual void unused0(void);
    virtual void unused1(void);
    virtual void reset(void);
    virtual void advance(void);
    virtual void unused4(void);
    virtual char canProcess(int flags);
    virtual void unused6(void);
    virtual void unused7(void);
    virtual void unused8(void);
    virtual void unused9(void);
    virtual void unused10(void);
    virtual void unused11(void);
    virtual void unused12(void);
    virtual char isReady(void);

    int update(int flags);

private:
    char m_pad0[0x28];
    Rva007E4B80Nested *m_nested;
    char m_pad30[0x10];
    int m_rate;
    int m_period;
    int m_frame;
    int m_previous;
    int m_time;
};

int Rva007E4B80Vp6Stream::update(int flags)
{
    Rva007E4B80Locals local;
    int result = isReady() ? 2 : 0;
    if (m_frame < 0) {
        reset();
    }

    local.flag4 = flags & 4;
    if (local.flag4 == 0 && (result & 2) != 0) {
        return result;
    }
    if (!canProcess(flags)) {
        return result;
    }

    local.frame = ((Rva007E4820FrameClock *)this)->frame(flags);
    if (*(volatile unsigned char *)0x01309838 || local.flag4 || (flags & 0x40)) {
        local.rate = m_period;
        local.period = m_rate;
        int now = (int)timeGetTime();
        int elapsed = now - (int)(((__int64)(local.rate * 1000) * local.frame) / local.period);
        int frameTime = 1000 / (local.period / local.rate);
        if (elapsed - m_time > frameTime) {
            m_time = elapsed;
        }
    }

    while (m_frame < local.frame) {
        if (isReady() || local.flag4) {
            break;
        }
        reset();
        result |= 4;
    }

    if (flags & 1) {
        return result;
    }

    if (m_previous != m_frame) {
        advance();
        m_nested->release();
        result |= 1;
        reset();
        if (local.flag4 != 0 && isReady()) {
            ((Rva007E4AD0Vp6Stream *)this)->update();
        }
    }

    return result;
}
