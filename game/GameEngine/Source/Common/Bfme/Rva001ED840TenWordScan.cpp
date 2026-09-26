// cl: /DNDEBUG /MD /EHsc

class Rva001ED840
{
	unsigned values[10];

public:
	bool anyPresent() const;
};

bool Rva001ED840::anyPresent() const
{
	for( unsigned index = 0; index < 10; ++index )
		if( values[index] != 0 )
			return true;
	return false;
}
