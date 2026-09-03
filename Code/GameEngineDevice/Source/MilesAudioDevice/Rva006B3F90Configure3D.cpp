// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// The BFME audio wrapper reaches this helper with a playing-audio wrapper and
// a world position.  Keep these layouts local: the wrapper is not the public
// AudioEventRTS object used by the common audio TUs.

struct Rva006B3F90AudioInfo
{
	struct List
	{
		void *m_begin;
		void *m_end;
	};

	char m_pad00[0x38];
	unsigned char m_type;
	char m_pad39[0x3b];
	float m_minDistance;
	float m_maxDistance;
	char m_pad7c[0x10];
	List m_list;
};

struct Rva006B3F90AudioEvent
{
	char m_pad00[8];
	Rva006B3F90AudioInfo *m_audioInfo;
	char m_pad0c[0x1c];
	int m_kind;
};

struct Rva006B3F90Inner
{
	char m_pad00[8];
	int m_index;
	int m_type;
	char m_pad10[4];
	Rva006B3F90AudioEvent *m_audioEvent;
};

struct Rva006B3F90Wrapper
{
	Rva006B3F90Inner *m_inner;
};

struct Rva006B3F90Settings
{
	char m_pad00[0x38];
	int m_globalRange;
	char m_pad3c[0x40];
	float m_minVolume;
};

struct Rva006B3F90SampleEntry
{
	char m_pad00[4];
	unsigned int m_sample;
	char m_pad08[0x38];
};

extern void j_0000b43d();
extern void j_000091ba();
extern void j_000173af();

extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_distances(
	unsigned int sample, float minDistance, float maxDistance);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_position(
	unsigned int sample, float x, float y, float z);

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Rva006B3F90Owner
{
public:
	void configure3D(Rva006B3F90Wrapper * volatile wrapper, const Coord3D *position);

private:
	char m_pad00[0x0c];
	Rva006B3F90Settings *m_settings;
	char m_pad10[0xb34];
	Rva006B3F90SampleEntry *m_samples;

	void initFilters3D(Rva006B3F90Wrapper *wrapper, const Coord3D *position);
};

void Rva006B3F90Owner::configure3D(
	Rva006B3F90Wrapper * volatile wrapper, const Coord3D *position)
{
	unsigned int sample;
	Rva006B3F90Inner *inner = wrapper->m_inner;

	switch (inner->m_type)
	{
		case 1:
			sample = inner->m_index;
			break;
		case 2:
			sample = m_samples[inner->m_index].m_sample;
			break;
		default:
			sample = 0;
			break;
	}

	{
		Rva006B3F90AudioEvent *event = inner->m_audioEvent;
		Rva006B3F90AudioInfo *info = event->m_audioInfo;
		Rva006B3F90AudioInfo::List *list = &info->m_list;
		if (list->m_begin != list->m_end)
		{
			typedef void (Rva006B3F90Owner::*Process)(void *, int);
			union
			{
				void (__cdecl *freeProcess)();
				Process memberProcess;
			} process;
			process.freeProcess = ::j_0000b43d;
			(this->*process.memberProcess)(&event->m_audioInfo, event->m_kind);
		}
	}

	typedef float (Rva006B3F90AudioEvent::*GetVolume)() const;
	union
	{
		float (__cdecl *freeGetVolume)();
		GetVolume memberGetVolume;
	} getVolume;
	getVolume.freeGetVolume = reinterpret_cast<float (__cdecl *)()>(::j_000173af);
	float maxDistance;
	if ((inner->m_audioEvent->m_audioInfo->m_type & 8) != 0 ||
		(inner->m_audioEvent->*getVolume.memberGetVolume)() > m_settings->m_minVolume)
		maxDistance = static_cast<float>(m_settings->m_globalRange);
	else
		maxDistance = inner->m_audioEvent->m_audioInfo->m_maxDistance;

	AIL_set_3D_sample_distances(
		sample, inner->m_audioEvent->m_audioInfo->m_minDistance, maxDistance * 2.0f);
	AIL_set_3D_position(sample, position->x, position->y, -position->z);

	typedef void (Rva006B3F90Owner::*InitFilters)(
		Rva006B3F90Wrapper *, const Coord3D *);
	union
	{
		void (__cdecl *freeInitFilters)();
		InitFilters memberInitFilters;
	} initFilters;
	initFilters.freeInitFilters = ::j_000091ba;
	(this->*initFilters.memberInitFilters)(wrapper, position);
}
