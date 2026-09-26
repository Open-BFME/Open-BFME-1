// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: ScriptList scalar-deleting destructor at retail
// 0x0035C990 (30 bytes).  The matched ScriptList constructor at 0x0035BBA0,
// complete destructor at 0x0035BC20, and the ScriptList parser/reset methods
// establish the class identity.

class ScriptList
{
public:
	~ScriptList();
};

void Force_ScriptList_Deleting_Destructor(ScriptList *value)
{
	delete value;
}
