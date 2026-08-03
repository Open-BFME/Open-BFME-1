// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: query a retail RenderObjClass bone and copy its Matrix3D.

class Matrix3D
{
    unsigned long m_data[12];

public:
    __forceinline Matrix3D &operator=(const Matrix3D &other)
    {
        m_data[0] = other.m_data[0];
        m_data[1] = other.m_data[1];
        m_data[2] = other.m_data[2];
        m_data[3] = other.m_data[3];
        m_data[4] = other.m_data[4];
        m_data[5] = other.m_data[5];
        m_data[6] = other.m_data[6];
        m_data[7] = other.m_data[7];
        m_data[8] = other.m_data[8];
        m_data[9] = other.m_data[9];
        m_data[10] = other.m_data[10];
        m_data[11] = other.m_data[11];
        return *this;
    }
};

class RenderObjClassVtablePrefix
{
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
    virtual void f41() = 0;
    virtual void f42() = 0;
    virtual void f43() = 0;
    virtual void f44() = 0;
    virtual void f45() = 0;
    virtual void f46() = 0;
    virtual void f47() = 0;
    virtual void f48() = 0;
};

class RenderObjClass : public RenderObjClassVtablePrefix
{
public:
    virtual int Get_Bone_Index(const char *);
    virtual const Matrix3D &Get_Bone_Transform(int);
};

class W3DModelDraw
{
    unsigned char m_padding04[0x24];
    RenderObjClass *m_renderObject;

public:
    virtual bool getCurrentWorldspaceClientBonePositions(const char *, Matrix3D &) const;
};

// ?getCurrentWorldspaceClientBonePositions@W3DModelDraw@@UBE_NPBDAAVMatrix3D@@@Z
bool W3DModelDraw::getCurrentWorldspaceClientBonePositions(
    const char *boneName,
    Matrix3D &transform) const
{
    if (!m_renderObject)
        return false;

    int boneIndex = m_renderObject->Get_Bone_Index(boneName);
    if (boneIndex == 0)
        return false;

    transform = m_renderObject->Get_Bone_Transform(boneIndex);
    return true;
}
