// cl: /DNDEBUG /MD /EHsc

template <typename T>
class StringBase
{
public:
    ~StringBase()
    {
        releaseBuffer();
    }

    void *m_data;

private:
    void releaseBuffer();
};

class BFMERetailAsciiString : private StringBase<char>
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
