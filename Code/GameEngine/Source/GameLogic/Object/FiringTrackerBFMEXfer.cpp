// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef UnsignedInt AudioHandle;

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct XferVersion
{
	XferVersion(UnsignedByte version, UnsignedByte currentVersion) :
		m_version(version), m_currentVersion(currentVersion)
	{
	}

	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual bool IsLightCRC() const;
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion &version);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void xferCoord3D(Coord3D &value);
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void xferUnsignedInt(UnsignedInt &value);
	virtual void xferInt(Int &value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(bool &value);
};

void friend_xferObjectID(Xfer *xfer, ObjectID *id);

class Object;

class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface() = 0;
};

class Module
{
protected:
	virtual ~Module();

private:
	const void *m_moduleData;
};

class ObjectModule : public Module
{
protected:
	Object *m_object;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	UnsignedInt m_nextCallFrameAndPhase;
	Int m_indexInLogic;
	Int m_pad;
};

class AudioManager
{
public:
#define AUDIO_SLOT(n) virtual void audioSlot##n();
	AUDIO_SLOT(00) AUDIO_SLOT(01) AUDIO_SLOT(02) AUDIO_SLOT(03)
	AUDIO_SLOT(04) AUDIO_SLOT(05) AUDIO_SLOT(06) AUDIO_SLOT(07)
	AUDIO_SLOT(08) AUDIO_SLOT(09) AUDIO_SLOT(10) AUDIO_SLOT(11)
	AUDIO_SLOT(12) AUDIO_SLOT(13) AUDIO_SLOT(14) AUDIO_SLOT(15)
	AUDIO_SLOT(16) AUDIO_SLOT(17) AUDIO_SLOT(18) AUDIO_SLOT(19)
	AUDIO_SLOT(20) AUDIO_SLOT(21) AUDIO_SLOT(22) AUDIO_SLOT(23)
	AUDIO_SLOT(24) AUDIO_SLOT(25) AUDIO_SLOT(26) AUDIO_SLOT(27)
	AUDIO_SLOT(28) AUDIO_SLOT(29) AUDIO_SLOT(30) AUDIO_SLOT(31)
	AUDIO_SLOT(32) AUDIO_SLOT(33) AUDIO_SLOT(34) AUDIO_SLOT(35)
	AUDIO_SLOT(36) AUDIO_SLOT(37) AUDIO_SLOT(38) AUDIO_SLOT(39)
	AUDIO_SLOT(40) AUDIO_SLOT(41) AUDIO_SLOT(42) AUDIO_SLOT(43)
	AUDIO_SLOT(44) AUDIO_SLOT(45) AUDIO_SLOT(46) AUDIO_SLOT(47)
	AUDIO_SLOT(48) AUDIO_SLOT(49) AUDIO_SLOT(50) AUDIO_SLOT(51)
	AUDIO_SLOT(52) AUDIO_SLOT(53) AUDIO_SLOT(54) AUDIO_SLOT(55)
	AUDIO_SLOT(56) AUDIO_SLOT(57) AUDIO_SLOT(58) AUDIO_SLOT(59)
	AUDIO_SLOT(60) AUDIO_SLOT(61) AUDIO_SLOT(62) AUDIO_SLOT(63)
	AUDIO_SLOT(64) AUDIO_SLOT(65) AUDIO_SLOT(66) AUDIO_SLOT(67)
	AUDIO_SLOT(68) AUDIO_SLOT(69) AUDIO_SLOT(70) AUDIO_SLOT(71)
	AUDIO_SLOT(72) AUDIO_SLOT(73) AUDIO_SLOT(74) AUDIO_SLOT(75)
	AUDIO_SLOT(76) AUDIO_SLOT(77) AUDIO_SLOT(78) AUDIO_SLOT(79)
	AUDIO_SLOT(80) AUDIO_SLOT(81)
#undef AUDIO_SLOT
	virtual void xferAudioHandle(Xfer *xfer, AudioHandle *handle);
};

extern AudioManager *TheAudio;

class FiringTracker : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	Int m_consecutiveShots;
	ObjectID m_victimID;
	Coord3D m_victimPosition;
	bool m_victimIsPosition;
	UnsignedByte m_alignment35[3];
	ObjectID m_auxiliaryObjectID;
	UnsignedInt m_frameToStartCooldown;
	UnsignedInt m_frameToForceReload;
	UnsignedInt m_lastShotFrame;
	Coord3D m_lastShotPosition;
	UnsignedInt m_frameToStopLoopingSound;
	AudioHandle m_audioHandle;
};

void FiringTracker::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);

	if (xfer->IsLightCRC())
		return;

	XferVersion version(1, 2);
	xfer->xferVersion(version);
	xfer->xferInt(m_consecutiveShots);
	friend_xferObjectID(xfer, &m_victimID);
	friend_xferObjectID(xfer, &m_auxiliaryObjectID);
	xfer->xferUnsignedInt(m_frameToStartCooldown);
	xfer->xferUnsignedInt(m_frameToForceReload);
	xfer->xferUnsignedInt(m_lastShotFrame);
	xfer->xferCoord3D(m_lastShotPosition);
	xfer->xferBool(m_victimIsPosition);
	xfer->xferCoord3D(m_victimPosition);

	if (version.m_currentVersion >= 2)
		xfer->xferUnsignedInt(m_frameToStopLoopingSound);

	if (TheAudio != 0)
		TheAudio->xferAudioHandle(xfer, &m_audioHandle);
}
