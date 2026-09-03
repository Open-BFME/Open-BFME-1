// ?d_007e4820@@YAXXZ
// partial score=0.6 date=2026-09-03
// ?frame@Rva007E4820FrameClock@@QAEHH@Z [retail body 0x007E4820]
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class Rva007E4820FrameClock
{
public:
    int frame(int flags);

private:
    char m_pad0[0x40];
    int m_scale;
    int m_denominator;
    int m_frame;
    int m_pad4c;
    int m_startTime;
};

int Rva007E4820FrameClock::frame(int flags)
{
    if (!*(volatile unsigned char *)0x01309838 && !(flags & 0x44)) {
        return (int)(((__int64)((int)timeGetTime() - m_startTime) * m_scale
            / m_denominator) / 1000);
    }

    int scale = m_scale;
    if (flags & 0x800000)
        scale >>= 1;

    flags = m_frame + 1;
    if (flags >= (int)(((__int64)((int)timeGetTime() - m_startTime) * scale
        / m_denominator) / 1000))
        return flags;
    return (int)(((__int64)((int)timeGetTime() - m_startTime) * scale
        / m_denominator) / 1000);
}
