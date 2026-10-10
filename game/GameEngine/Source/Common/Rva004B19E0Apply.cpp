// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/sweep /Igame/GameEngine/Include/Precompiled /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Evidence: targets/game/reverse/identity_evidence/004b19e0-window-vector.md
#include "PreRTS.h"
#include "GameClient/GameWindow.h"
#include <vector>

class Gen_004B1720 { public: void bfmeClear(); };
struct BfmeRunAH
{
    const int *m_bfmeBegin;
    const int *m_bfmeEnd;
};
extern int bfmeSameAH(const BfmeRunAH *, const BfmeRunAH *);
namespace _STL
{
    typedef _STLP_alloc_proxy<GameWindow **, GameWindow *, allocator<GameWindow *> > Proxy004B0130;
    // The capacity-proxy swap stays external at its independently decoded body.
    template <> void swap(Proxy004B0130 &, Proxy004B0130 &);
}

class Rva004B19E0
{
public:
    void apply(void *windows);
    int m_head[2];
    unsigned char m_flag;
    _STL::vector<GameWindow *> m_bfmeVector;
    int m_18, m_1c, m_20, m_24, m_28, m_2c;
    int m_30, m_34, m_38;
    float m_3c, m_40;
};

// ?apply@Rva004B19E0@@QAEXPAX@Z
void Rva004B19E0::apply(void *windows)
{
    _STL::vector<GameWindow *> &incoming = *(_STL::vector<GameWindow *> *)windows;
    _STL::vector<GameWindow *>::iterator it = incoming.begin();
    while (it != incoming.end())
    {
        GameWindow *window = *it;
        if (window == 0)
            it = incoming.erase(it);
        else if (!window->winIsHidden() && (window->winGetStatus() & 0x4000000))
            ++it;
        else
        {
            it = incoming.erase(it);
            window->winSetSize(1, 1);
            window->winSetPosition(-1, -1);
        }
    }
    // The existing comparator returns zero or one; retail consumes AL.
    if (!(unsigned char)bfmeSameAH((const BfmeRunAH *)&m_bfmeVector, (const BfmeRunAH *)&incoming))
    {
        ((Gen_004B1720 *)this)->bfmeClear();
        m_bfmeVector.swap(incoming);
        if (!m_bfmeVector.empty())
        {
            m_flag = 1;
            m_24 = 0;
            m_20 = 0;
            m_2c = 0;
            m_28 = 0;
            m_30 = 0;
            m_34 = 0;
            m_38 = 0;
            m_3c = 0.0f;
            m_40 = 0.0f;
            _STL::vector<GameWindow *>::iterator end = m_bfmeVector.end();
            for (it = m_bfmeVector.begin(); it != end; ++it)
            {
                GameWindow *window = *it;
                window->winSetSize(4, 4);
                window->winSetPosition(m_20, m_24);
                window->winSetStatus(0x200);
            }
        }
    }
}
