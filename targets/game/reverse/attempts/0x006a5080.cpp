// ?releaseSlot@Rva006A5080Owner@@QAEXPAURva006A5080Slot@@@Z
// partial score=0.28719 date=2026-09-25
// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc
// stlport
// Scratch native reconstruction of retail 0x006A5080 (484 bytes). Owner and
// slot names are address-derived; the caller passes a 64-byte slot in the
// manager's +0xB44 array. The hash table and pending-handle list are modeled
// with their native STLport types and witnessed member offsets.
#include <hash_map>
#include <list>

extern "C" __declspec(dllimport) int __stdcall AIL_3D_sample_status(void *);
extern "C" __declspec(dllimport) void __stdcall AIL_lock_mutex(void);
extern "C" __declspec(dllimport) void __stdcall AIL_unlock_mutex(void);
extern "C" __declspec(dllimport) void __stdcall AIL_stop_timer(int);

struct Rva006A5080PlayingAudio
{
	unsigned char prefix[0xC];
	int type;
	int status;
};

struct Rva006A5080Slot
{
	unsigned char active;
	unsigned char gap01[3];
	void *handle;
	void *refEvent;
	unsigned char enabled;
	unsigned char gap0D[3];
	Rva006A5080PlayingAudio *playing;
	void *freeEvent;
	unsigned char gap18[4];
	void *file;
	void *file20;
	void *file24;
	unsigned int clear28;
	unsigned int clear2C;
	unsigned int clear30;
};

class Rva006A5080RefBase
{
public:
	virtual ~Rva006A5080RefBase();
	long references;
	void Release_Ref()
	{
		if (InterlockedDecrement(&references) <= 0)
			delete this;
	}
};

typedef _STL::hash_map<int, Rva006A5080PlayingAudio *> Rva006A5080PlayingMap;
typedef _STL::list<int> Rva006A5080PendingHandles;

class Rva006ABFD0File
{
public:
	void release();
};

class Rva00691180
{
public:
	void go();
};

class Rva006A5080AilLockGuard
{
public:
	Rva006A5080AilLockGuard() { AIL_lock_mutex(); owns = true; }
	~Rva006A5080AilLockGuard() { if (owns) AIL_unlock_mutex(); }
	void release() { AIL_unlock_mutex(); owns = false; }
private:
	bool owns;
};

class Rva006A5080Owner
{
public:
	void releaseSlot(Rva006A5080Slot *slot);

	unsigned char *at(unsigned int offset) { return (unsigned char *)this + offset; }
};

void Rva006A5080Owner::releaseSlot(Rva006A5080Slot *slot)
{
	if (slot->active != 0 || slot->enabled == 0)
		return;
	if (slot->handle != 0 && AIL_3D_sample_status(slot->handle) == 4)
		return;
	if (slot->handle != 0)
	{
		if (slot->playing != 0) {
			Rva006A5080AilLockGuard guard;
			Rva006A5080PlayingMap &playing = *(Rva006A5080PlayingMap *)at(0xB1C);
			Rva006A5080PlayingMap::iterator found = playing.find(*(int *)&slot->handle);
			if (found == playing.end() || (*found).second != slot->playing)
				guard.release();
			else
				playing.erase(found);
		}
		((_STL::list<int> *)at(0x9C4))->push_back(*(int *)&slot->handle);
		slot->handle = 0;
		unsigned int *soundCount = (unsigned int *)at(0x614);
		if (*soundCount != 0)
			--*soundCount;
	}
	if (slot->freeEvent != 0) {
		::operator delete[](slot->freeEvent);
		slot->freeEvent = 0;
	}
	((Rva006ABFD0File *)&slot->file)->release();
	slot->clear2C = 0;
	slot->clear28 = 0;
	slot->clear30 = 0;
	((Rva00691180 *)&slot->file20)->go();
	((Rva00691180 *)&slot->file24)->go();
	if (slot->playing != 0) {
		slot->playing->status = 1;
		slot->playing->type = 4;
		slot->playing = 0;
	}
	if (slot->refEvent != 0) {
		((Rva006A5080RefBase *)((char *)slot->refEvent + 0x70))->Release_Ref();
		slot->refEvent = 0;
	}
	slot->enabled = 0;
	int *timerCount = (int *)at(0xB50);
	--*timerCount;
	if (*timerCount <= 0) {
		int timer = *(int *)at(0xB4C);
		if (timer != -1)
			AIL_stop_timer(timer);
	}
}
