// cl: /DNDEBUG /MD /EHsc
// DozerAIUpdateView::getDockPoint, retail 0x002B69C0. Same +0x98 dock-point base
// as internalTaskComplete.

enum DozerTask
{
	DOZER_TASK_BUILD = 0,
	DOZER_NUM_TASKS = 3
};

enum DozerDockPoint
{
	DOZER_DOCK_POINT_START = 0,
	DOZER_NUM_DOCK_POINTS = 3
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;
};

struct DozerDockPointInfo
{
	bool valid;
	unsigned char pad[3];
	Coord3D location;
};

class DozerAIUpdateView
{
public:
	const Coord3D *getDockPoint(DozerTask task, DozerDockPoint point);

private:
	unsigned char m_pad[0x98];
	DozerDockPointInfo m_dockPoint[3][3];	// +0x98
};

// ?getDockPoint@DozerAIUpdate@@UAEPBUCoord3D@@W4DozerTask@@W4DozerDockPoint@@@Z
const Coord3D *DozerAIUpdateView::getDockPoint(DozerTask task, DozerDockPoint point)
{
	if (task < 0 || task >= DOZER_NUM_TASKS)
		return 0;
	if (point < 0 || point >= DOZER_NUM_DOCK_POINTS)
		return 0;
	if (!m_dockPoint[task][point].valid)
		return 0;
	return &m_dockPoint[task][point].location;
}
