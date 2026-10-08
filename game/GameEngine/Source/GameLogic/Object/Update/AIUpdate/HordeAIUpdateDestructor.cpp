// HordeAIUpdate complete destructor at retail 0x002C4190 (49 bytes).
// ??_GHordeAIUpdate (0x002C4450) calls it through ILT 0x00033A37, pinned
// ??1HordeAIUpdate@@MAE@XZ (ilt_oracle: MAE exact at 0x002C4190). The body
// re-seats the six vftables that HordeAIUpdate's constructor
// (HordeAIUpdateCtorThunk.cpp) installs, in ascending displacement order, and
// tail-jumps to ??1AIUpdateInterface@@UAE@XZ through ILT 0x0001C774.
//
// The vftables are the constructor TU's COMDATs, named by their decorated
// symbols; novtable keeps this TU from emitting second copies of them.

extern "C" const void *__identifier("??_7HordeAIUpdate@@6BHordeAIUpdateBase@@@")[];
extern "C" const void *__identifier("??_7HordeAIUpdate@@6BHordeAIUpdateIface1@@@")[];
extern "C" const void *__identifier("??_7HordeAIUpdate@@6BHordeAIUpdateIface2@@@")[];
extern "C" const void *__identifier("??_7HordeAIUpdate@@6BHordeAIUpdateIface3@@@")[];
extern "C" const void *__identifier("??_7HordeAIUpdate@@6BHordeAIUpdateIface4@@@")[];
extern "C" const void *__identifier("??_7HordeAIUpdate@@6BHordeAIUpdateIface5@@@")[];

class AIUpdateInterface
{
public:
	virtual ~AIUpdateInterface();
};

class __declspec(novtable) HordeAIUpdate : public AIUpdateInterface
{
protected:
	virtual ~HordeAIUpdate();
};

#define HORDE_AI_UPDATE_VPTR(offset, table) \
	(*(const void *volatile *)((unsigned char *)this + (offset)) = (const void *)__identifier(table))

HordeAIUpdate::~HordeAIUpdate()
{
	HORDE_AI_UPDATE_VPTR(0x000, "??_7HordeAIUpdate@@6BHordeAIUpdateBase@@@");
	HORDE_AI_UPDATE_VPTR(0x00C, "??_7HordeAIUpdate@@6BHordeAIUpdateIface1@@@");
	HORDE_AI_UPDATE_VPTR(0x010, "??_7HordeAIUpdate@@6BHordeAIUpdateIface2@@@");
	HORDE_AI_UPDATE_VPTR(0x020, "??_7HordeAIUpdate@@6BHordeAIUpdateIface3@@@");
	HORDE_AI_UPDATE_VPTR(0x024, "??_7HordeAIUpdate@@6BHordeAIUpdateIface4@@@");
	HORDE_AI_UPDATE_VPTR(0x340, "??_7HordeAIUpdate@@6BHordeAIUpdateIface5@@@");
}
