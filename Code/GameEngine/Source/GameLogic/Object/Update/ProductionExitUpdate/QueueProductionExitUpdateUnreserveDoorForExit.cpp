// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /O2 /Ob2
// Retail 0x002D04E0, 3 bytes: QueueProductionExitUpdate::unreserveDoorForExit.
// ExitInterface vtable slot 4. ZH empty body; ret 4.

enum ExitDoorType
{
	DOOR_1 = 0
};

class QueueProductionExitUpdate
{
public:
	virtual void unreserveDoorForExit(ExitDoorType exitDoor);
};

void QueueProductionExitUpdate::unreserveDoorForExit(ExitDoorType)
{
}
