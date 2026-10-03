// cl: /O1 /GS /MD /Iinputs/toolchains/vs2003/native/Vc7/atlmfc/include /Iinputs/toolchains/vs2003/native/Vc7/PlatformSDK/Include
#include <atlcore.h>
// Native ATL 7.1 declarations; retain the existing matched initializer's
// address-qualified constructor and its already-matched base constructor.
// See identity_evidence/009f6adb-atl-constructor.md for all nine bindings.
extern "C" IMAGE_DOS_HEADER __ImageBase;
extern "C" const GUID GUID_ATLVer70;

class Rva009F69B1 : public ATL::_ATL_BASE_MODULE70
{
public:
    Rva009F69B1() throw();
};
class Rva009F6ADBObject : public Rva009F69B1
{
public:
    Rva009F6ADBObject() throw();
};
Rva009F6ADBObject::Rva009F6ADBObject() throw()
{
    cbSize = sizeof(ATL::_ATL_BASE_MODULE70);
    m_hInst = m_hInstResource = reinterpret_cast<HINSTANCE>(&__ImageBase);
    m_bNT5orWin98 = false;
    OSVERSIONINFO version;
    memset(&version, 0, sizeof(version));
    version.dwOSVersionInfoSize = sizeof(version);
    ::GetVersionEx(&version);
    if (version.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        if (version.dwMajorVersion >= 5)
            m_bNT5orWin98 = true;
    }
    else if (version.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
    {
        if ((version.dwMajorVersion > 4) ||
            ((version.dwMajorVersion == 4) && version.dwMinorVersion > 0))
            m_bNT5orWin98 = true;
    }
    dwAtlBuildVer = _ATL_VER;
    pguidVer = &GUID_ATLVer70;
    if (FAILED(m_csResource.Init()))
        ATL::CAtlBaseModule::m_bInitFailed = true;
}
