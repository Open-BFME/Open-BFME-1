// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: QueueProductionExitUpdate::update, reached through the
// UpdateModule vtable subobject (this+0x10 in the full retail layout), so
// this TU-local shape starts its own fields at that subobject's offset 0.

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

class QueueProductionExitUpdate
{
public:
    virtual UpdateSleepTime update();

private:
    bool isFreeToExit() const
    {
        if (m_currentBurstCount > 0)
            return true;
        return (*(volatile const unsigned int *)&m_currentDelay == 0);
    }

    unsigned char m_pad00[0x14 - 4];
    unsigned int m_currentDelay;
    unsigned char m_pad18[0x2C - 0x14 - 4];
    unsigned int m_currentBurstCount;
};

// ?update@QueueProductionExitUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime QueueProductionExitUpdate::update()
{
    if (isFreeToExit())
    {
        m_currentDelay = 0;
        return UPDATE_SLEEP_NONE;
    }

    m_currentDelay--;
    return UPDATE_SLEEP_NONE;
}
