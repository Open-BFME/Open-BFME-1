// A flag taken away with a
// side effect when it is the tenth one, and a search that marks the first cell
// carrying a given key.

// BfmeThingYX::bfmePickYX (retail 0x00699E50) lives in Rva0069A6F0SetReverb.cpp,
// beside its caller setReverb, which keeps ECX live across the call only when
// the callee body is visible.

class BfmeJobYY
{
public:
	unsigned char m_bfmeHead[0x34];		// 0x00
	int m_bfmeDelay;			// 0x34
	unsigned char m_bfmeState;		// 0x38
};

class BfmeThingYY
{
public:
	void bfmeClearYY(unsigned int bit);

private:
	unsigned char m_bfmeHead[0x68];		// 0x000
	BfmeJobYY *m_bfmeJob;			// 0x068
	unsigned char m_bfmeGap[0xa8];		// 0x06c
	unsigned int m_bfmeFlags;		// 0x114
};

void BfmeThingYY::bfmeClearYY(unsigned int bit)
{
	m_bfmeFlags &= ~bit;

	if (bit == 0x10)
	{
		BfmeJobYY *job = m_bfmeJob;

		if (job != 0)
		{
			job->m_bfmeDelay = 10;
			m_bfmeJob->m_bfmeState = 2;
		}
	}
}

// ScriptEngine::setSequentialTimer(Object *, Int) (retail 0x00339980, ILT
// 0x00044A1C; ilt_oracle CONFIRMED exact): the first sequential script whose
// object ID matches gets its frames-to-wait. TU-local layout view.
class Object
{
public:
	unsigned char m_bfmeHead[0x74];		// 0x00
	int m_bfmeID;				// 0x74
};

class Team;

struct SequentialScript
{
	unsigned char m_bfmeHead[4];		// 0x00
	Team *m_teamToExecOn;			// 0x04
	int m_objectID;				// 0x08
	unsigned char m_bfmeBody[0x14];		// 0x0c
	int m_framesToWait;			// 0x20
};

class ScriptEngine
{
public:
	void setSequentialTimer(Object *obj, int frameCount);
	void setSequentialTimer(Team *team, int frameCount);

private:
	unsigned char m_bfmeHead[0xc];		// 0x00
	SequentialScript **m_bfmeBegin;		// 0x0c
	SequentialScript **m_bfmeEnd;		// 0x10
};

void ScriptEngine::setSequentialTimer(Object *obj, int frameCount)
{
	if (obj == 0)
		return;

	SequentialScript **end = m_bfmeEnd;
	int key = obj->m_bfmeID;
	SequentialScript **at = m_bfmeBegin;

	while (at != end)
	{
		SequentialScript *seq = *at;

		if (seq != 0 && seq->m_objectID == key)
		{
			seq->m_framesToWait = frameCount;
			return;
		}

		++at;
	}
}

// ScriptEngine::setSequentialTimer(Team *, Int) (retail 0x003399D0, ILT
// 0x00010DC5; ilt_oracle CONFIRMED exact): the Team overload, matched by the
// script's m_teamToExecOn. doTeamIdleForFramecount calls it through the ILT.
void ScriptEngine::setSequentialTimer(Team *team, int frameCount)
{
	if (team == 0)
		return;

	SequentialScript **at = m_bfmeBegin;
	SequentialScript **end = m_bfmeEnd;

	while (at != end)
	{
		SequentialScript *seq = *at;

		if (seq != 0 && seq->m_teamToExecOn == team)
		{
			seq->m_framesToWait = frameCount;
			return;
		}

		++at;
	}
}
