// cl: /DNDEBUG /DWIN32 /MD
// Open-BFME: ScriptActions UNIT_GIVE_EXPERIENCE_POINTS, retail 0x002F0460, 54 bytes.
//
// executeAction callee. Template 359 is UNIT_GIVE_EXPERIENCE_POINTS. getUnitNamed
// then ExperienceTracker::addExperiencePoints at Object+0x210 with the int
// widened to float and flags (scale, shared, allow-level, no-feedback). That
// five-argument body is already pinned at ILT 0x00010096.

class AsciiString
{
	char *m_data;
};

class ExperienceTracker
{
public:
	void addExperiencePoints(float experienceGain, bool canScaleForBonus, bool isShared, bool allowLevelGain, bool provideFeedback);
};

class Object
{
public:
	unsigned char m_pad[0x210];
	ExperienceTracker *m_experienceTracker;
};

class ScriptEngine
{
public:
	virtual void _se_0() = 0;
	virtual void _se_1() = 0;
	virtual void _se_2() = 0;
	virtual void _se_3() = 0;
	virtual void _se_4() = 0;
	virtual void _se_5() = 0;
	virtual void _se_6() = 0;
	virtual void _se_7() = 0;
	virtual void _se_8() = 0;
	virtual void _se_9() = 0;
	virtual void _se_10() = 0;
	virtual void _se_11() = 0;
	virtual void _se_12() = 0;
	virtual void _se_13() = 0;
	virtual void _se_14() = 0;
	virtual void _se_15() = 0;
	virtual void _se_16() = 0;
	virtual void _se_17() = 0;
	virtual void _se_18() = 0;
	virtual void _se_19() = 0;
	virtual void _se_20() = 0;
	virtual void _se_21() = 0;
	virtual void _se_22() = 0;
	virtual void _se_23() = 0;
	virtual void _se_24() = 0;
	virtual void _se_25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doNamedGiveExperiencePoints(const AsciiString &unitName, int experience);
};

void ScriptActions::doNamedGiveExperiencePoints(const AsciiString &unitName, int experience)
{
	Object *object = TheScriptEngine->getUnitNamed(unitName);
	if (!object)
		return;

	ExperienceTracker *tracker = object->m_experienceTracker;
	if (!tracker)
		return;

	tracker->addExperiencePoints((float)experience, true, true, true, false);
}
