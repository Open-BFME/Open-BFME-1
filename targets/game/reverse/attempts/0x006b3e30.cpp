// ?start@Rva006B3E30Owner@@QAE_NPAURva006B3E30PlayingRef@@@Z
// partial score=0.9852 date=2026-10-10
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
class AsciiString;
extern const AsciiString Rva01336E50EmptyString;

extern void j_0001978b(void);
extern void j_00021ff3(void);
class Rva006B1B40PlayingAudioRef;
class Rva006B1B40MilesAudioManager {
public:
	void rva006B1B40InitFilters(Rva006B1B40PlayingAudioRef *);
};
class Rva006A8210Owner { public: void dispatch(int, int); };

extern "C" __declspec(dllimport) void __stdcall AIL_init_sample(unsigned int sample);
extern "C" __declspec(dllimport) void *__stdcall AIL_register_EOS_callback(
	unsigned int sample, void (*callback)(void));
extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_file(
	unsigned int sample, void *data, int flags);
extern "C" __declspec(dllimport) void __stdcall AIL_start_sample(unsigned int sample);
extern "C" __declspec(dllimport) void __stdcall AIL_resume_sample(unsigned int sample);
extern "C" __declspec(dllimport) void __stdcall AIL_stop_sample(unsigned int sample);

struct Rva006B3E30Info
{
	char m_pad00[0x8c];
	struct List { int m_begin; int m_end; } m_list;
};

struct Rva006B3E30Event
{
	char m_pad00[8];
	Rva006B3E30Info *m_info;
	char m_pad0c[0x1c];
	int m_kind;
	char m_pad2c[0x1c];
	bool m_started;
};

struct Rva006B3E30File
{
	char m_pad00[0x2c];
	void *m_data;
};

struct Rva006B3E30EventRef {
	Rva006B3E30Event *m_ptr;
	Rva006B3E30Event *operator->() const { return m_ptr; }
};
struct Rva006B3E30FileRef {
	Rva006B3E30File *m_ptr;
	bool isOpen() const { return m_ptr != 0; }
	void *fileData() const { return m_ptr ? m_ptr->m_data : 0; }
	const void *fileName() const { return m_ptr ? m_ptr : (const void *)&Rva01336E50EmptyString; }
};

struct Rva006B3E30Playing
{
	char m_pad00[8];
	unsigned int m_sample;
	int m_type;
	char m_pad10[4];
	Rva006B3E30EventRef m_event;
	Rva006B3E30FileRef m_file;
	char m_pad1c[0x1d];
	bool m_state39;
	bool m_state3a;
	bool m_state3b;
	bool m_state3c;

	const void *fileName() const
	{
		return m_file.fileName();
	}
};

struct Rva006B3E30PlayingRef
{
	Rva006B3E30Playing *m_playing;
	Rva006B3E30Playing *operator->() const { return m_playing; }
};

class Rva006B3E30Owner
{
public:
	bool start(Rva006B3E30PlayingRef *ref);
	void initFilters(Rva006B3E30PlayingRef *ref) {
		((Rva006B1B40MilesAudioManager *)this)->rva006B1B40InitFilters((Rva006B1B40PlayingAudioRef *)ref);
	}
	void dispatch(void *entry, int kind) {
		((Rva006A8210Owner *)this)->dispatch((int)entry, kind);
	}
	void touch(const void *value) {
		typedef void (Rva006B3E30Owner::*Call)(const void *);
		union { void (*function)(); Call member; } target;
		target.function = j_00021ff3;
		(this->*target.member)(value);
	}

private:
	char m_pad00[0x604];
	int m_field604;
};


// Ported from Open BFME 2 Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp.
bool Rva006B3E30Owner::start(Rva006B3E30PlayingRef *ref)
{
	Rva006B3E30PlayingRef &playing = *ref;
	unsigned int sample = playing->m_sample;
	Rva006B3E30EventRef &event = playing->m_event;
	AIL_init_sample(sample);
	AIL_register_EOS_callback(sample, j_0001978b);
	initFilters(ref);
	if (playing->m_file.isOpen())
	{
		Rva006B3E30Info *info = event->m_info;
		Rva006B3E30Info::List *list = &info->m_list;
		if (list->m_begin != list->m_end)
			dispatch(&event->m_info, event->m_kind);
		void *data = playing->m_file.fileData();
		AIL_set_sample_file(sample, data, 0);
		AIL_start_sample(sample);
		event->m_started = true;
		if (playing->m_event->m_kind != 2 && playing->m_event->m_kind != m_field604)
			playing->m_state3b = true;
		else
			playing->m_state3b = false;
		if (!playing->m_state39 && !playing->m_state3a && !playing->m_state3b && !playing->m_state3c)
			AIL_resume_sample(playing->m_sample);
		else
			AIL_stop_sample(playing->m_sample);
		touch(playing->m_file.fileName());
		return true;
	}
	return false;
}
