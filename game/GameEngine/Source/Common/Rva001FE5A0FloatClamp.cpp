// cl: /DNDEBUG /MD /EHsc
// Address-derived secondary-interface method. Retail clamps the referenced
// value plus five to at least one before converting it to an integer.

class Rva001FE5A0Owner
{
public:
	void updateClampedValue();
};

void Rva001FE5A0Owner::updateClampedValue()
{
	unsigned char *source = *(unsigned char **)((unsigned char *)this - 0x1C);
	float value = *(float *)(source + 0x24) * 5.0f;
	float minimum = 1.0f;
	float *selected = minimum > value ? &minimum : &value;
	*(int *)((unsigned char *)this + 0x0C) = (int)*selected;
}
