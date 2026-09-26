struct RvaA22F0FieldReset
{
    unsigned char unused[4];
    unsigned int value04;
    unsigned int value08;
    unsigned int value0C;
    unsigned int value10;
    unsigned int value14;
    unsigned int value18;
    unsigned int value1C;
    unsigned int value20;
    unsigned int value24;
    unsigned int value28;
    unsigned int value2C;
    unsigned int value30;
    unsigned int value34;
    unsigned int value38;
    unsigned int value3C;
    unsigned int value40;
    unsigned int value44;
    unsigned int value48;
    unsigned int value4C;
    unsigned int unused50;
    unsigned int value54;

    void reset();
};

// ?d_000a22f0@@YAXXZ
void RvaA22F0FieldReset::reset()
{
    value0C = 0;
    value10 = 0;
    value14 = 0;
    value18 = 0;
    value1C = 0;
    value20 = 0;
    value54 = 0;
    value08 = 0;
    value04 = 0;
    value30 = 0;
    value34 = 0;
    value38 = 0;
    value3C = 0;
    value40 = 0;
    value44 = 0;
    value48 = 0;
    value4C = 0;
    value24 = 0;
    value28 = 0;
    value2C = 0;
}
