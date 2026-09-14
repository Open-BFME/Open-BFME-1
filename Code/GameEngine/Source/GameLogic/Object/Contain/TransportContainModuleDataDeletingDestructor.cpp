// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: TransportContainModuleData scalar-deleting destructor at retail
// RVA 0x0021FD90 (30 bytes).  The wrapper calls the matched complete
// destructor at 0x0021D560 through ILT 0x0004B227.  Its exact constructor at
// 0x0021FC80, module-data factory allocation, and typed contain users establish
// the class identity independently of the generated placeholder.

class TransportContainModuleData
{
public:
	virtual ~TransportContainModuleData();
};

void forceTransportContainModuleDataDeletingDestructor()
{
	TransportContainModuleData value;
}
