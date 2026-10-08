// HealContain complete destructor at retail 0x00220240 (67 bytes).
// ??_GHealContain (0x00220350) calls it through ILT 0x0003A41D, pinned
// ??1HealContain@@MAE@XZ (ilt_oracle: MAE exact at 0x00220240). The body
// re-seats the nine vftables that HealContain's constructor
// (HealContainCtorThunk.cpp) installs, in ascending displacement order, and
// tail-jumps to ??1OpenContain@@UAE@XZ through ILT 0x00039D6A.
//
// The vftables are the constructor TU's COMDATs, named by their decorated
// symbols; novtable keeps this TU from emitting second copies of them.

extern "C" const void *__identifier("??_7HealContain@@6BHealContainGrandBase@@@")[];
extern "C" const void *__identifier("??_7HealContain@@6BHealContainIface1@@@")[];
extern "C" const void *__identifier("??_7HealContain@@6BHealContainIface2@@@")[];
extern "C" const void *__identifier("??_7HealContain@@6BHealContainIface3@@@")[];
extern "C" const void *__identifier("??_7HealContain@@6BHealContainIface4@@@")[];
extern "C" const void *__identifier("??_7HealContain@@6BHealContainIface5@@@")[];
extern "C" const void *__identifier("??_7HealContain@@6BHealContainIface6@@@")[];
extern "C" const void *__identifier("??_7HealContain@@6BHealContainIface7@@@")[];
extern "C" const void *__identifier("??_7HealContain@@6BHealContainIface8@@@")[];

class OpenContain
{
public:
	virtual ~OpenContain();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HealContain.h
class __declspec(novtable) HealContain : public OpenContain
{
protected:
	virtual ~HealContain();
};

#define HEAL_CONTAIN_VPTR(offset, table) \
	(*(const void *volatile *)((unsigned char *)this + (offset)) = (const void *)__identifier(table))

HealContain::~HealContain()
{
	HEAL_CONTAIN_VPTR(0x00, "??_7HealContain@@6BHealContainGrandBase@@@");
	HEAL_CONTAIN_VPTR(0x0C, "??_7HealContain@@6BHealContainIface1@@@");
	HEAL_CONTAIN_VPTR(0x10, "??_7HealContain@@6BHealContainIface2@@@");
	HEAL_CONTAIN_VPTR(0x20, "??_7HealContain@@6BHealContainIface3@@@");
	HEAL_CONTAIN_VPTR(0x24, "??_7HealContain@@6BHealContainIface4@@@");
	HEAL_CONTAIN_VPTR(0x28, "??_7HealContain@@6BHealContainIface5@@@");
	HEAL_CONTAIN_VPTR(0x2C, "??_7HealContain@@6BHealContainIface6@@@");
	HEAL_CONTAIN_VPTR(0x30, "??_7HealContain@@6BHealContainIface7@@@");
	HEAL_CONTAIN_VPTR(0x34, "??_7HealContain@@6BHealContainIface8@@@");
}
