// cl: /DNDEBUG /MD /EHsc
// readable body of ?setID@Drawable@@QAEXW4DrawableID@@@Z: Code/GameEngine/Source/GameClient/Drawable.cpp

typedef unsigned char UnsignedByte;
enum DrawableID
{
	INVALID_DRAWABLE_ID = 0
};

class Drawable;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameClient.h
class GameClient
{
public:
	void removeDrawableFromLookupTable(Drawable *draw);
	void addDrawableToLookupTable(Drawable *draw);
};

extern GameClient *TheGameClient;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	void setDrawableID(DrawableID id);
};

struct DrawableAudioEvent
{
	void *m_vtable;
	AudioEventRTS m_event;
};

// The field names and offsets below are limited to what the retail setID body
// itself proves.  The three audio holders occupy consecutive pointer slots and
// each embeds its AudioEventRTS at +4.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	void setID(DrawableID id);

private:
	UnsignedByte m_bfmePad000[0x100];
	DrawableID m_id;
	UnsignedByte m_bfmePad104[0x40];
	DrawableAudioEvent *m_audioEvents[3];
};

void Drawable::setID(DrawableID id)
{
	if (m_id == id)
		return;

	if (m_id != INVALID_DRAWABLE_ID)
		TheGameClient->removeDrawableFromLookupTable(this);

	m_id = id;
	if (m_id != INVALID_DRAWABLE_ID)
	{
		TheGameClient->addDrawableToLookupTable(this);

		if (m_audioEvents[0])
			m_audioEvents[0]->m_event.setDrawableID(m_id);
		if (m_audioEvents[1])
			m_audioEvents[1]->m_event.setDrawableID(m_id);
		if (m_audioEvents[2])
			m_audioEvents[2]->m_event.setDrawableID(m_id);
	}
}
