// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: LargeGroupAudioUpdateModuleData scalar-deleting destructor at
// retail RVA 0x00297410 (30 bytes).  Its wrapper calls the matched complete
// destructor at 0x00297390 through ILT 0x0003D302.  The matched default/copy
// constructors at 0x002971F0/0x002972B0 and typed module-data factory establish
// the class identity independently of the generated placeholder.

class LargeGroupAudioUpdateModuleData
{
public:
	virtual ~LargeGroupAudioUpdateModuleData();
};

void forceLargeGroupAudioUpdateModuleDataDeletingDestructor()
{
	LargeGroupAudioUpdateModuleData value;
}
