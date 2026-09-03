// cl: /DNDEBUG /MD /EHsc
// readable body of ?Render_Seg_Line@StreakLineClass@@: Code/Libraries/Source/WWVegas/WW3D2/streak.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/rinfo.h
class RenderInfoClass
{
};

class Matrix3D
{
	float Values[12];
};

class Vector3
{
};

class Vector4
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/sphere.h
class SphereClass
{
	float Values[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/seglinerenderer.h
class SegLineRendererClass
{
public:
	void Render(RenderInfoClass &, const Matrix3D &, unsigned int, Vector3 *,
		const SphereClass &, Vector4 * = 0);
};

template <class Type>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/simplevec.h
class SimpleDynVecClass
{
public:
	virtual ~SimpleDynVecClass(void);

	Type *Vector;
	int VectorMax;
	int ActiveCount;
};

// BFME's StreakLineClass has the same RenderObj vtable slot, but its tail is
// enlarged relative to the Zero Hour SegmentedLineClass layout.  The fields
// below are placed from the retail constructor and caller offsets.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/streak.h
class StreakLineClass
{
public:
	virtual void reserved_0(void);
	virtual void reserved_1(void);
	virtual void reserved_2(void);
	virtual void reserved_3(void);
	virtual void reserved_4(void);
	virtual void reserved_5(void);
	virtual void reserved_6(void);
	virtual void reserved_7(void);
	virtual void reserved_8(void);
	virtual void reserved_9(void);
	virtual void reserved_10(void);
	virtual void reserved_11(void);
	virtual void reserved_12(void);
	virtual void reserved_13(void);
	virtual void reserved_14(void);
	virtual void reserved_15(void);
	virtual void reserved_16(void);
	virtual void reserved_17(void);
	virtual void reserved_18(void);
	virtual void reserved_19(void);
	virtual void reserved_20(void);
	virtual void reserved_21(void);
	virtual void reserved_22(void);
	virtual void reserved_23(void);
	virtual void reserved_24(void);
	virtual void reserved_25(void);
	virtual void reserved_26(void);
	virtual void reserved_27(void);
	virtual void reserved_28(void);
	virtual void reserved_29(void);
	virtual void reserved_30(void);
	virtual void reserved_31(void);
	virtual void reserved_32(void);
	virtual void reserved_33(void);
	virtual void reserved_34(void);
	virtual void reserved_35(void);
	virtual void reserved_36(void);
	virtual void reserved_37(void);
	virtual void reserved_38(void);
	virtual void reserved_39(void);
	virtual void reserved_40(void);
	virtual void reserved_41(void);
	virtual void reserved_42(void);
	virtual void reserved_43(void);
	virtual void reserved_44(void);
	virtual void reserved_45(void);
	virtual void reserved_46(void);
	virtual void reserved_47(void);
	virtual void reserved_48(void);
	virtual void reserved_49(void);
	virtual void reserved_50(void);
	virtual void reserved_51(void);
	virtual void reserved_52(void);
	virtual void reserved_53(void);
	virtual void reserved_54(void);
	virtual void reserved_55(void);
	virtual void reserved_56(void);
	virtual void reserved_57(void);
	virtual void reserved_58(void);
	virtual void reserved_59(void);
	virtual void reserved_60(void);
	virtual void reserved_61(void);
	virtual void reserved_62(void);
	virtual void reserved_63(void);
	virtual void reserved_64(void);
	virtual void reserved_65(void);
	virtual void Get_Obj_Space_Bounding_Sphere(SphereClass &);

	unsigned char Prefix[0x14];
	Matrix3D Transform;
	unsigned char BeforeTail[0x80];
	unsigned int MaxSubdivisionLevels;
	unsigned int *Personalities;
	float NormalizedScreenArea;
	SimpleDynVecClass<Vector3> PointLocations;
	SimpleDynVecClass<Vector4> PointColors;
	SimpleDynVecClass<float> PointWidths;
	SegLineRendererClass LineRenderer;

protected:
	void Render_Seg_Line(RenderInfoClass &);
};

// ?Render_Seg_Line@StreakLineClass@@IAEXAAVRenderInfoClass@@@Z
void StreakLineClass::Render_Seg_Line(RenderInfoClass &rinfo)
{
	if (PointLocations.ActiveCount < 2) {
		return;
	}

	SphereClass boundingSphere;
	Get_Obj_Space_Bounding_Sphere(boundingSphere);

	LineRenderer.Render(
		rinfo,
		Transform,
		PointLocations.ActiveCount,
		PointLocations.Vector,
		boundingSphere);
}
