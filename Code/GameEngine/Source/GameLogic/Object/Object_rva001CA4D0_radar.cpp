// cl: /DNDEBUG /MD /EHsc
// BFME radar priority selection.  The template and contain offsets are from
// the BFME Object/ThingTemplate layouts; the original routine repeats the
// final-override walk for its kind-of fallback.

typedef unsigned int UnsignedInt;

enum RadarPriorityType
{
	RADAR_PRIORITY_INVALID,
	RADAR_PRIORITY_NOT_ON_RADAR,
	RADAR_PRIORITY_STRUCTURE,
	RADAR_PRIORITY_UNIT,
	RADAR_PRIORITY_LOCAL_UNIT_ONLY,
	RADAR_PRIORITY_NUM_PRIORITIES
};

class Overridable
{
public:
	Overridable *getFinalOverride();

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad08[0xc8 - 0x08];
	UnsignedInt m_kindOf[3];
	unsigned char m_pad_d4[0x490 - 0xd4];
	signed char m_radarPriority;
};

class BfmeRadarContain
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual bool isGarrisonable();
};

class Object
{
public:
	RadarPriorityType getRadarPriority() const;

private:
	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_pad08[0x1fc - 0x08];
	BfmeRadarContain *m_contain;
};

RadarPriorityType Object::getRadarPriority() const
{
	ThingTemplate *templateValue = m_template;
	if (templateValue != 0 && templateValue->m_nextOverride != 0)
		templateValue = (ThingTemplate *)templateValue->m_nextOverride->getFinalOverride();

	RadarPriorityType priority = (RadarPriorityType)templateValue->m_radarPriority;
	if (priority != RADAR_PRIORITY_INVALID)
		return priority;

	BfmeRadarContain *contain = m_contain;
	if (contain != 0 && contain->isGarrisonable())
		priority = RADAR_PRIORITY_STRUCTURE;

	templateValue = m_template;
	if (templateValue != 0 && templateValue->m_nextOverride != 0)
		templateValue = (ThingTemplate *)templateValue->m_nextOverride->getFinalOverride();
	return (templateValue->m_kindOf[1] & 0x20000) != 0
		? RADAR_PRIORITY_STRUCTURE : priority;
}
