// cl: /DNDEBUG /MD /EHsc

// The name-taking overload of Add_Sub_Object_To_Bone: it resolves its bone-name
// argument through the virtual at vtable offset 0xC4 -- the same Get_Bone_Index
// the Remove_Sub_Objects_From_Bone name overload uses -- and forwards object,
// index and offset to the int overload at 0x94. ret 0xc confirms three
// arguments.
//
// The placeholders put those two methods at the offsets the body encodes. The
// overload pair is declared name-first because MSVC reverses within an overload
// group, which lands the int version at the lower slot.
//
// Note the parameter typed as the enclosing class mangles as PAV1@, a
// backreference -- spelling out PAVRenderObjClass@@ fails as symbol-not-found
// rather than as a byte mismatch.
class Vector3;

class RenderObjClass
{
public:
	virtual void slot_00(void);
	virtual void slot_01(void);
	virtual void slot_02(void);
	virtual void slot_03(void);
	virtual void slot_04(void);
	virtual void slot_05(void);
	virtual void slot_06(void);
	virtual void slot_07(void);
	virtual void slot_08(void);
	virtual void slot_09(void);
	virtual void slot_10(void);
	virtual void slot_11(void);
	virtual void slot_12(void);
	virtual void slot_13(void);
	virtual void slot_14(void);
	virtual void slot_15(void);
	virtual void slot_16(void);
	virtual void slot_17(void);
	virtual void slot_18(void);
	virtual void slot_19(void);
	virtual void slot_20(void);
	virtual void slot_21(void);
	virtual void slot_22(void);
	virtual void slot_23(void);
	virtual void slot_24(void);
	virtual void slot_25(void);
	virtual void slot_26(void);
	virtual void slot_27(void);
	virtual void slot_28(void);
	virtual void slot_29(void);
	virtual void slot_30(void);
	virtual void slot_31(void);
	virtual void slot_32(void);
	virtual void slot_33(void);
	virtual void slot_34(void);
	virtual void slot_35(void);
	virtual void slot_36(void);
	virtual int Add_Sub_Object_To_Bone(RenderObjClass *obj, const char *bone_name, const Vector3 *offset);
	virtual int Add_Sub_Object_To_Bone(RenderObjClass *obj, int bone_index, const Vector3 *offset);
	virtual void slot_39(void);
	virtual void slot_40(void);
	virtual void slot_41(void);
	virtual void slot_42(void);
	virtual void slot_43(void);
	virtual void slot_44(void);
	virtual void slot_45(void);
	virtual void slot_46(void);
	virtual void slot_47(void);
	virtual void slot_48(void);
	virtual int Get_Bone_Index(const char *bone_name) const;
};

// ?Add_Sub_Object_To_Bone@RenderObjClass@@UAEHPAV1@PBDPBVVector3@@@Z
int RenderObjClass::Add_Sub_Object_To_Bone(RenderObjClass *obj, const char *bone_name, const Vector3 *offset)
{
	int bone_index = Get_Bone_Index(bone_name);
	return Add_Sub_Object_To_Bone(obj, bone_index, offset);
}
