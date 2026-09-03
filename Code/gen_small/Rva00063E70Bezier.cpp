// cl: /DNDEBUG /MD /EHs-c-
// Quadratic Bezier and constant-coefficient blends out of d_0001466e.asm.
// Identity is address-derived; the constants are the image's float pool.

// ?Rva00063E70Bezier@@YAMMMMM@Z
float Rva00063E70Bezier(float a, float b, float c, float t)
{
	float u = 1.0f - t;
	float au = a * u;
	float inner = au + (b * t + b * t);
	return u * inner + c * t * t;
}


