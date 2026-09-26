// cl: /DNDEBUG /MD /EHsc
// TAiData::~TAiData, retail RVA 0x0014AC60.
// BFME has three one-word strings and a list at +0xF4 that are absent from
// the later Zero Hour header, so this TU describes the retail layout locally.

template <class T> class StringBase
{
public:
    ~StringBase() { releaseBuffer(); }

private:
    void releaseBuffer();
    T *m_text;
};

class AsciiString : public StringBase<char> {};

class Xfer;

class Snapshot
{
public:
    virtual ~Snapshot() {}
    virtual void crc(Xfer *) = 0;
    virtual void xfer(Xfer *) = 0;
    virtual void loadPostProcess() = 0;
};

class AISideInfo
{
public:
    virtual ~AISideInfo();
    char m_padding[0x1B8];
    AISideInfo *m_next; // +0x1BC
};

class AINamedListNode
{
public:
    virtual ~AINamedListNode();
    char m_padding[0x0C];
    AINamedListNode *m_next; // +0x10
};

class AISideBuildList
{
public:
    virtual ~AISideBuildList();
    char m_padding[0x08];
    AISideBuildList *m_next; // +0x0C
};

class TAiData : public Snapshot
{
public:
    virtual ~TAiData();
    virtual void crc(Xfer *);
    virtual void xfer(Xfer *);
    virtual void loadPostProcess();

private:
    char m_padding[0xD4];
    AsciiString m_treeF03; // +0xD8
    AsciiString m_treeF02; // +0xDC
    AsciiString m_ptStump02; // +0xE0
    char m_padding2[8];
    AISideInfo *m_sideInfo; // +0xEC
    AISideBuildList *m_sideBuildLists; // +0xF0
    AINamedListNode *m_namedLists; // +0xF4
    TAiData *m_next; // +0xF8
};

TAiData::~TAiData()
{
    AISideInfo *info = m_sideInfo;
    m_sideInfo = 0;
    while (info)
    {
        AISideInfo *current = info;
        info = info->m_next;
        delete current;
    }

    AINamedListNode *named = m_namedLists;
    m_namedLists = 0;
    while (named)
    {
        AINamedListNode *current = named;
        named = named->m_next;
        delete current;
    }

    AISideBuildList *build = m_sideBuildLists;
    m_sideBuildLists = 0;
    while (build)
    {
        AISideBuildList *current = build;
        build = build->m_next;
        delete current;
    }
}
