// ?Rva002E5090ScriptLogMessage@@YAXPBD@Z
// partial score=0.47 date=2026-09-18
// cl: /O2 /DNDEBUG /MD /EHsc-

struct Rva002E5090Data
{
    unsigned char header[8];
    unsigned short length;
    unsigned short capacity;
    char text[1];
};

class Rva002E5090String
{
public:
    Rva002E5090String();
    ~Rva002E5090String();
    void concat(const char *text, int length);
    const char *reverseFind(char c) const;
    void removeLastChar();
    void releaseBuffer();
    Rva002E5090Data *m_data;
};

class Rva002E5090ScriptEngine
{
public:
    void AppendDebugMessage(const Rva002E5090String &message, bool forcePause);
};

typedef void (__cdecl *Rva002E5090VoidCallback)(void);
extern "C" int __cdecl _atexit(Rva002E5090VoidCallback);

#define Rva002E5090Message (*(Rva002E5090String *)0x012f0618)

void __cdecl Rva002E5090ScriptLogMessage(const char *input)
{
    unsigned char enabled = (*(unsigned char **)0x012ed5c8)[0xa90];
    if (!enabled)
        return;

    unsigned char initialized = *(unsigned char *)0x012f061c;
    unsigned int one = 1;
    if ((initialized & one) == 0)
    {
        unsigned int guard = *(unsigned int *)0x012f061c;
        guard |= one;
        *(unsigned int *)0x012f061c = guard;
        Rva002E5090Message.Rva002E5090String::Rva002E5090String();
        _atexit((Rva002E5090VoidCallback)0x0106fe40);
    }

    Rva002E5090String *message = (Rva002E5090String *)0x012f0618;

    const char *text = input;
    int length;
    if (text != 0)
    {
        const char *p = text;
        while (*p != 0)
            ++p;
        length = (int)(p - text);
    }
    else
    {
        length = 0;
    }
    message->concat(text, length);

    if (message->m_data != 0 && message->m_data->length > 0x50)
        goto scan;
    if (message->reverseFind('\n') == 0)
        return;

scan:
    const char *start;
    int currentLength;
    if (message->m_data != 0)
    {
        currentLength = message->m_data->length;
        start = message->m_data->text;
    }
    else
    {
        currentLength = 0;
        start = "";
    }

    const char *end = start + currentLength;
    while (end != start)
    {
        --end;
        if (*end == '\n')
        {
            message->removeLastChar();
            break;
        }
    }

    Rva002E5090ScriptEngine *engine = *(Rva002E5090ScriptEngine **)0x012f076c;
    engine->AppendDebugMessage(*message, false);
    message->releaseBuffer();
}
