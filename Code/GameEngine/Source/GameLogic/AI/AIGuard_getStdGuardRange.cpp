// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGuardMachine::getStdGuardRange, retail 0x0015C060, 59 bytes.
// ZH wrapper plus a std::min clamp at 300.0f. The name is already claimed on
// the 16-byte unclamped ICF at 0x00189B30.
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>

typedef float Real;

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	static Real getAdjustedVisionRangeForObject(const Object *obj, int factors);
};

enum
{
	AI_VISIONFACTOR_OWNERTYPE = 1,
	AI_VISIONFACTOR_MOOD = 2,
	AI_VISIONFACTOR_GUARDINNER = 4
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIGuard.h
class AIGuardMachine
{
public:
	static Real _bfme_getStdGuardRange(const Object *obj);
};

Real AIGuardMachine::_bfme_getStdGuardRange(const Object *obj)
{
	Real visionRange = AI::getAdjustedVisionRangeForObject(obj,
		AI_VISIONFACTOR_OWNERTYPE | AI_VISIONFACTOR_MOOD | AI_VISIONFACTOR_GUARDINNER);

	const Real cap = 300.0f;
	return (_STL::min)(visionRange, cap);
}
