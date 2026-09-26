// cl: /DNDEBUG /MD /EHsc

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

class SphereClass
{
    float Values[4];
};

class SegLineRendererClass
{
public:
    void Render(RenderInfoClass &, const Matrix3D &, unsigned int, Vector3 *,
        const SphereClass &, Vector4 * = 0);
};

template <class Type>
class SimpleDynVecClass
{
public:
    virtual ~SimpleDynVecClass();

    Type *Vector;
    int VectorMax;
    int ActiveCount;
};

class SegmentedLineClass
{
public:
    virtual void Reserved_0();
    virtual void Reserved_1();
    virtual void Reserved_2();
    virtual void Reserved_3();
    virtual void Reserved_4();
    virtual void Reserved_5();
    virtual void Reserved_6();
    virtual void Reserved_7();
    virtual void Reserved_8();
    virtual void Reserved_9();
    virtual void Reserved_10();
    virtual void Reserved_11();
    virtual void Reserved_12();
    virtual void Reserved_13();
    virtual void Reserved_14();
    virtual void Reserved_15();
    virtual void Reserved_16();
    virtual void Reserved_17();
    virtual void Reserved_18();
    virtual void Reserved_19();
    virtual void Reserved_20();
    virtual void Reserved_21();
    virtual void Reserved_22();
    virtual void Reserved_23();
    virtual void Reserved_24();
    virtual void Reserved_25();
    virtual void Reserved_26();
    virtual void Reserved_27();
    virtual void Reserved_28();
    virtual void Reserved_29();
    virtual void Reserved_30();
    virtual void Reserved_31();
    virtual void Reserved_32();
    virtual void Reserved_33();
    virtual void Reserved_34();
    virtual void Reserved_35();
    virtual void Reserved_36();
    virtual void Reserved_37();
    virtual void Reserved_38();
    virtual void Reserved_39();
    virtual void Reserved_40();
    virtual void Reserved_41();
    virtual void Reserved_42();
    virtual void Reserved_43();
    virtual void Reserved_44();
    virtual void Reserved_45();
    virtual void Reserved_46();
    virtual void Reserved_47();
    virtual void Reserved_48();
    virtual void Reserved_49();
    virtual void Reserved_50();
    virtual void Reserved_51();
    virtual void Reserved_52();
    virtual void Reserved_53();
    virtual void Reserved_54();
    virtual void Reserved_55();
    virtual void Reserved_56();
    virtual void Reserved_57();
    virtual void Reserved_58();
    virtual void Reserved_59();
    virtual void Reserved_60();
    virtual void Reserved_61();
    virtual void Reserved_62();
    virtual void Reserved_63();
    virtual void Reserved_64();
    virtual void Reserved_65();
    virtual void Get_Obj_Space_Bounding_Sphere(SphereClass &);

private:
    unsigned char Prefix[0x14];
    Matrix3D Transform;
    unsigned char BeforePointLocations[0x88];
    SimpleDynVecClass<Vector3> PointLocations;
    SegLineRendererClass LineRenderer;

protected:
    void Render_Seg_Line(RenderInfoClass &);
};

void SegmentedLineClass::Render_Seg_Line(RenderInfoClass &rinfo)
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
