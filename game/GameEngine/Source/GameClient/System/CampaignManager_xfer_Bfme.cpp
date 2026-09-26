// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib
// BFME CampaignManager snapshot transfer at retail RVA 0x005BCDA0.
// The body stores campaign state in the version-one save format.

#include "string_base.h"

typedef unsigned char UnsignedByte;
typedef int Int;

enum XferMode
{
    XFER_SAVE,
    XFER_LOAD,
    XFER_CRC
};

struct XferVersion
{
    XferVersion(UnsignedByte version) : m_version(version), m_currentVersion(version) {}

    UnsignedByte m_version;
    UnsignedByte m_currentVersion;
};

#include "ascii_string.h"

class Xfer
{
public:
    virtual void slot00();
    virtual unsigned char getXferMode();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void xferVersion(XferVersion *version);
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void xferAsciiString(AsciiString *value);
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void xferInt(Int *value);
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void xferBool(Int *value);
};

class MidVirtualSlot90Receiver;
extern void j_0003e81f();

class Campaign
{
public:
    char m_bfme_vptr[4];
    AsciiString m_name;
};

class Mission
{
public:
    char m_bfme_vptr[4];
    AsciiString m_name;
};

class CampaignManager
{
public:
    virtual void xfer(Xfer *xfer);
    void setCampaignAndMission(AsciiString campaign, AsciiString mission);

private:
    char m_campaignList[4];
    Campaign *m_currentCampaign;
    Mission *m_currentMission;
    Int m_victorious;
    Int m_currentRankPoints;
    Int m_difficulty;
};

extern void j_000189df();

// ?xfer@CampaignManager@@UAEXPAVXfer@@@Z
void CampaignManager::xfer(Xfer *xfer)
{
    XferVersion version(1);
    xfer->xferVersion(&version);

    AsciiString currentCampaign;
    if (m_currentCampaign)
        currentCampaign.set(m_currentCampaign->m_name);
    xfer->xferAsciiString(&currentCampaign);

    AsciiString currentMission;
    if (m_currentMission)
        currentMission.set(m_currentMission->m_name);
    xfer->xferAsciiString(&currentMission);

    xfer->xferInt(&m_currentRankPoints);
    typedef void (__cdecl *UserXfer)(MidVirtualSlot90Receiver *, void *);
    ((UserXfer)j_0003e81f)((MidVirtualSlot90Receiver *)xfer, &m_difficulty);
    xfer->xferBool(&m_victorious);

    if (xfer->getXferMode())
    {
        setCampaignAndMission(currentCampaign, currentMission);
    }
}
