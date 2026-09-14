// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// Open-BFME: ModelConditionInfo scalar-deleting destructor at retail RVA
// 0x0013C570 (30 bytes).  The unique destructor ILT 0x0002306F enters the
// matched complete destructor at 0x0013C3F0; the matched 0x128-byte default
// constructor at 0x00776330 and its model-condition vector family establish
// the class identity.

class ModelConditionInfo
{
public:
	~ModelConditionInfo();
};

void forceModelConditionInfoDeletingDestructor(ModelConditionInfo *value)
{
	delete value;
}
