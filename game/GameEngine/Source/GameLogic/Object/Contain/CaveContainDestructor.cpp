// CaveContain complete destructor at retail 0x00219290 (77 bytes).
// ??_GCaveContain (0x00219C40) calls it through ILT 0x0002748F, pinned
// ??1CaveContain@@MAE@XZ (ilt_oracle: MAE exact at 0x00219290, UAE
// contradicted). The body re-seats the ten vftables of CaveContain's
// sub-objects in ascending displacement order and tail-jumps to
// ??1OpenContain@@UAE@XZ through ILT 0x00039D6A.
//
// The vftables are named by the decorated symbols dir32_addresses.csv records
// for them; novtable keeps this TU from emitting second copies.

extern "C" const void *__identifier("??_7CaveContain@@6BCaveContainBase@@@")[];
extern "C" const void *__identifier("??_7CaveContain@@6BCaveContainIface1@@@")[];
extern "C" const void *__identifier("??_7CaveContain@@6BCaveContainIface2@@@")[];
extern "C" const void *__identifier("??_7CaveContain@@6BCaveContainIface3@@@")[];
extern "C" const void *__identifier("??_7CaveContain@@6BCaveContainIface4@@@")[];
extern "C" const void *__identifier("??_7CaveContain@@6BCaveContainIface5@@@")[];
extern "C" const void *__identifier("??_7CaveContain@@6BCaveContainIface6@@@")[];
extern "C" const void *__identifier("??_7CaveContain@@6BCaveContainIface7@@@")[];
extern "C" const void *__identifier("??_7CaveContain@@6BCaveContainIface8@@@")[];
extern "C" const void *__identifier("??_7CaveContain@@6BCaveContainIface9@@@")[];

class OpenContain
{
public:
	virtual ~OpenContain();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CaveContain.h
class __declspec(novtable) CaveContain : public OpenContain
{
protected:
	virtual ~CaveContain();
};

#define CAVE_CONTAIN_VPTR(offset, table) \
	(*(const void *volatile *)((unsigned char *)this + (offset)) = (const void *)__identifier(table))

CaveContain::~CaveContain()
{
	CAVE_CONTAIN_VPTR(0x00, "??_7CaveContain@@6BCaveContainBase@@@");
	CAVE_CONTAIN_VPTR(0x0C, "??_7CaveContain@@6BCaveContainIface1@@@");
	CAVE_CONTAIN_VPTR(0x10, "??_7CaveContain@@6BCaveContainIface2@@@");
	CAVE_CONTAIN_VPTR(0x20, "??_7CaveContain@@6BCaveContainIface3@@@");
	CAVE_CONTAIN_VPTR(0x24, "??_7CaveContain@@6BCaveContainIface4@@@");
	CAVE_CONTAIN_VPTR(0x28, "??_7CaveContain@@6BCaveContainIface5@@@");
	CAVE_CONTAIN_VPTR(0x2C, "??_7CaveContain@@6BCaveContainIface6@@@");
	CAVE_CONTAIN_VPTR(0x30, "??_7CaveContain@@6BCaveContainIface7@@@");
	CAVE_CONTAIN_VPTR(0x34, "??_7CaveContain@@6BCaveContainIface8@@@");
	CAVE_CONTAIN_VPTR(0xD4, "??_7CaveContain@@6BCaveContainIface9@@@");
}
