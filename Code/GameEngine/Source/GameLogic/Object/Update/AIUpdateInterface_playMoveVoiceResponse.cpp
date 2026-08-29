// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <list>

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Drawable;

class Object
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual Drawable *getDrawable();

	const Coord3D *getPosition() const { return &m_position; }
	Bool isUsingAirborneLocomotor() const;

private:
	unsigned char m_unmodelled_04[ 0x34 ];
	Coord3D m_position;
};

typedef _STL::list<Drawable *> DrawableList;

class PickAndPlayInfo
{
public:
	PickAndPlayInfo();

	Bool m_air;
	Drawable *m_drawTarget;
	void *m_weaponSlot;
	int m_specialPowerType;
	Coord3D m_position;
	unsigned int m_unmodelled_1C;
};

class GameMessage
{
public:
	enum Type
	{
		MSG_DO_ATTACK_OBJECT = 0x7E7,
		MSG_DO_MOVETO = 0x7E8
	};
};

void pickAndPlayUnitVoiceResponse( const DrawableList *list, GameMessage::Type messageType,
	PickAndPlayInfo *info );

class AIUpdateInterface
{
protected:
	virtual void slot00();
	void playAttackVoiceResponse( Object *victim );
	void playAttackVoiceResponse( const Coord3D *position );
	void playMoveVoiceResponse( const Coord3D *position );

private:
	unsigned char m_unmodelled_04[ 4 ];
	Object *m_object;
};

void AIUpdateInterface::playAttackVoiceResponse( Object *victim )
{
	Drawable *drawable = m_object->getDrawable();
	if( drawable )
	{
		DrawableList list;
		list.push_back( drawable );
		PickAndPlayInfo info;
		if( victim )
		{
			info.m_drawTarget = victim->getDrawable();
			info.m_position = *victim->getPosition();
			info.m_air = victim->isUsingAirborneLocomotor();
		}
		pickAndPlayUnitVoiceResponse( &list, GameMessage::MSG_DO_ATTACK_OBJECT, &info );
	}
}

void AIUpdateInterface::playAttackVoiceResponse( const Coord3D *position )
{
	Drawable *drawable = m_object->getDrawable();
	if( drawable )
	{
		DrawableList list;
		list.push_back( drawable );
		PickAndPlayInfo info;
		info.m_position = *position;
		pickAndPlayUnitVoiceResponse( &list, GameMessage::MSG_DO_ATTACK_OBJECT, &info );
	}
}

void AIUpdateInterface::playMoveVoiceResponse( const Coord3D *position )
{
	Drawable *drawable = m_object->getDrawable();
	if( drawable )
	{
		DrawableList list;
		list.push_back( drawable );
		PickAndPlayInfo info;
		info.m_position = *position;
		pickAndPlayUnitVoiceResponse( &list, GameMessage::MSG_DO_MOVETO, &info );
	}
}
