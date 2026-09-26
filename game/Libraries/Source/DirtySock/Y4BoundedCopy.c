// cl: /Od /GZ /GS /MD /DNDEBUG

void Rva0080D930( const char *source, int sourceLength,
	char *destination, int destinationLength )
{
	for ( ; sourceLength > 0 && destinationLength > 1;
		sourceLength--, destinationLength-- )
	{
		*destination = *source;
		destination++;
		source++;
	}

	if ( destinationLength > 0 )
	{
		*destination = 0;
	}
}

const unsigned char *Rva0080D7A0( const unsigned char *cursor,
	const unsigned char *end, int *firstByte, int *valueOut )
{
	int byteCount;
	unsigned int value;

	if ( valueOut != 0 )
	{
		*valueOut = 0;
	}
	if ( firstByte != 0 )
	{
		*firstByte = 0;
	}
	if ( cursor == 0 )
	{
		return 0;
	}
	if ( cursor == end )
	{
		return 0;
	}

	if ( firstByte != 0 )
	{
		*firstByte = *cursor;
	}
	cursor++;
	if ( cursor == end )
	{
		return 0;
	}

	value = *cursor;
	cursor++;
	if ( value > 0x7F )
	{
		byteCount = value & 0x7F;
		value = 0;
		for ( ; byteCount > 0; byteCount-- )
		{
			if ( cursor == end )
			{
				return 0;
			}
			value = ( value << 8 ) | *cursor;
			cursor++;
		}
	}

	if ( valueOut != 0 )
	{
		*valueOut = value;
	}
	return cursor;
}
