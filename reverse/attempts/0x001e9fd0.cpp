// ?privateFireWeapon@Weapon@@QAE_NPBVObject@@PBUCoord3D@@0H1HHHPAH@Z
// partial score=0.33 date=2026-09-04
// cl: /DNDEBUG /MD /O2 /Ob2 /GX-
// Open-BFME5: Weapon::privateFireWeapon, retail 0x001E9FD0 size 1253.
// extraBonusFlags then source, then bitcast WeaponBonus ctor. Stub-only
// (no later locals) emits eax=0x3f800000 stores and edx=extra; the full
// body steals the schedule: frame 0x24 vs 0x20, esi=this not ebp, extra
// loaded after the six stores. Linear helper 0x001E49E0 is ecx=vec
// eax=index edi=source esi=out (144B x87 sin/cos + getGroundHeight).

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Coord2D
{
	float x;
	float y;
};

class WeaponBonus
{
public:
	WeaponBonus()
	{
		unsigned v = 0x3f800000;
		*(unsigned *)&m_a = v;
		*(unsigned *)&m_b = v;
		*(unsigned *)&m_c = v;
		*(unsigned *)&m_d = v;
		*(unsigned *)&m_e = v;
		*(unsigned *)&m_f = v;
	}

	float m_a, m_b, m_c, m_d, m_e, m_f;
};

class ObjectFilter
{
public:
	bool isValid() const;
};

class Drawable
{
public:
	int getBarrelCount(int wslot) const;
};

class Object
{
public:
	virtual void _v00();
	virtual void _v01();
	virtual void _v02();
	virtual void _v03();
	virtual void _v04();
	virtual void _v05();
	virtual void _v06();
	virtual void _v07();
	virtual void _v08();
	virtual void _v09();
	virtual Drawable *getDrawable() const;

	char m_pad[0x38];
	Coord3D m_position;
	char m_pad44[0x1FC - 0x44];
	class FilterSink *m_filterSink;
};

class FilterSink
{
public:
	void apply(ObjectFilter *filter);
};

class GameLogic
{
public:
	unsigned getFrame() const
	{
		return *reinterpret_cast<const unsigned *>(
			reinterpret_cast<const char *>(this) + 0x3c);
	}
	Object *findObjectByID(int id);
};

class TerrainLogic
{
public:
	virtual void _v00();
	virtual void _v01();
	virtual void _v02();
	virtual void _v03();
	virtual void _v04();
	virtual void _v05();
	virtual float getGroundHeight(float x, float y, int layer);
};

class Weapon;
class WeaponTemplate;

class LinearTargets
{
public:
	void aim(int index, const Object *source, Coord3D *out);
	char *m_begin;
	char *m_end;
	char *m_cap;
};

class Scatter2D
{
public:
	Coord2D *m_begin;
	Coord2D *m_end;
	Coord2D *m_cap;
};

class WeaponTemplate
{
public:
	int getDelayBetweenShots(const WeaponBonus &bonus) const;
	void fireWeaponTemplate(
		const Object *source, int wslot, int barrel,
		const Object *victim, const Coord3D *victimPos,
		const WeaponBonus &bonus, int isDetonation, int ignoreRanges,
		Weapon *weapon, int *projectileID, int inflict) const;
	void bfmeTellLO(Weapon *weapon, const Object *source,
		const Object *victim, WeaponBonus *bonus);

	char m_pad000[0x1c];
	float m_requestAssistRange;
	char m_pad020[0x2c - 0x20];
	float m_scatterScalar;
	char m_pad030[0x34 - 0x30];
	Scatter2D m_scatterTargets;
	LinearTargets m_linearTargets;
	char m_pad04c[0x4d0 - 0x4c];
	int m_shotsPerBarrel;
	char m_pad4d4[0x4e8 - 0x4d4];
	ObjectFilter m_filter;
	int m_reloadType;
	char m_pad4f4[0x4f8 - 0x4f4];
	unsigned char m_isLeechRangeWeapon;
	char m_pad4f9[0x50c - 0x4f9];
	int m_timingExtra;
	char m_pad510[0x51c - 0x510];
	unsigned char m_linearGate;
};

class WeaponSet
{
public:
	bool isReloadTimeShared() const;
	Weapon *getWeaponInWeaponSlot(int slot);
};

enum WeaponStatus
{
	READY_TO_FIRE = 0,
	OUT_OF_AMMO = 1,
	BETWEEN_FIRING_SHOTS = 2
};

class Weapon
{
public:
	bool privateFireWeapon(const Object *source, const Coord3D *sourcePos,
		const Object *victim, int victimId, const Coord3D *victimPos,
		int isDetonation, int ignoreRanges, int extraBonusFlags,
		int *projectileID);

	WeaponStatus bfmeComputeStatus(bool *valid) const;
	void computeBonus(const Object *source, unsigned extra, WeaponBonus &bonus) const;
	void processRequestAssistance(const Object *source, const Object *victim);
	void reloadAmmo(const Object *source);
	unsigned getRemainingAmmo(bool countReloadingAsEmpty) const;

	void *m_vptr;
	WeaponTemplate *m_template;
	int m_sourceId;
	int m_wslot;
	unsigned m_status;
	unsigned m_ammoInClip;
	unsigned m_whenWeCanFireAgain;
	unsigned m_whenPreAttackFinished;
	unsigned m_whenLastReloadStarted;
	unsigned m_lastFireFrame;
	unsigned m_projectileStreamID;
	unsigned m_lastFireStamp;
	unsigned m_suspendFXFrame;
	int m_maxShotCount;
	int m_curBarrel;
	int m_numShotsForCurBarrel;
	int *m_scatterBegin;
	int *m_scatterEnd;
	int *m_scatterCap;
	unsigned char m_pitchLimited;
	unsigned char m_pad4d[3];
	unsigned m_leechWeaponRangeActive;
	unsigned m_linearIndex;
	unsigned m_tail;
};

extern GameLogic *TheGameLogic;
extern TerrainLogic *TheTerrainLogic;
extern float g_bfmeZeroCY;

int GetGameLogicRandomValue(int low, int high, char *file, int line);

// ?privateFireWeapon@Weapon@@QAE_NPBVObject@@PBUCoord3D@@0H1HHHPAH@Z
bool Weapon::privateFireWeapon(const Object *source, const Coord3D *sourcePos,
	const Object *victim, int victimId, const Coord3D *victimPos,
	int isDetonation, int ignoreRanges, int extraBonusFlags,
	int *projectileID)
{
	unsigned extra = (unsigned)extraBonusFlags;
	const Object *src = source;
	WeaponBonus bonus;
	computeBonus(src, extra, bonus);

	if (projectileID)
		*projectileID = 0;

	if (!m_template)
		return false;

	const Object *vic = victim;
	if (m_template->m_requestAssistRange != g_bfmeZeroCY && vic)
		processRequestAssistance(src, vic);

	if (m_template->m_isLeechRangeWeapon)
	{
		int timing = (int)(float)m_template->m_timingExtra;
		int one = 1;
		int *add = timing < 1 ? &one : &timing;
		m_leechWeaponRangeActive = TheGameLogic->getFrame() + *add;
	}

	bool cacheOk = true;
	WeaponStatus st = bfmeComputeStatus(&cacheOk);
	if (cacheOk && m_status != (unsigned)st)
		m_status = (unsigned)st;
	if (st != READY_TO_FIRE)
		return false;

	unsigned now = TheGameLogic->getFrame();
	bool reloaded = false;
	int delay = m_template->getDelayBetweenShots(bonus);

	if (m_template->m_filter.isValid())
	{
		Object *srcObj = TheGameLogic->findObjectByID(m_sourceId);
		FilterSink *sink = srcObj ? srcObj->m_filterSink : 0;
		if (sink)
			sink->apply(&m_template->m_filter);
	}

	if (m_ammoInClip == 0)
		return reloaded;

	int barrels = src->getDrawable()->getBarrelCount(m_wslot);
	if (m_curBarrel >= barrels)
	{
		m_curBarrel = 0;
		m_numShotsForCurBarrel = m_template->m_shotsPerBarrel;
	}

	Coord3D *aimed = (Coord3D *)&bonus;
	if (isDetonation)
	{
		m_template->bfmeTellLO(this, src, vic, &bonus);
	}
	else if (m_template->m_linearTargets.m_end != m_template->m_linearTargets.m_begin)
	{
		int n = (int)(m_template->m_linearTargets.m_end
			- m_template->m_linearTargets.m_begin) / 12;
		int i = 0;
		while (i < n)
		{
			m_template->m_linearTargets.aim((int)m_linearIndex, src, aimed);
			if (!m_template->m_linearGate || m_linearIndex)
			{
				m_template->fireWeaponTemplate(src, m_wslot, m_curBarrel,
					vic, aimed, bonus, isDetonation, ignoreRanges,
					this, projectileID, 1);
			}
			int flag = ((int *)(m_template->m_linearTargets.m_begin
				+ m_linearIndex * 12))[2];
			m_linearIndex = (m_linearIndex + 1) % n;
			if (flag)
				break;
			++i;
		}
	}
	else if (m_scatterEnd - m_scatterBegin)
	{
		const Coord3D *pos = victimPos;
		if (vic)
		{
			pos = &vic->m_position;
			vic = 0;
		}
		*aimed = *pos;
		int pick = GetGameLogicRandomValue(
			0,
			(int)(m_scatterEnd - m_scatterBegin) - 1,
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Weapon.cpp",
			2915);
		int index = m_scatterBegin[pick];
		float scalar = m_template->m_scatterScalar;
		Coord2D off = m_template->m_scatterTargets.m_begin[index];
		aimed->x += off.x * scalar;
		aimed->y += off.y * scalar;
		aimed->z = TheTerrainLogic->getGroundHeight(aimed->x, aimed->y, 0);
		m_scatterBegin[pick] = m_scatterEnd[-1];
		--m_scatterEnd;
		m_template->fireWeaponTemplate(src, m_wslot, m_curBarrel,
			vic, aimed, bonus, isDetonation, ignoreRanges,
			this, projectileID, 1);
	}
	else
	{
		m_template->fireWeaponTemplate(src, m_wslot, m_curBarrel,
			vic, victimPos, bonus, isDetonation, ignoreRanges,
			this, projectileID, 1);
	}

	--m_ammoInClip;
	--m_maxShotCount;
	--m_numShotsForCurBarrel;
	m_lastFireStamp = now;
	if (m_numShotsForCurBarrel <= 0)
	{
		++m_curBarrel;
		m_numShotsForCurBarrel = m_template->m_shotsPerBarrel;
	}

	if (getRemainingAmmo(false) == 0)
	{
		if (m_template->m_reloadType == 0)
		{
			reloadAmmo(src);
			reloaded = true;
			return reloaded;
		}
		if (m_status != OUT_OF_AMMO)
			m_status = OUT_OF_AMMO;
		if (!m_template->m_filter.isValid())
			m_whenWeCanFireAgain = 0x7fffffff;
		return reloaded;
	}

	if (m_status != BETWEEN_FIRING_SHOTS)
		m_status = BETWEEN_FIRING_SHOTS;
	m_whenWeCanFireAgain = now + (unsigned)delay;
	m_projectileStreamID = now;

	WeaponSet *ws = (WeaponSet *)((char *)src + 0x264);
	if (ws->isReloadTimeShared())
	{
		for (int slot = 0; slot < 4; ++slot)
		{
			Weapon *w = ws->getWeaponInWeaponSlot(slot);
			if (w)
			{
				w->m_whenWeCanFireAgain = m_whenWeCanFireAgain;
				if (w->m_status != BETWEEN_FIRING_SHOTS)
					w->m_status = BETWEEN_FIRING_SHOTS;
			}
		}
	}

	int extraTime = (int)(float)m_template->m_timingExtra;
	if (extraTime > 0)
		m_whenLastReloadStarted = TheGameLogic->getFrame() + (unsigned)extraTime;

	return reloaded;
}
