// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

class AsciiString;

class AsciiStringEqualityShim
{
public:
    static bool equal(const AsciiString &, const AsciiString &);
};

bool operator==(const AsciiString &a, const AsciiString &b)
{
    return AsciiStringEqualityShim::equal(a, b);
}
