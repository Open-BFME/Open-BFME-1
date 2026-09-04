// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Miles reverb switch: stream/sample reverb levels or 3D effects level.

extern "C" __declspec(dllimport) void __stdcall _AIL_set_stream_reverb_levels(
	int handle, float dry, float wet);
extern "C" __declspec(dllimport) void __stdcall _AIL_set_sample_reverb_levels(
	int handle, float dry, float wet);
extern "C" __declspec(dllimport) void __stdcall _AIL_set_3D_sample_effects_level(
	int handle, float level);

struct Rva0069A6F0AudioInfo
{
	char m_pad[0x7c];
	float m_wet;
	float m_dry;
};

struct Rva0069A6F0AudioEvent
{
	char m_pad[8];
	Rva0069A6F0AudioInfo *m_info;
};

struct Rva0069A6F0Playing
{
	char m_pad00[8];
	int m_handle;
	int m_type;
	char m_pad10[4];
	Rva0069A6F0AudioEvent *m_event;
	char m_pad18[0x2c - 0x18];
	float m_effectsScale;
};

class Rva0069A6F0Owner
{
public:
	void setReverb(Rva0069A6F0Playing **pp);
	int getHandle(Rva0069A6F0Playing **pp);

	char m_bytes[0xb44];
	char *m_samplePool;
};

int Rva0069A6F0Owner::getHandle(Rva0069A6F0Playing **pp)
{
	Rva0069A6F0Playing *p = *pp;
	switch (p->m_type)
	{
	case 1:
		return p->m_handle;
	case 2:
		return *(int *)(m_samplePool + (p->m_handle << 6) + 4);
	default:
		return 0;
	}
}

void Rva0069A6F0Owner::setReverb(Rva0069A6F0Playing **pp)
{
	Rva0069A6F0Playing *p = *pp;
	switch (p->m_type)
	{
	case 0:
		if (m_bytes[0x633])
		{
			Rva0069A6F0AudioInfo *info = p->m_event->m_info;
			_AIL_set_stream_reverb_levels(p->m_handle, info->m_dry, info->m_wet);
		}
		else
			_AIL_set_stream_reverb_levels(p->m_handle, 1.0f, 0.0f);
		return;
	case 1:
		if (m_bytes[0x633])
		{
			Rva0069A6F0AudioInfo *info = p->m_event->m_info;
			_AIL_set_sample_reverb_levels(p->m_handle, info->m_dry, info->m_wet);
		}
		else
			_AIL_set_sample_reverb_levels(p->m_handle, 1.0f, 0.0f);
		return;
	case 2:
	case 3:
	{
		int handle = getHandle(pp);
		if (handle)
		{
			float level;
			if (m_bytes[0x633])
				level = p->m_event->m_info->m_wet * p->m_effectsScale;
			else
				level = 0.0f;
			_AIL_set_3D_sample_effects_level(handle, level);
		}
		return;
	}
	}
}
