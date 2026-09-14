// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

typedef float Real;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct FieldParse;

template <typename T>
class StringBase
{
    friend class AsciiString;

public:
    StringBase()
        : m_data(0)
    {
    }

    StringBase(const StringBase<T> &source);
    void set(const StringBase<T> &source);
    StringBase<T> &operator=(const StringBase<T> &source)
    {
        set(source);
        return *this;
    }
    void toLower();
    Bool isNone() const;

private:
    void releaseBuffer();

public:

    struct Header
    {
        int refCount;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    Header *m_data;
};

class AsciiString
    : public StringBase<char>
{
public:
    AsciiString(const AsciiString &source) :
        StringBase<char>(*(const StringBase<char> *)&source)
    {
    }

    ~AsciiString()
    {
        ((StringBase<char> *)this)->releaseBuffer();
    }

    void toLower()
    {
        ((StringBase<char> *)this)->toLower();
    }

    void set(const AsciiString &source)
    {
        ((StringBase<char> *)this)->set(
            *(const StringBase<char> *)&source);
    }

    Bool isNone() const
    {
        return ((const StringBase<char> *)this)->isNone();
    }
};

class INI
{
public:
    AsciiString getNextAsciiString();
    void initFromINI(void *instance, const FieldParse *fieldParse);
};

class Gen_uw_000448d2
{
public:
    ~Gen_uw_000448d2();
};

struct AnimationMode
{
    AnimationMode()
        : m_bits(1.40129846e-45f)
    {
    }

    union
    {
        int m_value;
        float m_bits;
    };
};

struct Rva00774090Element : public StringBase<char>
{
public:
    __forceinline Rva00774090Element(const AsciiString &source) :
        StringBase<char>(*(const StringBase<char> *)&source),
        m_secondName(),
        m_animationName(),
        m_distance(0),
        m_unknown(-1.0f),
        m_mode(),
        m_blendTime(5.0f),
        m_speedFactorMin(1.0f),
        m_speedFactorMax(1.0f),
        m_mustCompleteBlend(false),
        m_useWeaponTiming(false),
        m_priority(1),
        m_fadeBeginFrame(-1.0f),
        m_fadeEndFrame(-1.0f),
        m_fadingIn(false)
    {
    }

    ~Rva00774090Element()
    {
        ((Gen_uw_000448d2 *)this)->~Gen_uw_000448d2();
    }

    StringBase<char> m_secondName;
    StringBase<char> m_animationName;
    int m_distance;
    Real m_unknown;
    AnimationMode m_mode;
    Real m_blendTime;
    Real m_speedFactorMin;
    Real m_speedFactorMax;
    Bool m_mustCompleteBlend;
    Bool m_useWeaponTiming;
    int m_priority;
    Real m_fadeBeginFrame;
    Real m_fadeEndFrame;
    Bool m_fadingIn;
};

namespace _STL
{
template <typename T>
class allocator;

template <typename T, typename Allocator>
class vector
{
public:
    void push_back(const T *value);
};
}

__declspec(noinline) static void parseAnimation(INI *ini, void *instance, void *store, const void *userData)
{
    AsciiString animationName = ini->getNextAsciiString();
    AsciiString originalAnimationName = animationName;

    animationName.toLower();
    Rva00774090Element animation(animationName);

    animation.m_secondName =
        *(const StringBase<char> *)&originalAnimationName;
    if ((UnsignedInt)userData == 1)
        animation.m_mode.m_bits = 2.80259693e-45f;
    ini->initFromINI(&animation, (const FieldParse *)0x011240A0);

    if (animation.m_priority < 0)
        animation.m_priority = 0;
    else if (animation.m_priority > 100)
        animation.m_priority = 100;

    if (animation.m_animationName.m_data != 0 &&
        animation.m_animationName.m_data->length != 0 &&
        animation.m_animationName.isNone() == false)
        ((_STL::vector<Rva00774090Element, _STL::allocator<Rva00774090Element> > *)
            ((char *)instance + 0x2c))->push_back(&animation);
}

void (*volatile g_parseAnimationAnchor)(INI *, void *, void *, const void *) = parseAnimation;
