// cl: /DNDEBUG /MD /EHsc
// readable body of ?changedTeam@Drawable@@QAEXXZ: Code/GameEngine/Source/GameClient/Drawable.cpp
// Open-BFME: Drawable::changedTeam, retail 0x00418830, 57 bytes.
//
// The reference's first block, unchanged: pick the night or the day indicator
// colour off the object and set it on the drawable.  TheGlobalData's
// m_timeOfDay sits at +0x218 and the value tested is 4, which is exactly
// TIME_OF_DAY_NIGHT in the reference's enum.
//
// The reference's second block -- the FS_FAKE terrain decal -- is gone; in its
// place the body tail-jumps a virtual slot at +0x34 with no arguments, so it is
// spelled here as a slot of the drawable's own vtable.  The name is shape only.
//
// getObject() is a member read, not a call: retail loads this+0xFC straight
// into ecx and reuses it as the `this` of both colour getters.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef UnsignedInt Color;

enum TimeOfDay
{
	TIME_OF_DAY_INVALID = 0,
	TIME_OF_DAY_FIRST = 1,
	TIME_OF_DAY_MORNING = TIME_OF_DAY_FIRST,
	TIME_OF_DAY_AFTERNOON,
	TIME_OF_DAY_EVENING,
	TIME_OF_DAY_NIGHT,

	TIME_OF_DAY_COUNT
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Color getIndicatorColor(void) const;			// ILT 0x00009CA0
	Int getNightIndicatorColor(void) const;			// ILT 0x0001D18D

private:
	unsigned char m_unmodelled_000[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_unmodelled_000[0x218];
	TimeOfDay m_timeOfDay;					// +0x218
};

extern GlobalData *TheGlobalData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	virtual void unusedSlot00();
	virtual void unusedSlot01();
	virtual void unusedSlot02();
	virtual void unusedSlot03();
	virtual void unusedSlot04();
	virtual void unusedSlot05();
	virtual void unusedSlot06();
	virtual void unusedSlot07();
	virtual void unusedSlot08();
	virtual void unusedSlot09();
	virtual void unusedSlot10();
	virtual void unusedSlot11();
	virtual void unusedSlot12();
	virtual void bfme_teamIndicatorChanged();		// vtable +0x34

	void changedTeam(void);

	void setIndicatorColor(Color color);			// ILT 0x00028C09

private:
	Object *getObject(void) const { return m_object; }

	unsigned char m_unmodelled_004[0xF8];			// this+0x04 .. +0xFB, untouched
	Object *m_object;					// this+0xFC
};

void Drawable::changedTeam()
{
	Object *object = getObject();
	if( object )
	{
		if (TheGlobalData->m_timeOfDay == TIME_OF_DAY_NIGHT)
			setIndicatorColor( object->getNightIndicatorColor() );
		else
			setIndicatorColor( object->getIndicatorColor() );

		bfme_teamIndicatorChanged();
	}
}
