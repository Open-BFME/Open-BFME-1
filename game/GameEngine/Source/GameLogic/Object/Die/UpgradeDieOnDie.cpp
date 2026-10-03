// cl: /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Include /Igame/GameEngine/Source/Common/Thing /Igame/GameEngine/Source/GameLogic/Object /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "GameLogic/Module/UpgradeDie.h"
class UpgradeTemplate;
#define BFME_HAVE_OBJECTID 1
#define OBJECT_TU_MEMBERS ObjectID getProducerID() const {return m_producerID;} bool hasUpgrade(const UpgradeTemplate *) const; void removeUpgrade(const UpgradeTemplate *);
#include "object.h"
#define BFME_GAMELOGIC_LOOKUP_VISIBLE
// The shared BFME lookup is pinned with an int key; GameType.h declares
// ObjectID as an enum. Keep the native module enum and the existing int ABI.
#define ObjectID Int
#include "GameLogicObjectLookup.h"
#undef ObjectID
extern GameLogic *TheGameLogic;
extern UpgradeCenter *TheUpgradeCenter;
// Retail 0x00256240; see identity_evidence/00256240-upgrade-die.md.
void UpgradeDie::onDie( const DamageInfo *damageInfo )
{
	if (!isDieApplicable(damageInfo))
		return;

	Object *producer = TheGameLogic->findObjectByID(getObject()->getProducerID());
	if (producer)
	{
		// BFME extends the die-mux data: retail UpgradeToRemove is at +0x34,
		// rather than the Zero Hour header field offset. Use the real string type.
		const AsciiString &upgradeName = *reinterpret_cast<const AsciiString *>(
			reinterpret_cast<const char *>(getModuleData()) + 0x34);
		const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(upgradeName);
		if (upgrade && producer->hasUpgrade(upgrade))
			producer->removeUpgrade(upgrade);
	}
}
