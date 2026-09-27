// ?_bfme_checkMsg@BfmeAptScreenOptions@@QAEHHPAX0@Z
// partial score=0.632 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BfmeAptScreenOptions message handler, retail 0x0055F290, 2771-byte body.
// The ledger extent includes the switch table and trailing INT3 bytes.

template <typename T> class StringBase
{
    friend class BFMERetailAsciiString;
    friend class UnicodeString;

public:
    StringBase() : m_data(0) {}
    StringBase(const T *text);
    StringBase(const StringBase<T> &other);
    ~StringBase();
    void releaseBuffer();
    void *m_data;
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
    BFMERetailAsciiString() : StringBase<char>() {}
    BFMERetailAsciiString(const char *text) : StringBase<char>(text) {}
    BFMERetailAsciiString(const BFMERetailAsciiString &other)
        : StringBase<char>(other) {}
    ~BFMERetailAsciiString() { releaseBuffer(); }
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    UnicodeString() : StringBase<unsigned short>() {}
    UnicodeString(const UnicodeString &other)
        : StringBase<unsigned short>(other) {}
    ~UnicodeString() { releaseBuffer(); }
};

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

struct FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);

struct FunctorBinding
{
    FunctorBinding(FunctorMethod method, FunctorTarget *target)
        : m_target(target), m_unmodelled(0), m_method(method) {}

    FunctorTarget *m_target;
    unsigned int m_unmodelled;
    FunctorMethod m_method;
};

class Rva0055F220FunctorHolder
{
public:
    Rva0055F220FunctorHolder(FunctorBinding binding);
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
    virtual void *slot17(const AudioEventRTS *event);
    virtual void slot18();
    virtual void slot19();
    virtual void stopAudioEvent(void *handle);
    virtual void slot21();
    virtual void *slot22(const AudioEventRTS *event);
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
    virtual bool slot44(void *handle);
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void setSoundFXVolume(float value);
    virtual void setVoiceVolume(float value);
    virtual void setMusicVolume(float value);
    virtual void setMovieVolume(float value);
    virtual void setAmbientVolume(float value);
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

extern Rva0005C5E0 *TheBfmeGameLogic;

class BfmeAptScreenOptions
{
public:
    int _bfme_checkMsg(int msg, void *data, void *control);

public:
    char m_pad000[0x258];
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
    bool m_flag308;
    char m_pad309[3];
    int m_defaultResolution;
};

static __forceinline void clearAudioState()
{
    *(unsigned char *)0x012F4AD8 = 0;
    *(unsigned char *)0x012F4AD9 = 0;
    *(unsigned char *)0x012F4ADA = 0;
    *(unsigned char *)0x012F4ADB = 0;
    *(unsigned char *)0x012F4ADC = 0;
    *(unsigned char *)0x012F4ADD = 0;
    *(unsigned char *)0x012F4ADE = 0;
    *(unsigned char *)0x012F4ADF = 0;
    *(unsigned char *)0x012F4AE0 = 0;
    *(unsigned char *)0x012F4AE1 = 0;
}

static __forceinline void stopPreviewIfNeeded(BfmeAptScreenOptions *self)
{
    void *handle = *(void **)0x012F4AE4;
    if (handle == 0 || self->m_audioSample == 2)
        return;

    TheAudioClientUpdate->stopAudioEvent(handle);
    *(void **)0x012F4AE4 = 0;
    clearAudioState();
}

class AudioEventRTS
{
public:
    AudioEventRTS(const BFMERetailAsciiString &eventName, int owner);
    virtual ~AudioEventRTS();
    char m_storage[0x6c];
};

static __forceinline void startPreview(BfmeAptScreenOptions *self, int sample, const char *name,
    int flag)
{
    if (self->m_audioSample == sample)
        return;

    void *handle = *(void **)0x012F4AE4;
    if (handle)
        TheAudioClientUpdate->stopAudioEvent(handle);
    *(void **)0x012F4AE4 = 0;

    if (TheAudioClientUpdate->slot44(0))
    {
        *(unsigned char *)(0x012F4AD8 + sample) = 1;
        return;
    }

    clearAudioState();
    if (*(unsigned char *)(0x012F4AD8 + sample) == 0)
    {
        BFMERetailAsciiString eventName(name);
        AudioEventRTS event(eventName, flag);
        if (sample == 0)
            *(void **)0x012F4AE4 = TheAudioClientUpdate->slot22(&event);
        else
            *(void **)0x012F4AE4 = TheAudioClientUpdate->slot17(&event);
        *(unsigned char *)(0x012F4AD8 + sample) = 1;
        *(unsigned char *)(0x012F4AE1 + (flag & 0)) = 1;
    }
    self->m_audioSample = sample;
}

class Rva00579160Manager;
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
    if (msg == 0x4008)
    {
        if (control == m_checkEAX3)
        {
            bool checked = GadgetCheckBoxIsChecked((GameWindow *)control);
        if (checked)
        {
            if (TheAudioClientUpdate->slot44((void *)checked))
                return 1;
            if (TheBfmeGameLogic && !TheBfmeGameLogic->isEither())
            {
                BFMERetailAsciiString title("APT:Warning");
                BFMERetailAsciiString message("Eax3NotSupported");
                GadgetCheckBoxSetChecked(m_checkEAX3, false);
                bfmeSendZB((void *)m_page, &title, &message, BfmeTagZB());
            }
        }
        return 1;
    }
    }
    if (msg == 0x4006 || msg == 0x4007 || msg == 0x4017)
        return 1;
    if (msg == 0x4010)
    {
        stopPreviewIfNeeded(this);
        return handled;
    }
    if (msg == 0x4025)
    {
        if (control == m_comboDetail)
        {
            int selected;
            GadgetComboBoxGetSelectedPos(m_comboDetail, &selected);
            int current = TheGameLODManager->m_currentDetail;
            if (selected < 0 && selected != m_defaultResolution
                && current != 3)
            {
                union MethodBits
                {
                    unsigned int words[2];
                    FunctorMethod member;
                } method;
                method.words[0] = (unsigned int)data;
                method.words[1] = 0;
                FunctorBinding binding(method.member, (FunctorTarget *)this);
                Rva0055F220FunctorHolder holder(binding);
                UnicodeString title = TheGameText->fetch("APT:DetailTooHigh");
                UnicodeString warning = TheGameText->fetch("APT:Warning");
                bfmeSendZB((void *)1, &warning, &title, BfmeTagZB());
            }
            m_defaultResolution = bfmeGo1022L((int)m_comboDetail);
        }
        return 1;
    }
    if (msg != 0x400C)
        return handled;

volume_message:
    if (control == m_sliderBrightness)
    {
        int value = (int)data;
        if (value != -1)
        {
            float gamma = 1.0f;
            if (value < 50)
                gamma = value <= 0 ? 0.6f : 1.0f - 0.4f * (float)(50 - value) / 50.0f;
            else if (value > 50)
                gamma = 1.0f + (float)(value - 50) / 50.0f;
            TheDisplay->setGamma(gamma, 0.0f, 1.0f, false);
        }
        return 1;
    }

    if (control == m_sliderMusic)
    {
        if ((int)data != -1)
        {
            TheAudioClientUpdate->setMusicVolume((float)(int)data * 0.01f);
            startPreview(this, 0, "VolumeSampleMusic", 2);
        }
        return 1;
    }
    if (control == m_sliderSfx)
    {
        if ((int)data != -1)
        {
            TheAudioClientUpdate->setSoundFXVolume((float)(int)data * 0.01f);
            startPreview(this, 1, "VolumeSampleSoundFX", 2);
        }
        return 1;
    }
    if (control == m_sliderVoice)
    {
        if ((int)data != -1)
        {
            TheAudioClientUpdate->setVoiceVolume((float)(int)data * 0.01f);
            startPreview(this, 2, "VolumeSampleVoice", 2);
        }
        return 1;
    }
    if (control == m_sliderAmbient)
    {
        if ((int)data != -1)
        {
            TheAudioClientUpdate->setAmbientVolume((float)(int)data * 0.01f);
            startPreview(this, 3, "VolumeSampleAmbient", 2);
        }
        return 1;
    }
    if (control == m_sliderMovie)
    {
        if ((int)data != -1)
        {
            TheAudioClientUpdate->setMovieVolume((float)(int)data * 0.01f);
            startPreview(this, 4, "VolumeSampleMovie", 2);
        }
        return 1;
    }
    return handled;
}
