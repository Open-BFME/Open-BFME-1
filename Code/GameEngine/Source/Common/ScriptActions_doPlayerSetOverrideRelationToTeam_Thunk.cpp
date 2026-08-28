// cl: /DNDEBUG /MD /EHsc
// readable body of ?doPlayerSetOverrideRelationToTeam@ScriptActions@@IAEXABVAsciiString@@0H@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// Open-BFME5: lift ScriptActions::doPlayerSetOverrideRelationToTeam to clean C++.

typedef int Int;

class Player;
class Team;

template <class T> class StringBase
{
    friend class AsciiString;

public:
    struct Header;
    Header *m_data;

private:
    StringBase(const StringBase &);
    ~StringBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
    AsciiString(const AsciiString &that)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(
            *(const StringBase<char> *)&that);
    }
    ~AsciiString();

public:
    struct AsciiStringData;
    AsciiStringData *m_data;
};

enum NameKeyType
{
    NAMEKEY_INVALID = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const char *);
};

extern NameKeyGenerator *g_theNameKeyGenerator;
extern "C" char g_NAMEKEY_empty_string;

NameKeyType NAMEKEY(const AsciiString &s)
{
    const char *p;
    if (s.m_data)
    {
        p = (const char *)s.m_data + 8;
    }
    else
    {
        p = &g_NAMEKEY_empty_string;
    }
    return g_theNameKeyGenerator->nameToKey(p);
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
    Player *findPlayerWithNameKey(NameKeyType);
};

enum Relationship
{
    RELATIONSHIP_UNUSED = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
    void setTeamRelationship(const Team *, Relationship);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
    virtual void _slot00() = 0;
    virtual void _slot01() = 0;
    virtual void _slot02() = 0;
    virtual void _slot03() = 0;
    virtual void _slot04() = 0;
    virtual void _slot05() = 0;
    virtual void _slot06() = 0;
    virtual void _slot07() = 0;
    virtual void _slot08() = 0;
    virtual void _slot09() = 0;
    virtual void _slot10() = 0;
    virtual void _slot11() = 0;
    virtual void _slot12() = 0;
    virtual void _slot13() = 0;
    virtual void _slot14() = 0;
    virtual void _slot15() = 0;
    virtual void _slot16() = 0;
    virtual Team *getTeamNamed(AsciiString, bool = false);
};

extern PlayerList *ThePlayerList;
extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
    void doPlayerSetOverrideRelationToTeam(const AsciiString &, const AsciiString &, Int);
};

// ?doPlayerSetOverrideRelationToTeam@ScriptActions@@IAEXABVAsciiString@@0H@Z
void ScriptActions::doPlayerSetOverrideRelationToTeam(
    const AsciiString &playerName, const AsciiString &otherTeam, Int relation)
{
    Player *thePlayer = ThePlayerList->findPlayerWithNameKey(NAMEKEY(playerName));
    Team *theOtherTeam = TheScriptEngine->getTeamNamed(otherTeam);
    if (thePlayer && theOtherTeam)
    {
        thePlayer->setTeamRelationship(theOtherTeam, (Relationship)relation);
    }
}
