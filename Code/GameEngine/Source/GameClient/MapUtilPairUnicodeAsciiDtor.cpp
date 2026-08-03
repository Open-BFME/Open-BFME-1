// cl: /DNDEBUG /MD /EHsc

class UnicodeString
{
public:
    ~UnicodeString() { releaseBuffer(); }

protected:
    void releaseBuffer();

private:
    void *m_data;
};

class AsciiString
{
public:
    ~AsciiString() { freeBytes(); }

private:
    void freeBytes();

private:
    void *m_data;
};

namespace _STL
{
template <class First, class Second>
class pair
{
public:
    First first;
    Second second;

    ~pair();
};

template <class First, class Second>
pair<First, Second>::~pair()
{
}
}

typedef _STL::pair<const UnicodeString, AsciiString> UnicodeAsciiPair;
template UnicodeAsciiPair::~UnicodeAsciiPair();
