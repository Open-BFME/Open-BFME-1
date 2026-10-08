// SpecialDisguiseUpdate complete destructor at retail 0x002675F0 (42 bytes).
// ??_GSpecialDisguiseUpdate (0x00267890) calls it through ILT 0x00008AE4,
// pinned ??1SpecialDisguiseUpdate@@MAE@XZ (ilt_oracle: MAE exact at
// 0x002675F0). The body re-seats the five vftables that
// SpecialDisguiseUpdate's constructor (SpecialDisguiseUpdateCtorThunk.cpp)
// installs, in ascending displacement order, and tail-jumps to
// ??1SpecialAbilityUpdate@@UAE@XZ through ILT 0x000243A7.
//
// The vftables are the constructor TU's COMDATs, named by their decorated
// symbols; novtable keeps this TU from emitting second copies of them.

extern "C" const void *__identifier("??_7SpecialDisguiseUpdate@@6BSpecialDisguiseUpdateBase@@@")[];
extern "C" const void *__identifier("??_7SpecialDisguiseUpdate@@6BSpecialDisguiseUpdateIface1@@@")[];
extern "C" const void *__identifier("??_7SpecialDisguiseUpdate@@6BSpecialDisguiseUpdateIface2@@@")[];
extern "C" const void *__identifier("??_7SpecialDisguiseUpdate@@6BSpecialDisguiseUpdateIface3@@@")[];
extern "C" const void *__identifier("??_7SpecialDisguiseUpdate@@6BSpecialDisguiseUpdateIface4@@@")[];

class SpecialAbilityUpdate
{
public:
	virtual ~SpecialAbilityUpdate();
};

class __declspec(novtable) SpecialDisguiseUpdate : public SpecialAbilityUpdate
{
protected:
	virtual ~SpecialDisguiseUpdate();
};

#define SPECIAL_DISGUISE_UPDATE_VPTR(offset, table) \
	(*(const void *volatile *)((unsigned char *)this + (offset)) = (const void *)__identifier(table))

SpecialDisguiseUpdate::~SpecialDisguiseUpdate()
{
	SPECIAL_DISGUISE_UPDATE_VPTR(0x00, "??_7SpecialDisguiseUpdate@@6BSpecialDisguiseUpdateBase@@@");
	SPECIAL_DISGUISE_UPDATE_VPTR(0x0C, "??_7SpecialDisguiseUpdate@@6BSpecialDisguiseUpdateIface1@@@");
	SPECIAL_DISGUISE_UPDATE_VPTR(0x10, "??_7SpecialDisguiseUpdate@@6BSpecialDisguiseUpdateIface2@@@");
	SPECIAL_DISGUISE_UPDATE_VPTR(0x20, "??_7SpecialDisguiseUpdate@@6BSpecialDisguiseUpdateIface3@@@");
	SPECIAL_DISGUISE_UPDATE_VPTR(0xE8, "??_7SpecialDisguiseUpdate@@6BSpecialDisguiseUpdateIface4@@@");
}
