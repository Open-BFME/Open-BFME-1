// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

#include "../../../Common/System/game_client_random_variable.h"

class OwnerY005E6030
{
public:
	char m_pad00[ 0x30 ];
	GameClientRandomVariable m_value;
};

class BaseY005E6030Primary
{
public:
	virtual void primarySlot();
};

class BaseY005E6030Interface
{
public:
	virtual void interfaceSlot();
	virtual ~BaseY005E6030Interface();
};

class BaseY005E6030Value
{
public:
	BaseY005E6030Value() : m_sample( 0.0f ) {}
	virtual void valueSlot();
	virtual ~BaseY005E6030Value();

protected:
	float m_sample;
};

class BaseY005E6030
	: public BaseY005E6030Primary,
	  public BaseY005E6030Interface,
	  public BaseY005E6030Value
{
public:
	BaseY005E6030( OwnerY005E6030 *owner );
	virtual void baseSlot();
};

BaseY005E6030::BaseY005E6030( OwnerY005E6030 *owner )
{
	m_sample = owner->m_value.getValue();
}
