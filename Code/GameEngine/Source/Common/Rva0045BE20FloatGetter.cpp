// ?get@Rva0045BE20FloatField@@QBEMXZ
// The carved boundary proves a const thiscall getter for the float at +0x6C.
// No caller identifies the owning class or field semantically.
// cl: /O2 /Ob2 /G6 /DNDEBUG /MD /EHs-c-

class Rva0045BE20FloatField
{
public:
	float get() const;
};

float Rva0045BE20FloatField::get() const
{
	return *reinterpret_cast<const float *>(
		reinterpret_cast<const char *>(this) + 0x6c);
}
