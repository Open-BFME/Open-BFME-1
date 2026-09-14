// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: OneRingPenaltyUpdateModuleData scalar-deleting destructor at
// retail RVA 0x00299050 (30 bytes).  The wrapper calls the exact complete
// destructor at 0x00298D60 through ILT 0x0002A86F.  Its matched constructor at
// 0x00298D30 and the owning module-data factory establish the class identity
// independently of the generated placeholder.

class OneRingPenaltyUpdateModuleData
{
public:
	virtual ~OneRingPenaltyUpdateModuleData();
};

void forceOneRingPenaltyUpdateModuleDataDeletingDestructor()
{
	OneRingPenaltyUpdateModuleData value;
}
