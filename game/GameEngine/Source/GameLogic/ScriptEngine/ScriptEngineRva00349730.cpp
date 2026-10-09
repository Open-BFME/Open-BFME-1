// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Evidence: targets/game/reverse/identity_evidence/00349730-native-accessors.md.

#include <vector>
#include "ascii_string.h"

template <typename T>
inline bool StringBase<T>::isEmpty() const
{
    return m_data == 0 || m_data->length == 0;
}

class Overridable
{
public:
    const Overridable *getFinalOverride() const
    {
        if (m_nextOverride)
            return m_nextOverride->getFinalOverride();
        return this;
    }

    void *m_vtable;
    Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
    const AsciiString &getName() const { return name; }

    unsigned char head[0x18];
    AsciiString name;
};

class Object
{
public:
    const ThingTemplate *getTemplate() const
    {
        if (!type)
            return 0;
        return (const ThingTemplate *)type->getFinalOverride();
    }

    int getID() const { return id; }
    const AsciiString &getName() const { return name; }

    unsigned char head[4];
    ThingTemplate *type;
    unsigned char pad08[0x74 - 8];
    int id;
    unsigned char pad78[12];
    AsciiString name;
};

typedef _STL::pair<AsciiString, Object *> NamedRequest;

class ScriptEngine
{
public:
    void rva00349730(Object *, const AsciiString &);
    void AppendDebugMessage(const AsciiString &, bool);

    unsigned char head[0x1709c];
    _STL::vector<NamedRequest> records;
};

extern ScriptEngine *TheScriptEngine;
extern const AsciiString Rva01336E50EmptyString;

// ?rva00349730@ScriptEngine@@QAEXPAVObject@@ABVAsciiString@@@Z
void ScriptEngine::rva00349730(Object *object, const AsciiString &fallback)
{
    if (!object)
        return;

    AsciiString name(object->getName());
    bool replaced = false;
    if (((const StringBase<char> &)name).compare((const StringBase<char> &)Rva01336E50EmptyString) == 0)
    {
        if (fallback.isEmpty())
            return;
        name = fallback;
        replaced = true;
    }

    for (_STL::vector<NamedRequest>::iterator it = records.begin(); it != records.end(); ++it)
    {
        if (it->first.compare(name) == 0)
        {
            if (!it->second)
            {
                AsciiString message;
                message.format(AsciiString("Reassigning dead object's name '%s' to object (%d) of type '%s'\n"), name.str(), object->getID(), object->getTemplate()->getName().str());
                TheScriptEngine->AppendDebugMessage(message, false);
                it->second = object;
            }
            else if (it->second != object && replaced)
            {
                it->second = object;
            }
            return;
        }
        if (object == it->second)
        {
            it->first = name;
            return;
        }
    }

    NamedRequest request;
    request.first = name;
    request.second = object;
    records.push_back(request);
}
