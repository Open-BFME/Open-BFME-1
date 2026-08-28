// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: preserve the retail payload layout and STLPort growth path.

extern "C" unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strlen)

inline void *__cdecl operator new(unsigned int, void *place)
{
    return place;
}

inline void __cdecl operator delete(void *, void *)
{
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
    const char *getNextToken(const char *separators);
    const char *getNextTokenOrNull(const char *separators);
    static int scanInt(const char *text);
};

class AsciiString;

template <typename T>
class StringBase
{
    T *m_text;

    friend class AsciiString;
    StringBase(const StringBase<T> &that);

public:
    void set(const T *text, int length);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
    char *m_text;

public:
    AsciiString() { m_text = 0; }
    AsciiString(const AsciiString &that)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(
            *(const StringBase<char> *)&that);
    }
    ~AsciiString();
    void set(const char *text)
    {
        ((StringBase<char> *)this)->set(text, text ? strlen(text) : 0);
    }
};

namespace _STL
{
struct __false_type
{
};

template <typename Destination, typename Source>
__declspec(noinline) void _Construct(Destination *place, const Source &value)
{
    new (place) Destination(value);
}

template <typename T>
class allocator
{
};

template <typename T, typename Allocator>
class vector
{
    T *m_start;
    T *m_finish;
    T *m_end;

protected:
    void _M_insert_overflow(T *position, const T &value,
                            const __false_type &, unsigned int count,
                            bool atEnd);

public:
    void push_back(const T &value)
    {
        T *end = m_end;
        T *finish = m_finish;
        if (finish != end)
        {
            _Construct(finish, value);
            ++m_finish;
        }
        else
        {
            __false_type tag;
            _M_insert_overflow(finish, value, tag, 1, true);
        }
    }
};
}

class DeliverPayloadNugget
{
public:
    struct Payload
    {
        AsciiString m_payloadName;
        int m_payloadCount;

        Payload() {}
    };

    static void __cdecl parsePayload(INI *ini, void *instance, void *,
                                     const void *);

private:
    char m_beforePayload[0x1c];
    _STL::vector<Payload, _STL::allocator<Payload> > m_payload;
};

void __cdecl DeliverPayloadNugget::parsePayload(INI *ini, void *instance,
                                                 void *, const void *)
{
    DeliverPayloadNugget *self = (DeliverPayloadNugget *)instance;
    const char *name = ini->getNextToken(0);
    const char *countText = ini->getNextTokenOrNull(0);
    int count = countText ? INI::scanInt(countText) : 1;

    Payload payload;
    payload.m_payloadCount = count;
    payload.m_payloadName.set(name);
    self->m_payload.push_back(payload);
}
