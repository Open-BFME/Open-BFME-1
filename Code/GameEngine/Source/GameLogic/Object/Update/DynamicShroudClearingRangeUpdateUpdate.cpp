// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// ?update@DynamicShroudClearingRangeUpdate@@UAE?AW4UpdateSleepTime@@XZ
// Zero Hour reference source: GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/DynamicShroudClearingRangeUpdate.cpp
//
// update() runs on the UpdateModuleInterface subobject at this+0x10 (MSVC
// secondary-base this), so every member reads 0x10 below its offset. BFME's
// UpdateModule carries three members (0x14..0x1c), one more than Zero Hour,
// so m_state sits at +0x20.

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }

private:
	unsigned char m_pad000[0x3c];
	unsigned int m_frame;
};

extern GameLogic *TheBfmeGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const Coord3D *getPosition() const { return &m_cachedPos; }
	void setShroudClearingRange(float range);

private:
	unsigned char m_pad000[0x38];
	Coord3D m_cachedPos;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/RadiusDecal.h
class RadiusDecalTemplate
{
private:
	const void *m_name;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/RadiusDecal.h
class RadiusDecal
{
private:
	const void *m_template;
	void *m_decal;
	unsigned char m_rest[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DynamicShroudClearingRangeUpdate.h
class DynamicShroudClearingRangeUpdateModuleData
{
public:
	unsigned char m_head[8];
	unsigned int m_shrinkDelay;				///< +0x08
	unsigned int m_shrinkTime;				///< +0x0c
	unsigned int m_growDelay;				///< +0x10
	unsigned int m_growTime;				///< +0x14
	float m_finalVision;					///< +0x18
	unsigned int m_changeInterval;			///< +0x1c
	unsigned int m_growInterval;			///< +0x20
	bool m_doSpySatFX;						///< +0x24
	RadiusDecalTemplate m_gridDecalTemplate;	///< +0x28
};

class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual void objectModuleAnchor();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorInterface
{
public:
	virtual void behaviorAnchor() = 0;
};

class UpdateInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public ObjectModule, public BehaviorInterface, public UpdateInterface
{
protected:
	Object *getObject() const { return m_object; }
	const ModuleData *getModuleData() const { return m_moduleData; }

	int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

enum DSCRU_STATE
{
	DSCRU_NOT_STARTED_YET,
	DSCRU_GROWING,
	DSCRU_SUSTAINING,
	DSCRU_SHRINKING,
	DSCRU_DONE_FOREVER,
	DSCRU_SLEEPING
};

template <class T> inline const T &dscruMax(const T &a, const T &b) { return (a > b) ? a : b; }

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DynamicShroudClearingRangeUpdate.h
class DynamicShroudClearingRangeUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();

	void createGridDecals(const RadiusDecalTemplate &tmpl, float radius, const Coord3D &position);
	void killGridDecals();
	void animateGridDecals();

	const DynamicShroudClearingRangeUpdateModuleData *getDynamicShroudClearingRangeUpdateModuleData() const
	{
		return (const DynamicShroudClearingRangeUpdateModuleData *)getModuleData();
	}

private:
	DSCRU_STATE m_state;						///< +0x20
	int m_stateCountDown;						///< +0x24
	int m_totalFrames;							///< +0x28
	unsigned int m_growStartDeadline;			///< +0x2c
	unsigned int m_sustainDeadline;				///< +0x30
	unsigned int m_shrinkStartDeadline;			///< +0x34
	unsigned int m_doneForeverFrame;			///< +0x38
	unsigned int m_changeIntervalCountdown;		///< +0x3c
	bool m_decalsCreated;						///< +0x40
	float m_visionChangePerInterval;			///< +0x44
	float m_nativeClearingRange;				///< +0x48
	float m_currentClearingRange;				///< +0x4c
	RadiusDecal m_gridDecal[30];				///< +0x50
};

UpdateSleepTime DynamicShroudClearingRangeUpdate::update( void )
{
	if (m_state == DSCRU_SLEEPING) {
		return UPDATE_SLEEP_NONE;
	}

	Object *me = getObject();
	const DynamicShroudClearingRangeUpdateModuleData *md = getDynamicShroudClearingRangeUpdateModuleData();
	unsigned int currentFrame = TheBfmeGameLogic->getFrame();

	if ( ! m_decalsCreated )
	{
		createGridDecals(md->m_gridDecalTemplate, 100, *(me->getPosition()));
		m_decalsCreated = true;
	}

	if( m_stateCountDown <= 0 || currentFrame > m_doneForeverFrame )
		m_state = DSCRU_DONE_FOREVER;
	else if ( m_stateCountDown <= m_shrinkStartDeadline  )
		m_state = DSCRU_SHRINKING;
	else if ( m_stateCountDown <= m_sustainDeadline )
		m_state = DSCRU_SUSTAINING;
	else if ( m_stateCountDown <= m_growStartDeadline )
		m_state = DSCRU_GROWING;

	switch (m_state)
	{
		case DSCRU_NOT_STARTED_YET :
		{
			animateGridDecals();
			break;
		}
		case DSCRU_GROWING :
		{
			animateGridDecals();
			m_currentClearingRange += m_nativeClearingRange / dscruMax(1.0f, (float)md->m_growTime);
			if (m_currentClearingRange >= m_nativeClearingRange)
				m_state = DSCRU_SUSTAINING;
			break;
		}
		case DSCRU_SUSTAINING :
		{
			m_currentClearingRange = m_nativeClearingRange;
			killGridDecals();
			break;
		}
		case DSCRU_SHRINKING :
		{
			m_currentClearingRange -= (m_nativeClearingRange-md->m_finalVision) / dscruMax(1.0f, (float)md->m_shrinkTime);
			break;
		}
		case DSCRU_DONE_FOREVER :
		{
			killGridDecals();
			m_currentClearingRange = md->m_finalVision;
			break;
		}
	}

	if ( m_stateCountDown > 0 ) m_stateCountDown --;

	if( m_changeIntervalCountdown > 0 )
		m_changeIntervalCountdown--;
	else
	{
		m_changeIntervalCountdown = ( m_state == DSCRU_GROWING ? md->m_growInterval : md->m_changeInterval);
		me->setShroudClearingRange( m_currentClearingRange );
		if (m_state == DSCRU_DONE_FOREVER) {
			m_state = DSCRU_SLEEPING;
		}
	}

	return UPDATE_SLEEP_NONE;
}
