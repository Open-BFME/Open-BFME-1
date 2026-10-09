// cl: /MD

struct Rva009AA260Context
{
    unsigned char m_pad00[0x40];
    int m_value40;
    int m_value44;
    unsigned char m_pad48[0x10];
    int m_hscale;
    int m_hratio;
    int m_vscale;
    int m_vratio;
    unsigned char m_pad68[0x10];
    unsigned char *m_data78;
    unsigned char *m_data7C;
    unsigned char *m_data80;
};
struct Rva009AA100Args
{
    int m_value00;
    int m_value04;
    int m_value08;
    int m_value0C;
    int m_value10;
    int m_value14;
    unsigned char *m_data18;
    unsigned char *m_data1C;
    unsigned char *m_data20;
};

void __cdecl Rva009A9400(Rva009AA260Context *, const unsigned char *, int, unsigned int, unsigned int, unsigned char *, unsigned int, unsigned int, unsigned int);

// Ported from Open BFME 2 Code/Libraries/Source/VP6/scalesystem.cpp.
// ?Rva009AA100@@YAXPAURva009AA260Context@@HPAURva009AA100Args@@@Z
void __cdecl Rva009AA100(Rva009AA260Context *context, int byteOffset, Rva009AA100Args *args)
{
    int width = context->m_value40;
    int height = context->m_value44;
    int outputWidth = args->m_value00;
    int outputHeight = args->m_value04;
    Rva009A9400(context, context->m_data78 + byteOffset, width + 32, width, height, args->m_data18, outputWidth, outputWidth, outputHeight);
    width >>= 1;
    height >>= 1;
    outputWidth >>= 1;
    outputHeight >>= 1;
    int sourcePitch = width + 16;
    Rva009A9400(context, context->m_data7C + byteOffset, sourcePitch, width, height, args->m_data1C, outputWidth, outputWidth, outputHeight);
    Rva009A9400(context, context->m_data80 + byteOffset, sourcePitch, width, height, args->m_data20, outputWidth, outputWidth, outputHeight);
}

struct Rva009AA1B0Args
{
    int m_value00;
    int m_value04;
    int m_value08;
    int m_value0C;
    int m_value10;
    int m_value14;
    unsigned char *m_data18;
    unsigned char *m_data1C;
    unsigned char *m_data20;
};

void __cdecl Rva009A97B0(Rva009AA260Context *, const unsigned char *, int, unsigned int, unsigned int, unsigned char *, unsigned int, unsigned int, unsigned int);

// Ported from Open BFME 2 Code/Libraries/Source/VP6/scalesystem.cpp.
// ?Rva009AA1B0@@YAXPAURva009AA260Context@@HPAURva009AA1B0Args@@@Z
void __cdecl Rva009AA1B0(Rva009AA260Context *context, int byteOffset, Rva009AA1B0Args *args)
{
    int width = context->m_value40;
    int height = context->m_value44;
    int outputWidth = args->m_value00;
    int outputHeight = args->m_value04;
    unsigned char *source0 = context->m_data78;
    unsigned char *dest0 = args->m_data18;
    Rva009A97B0(context, source0 + byteOffset, width + 32, width, height, dest0, outputWidth, outputWidth, outputHeight);
    width >>= 1;
    height >>= 1;
    outputWidth >>= 1;
    outputHeight >>= 1;
    int sourcePitch = width + 16;
    Rva009A97B0(context, context->m_data7C + byteOffset, sourcePitch, width, height, args->m_data1C, outputWidth, outputWidth, outputHeight);
    Rva009A97B0(context, context->m_data80 + byteOffset, sourcePitch, width, height, args->m_data20, outputWidth, outputWidth, outputHeight);
}
