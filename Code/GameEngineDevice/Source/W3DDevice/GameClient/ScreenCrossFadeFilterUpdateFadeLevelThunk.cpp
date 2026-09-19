// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib
// readable body of ?updateFadeLevel@ScreenCrossFadeFilter@@IAE_NXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DShaderManager.h
class ScreenCrossFadeFilter
{
protected:
    bool updateFadeLevel();
};

class ScreenCrossFadeFilterUpdateFadeLevelShim
{
public:
    bool update();

private:
    static float m_curFadeValue;
    static int m_fadeDirection;
    static int m_fadeFrames;
    static int m_curFadeFrame;
};

class TacticalViewFadeShim
{
public:
    virtual void unused00();
    virtual void unused01();
    virtual void unused02();
    virtual void unused03();
    virtual void unused04();
    virtual void unused05();
    virtual void unused06();
    virtual void unused07();
    virtual void unused08();
    virtual void unused09();
    virtual void unused10();
    virtual void unused11();
    virtual void unused12();
    virtual void unused13();
    virtual void unused14();
    virtual void unused15();
    virtual void unused16();
    virtual void unused17();
    virtual void unused18();
    virtual void unused19();
    virtual void unused20();
    virtual void unused21();
    virtual void unused22();
    virtual void unused23();
    virtual void unused24();
    virtual void unused25();
    virtual void unused26();
    virtual void unused27();
    virtual void unused28();
    virtual void unused29();
    virtual void unused30();
    virtual void unused31();
    virtual void unused32();
    virtual void unused33();
    virtual void unused34();
    virtual void unused35();
    virtual void unused36();
    virtual void unused37();
    virtual void unused38();
    virtual void unused39();
    virtual void unused40();
    virtual void unused41();
    virtual void unused42();
    virtual void unused43();
    virtual bool setViewFilterMode(int mode);
    virtual void unused45();
    virtual bool setViewFilter(int filter);
};

extern TacticalViewFadeShim *TheTacticalViewFadeShim;

bool ScreenCrossFadeFilter::updateFadeLevel()
{
    return ((ScreenCrossFadeFilterUpdateFadeLevelShim *)this)->update();
}

bool ScreenCrossFadeFilterUpdateFadeLevelShim::update()
{
    if (m_fadeDirection > 0) {
        ++m_curFadeFrame;
        int fade = m_curFadeFrame;

        if (fade < m_fadeFrames) {
            m_curFadeValue = (float)fade / (float)m_fadeFrames;
        } else {
            m_curFadeFrame = 0;
            m_curFadeValue = 1.0f;
            m_fadeDirection = 0;
            return false;
        }
    } else if (m_fadeDirection < 0) {
        int fade = m_curFadeFrame;

        if (fade < m_fadeFrames) {
            m_curFadeValue = 1.0f - (float)fade / (float)m_fadeFrames;
            ++m_curFadeFrame;
        } else {
            m_curFadeValue = 0.0f;
            TheTacticalViewFadeShim->setViewFilterMode(0);
            TheTacticalViewFadeShim->setViewFilter(0);
            m_curFadeFrame = 0;
            m_fadeDirection = 0;
            return false;
        }
    }

    return true;
}
