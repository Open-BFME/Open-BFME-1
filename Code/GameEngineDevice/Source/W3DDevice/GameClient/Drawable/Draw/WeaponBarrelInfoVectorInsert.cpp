// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: vector<ModelConditionInfo::WeaponBarrelInfo>::_M_insert_overflow,
// retail 0x0076D380, 338 bytes. The body carried no ledger row; its name sat
// on a 5-byte thunk.
//
// The element is 0x3C bytes -- the imul by 0x3C in the allocation says so --
// and its copy is a call, which is what a declared copy constructor gives.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class ModelConditionInfo
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
	struct WeaponBarrelInfo
	{
		WeaponBarrelInfo(const WeaponBarrelInfo &other);

		char m_bfmeBody[0x3C];
	};
};

void BfmeWeaponBarrelInfoVectorAnchor(_STL::vector<ModelConditionInfo::WeaponBarrelInfo> &v, const ModelConditionInfo::WeaponBarrelInfo &value)
{
	v.insert(v.begin(), value);
}
