// cl: /DNDEBUG /MD /EHs-c-

struct Vector3
{
    float X;
    float Y;
    float Z;
};

// TU-local VIEW of the real GlobalData, kept only for its offsets.  It must
// NOT be named GlobalData: MSVC mangles a global's TYPE into its symbol, and
// retail's global at 0x012ED5C8 is `GlobalData *TheWritableGlobalData`.
struct WaterSkyBoxGlobalView
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

// retail 0x012ED5C8 is EA's `GlobalData *TheWritableGlobalData`, defined once
// in Common/GlobalData.cpp.  `struct` vs `class` changes the mangled name, so
// the view above is cast at the use instead.
class GlobalData;
extern GlobalData *TheWritableGlobalData;

// ?setSkyBoxPosition@WaterSkyBoxPositionAccessor@@QAEXABUVector3@@@Z
void WaterSkyBoxPositionAccessor::setSkyBoxPosition(const Vector3 &position)
{
    if (((WaterSkyBoxGlobalView *)TheWritableGlobalData)->m_drawSkyBox != 0.0f)
        m_skyBox->setPosition(position);
}
