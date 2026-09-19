// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc
// The body proves a float read at offset 0x188.

class Rva006003D0
{
public:
	float get() const;
};

// ?get@Rva006003D0@@QBEMXZ
float Rva006003D0::get() const
{
	return *reinterpret_cast<const float *>(
		reinterpret_cast<const unsigned char *>(this) + 0x188);
}
