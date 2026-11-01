// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for QueueProductionExitUpdateModuleData.
// Constructor 0x00124150 installs dedicated vtable 0x00C8CFC0; its slot
// zero routes through ILT 0x0002D79A to this 30-byte wrapper, whose complete
// destructor route ILT 0x000114BE reaches cleanup body 0x001259F0.

class QueueProductionExitUpdateModuleData
{
public:
	virtual ~QueueProductionExitUpdateModuleData();
private:
	friend void forceQueueProductionExitUpdateModuleDataDeletingDestructor(const QueueProductionExitUpdateModuleData &);
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceQueueProductionExitUpdateModuleDataDeletingDestructor(const QueueProductionExitUpdateModuleData &that)
{
	QueueProductionExitUpdateModuleData value(that);
}
