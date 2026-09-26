// cl: /DNDEBUG /MD
//
// Retail 0x006ABFD0: thiscall taking a slot whose first dword is a PlayingAudio-
// shaped object.  Type at +0xC equal to 2 fails.  Otherwise release the file
// holder at +0x18, test hasMoreLoops on the event at +0x14, run a second event
// helper, then add the slot.

class Rva006ABFD0File
{
public:
	void release();
};

extern float g_Va0112E8B0;

class Rva006ABFD0Event
{
public:
	bool hasMoreLoops() const;
	void advance();
	void advanceNextPlayPortion();
	void clamp(float low, float high);

	char m_pad[0x44];
	unsigned char m_flag;
};

class Rva006ABFD0Playing
{
public:
	char m_pad00[0xC];
	int m_type;
	char m_pad10[4];
	Rva006ABFD0Event *m_event;
	Rva006ABFD0File m_file;
};

class Rva006ABFD0Slot
{
public:
	Rva006ABFD0Playing *m_playing;
};

class Rva006ABFD0
{
public:
	bool go(Rva006ABFD0Slot *slot);
	void goLoop(Rva006ABFD0Slot *slot);

private:
	void add(Rva006ABFD0Slot *slot);
};

bool Rva006ABFD0::go(Rva006ABFD0Slot *slot)
{
	if (slot->m_playing->m_type != 2)
	{
		slot->m_playing->m_file.release();
		if (slot->m_playing->m_event->hasMoreLoops())
		{
			slot->m_playing->m_event->advance();
			add(slot);
			return true;
		}
	}
	return false;
}

void Rva006ABFD0::goLoop(Rva006ABFD0Slot *slot)
{
	slot->m_playing->m_event->advance();
	if (slot->m_playing->m_event->hasMoreLoops())
	{
		slot->m_playing->m_event->advanceNextPlayPortion();
		slot->m_playing->m_event->clamp(34.3333321f, g_Va0112E8B0);
		slot->m_playing->m_event->m_flag = 1;
		add(slot);
	}
}
