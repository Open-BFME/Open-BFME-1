// cl: /DNDEBUG /MD /EHsc

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// Keep the original inline destructor layer over the canonical string type:
// direct AsciiString members exchange ESI/EDI allocation in this retail body.
// This wrapper adds no storage and delegates the same 0x00887940 teardown.
class BFMERetailAsciiString : public AsciiString
{
public:
    ~BFMERetailAsciiString() {}
};

class BfmeBase
{
public:
    virtual ~BfmeBase() {}
    virtual void crc(void *) = 0;
    virtual void xfer(void *) = 0;
    virtual void loadPostProcess() = 0;
};

// Complete destructor 0x00194320 also emits scalar wrapper 0x00195550.
// Constructor 0x00194210, its installed vtable, and named SidesList callers
// independently establish the BuildListInfo identity and string fields.
class BuildListInfo : public BfmeBase
{
public:
    void deleteInstance()
    {
        delete this;
    }

    BuildListInfo *getNext() const
    {
        return m_nextBuildList;
    }

    void setNextBuildList(BuildListInfo *next)
    {
        m_nextBuildList = next;
    }

    BFMERetailAsciiString m_buildingName;
    BFMERetailAsciiString m_templateName;
    unsigned char m_padding[0x20];
    BuildListInfo *m_nextBuildList;
    BFMERetailAsciiString m_script;

protected:
    virtual ~BuildListInfo();
};

// ??1BuildListInfo@@MAE@XZ
BuildListInfo::~BuildListInfo()
{
    register BuildListInfo *next;
    if (m_nextBuildList) {
        register BuildListInfo *cur = m_nextBuildList;
        while (cur) {
            next = cur->getNext();
            cur->setNextBuildList(0);
            cur->deleteInstance();
            cur = next;
        }
    }
}
