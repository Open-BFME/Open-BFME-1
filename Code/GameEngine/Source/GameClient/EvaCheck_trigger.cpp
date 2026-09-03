// cl: /O2

// Per-message EvaCheck trigger, retail 0x004223F0. Called from
// Eva::setShouldPlay as checks[msg].trigger(infos[msg], pos).

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct EvaCheckInfo
{
	unsigned m_a;
	unsigned m_framesBetweenChecks;
	unsigned m_framesToExpire;
};

struct EvaCheck
{
	Bool trigger(const EvaCheckInfo *info, const Coord3D *pos);

	Real m_triggeredOnFrame;
	Real m_timeForNextCheck;
	Coord3D m_pos;
	Bool m_alreadyPlayed;
};

Bool EvaCheck::trigger(const EvaCheckInfo *info, const Coord3D *pos)
{
	if (m_triggeredOnFrame > 0.0f)
	{
		Real expire = (Real)info->m_framesToExpire;
		if (expire > m_triggeredOnFrame)
			m_triggeredOnFrame = expire;
		return false;
	}

	m_timeForNextCheck = (Real)info->m_framesBetweenChecks;
	if (pos == 0)
	{
		m_alreadyPlayed = false;
		return true;
	}
	m_alreadyPlayed = true;
	m_pos = *pos;
	return true;
}
