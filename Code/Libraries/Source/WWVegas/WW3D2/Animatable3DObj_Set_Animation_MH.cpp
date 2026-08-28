// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Animatable3DObjClass::Set_Animation(HAnimClass *, float, int) -- retail
// 0x00982190, 301 bytes. This used to be a wall of __asm _emit bytes; it is real
// C++ now.
//
// BFME rewrote the body Zero Hour has. Zero Hour sets PrevFrame from the
// previous Frame, always stores the new Frame, and picks the playback direction
// purely from the mode. BFME instead:
//   - stores a clamped copy of the requested frame in PrevFrame;
//   - only overwrites Frame when the mode is not ANIM_MODE_LOOP_BACKWARDS, so
//     re-issuing a backwards loop keeps whatever frame the object had reached;
//   - for that one mode, derives the direction by comparing the clamped frame
//     against the current Frame rather than from the mode;
//   - drops the embedded-sound bone lookup entirely.
//
// The clamp has to be spelled with macros. Retail evaluates the inner minimum
// three times over -- calling Get_Num_Frames again each time -- which is what
// textual macro substitution does and what an inline function like
// WWMath::Clamp cannot produce.
#define BFME_MIN(a,b) (((a) < (b)) ? (a) : (b))
#define BFME_MAX(a,b) (((a) > (b)) ? (a) : (b))

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	void Add_Ref( void ) { NumRefs++; }

protected:
	virtual ~RefCountClass();	// vtable pointer at +0x00
	int NumRefs;				// +0x04
};

// Only slot 4 is proven here: retail's call is call dword ptr [eax+0x10].
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hanim.h
class HAnimClass : public RefCountClass
{
public:
	virtual const char *Get_Name( void ) const;		// slot 1
	virtual const char *Get_HName( void ) const;	// slot 2
	virtual const char *Get_Key( void );			// slot 3
	virtual int Get_Num_Frames( void );				// slot 4
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/ww3d.h
class WW3D
{
public:
	static unsigned int Get_Sync_Time( void ) { return SyncTime; }

private:
	static unsigned int SyncTime;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/animobj.h
class Animatable3DObjClass
{
public:
	enum { NONE = 0, BASE_POSE, SINGLE_ANIM, DOUBLE_ANIM, MULTIPLE_ANIM };
	enum
	{
		ANIM_MODE_MANUAL = 0,
		ANIM_MODE_LOOP,
		ANIM_MODE_ONCE,
		ANIM_MODE_LOOP_PINGPONG,
		ANIM_MODE_LOOP_BACKWARDS,
		ANIM_MODE_ONCE_BACKWARDS,
	};

	virtual void Set_Animation( HAnimClass *motion, float frame, int mode );

	void Release( void );
	void Set_Hierarchy_Valid( bool onoff ) const { IsTreeValid = onoff; }

protected:
	char m_head[0xf4];				// vtable pointer is +0x00; RenderObjClass's fields follow

	mutable bool IsTreeValid;		// +0xf8
	char m_pad[3];
	void *HTree;					// +0xfc
	void *m_slavedTo;				// +0x100
	int CurMotionMode;				// +0x104

	struct
	{
		HAnimClass *Motion;			// +0x108
		float Frame;				// +0x10c
		float PrevFrame;			// +0x110
		int AnimMode;				// +0x114
		mutable int LastSyncTime;	// +0x118
		float animDirection;		// +0x11c
		float frameRateMultiplier;	// +0x120
	} ModeAnim;
};

// ?Set_Animation@Animatable3DObjClass@@UAEXPAVHAnimClass@@MH@Z
void Animatable3DObjClass::Set_Animation( HAnimClass *motion, float frame, int mode )
{
	if( motion != 0 )
	{
		// Add_Ref before the release, in case it is the animation already playing.
		motion->Add_Ref();
		Release();

		CurMotionMode = SINGLE_ANIM;
		ModeAnim.Motion = motion;

		ModeAnim.PrevFrame = BFME_MAX( BFME_MIN( (float)(ModeAnim.Motion->Get_Num_Frames() - 1), frame ), 0.0f );

		if( mode == ANIM_MODE_LOOP_BACKWARDS )
		{
			// Frame is deliberately left alone: the direction says which way to
			// walk away from wherever the object already was.
			if( ModeAnim.PrevFrame >= ModeAnim.Frame )
			{
				ModeAnim.animDirection = 1.0f;
			}
			else
			{
				ModeAnim.animDirection = -1.0f;
			}
		}
		else
		{
			ModeAnim.Frame = frame;

			if( mode < ANIM_MODE_ONCE_BACKWARDS )
			{
				ModeAnim.animDirection = 1.0f;
			}
			else
			{
				ModeAnim.animDirection = -1.0f;
			}
		}

		ModeAnim.LastSyncTime = WW3D::Get_Sync_Time();
		ModeAnim.frameRateMultiplier = 1.0f;
		ModeAnim.AnimMode = mode;
	}
	else
	{
		Release();
		CurMotionMode = BASE_POSE;
	}

	Set_Hierarchy_Valid( false );
}
