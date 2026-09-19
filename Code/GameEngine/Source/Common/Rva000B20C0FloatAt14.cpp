// The carved boundary at 0x000B20C0 loads a float from this+0x14 and returns.
// No caller or class table proves the semantic owner.
class Rva000B20C0Owner
{
public:
	float fieldAt14(void) const;
};

float Rva000B20C0Owner::fieldAt14(void) const
{
	return *(const float *)((const unsigned char *)this + 0x14);
}
