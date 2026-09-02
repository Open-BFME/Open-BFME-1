// cl: /DNDEBUG /MD /EHsc

class GiantBirdGuardReturnState
{
public:
	GiantBirdGuardReturnState( void *owner );

private:
	unsigned char m_unreconstructed[ 0x78 ];
};

class Rva002C1BC0Factory
{
public:
	GiantBirdGuardReturnState *createGuardReturnState();

private:
	unsigned char m_unreconstructed00[ 0x10 ];
	void *m_owner;
};

GiantBirdGuardReturnState *Rva002C1BC0Factory::createGuardReturnState()
{
	return new GiantBirdGuardReturnState( m_owner );
}
