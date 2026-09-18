// Open-BFME5: CommandSet scalar deleting destructor.
// The protected virtual destructor access is inherited from
// MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(CommandSet, "CommandSet") in the
// retail ControlBar.h.  The friend exists only to make this ABI wrapper
// materialize; the complete destructor is defined in CommandSetCompleteDestructor.cpp.
class CommandSet
{
	friend void forceCommandSetDeletingDestructor();

protected:
	virtual ~CommandSet();
};

void forceCommandSetDeletingDestructor()
{
	CommandSet value;
}
