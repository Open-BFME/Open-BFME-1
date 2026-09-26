// cl: /DNDEBUG /MD

struct Rva00249F00Node
{
	Rva00249F00Node *next;
	void *unused;
	void *value;
};

struct Rva00249F00List
{
	Rva00249F00Node *sentinel;
};

class Gen_002227A0
{
public:
	#define RVASLOT(n) virtual void slot##n();
	RVASLOT(0) RVASLOT(1) RVASLOT(2) RVASLOT(3) RVASLOT(4) RVASLOT(5)
	RVASLOT(6) RVASLOT(7) RVASLOT(8) RVASLOT(9) RVASLOT(10) RVASLOT(11)
	RVASLOT(12) RVASLOT(13) RVASLOT(14) RVASLOT(15) RVASLOT(16) RVASLOT(17)
	RVASLOT(18) RVASLOT(19) RVASLOT(20) RVASLOT(21) RVASLOT(22) RVASLOT(23)
	RVASLOT(24) RVASLOT(25) RVASLOT(26) RVASLOT(27) RVASLOT(28) RVASLOT(29)
	RVASLOT(30) RVASLOT(31) RVASLOT(32) RVASLOT(33) RVASLOT(34) RVASLOT(35)
	RVASLOT(36) RVASLOT(37) RVASLOT(38) RVASLOT(39) RVASLOT(40) RVASLOT(41)
	RVASLOT(42) RVASLOT(43) RVASLOT(44) RVASLOT(45) RVASLOT(46) RVASLOT(47)
	RVASLOT(48) RVASLOT(49) RVASLOT(50) RVASLOT(51) RVASLOT(52) RVASLOT(53)
	RVASLOT(54) RVASLOT(55) RVASLOT(56) RVASLOT(57) RVASLOT(58) RVASLOT(59)
	RVASLOT(60) RVASLOT(61) RVASLOT(62) RVASLOT(63) RVASLOT(64) RVASLOT(65)
	#undef RVASLOT
	virtual Rva00249F00List *getList();

	bool containsOrAccepts( void *value );
	bool bfmeContains( void *value ) const;
};

bool Gen_002227A0::containsOrAccepts( void *value )
{
	Rva00249F00List *list = getList();
	Rva00249F00Node *sentinel = list->sentinel;

	for ( Rva00249F00Node *node = sentinel->next;
		node != sentinel; node = node->next )
	{
		if ( node->value == value )
			return true;
	}

	return bfmeContains( value );
}
