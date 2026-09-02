// cl: /DNDEBUG /MD
//
// Retail 0x002AC5C0: StealthUpdate::hintDetectableWhileUnstealthed.  ZH source
// at StealthUpdate.cpp:431, with BFME offsets: object at this+8, module data
// at this+4, hint-detectable mask at module-data+0x10, status bits at
// object+0x90, getDrawable at vtable+0x28, second-pass opacity at drawable+0x2E4.

#define BFME_VSLOT(n) virtual void slot##n();

class Player;
class Drawable;
class ObjectStatusMaskType;

class ObjectStatusMaskType
{
public:
	bool testForAny( const ObjectStatusMaskType &that ) const;
};

class Drawable
{
public:
	void setSecondMaterialPassOpacity( float op )
	{
		m_secondMaterialPassOpacity = op;
	}

private:
	unsigned char m_pad[ 0x2E4 ];
	float m_secondMaterialPassOpacity;
};

class Object
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3) BFME_VSLOT(4)
	BFME_VSLOT(5) BFME_VSLOT(6) BFME_VSLOT(7) BFME_VSLOT(8) BFME_VSLOT(9)
	virtual Drawable *getDrawable();

	Player *getControllingPlayer() const;

	const ObjectStatusMaskType &getStatusBits() const
	{
		return m_status;
	}

private:
	unsigned char m_pad[ 0x8C ];
	ObjectStatusMaskType m_status;
};

class PlayerList
{
public:
	Player *getLocalPlayer() const
	{
		return m_localPlayer;
	}

private:
	unsigned char m_pad[ 0x0C ];
	Player *m_localPlayer;
};

extern PlayerList *ThePlayerList;

class StealthUpdateModuleData
{
public:
	unsigned char m_pad[ 0x10 ];
	ObjectStatusMaskType m_hintDetectableStates;
};

class StealthUpdate
{
protected:
	void hintDetectableWhileUnstealthed();

	Object *getObject()
	{
		return m_object;
	}

	const StealthUpdateModuleData *getStealthUpdateModuleData() const
	{
		return m_moduleData;
	}

private:
	void *m_vtable;
	const StealthUpdateModuleData *m_moduleData;
	Object *m_object;
};

// ?hintDetectableWhileUnstealthed@StealthUpdate@@IAEXXZ
void StealthUpdate::hintDetectableWhileUnstealthed()
{
	Object *self = getObject();

	if ( self )
	{
		const StealthUpdateModuleData *md = getStealthUpdateModuleData();
		if ( md->m_hintDetectableStates.testForAny( self->getStatusBits() ) )
		{
			if ( self->getControllingPlayer() == ThePlayerList->getLocalPlayer() )
			{
				Drawable *selfDraw = self->getDrawable();
				if ( selfDraw )
					selfDraw->setSecondMaterialPassOpacity( 1.0f );
			}
		}
	}
}
