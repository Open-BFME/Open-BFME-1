// readable body of ?isAcceptingExperiencePoints@ExperienceTracker@@: Code/GameEngine/Source/GameLogic/Object/ExperienceTracker.cpp
// Byte-matched BFME ExperienceTracker transfer implementation.

typedef int Int;
typedef int Bool;
typedef float Real;
typedef unsigned char UnsignedByte;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	unsigned char m_unreconstructed[0xC8 - sizeof(Overridable)];
	char m_kindof;
	unsigned char m_unreconstructed2[0x487 - 0xC8 - 1];
	bool m_isTrainable;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	bool isLivingWorld();
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	ThingTemplate *m_template;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameMemory.h
class MemoryPoolObject
{
public:
	void *m_mp;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public MemoryPoolObject, public Thing
{
public:
	unsigned char m_pad[0x94 - 8];
	unsigned int m_status;
};

class Xfer;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
private:
	char *m_data;
};

class XferVersion
{
public:
	XferVersion(UnsignedByte major, UnsignedByte minor) :
		m_major(major), m_minor(minor) {}

	UnsignedByte m_major;
	UnsignedByte m_minor;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Xfer.h
class Xfer
{
public:
	virtual ~Xfer();
	virtual bool isLoading();
	virtual void slot02();
	virtual bool isDoingCRC();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion &value);
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
	virtual void slot24();
	virtual void slot25();
	virtual void xferAsciiString(AsciiString &value);
	virtual void xferReal(Real &value);
	virtual void slot28();
	virtual void slot29();
	virtual void xferInt(Int &value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(bool &value);
};

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

void friend_xferObjectID(Xfer *xfer, ObjectID *id);

class BfmeThingEFE
{
public:
	virtual ~BfmeThingEFE();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);

	void *m_tracker;
	Real m_scalar;
};

class ExperienceLevelSystem
{
public:
	void postLoad(Object *object);
};

extern ExperienceLevelSystem *TheExperienceLevelSystem;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer) = 0;
	virtual const char *getSnapshotName() const = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ExperienceTracker.h
class ExperienceTracker : public Snapshot
{
public:
	virtual ~ExperienceTracker();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual const char *getSnapshotName() const;
	bool isTrainable() const;
	bool isAcceptingExperiencePoints() const;

private:
	Object *m_parent;
	AsciiString m_levelName;
	Real m_currentExperience;
	Int m_currentLevel;
	Int m_unknown14;
	ObjectID m_experienceSink;
	Real m_experienceScalar;
	Int m_unknown20;
	bool m_unknown24;
	unsigned char m_padding25[3];
	Int m_scalarIndex;
	BfmeThingEFE *m_scalarTable;
};

void ExperienceTracker::xfer(Xfer *xfer)
{
	XferVersion version(1, 2);
	xfer->xferVersion(version);

	if (version.m_minor >= 2)
	{
		xfer->xferReal(m_currentExperience);
	}
	else if (xfer->isLoading())
	{
		Int oldExperience = 0;
		xfer->xferInt(oldExperience);
		m_currentExperience = static_cast<Real>(oldExperience);
	}

	xfer->xferAsciiString(m_levelName);
	friend_xferObjectID(xfer, &m_experienceSink);
	xfer->xferReal(m_experienceScalar);
	xfer->xferInt(m_currentLevel);
	xfer->xferInt(m_unknown20);
	xfer->xferInt(m_scalarIndex);
	xfer->xferInt(m_unknown14);
	xfer->xferBool(m_unknown24);

	if (!xfer->isDoingCRC() && xfer->isLoading())
		TheExperienceLevelSystem->postLoad(m_parent);

	if (version.m_minor >= 2)
		m_scalarTable->xfer(xfer);
}

inline bool ExperienceTracker::isTrainable() const
{
	const ThingTemplate *t = m_parent->m_template;
	if (t && t->m_nextOverride)
		t = static_cast<const ThingTemplate *>(t->m_nextOverride->getFinalOverride());
	return t->m_isTrainable;
}

bool ExperienceTracker::isAcceptingExperiencePoints() const
{
	if (m_parent->m_status & 0x20000000)
		return false;

	return isTrainable() || (m_experienceSink != 0);
}
