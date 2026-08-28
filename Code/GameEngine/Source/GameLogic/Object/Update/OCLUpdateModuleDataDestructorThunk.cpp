// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: empty virtual dtor emits mov [ecx], vtbl; ret (7B).
// No base class: inheritance would emit jmp to base dtor.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OCLUpdate.h
class OCLUpdateModuleData
{
public:
	virtual ~OCLUpdateModuleData();
};

// ??1OCLUpdateModuleData@@UAE@XZ
OCLUpdateModuleData::~OCLUpdateModuleData()
{
}
