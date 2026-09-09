// ?recompute@AIGroup@@QAEXXZ
// Open-BFME: AIGroup::recompute, retail 0x00154B80, 276 bytes.
//
// BFME extends the Zero Hour recompute walk with the ground-path state reset,
// the immobile/held filters, and the body damage-state speed check.  The
// scalar delete is explicitly non-throwing so the old MSVC caller cleanup can
// be scheduled with the following path-state stores.

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum KindOfType { KINDOF_IMMOBILE = 2 };

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride(void) const;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	bool isKindOf(KindOfType t) const
	{
		return (m_kindof[(unsigned int)t >> 5] &
			(1u << ((unsigned int)t & 31))) != 0;
	}

private:
	unsigned char m_unreconstructed_08[0xC8 - 0x08];
	unsigned int m_kindof[3];
};

void __cdecl operator delete(void *) throw();

class __declspec(novtable) Path
{
protected:
	virtual ~Path(void) throw();
};

class BFMEDeletablePath : public Path
{
public:
	void destroy(void) { Path::~Path(); }
};

class BodyModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual int getDamageState() = 0;
};

class AIUpdateInterface
{
public:
	float getCurLocomotorSpeed(void);
};

class Object
{
public:
	const ThingTemplate *getTemplate(void) const
	{
		const ThingTemplate *tmpl = m_template;
		if (tmpl == 0)
			return 0;
		if (tmpl->m_nextOverride)
			tmpl = (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
		return tmpl;
	}

	bool isKindOf(KindOfType t) const { return getTemplate()->isKindOf(t); }
	float getPosX(void) const { return m_position.x; }
	float getPosY(void) const { return m_position.y; }
	AIUpdateInterface *getAIUpdateInterface(void) { return m_ai; }
	BodyModuleInterface *getBodyModule(void) { return m_body; }
	unsigned char getDisabledMask(void) const { return m_disabledMask; }

private:
	virtual ~Object();
	const ThingTemplate *m_template;
	unsigned char m_unreconstructed_08[0x38 - 0x08];
	Coord3D m_position;
	unsigned char m_unreconstructed_44[0x1A4 - 0x44];
	unsigned char m_disabledMask;
	unsigned char m_unreconstructed_1A5[0x200 - 0x1A5];
	BodyModuleInterface *m_body;
	AIUpdateInterface *m_ai;
};

struct BfmeListNodeBase
{
	BfmeListNodeBase *m_bfmeNext;
	BfmeListNodeBase *m_bfmePrev;
};

struct BfmeMemberNode : public BfmeListNodeBase
{
	Object *m_bfmeValue;
};

class GlobalData
{
public:
	unsigned char m_unreconstructed_00[0xBD8];
	int m_movementPenaltyDamageState;
};

extern GlobalData *TheWritableGlobalData;

class AIGroup
{
public:
	bool getCenter(Coord3D *center);
	void recompute(void);
	friend class PathDeleteArgument;

private:
	char m_bfmeHead[0x04];
	BfmeListNodeBase *m_bfmeMembers;
	char m_bfmeSize[0x0C - 0x08];
	float m_speed;
	unsigned char m_dirty;
	char m_bfmeId[0x18 - 0x11];
	Path *m_groundPath;
	void *m_pathState1C;
	void *m_pathState20;
	void *m_pathState24;
	float m_pathState28;
	void *m_pathState2C;
	void *m_pathState30;
};

class PathDeleteArgument
{
public:
	PathDeleteArgument(Path *path, AIGroup *group) : m_path(path), m_group(group) { }
	operator void *(void) const { return m_path; }
	// The conversion temporary is intentional.  MSVC destroys this by-value
	// argument before popping operator delete's cdecl stack argument, placing
	// these four reset stores before retail's `add esp, 4`.
	~PathDeleteArgument()
	{
		m_group->m_groundPath = 0;
		m_group->m_pathState1C = 0;
		m_group->m_pathState20 = 0;
		m_group->m_pathState24 = 0;
	}

private:
	Path *m_path;
	AIGroup *m_group;
};

void AIGroup::recompute(void)
{
	float closeDist = 999999999.9f;
	Coord3D center;

	getCenter(&center);

	if (m_groundPath)
	{
		Path *p = m_groundPath;
		reinterpret_cast<BFMEDeletablePath *>(p)->destroy();
		operator delete(PathDeleteArgument(p, this));
		m_pathState28 = 10.0f;
		m_pathState2C = 0;
		m_pathState30 = 0;
	}

	m_speed = 9999999999.9f;

	for (BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
		it != m_bfmeMembers;
		it = it->m_bfmeNext)
	{
		Object *obj = ((BfmeMemberNode *)it)->m_bfmeValue;

		if (obj->isKindOf(KINDOF_IMMOBILE))
			continue;
		if (obj->getDisabledMask() & 8)
			continue;

		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (ai == 0)
			continue;

		float maxSpeed = ai->getCurLocomotorSpeed();
		if (m_speed > maxSpeed &&
				obj->getBodyModule()->getDamageState() <
					TheWritableGlobalData->m_movementPenaltyDamageState)
			m_speed = maxSpeed;

		float dx = obj->getPosX() - center.x;
		float dy = obj->getPosY() - center.y;
		float dist = dx * dx + dy * dy;
		if (dist < closeDist)
			closeDist = dist;
	}

	m_dirty = 0;
}
