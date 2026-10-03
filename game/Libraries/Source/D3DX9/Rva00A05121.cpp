// cl: /O2 /MD
// Retail CD3DXSkinInfo table VA01149088 slot7 (+1C) points to00A05121.
// Its matched constructor00A116D3 installs the table at00A116DF;
// slot0 is the native CD3DXSkinInfo::QueryInterface at00A04EA7.
// This ten-byte stack-this accessor ends RET4 at00A05128, immediately
// before the next proven body00A0512B. Ghidra and PE bytes agree.
// Owner is established; original method name is not claimed.
class CD3DXSkinInfo
{
public:
    unsigned long __stdcall rva00A05121();
};

unsigned long __stdcall CD3DXSkinInfo::rva00A05121()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 8);
}
