// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Miles reverb switch: stream/sample reverb levels or 3D effects level.

extern "C" __declspec(dllimport) void __stdcall AIL_set_stream_reverb_levels(
	int handle, float dry, float wet);
extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_reverb_levels(
	int handle, float dry, float wet);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_effects_level(
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

// The playing-handle lookup at retail 0x00699E50, address-named
// BfmeThingYX::bfmePickYX: a reading chosen by the sort of playing handle.
// setReverb keeps ECX live across the call, so the body sits in this TU.
struct BfmeSlotYX
{
	int m_bfmeFirst;			// 0x00
	int m_bfmeSecond;			// 0x04
	unsigned char m_bfmeBody[0x38];		// 0x08
};

struct BfmeItemYX
{
	unsigned char m_bfmeHead[8];		// 0x0
	int m_bfmeValue;			// 0x8
	int m_bfmeKind;				// 0xc
};

struct BfmeBoxYX
{
	BfmeItemYX *m_bfmeItem;			// 0x0
};

class BfmeThingYX
{
public:
	int bfmePickYX(BfmeBoxYX *box) const;

private:
	unsigned char m_bfmeHead[0xb44];	// 0x000
	BfmeSlotYX *m_bfmeTable;		// 0xb44
};

int BfmeThingYX::bfmePickYX(BfmeBoxYX *box) const
{
	BfmeItemYX *item = box->m_bfmeItem;

	switch (item->m_bfmeKind)
	{
		case 1:
			return item->m_bfmeValue;

		case 2:
			return m_bfmeTable[item->m_bfmeValue].m_bfmeSecond;

		case 4:
			return 0;
	}

	return 0;
}

class Rva0069A6F0Owner
{
public:
	void setReverb(Rva0069A6F0Playing **pp);

	char m_bytes[0xb44];
	char *m_samplePool;
};

void Rva0069A6F0Owner::setReverb(Rva0069A6F0Playing **pp)
{
	Rva0069A6F0Playing *p = *pp;
	switch (p->m_type)
	{
	case 3:
		if (m_bytes[0x633])
		{
			Rva0069A6F0AudioInfo *info = p->m_event->m_info;
			AIL_set_stream_reverb_levels(p->m_handle, info->m_dry, info->m_wet);
		}
		else
			AIL_set_stream_reverb_levels(p->m_handle, 1.0f, 0.0f);
		return;
	case 0:
		if (m_bytes[0x633])
		{
			Rva0069A6F0AudioInfo *info = p->m_event->m_info;
			AIL_set_sample_reverb_levels(p->m_handle, info->m_dry, info->m_wet);
		}
		else
			AIL_set_sample_reverb_levels(p->m_handle, 1.0f, 0.0f);
		return;
	case 1:
	case 2:
	{
		int handle = reinterpret_cast<const BfmeThingYX *>(this)->bfmePickYX((BfmeBoxYX *)pp);
		if (handle)
		{
			float level;
			if (m_bytes[0x633])
				level = p->m_event->m_info->m_wet * p->m_effectsScale;
			else
				level = 0.0f;
			AIL_set_3D_sample_effects_level(handle, level);
		}
		return;
	}
	}
}
