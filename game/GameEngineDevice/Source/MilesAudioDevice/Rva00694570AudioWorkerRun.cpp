// ?run@Rva00694570@@QAEKXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /MD /EHsc /O2 /Ob2 /Iinputs/vendor/stlport /Iinputs/reference/shims/stlp_nodealloc
// stlport
//
// Retail 0x00694570, 315 bytes through the RET at +0x13A. Audio file cache
// loader thread: until the stop flag at +0x44 is set, take the mutex at +0x48
// (500 ms wait), pick the first pending entry from the three priority lists
// (2 down to 0), make it resident when its use count is zero, keep a handle to
// it, pop the list entry, then read it outside the lock and sleep 1 ms.
// Only caller: the stdcall thread wrapper at 0x00694700 through ILT 0x000279A8.
// Identity stays address-derived.
//
// Codegen: begin() compared against end() with the use count read into a
// named int local reproduces retail's sentinel-in-ECX / begin-in-EAX
// allocation at +0x75 (the earlier end-first and empty() spellings left a
// three or four byte register exchange there). The count-local form was
// carried from the Open-BFME-2 donor
// Code/GameEngineDevice/Source/MilesAudioDevice/AudioFileCacheLoader.cpp
// (AudioFileCache::rva000A8437); layouts and callee identities are BFME 1's.
#include <list>

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *, unsigned long);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *);
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long);

class Gen0002857E
{
public:
	char m_beforeCount[0x34];
	int m_count;
};

class Gen0002857EOwner
{
public:
	void Rva00693B00(Gen0002857E *value);
	void Rva00694230(Gen0002857E *value);
};

class Rva00691140Handle
{
public:
	Rva00691140Handle &operator=(const Rva00691140Handle &other);
	Gen0002857E *m_target;
};

class Rva006910F0Handle
{
public:
	Rva006910F0Handle();
	Rva006910F0Handle(Gen0002857E *target);
	~Rva006910F0Handle();
	Gen0002857E *m_target;
};

class Rva006915E0
{
public:
	Rva006915E0() : m_live(false) {}
	unsigned long acquire(void *mutex)
	{
		m_object = mutex;
		unsigned long status = WaitForSingleObject(mutex, 500);
		if (status != 0x102)
			m_live = true;
		return status;
	}
	~Rva006915E0() { release(); }
	void release()
	{
		if (m_live)
		{
			ReleaseMutex(m_object);
			m_live = false;
		}
	}
	void *m_object;
	bool m_live;
};

class Rva00694570
{
public:
	unsigned long run();

	char m_beforeRequests[0x14];
	_STL::list<Gen0002857E *> m_requests[3];
	char m_beforeStop[0x24];
	bool m_stop;
	void *m_context;
};

unsigned long Rva00694570::run()
{
	while (!m_stop)
	{
		Gen0002857E *selected = 0;
		Rva006910F0Handle handle;
		{
			Rva006915E0 lock;
			if (lock.acquire(m_context) != 0x102)
			{
				for (int priority = 2; !selected && priority >= 0; --priority)
				{
					_STL::list<Gen0002857E *> &requests = m_requests[priority];
					_STL::list<Gen0002857E *>::iterator it = requests.begin();
					if (it != requests.end())
					{
						selected = *it;
						int count = selected->m_count;
						if (count == 0)
							reinterpret_cast<Gen0002857EOwner *>(this)->Rva00693B00(selected);
						*reinterpret_cast<Rva00691140Handle *>(&handle) =
							reinterpret_cast<const Rva00691140Handle &>(Rva006910F0Handle(selected));
						requests.pop_front();
					}
				}
			}
		}
		if (selected)
			reinterpret_cast<Gen0002857EOwner *>(this)->Rva00694230(selected);
		Sleep(1);
	}
	return 0;
}
