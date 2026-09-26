// cl: /EHsc
// Open-BFME: the BFME2 three-string AnimSet copy constructor and destructor.

template <typename T>
class StringBase
{
    friend class AsciiString;

private:
    StringBase(const StringBase<T> &source);
    void releaseBuffer();
    void *m_data;
};

class AsciiString
{
public:
    AsciiString(const AsciiString &source)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(
            *(const StringBase<char> *)&source);
    }

    ~AsciiString()
    {
        ((StringBase<char> *)this)->releaseBuffer();
    }

private:
    void *m_text;
};

class GenericObjectCreationNugget
{
public:
    struct AnimSet
    {
        AnimSet(const AnimSet &source);
        ~AnimSet();

        AsciiString m_animInitial;
        AsciiString m_animFlying;
        AsciiString m_animFinal;
    };
};

GenericObjectCreationNugget::AnimSet::AnimSet(const AnimSet &source)
    : m_animInitial(source.m_animInitial),
      m_animFlying(source.m_animFlying),
      m_animFinal(source.m_animFinal)
{
}

GenericObjectCreationNugget::AnimSet::~AnimSet()
{
}
