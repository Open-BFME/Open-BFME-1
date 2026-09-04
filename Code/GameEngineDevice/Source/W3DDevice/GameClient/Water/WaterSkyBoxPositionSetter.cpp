// cl: /DNDEBUG /MD /EHs-c-

struct Vector3
{
    float X;
    float Y;
    float Z;
};

struct GlobalData
{
    char m_beforeDrawSkyBox[0x180];
    float m_drawSkyBox;
};

class SkyBoxRenderObject
{
public:
    virtual void slot00(void);
    virtual void slot01(void);
    virtual void slot02(void);
    virtual void slot03(void);
    virtual void slot04(void);
    virtual void slot05(void);
    virtual void slot06(void);
    virtual void slot07(void);
    virtual void slot08(void);
    virtual void slot09(void);
    virtual void slot10(void);
    virtual void slot11(void);
    virtual void setPosition(const Vector3 &position);
};

class WaterSkyBoxPositionAccessor
{
public:
    void setSkyBoxPosition(const Vector3 &position);

private:
    char m_beforeSkyBox[0x250];
    SkyBoxRenderObject *m_skyBox;
};

extern GlobalData *TheWritableGlobalData;

// ?setSkyBoxPosition@WaterSkyBoxPositionAccessor@@QAEXABVVector3@@@Z
void WaterSkyBoxPositionAccessor::setSkyBoxPosition(const Vector3 &position)
{
    if (TheWritableGlobalData->m_drawSkyBox != 0.0f)
        m_skyBox->setPosition(position);
}
