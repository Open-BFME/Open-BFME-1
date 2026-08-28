// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: GlobalData::newOverride, retail 0x00085BA0, zh_sweep packet
// 00085ba0.
//
// The Zero Hour body copies the current data into the new override:
//
//     GlobalData *override = NEW GlobalData;
//     *override = *TheWritableGlobalData;
//     override->m_next = TheWritableGlobalData;
//     TheWritableGlobalData = override;
//
// BFME dropped the copy. Retail allocates, links and returns with nothing in
// between -- no memcpy, no operator=, no call at all between the constructor
// and the m_next store -- so the assignment is gone rather than inlined. The
// fresh override starts at the constructor's defaults.
//
// The bytes pin the class: operator new is handed 0x1290, and m_next is
// written at [eax+0x128C], the last four bytes of it. Its own TU spelling
// only that, since nothing else here depends on the other 4748.
//
// The SEH frame is not ours: /EHsc gives `new GlobalData` a funclet so the
// allocation is released if the constructor throws.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	GlobalData();												///< ??0GlobalData@@QAE@XZ, ILT 0x00001807

private:
	GlobalData *newOverride( void );

	unsigned char m_unreconstructed[0x128C];					///< +0x0000
	GlobalData *m_next;											///< +0x128C, sizeof is 0x1290
};

extern GlobalData *TheWritableGlobalData;						///< 0x012ED5C8

// ?newOverride@GlobalData@@AAEPAV1@XZ
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
