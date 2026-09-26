// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc-

// The BFME DockUpdate slice is four bytes narrower than the Zero Hour header
// slice.  Keep this declaration TU-local: the body is the retail
// RailedTransportDockUpdate::unloadNext operation, but its ABI view is BFME's.

#include <math.h>

typedef float Real;
typedef unsigned int ObjectID;
typedef int Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Real length() const
	{
		return (Real)sqrt(x * x + y * y + z * z);
	}
};

class OpenContain;

class ContainModuleInterface
{
public:
	virtual void *asOpenContain() = 0;
};

class Thing
{
public:
	void setPosition(const Coord3D *position);
	void setOrientation(Real angle);
};

class Object : public Thing
{
public:
	ContainModuleInterface *getContain() const
	{
		return *reinterpret_cast<ContainModuleInterface *const *>(
			reinterpret_cast<const char *>(this) + 0x1FC);
	}

	ObjectID getID() const
	{
		return *reinterpret_cast<const ObjectID *>(
			reinterpret_cast<const char *>(this) + 0x74);
	}

	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(
			reinterpret_cast<const char *>(this) + 0x38);
	}

	Real getOrientation() const
	{
		return *reinterpret_cast<const Real *>(
			reinterpret_cast<const char *>(this) + 0x44);
	}

	void bfmeSetConditionState(int state);
};

class OpenContainSlots0To35
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5c();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6c();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7c();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8c();
};

typedef void (*ContainIterateFunc)(Object *, void *);

class OpenContain : public OpenContainSlots0To35
{
public:
	virtual void removeFromContain(Object *object, Bool exposeStealthUnits);
	virtual void slot94();
	virtual void slot98();
	virtual void slot9c();
	virtual void slota0();
	virtual void slota4();
	virtual void slota8();
	virtual void slotac();
	virtual void slotb0();
	virtual void slotb4();
	virtual void slotb8();
	virtual void slotbc();
	virtual void slotc0();
	virtual void slotc4();
	virtual void slotc8();
	virtual void slotcc();
	virtual void slotd0();
	virtual void slotd4();
	virtual void slotd8();
	virtual void slotdc();
	virtual void slote0();
	virtual void slote4();
	virtual void slote8();
	virtual void slotec();
	virtual void slotf0();
	virtual void slotf4();
	virtual void slotf8();
	virtual void iterateContained(ContainIterateFunc func, void *userData, Bool reverse);
};

class DockUpdateInterfaceSlots0To6
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
};

class DockUpdateInterface : public DockUpdateInterfaceSlots0To6
{
public:
	virtual void getExitPosition(Object *docker, Coord3D *position);
};

class RailedTransportDockUpdateModuleData
{
public:
	char m_prefix[0x14];
	unsigned int m_pushOutsideDurationInFrames;
};

extern void getFirstContain(Object *object, void *userData);

class RailedTransportDockUpdateUnloadNextShim
{
public:
	void unloadNext();

	char m_prefix[4];
	RailedTransportDockUpdateModuleData *m_moduleData;
	Object *m_object;
	char m_between[0x14];
	DockUpdateInterface m_dockInterface;
	char m_suffix[0x70];
	ObjectID m_unloadingObjectID;
	Real m_pushOutsideDistancePerFrame;
	int m_unloadCount;
};

void RailedTransportDockUpdateUnloadNextShim::unloadNext()
{
	Object *us = m_object;

	m_unloadingObjectID = 0;

	if (m_unloadCount == 0)
		return;

	ContainModuleInterface *contain = us->getContain();
	void *openBase = contain ? contain->asOpenContain() : 0;
	OpenContain *openContain = reinterpret_cast<OpenContain *>(
		reinterpret_cast<char *>(openBase) + 0x20);

	Object *unloader = 0;
	openContain->iterateContained(getFirstContain, &unloader, 1);
	if (unloader)
	{
		openContain->removeFromContain(unloader, 0);
		unloader->setPosition(us->getPosition());
		unloader->setOrientation(us->getOrientation());
		unloader->bfmeSetConditionState(3);

		Coord3D dockPosition;
		m_dockInterface.getExitPosition(unloader, &dockPosition);

		const Coord3D *unloaderPos = unloader->getPosition();
		Coord3D v;
		v.x = dockPosition.x - unloaderPos->x;
		v.y = dockPosition.y - unloaderPos->y;
		v.z = dockPosition.z - unloaderPos->z;
		Real mag = v.length();

		m_pushOutsideDistancePerFrame = mag / m_moduleData->m_pushOutsideDurationInFrames;
		m_unloadingObjectID = unloader->getID();

		if (m_unloadCount != -1)
			--m_unloadCount;
	}
}
