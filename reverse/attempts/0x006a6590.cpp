// ?d_006a6590@@YAXXZ
// partial score=0.12 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Reconstruction attempt for retail 0x006A6590 (777 B), thiscall bool(AudioEventRTS*).
// Grounded in matched neighbours: AsciiString::compare (0x0005FEB0, through ILT
// 0x000220C5), AudioEventRTS::isPositionalAudio (0x000B28F0, through ILT
// 0x0000F380), AudioEventRTS::setHandleToKill (0x000B2310, through ILT 0x00006302).
// The two playing-list scans below mirror MilesAudioManager::doesViolateLimit
// from reference/CnC_Generals_Zero_Hour, adapted for the BFME self-exclusion
// check observed in the byte diff (cmp esi,ebp after the compare). The trailing
// request-list scan (through ILT 0x0000FE93, retail 0x006A0400, still an
// unclaimed gen-tgrid hashtable body) is NOT reconstructed with confidence and
// is left as a stub so this file compiles for a divergence probe.

class AsciiString
{
public:
	int compare(const AsciiString &other) const;
};

class AudioEventRTS
{
public:
	bool isPositionalAudio() const;
	void setHandleToKill(unsigned int handle);
};

struct BfmeListNode
{
	BfmeListNode *m_next;
	BfmeListNode *m_prev;
	void *m_value;
};

static inline AsciiString *EventNameOf(AudioEventRTS *ev)
{
	return (AsciiString *)((char *)ev + 0x14);
}

static inline AudioEventRTS *AudioEventRTSOf(void *playingAudio)
{
	return *(AudioEventRTS **)((char *)playingAudio + 0x14);
}

static inline unsigned int PlayingHandleOf(AudioEventRTS *ev)
{
	return *(unsigned int *)((char *)ev + 0xc);
}

class MilesAudioManager
{
public:
	bool doesViolateLimit(AudioEventRTS *event) const;

private:
	char m_pad[0x9c8];
	BfmeListNode *m_playingSoundsHead;
	BfmeListNode *m_playing3DSoundsHead;
};

static int scanList(BfmeListNode *head, AudioEventRTS *event, int &totalCount)
{
	for (BfmeListNode *node = head->m_next; node != head; node = node->m_next)
	{
		void *playingAudio = node->m_value;
		AudioEventRTS *candidate = AudioEventRTSOf(playingAudio);
		if (EventNameOf(candidate)->compare(*EventNameOf(event)) == 0)
		{
			if (candidate == event)
				continue;
			if (totalCount == 0)
				event->setHandleToKill(PlayingHandleOf(candidate));
			++totalCount;
		}
	}
	return totalCount;
}

bool MilesAudioManager::doesViolateLimit(AudioEventRTS *event) const
{
	const int *info = *(const int **)((const char *)event + 8);
	if (!info)
		return false;
	int limit = *(const int *)((const char *)info + 0x30);
	if (limit == 0)
		return false;

	int totalCount = 0;
	if (!event->isPositionalAudio())
		scanList(m_playingSoundsHead, event, totalCount);
	else
		scanList(m_playing3DSoundsHead, event, totalCount);

	// Request-list hashtable scan not reconstructed; stub for probe purposes.
	if (totalCount < limit)
	{
		event->setHandleToKill(0);
		return false;
	}
	return true;
}
