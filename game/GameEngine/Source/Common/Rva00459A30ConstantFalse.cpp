// ?isFalse@Rva00459A30ConstantFalse@@QBE_NXZ
// Retail 0x00459A30 returns a false byte and does not read this.
// The only boundary evidence reaches the address through an ILT thunk.
// No caller or layout evidence proves a semantic class or method name.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva00459A30ConstantFalse
{
public:
    bool isFalse() const;
};

bool Rva00459A30ConstantFalse::isFalse() const
{
    return false;
}
