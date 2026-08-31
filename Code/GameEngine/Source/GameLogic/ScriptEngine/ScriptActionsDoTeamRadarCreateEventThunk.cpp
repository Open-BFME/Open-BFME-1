// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef bool Bool;
typedef float Real;

enum RadarEventType
{
};

struct Coord3D
{
    Real x;
    Real y;
    Real z;
};

class AsciiString
{
private:
    char *m_text;
};

class BfmeStringArgBase
{
    friend class BfmeAsciiStringArg;

private:
    BfmeStringArgBase(const BfmeStringArgBase &);
    ~BfmeStringArgBase();
};

class BfmeAsciiStringArg
{
public:
    BfmeAsciiStringArg(const AsciiString &that)
    {
        ((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
            *(const BfmeStringArgBase *)&that);
    }
    ~BfmeAsciiStringArg();

private:
    char *m_text;
};

class Team
{
public:
    Bool hasAnyUnits() const;
    // The retail BFME body at 0x000EDCD0 is distinct from the already named
    // getEstimateTeamPosition body at 0x000F2420.
    Coord3D *getEstimateTeamPosition_000EDCD0(Coord3D *) const;
};

class ScriptEngine
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
    virtual Team *getTeamNamed(BfmeAsciiStringArg, Bool) = 0;
};

class Radar
{
public:
    void createEvent(const Coord3D *, RadarEventType, Real secondsToLive = 4.0f);
};

extern ScriptEngine *TheScriptEngine;
extern Radar *TheRadar;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
    void doTeamRadarCreateEvent(const AsciiString &teamName, int eventType);
};

// ?doTeamRadarCreateEvent@ScriptActions@@IAEXABVAsciiString@@H@Z
void ScriptActions::doTeamRadarCreateEvent(const AsciiString &teamName, int eventType)
{
    Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
    if (!theTeam || !theTeam->hasAnyUnits())
        return;

    Coord3D position;
    theTeam->getEstimateTeamPosition_000EDCD0(&position);
    TheRadar->createEvent(&position, (RadarEventType)eventType);
}
