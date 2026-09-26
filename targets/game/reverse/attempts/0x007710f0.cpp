// ?d_007710f0@@YAXXZ
// partial score=0.27 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <vector>
#include <string.h>

template <typename T> class StringBase
{
    friend class AsciiString;
private:
    struct Header
    {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };
public:
    int getLength() const { return m_data ? m_data->length : 0; }
    const T *str() const { return m_data ? &m_data->data[0] : (const T *)""; }
    void concat(const T *text, int length);
private:
    StringBase(const T *text);
    StringBase(const StringBase<T> &other);
    ~StringBase();
    Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString(const char *text) : StringBase<char>(text) {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}
    int getLength() const { return StringBase<char>::getLength(); }
    const char *str() const { return StringBase<char>::str(); }
    bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
    int compare(const AsciiString &other) const
    {
        int leftLength = getLength();
        int rightLength = other.getLength();
        int count = leftLength < rightLength ? leftLength : rightLength;
        int result = memcmp(str(), other.str(), count);
        return result != 0 ? result : leftLength - rightLength;
    }
    friend AsciiString operator+(AsciiString left, const char *right);
};

namespace _STL
{
template <> struct less<AsciiString>
{
    bool operator()(const AsciiString &left, const AsciiString &right) const
    {
        return left.compare(right) < 0;
    }
};
}

void *bfmeGoEMEb(void *);

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key, _STL::less<Rva001408C0Key>,
    _STL::allocator<Rva001408C0Key> > Rva001408C0Set;

class AssetList
{
public:
    AssetList &operator <<(const AssetList &other)
    {
        m_prototypes.insert(other.m_prototypes.begin(),
            other.m_prototypes.end());
        m_changed = true;
        return *this;
    }

    AssetList &operator <<(const AsciiString &name)
    {
        if (m_prototypes.insert((Rva001408C0Key)bfmeGoEMEb(
            (void *)name.str())).second)
            m_changed = true;
        return *this;
    }

    void addRaw(const char *name)
    {
        if (m_prototypes.insert((Rva001408C0Key)bfmeGoEMEb(
            (void *)name)).second)
            m_changed = true;
    }

    bool empty() const { return m_prototypes.empty(); }
    void markChanged() { m_changed = true; }

private:
    Rva001408C0Set m_prototypes;
    unsigned int m_treeLayoutPad;
    bool m_changed;
};

class Rva00769DD0Owner
{
public:
    void invoke(AssetList *, void *, int, int);
};

#pragma comment(linker, "/alternatename:?invoke@Rva00769DD0Owner@@QAEXPAVAssetList@@PAXHH@Z=?j_00027575@@YAXXZ")

class Rva00769490Owner
{
public:
    void invoke(AssetList *, void *, const AsciiString &, int);
};

class BfmeThing935E
{
public:
    void bfmeGo935E(void *, void *);
};

struct Rva0038C0E0Value
{
    AsciiString m_key;
};

struct Rva0038C0E0KeyOfValue
{
    const AsciiString &operator()(const Rva0038C0E0Value &value) const
    {
        return value.m_key;
    }
};

typedef _STL::_Rb_tree<AsciiString, Rva0038C0E0Value,
    Rva0038C0E0KeyOfValue, _STL::less<AsciiString>,
    _STL::allocator<Rva0038C0E0Value> > Rva0038C0E0Tree;

struct Rva007710F0Outer
{
    unsigned char m_pad0[0x34];
    Rva0038C0E0Value m_key;
    unsigned char m_pad38[0xf0];
};

struct Rva007710F0Nested
{
    unsigned char m_body[0xbc];
};

struct Rva007710F0InnerName
{
    AsciiString m_name;
    unsigned char m_pad04[4];
};

struct Rva007710F0Record6C
{
    unsigned char m_pad0[0x10];
    Rva007710F0InnerName *m_begin;
    Rva007710F0InnerName *m_end;
    unsigned char m_pad18[0x54];
};

struct Rva007710F0Elem14
{
    AsciiString m_name;
    unsigned char m_pad04[0x10];
};

struct Rva007710F0Elem2C
{
    AsciiString m_name;
    unsigned char m_pad04[0x28];
};

struct Rva007710F0Lod
{
    unsigned char m_pad0[0x16c4];
    int m_level;
};

class Rva007710F0Owner
{
public:
    void collect(AssetList *assets, void *context);

private:
    unsigned char m_pad0[8];
    _STL::vector<Rva007710F0Record6C> m_records08;
    AsciiString m_name14;
    _STL::vector<Rva007710F0Outer> m_outer18;
    _STL::vector<Rva007710F0Nested> m_nested24;
    unsigned char m_pad30[0xc];
    AsciiString m_name3c;
    unsigned char m_pad40[0x2c];
    _STL::vector<Rva007710F0Elem2C> m_names6c;
    _STL::vector<Rva007710F0Elem14> m_names78;
    const char *m_final84;
    unsigned char m_pad88[0x83];
    unsigned char m_flag10b;
    unsigned char m_pad10c[0x28];
    AssetList m_assetLists[2];
};

void Rva007710F0Owner::collect(AssetList *assets, void *context)
{
    unsigned char which = *(unsigned char *)context;
    unsigned int index = which != 0;
    char *variant = (char *)this + index * 20;
    AssetList *selected = m_assetLists + index;

    if (!selected->empty())
    {
        *assets << *selected;
        return;
    }

    Rva007710F0Lod *lod = *(Rva007710F0Lod **)0x012ED5AC;
    int level = lod->m_level;
    if (which)
        level = 1;

    for (Rva007710F0Record6C *record = m_records08.begin();
        record != m_records08.end(); ++record)
    {
        for (Rva007710F0InnerName *name = record->m_begin;
            name != record->m_end; ++name)
            selected->addRaw(name->m_name.str());
    }

    if (!m_name14.isEmpty())
    {
        BfmeThing935E *particle = *(BfmeThing935E **)0x012F64BC;
        particle->bfmeGo935E(&m_name14,
            selected);
    }

    if (!m_name3c.isEmpty())
        selected->addRaw((m_name3c + ".").str());

    Rva0038C0E0Tree names;
    for (Rva007710F0Outer *outer = m_outer18.begin();
        outer != m_outer18.end(); ++outer)
    {
        ((Rva00769DD0Owner *)outer)->invoke(assets, context,
            level, m_flag10b);

        for (Rva007710F0Nested *nested = m_nested24.begin();
            nested != m_nested24.end(); ++nested)
        {
            ((Rva00769490Owner *)nested)->invoke(assets, context,
                outer->m_key.m_key, level);
        }

        if (names.find(outer->m_key.m_key) == names.end())
            names.insert_unique(outer->m_key);
    }

    for (Rva007710F0Elem14 *item = m_names78.begin();
        item != m_names78.end(); ++item)
        selected->addRaw(item->m_name.str());

    for (Rva007710F0Elem2C *item = m_names6c.begin();
        item != m_names6c.end(); ++item)
        selected->addRaw(item->m_name.str());

    if (m_final84)
        selected->addRaw(m_final84);

    for (Rva0038C0E0Tree::iterator it = names.begin();
        it != names.end(); ++it)
        *assets << it->m_key;

    assets->markChanged();
}
