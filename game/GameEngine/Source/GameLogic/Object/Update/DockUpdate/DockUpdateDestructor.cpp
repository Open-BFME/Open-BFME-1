// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_MODULE_NO_MPO /Iinputs/reference/shims/dockupdate /Iinputs/reference/shims/moduledata /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include "GameLogic/Module/UpdateModule.h"

extern void __cdecl operator delete(void *block);
extern void Gen0082E5F0(void *block, unsigned int bytes);

class DockUpdateVector12
{
public:
	~DockUpdateVector12()
	{
		if (m_start != 0)
		{
			unsigned int bytes = static_cast<unsigned int>((m_end - m_start) / 12) * 12;
			if (bytes > 128)
				::operator delete(m_start);
			else
				Gen0082E5F0(m_start, bytes);
		}
	}

	char *m_start;
	char *m_finish;
	char *m_end;
};

class DockUpdateVector4
{
public:
	~DockUpdateVector4()
	{
		if (m_start != 0)
		{
			unsigned int bytes = static_cast<unsigned int>(m_end - m_start) * 4;
			if (bytes > 128)
				::operator delete(m_start);
			else
				Gen0082E5F0(m_start, bytes);
		}
	}

	unsigned int *m_start;
	unsigned int *m_finish;
	unsigned int *m_end;
};

class DockUpdateBitVector
{
public:
	~DockUpdateBitVector()
	{
		if (m_start != 0)
		{
			unsigned int bytes = static_cast<unsigned int>(m_end - m_start) * 4;
			if (bytes > 128)
				::operator delete(m_start);
			else
				Gen0082E5F0(m_start, bytes);
		}
	}

	unsigned int *m_start;
	unsigned int m_startOffset;
	unsigned int *m_finish;
	unsigned int m_finishOffset;
	unsigned int *m_end;
};

class DockUpdate : public UpdateModule, public DockUpdateInterface
{
	static void forceDestructorEmission(DockUpdate *object);

	protected:
	virtual ~DockUpdate();

	public:

	virtual Bool isClearToApproach(Object const *docker) const;
	virtual Bool reserveApproachPosition(Object *docker, Coord3D *position, Int *index);
	virtual Bool advanceApproachPosition(Object *docker, Coord3D *position, Int *index);
	virtual Bool isClearToEnter(Object const *docker) const;
	virtual Bool isClearToAdvance(Object const *docker, Int dockerIndex) const;
	virtual void getEnterPosition(Object *docker, Coord3D *position);
	virtual void getDockPosition(Object *docker, Coord3D *position);
	virtual void getExitPosition(Object *docker, Coord3D *position);
	virtual void onApproachReached(Object *docker);
	virtual void onEnterReached(Object *docker);
	virtual void onDockReached(Object *docker);
	virtual void onExitReached(Object *docker);
	virtual void cancelDock(Object *docker);
	virtual Bool isDockOpen();
	virtual void setDockOpen(Bool open);
	virtual Bool isAllowPassthroughType();
	virtual Bool isRallyPointAfterDockType();
	virtual void setDockCrippled(Bool setting);
	virtual UpdateSleepTime update();

private:
	char m_enterPosition[12];
	char m_dockPosition[12];
	char m_exitPosition[12];
	Int m_numberApproachPositions;
	Int m_numberApproachPositionBones;
	Bool m_positionsLoaded;
	DockUpdateVector12 m_approachPositions;
	DockUpdateVector4 m_approachPositionOwners;
	DockUpdateBitVector m_approachPositionReached;
	ObjectID m_activeDocker;
	Bool m_dockerInside;
	Bool m_dockCrippled;
	Bool m_dockOpen;
};

DockUpdate::~DockUpdate()
{
}

// ?forceDestructorEmission@DockUpdate@@SAXPAV1@@Z absent-from-retail
void DockUpdate::forceDestructorEmission(DockUpdate *object)
{
	object->~DockUpdate();
}
