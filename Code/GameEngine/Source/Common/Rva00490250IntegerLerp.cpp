// Retail 0x00490250: integer interpolation using the shared BFME scale.

#define BFME_AT(TYPE, ADDRESS) (*(TYPE *)(ADDRESS))

int Rva00490250IntegerLerp( int a, int b, int t )
{
	float factor = (float)t * BFME_AT( float, 0x01076C24 );
	int difference = b - a;

	return a + (int)(factor * difference);
}
