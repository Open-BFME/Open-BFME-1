// ?d_006b9c90@@YAXXZ
// partial score=0.3 date=2026-09-09
// Scratch reconstruction for retail 0x006B9C90.  This file is not part of the
// production build; it preserves the observed AudioManager update lifetime and
// call graph while the source/identity evidence is reviewed.
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned char Bool;
typedef __int64 Time64;

__declspec(dllimport) int __stdcall bfmeWait1012(void *handle, int timeout);
__declspec(dllimport) void __stdcall Rva01358ECC(void *handle);
extern "C" __declspec(dllimport) Time64 __cdecl _time64(Time64 *time);
void __cdecl operator delete(void *block) throw();

extern void j_0002f1d5();
extern void j_00044661();
extern void j_0000c30b();
extern void j_0002f68f();
extern void j_00022c96();
extern void j_00048c84();
extern void j_00002f13();
extern void j_00019dad();
extern void j_0002e6ae();
extern void j_0004ac82();
extern void j_00044be3();
extern void j_0003d7d0();
extern void j_00017f85();
extern void j_00047cee();
extern void j_0000d33c();

struct Rva006B9C90Settings
{
	char pad00[0x70];
	int field70;
};

struct Rva006B9C90Job
{
	void *vtable;
	char *begin;
	char *end;
	char pad10[4];
	int status;
};

class Rva006B9C90Channel
{
};

class Rva006B9C90Logic
{
public:
	bool check();
};

#define RVA006B9C90_SLOT(n) virtual void slot##n();
class MilesAudioManager
{
public:
	RVA006B9C90_SLOT(00) RVA006B9C90_SLOT(01) RVA006B9C90_SLOT(02)
	RVA006B9C90_SLOT(03) RVA006B9C90_SLOT(04) RVA006B9C90_SLOT(05)
	RVA006B9C90_SLOT(06) RVA006B9C90_SLOT(07) RVA006B9C90_SLOT(08)
	RVA006B9C90_SLOT(09) RVA006B9C90_SLOT(10) RVA006B9C90_SLOT(11)
	RVA006B9C90_SLOT(12) RVA006B9C90_SLOT(13) RVA006B9C90_SLOT(14)
	RVA006B9C90_SLOT(15) RVA006B9C90_SLOT(16) RVA006B9C90_SLOT(17)
	RVA006B9C90_SLOT(18) RVA006B9C90_SLOT(19) RVA006B9C90_SLOT(20)
	RVA006B9C90_SLOT(21) RVA006B9C90_SLOT(22) RVA006B9C90_SLOT(23)
	RVA006B9C90_SLOT(24) RVA006B9C90_SLOT(25) RVA006B9C90_SLOT(26)
	RVA006B9C90_SLOT(27) RVA006B9C90_SLOT(28) RVA006B9C90_SLOT(29)
	RVA006B9C90_SLOT(30) RVA006B9C90_SLOT(31) RVA006B9C90_SLOT(32)
	RVA006B9C90_SLOT(33) RVA006B9C90_SLOT(34) RVA006B9C90_SLOT(35)
	RVA006B9C90_SLOT(36) RVA006B9C90_SLOT(37) RVA006B9C90_SLOT(38)
	RVA006B9C90_SLOT(39) RVA006B9C90_SLOT(40) RVA006B9C90_SLOT(41)
	RVA006B9C90_SLOT(42) RVA006B9C90_SLOT(43) RVA006B9C90_SLOT(44)
	RVA006B9C90_SLOT(45) RVA006B9C90_SLOT(46) RVA006B9C90_SLOT(47)
	RVA006B9C90_SLOT(48) RVA006B9C90_SLOT(49) RVA006B9C90_SLOT(50)
	RVA006B9C90_SLOT(51) RVA006B9C90_SLOT(52) RVA006B9C90_SLOT(53)
	RVA006B9C90_SLOT(54) RVA006B9C90_SLOT(55) RVA006B9C90_SLOT(56)
	RVA006B9C90_SLOT(57) RVA006B9C90_SLOT(58) RVA006B9C90_SLOT(59)
	RVA006B9C90_SLOT(60) RVA006B9C90_SLOT(61) RVA006B9C90_SLOT(62)
	RVA006B9C90_SLOT(63) RVA006B9C90_SLOT(64) RVA006B9C90_SLOT(65)
	RVA006B9C90_SLOT(66) RVA006B9C90_SLOT(67) RVA006B9C90_SLOT(68)
	RVA006B9C90_SLOT(69) RVA006B9C90_SLOT(70) RVA006B9C90_SLOT(71)
	RVA006B9C90_SLOT(72) RVA006B9C90_SLOT(73) RVA006B9C90_SLOT(74)
	RVA006B9C90_SLOT(75) RVA006B9C90_SLOT(76) RVA006B9C90_SLOT(77)
	RVA006B9C90_SLOT(78) RVA006B9C90_SLOT(79) RVA006B9C90_SLOT(80)
	RVA006B9C90_SLOT(81) RVA006B9C90_SLOT(82) RVA006B9C90_SLOT(83)
	RVA006B9C90_SLOT(84) RVA006B9C90_SLOT(85) RVA006B9C90_SLOT(86)
	RVA006B9C90_SLOT(87) RVA006B9C90_SLOT(88) RVA006B9C90_SLOT(89)
	RVA006B9C90_SLOT(90) RVA006B9C90_SLOT(91) RVA006B9C90_SLOT(92)
	RVA006B9C90_SLOT(93) RVA006B9C90_SLOT(94) RVA006B9C90_SLOT(95)
	RVA006B9C90_SLOT(96) RVA006B9C90_SLOT(97) RVA006B9C90_SLOT(98)
	virtual float slot99();
	virtual void update();

	char pad004[8];
	Rva006B9C90Settings *settings;
	char pad010[0x44 - 0x10];
	float field44;
	char pad048[0x604 - 0x48];
	int field604;
	char pad608[0x631 - 0x608];
	unsigned char flag631;
	char pad632[2];
	unsigned char flag634;
	unsigned char flag635;
	unsigned char flag636;
	char pad637[0x95c - 0x637];
	void *mutex;
	char pad960[0xadc - 0x960];
	void *vectorBegin;
	void *vectorEnd;
	char pad0ae4[0xb58 - 0xae4];
	Rva006B9C90Job *job;
	char pad0b5c[0xb68 - 0xb5c];
	Time64 lastUpdate;
	char pad0b70[4];
};
#undef RVA006B9C90_SLOT

class Rva006B9C90Mutex
{
public:
	Rva006B9C90Mutex(void *handle)
	{
		held = 0;
		mutex = handle;
		if (bfmeWait1012(mutex, -1) != 0x102)
			held = 1;
	}

	~Rva006B9C90Mutex()
	{
		if (held)
			Rva01358ECC(mutex);
	}

	void *mutex;
	unsigned char held;
};

int scratch_offset44()
{
	return (int)((char *)&((MilesAudioManager *)0)->field44 - (char *)0);
}

#define UPDATE_GUARD (*(volatile unsigned char *)0x012F77A0)
#define REFRESH_GUARD (*(volatile unsigned int *)0x012F779C)
#define REFRESH_RESULT (*(volatile unsigned char *)0x012F7798)
#define THE_GAME_ENGINE (*(struct Rva006B9C90Engine **)0x012ED524)
#define THE_GAME_LOGIC (*(Rva006B9C90Logic **)0x012F0898)

struct Rva006B9C90Engine
{
	char pad00[0x30];
	int mode;
};

void MilesAudioManager::update()
{
	Rva006B9C90Mutex guard(mutex);
	if (UPDATE_GUARD)
		return;

	UPDATE_GUARD = 1;
	Time64 now = _time64(0);
	if (now - lastUpdate > settings->field70)
	{
		if (!(REFRESH_GUARD & 1))
		{
			REFRESH_GUARD |= 1;
			typedef bool (MilesAudioManager::*Probe)();
			union { void (__cdecl *freeFunction)(); Probe memberFunction; } probe;
			probe.freeFunction = ::j_0002f1d5;
			REFRESH_RESULT = (this->*probe.memberFunction)();
			if (REFRESH_RESULT)
			{
				typedef void (MilesAudioManager::*Refresh)();
				union { void (__cdecl *freeFunction)(); Refresh memberFunction; } refresh;
				refresh.freeFunction = ::j_00044661;
				(this->*refresh.memberFunction)();
				field44 = slot99();
			}
		}

		if (!flag636 && vectorBegin != vectorEnd &&
			THE_GAME_ENGINE != 0 && THE_GAME_ENGINE->mode == 1)
			flag635 = 1;
	}

	UPDATE_GUARD = 0;

	typedef void (MilesAudioManager::*NoArg)();
	union { void (__cdecl *freeFunction)(); NoArg memberFunction; } base;
	base.freeFunction = ::j_0000c30b;
	(this->*base.memberFunction)();

	typedef void (Rva006B9C90Channel::*Apply)(float);
	union { void (__cdecl *freeFunction)(); Apply memberFunction; } apply;
	apply.freeFunction = ::j_0002f68f;
	Rva006B9C90Channel *channel =
		(Rva006B9C90Channel *)((char *)this + 0x440);
	(channel->*apply.memberFunction)(field44);

	if (field604 != 2 && THE_GAME_LOGIC != 0)
	{
		typedef bool (Rva006B9C90Logic::*Check)();
		union { void (__cdecl *freeFunction)(); Check memberFunction; } check;
		check.freeFunction = ::j_00022c96;
		if (!(THE_GAME_LOGIC->*check.memberFunction)())
		{
			channel = (Rva006B9C90Channel *)((char *)this + 0xb8 + field604 * 0x1c4);
			(channel->*apply.memberFunction)(field44);
		}
	}

	base.freeFunction = ::j_00048c84;
	(this->*base.memberFunction)();
	base.freeFunction = ::j_00002f13;
	(this->*base.memberFunction)();
	base.freeFunction = ::j_00019dad;
	(this->*base.memberFunction)();
	base.freeFunction = ::j_0002e6ae;
	(this->*base.memberFunction)();

	int local = 0;
	typedef void (MilesAudioManager::*WithLocal)(void *);
	union { void (__cdecl *freeFunction)(); WithLocal memberFunction; } withLocal;
	withLocal.freeFunction = ::j_0004ac82;
	(this->*withLocal.memberFunction)(&local);
	withLocal.freeFunction = ::j_00044be3;
	(this->*withLocal.memberFunction)(&local);
	base.freeFunction = ::j_0003d7d0;
	(this->*base.memberFunction)();
	base.freeFunction = ::j_00017f85;
	(this->*base.memberFunction)();

	flag631 = 0;
	flag634 = 0;
	flag635 = 0;
	flag636 = 0;

	channel = (Rva006B9C90Channel *)((char *)this + 0xb8);
	int remaining = 3;
	do
	{
		typedef void (Rva006B9C90Channel::*Decay)();
		union { void (__cdecl *freeFunction)(); Decay memberFunction; } decay;
		decay.freeFunction = ::j_00047cee;
		(channel->*decay.memberFunction)();
		channel = (Rva006B9C90Channel *)((char *)channel + 0x1c4);
	}
	while (--remaining);

	Rva006B9C90Job *oldJob = job;
	if (oldJob != 0 && oldJob->status == 1)
	{
		int count = ((int)(oldJob->end - oldJob->begin)) >> 3;
		if (count <= 0)
		{
			typedef void (Rva006B9C90Job::*Destroy)();
			union { void (__cdecl *freeFunction)(); Destroy memberFunction; } destroy;
			destroy.freeFunction = ::j_0000d33c;
			(oldJob->*destroy.memberFunction)();
			::operator delete(oldJob);
			job = 0;
		}
	}
}
