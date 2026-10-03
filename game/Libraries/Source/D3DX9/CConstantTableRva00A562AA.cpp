// cl: /O2 /MD
// Native QueryInterface at A56226 establishes D3DXShader::CConstantTable.
// Constructor A56DFE installs table VA0114D7C8 at A56E11; destructor A55206
// reinstalls it at A5520D. Slots 3 and 4 independently select A562AA/A562B4.
// Both ten-byte stack-this getters end RET4. Their original names are unknown.
struct _GUID;

namespace D3DXShader
{
    class CConstantTable
    {
    public:
        virtual long __stdcall QueryInterface(const _GUID &, void **);
        virtual unsigned long __stdcall AddRef();
        unsigned long __stdcall rva00A562AA();
        unsigned long __stdcall rva00A562B4();
    };

    unsigned long __stdcall CConstantTable::rva00A562AA()
    {
        return *reinterpret_cast<const unsigned long *>(
            reinterpret_cast<const char *>(this) + 0x0c);
    }

    unsigned long __stdcall CConstantTable::rva00A562B4()
    {
        return *reinterpret_cast<const unsigned long *>(
            reinterpret_cast<const char *>(this) + 8);
    }
}

// QueryInterface at A56226 names AddRef and calls slot 1 of VA0114D7C8.
// See identity_evidence/00a5627e-addref-caller.md for the independent route.

// Table slot 1 increments receiver dword +4 and returns its new value.
// Volatile readback preserves the separate retail load after the increment.
// It does not claim an original volatile member type.
unsigned long __stdcall D3DXShader::CConstantTable::AddRef()
{
    unsigned long *value = reinterpret_cast<unsigned long *>(
        reinterpret_cast<char *>(this) + 4);
    ++*value;
    return *static_cast<volatile unsigned long *>(value);
}
