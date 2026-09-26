// cl: /DNDEBUG /MD /EHsc

// Retail 0x002ED760. ScriptActions::doMergeTeamIntoTeam and
// bfmeAttachSubAF0 both call this helper after attaching an object's subobject.

class Object;

class Radar
{
public:
	void refreshObjectColor(void *object);
};

extern Radar *TheRadar;

// BFME keeps the radar color refresh behind the existing ILT thunk.
#pragma comment(linker, "/alternatename:?refreshObjectColor@Radar@@QAEXPAX@Z=?j_00011383@@YAXXZ")

class Drawable
{
public:
	void setIndicatorColor(unsigned color);

	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void teamIndicatorChanged() = 0;
};

class Object
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual Drawable *getDrawable() const;

	void updateUpgradeModules();
	int getNightIndicatorColor() const;
	int getIndicatorColor() const;
};

class GlobalData
{
public:
	unsigned char m_pad00[0x218];
	int m_timeOfDay;
};

extern GlobalData *TheWritableGlobalData;

// ?bfmeHelper760@@YAHPAXH@Z
int __cdecl bfmeHelper760(void *value, int unused)
{
	(void)unused;
	if (value)
	{
		Object *object = (Object *)value;
		TheRadar->refreshObjectColor(object);
		object->updateUpgradeModules();
		Drawable *drawable = object->getDrawable();
		if (drawable)
		{
			if (TheWritableGlobalData->m_timeOfDay == 4)
				drawable->setIndicatorColor(object->getNightIndicatorColor());
			else
				drawable->setIndicatorColor(object->getIndicatorColor());

			drawable->teamIndicatorChanged();
		}
	}
	return 1;
}
