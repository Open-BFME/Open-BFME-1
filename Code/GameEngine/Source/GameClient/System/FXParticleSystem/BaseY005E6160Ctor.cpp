// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

extern float GetGameClientRandomValueReal( float low, float high,
	char *file, int line );

class OwnerY005E6160;

class BaseY005E6160Primary
{
public:
	virtual void primarySlot();
};

class BaseY005E6160Interface
{
public:
	virtual void interfaceSlot();
	virtual ~BaseY005E6160Interface();
};

class BaseY005E6160Value
{
public:
	BaseY005E6160Value() : m_sample( 0.0f ) {}
	virtual void valueSlot();
	virtual ~BaseY005E6160Value();

protected:
	float m_sample;
};

class BaseY005E6160
	: public BaseY005E6160Primary,
	  public BaseY005E6160Interface,
	  public BaseY005E6160Value
{
public:
	BaseY005E6160( OwnerY005E6160 *owner );
	virtual void baseSlot();
};

BaseY005E6160::BaseY005E6160( OwnerY005E6160 * )
{
	char *source = "F:\\bfme\\Code\\gameengine\\Source\\GameClient\\System\\FXParticleSystem\\fxpswindmodule.cpp";
	m_sample = GetGameClientRandomValueReal( 0.7f, 1.3f, source, 402 );
}
