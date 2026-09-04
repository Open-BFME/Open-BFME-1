struct BfmeColorAdjust_00783070 {
    int reserved;
    float mult[4];
    float add[4];
};

extern BfmeColorAdjust_00783070 g_bfmeColorAdjust_00783070;
extern float g_bfmeColorBias_00783070;
extern float g_bfmeColorScale_00783070;

extern "C" long __ftol2(double value);

static int bfmeColorComponent_00783070(unsigned int value, int index) {
    unsigned int channel = value;
    float result = (float)channel;
    result = result * g_bfmeColorBias_00783070;
    result = result * g_bfmeColorAdjust_00783070.mult[index];
    result = result + g_bfmeColorAdjust_00783070.add[index];
    result = result * g_bfmeColorScale_00783070;
    return (int)result;
}

int __cdecl bfmeHelpWI(int color) {
    unsigned int value = (unsigned int)color;
    unsigned int first = (value >> 16) & 0xff;
    unsigned int second = (value >> 24) & 0xff;
    unsigned int third = (value >> 8) & 0xff;
    unsigned int fourth = value & 0xff;
    int result = bfmeColorComponent_00783070(first, 1);
    result = result | (bfmeColorComponent_00783070(second, 0) << 8);
    result = result << 8;
    result = result | bfmeColorComponent_00783070(third, 2);
    result = result << 8;
    result = result | bfmeColorComponent_00783070(fourth, 3);
    return result;
}
