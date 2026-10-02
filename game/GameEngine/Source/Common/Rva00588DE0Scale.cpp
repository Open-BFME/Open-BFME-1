// cl: /O2
// Retail converts the integer directly in x87 before applying global scale and bias.
extern const float g_01076C24;
extern float g_bfmeDefaultBU;

float Rva00588DE0Scale(int count)
{
    return count * g_01076C24 + g_bfmeDefaultBU;
}

// Retail .rdata 0x01076C24: 0A D7 23 3C; the x87 FMUL above reads four bytes.
// No source-level identity is proven for this shared 0.01f literal.
const float g_01076C24 = 0.01f;
