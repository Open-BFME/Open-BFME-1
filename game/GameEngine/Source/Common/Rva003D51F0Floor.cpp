// cl: /MD
// Retail RVA0x003D51F0 is a float-argument wrapper around MSVCR71 floor.
// The previous ceilf alias hid the wrong import behind DIR32 rebasing.
// The address-derived name does not claim an original owning class.
extern "C" __declspec(dllimport) double __cdecl floor(double value);

float bfmeFloor003D51F0(float value)
{
    return (float)floor(value);
}
