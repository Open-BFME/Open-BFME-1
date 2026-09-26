// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for QueueProductionExitUpdateModuleData.
// Constructor 0x00124150 installs dedicated vtable 0x00C8CFC0; its slot
// zero routes through ILT 0x0002D79A to this 30-byte wrapper, whose complete
// destructor route ILT 0x000114BE reaches cleanup body 0x001259F0.

class QueueProductionExitUpdateModuleData
{
protected:
	virtual ~QueueProductionExitUpdateModuleData();
private:
	friend void forceQueueProductionExitUpdateModuleDataDeletingDestructor();
};

void forceQueueProductionExitUpdateModuleDataDeletingDestructor()
{
	QueueProductionExitUpdateModuleData value;
}
