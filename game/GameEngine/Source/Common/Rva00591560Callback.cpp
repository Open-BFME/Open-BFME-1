// cl: /O2 /Ob0

void __cdecl bfmeFree591560( void *block );

class Rva00591560Resource
{
public:
	void run();
	void destroy();
};

class Rva00591560Context
{
public:
	Rva00591560Resource *find();
	void clear( Rva00591560Resource *resource );
};

int __cdecl rva00591560Callback( Rva00591560Context *context, int message )
{
	if( context )
	{
		switch( message )
		{
		case 0x4008:
		{
			Rva00591560Resource *resource = context->find();
			if( resource )
			{
				resource->run();
				return 1;
			}
			break;
		}

		case 2:
		{
			Rva00591560Resource *resource = context->find();
			if( resource )
			{
				resource->destroy();
				bfmeFree591560( resource );
			}
			context->clear( 0 );
			break;
		}

		default:
			break;
		}
	}

	return 1;
}
