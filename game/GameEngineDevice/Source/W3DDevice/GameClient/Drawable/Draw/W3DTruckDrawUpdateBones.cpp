// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWAudio /Igame/Libraries/Source/Compression /Iinputs/reference/shims/sweep
// W3DTruckDraw::updateBones at RVA 0x00780170, complete 3705-byte body.
// Started from the banked reconstruction; factory/constructor and module parser
// evidence establish the owner and fields. See targets/game/reverse/identity_evidence/00780170.md.
// The secondary tire and cab diagnostics intentionally keep retail's reversed
// condition: those seven reports run for a nonzero bone index. Do not normalize
// them to the primary-pair checks without changing the original behavior.
// The debug helper preserves evaluation of model, bone name, report receiver,
// and model name in that order. Native headers supply strings, render objects,
// and the 512-byte Debug::Format temporary. No assembly is used.
#include "ascii_string.h"
#include "rendobj.h"
#include "debug.h"
template<> inline bool StringBase<char>::isEmpty() const { return !m_data || m_data->length == 0; }
class TruckBoneCrashMessage
{
public:
    TruckBoneCrashMessage &operator<<(const Debug::Format &value) { setText((const char *)&value); return *this; }

	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual void setText(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual void show(int mode);
};

struct Rva00889690Obj
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void beginReport();
	virtual void slot64(); virtual void slot68();
	virtual TruckBoneCrashMessage *getCrashMessage(void *first, void *second);
};

extern Rva00889690Obj *g_rva00889690;
bool _bfme_debugReportingEnabled();
void _bfme_debugRecordCallsite(int kind);

static __forceinline void reportMissingBone(const char *format, const char *name, RenderObjClass *model)
{
    TruckBoneCrashMessage *out = g_rva00889690->getCrashMessage(0,0);
    (*out << Debug::Format(format,name,model->Get_Name())).show(2);
}
#define REPORT_MISSING(format, name, model) do { RenderObjClass *object = model; const char *boneName = name; reportMissingBone(format, boneName, object); } while (0)
#define TRUCK_ASSERT(condition, message) do { \
    if (!(condition) && _bfme_debugReportingEnabled()) { \
        _bfme_debugRecordCallsite(1); \
        g_rva00889690->beginReport(); \
        REPORT_MISSING message; \
    } \
} while (0)
class W3DTruckDrawModuleData {
public:
    char prefix[0x168];
    AsciiString m_frontLeftTireBoneName;
    AsciiString m_frontRightTireBoneName;
    AsciiString m_rearLeftTireBoneName;
    AsciiString m_rearRightTireBoneName;
    AsciiString m_midFrontLeftTireBoneName;
    AsciiString m_midFrontRightTireBoneName;
    AsciiString m_midRearLeftTireBoneName;
    AsciiString m_midRearRightTireBoneName;
    AsciiString m_midMidLeftTireBoneName;
    AsciiString m_midMidRightTireBoneName;
    AsciiString field190;
    AsciiString field194;
    AsciiString field198;
    AsciiString field19c;
    AsciiString field1a0;
    AsciiString field1a4;
    AsciiString m_cabBoneName, m_trailerBoneName;
};
class W3DTruckDraw {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3c();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4c();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5c();
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void slot6c();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual void slot7c();
    virtual void slot80();
    virtual void slot84();
    virtual void slot88();
    virtual void slot8c();
    virtual void slot90();
    virtual void slot94();
    virtual void slot98();
    virtual void slot9c();
    virtual void slota0();
    virtual void slota4();
    virtual void slota8();
    virtual void slotac();
    virtual void slotb0();
    virtual void slotb4();
    virtual RenderObjClass *getRenderObject() const;
    W3DTruckDrawModuleData *data;
    char gap008[0x2b4-8];
    int m_frontLeftTireBone, m_frontRightTireBone;
    int m_rearLeftTireBone, m_rearRightTireBone;
    int m_midFrontLeftTireBone, m_midFrontRightTireBone;
    int m_midRearLeftTireBone, m_midRearRightTireBone;
    int m_midMidLeftTireBone, m_midMidRightTireBone;
    int m_secondaryFrontLeftTireBone, m_secondaryFrontRightTireBone;
    int m_secondaryRearLeftTireBone, m_secondaryRearRightTireBone;
    int m_secondaryMidMidLeftTireBone, m_secondaryMidMidRightTireBone;
    int m_cabBone, field2f8, m_trailerBone, field300, m_prevNumBones;
    char gap308[0x3e8-0x308];
    RenderObjClass *m_prevRenderObj;
    const W3DTruckDrawModuleData *getW3DTruckDrawModuleData() const { return data; }
protected:
    virtual void onRenderObjRecreated(void);
    void updateBones();
};
void W3DTruckDraw::updateBones()
{
    if (getW3DTruckDrawModuleData()) {
        if (!getW3DTruckDrawModuleData()->m_frontLeftTireBoneName.isEmpty()) {
            m_frontLeftTireBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->m_frontLeftTireBoneName.str());
            TRUCK_ASSERT(m_frontLeftTireBone, ("Missing front-left tire bone %s in model %s\n", getW3DTruckDrawModuleData()->m_frontLeftTireBoneName.str(), getRenderObject()));
            m_frontRightTireBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->m_frontRightTireBoneName.str());
            TRUCK_ASSERT(m_frontRightTireBone, ("Missing front-right tire bone %s in model %s\n", getW3DTruckDrawModuleData()->m_frontRightTireBoneName.str(), getRenderObject()));
            if (!m_frontRightTireBone) m_frontLeftTireBone = 0;
        }
        if (!getW3DTruckDrawModuleData()->m_rearLeftTireBoneName.isEmpty()) {
            m_rearLeftTireBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->m_rearLeftTireBoneName.str());
            TRUCK_ASSERT(m_rearLeftTireBone, ("Missing rear-left tire bone %s in model %s\n", getW3DTruckDrawModuleData()->m_rearLeftTireBoneName.str(), getRenderObject()));
            m_rearRightTireBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->m_rearRightTireBoneName.str());
            TRUCK_ASSERT(m_rearRightTireBone, ("Missing rear-left tire bone %s in model %s\n", getW3DTruckDrawModuleData()->m_rearRightTireBoneName.str(), getRenderObject()));
            if (!m_rearRightTireBone) m_rearLeftTireBone = 0;
        }
        if (!getW3DTruckDrawModuleData()->m_midFrontLeftTireBoneName.isEmpty()) {
            m_midFrontLeftTireBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->m_midFrontLeftTireBoneName.str());
            TRUCK_ASSERT(m_midFrontLeftTireBone, ("Missing mid-front-left tire bone %s in model %s\n", getW3DTruckDrawModuleData()->m_midFrontLeftTireBoneName.str(), getRenderObject()));
            m_midFrontRightTireBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->m_midFrontRightTireBoneName.str());
            TRUCK_ASSERT(m_midFrontRightTireBone, ("Missing mid-front-right tire bone %s in model %s\n", getW3DTruckDrawModuleData()->m_midFrontRightTireBoneName.str(), getRenderObject()));
            if (!m_midFrontRightTireBone) m_midFrontLeftTireBone = 0;
        }
        if (!getW3DTruckDrawModuleData()->m_midRearLeftTireBoneName.isEmpty()) {
            m_midRearLeftTireBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->m_midRearLeftTireBoneName.str());
            TRUCK_ASSERT(m_midRearLeftTireBone, ("Missing mid-rear-left tire bone %s in model %s\n", getW3DTruckDrawModuleData()->m_midRearLeftTireBoneName.str(), getRenderObject()));
            m_midRearRightTireBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->m_midRearRightTireBoneName.str());
            TRUCK_ASSERT(m_midRearRightTireBone, ("Missing mid-rear-right tire bone %s in model %s\n", getW3DTruckDrawModuleData()->m_midRearRightTireBoneName.str(), getRenderObject()));
            if (!m_midRearRightTireBone) m_midRearLeftTireBone = 0;
        }
        if (!getW3DTruckDrawModuleData()->m_midMidLeftTireBoneName.isEmpty()) {
            m_midMidLeftTireBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->m_midMidLeftTireBoneName.str());
            TRUCK_ASSERT(m_midMidLeftTireBone, ("Missing mid-mid-left tire bone %s in model %s\n", getW3DTruckDrawModuleData()->m_midMidLeftTireBoneName.str(), getRenderObject()));
            m_midMidRightTireBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->m_midMidRightTireBoneName.str());
            TRUCK_ASSERT(m_midMidRightTireBone, ("Missing mid-mid-right tire bone %s in model %s\n", getW3DTruckDrawModuleData()->m_midMidRightTireBoneName.str(), getRenderObject()));
            if (!m_midMidRightTireBone) m_midMidLeftTireBone = 0;
        }
        if (!getW3DTruckDrawModuleData()->field190.isEmpty()) {
            m_secondaryFrontLeftTireBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->field190.str());
            TRUCK_ASSERT(!m_secondaryFrontLeftTireBone, ("Missing secondary front-left tire bone %s in model %s\n", getW3DTruckDrawModuleData()->field190.str(), getRenderObject()));
            m_secondaryFrontRightTireBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->field194.str());
            TRUCK_ASSERT(!m_secondaryFrontRightTireBone, ("Missing secondary front-right tire bone %s in model %s\n", getW3DTruckDrawModuleData()->field194.str(), getRenderObject()));
            if (!m_secondaryFrontRightTireBone) m_secondaryFrontLeftTireBone = 0;
            if (m_secondaryFrontLeftTireBone && !m_frontLeftTireBone) m_secondaryFrontLeftTireBone = 0;
            if (m_secondaryFrontRightTireBone && !m_frontRightTireBone) m_secondaryFrontRightTireBone = 0;
        }
        if (!getW3DTruckDrawModuleData()->field198.isEmpty()) {
            m_secondaryRearLeftTireBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->field198.str());
            TRUCK_ASSERT(!m_secondaryRearLeftTireBone, ("Missing secondary rear-left tire bone %s in model %s\n", getW3DTruckDrawModuleData()->field198.str(), getRenderObject()));
            m_secondaryRearRightTireBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->field19c.str());
            TRUCK_ASSERT(!m_secondaryRearRightTireBone, ("Missing rear-left tire bone %s in model %s\n", getW3DTruckDrawModuleData()->field19c.str(), getRenderObject()));
            if (!m_secondaryRearRightTireBone) m_secondaryRearLeftTireBone = 0;
            if (m_secondaryRearLeftTireBone && !m_rearLeftTireBone) m_secondaryRearLeftTireBone = 0;
            if (m_secondaryRearRightTireBone && !m_rearRightTireBone) m_secondaryRearRightTireBone = 0;
        }
        if (!getW3DTruckDrawModuleData()->field1a0.isEmpty()) {
            m_secondaryMidMidLeftTireBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->field1a0.str());
            TRUCK_ASSERT(!m_secondaryMidMidLeftTireBone, ("Missing secondary mid-mid-left tire bone %s in model %s\n", getW3DTruckDrawModuleData()->field1a0.str(), getRenderObject()));
            m_secondaryMidMidRightTireBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->field1a4.str());
            TRUCK_ASSERT(!m_secondaryMidMidRightTireBone, ("Missing secondary mid-mid-right tire bone %s in model %s\n", getW3DTruckDrawModuleData()->field1a4.str(), getRenderObject()));
            if (!m_secondaryMidMidRightTireBone) m_secondaryMidMidLeftTireBone = 0;
            if (m_secondaryMidMidLeftTireBone && !m_midMidLeftTireBone) m_secondaryMidMidLeftTireBone = 0;
            if (m_secondaryMidMidRightTireBone && !m_midMidRightTireBone) m_secondaryMidMidRightTireBone = 0;
        }
        if (!getW3DTruckDrawModuleData()->m_cabBoneName.isEmpty()) {
            m_cabBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->m_cabBoneName.str());
            TRUCK_ASSERT(!m_cabBone, ("Missing cab bone %s in model %s\n", getW3DTruckDrawModuleData()->m_cabBoneName.str(), getRenderObject()));
            m_trailerBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->m_trailerBoneName.str());
        }
    }
    m_prevRenderObj = getRenderObject();
    m_prevNumBones = m_prevRenderObj->Get_Num_Bones();
}

// W3DTruckDraw::onRenderObjRecreated, retail 0x00781440 (104 bytes): no ledger
// row covered it; it fills the W3DTruckDraw vtable slot at rdata 0x00D22F98.
// ZH's body with BFME's extra tire bones: forget the cached render object and
// every bone index, then rebuild them (a tail jump into updateBones).
void W3DTruckDraw::onRenderObjRecreated(void)
{
    m_prevRenderObj = NULL;
    m_frontLeftTireBone = 0;
    m_frontRightTireBone = 0;
    m_rearLeftTireBone = 0;
    m_rearRightTireBone = 0;
    m_midFrontLeftTireBone = 0;
    m_midFrontRightTireBone = 0;
    m_midRearLeftTireBone = 0;
    m_midRearRightTireBone = 0;
    m_midMidLeftTireBone = 0;
    m_midMidRightTireBone = 0;
    m_secondaryFrontLeftTireBone = 0;
    m_secondaryFrontRightTireBone = 0;
    m_secondaryRearLeftTireBone = 0;
    m_secondaryRearRightTireBone = 0;
    m_secondaryMidMidLeftTireBone = 0;
    m_secondaryMidMidRightTireBone = 0;
    updateBones();
}
