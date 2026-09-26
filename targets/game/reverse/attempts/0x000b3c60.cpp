// ?d_000b3c60@@YAXXZ
// partial score=0.49 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc
// AudioEventRTS::generatePlayInfo, retail 0x000B3C60, 664 bytes.

typedef int Int;
typedef bool Bool;

extern int GetGameLogicRandomValue(int, int, char *, int);
extern int GetGameAudioRandomValue(int, int, char *, int);
extern void j_000053ad(void);
extern float GetGameAudioRandomValueReal(float, float, char *, int);
extern float g_bfmeDefaultBU;
extern void j_000067d5(void);
extern void j_0002b8eb(void);
extern void j_0002704d(void);
extern void j_0002dfb5(void);
extern void j_0003b769(void);
extern "C" void _WriteBarrier();
#pragma intrinsic(_WriteBarrier)

typedef float (__cdecl *RandomRealFunction)(float, float, char *, int);

static __forceinline float callRandomReal(
    float low, float high, char *file, int line)
{
    union
    {
        void (*function)(void);
        RandomRealFunction typed;
    } thunk;
    thunk.function = j_000053ad;
    return thunk.typed(low, high, file, line);
}

template <typename T> class StringBase;
class AsciiString;

template <typename T>
class StringBase
{
    friend class AsciiString;

protected:
    struct Data
    {
        int refCount;
        unsigned short length;
        unsigned short capacity;
        T text[1];
    };

    StringBase() : m_data(0) {}
    StringBase(const StringBase<T> &other);
    ~StringBase();

private:
    void set(const StringBase<T> &other);
    void releaseBuffer();

public:
    void concat(const T *text, Int length);

    Data *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}

    AsciiString &operator=(const AsciiString &other)
    {
        StringBase<char>::set(other);
        return *this;
    }

    void concat(const char *text, Int length)
    {
        StringBase<char>::concat(text, length);
    }

    void concat(const AsciiString &other)
    {
        const Data *data = other.m_data;
        const Int length = data ? data->length : 0;
        const char *text = data ? &data->text[0] : "";
        StringBase<char>::concat(text, length);
    }

    void concatPeek(const AsciiString &other)
    {
        const Data *data = other.m_data;
        const Int length = data ? data->length : 0;
        const char *text = data ? &data->text[0] : "";
        StringBase<char>::concat(text, length);
    }
};

struct WeightedSoundB2430
{
    AsciiString m_filename;
    unsigned m_weight;
};

struct WeightedSoundRangeB2430
{
    WeightedSoundB2430 *m_begin;
    WeightedSoundB2430 *m_end;
    WeightedSoundB2430 *m_capacity;
};

static __declspec(noinline) int bfmeWeightedChoiceB2430(
    unsigned count, const WeightedSoundRangeB2430 *range, Bool logical)
{
    if (!(count > 0))
        return -1;

    unsigned value;
    --count;
    if (logical)
        value = GetGameLogicRandomValue(0, count,
            "F:\\bfme\\Code\\gameengine\\Source\\Common\\Audio\\AudioEventRTS.cpp",
            55);
    else
        value = GetGameAudioRandomValue(0, count,
            "F:\\bfme\\Code\\gameengine\\Source\\Common\\Audio\\AudioEventRTS.cpp",
            59);

    WeightedSoundB2430 *it = range->m_begin;
    if (it != range->m_end)
    {
        do
        {
            if (value < it->m_weight)
                goto found;
            value -= it->m_weight;
            ++it;
        }
        while (it != range->m_end);
        return 0;
    }

found:
    if (it == range->m_end)
    {
        _WriteBarrier();
        return 0;
    }
    return (int)(it - range->m_begin);
}

enum AudioType
{
    AT_Music = 0,
    AT_Streaming = 1,
    AT_SoundEffect = 2,
    AT_AmbientStream = 3,
    AT_SoundEffectAlt = 4
};

class AudioEventInfo
{
public:
    char m_pad00[0x14];
    volatile float m_volumeShift;
    char m_pad18[4];
    float m_pitchShiftMin;
    float m_pitchShiftMax;
    char m_pad24[0x50 - 0x24];
    WeightedSoundRangeB2430 m_attackSounds;
    unsigned m_attackTotalWeight;
    WeightedSoundRangeB2430 m_decaySounds;
    unsigned m_decayTotalWeight;
    char m_pad70[0x84 - 0x70];
    AudioType m_soundType;
};

class AudioEventRTS
{
public:
    void generatePlayInfo();

private:
    char m_pad00[4];
    AsciiString m_filenameToLoad;
    AudioEventInfo *m_eventInfo;
    char m_pad0C[0x18 - 0x0C];
    AsciiString m_attackName;
    AsciiString m_decayName;
    char m_pad24[0x42 - 0x20];
    Bool m_isLogicalAudio;
    char m_pad43[0x4C - 0x43];
    float m_pitchShift;
    float m_volumeShift;
    char m_pad54[0x60 - 0x54];
    int m_portionToPlayNext;
};

void AudioEventRTS::generatePlayInfo()
{
    m_pitchShift = callRandomReal(
        m_eventInfo->m_pitchShiftMin,
        m_eventInfo->m_pitchShiftMax,
        "F:\\bfme\\Code\\gameengine\\Source\\Common\\Audio\\AudioEventRTS.cpp",
        641);
    m_volumeShift = GetGameAudioRandomValueReal(
        m_eventInfo->m_volumeShift + g_bfmeDefaultBU,
        1.0f,
        "F:\\bfme\\Code\\gameengine\\Source\\Common\\Audio\\AudioEventRTS.cpp",
        642);

    typedef WeightedSoundRangeB2430 *(AudioEventInfo::*RangeThunk)(void);
    union
    {
        void (*function)(void);
        RangeThunk member;
    } rangeThunk;

    rangeThunk.function = j_0002b8eb;
    if (m_eventInfo->m_soundType == AT_SoundEffect)
    {
        m_portionToPlayNext = 0;
        unsigned attackTotalWeight = m_eventInfo->m_attackTotalWeight;
        WeightedSoundRangeB2430 *attackRange =
            (m_eventInfo->*rangeThunk.member)();
        Int attack = bfmeWeightedChoiceB2430(
            attackTotalWeight, attackRange, m_isLogicalAudio);
        if (attack >= 0)
        {
            typedef AsciiString (AudioEventRTS::*PrefixThunk)(AudioType, Bool);
            union
            {
                void (*function)(void);
                PrefixThunk member;
            } prefixThunk;
            prefixThunk.function = j_0003b769;
            m_attackName = (this->*prefixThunk.member)(
                m_eventInfo->m_soundType, false);

            attackRange = (m_eventInfo->*rangeThunk.member)();
            m_attackName.concatPeek(attackRange->m_begin[attack].m_filename);

            typedef AsciiString (AudioEventRTS::*ExtensionThunk)(AudioType);
            union
            {
                void (*function)(void);
                ExtensionThunk member;
            } extensionThunk;
            extensionThunk.function = j_000067d5;
            m_attackName.concatPeek((this->*extensionThunk.member)(
                m_eventInfo->m_soundType));

            typedef void (AudioEventRTS::*AdjustThunk)(AsciiString &);
            union
            {
                void (*function)(void);
                AdjustThunk member;
            } adjustThunk;
            adjustThunk.function = j_0002dfb5;
            (this->*adjustThunk.member)(m_attackName);
        }
        else
        {
            m_portionToPlayNext = 1;
        }

        rangeThunk.function = j_0002704d;
        unsigned decayTotalWeight = m_eventInfo->m_decayTotalWeight;
        WeightedSoundRangeB2430 *decayRange =
            (m_eventInfo->*rangeThunk.member)();
        Int decay = bfmeWeightedChoiceB2430(
            decayTotalWeight, decayRange, m_isLogicalAudio);
        if (decay >= 0)
        {
            typedef AsciiString (AudioEventRTS::*PrefixThunk)(AudioType, Bool);
            union
            {
                void (*function)(void);
                PrefixThunk member;
            } prefixThunk;
            prefixThunk.function = j_0003b769;
            m_decayName = (this->*prefixThunk.member)(
                m_eventInfo->m_soundType, false);

            decayRange = (m_eventInfo->*rangeThunk.member)();
            m_decayName.concatPeek(decayRange->m_begin[decay].m_filename);

            typedef AsciiString (AudioEventRTS::*ExtensionThunk)(AudioType);
            union
            {
                void (*function)(void);
                ExtensionThunk member;
            } extensionThunk;
            extensionThunk.function = j_000067d5;
            m_decayName.concatPeek((this->*extensionThunk.member)(
                m_eventInfo->m_soundType));

            typedef void (AudioEventRTS::*AdjustThunk)(AsciiString &);
            union
            {
                void (*function)(void);
                AdjustThunk member;
            } adjustThunk;
            adjustThunk.function = j_0002dfb5;
            (this->*adjustThunk.member)(m_decayName);
        }
        else
        {
            m_decayName.~AsciiString();
        }
    }
    else
    {
        m_portionToPlayNext = 1;
    }

    m_isLogicalAudio = false;
}
