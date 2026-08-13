// cl: /DNDEBUG /MD /EHsc

class SpecialPowerTemplate;
class Waypoint;
class Object;

class SpecialPowerModuleInterface
{
public:
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void doSpecialPowerUsingWaypoints(const Waypoint *, unsigned int) = 0;
};

class SpecialPowerStore
{
public:
    bool canUseSpecialPower(Object *, const SpecialPowerTemplate *);
};

extern SpecialPowerStore *TheSpecialPowerStore;

class Object
{
public:
    void doSpecialPowerUsingWaypoints(const SpecialPowerTemplate *, const Waypoint *, unsigned int, bool);
    SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *);

private:
    unsigned char m_padding[0x1a4];
    unsigned int m_status;
};

// ?doSpecialPowerUsingWaypoints@Object@@QAEXPBVSpecialPowerTemplate@@PBVWaypoint@@I_N@Z
void Object::doSpecialPowerUsingWaypoints(const SpecialPowerTemplate *specialPowerTemplate,
                                           const Waypoint *way,
                                           unsigned int commandOptions,
                                           bool forced)
{
    if (m_status != 0) {
        return;
    }

    if (!forced && !TheSpecialPowerStore->canUseSpecialPower(this, specialPowerTemplate)) {
        return;
    }

    SpecialPowerModuleInterface *module = getSpecialPowerModule(specialPowerTemplate);
    if (module) {
        module->doSpecialPowerUsingWaypoints(way, commandOptions);
    }
}
