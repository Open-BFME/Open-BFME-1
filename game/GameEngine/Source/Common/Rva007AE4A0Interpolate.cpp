// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Complete retail leaf: linear interpolation with double endpoints and a
// single-precision interpolation factor.
double rva007AE4A0Interpolate( double first, double second, float factor )
{
	return first + ( second - first ) * factor;
}
