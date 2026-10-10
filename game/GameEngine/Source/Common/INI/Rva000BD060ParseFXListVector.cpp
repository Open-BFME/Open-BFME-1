// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// The callback appends FXList pointers and reports unresolved non-None tokens.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "Common/INI/INI.h"

// These accessors use the decoded INI receiver and hidden string result ABI.
class Rva000BD060INIView {
public:
    AsciiString getFilename() const;
    int getLineNum() const;
};

class FXList;
class FXListStore {
public:
    const FXList *findFXList(const char *name) const;
};
extern FXListStore *TheFXListStore;
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);
bool _bfme_debugReportingEnabled();
void _bfme_debugRecordCallsite(int kind);

// Only the diagnostic slots used by this callback have typed declarations.
class Rva000BD060Debug {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual Rva000BD060Debug &slot30(unsigned int value);
    virtual void slot34();
    virtual Rva000BD060Debug &slot38(const char *value);
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual bool slot4C(int kind);
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5C();
    virtual bool slot60();
    virtual void slot64();
    virtual void slot68();
    virtual Rva000BD060Debug &slot6C(const char *file, int line);
};
extern void *g_Rva00F36E5C;
#define TheRva000BD060Debug (static_cast<Rva000BD060Debug *>(g_Rva00F36E5C))

// ?appendFilename@@YAAAVRva000BD060Debug@@AAV1@ABVAsciiString@@@Z absent-from-retail
static inline Rva000BD060Debug &appendFilename(Rva000BD060Debug &log, const AsciiString &filename)
{
    log.slot38(filename.str());
    return log;
}

class Rva000BD060 {
public:
    static void parseFXListVector(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseFXListVector@Rva000BD060@@SAXPAVINI@@PAX1PBX@Z
void Rva000BD060::parseFXListVector(INI *ini, void *, void *store, const void *)
{
    _STL::vector<const FXList *> *values = (_STL::vector<const FXList *> *)store;
    for (const char *token = ini->getNextToken(); token; token = ini->getNextTokenOrNull()) {
        const FXList *fx = TheFXListStore->findFXList(token);
        values->push_back(fx);
        if (!fx && _strcmpi(token, "None") != 0) {
            _bfme_debugReportingEnabled() ?
                (_bfme_debugRecordCallsite(1), TheRva000BD060Debug->slot60(),
                (void)appendFilename(TheRva000BD060Debug->slot6C(0, 0).slot38("Unknown FX list ").slot38(token).slot38(" requested near line ").slot30(reinterpret_cast<const Rva000BD060INIView *>(ini)->getLineNum()).slot38(" of "), reinterpret_cast<const Rva000BD060INIView *>(ini)->getFilename()).slot4C(2)) : (void)0;
        }
    }
}
