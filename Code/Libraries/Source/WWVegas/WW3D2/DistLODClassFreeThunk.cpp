// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/distlod.h
class DistLODClass
{
private:
    __declspec(dllexport) void Free();
};

class DistLODClassFreeShim
{
public:
    void release();
};

void DistLODClass::Free()
{
    ((DistLODClassFreeShim *)this)->release();
}
