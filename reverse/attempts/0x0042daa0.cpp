// ?bfmeIsBlocked@FXList@@QAE_NXZ
// partial score=0.82 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FXList play-cull gate at 0x0042DAA0 (188B).
// CullingInfo writes TrackingSeconds to +0x14, StartCullingAbove to +0x1C,
// CullAllAbove to +0x20.  Default ctor leaves +0x14 at 0 (gate off).
// Static doFXObj skips the play when this returns true.
// Node expire is an inlined unlink plus the 12-byte node allocator
// (stdcall, count=1).  Insert is the 3-arg STLport helper at 0x0009A3E0.

typedef unsigned int UnsignedInt;

extern int GetGameClientRandomValue(int lo, int hi, char *file, int line);

struct PlayTimeNode
{
	PlayTimeNode *next;
	PlayTimeNode *prev;
	UnsignedInt value;
};

class PlayTimeList
{
public:
	UnsignedInt size() const;
	void putNode(PlayTimeNode *node, UnsignedInt count);
	PlayTimeNode **insert(PlayTimeNode **out, PlayTimeNode *pos, const UnsignedInt *value);

	PlayTimeNode *sentinel;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
	unsigned char m_pad[0x3C];
public:
	UnsignedInt m_frame;
};

extern GameLogic *TheBfmeGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXList
{
public:
	bool bfmeIsBlocked();

private:
	unsigned char m_pad00[0x14];
	UnsignedInt m_trackingFrames;
	PlayTimeList m_playTimes;
	UnsignedInt m_startCullingAbove;
	UnsignedInt m_cullAllAbove;
};

// ?bfmeIsBlocked@FXList@@QAE_NXZ
bool FXList::bfmeIsBlocked()
{
	if (!m_trackingFrames)
		return false;

	UnsignedInt frame = TheBfmeGameLogic->m_frame;
	PlayTimeList *times = &m_playTimes;
	PlayTimeNode *node = times->sentinel->next;

	while (node != times->sentinel)
	{
		if (node->value >= frame - m_trackingFrames)
			break;

		PlayTimeNode *prev = node->prev;
		PlayTimeNode *next = node->next;
		prev->next = next;
		next->prev = prev;
		times->putNode(node, 1);
		node = next;
	}

	UnsignedInt n = times->size();
	UnsignedInt startCull = m_startCullingAbove;
	if (n > startCull)
		return true;

	UnsignedInt cullAll = m_cullAllAbove;
	if (n <= cullAll)
	{
		PlayTimeNode *out;
		times->insert(&out, times->sentinel, &frame);
		return false;
	}

	UnsignedInt q = (n - cullAll) / (startCull - cullAll);
	if (GetGameClientRandomValue(0, (int)q,
		"F:\\bfme\\Code\\gameengine\\Source\\GameClient\\FXList.cpp", 0x845))
	{
		PlayTimeNode *out;
		times->insert(&out, times->sentinel, &frame);
		return false;
	}
	return true;
}
