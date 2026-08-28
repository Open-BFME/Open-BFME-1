// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the Animatable3DObjClass::Release naked dump to clean C++.
//
// Zero Hour's animobj.cpp switch, plus one release ZH does not have: retail
// drops a reference on the field at this+0x100 after the switch, unconditionally.
// That offset is HTree -- ZH declares it immediately before CurMotionMode, which
// retail puts at this+0x104 -- so in BFME the skeleton is reference counted and
// Release lets go of it too.
//
// The case values are one higher than ZH's. Retail tests CurMotionMode against 2
// for the single-animation case and 3 for the double, where ZH's enum makes
// those 1 and 2, so BFME has an extra enumerator ahead of the list. Only the two
// values the bytes prove are named here.
//
// Release_Ref inlines to `--NumRefs; if (NumRefs == 0) Delete_This();` with
// NumRefs at +0x04 and Delete_This as vtable slot 0. The null-and-clear around
// each one is ZH's REF_PTR_RELEASE shape written out.
//
// `mov edi,0` rather than `xor edi,edi` is not a different constant: the switch
// subtraction has already set the flags that the following je reads, so MSVC
// picks the encoding that leaves them alone.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	void Release_Ref(void)
	{
		NumRefs--;
		if (NumRefs == 0)
		{
			Delete_This();
		}
	}

protected:
	virtual void Delete_This(void);						///< vtable +0x00

	int NumRefs;										///< retail this+0x04
};

class HAnimClass : public RefCountClass {};
class HTreeClass : public RefCountClass {};

// Proven by the bytes; ZH numbers these one lower.
enum
{
	SINGLE_ANIM = 2,
	DOUBLE_ANIM = 3
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/animobj.h
class Animatable3DObjClass
{
protected:
	void Release(void);

	// this shim declares no virtuals of its own, so the filler covers the real
	// object's vtable pointer as well
	unsigned char m_unreconstructed_00[0x100];
	HTreeClass *HTree;									///< retail this+0x100
	int CurMotionMode;									///< retail this+0x104

	union
	{
		struct
		{
			HAnimClass *Motion;							///< retail this+0x108
		} ModeAnim;

		struct
		{
			HAnimClass *Motion0;						///< retail this+0x108
			HAnimClass *Motion1;						///< retail this+0x10C
		} ModeInterp;
	};
};

// ?Release@Animatable3DObjClass@@IAEXXZ
void Animatable3DObjClass::Release(void)
{
	switch (CurMotionMode)
	{
		case SINGLE_ANIM:
			if (ModeAnim.Motion != 0)
			{
				ModeAnim.Motion->Release_Ref();
				ModeAnim.Motion = 0;
			}
			break;

		case DOUBLE_ANIM:
			if (ModeInterp.Motion0 != 0)
			{
				ModeInterp.Motion0->Release_Ref();
				ModeInterp.Motion0 = 0;
			}

			if (ModeInterp.Motion1 != 0)
			{
				ModeInterp.Motion1->Release_Ref();
				ModeInterp.Motion1 = 0;
			}
			break;

		default:
			break;
	}

	if (HTree != 0)
	{
		HTree->Release_Ref();
		HTree = 0;
	}
}
