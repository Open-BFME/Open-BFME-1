// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Animatable3DObjClass::Set_Animation, the blend overload -- retail 0x009822C0,
// 99 bytes. This used to be a wall of __asm _emit bytes; it is real C++ now.
//
// It also pins the BFME layout of the DOUBLE_ANIM arm of the motion-state
// union, which differs from Zero Hour's: retail stores both motions before
// either frame (Motion0 +0x108, Motion1 +0x10c, Frame0 +0x110, Frame1 +0x114)
// and puts Percentage at +0x118, immediately after Frame1, where Zero Hour has
// two PrevFrame floats in between. BFME dropped the embedded-sound triggering
// that those prev-frames existed to feed.
//
// The class below is a layout skeleton -- it only has to place the fields and
// give HAnimClass a reference count at +0x04, which is where retail's inlined
// Add_Ref increments.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	void Add_Ref( void ) { NumRefs++; }

protected:
	virtual ~RefCountClass();	// vtable pointer at +0x00
	int NumRefs;				// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hanim.h
class HAnimClass : public RefCountClass
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/animobj.h
class Animatable3DObjClass
{
public:
	enum { NONE = 0, BASE_POSE, SINGLE_ANIM, DOUBLE_ANIM, MULTIPLE_ANIM };

	virtual void Set_Animation( HAnimClass *motion0, float frame0, HAnimClass *motion1, float frame1, float percentage );

	void Release( void );
	void Set_Hierarchy_Valid( bool onoff ) const { IsTreeValid = onoff; }

protected:
	char m_head[0xf4];			// vtable pointer is +0x00; RenderObjClass's fields follow

	mutable bool IsTreeValid;	// +0xf8
	char m_pad[3];
	void *HTree;				// +0xfc
	void *m_container;			// +0x100
	int CurMotionMode;			// +0x104

	struct
	{
		HAnimClass *Motion0;	// +0x108
		HAnimClass *Motion1;	// +0x10c
		float Frame0;			// +0x110
		float Frame1;			// +0x114
		float Percentage;		// +0x118
	} ModeInterp;
};

// ?Set_Animation@Animatable3DObjClass@@UAEXPAVHAnimClass@@M0MM@Z
void Animatable3DObjClass::Set_Animation( HAnimClass *motion0, float frame0, HAnimClass *motion1, float frame1, float percentage )
{
	if( motion0 )
	{
		motion0->Add_Ref();
	}

	if( motion1 )
	{
		motion1->Add_Ref();
	}

	Release();

	CurMotionMode = DOUBLE_ANIM;
	ModeInterp.Motion0 = motion0;
	ModeInterp.Frame0 = frame0;
	ModeInterp.Motion1 = motion1;
	ModeInterp.Frame1 = frame1;
	ModeInterp.Percentage = percentage;

	Set_Hierarchy_Valid( false );
}
