// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: TAiData scalar-deleting destructor at retail RVA 0x0014AD90
// (30 bytes). The exact constructor at 0x0014B150 installs vtable 0x01095754,
// whose slot zero routes through ILT 0x00007941 to this wrapper. The AI owner
// allocates this concrete type and its literal snapshot name corroborates
// identity; the complete destructor is called through ILT 0x00004499.

class TAiData
{
public:
	virtual ~TAiData();
};

void forceTAiDataDeletingDestructor()
{
	TAiData value;
}
