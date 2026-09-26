// The retail body at 0x00848080 is a 16-bit constant return (mov ax, 0x20; ret).
// Its semantic owner was not recovered, so keep the identity address-derived.
unsigned short rva_848080_constant_twenty()
{
    return 0x20;
}
