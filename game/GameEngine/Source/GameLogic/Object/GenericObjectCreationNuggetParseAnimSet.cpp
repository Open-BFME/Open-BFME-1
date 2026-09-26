// cl: /EHsc
// stlport
// Open-BFME: BFME2 GenericObjectCreationNugget::parseAnimSet reconstruction.
// The retail AnimSet is three inline AsciiString objects (12 bytes total).

#include <vector>

template <typename T>
class StringBase
{
    friend class AsciiString;

public:
    void set(const StringBase<T> &source);

private:
    StringBase(const StringBase<T> &source);
    void releaseBuffer();
    void *m_data;
};

class AsciiString
{
public:
    AsciiString() : m_text(0) {}

    AsciiString(const AsciiString &source)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(
            *(const StringBase<char> *)&source);
    }

    ~AsciiString()
    {
        ((StringBase<char> *)this)->releaseBuffer();
    }

    AsciiString &operator=(const AsciiString &source)
    {
        ((StringBase<char> *)this)->set(*(const StringBase<char> *)&source);
        return *this;
    }

private:
    void *m_text;
};

class INI
{
public:
    AsciiString getNextAsciiString();
};

struct Gen_t_001da8b0_p12cd
{
    Gen_t_001da8b0_p12cd() {}
    Gen_t_001da8b0_p12cd(const Gen_t_001da8b0_p12cd &source);
    ~Gen_t_001da8b0_p12cd();

    AsciiString m_animInitial;
    AsciiString m_animFlying;
    AsciiString m_animFinal;
};

class GenericObjectCreationNugget
{
public:
    typedef Gen_t_001da8b0_p12cd AnimSet;

    static void parseAnimSet(INI *ini, void *instance, void *store,
                             const void *userData);
};

void GenericObjectCreationNugget::parseAnimSet(INI *ini, void *, void *store,
                                               const void *)
{
    AnimSet anim;
    anim.m_animInitial = ini->getNextAsciiString();
    anim.m_animFlying = ini->getNextAsciiString();
    anim.m_animFinal = ini->getNextAsciiString();
    ((std::vector<AnimSet> *)store)->push_back(anim);
}
