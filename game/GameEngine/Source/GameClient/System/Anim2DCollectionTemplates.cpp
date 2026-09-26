// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Collection head +8 and template nextTemplate +4 are shared by creation and lookup.
// The returned name temporary must be released before the lookup branch.
typedef int Int;
extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);

class AsciiString;
template <typename T> class StringBase
{
    friend class AsciiString;
private:
    StringBase(const StringBase<T> &);
    ~StringBase();
    struct Header
    {
        unsigned char m_unreconstructed_00[4];
        unsigned short m_len;
        unsigned char m_unreconstructed_06[2];
    };
    Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}
    Int len() const { return m_data ? m_data->m_len : 0; }
    const char *str() const { return m_data ? reinterpret_cast<const char *>(m_data + 1) : ""; }
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
    Int rightLength = right.len();
    const char *rightChars = right.str();
    Int leftLength = left.len();
    const char *leftChars = left.str();
    Int compareLength = (leftLength < rightLength) ? leftLength : rightLength;
    Int prefixOrder = memcmp(leftChars, rightChars, compareLength);
    Int order = prefixOrder ? prefixOrder : (leftLength - rightLength);
    return order == 0;
}

// The constructor installs the vptr in 0x1C bytes; only the link is accessed here.
class Anim2DTemplate
{
public:
    Anim2DTemplate(AsciiString name);
    virtual ~Anim2DTemplate();
    AsciiString getName() const;
    Anim2DTemplate *friend_getNextTemplate() const { return m_nextTemplate; }
    void friend_setNextTemplate(Anim2DTemplate *nextTemplate) { m_nextTemplate = nextTemplate; }
private:
    Anim2DTemplate *m_nextTemplate;
    unsigned char m_unreconstructed_08[0x14];
};

class Anim2DCollection
{
public:
    Anim2DTemplate *findTemplate(const AsciiString &name);
    Anim2DTemplate *newTemplate(const AsciiString &name);
private:
    unsigned char m_unreconstructed_00[8];
    Anim2DTemplate *m_templateList;
};

Anim2DTemplate *Anim2DCollection::findTemplate(const AsciiString &name)
{
    for (Anim2DTemplate *animTemplate = m_templateList;
         animTemplate;
         animTemplate = animTemplate->friend_getNextTemplate())
    {
        if (animTemplate->getName() == name)
            return animTemplate;
    }
    return 0;
}

Anim2DTemplate *Anim2DCollection::newTemplate(const AsciiString &name)
{
    Anim2DTemplate *createdTemplate = new Anim2DTemplate(name);
    createdTemplate->friend_setNextTemplate(m_templateList);
    m_templateList = createdTemplate;
    return createdTemplate;
}
