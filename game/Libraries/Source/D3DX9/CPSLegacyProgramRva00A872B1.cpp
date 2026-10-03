// cl: /O1 /MD
// Original cpslegacyprogram.obj table establishes this owner and the long
// thiscall/no-argument signatures. Retail ctor A87148 installs VA01157480
// at A87165; dtor A90C35 installs it at A90C41. Slots 5 and 19 independently
// select A872B1 and A8FE02; both end after three bytes, before the next entry.
namespace D3DXShader
{
    class CPSLegacyProgram
    {
    public:
        long rva00A872B1();
        long rva00A8FE02();
    };

    long CPSLegacyProgram::rva00A872B1()
    {
        return 0;
    }

    long CPSLegacyProgram::rva00A8FE02()
    {
        return 0;
    }
}
