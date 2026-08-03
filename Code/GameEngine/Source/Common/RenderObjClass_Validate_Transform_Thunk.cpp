// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: recurse dirty RenderObjClass parents and refresh transform state.

class Matrix3D
{
    unsigned long m_data[12];

public:
    bool Check_Is_Transform_Identity() const;
};

class RenderObjClass
{
    unsigned long m_refCount;
    unsigned long m_secondaryVtable;
    unsigned long m_unknown0c;
    unsigned long m_bits;
    unsigned long m_unknown14;
    Matrix3D m_transform;
    unsigned char m_padding48[0x34];
    mutable bool m_isTransformIdentity;
    unsigned char m_padding7d[7];
    RenderObjClass *m_container;

public:
    virtual void f00() = 0;
    virtual void f01() = 0;
    virtual void f02() = 0;
    virtual void f03() = 0;
    virtual void f04() = 0;
    virtual void f05() = 0;
    virtual void f06() = 0;
    virtual void f07() = 0;
    virtual void f08() = 0;
    virtual void f09() = 0;
    virtual void f10() = 0;
    virtual void f11() = 0;
    virtual void f12() = 0;
    virtual void f13() = 0;
    virtual void f14() = 0;
    virtual void f15() = 0;
    virtual void f16() = 0;
    virtual void f17() = 0;
    virtual void f18() = 0;
    virtual void f19() = 0;
    virtual void f20() = 0;
    virtual void f21() = 0;
    virtual void f22() = 0;
    virtual void f23() = 0;
    virtual void f24() = 0;
    virtual void f25() = 0;
    virtual void f26() = 0;
    virtual void f27() = 0;
    virtual void f28() = 0;
    virtual void f29() = 0;
    virtual void f30() = 0;
    virtual void f31() = 0;
    virtual void f32() = 0;
    virtual void f33() = 0;
    virtual void f34() = 0;
    virtual void f35() = 0;
    virtual void f36() = 0;
    virtual void f37() = 0;
    virtual void f38() = 0;
    virtual void f39() = 0;
    virtual void f40() = 0;
    virtual void Update_Sub_Object_Transforms();
    virtual void Validate_Transform() const;

    RenderObjClass *Get_Container() const { return m_container; }
    bool Are_Sub_Object_Transforms_Dirty() const { return (m_bits & 0x00200000) != 0; }
};

// ?Validate_Transform@RenderObjClass@@UBEXXZ
void RenderObjClass::Validate_Transform() const
{
    RenderObjClass *con = Get_Container();
    bool dirty = false;
    if (con != 0)
    {
        dirty = con->Are_Sub_Object_Transforms_Dirty();
        while (con->Get_Container() != 0)
        {
            dirty |= con->Are_Sub_Object_Transforms_Dirty();
            con = con->Get_Container();
        }
        if (dirty)
            con->Update_Sub_Object_Transforms();
    }
    if (dirty)
        m_isTransformIdentity = m_transform.Check_Is_Transform_Identity();
}
