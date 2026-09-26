// ?value@Rva006DF5A0Value@@QBEMXZ
// The carved body at 0x006DF5A0 only proves a const thiscall float load from
// this+0x08, so the address-derived owner keeps the identity honest.

class Rva006DF5A0Value
{
public:
	float value() const;
};

float Rva006DF5A0Value::value() const
{
	return *(const float *)((const char *)this + 8);
}
