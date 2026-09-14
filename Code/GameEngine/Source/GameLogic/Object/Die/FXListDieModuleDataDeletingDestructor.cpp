// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: FXListDieModuleData scalar-deleting destructor at retail RVA
// 0x00125620 (30 bytes).  The exact module-data constructor at 0x001234F0
// installs the dedicated vtable 0x0108B758; slot zero is ILT 0x000124A4,
// which reaches this wrapper.  The wrapper's complete-destructor call is
// ILT 0x00037759 to the 7-byte base-vptr teardown at 0x00125650.

class FXListDieModuleData
{
public:
	virtual ~FXListDieModuleData();
};

void forceFXListDieModuleDataDeletingDestructor()
{
	FXListDieModuleData value;
}
