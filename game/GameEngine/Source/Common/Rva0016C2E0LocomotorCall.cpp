// cl: /O2 /MD

#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier(void);

class AIUpdateInterface
{
};

extern void j_0003daa5();

class Rva0016C2E0Controller
{
private:
	char m_padding[0x204];

public:
	AIUpdateInterface *m_aiUpdate;
};

class Rva0016C2E0Inner
{
private:
	char m_padding[0x10];

public:
	Rva0016C2E0Controller *m_controller;
};

class Rva0016C2E0
{
private:
	char m_padding[0x1C];
	Rva0016C2E0Inner *m_inner;

public:
	void run();
};

void Rva0016C2E0::run()
{
	typedef void (AIUpdateInterface::*SpeedCall)();
	union
	{
		void (*raw)();
		SpeedCall member;
	} call;
	call.raw = j_0003daa5;
	(m_inner->m_controller->m_aiUpdate->*call.member)();
	_ReadWriteBarrier();
}
