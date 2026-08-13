// cl: /DNDEBUG /MD /EHsc

typedef void *(__stdcall *D3DXMatrixInverseFunction)(void *, float *, const void *);
extern D3DXMatrixInverseFunction g_D3DXMatrixInverseImport;

extern "C" void *__stdcall D3DXMatrixInverse(void *output, float *determinant,
                                              const void *input)
{
    return g_D3DXMatrixInverseImport(output, determinant, input);
}
