// Address-qualified reconstruction.  The 102-byte matched caller at
// 0x005E7360 allocates 0x4c bytes, passes its adjusted receiver as the only
// argument, invokes this constructor through ILT 0x00012FA3, and stamps the
// returned object at offsets 0, 4, and 8.  Retail ends this body with ret 4 at
// +0xcc and then 65 bytes of int3 padding, proving the complete 207-byte
// boundary.
//
// The constructor's stores prove three polymorphic subobjects.  The primary
// base has a vptr but a trivial destructor.  The two secondary bases are the
// only cleanup states; that distinction reproduces retail's delayed EH states
// 0 and 1.  The third subobject owns eight value/pointer pairs, making the
// complete layout exactly 0x4c bytes.  No semantic owner name is asserted.
// cl: /EHsc

#include "../../../Common/System/game_client_random_variable.h"

struct OwnerY005E7360Record
{
	GameClientRandomVariable value;
	void *pointer;
};

class OwnerY005E7360
{
public:
	char padding00[ 0x20 ];
	OwnerY005E7360Record records[ 8 ];
};

class BaseY005E7360Primary
{
public:
	virtual void primary() {}
};

class BaseY005E7360Secondary
{
public:
	virtual ~BaseY005E7360Secondary() {}
	virtual void secondary() {}
};

struct BaseY005E7360Pair
{
	BaseY005E7360Pair() : value( 0.0f ), pointer( 0 ) {}
	float value;
	void *pointer;
};

class BaseY005E7360Pairs
{
public:
	BaseY005E7360Pairs() {}
	virtual ~BaseY005E7360Pairs() {}
	virtual void pairs() {}
	BaseY005E7360Pair entries[ 8 ];
};

class BaseY005E7360 : public BaseY005E7360Primary,
	public BaseY005E7360Secondary, public BaseY005E7360Pairs
{
public:
	BaseY005E7360( OwnerY005E7360 *owner );
	virtual ~BaseY005E7360() {}
	virtual void primary() {}
	virtual void secondary() {}
	virtual void pairs() {}
};

// @??0BaseY005E7360@@QAE@PAVOwnerY005E7360@@@Z 0x005EEA60
BaseY005E7360::BaseY005E7360( OwnerY005E7360 *owner )
{
	for( int index = 0; index < 8; ++index )
	{
		entries[ index ].value = owner->records[ index ].value.getValue();
		entries[ index ].pointer = owner->records[ index ].pointer;
	}
}
