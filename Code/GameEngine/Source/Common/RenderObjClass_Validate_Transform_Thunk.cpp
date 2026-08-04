// cl: /DNDEBUG /MD /EHsc
// Lift the RenderObjClass::Validate_Transform __emit thunk to clean C++.
//
// Zero Hour's rendobj.cpp carries this body verbatim: walk up the container
// chain accumulating whether any ancestor's sub-object transforms are dirty,
// update them if so, and recompute the cached identity flag. Retail pins the
// layout ZH leaves symbolic -- Bits at this+0x10 with SUBOBJ_TRANSFORMS_DIRTY
// as bit 21 (`shr edx, 0x15` then `and dl, 1`), Transform at this+0x18,
// IsTransformIdentity at this+0x7C, and Container at this+0x84.
//
// Check_Is_Transform_Identity is `static inline` in the ZH source, and MSVC 7.1
// gives such a function a register calling convention when its address is never
// taken -- retail passes the matrix in ecx with no push. Declaring it __fastcall
// here reproduces that call site exactly; the pin points the rel32 at the same
// body the cdecl-mangled ledger row already claims at 0x0091FF40.

#define NULL 0

class Matrix3D
{
public:
	float Row[3][4];
};

bool __fastcall Check_Is_Transform_Identity(const Matrix3D &m);

class RenderObjClass
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void Update_Sub_Object_Transforms(void);	///< vtable +0xA4
	virtual void Validate_Transform(void) const;

	RenderObjClass *Get_Container(void) const { return Container; }
	bool Are_Sub_Object_Transforms_Dirty(void) { return (Bits & SUBOBJ_TRANSFORMS_DIRTY) != 0; }

private:
	enum { SUBOBJ_TRANSFORMS_DIRTY = 0x00200000 };

	unsigned char m_unreconstructed_04[0x10 - 4];
	unsigned int Bits;								///< retail this+0x10
	unsigned char m_unreconstructed_14[0x18 - 0x14];
	Matrix3D Transform;								///< retail this+0x18
	unsigned char m_unreconstructed_48[0x7C - 0x48];
	mutable bool IsTransformIdentity;				///< retail this+0x7C
	unsigned char m_unreconstructed_7D[0x84 - 0x7D];
	RenderObjClass *Container;						///< retail this+0x84
};

// ?Validate_Transform@RenderObjClass@@UBEXXZ
void RenderObjClass::Validate_Transform(void) const
{
	/*
	** Recurse up the tree to see if any of my parents are saying that their sub-object
	** transforms are dirty
	*/
	RenderObjClass *con = Get_Container();
	bool dirty = false;
	if (con != NULL)
	{
		dirty = con->Are_Sub_Object_Transforms_Dirty();

		while (con->Get_Container() != NULL)
		{
			dirty |= con->Are_Sub_Object_Transforms_Dirty();
			con = con->Get_Container();
		}

		/*
		** If the transforms are dirty, update them
		*/
		if (dirty)
		{
			con->Update_Sub_Object_Transforms();
		}
	}
	if (dirty)
		IsTransformIdentity = Check_Is_Transform_Identity(Transform);
}
