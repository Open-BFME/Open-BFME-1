// cl: /DNDEBUG /MD /EHsc

// STLport's raw placement-construct helper for PSResponse.  The retail body is
// the new-expression expanded inline: the placement operator new returns its
// argument (hence the `test esi,esi` null check), the compiler-generated
// PSResponse copy constructor is inlined member-by-member, and the AsciiString
// member forwards to the private StringBase<char> copy constructor.  The SEH
// frame is the new-expression's cleanup region for the matching placement
// operator delete.

template <typename T>
class StringBase
{
    friend class AsciiString;

private:
    StringBase(const StringBase<T> &src);

private:
    void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
    AsciiString(const AsciiString &that)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
    }

private:
    char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PersistentStorageThread.h
class PSResponse
{
public:
    int m_responseType;
    AsciiString m_text;
    int m_valueA;
    int m_valueB;
};

inline void *__cdecl operator new(unsigned int, void *place)
{
    return place;
}

inline void __cdecl operator delete(void *, void *)
{
}

namespace _STL
{
template <class T, class U>
void _Construct(T *, const U &);

template <class T, class U>
void _Construct(T *p, const U &v)
{
    new (p) T(v);
}

template void _Construct<PSResponse, PSResponse>(PSResponse *, const PSResponse &);
}
