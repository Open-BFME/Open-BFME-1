// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
extern void *g_aptLivingWorldWindowIndex;
void *bfmeMakeEYA(unsigned int low, unsigned int high);

void bfmeRva00C6BC50InitializeWindowIndex()
{
    g_aptLivingWorldWindowIndex = bfmeMakeEYA(0, 0);
}
