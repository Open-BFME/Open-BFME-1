// ?setupWaypointPath@W3DView@@AAEXH_NMM@Z
// partial score=0.68 date=2026-09-11
// BFME W3DView waypoint-path setup.
//
// The retail body at 0x00740F60 is the private four-argument companion used
// by W3DView's waypoint-path entry point.  The deliberately sparse virtual
// declarations below preserve the retail ABI slots while keeping the source
// independent of the much larger, still-being-recovered W3D headers.
//
// Confirmed real bug fixed vs the prior 0.65 stash: retail stores each
// waypoint's segment length through an Int-reinterpreted round trip
// (fstp to a stack temp, reload as int, reload as float, int-store into the
// array, then add the reloaded float) rather than a direct float store; see
// the RealBits round trip below. This moved the first divergence from +0x4b
// to +0x7d (probe.py, confirmed).

typedef int Int;
typedef float Real;
typedef bool Bool;

struct Coord3D {
    Real x;
    Real y;
    Real z;
};

struct WaypointRecord {
    Coord3D position;
    void *name;
    Int flags;
};

class Rva00740440 {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void configure(Int value, Int duration, Int first, Int second,
                           Int stored, Int unused);

    void setCameraPathAngles(Bool orient, Real angle, Int firstWaypoint);

    char m_padding0004[0x2c - 4];
    WaypointRecord m_waypoints[255];
    WaypointRecord m_extraWaypoints[4];
    Real m_cameraAngles[256];
    Real m_waySegmentLengths[256];
    Real m_totalDistance;
    Real m_initialGroundHeight;
    Real m_finalGroundHeight;
    char m_padding1c74[0x2070 - 0x1c74];
    Int m_numWaypoints;
};

class Rva0045A000 {
public:
    char m_padding0000[0x1c];
    Bool m_ready;
    char m_padding001d[0x70 - 0x1d];
};

struct Rva003FD060TerrainLogic {
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual Real getGroundHeight(Real x, Real y) = 0;
};

extern Rva003FD060TerrainLogic *TheTerrainLogic;
extern void j_00046fa1(void);
extern Real g_bfmeK1253;

union RealBits {
    Real value;
    Int bits;
};

static __forceinline Real squareRoot(Real value)
{
    __asm {
        fld value
        fsqrt
    }
}

class W3DView {
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
    virtual void slot27(Int value) = 0;
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
    virtual void slot49() = 0;
    virtual void slot50() = 0;
    virtual void slot51() = 0;
    virtual void slot52() = 0;
    virtual void slot53() = 0;
    virtual void slot54() = 0;
    virtual void slot55() = 0;
    virtual void slot56() = 0;
    virtual void slot57() = 0;
    virtual void slot58() = 0;
    virtual void slot59() = 0;
    virtual void slot60() = 0;
    virtual void slot61() = 0;
    virtual void slot62() = 0;
    virtual Real slot63() = 0;

private:
    void setupWaypointPath(Int shutter, Bool orient, Real easeIn,
                           Real easeOut);

    char m_padding0004[0x1dc - 4];
    Bool m_doingRotateCamera;
    char m_padding01dd[0x280 - 0x1dd];
    Rva00740440 m_cameraPath;
    char m_padding22f4[0x2354 - 0x22f4];
    Int m_cameraMovementMode;
    char m_padding2358[0x23c4 - 0x2358];
    Int m_timeMultiplierDefault;
    char m_padding23c8[0x23f8 - 0x23c8];
    Real m_groundLevel;
    char m_padding23fc[0x2448 - 0x23fc];
    Rva0045A000 m_heightField;
};

void W3DView::setupWaypointPath(Int shutter, Bool orient, Real easeIn,
                                 Real easeOut)
{
    m_cameraPath.configure(m_timeMultiplierDefault, shutter,
                           *(Int *)&easeIn, *(Int *)&easeOut, 0, 1);

    Int waypointCount = m_cameraPath.m_numWaypoints;
    Int waypoint = 1;
    m_cameraPath.m_totalDistance = 0.0f;
    if (waypointCount > 1) {
        Real *segmentLength = m_cameraPath.m_waySegmentLengths;
        Real *point = &m_cameraPath.m_waypoints[1].position.y;
        do {
            Real dx = point[4] - point[-1];
            Real dy = point[5] - point[0];
            easeIn = dx * dx + dy * dy;
            RealBits d;
            d.value = squareRoot(easeIn);
            *(Int *)segmentLength = d.bits;
            m_cameraPath.m_totalDistance += d.value;
            ++waypoint;
            ++segmentLength;
            point += 5;
        } while (waypoint < m_cameraPath.m_numWaypoints);
    }

    m_cameraPath.m_waySegmentLengths[-1] = 0.0f;
    m_cameraPath.m_waySegmentLengths[m_cameraPath.m_numWaypoints - 1] = 0.0f;
    m_cameraPath.m_waySegmentLengths[m_cameraPath.m_numWaypoints] = 0.0f;

    Rva00740440 *path = &m_cameraPath;
    path->setCameraPathAngles(orient, slot63(), -1);

    Real startAngle = slot63();
    path->m_cameraAngles[1] = startAngle;
    path->m_cameraAngles[m_cameraPath.m_numWaypoints + 1] =
        path->m_cameraAngles[m_cameraPath.m_numWaypoints];
    path->m_cameraAngles[0] = path->m_cameraAngles[1];
    path->m_cameraAngles[m_cameraPath.m_numWaypoints] =
        path->m_cameraAngles[m_cameraPath.m_numWaypoints - 1];
    path->m_cameraAngles[m_cameraPath.m_numWaypoints + 1] =
        path->m_cameraAngles[m_cameraPath.m_numWaypoints];

    Int lastAngle = m_cameraPath.m_numWaypoints - 1;
    if (lastAngle - 1 >= 4) {
        Int groups = ((lastAngle - 5) >> 2) + 1;
        Real *angle = &path->m_cameraAngles[lastAngle - 2];
        Int remaining = groups;
        do {
            Real smoothed = *angle;
            angle -= 4;
            smoothed += angle[5];
            smoothed *= g_bfmeK1253;
            angle[5] = smoothed;
            smoothed = angle[4] + angle[3];
            smoothed *= g_bfmeK1253;
            angle[4] = smoothed;
            smoothed = angle[3] + angle[2];
            smoothed *= g_bfmeK1253;
            angle[3] = smoothed;
            smoothed = angle[1] + angle[3];
            smoothed *= g_bfmeK1253;
            angle[3] = smoothed;
            --remaining;
        } while (remaining != 0);
    }

    if (lastAngle > 1) {
        Real *angle = &path->m_cameraAngles[lastAngle + 1];
        Int remaining = lastAngle - 1;
        do {
            --angle;
            Real smoothed = angle[0] + angle[1];
            smoothed *= g_bfmeK1253;
            angle[1] = smoothed;
            --remaining;
        } while (remaining != 0);
    }

    Int lastWaypoint = m_cameraPath.m_numWaypoints;
    Coord3D finalPos;
    finalPos.x = m_cameraPath.m_waypoints[lastWaypoint].position.x;
    finalPos.y = m_cameraPath.m_waypoints[lastWaypoint].position.y;
    m_cameraPath.m_initialGroundHeight = m_groundLevel;

    Real finalGround =
        TheTerrainLogic->getGroundHeight(finalPos.x, finalPos.y);
    m_cameraPath.m_finalGroundHeight = finalGround;
    if (m_heightField.m_ready) {
        typedef Real (Rva0045A000::*HeightSample)(Real, Real);
        union HeightSampleBits {
            void (*raw)(void);
            HeightSample member;
        } sample;
        sample.raw = j_00046fa1;
        finalGround = (m_heightField.*sample.member)(finalPos.x, finalPos.y);
        m_cameraPath.m_finalGroundHeight = finalGround;
    }

    m_cameraMovementMode = m_cameraPath.m_numWaypoints > 1;
    slot27(0);
    m_doingRotateCamera = false;
}
