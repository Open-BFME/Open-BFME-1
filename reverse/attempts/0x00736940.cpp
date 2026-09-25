// ?rva00736940@W3DTreeBuffer@@QAEHABVAsciiString@@H0@Z
// partial score=0.19883 date=2026-09-25
// ?rva00736940@W3DTreeBuffer@@QAEHABVAsciiString@@H0@Z
// RVA 00736940: W3DTreeBuffer caller and matched six-argument addTreeType prove owner.
// Unused virtual slots reserve positions only; their signatures are not claimed.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/stringinline
#include "StringInline.h"

class ThingTemplate;
class BfmeThingFactory
{
public:
    const ThingTemplate *findTemplate(const AsciiString &name);
};
extern BfmeThingFactory *TheThingFactory;

class Rva00736940DebugOutput
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
    virtual void slot30(); virtual void slot34();
    virtual Rva00736940DebugOutput &write(const char *text);
    virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
    virtual Rva00736940DebugOutput &write(int value); virtual void slot50(); virtual void slot54(); virtual void slot58();
    virtual void slot5C(); virtual void slot60(); virtual void slot64(); virtual void slot68();
    virtual void slot6C();
};
class Rva00736940DebugManager
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
    virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
    virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
    virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
    virtual void slot60(); virtual void slot64(); virtual void slot68();
    virtual Rva00736940DebugOutput &getOutput(int, int);
};
extern Rva00736940DebugManager *TheGen001336E5C;
bool _bfme_debugReportingEnabled(void);
void _bfme_debugRecordCallsite(int kind);

class Rva00736940DrawModule
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
    virtual void slot10(); virtual void slot14(); virtual void slot18();
    virtual void slot1C(); virtual void slot20();
    virtual const void *getAsW3DTreeDrawModuleData() const;
};
struct Rva00736940ModuleEntry
{
    unsigned char m_pad0000[8];
    Rva00736940DrawModule *module;
    unsigned char remaining[8];
};
struct Rva00736940TreeDrawData
{
    unsigned char moduleDataBase[8];
    AsciiString modelName;
    AsciiString nameC;
};
class ThingTemplate
{
public:
    unsigned char m_pad0000[0x20];
    AsciiString m_name;
    unsigned char m_pad0024[0x27c];
    Rva00736940ModuleEntry *m_modules;
    Rva00736940ModuleEntry *m_moduleEnd;
};
struct Rva00736940TreeType
{
    unsigned char prefix[0x4c];
    AsciiString modelName;
    AsciiString nameC;
    unsigned char suffix[8];
};
class W3DTreeBuffer
{
public:
    int addTreeType(const AsciiString &, const AsciiString &, const void *, int,
        const AsciiString &, const AsciiString &);
    int rva00736940(const AsciiString &templateName, int shadowKind,
        const AsciiString &textureName);
    unsigned char prefix[0x2a7cb9];
    unsigned char needUpdate;
    unsigned char alignment[2];
    Rva00736940TreeType types[64];
    int typeCount;
};

int W3DTreeBuffer::rva00736940(const AsciiString &templateName, int shadowKind,
    const AsciiString &textureName)
{
    const void *nameData = *(const void * const *)(const void *)&templateName;
    if (!nameData || *(const unsigned short *)((const char *)nameData + 4) == 0)
        return -2;
    const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(templateName);
    if (!thingTemplate) return -2;
    const int count = thingTemplate->m_moduleEnd - thingTemplate->m_modules;
    if (!count || !thingTemplate->m_modules->module) return -2;
    const Rva00736940TreeDrawData *treeData =
        (const Rva00736940TreeDrawData *)thingTemplate->m_modules->module->getAsW3DTreeDrawModuleData();
    if (!treeData) {
        if (_bfme_debugReportingEnabled()) {
            _bfme_debugRecordCallsite(1);
            TheGen001336E5C->slot60();
            TheGen001336E5C->getOutput(0, 0).write("Tree ")
                .write(thingTemplate->m_name.str())
                .write(" requires a W3DTreeDrawModule.\n").write(2);
        }
        return -2;
    }
    int index = -2;
    for (int i = 0; i < typeCount; ++i) {
        if (types[i].modelName.compareNoCase(treeData->modelName) == 0 &&
            types[i].nameC.compareNoCase(treeData->nameC) == 0) {
            index = i;
            break;
        }
    }
    if (index >= 0) return index;
    index = addTreeType(treeData->modelName, treeData->nameC, treeData,
        shadowKind, textureName, templateName);
    if (index >= 0) needUpdate = 1;
    return index;
}
