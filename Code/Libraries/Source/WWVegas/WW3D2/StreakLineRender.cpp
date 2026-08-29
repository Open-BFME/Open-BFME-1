// cl: /DNDEBUG /MD /EHsc

class RenderInfoClass;

class Matrix3D
{
    float values[12];
};

class Vector3 {};
class Vector4 {};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/sphere.h
class SphereClass
{
    float values[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/streakRender.h
class StreakRendererClass
{
public:
    void RenderStreak(RenderInfoClass &, const Matrix3D &, unsigned int, Vector3 *, Vector4 *, float *,
        const SphereClass &, unsigned int *);
};

template <class Type>
struct RetailPointContainer
{
    Type *data;
    int capacity;
    int count;
    int growth;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/streak.h
class StreakLineClass
{
    virtual void reserved_0();
    virtual void reserved_1();
    virtual void reserved_2();
    virtual void reserved_3();
    virtual void reserved_4();
    virtual void reserved_5();
    virtual void reserved_6();
    virtual void reserved_7();
    virtual void reserved_8();
    virtual void reserved_9();
    virtual void reserved_10();
    virtual void reserved_11();
    virtual void reserved_12();
    virtual void reserved_13();
    virtual void reserved_14();
    virtual void reserved_15();
    virtual void reserved_16();
    virtual void reserved_17();
    virtual void reserved_18();
    virtual void reserved_19();
    virtual void reserved_20();
    virtual void reserved_21();
    virtual void reserved_22();
    virtual void reserved_23();
    virtual void reserved_24();
    virtual void reserved_25();
    virtual void reserved_26();
    virtual void reserved_27();
    virtual void reserved_28();
    virtual void reserved_29();
    virtual void reserved_30();
    virtual void reserved_31();
    virtual void reserved_32();
    virtual void reserved_33();
    virtual void reserved_34();
    virtual void reserved_35();
    virtual void reserved_36();
    virtual void reserved_37();
    virtual void reserved_38();
    virtual void reserved_39();
    virtual void reserved_40();
    virtual void reserved_41();
    virtual void reserved_42();
    virtual void reserved_43();
    virtual void reserved_44();
    virtual void reserved_45();
    virtual void reserved_46();
    virtual void reserved_47();
    virtual void reserved_48();
    virtual void reserved_49();
    virtual void reserved_50();
    virtual void reserved_51();
    virtual void reserved_52();
    virtual void reserved_53();
    virtual void reserved_54();
    virtual void reserved_55();
    virtual void reserved_56();
    virtual void reserved_57();
    virtual void reserved_58();
    virtual void reserved_59();
    virtual void reserved_60();
    virtual void reserved_61();
    virtual void reserved_62();
    virtual void reserved_63();
    virtual void reserved_64();
    virtual void reserved_65();
    virtual void Get_Obj_Space_Bounding_Sphere(SphereClass &);

    unsigned char prefix[0x14];
    Matrix3D Transform;
    unsigned char beforePersonalities[0x84];
    unsigned int *Personalities;
    unsigned char beforeLocations[8];
    RetailPointContainer<Vector3> PointLocations;
    RetailPointContainer<Vector4> PointColors;
    RetailPointContainer<float> PointWidths;
    unsigned char beforeRenderer[0x4c];
    StreakRendererClass StreakRenderer;

protected:
    void Render_Streak_Line(RenderInfoClass &);
};

// ?Render_Streak_Line@StreakLineClass@@ present-unmatched
void StreakLineClass::Render_Streak_Line(RenderInfoClass &renderInfo)
{
    if (PointLocations.count < 2) return;
    if (PointColors.count < 2) return;
    if (PointWidths.count < 2) return;
    if (PointLocations.count != PointColors.count) return;
    if (PointLocations.count != PointWidths.count) return;

    SphereClass boundingSphere;
    Get_Obj_Space_Bounding_Sphere(boundingSphere);

    StreakRenderer.RenderStreak(
        renderInfo,
        Transform,
        PointLocations.count,
        PointLocations.data,
        PointColors.data,
        PointWidths.data,
        boundingSphere,
        Personalities);
}
