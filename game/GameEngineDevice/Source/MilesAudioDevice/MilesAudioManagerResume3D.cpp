// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// BFME's pauseAudio (0x006A8540) and resumeAudio (0x006A8970) both call the
// private Miles helper at 0x0069A920 through the 0x0002E668 thunk.  The
// callers pass the manager in ECX and the address of their PlayingAudioRef
// local as the sole stack argument; the helper returns with ret 4.
//
// This is a BFME helper, not the one-argument Zero Hour resumeAudio method.
// The extra handle-state table and four pause flags are the BFME layout seen
// in the matched MilesAudioManager stopAudio sibling.

extern "C" __declspec(dllimport) int __stdcall AIL_3D_sample_status(
	void *sample);
extern "C" __declspec(dllimport) void __stdcall AIL_stop_3D_sample(
	void *sample);
extern "C" __declspec(dllimport) void __stdcall AIL_resume_3D_sample(
	void *sample);

enum PlayingAudioType
{
	PAT_Sample,
	PAT_3DSample,
	PAT_Stream,
	PAT_Invalid
};

class PlayingAudio
{
public:
	char m_prefix[8];
	void *m_milesHandle;
	PlayingAudioType m_type;
	char m_pad010[0x39 - 0x10];
	bool m_requestStop;
	bool m_systemRequestStop;
	bool m_fadeRequestStop;
	bool m_cleanupRequestStop;
};

class PlayingAudioRef
{
public:
	PlayingAudio *m_ptr;
};

class MilesAudioManager
{
public:
	void resume3D(PlayingAudioRef *playingRef);

private:
	char m_pad000[0xB44];
	unsigned char *m_handleState;
};

void MilesAudioManager::resume3D(PlayingAudioRef *playingRef)
{
	PlayingAudioRef *ref = playingRef;
	PlayingAudio *playing = ref->m_ptr;
	PlayingAudioType type = playing->m_type;
	void *sample;

	switch (type)
	{
		case PAT_3DSample:
			sample = playing->m_milesHandle;
			break;
		case PAT_Stream:
		{
			unsigned int handle = (unsigned int)playing->m_milesHandle;
			sample = *(void **)(m_handleState + handle * 64 + 4);
			break;
		}
		default:
			return;
	}

	if (!sample)
		return;

	do
	{
		if (playing->m_requestStop)
			break;
		if (playing->m_systemRequestStop)
			break;
		if (playing->m_fadeRequestStop)
			break;
		if (playing->m_cleanupRequestStop)
			break;
		goto resumePlaying;
	}
	while (false);

	if (AIL_3D_sample_status(sample) != 2)
		AIL_stop_3D_sample(sample);
	return;

resumePlaying:
	{
		if (type == PAT_Stream)
		{
			unsigned int handle = (unsigned int)playing->m_milesHandle;
			unsigned char *state = m_handleState + handle * 64;
			if (state[1])
				return;
			if (AIL_3D_sample_status(*(void **)(state + 4)) == 8)
				return AIL_resume_3D_sample(*(void **)(state + 4));
		}
		else if (AIL_3D_sample_status(ref->m_ptr->m_milesHandle) == 8)
			return AIL_resume_3D_sample(ref->m_ptr->m_milesHandle);

		return;
	}
}
