// HordeWorkerAIUpdate complete destructor at retail 0x002C4980 (49 bytes).
// ??_GHordeWorkerAIUpdate (0x002C4B30) calls it through ILT 0x000369AD, pinned
// ??1HordeWorkerAIUpdate@@MAE@XZ (ilt_oracle: MAE exact at 0x002C4980). The
// body re-seats the six vftables that HordeWorkerAIUpdate's constructor
// (HordeWorkerAIUpdateCtorThunk.cpp) installs, in ascending displacement
// order, and tail-jumps to ??1HordeAIUpdate@@MAE@XZ through ILT 0x00033A37.
//
// The vftables are the constructor TU's COMDATs, named by their decorated
// symbols; novtable keeps this TU from emitting second copies of them.

extern "C" const void *__identifier("??_7HordeWorkerAIUpdate@@6BHordeWorkerAIUpdateBase@@@")[];
extern "C" const void *__identifier("??_7HordeWorkerAIUpdate@@6BHWAI_Iface1@@@")[];
extern "C" const void *__identifier("??_7HordeWorkerAIUpdate@@6BHWAI_Iface2@@@")[];
extern "C" const void *__identifier("??_7HordeWorkerAIUpdate@@6BHWAI_Iface3@@@")[];
extern "C" const void *__identifier("??_7HordeWorkerAIUpdate@@6BHWAI_Iface4@@@")[];
extern "C" const void *__identifier("??_7HordeWorkerAIUpdate@@6BHWAI_Iface5@@@")[];

class HordeAIUpdate
{
protected:
	virtual ~HordeAIUpdate();
};

class __declspec(novtable) HordeWorkerAIUpdate : public HordeAIUpdate
{
protected:
	virtual ~HordeWorkerAIUpdate();
};

#define HORDE_WORKER_AI_UPDATE_VPTR(offset, table) \
	(*(const void *volatile *)((unsigned char *)this + (offset)) = (const void *)__identifier(table))

HordeWorkerAIUpdate::~HordeWorkerAIUpdate()
{
	HORDE_WORKER_AI_UPDATE_VPTR(0x000, "??_7HordeWorkerAIUpdate@@6BHordeWorkerAIUpdateBase@@@");
	HORDE_WORKER_AI_UPDATE_VPTR(0x00C, "??_7HordeWorkerAIUpdate@@6BHWAI_Iface1@@@");
	HORDE_WORKER_AI_UPDATE_VPTR(0x010, "??_7HordeWorkerAIUpdate@@6BHWAI_Iface2@@@");
	HORDE_WORKER_AI_UPDATE_VPTR(0x020, "??_7HordeWorkerAIUpdate@@6BHWAI_Iface3@@@");
	HORDE_WORKER_AI_UPDATE_VPTR(0x024, "??_7HordeWorkerAIUpdate@@6BHWAI_Iface4@@@");
	HORDE_WORKER_AI_UPDATE_VPTR(0x340, "??_7HordeWorkerAIUpdate@@6BHWAI_Iface5@@@");
}
