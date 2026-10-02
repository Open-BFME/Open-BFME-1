// cl: /DNDEBUG /MD /EHsc
// RVA0085F2B0: INT3 boundary, 55-byte cdecl body through RET at+0x36.
// Four incoming stack slots; first ignored, second stored at context+0x54,
// third is the piMangleUser output buffer, fourth points to the context.
// Lookup00860700 independently reads connection+0x8b0; a nonzero result
// replaces context+0x5c before piMangleUser(buffer,field54,field5C).
// The original callback/context identity remains unproven.
class Rva00860700 { public: static unsigned get(const unsigned *); };
extern "C" void piMangleUser(char *,unsigned,int);
struct Rva0085F2B0Context {
    const unsigned *field00;
    unsigned char gap04[0x50];
    unsigned field54;
    unsigned gap58;
    int field5C;
};
void rva0085F2B0(const void *, unsigned value, char *buffer, Rva0085F2B0Context **slot)
{
    Rva0085F2B0Context *context=*slot;
    context->field54=value;
    unsigned result=Rva00860700::get(context->field00);
    if(result) context->field5C=result;
    piMangleUser(buffer,context->field54,context->field5C);
}
