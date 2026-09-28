// ?start@Rva006B3E30Owner@@QAE_NPAURva006B3E30PlayingRef@@@Z
// partial score=0.3333333 date=2026-09-28
class AsciiString;
extern const AsciiString Rva01336E50EmptyString;

extern void j_0001978b(void);

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
	int m_begin;
	int m_end;
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

struct Rva006B3E30Playing
{
	char m_pad00[8];
	unsigned int m_sample;
	int m_type;
	char m_pad10[4];
	Rva006B3E30Event *m_event;
	Rva006B3E30File *m_file;
	char m_pad1c[0x1d];
	bool m_state39;
	bool m_state3a;
	bool m_state3b;
	bool m_state3c;

	const void *fileName() const
	{
		if (m_file != 0)
			return m_file;
		return &Rva01336E50EmptyString;
	}
};

struct Rva006B3E30PlayingRef
{
	Rva006B3E30Playing *m_playing;
};

class Rva006B3E30Owner
{
public:
	bool start(Rva006B3E30PlayingRef *ref);
	void initFilters(Rva006B3E30PlayingRef *ref);
	void dispatch(void *entry, int kind);
	void touch(const void *value);

private:
	char m_pad00[0x604];
	int m_field604;
};

#pragma comment(linker, "/alternatename:?initFilters@Rva006B3E30Owner@@QAEXPAVRva006B3E30PlayingRef@@@Z=?j_00016928@@YAXXZ")
#pragma comment(linker, "/alternatename:?dispatch@Rva006B3E30Owner@@QAEXPAXH@Z=?j_0000b43d@@YAXXZ")
#pragma comment(linker, "/alternatename:?touch@Rva006B3E30Owner@@QAEXPBX@Z=?j_00021ff3@@YAXXZ")

bool Rva006B3E30Owner::start(Rva006B3E30PlayingRef *ref)
{
	Rva006B3E30Owner *owner = this;
	Rva006B3E30Playing *playing = ref->m_playing;
	unsigned int sample = playing->m_sample;
	AIL_init_sample(sample);
	AIL_register_EOS_callback(sample, j_0001978b);
	owner->initFilters(ref);

	if (ref->m_playing->m_file != 0)
	{
		Rva006B3E30Event *event = playing->m_event;
		Rva006B3E30Info *info = event->m_info;
		int begin = info->m_begin;
		if (begin != info->m_end)
			owner->dispatch(&event->m_info, event->m_kind);

		void *data = ref->m_playing->m_file != 0
			? ref->m_playing->m_file->m_data : 0;
		AIL_set_sample_file(sample, data, 0);
		AIL_start_sample(sample);
		playing->m_event->m_started = true;

		Rva006B3E30Playing *current = ref->m_playing;
		if (current->m_event->m_kind != 2 &&
			current->m_event->m_kind != owner->m_field604)
			current->m_state3b = true;
		else
			current->m_state3b = false;

		if (!current->m_state39 && !current->m_state3a &&
			!current->m_state3b && !current->m_state3c)
			AIL_resume_sample(current->m_sample);
		else
			AIL_stop_sample(current->m_sample);

		owner->touch(ref->m_playing->fileName());
		return true;
	}
	return false;
}
