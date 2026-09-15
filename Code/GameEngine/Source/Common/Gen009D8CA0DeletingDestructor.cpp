// cl: /O2 /EHsc
//
// Gen009D8CA0 scalar-deleting destructor, retail 0x009D9090.
// Its matched three-argument constructor at 0x009D8CA0 installs the named
// vtable 0x01144180; slot zero of that table is this wrapper.  The complete
// destructor is the existing folded body at 0x009D8D00.

class Gen009D8CA0Base
{
public:
	virtual ~Gen009D8CA0Base();
};

Gen009D8CA0Base::~Gen009D8CA0Base()
{
}

class Gen009D8CA0 : public Gen009D8CA0Base
{
public:
	virtual ~Gen009D8CA0();
};

Gen009D8CA0::~Gen009D8CA0()
{
}

void forceGen009D8CA0DeletingDestructor()
{
	Gen009D8CA0 value;
}
