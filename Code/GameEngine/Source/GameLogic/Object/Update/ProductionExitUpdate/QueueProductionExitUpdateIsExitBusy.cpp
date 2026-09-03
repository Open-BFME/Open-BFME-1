// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /O2 /Ob2
// Retail 0x002D04B0, 3 bytes: QueueProductionExitUpdate::isExitBusy.
// ExitInterface vtable slot 0. ZH inline returns FALSE.

class QueueProductionExitUpdate
{
public:
	virtual bool isExitBusy() const;
};

bool QueueProductionExitUpdate::isExitBusy() const
{
	return false;
}
