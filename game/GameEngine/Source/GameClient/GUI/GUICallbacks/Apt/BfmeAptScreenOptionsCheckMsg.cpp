// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// ?_bfme_checkMsg@BfmeAptScreenOptions@@QAEHHPAX0@Z
// Evidence: targets/game/reverse/identity_evidence/0055f290-options-message.md

#include "ascii_string.h"
#include "unicode_string.h"

class BFMERetailAsciiString : public AsciiString
{
public:
    BFMERetailAsciiString() : AsciiString() {}
    BFMERetailAsciiString(const char *text) : AsciiString(text) {}
    BFMERetailAsciiString(const BFMERetailAsciiString &other) : AsciiString(other) {}
    ~BFMERetailAsciiString() {}
};

// ??0UnicodeString@@QAE@ABV0@@Z absent-from-retail
inline UnicodeString::UnicodeString(const UnicodeString &other)
{
    ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
        *(const StringBase<unsigned short> *)&other);
}
inline UnicodeString::~UnicodeString()
{
    ((StringBase<unsigned short> *)this)->releaseBuffer();
}

class GameWindow
{
public:
    int winEnable(bool enable);
};

class BfmeMsgHandler
{
public:
    int defaultHandler(int msg, void *control, void *data);
};

bool GadgetCheckBoxIsChecked(GameWindow *window);
void GadgetCheckBoxSetChecked(GameWindow *window, bool checked);
void GadgetComboBoxGetSelectedPos(GameWindow *window, int *selected);
int bfmeGo1022L(int window);

class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(int);

struct FunctorBinding
{
    FunctorBinding(FunctorMethod method, FunctorTarget *target)
        : m_target(target), m_method(method) {}

    FunctorTarget *m_target;
    unsigned int m_unmodelled;
    FunctorMethod m_method;
};


class BfmeTagZBRefCounted
{
public:
    virtual void Delete_This(unsigned int);
    int m_refs;
};

class BfmeTagZB
{
public:
    BfmeTagZB() : m_tag(0) {}
    BfmeTagZB(FunctorBinding binding);
    BfmeTagZB(const BfmeTagZB &other) throw() : m_tag(other.m_tag)
    {
        if (m_tag)
            ++((BfmeTagZBRefCounted *)m_tag)->m_refs;
    }
    ~BfmeTagZB()
    {
        BfmeTagZBRefCounted *tag = (BfmeTagZBRefCounted *)m_tag;
        if (tag && --tag->m_refs <= 0)
            tag->Delete_This(1);
    }

    BfmeTagZBRefCounted *m_tag;
};

void bfmeSendZB(void *first, void *second, void *third, BfmeTagZB tag);

class GameTextInterface
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual UnicodeString fetch(const char *label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

class GameLODManager
{
public:
    char m_pad[0x1708];
    int m_currentDetail;
};

extern GameLODManager *TheGameLODManager;

class AudioEventRTS;

class Display
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void setGamma(float gamma, float minimum, float maximum, bool immediate);
};

extern Display *TheDisplay;

class Rva005A00B0AudioClient
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual unsigned int slot17(const AudioEventRTS *event);
    virtual void slot18();
    virtual void slot19();
    virtual bool stopAudioEvent(unsigned int handle);
    virtual void slot21();
    virtual unsigned int slot22(const AudioEventRTS *event);
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual bool slot44(unsigned int handle);
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void setSoundFXVolume(float value);
    virtual void setVoiceVolume(float value);
    virtual void setMusicVolume(float value);
    virtual void setMovieVolume(float value);
    virtual void setAmbientVolume(float value);
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void slot61();
    virtual void slot62();
    virtual void slot63();
    virtual void slot64();
    virtual void slot65();
    virtual void slot66();
    virtual void slot67();
    virtual void slot68();
    virtual void slot69();
    virtual void slot70();
    virtual void slot71();
    virtual void slot72();
    virtual void slot73();
    virtual void slot74();
    virtual void slot75();
    virtual void slot76();
    virtual void slot77();
    virtual void slot78();
    virtual void slot79();
    virtual void slot80();
    virtual void slot81();
    virtual void slot82();
    virtual void slot83();
    virtual void slot84();
    virtual void slot85();
    virtual void slot86();
    virtual void slot87();
    virtual void slot88();
    virtual void slot89();
    virtual void slot90();
    virtual bool slot91(bool enabled);
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

class Rva00367E30Logic
{
public:
    char m_pad[0x10c];
};

class Rva0005C5E0
{
public:
    char m_pad[0x10c];
    int isEither() const;
};

// Retail 0x012F0898 is ?TheGameLogic@@3PAVGameLogic@@A (data_rows.csv,
// GameLogic.cpp); TheBfmeGameLogic was only a pin nothing defines.
class GameLogic;
extern GameLogic *TheGameLogic;
#define TheBfmeGameLogic ( reinterpret_cast<void *>( TheGameLogic ) )

class BfmeAptScreenOptions
{
public:
    int _bfme_checkMsg(int msg, void *control, void *data);

public:
    char m_pad000[0x250];
    int m_rva0055F290At250;
    int m_rva0055F290At254;
    int m_page;
    int m_audioSample;
    char m_options[0x14];
    char m_pad274[0x10];
    GameWindow *m_comboResolution;
    GameWindow *m_comboDetail;
    GameWindow *m_comboOnlineIp;
    GameWindow *m_checkHealthBars;
    GameWindow *m_checkAlternateMouse;
    GameWindow *m_unused298;
    GameWindow *m_checkUnitDecals;
    GameWindow *m_sliderSendDelay;
    char m_pad2a4[4];
    GameWindow *m_checkTurnOffMessenger;
    GameWindow *m_checkForeignLanguage;
    GameWindow *m_checkFilterLanguage;
    GameWindow *m_checkEAX3;
    GameWindow *m_checkHighAudioQuality;
    GameWindow *m_checkAnisotropic;
    GameWindow *m_checkTerrain;
    GameWindow *m_check3DShadows;
    GameWindow *m_check2DShadows;
    GameWindow *m_checkSmoothWater;
    GameWindow *m_checkShowProps;
    GameWindow *m_checkAnimations;
    GameWindow *m_checkHeatEffects;
    GameWindow *m_checkDynamicLOD;
    GameWindow *m_sliderMusic;
    GameWindow *m_sliderSfx;
    GameWindow *m_sliderVoice;
    GameWindow *m_sliderAmbient;
    GameWindow *m_sliderMovie;
    GameWindow *m_sliderScroll;
    GameWindow *m_sliderBrightness;
    GameWindow *m_sliderTexture;
    GameWindow *m_sliderParticle;
    char m_pad304[4];
    bool m_flag308;
    char m_pad309[3];
    int m_defaultResolution;
};

extern void *g_Va012F4AE4;
extern unsigned char g_optByte12F4AD0;
void j_00048a4a();
extern unsigned char g_optFlag12F4AD8;
extern unsigned char g_optFlag12F4AD9;
extern unsigned char g_optFlag12F4ADA;
extern unsigned char g_optFlag12F4ADB;
extern unsigned char g_optFlag12F4ADC;
extern unsigned char g_optFlag12F4ADD;
extern unsigned char g_optFlag12F4ADE;
extern unsigned char g_optFlag12F4ADF;
extern unsigned char g_optFlag12F4AE0;
extern unsigned char g_optFlag12F4AE1;

static __forceinline void clearAudioState()
{
    g_optFlag12F4AE0 = 0;
    g_optFlag12F4AE1 = 0;
    g_optFlag12F4AD8 = 0;
    g_optFlag12F4AD9 = 0;
    g_optFlag12F4ADA = 0;
    g_optFlag12F4ADB = 0;
    g_optFlag12F4ADC = 0;
    g_optFlag12F4ADD = 0;
    g_optFlag12F4ADE = 0;
    g_optFlag12F4ADF = 0;

}

static __forceinline void stopPreviewIfNeeded(BfmeAptScreenOptions *self)
{
    void *handle = g_Va012F4AE4;
    if (handle == 0 || self->m_audioSample == 2)
        return;

    TheAudioClientUpdate->stopAudioEvent((unsigned int)handle);
    g_Va012F4AE4 = 0;
    clearAudioState();
}

class AudioEventRTS
{
public:
    AudioEventRTS(const AsciiString &eventName, int owner);
    virtual ~AudioEventRTS();
    char m_storage[0x6c];
};


struct Rva00579160Manager { public: void fire(void *, const char *, int, int, int, int, int, int); };
extern Rva00579160Manager *Rva00579160TheManager;

class BfmeA1051
{
public:
    void bfmeGo1051A();
};

// ?_bfme_checkMsg@BfmeAptScreenOptions@@QAEHHPAX0@Z
int BfmeAptScreenOptions::_bfme_checkMsg(int msg, void *control, void *data)
{
    int handled = ((BfmeMsgHandler *)this)->defaultHandler(msg, control, data);
    switch ((unsigned int)msg)
    {
    case 1:
        return 1;
    case 2:
        return 1;
    case 0x17:
        goto consumed;
    case 0x4008:


        if (control == m_checkEAX3)
        {
            bool checked = GadgetCheckBoxIsChecked(m_checkEAX3);
            if (checked)
            {
                if (!TheAudioClientUpdate->slot91(checked))
                {
                    Rva00579160TheManager->fire((void *)m_rva0055F290At250, "DoOpenPopMessage", 1, (int)"Eax3NotSupported", 0, 0, 0, 0);
                    GadgetCheckBoxSetChecked(m_checkEAX3, false);
                }
            }
            else TheAudioClientUpdate->slot91(false);
        }
        goto consumed;
    case 0x4025:
    {
        if (control == m_comboDetail)
        {
            int selected;
            GadgetComboBoxGetSelectedPos(m_comboDetail, &selected);
            int current = TheGameLODManager->m_currentDetail;
            int currentPosition;
            switch (current) { case 0: currentPosition=4; break; case 1: currentPosition=3; break; case 2: currentPosition=2; break; case 3: currentPosition=1; break; default: currentPosition=0; }
            if (selected != 5)
            {
                if (selected != m_defaultResolution)
                {
                    if (currentPosition-selected > 0 && current != 3 && selected < m_defaultResolution)
                    {
                        void (*data)() = j_00048a4a;
                        union MethodBits { unsigned int words[2]; FunctorMethod member; } method;
                        method.words[0] = (unsigned int)data; method.words[1] = 0;
                        bfmeSendZB((void *)1, &TheGameText->fetch("APT:Warning"), &TheGameText->fetch("APT:DetailTooHigh"), BfmeTagZB(FunctorBinding(method.member, (FunctorTarget *)this)));
                    }
                    else if (m_comboDetail) m_defaultResolution = bfmeGo1022L((int)m_comboDetail);
                }
            }
            if (selected != 5)
            {
                if (selected == 4 || selected == 3)
                    goto disableDetailChecks;
                if (selected == 2 || selected == 1 || selected == 0)
                {
                    if (m_checkHealthBars) m_checkHealthBars->winEnable(true);
                    if (m_checkUnitDecals) m_checkUnitDecals->winEnable(true);
                }
                goto consumed;
disableDetailChecks:
                if (m_checkHealthBars) { GadgetCheckBoxSetChecked(m_checkHealthBars, true); m_checkHealthBars->winEnable(false); }
                if (m_checkUnitDecals) { GadgetCheckBoxSetChecked(m_checkUnitDecals, false); m_checkUnitDecals->winEnable(false); }
            }
            else ((BfmeA1051 *)this)->bfmeGo1051A();
        }
        goto consumed;
    }
    case 0x4010:

    {
        if (!g_Va012F4AE4 || m_audioSample == 2)
            goto unhandledMessage;
        TheAudioClientUpdate->stopAudioEvent((unsigned int)g_Va012F4AE4);
        g_Va012F4AE4 = 0;
        clearAudioState();
unhandledMessage:
        return handled;
    }
    case 0x400C:
    {
    if (control == m_sliderBrightness)
    {
        int value = (int)data;
        if (value != -1)
        {
            float gamma = 1.0f;
            if (value < 50)
                gamma = value <= 0 ? 0.6f : 1.0f - (float)(50 - value) * 0.008f;
            else if (value > 50)
                gamma = 1.0f + (float)(value - 50) * 0.02f;
            TheDisplay->setGamma(gamma, 0.0f, 1.0f, false);
        }
        goto consumed;
    }

    if (control == m_sliderMusic)
    {
        if ((int)data != -1)
        {
            TheAudioClientUpdate->setMusicVolume((float)(int)data * 0.01f);
            {
    if (this->m_audioSample != 0)
    {
        TheAudioClientUpdate->stopAudioEvent((unsigned int)g_Va012F4AE4);
        g_Va012F4AE4 = 0;
    }
    if (!TheAudioClientUpdate->slot44((unsigned int)g_Va012F4AE4))
    {
        if (this->m_audioSample != 0)
        {
            if (0 != 1) { g_optFlag12F4AD8 = 0; g_optFlag12F4AD9 = 0; }
            if (0 != 2) { g_optFlag12F4ADA = 0; g_optFlag12F4ADB = 0; }
            if (0 != 3) { g_optFlag12F4ADC = 0; g_optFlag12F4ADD = 0; }
            if (0 != 4) { g_optFlag12F4ADE = 0; g_optFlag12F4ADF = 0; }
            if (0 != 0) { g_optFlag12F4AE0 = 0; g_optFlag12F4AE1 = 0; }
        }
        if (!g_optFlag12F4AE1)
        {
            if (!g_optFlag12F4AE0)
            {
                if (0 != 0 || (TheBfmeGameLogic && !((unsigned char)((Rva0005C5E0 *)TheBfmeGameLogic)->isEither()) && !g_optByte12F4AD0))
                {
                    AudioEventRTS event(BFMERetailAsciiString("VolumeSampleMusic"), 2);
                    if (0 == 0 || 0 == 4)
                        g_Va012F4AE4 = (void *)TheAudioClientUpdate->slot22(&event);
                    else
                        g_Va012F4AE4 = (void *)TheAudioClientUpdate->slot17(&event);
                    g_optFlag12F4AE1 = 1;
                }
            }
        }
        else
        {
            if (g_optFlag12F4AE0) { g_optFlag12F4AE1 = 0; g_Va012F4AE4 = 0; }
            g_optFlag12F4AE0 = 0;
        }
    }
    else g_optFlag12F4AE0 = 1;
    this->m_audioSample = 0;
}
        }
        goto consumed;
    }
    if (control == m_sliderSfx)
    {
        if ((int)data != -1)
        {
            TheAudioClientUpdate->setSoundFXVolume((float)(int)data * 0.01f);
            {
    if (this->m_audioSample != 1)
    {
        TheAudioClientUpdate->stopAudioEvent((unsigned int)g_Va012F4AE4);
        g_Va012F4AE4 = 0;
    }
    if (!TheAudioClientUpdate->slot44((unsigned int)g_Va012F4AE4))
    {
        if (this->m_audioSample != 1)
        {
            if (1 != 1) { g_optFlag12F4AD8 = 0; g_optFlag12F4AD9 = 0; }
            if (1 != 2) { g_optFlag12F4ADA = 0; g_optFlag12F4ADB = 0; }
            if (1 != 3) { g_optFlag12F4ADC = 0; g_optFlag12F4ADD = 0; }
            if (1 != 4) { g_optFlag12F4ADE = 0; g_optFlag12F4ADF = 0; }
            if (1 != 0) { g_optFlag12F4AE0 = 0; g_optFlag12F4AE1 = 0; }
        }
        if (!g_optFlag12F4AD9)
        {
            if (!g_optFlag12F4AD8)
            {
                if (1 != 0 || (TheBfmeGameLogic && !((unsigned char)((Rva0005C5E0 *)TheBfmeGameLogic)->isEither()) && !g_optByte12F4AD0))
                {
                    AudioEventRTS event(BFMERetailAsciiString("VolumeSampleSoundFX"), 2);
                    if (1 == 0 || 1 == 4)
                        g_Va012F4AE4 = (void *)TheAudioClientUpdate->slot22(&event);
                    else
                        g_Va012F4AE4 = (void *)TheAudioClientUpdate->slot17(&event);
                    g_optFlag12F4AD9 = 1;
                }
            }
        }
        else
        {
            if (g_optFlag12F4AD8) { g_optFlag12F4AD9 = 0; g_Va012F4AE4 = 0; }
            g_optFlag12F4AD8 = 0;
        }
    }
    else g_optFlag12F4AD8 = 1;
    this->m_audioSample = 1;
}
        }
        goto consumed;
    }
    if (control == m_sliderVoice)
    {
        if ((int)data != -1)
        {
            TheAudioClientUpdate->setVoiceVolume((float)(int)data * 0.01f);
            {
    if (this->m_audioSample != 2)
    {
        TheAudioClientUpdate->stopAudioEvent((unsigned int)g_Va012F4AE4);
        g_Va012F4AE4 = 0;
    }
    if (!TheAudioClientUpdate->slot44((unsigned int)g_Va012F4AE4))
    {
        if (this->m_audioSample != 2)
        {
            if (2 != 1) { g_optFlag12F4AD8 = 0; g_optFlag12F4AD9 = 0; }
            if (2 != 2) { g_optFlag12F4ADA = 0; g_optFlag12F4ADB = 0; }
            if (2 != 3) { g_optFlag12F4ADC = 0; g_optFlag12F4ADD = 0; }
            if (2 != 4) { g_optFlag12F4ADE = 0; g_optFlag12F4ADF = 0; }
            if (2 != 0) { g_optFlag12F4AE0 = 0; g_optFlag12F4AE1 = 0; }
        }
        if (!g_optFlag12F4ADB)
        {
            if (!g_optFlag12F4ADA)
            {
                if (2 != 0 || (TheBfmeGameLogic && !((unsigned char)((Rva0005C5E0 *)TheBfmeGameLogic)->isEither()) && !g_optByte12F4AD0))
                {
                    AudioEventRTS event(BFMERetailAsciiString("VolumeSampleVoice"), 2);
                    if (2 == 0 || 2 == 4)
                        g_Va012F4AE4 = (void *)TheAudioClientUpdate->slot22(&event);
                    else
                        g_Va012F4AE4 = (void *)TheAudioClientUpdate->slot17(&event);
                    g_optFlag12F4ADB = 1;
                }
            }
        }
        else
        {
            if (g_optFlag12F4ADA) { g_optFlag12F4ADB = 0; g_Va012F4AE4 = 0; }
            g_optFlag12F4ADA = 0;
        }
    }
    else g_optFlag12F4ADA = 1;
    this->m_audioSample = 2;
}
        }
        goto consumed;
    }
    if (control == m_sliderAmbient)
    {
        if ((int)data != -1)
        {
            TheAudioClientUpdate->setAmbientVolume((float)(int)data * 0.01f);
            {
    if (this->m_audioSample != 3)
    {
        TheAudioClientUpdate->stopAudioEvent((unsigned int)g_Va012F4AE4);
        g_Va012F4AE4 = 0;
    }
    if (!TheAudioClientUpdate->slot44((unsigned int)g_Va012F4AE4))
    {
        if (this->m_audioSample != 3)
        {
            if (3 != 1) { g_optFlag12F4AD8 = 0; g_optFlag12F4AD9 = 0; }
            if (3 != 2) { g_optFlag12F4ADA = 0; g_optFlag12F4ADB = 0; }
            if (3 != 3) { g_optFlag12F4ADC = 0; g_optFlag12F4ADD = 0; }
            if (3 != 4) { g_optFlag12F4ADE = 0; g_optFlag12F4ADF = 0; }
            if (3 != 0) { g_optFlag12F4AE0 = 0; g_optFlag12F4AE1 = 0; }
        }
        if (!g_optFlag12F4ADD)
        {
            if (!g_optFlag12F4ADC)
            {
                if (3 != 0 || (TheBfmeGameLogic && !((unsigned char)((Rva0005C5E0 *)TheBfmeGameLogic)->isEither()) && !g_optByte12F4AD0))
                {
                    AudioEventRTS event(BFMERetailAsciiString("VolumeSampleAmbient"), 2);
                    if (3 == 0 || 3 == 4)
                        g_Va012F4AE4 = (void *)TheAudioClientUpdate->slot22(&event);
                    else
                        g_Va012F4AE4 = (void *)TheAudioClientUpdate->slot17(&event);
                    g_optFlag12F4ADD = 1;
                }
            }
        }
        else
        {
            if (g_optFlag12F4ADC) { g_optFlag12F4ADD = 0; g_Va012F4AE4 = 0; }
            g_optFlag12F4ADC = 0;
        }
    }
    else g_optFlag12F4ADC = 1;
    this->m_audioSample = 3;
}
        }
        goto consumed;
    }
    if (control == m_sliderMovie)
    {
        if ((int)data != -1)
        {
            TheAudioClientUpdate->setMovieVolume((float)(int)data * 0.01f);
            {
    if (this->m_audioSample != 4)
    {
        TheAudioClientUpdate->stopAudioEvent((unsigned int)g_Va012F4AE4);
        g_Va012F4AE4 = 0;
    }
    if (!TheAudioClientUpdate->slot44((unsigned int)g_Va012F4AE4))
    {
        if (this->m_audioSample != 4)
        {
            if (4 != 1) { g_optFlag12F4AD8 = 0; g_optFlag12F4AD9 = 0; }
            if (4 != 2) { g_optFlag12F4ADA = 0; g_optFlag12F4ADB = 0; }
            if (4 != 3) { g_optFlag12F4ADC = 0; g_optFlag12F4ADD = 0; }
            if (4 != 4) { g_optFlag12F4ADE = 0; g_optFlag12F4ADF = 0; }
            if (4 != 0) { g_optFlag12F4AE0 = 0; g_optFlag12F4AE1 = 0; }
        }
        if (!g_optFlag12F4ADF)
        {
            if (!g_optFlag12F4ADE)
            {
                if (4 != 0 || (TheBfmeGameLogic && !((unsigned char)((Rva0005C5E0 *)TheBfmeGameLogic)->isEither()) && !g_optByte12F4AD0))
                {
                    AudioEventRTS event(BFMERetailAsciiString("VolumeSampleMovie"), 2);
                    if (4 == 0 || 4 == 4)
                        g_Va012F4AE4 = (void *)TheAudioClientUpdate->slot22(&event);
                    else
                        g_Va012F4AE4 = (void *)TheAudioClientUpdate->slot17(&event);
                    g_optFlag12F4ADF = 1;
                }
            }
        }
        else
        {
            if (g_optFlag12F4ADE) { g_optFlag12F4ADF = 0; g_Va012F4AE4 = 0; }
            g_optFlag12F4ADE = 0;
        }
    }
    else g_optFlag12F4ADE = 1;
    this->m_audioSample = 4;
}
        }
        goto consumed;
    }
    goto consumed;
    }
    default:
        goto unhandledMessage;
    }
consumed:
    return 1;
}
