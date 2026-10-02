// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "PreRTS.h"
#include "GameLogic/Module/GarrisonContain.h"

// Unique registered update slot: identity_evidence/update-slot0.md.
// Existing GarrisonContain headers place the compiler update receiver at
// primary +0x14; retail uses +0x10. Preserve retail receiver-relative fields
// and explicitly reconstruct primary pointers for the two helper calls.
// Declaration views omit storage; all BFME field accesses below use offsets.
// Constructor chain: ContestableContain -> HordeGarrisonContain -> GarrisonContain.
class HordeGarrisonContain : public GarrisonContain {};
class ContestableContain : public HordeGarrisonContain
{
public:
    virtual UpdateSleepTime update();
    void updateContestStatus();
};

class Rva0021D180 { public: void body(); };
class GameLogic;
extern GameLogic *TheGameLogic;

class Rva0021D4A0Secondary
{
public:
#define RVA_SLOT(n) virtual void slot##n();
	RVA_SLOT(00) RVA_SLOT(01) RVA_SLOT(02) RVA_SLOT(03) RVA_SLOT(04)
	RVA_SLOT(05) RVA_SLOT(06) RVA_SLOT(07) RVA_SLOT(08) RVA_SLOT(09)
	RVA_SLOT(10) RVA_SLOT(11) RVA_SLOT(12) RVA_SLOT(13) RVA_SLOT(14)
	RVA_SLOT(15) RVA_SLOT(16) RVA_SLOT(17) RVA_SLOT(18) RVA_SLOT(19)
	RVA_SLOT(20) RVA_SLOT(21) RVA_SLOT(22) RVA_SLOT(23) RVA_SLOT(24)
	RVA_SLOT(25) RVA_SLOT(26) RVA_SLOT(27) RVA_SLOT(28) RVA_SLOT(29)
	RVA_SLOT(30) RVA_SLOT(31) RVA_SLOT(32) RVA_SLOT(33) RVA_SLOT(34)
	RVA_SLOT(35) RVA_SLOT(36) RVA_SLOT(37) RVA_SLOT(38) RVA_SLOT(39)
	RVA_SLOT(40) RVA_SLOT(41) RVA_SLOT(42) RVA_SLOT(43) RVA_SLOT(44)
	RVA_SLOT(45) RVA_SLOT(46) RVA_SLOT(47) RVA_SLOT(48)
	virtual bool predicate();
#undef RVA_SLOT
};

UpdateSleepTime ContestableContain::update()
{
	UpdateSleepTime result = GarrisonContain::update();
	char *receiver = reinterpret_cast<char *>(this) + 0x14;
	Rva0021D4A0Secondary *secondary = reinterpret_cast<Rva0021D4A0Secondary *>(receiver + 0x10);

	if (!secondary->predicate())
		goto done;

	void *logic = TheGameLogic;
	if (*reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(logic) + 0x3c) >=
		*reinterpret_cast<unsigned int *>(receiver + 0x9c4))
	{
		reinterpret_cast<ContestableContain *>(receiver - 0x10)->updateContestStatus();
	}

	void *list = *reinterpret_cast<void **>(receiver + 0x9ac);
	if (*reinterpret_cast<void **>(list) != list)
	{
		list = *reinterpret_cast<void **>(receiver + 0x28);
		if (*reinterpret_cast<void **>(list) != list)
			return UPDATE_SLEEP_NONE;
	}

	reinterpret_cast<Rva0021D180 *>(receiver - 0x10)->body();
done:
	return result;
}
