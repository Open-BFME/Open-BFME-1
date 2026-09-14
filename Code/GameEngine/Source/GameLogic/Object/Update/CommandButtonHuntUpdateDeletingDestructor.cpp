// cl: /DNDEBUG /MD /EHsc

// Open-BFME: CommandButtonHuntUpdate scalar-deleting destructor at retail
// RVA 0x0028AD70 (30 bytes). The exact module constructor at 0x0028AB20
// installs the dedicated vtable 0x010BD004, whose slot-zero ILT 0x0000EF2A
// routes here. The module factory at 0x00119890 allocates this concrete type,
// and the complete destructor at 0x0028AC90 restores the same vtables and
// releases its command-button string before destroying UpdateModule.

class CommandButtonHuntUpdate
{
public:
	virtual ~CommandButtonHuntUpdate();
};

void forceCommandButtonHuntUpdateDeletingDestructor()
{
	CommandButtonHuntUpdate value;
}
