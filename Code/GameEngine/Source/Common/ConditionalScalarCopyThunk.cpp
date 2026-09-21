void conditionalScalarCopy(unsigned long *destination, const unsigned long *source)
{
    if (destination != 0) {
        *destination = *source;
    }
}

void conditionalScalarCopyAlternate(unsigned long *destination, const unsigned long *source)
{
    if (destination != 0) {
        *destination = *source;
    }
}

// The carved boundary at 0x0036CAD0 contains one ret and no known semantic owner.
void b_0036cad0()
{
}
