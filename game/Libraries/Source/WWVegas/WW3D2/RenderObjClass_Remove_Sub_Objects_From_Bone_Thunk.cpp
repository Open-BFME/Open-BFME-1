// cl: /DNDEBUG /MD /EHsc

// The const char* overload of Remove_Sub_Objects_From_Bone: it converts its
// argument through the virtual at vtable offset 0xC4 and hands the result to the
// virtual at 0x9C, which is the int overload sitting in the adjacent slot.
//
// The placeholders exist only to put those two methods at the offsets the body
// uses, and getting there took two corrections worth recording. MSVC groups an
// overload set into consecutive slots wherever the second one is declared, so
// writing this overload at the end of the class pulled it up beside the int
// version and pushed everything after it down a slot. And within the group the
// order is reversed -- the last declared lands first -- so the int version has to
// be declared second to end up at 0x9C. That reversal matches the image, where
// the name overload occupies the slot before the int one.
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
	virtual void slot_37(void);
	virtual void slot_38(void);
	virtual int Remove_Sub_Objects_From_Bone(const char *bone_name);
	virtual int Remove_Sub_Objects_From_Bone(int bone_index);
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

// ?Remove_Sub_Objects_From_Bone@RenderObjClass@@UAEHPBD@Z
int RenderObjClass::Remove_Sub_Objects_From_Bone(const char *bone_name)
{
	return Remove_Sub_Objects_From_Bone(Get_Bone_Index(bone_name));
}
