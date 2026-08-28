// cl: /DNDEBUG /MD /EHsc

// Object::notifyModelConditionChanged, retail 0x001BE1C0. Two guarded calls and
// nothing else.
//
// The drawable at +0x80 is handed the object's own condition flags at +0x110
// with two zeroes after them. The AI at +0x204 is then told the state machine
// changed - through a name the ledger already has, and as a tail jump, so it is
// the last thing this function does. That call is virtual by its decorated name
// and reached DIRECTLY here, so it is written by qualified name; left to
// dispatch it becomes `jmp [edx]' and four bytes longer.
//
// Both are guarded independently: no drawable does not stop the AI being told.

typedef unsigned int UnsignedInt;

class ModelConditionFlags
{
public:
	unsigned char m_unmodelled_00[ 0x24 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	void replaceModelConditionState( const ModelConditionFlags &flags, UnsignedInt a, UnsignedInt b );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	virtual void friend_notifyStateMachineChanged( void );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void notifyModelConditionChanged( void );

private:
	unsigned char m_unmodelled_00[ 0x80 ];
	Drawable *m_drawable;					// +0x80
	unsigned char m_unmodelled_84[ 0x110 - 0x84 ];
	ModelConditionFlags m_conditionFlags;	// +0x110
	unsigned char m_unmodelled_134[ 0x204 - 0x134 ];
	AIUpdateInterface *m_ai;				// +0x204
};

// ?notifyModelConditionChanged@Object@@QAEXXZ
void Object::notifyModelConditionChanged( void )
{
	if( m_drawable )
		m_drawable->replaceModelConditionState( m_conditionFlags, 0, 0 );

	if( m_ai )
		m_ai->AIUpdateInterface::friend_notifyStateMachineChanged();
}
