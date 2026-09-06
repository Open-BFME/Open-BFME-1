// cl: /DNDEBUG /MD

typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;

class CommandButton;
struct Coord3D;
class AIUpdateInterface;

enum CommandSourceType
{
    COMMAND_SOURCE_UNKNOWN = 0
};

enum KindOfType
{
    KINDOF_PROJECTILE = 25
};

class Overridable
{
public:
    const Overridable *getFinalOverride() const;

    void *m_vtable;
    Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
    unsigned char m_pad08[0xC8 - 8];
    UnsignedInt m_kindOf[3];
};

class Thing
{
public:
    virtual void slot00();

    ThingTemplate *m_template;

};

class AsciiString;

class CommandSet
{
public:
    const CommandButton *getCommandButton(Int index) const;
};

class ControlBar
{
public:
    const CommandSet *findCommandSet(const AsciiString &name);
};

extern ControlBar *TheControlBar;

class Object : public Thing
{
public:
    const AsciiString &getCommandSetString() const;

    unsigned char m_pad08[0x1FC];
    AIUpdateInterface *m_ai;
};

class AIUpdateInterface
{
protected:
    virtual void privateCommandButtonPosition(const CommandButton *commandButton,
                                               const Coord3D *position,
                                               CommandSourceType commandSource);

    unsigned char m_pad04[4];
    Object * volatile m_object;
};

void AIUpdateInterface::privateCommandButtonPosition(const CommandButton *commandButton,
                                                      const Coord3D *position,
                                                      CommandSourceType commandSource)
{
    if (commandButton == 0)
    {
        return;
    }

    Object *owner = reinterpret_cast<Object *>(reinterpret_cast<unsigned int>(m_object) + 0);
    volatile unsigned char *objectBytes = reinterpret_cast<volatile unsigned char *>(owner);
    objectBytes += 4;
    ThingTemplate *objectTemplate = *reinterpret_cast<ThingTemplate * volatile *>(objectBytes);
    if (objectTemplate != 0 && objectTemplate->m_nextOverride != 0)
    {
        objectTemplate = (ThingTemplate *)objectTemplate->m_nextOverride->getFinalOverride();
    }

    if ((objectTemplate->m_kindOf[0] & 0x02000000) != 0)
    {
        return;
    }

    if (owner == 0)
    {
        return;
    }

    AIUpdateInterface *ai = owner->m_ai;
    if (ai == 0)
    {
        return;
    }

    const CommandSet *commandSet = TheControlBar->findCommandSet(owner->getCommandSetString());
    if (commandSet != 0)
    {
        for (Int index = 0; index < 20; ++index)
        {
            commandSet->getCommandButton(index);
        }
    }
}
