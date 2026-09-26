// Store the three low color channels as normalized floating-point values.
// The address-derived name retains the unproven calling owner.
extern float g_0107C64C;
extern float Rva00783F90Red;
extern float Rva00783F90Green;
extern float Rva00783F90Blue;

void Rva00783F90StorePackedColor(unsigned int color)
{
    unsigned int red = (color >> 16) & 255;
    Rva00783F90Red = (float)red * g_0107C64C;
    unsigned int green = (color >> 8) & 255;
    Rva00783F90Green = (float)green * g_0107C64C;
    unsigned int blue = color & 255;
    Rva00783F90Blue = (float)blue * g_0107C64C;
}
