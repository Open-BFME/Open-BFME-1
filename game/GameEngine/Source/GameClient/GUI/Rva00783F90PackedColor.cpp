// Store the three low color channels as normalized floating-point values.
// The address-derived name retains the unproven calling owner.
extern const float g_0107C64C;
// Retail .bss VA 0x0130696C/70/74: the stored red, green and blue channels. Address-derived names.
float g_Va0130696C;
float g_Va01306970;
float g_Va01306974;

void Rva00783F90StorePackedColor(unsigned int color)
{
    unsigned int red = (color >> 16) & 255;
    g_Va0130696C = (float)red * g_0107C64C;
    unsigned int green = (color >> 8) & 255;
    g_Va01306970 = (float)green * g_0107C64C;
    unsigned int blue = color & 255;
    g_Va01306974 = (float)blue * g_0107C64C;
}

// Retail .rdata at VA 0x0107C64C: 81 80 80 3b (float 1/255).
// The original symbol name is unproven; retain the address-derived spelling.
const float g_0107C64C = 0.0039215688593685626983642578125f;
