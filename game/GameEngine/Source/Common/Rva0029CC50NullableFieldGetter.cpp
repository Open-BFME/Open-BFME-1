struct Rva0029CC50NullableFieldGetter
{
	int get( int *value );
};

int Rva0029CC50NullableFieldGetter::get( int *value )
{
	if ( value )
		return value[ 15 ];
	return 0;
}
