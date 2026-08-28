// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift GameSpyGameSlot dtor __emit thunk to clean C++.
// Five member objects destroyed in reverse order (SEH states 4..0), then the
// out-of-line GameSlot base dtor (pinned).

class GGS_Member
{
public:
    ~GGS_Member();

private:
    unsigned int m_dummy;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
    ~GameSlot();

private:
    unsigned char m_pad[0x48];
};

class GameSpyGameSlot : public GameSlot
{
public:
    ~GameSpyGameSlot();

private:
    GGS_Member m_a;
    GGS_Member m_b;
    GGS_Member m_c;
    unsigned char m_pad[0x1C];
    GGS_Member m_d;
    GGS_Member m_e;
};

// ??1GameSpyGameSlot@@QAE@XZ
GameSpyGameSlot::~GameSpyGameSlot()
{
}
