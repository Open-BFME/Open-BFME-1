// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
private:
    void *m_data;
};

enum ObjectID
{
    OBJECT_ID_UNUSED = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
    ObjectID getID() const
    {
        return m_id;
    }

private:
    unsigned char m_pad[0x74];
    ObjectID m_id;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FlammableUpdate.h
class FlammableUpdateModuleData
{
private:
    unsigned char m_pad[0x18];

public:
    AsciiString m_burningSoundName;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
    AudioEventRTS(const AsciiString& eventName, ObjectID ownerID);
    virtual ~AudioEventRTS();

private:
    unsigned char m_pad[0x6c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager
{
public:
    virtual void unused00();
    virtual void unused01();
    virtual void unused02();
    virtual void unused03();
    virtual void unused04();
    virtual void unused05();
    virtual void unused06();
    virtual void unused07();
    virtual void unused08();
    virtual void unused09();
    virtual void unused10();
    virtual void unused11();
    virtual void unused12();
    virtual void unused13();
    virtual void unused14();
    virtual void unused15();
    virtual void unused16();
    virtual unsigned int addAudioEvent(const AudioEventRTS *event);
};

extern AudioManager *TheAudio;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FlammableUpdate.h
class FlammableUpdate
{
protected:
    const FlammableUpdateModuleData *getFlammableUpdateModuleData() const
    {
        return m_moduleData;
    }

    Object *getObject() const
    {
        return m_object;
    }

    void startBurningSound();

private:
    virtual void unused();
    const FlammableUpdateModuleData *m_moduleData;
    Object *m_object;
    unsigned char m_pad[0x28];
    unsigned int m_audioHandle;
};

// ?startBurningSound@FlammableUpdate@@IAEXXZ
void FlammableUpdate::startBurningSound()
{
    const FlammableUpdateModuleData *data = getFlammableUpdateModuleData();

    AudioEventRTS audio(data->m_burningSoundName, getObject()->getID());
    m_audioHandle = TheAudio->addAudioEvent(&audio);
}
