// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GlobalData::reset, retail 0x00083110.
//
// The Zero Hour body unchanged. GlobalData.cpp is not in this tree, so the
// class is spelled locally around the two things the retail bytes fix:
// m_next at GlobalData+0x128c, and the original-instance static at 0x012ED5CC,
// four bytes past TheWritableGlobalData at 0x012ED5C8.
//
// The loop deletes through the vtable -- `push 1` then `call [eax]` -- which is
// the scalar deleting destructor in slot 0 taking the delete flag, so the class
// is polymorphic and its destructor is the first virtual.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	GlobalData();
	virtual ~GlobalData();
	virtual void reset(void);

	private:
	GlobalData *newOverride(void);

	static GlobalData *m_theOriginal;				///< retail 0x012ED5CC

	char m_unreconstructed_04[0x128c - 4];
	GlobalData *m_next;								///< retail this+0x128c
};

extern GlobalData *TheWritableGlobalData;			///< retail 0x012ED5C8

// ?reset@GlobalData@@UAEXXZ
void GlobalData::reset( void )
{
	//
	// delete	any data instances that were loaded as an override and set the original
	// global data instance as the singleton TheWritableGlobalData once again
	//
	while (TheWritableGlobalData != GlobalData::m_theOriginal)
	{

		// get next instance
		GlobalData* next = TheWritableGlobalData->m_next;

		delete TheWritableGlobalData;

		TheWritableGlobalData = next;

	}
}

GlobalData *GlobalData::newOverride( void )
{
	GlobalData *override = new GlobalData;

	// link the override to the previously created one, the link order is important here
	// for the reset function, if you change the way things are linked
	// for overrides make sure you update the reset function
	override->m_next = TheWritableGlobalData;

	// set this new instance as the 'most current override' where we will access all data from
	TheWritableGlobalData = override;

	return override;

}  // end newOverride
