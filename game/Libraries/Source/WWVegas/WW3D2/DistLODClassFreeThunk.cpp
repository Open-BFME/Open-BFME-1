// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/distlod.h
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
