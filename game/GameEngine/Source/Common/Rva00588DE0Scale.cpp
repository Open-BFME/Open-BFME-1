// cl: /O2
// Retail converts the integer directly in x87 before applying global scale and bias.
extern const float g_01076C24;
extern float g_bfmeDefaultBU;

float Rva00588DE0Scale(int count)
{
    return count * g_01076C24 + g_bfmeDefaultBU;
}
