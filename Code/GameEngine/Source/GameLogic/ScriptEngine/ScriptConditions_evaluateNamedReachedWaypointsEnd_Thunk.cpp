// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ for ScriptConditions::evaluateNamedReachedWaypointsEnd.

typedef bool Bool;

template <class T> class StringBase
{
	friend class AsciiString;

	public:
	// Retail's non-throwing compare call leaves no intermediate EH-state stores.
	int compare(const StringBase &) const throw();

	private:
	StringBase(const StringBase &);
	~StringBase();
};

class AsciiString
{
public:
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString();

private:
	char *m_text;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return ((const StringBase<char> *)&left)->compare(
		*(const StringBase<char> *)&right) == 0;
}

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }

private:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

class Object;
class ScriptEngine;

// BFME's ScriptEngine has an extra slot before getUnitNamed compared with the
// Zero Hour declaration; getUnitNamed is the virtual at +0x68 in retail.
class BfmeScriptConditionEngine
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0;
	virtual void slot15() = 0; virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0; virtual void slot20() = 0;
	virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &) = 0;
};

class Object
{
public:
	class AIUpdateInterface *getAIUpdateInterface() const
	{
		return *(class AIUpdateInterface **)((const char *)this + 0x204);
	}
};

class AIUpdateInterface
{
public:
	class Waypoint *getCompletedWaypoint() const
	{
		return *(class Waypoint **)((const char *)this + 0x13c);
	}
};

class Waypoint
{
public:
	AsciiString getPathLabel1() const;
	AsciiString getPathLabel2() const;
	AsciiString getPathLabel3() const;
};

extern ScriptEngine *TheScriptEngine;

// ?evaluateNamedReachedWaypointsEnd@ScriptConditions@@IAE_NPAVParameter@@0@Z
class ScriptConditions
{
protected:
	Bool evaluateNamedReachedWaypointsEnd(Parameter *, Parameter *);
};

Bool ScriptConditions::evaluateNamedReachedWaypointsEnd(Parameter *pUnitParm, Parameter *pWaypointPathParm)
{
	// Retail passes the first Parameter's address as the AsciiString reference
	// consumed by getUnitNamed, while the path Parameter uses its +0x10 string
	// member below. Preserve that BFME-specific ABI shape explicitly.
	Object *theObj = reinterpret_cast<BfmeScriptConditionEngine *>(TheScriptEngine)->getUnitNamed(
		*(const AsciiString *)pUnitParm);
	if (!theObj)
		return false;

	AIUpdateInterface *ai = theObj->getAIUpdateInterface();
	if (!ai)
		return false;

	const Waypoint *targetWay = ai->getCompletedWaypoint();
	if (!targetWay)
		return false;

	AsciiString pathName = pWaypointPathParm->getString();
	if (targetWay->getPathLabel1() == pathName)
		return true;
	if (targetWay->getPathLabel2() == pathName)
		return true;
	if (targetWay->getPathLabel3() == pathName)
		return true;

	return false;
}
