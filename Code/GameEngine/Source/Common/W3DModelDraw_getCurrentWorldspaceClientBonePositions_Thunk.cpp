// cl: /DNDEBUG /MD /EHsc

class Matrix3D
{
public:
    unsigned int values[12];

    __forceinline Matrix3D &operator=(const Matrix3D &that)
    {
        values[0] = that.values[0];
        values[1] = that.values[1];
        values[2] = that.values[2];
        values[3] = that.values[3];
        values[4] = that.values[4];
        values[5] = that.values[5];
        values[6] = that.values[6];
        values[7] = that.values[7];
        values[8] = that.values[8];
        values[9] = that.values[9];
        values[10] = that.values[10];
        values[11] = that.values[11];
        return *this;
    }
};

class RenderObject
{
public:
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void slot16() = 0;
    virtual void slot17() = 0;
    virtual void slot18() = 0;
    virtual void slot19() = 0;
    virtual void slot20() = 0;
    virtual void slot21() = 0;
    virtual void slot22() = 0;
    virtual void slot23() = 0;
    virtual void slot24() = 0;
    virtual void slot25() = 0;
    virtual void slot26() = 0;
    virtual void slot27() = 0;
    virtual void slot28() = 0;
    virtual void slot29() = 0;
    virtual void slot30() = 0;
    virtual void slot31() = 0;
    virtual void slot32() = 0;
    virtual void slot33() = 0;
    virtual void slot34() = 0;
    virtual void slot35() = 0;
    virtual void slot36() = 0;
    virtual void slot37() = 0;
    virtual void slot38() = 0;
    virtual void slot39() = 0;
    virtual void slot40() = 0;
    virtual void slot41() = 0;
    virtual void slot42() = 0;
    virtual void slot43() = 0;
    virtual void slot44() = 0;
    virtual void slot45() = 0;
    virtual void slot46() = 0;
    virtual void slot47() = 0;
    virtual void slot48() = 0;
    virtual int Get_Bone_Index(const char *boneName) = 0;
    virtual const Matrix3D &Get_Bone_Transform(int boneIndex) = 0;
};

class W3DModelDraw
{
public:
    virtual bool getCurrentWorldspaceClientBonePositions(const char *boneName,
                                                          Matrix3D &transform) const;

private:
    unsigned char m_padding[0x24];
    RenderObject *m_renderObject;
};

// ?getCurrentWorldspaceClientBonePositions@W3DModelDraw@@UBE_NPBDAAVMatrix3D@@@Z
bool W3DModelDraw::getCurrentWorldspaceClientBonePositions(const char *boneName,
                                                            Matrix3D &transform) const
{
    if (m_renderObject == 0) {
        return false;
    }

    int boneIndex = m_renderObject->Get_Bone_Index(boneName);
    if (boneIndex == 0) {
        return false;
    }

    transform = m_renderObject->Get_Bone_Transform(boneIndex);
    return true;
}
