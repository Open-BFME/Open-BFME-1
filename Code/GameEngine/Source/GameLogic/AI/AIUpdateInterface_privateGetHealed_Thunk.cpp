// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AIUpdateInterface::privateGetHealed, retail 0x0027DE10.
//
// The Zero Hour body unchanged. AIUpdate.cpp is not in this tree, so the class
// is spelled locally around the two offsets the bytes fix, and both of them are
// really one fact about the layout:
//
//   [this+0x08]   the Object* getObject() returns
//   [this+0x20]   the AICommandInterface base subobject aiEnter is called on
//
// AIUpdateInterface derives from UpdateModule and AICommandInterface in that
// order, so the second base sits immediately past the first: `lea ecx,[esi+0x20]`
// says UpdateModule is exactly 0x20 bytes wide here.
//
// Callee pins, both resolved through their incremental-link thunks rather than
// taken on the packet's word:
//
//   0x0001B090 -> body 0x000C5140, canGetHealedAt. 185 bytes, and it sits in the
//     same block as 0x000C4240, which the sweep independently reads as
//     ActionManager::canFireWeaponAtLocation -- one compiland, one class.
//   0x000442A1 -> body 0x000D89C0, aiEnter. It reserves 0x9c of stack, pushes
//     0x17, calls a constructor on that buffer, stores the Object* argument into
//     it at +0x18, and then calls through vtable slot 0 -- which is
//     `AICommandParms parms(AICMD_ENTER, cmdSource); parms.m_obj = obj;
//     aiDoCommand(&parms);` and nothing else.

class Object;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ActionManager.h
class ActionManager
{
public:
	bool canGetHealedAt( const Object *obj, const Object *healDepot, CommandSourceType cmdSource );	///< ILT 0x0001B090
};

extern ActionManager *TheActionManager;			///< retail 0x012ED700

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiEnter( Object *obj, CommandSourceType cmdSource );	///< ILT 0x000442A1

private:
	char m_unreconstructed_00[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
public:
	// Undefined on purpose: it only has to exist so the vptr occupies +0x00 and
	// privateGetHealed mangles as the virtual it is.
	virtual ~UpdateModule();

	Object *getObject( void ) const { return m_obj; }

protected:
	char m_unreconstructed_04[4];
	Object *m_obj;								///< retail this+0x08
	char m_unreconstructed_0c[0x20 - 0x0c];		///< brings UpdateModule to 0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public UpdateModule, public AICommandInterface
{
protected:
	virtual void privateGetHealed( Object *healDepot, CommandSourceType cmdSource );
};

// ?privateGetHealed@AIUpdateInterface@@MAEXPAVObject@@W4CommandSourceType@@@Z
// Get healed at the heal depot
void AIUpdateInterface::privateGetHealed( Object *healDepot, CommandSourceType cmdSource )
{

  // sanity, if we can't get healed from here get outta here
	if( TheActionManager->canGetHealedAt( getObject(), healDepot, cmdSource ) == false )
		return;

	// enter the heal dest for healing
	aiEnter( healDepot, cmdSource );

}
