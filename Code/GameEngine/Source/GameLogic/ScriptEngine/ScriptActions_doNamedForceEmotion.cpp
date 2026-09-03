// cl: /DNDEBUG /DWIN32 /MD
// Open-BFME: ScriptActions UNIT_FORCE_EMOTION, retail 0x002F1190, 53 bytes.
//
// executeAction calls this. Template 518 is UNIT_FORCE_EMOTION (unit, emotion,
// seconds). EmotionType is range-checked to [0, 10) then Object::forceEmotion
// is called with a null source; that callee is already pinned at ILT 0x000218FF.

enum EmotionType
{
	EMOTION_INVALID = -1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void forceEmotion(EmotionType emotion, float duration, const Object *source);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doNamedForceEmotion(const AsciiString &unitName, EmotionType emotion, float duration);
};

void ScriptActions::doNamedForceEmotion(const AsciiString &unitName, EmotionType emotion, float duration)
{
	if (emotion < 0)
		return;
	if (emotion >= 10)
		return;

	Object *object = TheScriptEngine->getUnitNamed(unitName);
	if (object)
		object->forceEmotion(emotion, duration, 0);
}
