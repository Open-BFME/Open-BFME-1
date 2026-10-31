// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// W3DRadar::drawEvents (retail 0x006C3170, 729 bytes, ret 0x14).
//
// Identity: tools/ilt_oracle.py CONFIRMS ?drawEvents@W3DRadar@@IAEXHHHHH@Z at
// this body (the four-int ZH spelling is CONTRADICTED); the matched radar draw
// at 0x006C4A50 (Rva006C4A50.cpp) passes five ints.  The fifth is unused.
//
// Structure follows Zero Hour's W3DRadar::drawEvents (static "RadarEvent"
// AudioEventRTS played once per event, inlined Radar::radarToPixel) with the
// BFME ping handle of the Open BFME 2 donor W3DRadarDrawEvents.cpp
// (open-bfme-2 b5a7b8290): a missing ping is fetched by event type from the
// window-override source at 0x012F4B98 (getters 0x006C1C10..0x006C1CD0, in the
// donor's PingBeacon/Attack/Generic/Information/Upgrade order), moved to the
// event's radar pixel, and faded once the event's expiry frame has passed.
//
// Event record (stride 0x50 from this+0x28): +0x00 type, +0x04 active,
// +0x10 expiry frame, +0x40 radar cell, +0x48 sound played, +0x4C ping handle.

#include "ascii_string.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, Int ownerID);
	virtual void slot00();
	~AudioEventRTS();

private:
	unsigned char m_unmodelled[0x6C];
};

class AudioClient
{
public:
#define AUDIO_SLOT(n) virtual void audioSlot##n();
	AUDIO_SLOT(00) AUDIO_SLOT(04) AUDIO_SLOT(08) AUDIO_SLOT(0C)
	AUDIO_SLOT(10) AUDIO_SLOT(14) AUDIO_SLOT(18) AUDIO_SLOT(1C)
	AUDIO_SLOT(20) AUDIO_SLOT(24) AUDIO_SLOT(28) AUDIO_SLOT(2C)
	AUDIO_SLOT(30) AUDIO_SLOT(34) AUDIO_SLOT(38) AUDIO_SLOT(3C)
	AUDIO_SLOT(40)
	virtual void addAudioEvent(AudioEventRTS *event);
#undef AUDIO_SLOT
};

class AudioManager;
extern AudioManager *TheAudio;
#define TheAudioClientUpdate ((AudioClient *)TheAudio)

class GameClientFrameView
{
public:
#define CLIENT_SLOT(n) virtual void clientSlot##n();
	CLIENT_SLOT(00) CLIENT_SLOT(04) CLIENT_SLOT(08) CLIENT_SLOT(0C)
	CLIENT_SLOT(10) CLIENT_SLOT(14) CLIENT_SLOT(18) CLIENT_SLOT(1C)
	CLIENT_SLOT(20) CLIENT_SLOT(24) CLIENT_SLOT(28) CLIENT_SLOT(2C)
	CLIENT_SLOT(30) CLIENT_SLOT(34) CLIENT_SLOT(38) CLIENT_SLOT(3C)
	CLIENT_SLOT(40) CLIENT_SLOT(44) CLIENT_SLOT(48) CLIENT_SLOT(4C)
	CLIENT_SLOT(50) CLIENT_SLOT(54) CLIENT_SLOT(58) CLIENT_SLOT(5C)
	CLIENT_SLOT(60) CLIENT_SLOT(64)
	virtual UnsignedInt getFrame();
#undef CLIENT_SLOT
};

class GameClient;
extern GameClient *TheGameClient;

// The counted ping object: deleting destructor in slot 0, the reference
// count at +4 (the same counted base the 0x0058C2B0 handle owns).
class Rva0058BF70Base
{
public:
	virtual ~Rva0058BF70Base() {}
	virtual void setPosition(Real x, Real y);
	virtual void fadeOut();
	Int m_value;
};

// Drop one reference; the last one deletes the ping.  The handle passes the
// object as its own argument: retail copies it into ECX only after the null
// test, which a pointer local tested in the same condition does not give.
static __forceinline void releaseCounted(Rva0058BF70Base *object)
{
	if ((object->m_value = object->m_value - 1) <= 0)
		delete object;
}

class Rva0058C2B0RefPtr
{
public:
	Rva0058C2B0RefPtr &operator=(const Rva0058C2B0RefPtr &other)
	{
		if (this != &other)
		{
			if (other.m_ptr)
				++other.m_ptr->m_value;
			if (m_ptr)
				releaseCounted(m_ptr);
			m_ptr = other.m_ptr;
		}
		return *this;
	}
	~Rva0058C2B0RefPtr()
	{
		if (m_ptr)
			releaseCounted(m_ptr);
	}

	Rva0058BF70Base *m_ptr;
};

class Glo012F4B98Type
{
public:
	Rva0058C2B0RefPtr rva006C1C40();
	Rva0058C2B0RefPtr rva006C1C10();
	Rva0058C2B0RefPtr rva006C1C70();
	Rva0058C2B0RefPtr rva006C1CA0();
	Rva0058C2B0RefPtr rva006C1CD0();
};
extern Glo012F4B98Type *Glo012F4B98;

struct Rva006C3170Cell
{
	Int x;
	Int y;
};

enum
{
	MAX_RADAR_EVENTS = 64,
	RADAR_CELL_WIDTH = 128,
	RADAR_CELL_HEIGHT = 128
};

enum RadarEventType
{
	RADAR_EVENT_INFORMATION = 0,
	RADAR_EVENT_GENERIC = 1,
	RADAR_EVENT_UPGRADE = 2,
	RADAR_EVENT_UNDER_ATTACK = 3,
	RADAR_EVENT_BEACON_PULSE = 6,
	RADAR_EVENT_FAKE = 10
};

struct RadarEvent
{
	Int type;
	Bool active;
	char pad05[0x10 - 0x05];
	UnsignedInt expiry;
	char pad14[0x40 - 0x14];
	Rva006C3170Cell radarLoc;
	Bool soundPlayed;
	char pad49[3];
	Rva0058C2B0RefPtr ping;
};

// Radar::radarToPixel, inlined here.
static __forceinline Bool radarToPixel(const Rva006C3170Cell *radar, Rva006C3170Cell *pixel,
	Int radarUpperLeftX, Int radarUpperLeftY, Int radarWidth, Int radarHeight)
{
	if (radar == 0 || pixel == 0)
		return false;
	pixel->x = (radar->x * radarWidth / RADAR_CELL_WIDTH) + radarUpperLeftX;
	pixel->y = ((RADAR_CELL_HEIGHT - 1 - radar->y) * radarHeight / RADAR_CELL_HEIGHT) + radarUpperLeftY;
	return true;
}

class W3DRadar
{
protected:
	void drawEvents(Int pixelX, Int pixelY, Int width, Int height, Int unused);

	char m_pad[0x28];
	RadarEvent m_event[MAX_RADAR_EVENTS];
};

void W3DRadar::drawEvents(Int pixelX, Int pixelY, Int width, Int height, Int unused)
{
	Int i;

	for (i = 0; i < MAX_RADAR_EVENTS; i++)
	{
		if (m_event[i].active == true && m_event[i].type != RADAR_EVENT_FAKE)
		{
			if (m_event[i].soundPlayed == false && m_event[i].type != RADAR_EVENT_BEACON_PULSE)
			{
				static AudioEventRTS eventSound(AsciiString("RadarEvent"), 0);
				TheAudioClientUpdate->addAudioEvent(&eventSound);
			}

			Int type = m_event[i].type;
			m_event[i].soundPlayed = true;
			_ReadWriteBarrier();

			if (m_event[i].ping.m_ptr == 0)
			{
				if (type == RADAR_EVENT_BEACON_PULSE)
					m_event[i].ping = Glo012F4B98->rva006C1C40();
				else if (type == RADAR_EVENT_UNDER_ATTACK)
					m_event[i].ping = Glo012F4B98->rva006C1C10();
				else if (type == RADAR_EVENT_GENERIC)
					m_event[i].ping = Glo012F4B98->rva006C1C70();
				else if (type == RADAR_EVENT_INFORMATION)
					m_event[i].ping = Glo012F4B98->rva006C1CA0();
				else if (type == RADAR_EVENT_UPGRADE)
					m_event[i].ping = Glo012F4B98->rva006C1CD0();
			}

			if (m_event[i].ping.m_ptr)
			{
				Rva006C3170Cell pixel;
				radarToPixel(&m_event[i].radarLoc, &pixel, pixelX, pixelY, width, height);
				m_event[i].ping.m_ptr->setPosition((Real)pixel.x, (Real)pixel.y);
				if (((GameClientFrameView *)TheGameClient)->getFrame() > m_event[i].expiry)
					m_event[i].ping.m_ptr->fadeOut();
			}
		}
	}
}
