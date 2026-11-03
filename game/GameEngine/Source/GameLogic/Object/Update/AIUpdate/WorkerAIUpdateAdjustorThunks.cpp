// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: this-adjustor thunk of WorkerAIUpdate::onDelete.
// Retail 0x002C9450 is an 11-byte `sub ecx,0x340 / jmp` entry reached only from
// ILT 0x000134B7; it jumps through ILT 0x00026D50 to WorkerAIUpdate::onDelete
// (0x002C9090). ilt_oracle CONFIRMS ?onDelete@WorkerAIUpdate@@WDEA@AEXXZ here,
// so the secondary base declaring onDelete (DozerAIInterface in ZH
// WorkerAIUpdate.h) sits at +0x340. Only that offset and the override are
// modelled; the bases are novtable with external constructors and no
// destructors, so this unit emits no base vtable, constructor or destructor copy.

class __declspec(novtable) AIUpdateInterface
{
public:
	AIUpdateInterface();
	virtual void onDelete();
private:
	char m_aiFill[0x340 - 4];
};

class __declspec(novtable) DozerAIInterface
{
public:
	DozerAIInterface();
	virtual void onDelete();
};

class WorkerAIUpdate : public AIUpdateInterface, public DozerAIInterface
{
public:
	virtual void onDelete();
private:
	friend void forceWorkerAIUpdateAdjustorThunks();
};

void forceWorkerAIUpdateAdjustorThunks()
{
	WorkerAIUpdate value;
}
