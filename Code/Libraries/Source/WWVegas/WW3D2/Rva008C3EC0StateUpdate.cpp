// cl: /DNDEBUG /MD /EHsc

class Rva008C3EC0State
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual void On_Zero();

    void Update();

    unsigned m_flags;
    char m_gap08[0x58];
    unsigned m_mode;
};

void Rva008C3EC0State::Update()
{
    unsigned flags = m_flags;
    unsigned mode = m_mode;
    unsigned value = (flags >> 16) & 0xfff;

    if ((mode & 0xc0000) == 0x40000 && value == 1)
        return;

    --value;
    unsigned limited = value;
    if (limited > 0xfff)
        limited = 0xfff;

    flags = (flags & 0xf000ffff) | (limited << 16);
    m_flags = flags;

    if (value == 0)
        On_Zero();
}
