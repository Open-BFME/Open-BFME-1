class BfmeSubYG
{
public:
	virtual void bfmeS0YG();
	virtual void bfmeS1YG();
	virtual void bfmeS2YG();
	virtual void bfmeS3YG();
	virtual void bfmeS4YG();
	virtual void bfmeS5YG();
	virtual void bfmeS6YG();
	virtual void bfmeS7YG();
	virtual int bfmeKindYG();
};

// Retail calls ILT 0x00019B23 -> 0x001C74E0 and ILT 0x0000A001 -> 0x001C1770,
// matched as these Object members.
class Object
{
public:
	unsigned char getCrushableLevel() const;
	bool isUsingAirborneLocomotor() const;
};

class BfmeThingYG
{
public:
	unsigned char m_bfmeHeadYG[0x200];
	BfmeSubYG *m_bfmeSubYG;
};

class BfmeOwnerYG
{
public:
	char bfmeCheckYG(BfmeThingYG *thing);

	unsigned char m_bfmeStartYG[8];
	BfmeThingYG *m_bfmeCurrentYG;
	char m_bfmeLevelYG;
};

char BfmeOwnerYG::bfmeCheckYG(BfmeThingYG *thing)
{
	const Object *object = (const Object *)thing;

	if (m_bfmeLevelYG != 0 && m_bfmeLevelYG > (char)object->getCrushableLevel())
		return 0;

	if (thing == m_bfmeCurrentYG)
		return 0;

	if (object->isUsingAirborneLocomotor())
		return 0;

	BfmeSubYG *sub = thing->m_bfmeSubYG;

	if (sub == 0)
		return 1;

	return (char)(sub->bfmeKindYG() != 3 ? 1 : 0);
}
