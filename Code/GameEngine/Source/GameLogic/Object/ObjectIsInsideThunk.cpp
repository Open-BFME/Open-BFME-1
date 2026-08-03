// cl: /DNDEBUG /MD /EHsc

class PolygonTrigger;

struct TTriggerInfo
{
	const PolygonTrigger *pTrigger;
	unsigned char entered;
	unsigned char exited;
	unsigned char isInside;
	unsigned char padding;
};

// Retail BFME Object: m_triggerInfo @ +0x2d8, m_numTriggerAreasActive @ +0x346.
class Object
{
	unsigned char pad0[0x2d8];
	TTriggerInfo m_triggerInfo[13];
	unsigned char pad1[6];
	signed char m_numTriggerAreasActive;

public:
	bool isInside(const PolygonTrigger *pTrigger) const;
};

// ?isInside@Object@@QBE_NPBVPolygonTrigger@@@Z
bool Object::isInside(const PolygonTrigger *pTrigger) const
{
	for (int i = 0; i < m_numTriggerAreasActive; i++)
	{
		if (m_triggerInfo[i].isInside && m_triggerInfo[i].pTrigger == pTrigger)
			return true;
	}
	return false;
}
