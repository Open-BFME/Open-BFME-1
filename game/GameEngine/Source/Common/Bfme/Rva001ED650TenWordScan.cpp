// cl: /DNDEBUG /MD /EHsc

class Rva001ED650
{
	unsigned values[10];

public:
	bool allPresent() const;
};

bool Rva001ED650::allPresent() const
{
	for( unsigned index = 0; index < 10; ++index )
		if( values[index] != 0 )
			return true;
	return false;
}
