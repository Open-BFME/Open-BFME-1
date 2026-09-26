// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

class Thing;
class ModuleData;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyWarehouseCripplingBehavior.h
class SupplyWarehouseCripplingBehavior
{
public:
    SupplyWarehouseCripplingBehavior(Thing *, const ModuleData *);
};

__declspec(naked) SupplyWarehouseCripplingBehavior::SupplyWarehouseCripplingBehavior(Thing *, const ModuleData *)
{
    __asm {
        _emit 0E9h
        _emit 0A2h
        _emit 05Fh
        _emit 01Dh
        _emit 000h
    }
}
