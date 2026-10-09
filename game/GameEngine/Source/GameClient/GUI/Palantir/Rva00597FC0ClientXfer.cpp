// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common
// stlport
// Snapshot receiver is the complete owner plus eight bytes.
#include <map>
#include "System/xfer.h"

extern void j_00012139();
extern void j_0003856e();
extern void j_0003ba0c();
extern void j_000046bf();

class SubsystemInterface {
public:
    virtual ~SubsystemInterface();
private:
    void *m_name;
};

class Rva005954E0SnapshotSlots {
public:
    virtual ~Rva005954E0SnapshotSlots();
    virtual void slot01();
    virtual const char *getClassName() const;
    virtual void xfer(Xfer *);
};

typedef _STL::map<int, bool> Rva005954E0Map;
class Rva005954E0Route {};
struct Rva005954E0LoadValue { bool value; int key; };

class Rva00597FC0Client : public SubsystemInterface, public Rva005954E0SnapshotSlots {
protected:
    virtual void xfer(Xfer *xfer);
private:
    char m_0c[0x3c];
    bool m_48;
    char m_49[7];
    int m_50, m_54;
    char m_58[0x260];
    char m_2b8[0x1a8];
    int m_460[2];
    char m_468[0x50];
    bool m_4b8[12];
    bool m_4c4, m_4c5;
    char m_4c6[0x36];
    Rva005954E0Map m_4fc;
};

// ?xfer@Rva00597FC0Client@@MAEXPAVXfer@@@Z
void Rva00597FC0Client::xfer(Xfer *xfer)
{
    if (xfer->IsCRC())
        return;
    Xfer::Version version;
    version.data[0] = 1;
    version.data[1] = 3;
    *xfer == version;
    int *integer = m_460;
    *xfer == *integer;
    ++integer;
    *xfer == *integer;
    typedef Xfer &(__cdecl *BoolArray)(Xfer &, bool *);
    union { void (*raw)(); BoolArray call; } boolArray = { j_00012139 };
    boolArray.call(*xfer, m_4b8);
    *xfer == m_4c4;
    if (version.data[1] >= 2) {
        typedef void (Rva005954E0Route::*Transfer)(Xfer *, int);
        union { void (*raw)(); Transfer call; } transfer = { j_0003856e };
        (((Rva005954E0Route *)m_2b8)->*transfer.call)(xfer, version.data[1]);
    }
    typedef void (Rva005954E0Route::*Clear)();
    union { void (*raw)(); Clear call; } clear = { j_0003ba0c };
    if (version.data[1] >= 3) {
        int keyCount;
        if (xfer->IsStoring()) {
            int count = m_4fc.size();
            *xfer == count;
            for (Rva005954E0Map::iterator i = m_4fc.begin(); i != m_4fc.end(); ++i) {
                keyCount = i->first;
                *xfer == keyCount;
                *xfer == i->second;
            }
        } else {
            (((Rva005954E0Route *)&m_4fc)->*clear.call)();
            *xfer == keyCount;
            while (keyCount > 0) {
                Rva005954E0LoadValue record;
                record.value = false;
                *xfer == record.key;
                *xfer == record.value;
                typedef _STL::pair<Rva005954E0Map::iterator, bool> (Rva005954E0Route::*Insert)(const Rva005954E0Map::value_type &);
                union { void (*raw)(); Insert call; } insert = { j_000046bf };
                (((Rva005954E0Route *)&m_4fc)->*insert.call)(Rva005954E0Map::value_type(record.key, record.value));
                --keyCount;
            }
        }
        *xfer == m_4c5;
    } else if (xfer->IsLoading()) {
        (((Rva005954E0Route *)&m_4fc)->*clear.call)();
        m_4c5 = false;
    }
    *xfer == m_48;
    xfer->XferRawBytes(&m_50, 4);
    xfer->XferRawBytes(&m_54, 4);
}
