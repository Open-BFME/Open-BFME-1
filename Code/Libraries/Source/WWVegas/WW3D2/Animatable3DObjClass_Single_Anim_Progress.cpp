// cl: /DNDEBUG /MD /EHsc

// Animatable3DObjClass::Single_Anim_Progress, retail 0x00982870.
//
// Zero Hour's body minus its first two lines: it saves ModeAnim.PrevFrame and
// then assigns it from Frame before recomputing, and retail does neither - the
// frame is written once, from Compute_Current_Frame, and nothing reads the
// previous one. Those lines are gone rather than compiled out.
//
// What BFME adds is the byte at +0xF8, cleared on the same path.
//
// WW3D::Get_Sync_Time() is inlined to a read of the global at 0x0133F420.

typedef float Real;

enum
{
	SINGLE_ANIM = 2
};

extern int WW3DSyncTime;					// 0x0133F420

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/animobj.h
class Animatable3DObjClass
{
protected:
	Real Compute_Current_Frame( Real *newdirection ) const;

	void Single_Anim_Progress( void );

private:
	unsigned char m_unmodelled_00[ 0xF8 ];
	bool m_unmodelled_F8;					// +0xF8
	unsigned char m_unmodelled_F9[ 0x104 - 0xF9 ];
	int CurMotionMode;						// +0x104
	unsigned char m_unmodelled_108[4];
	Real ModeAnimFrame;						// +0x10C
	unsigned char m_unmodelled_110[8];
	int ModeAnimLastSyncTime;				// +0x118
	Real ModeAnimDirection;					// +0x11C
};

// ?Single_Anim_Progress@Animatable3DObjClass@@IAEXXZ
void Animatable3DObjClass::Single_Anim_Progress( void )
{
	if( CurMotionMode == SINGLE_ANIM )
	{
		ModeAnimFrame = Compute_Current_Frame( &ModeAnimDirection );
		ModeAnimLastSyncTime = WW3DSyncTime;
		m_unmodelled_F8 = false;
	}
}
