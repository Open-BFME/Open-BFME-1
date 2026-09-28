// cl: /O2 /MD
// Retail 0x00C6DC10 is the namespace-scope dynamic initializer for the
// AsciiString global at 0x01336E50: it runs the default constructor and
// registers the 0x00C70F00 atexit cleanup, which destroys the string.
// Defining the global here lets MSVC emit those bytes as its compiler-local
// _$E1; the ledger row names that COFF symbol via object-symbol=_$E1.
class AsciiString
{
public:
    AsciiString();
    ~AsciiString();
};

AsciiString Rva01336E50EmptyString;
