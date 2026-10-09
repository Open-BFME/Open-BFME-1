// cl: /MD
extern "C" {
__declspec(dllimport) void *__cdecl fopen(const char *, const char *);
__declspec(dllimport) int __cdecl fprintf(void *, const char *, ...);
__declspec(dllimport) int __cdecl fclose(void *);
}

struct Rva009AADF0MotionVector { short x, y; };
struct Rva009AADF0State {
    unsigned char pad00[0x1DC];
    int interlaced;
    unsigned char pad1E0[0x4C];
    unsigned int rows, columns;
    unsigned char pad234[0x4B8];
    signed char *interlacedModes;
    signed char *modes;
    Rva009AADF0MotionVector *motionVectors;
};
int Rva0134C940;
// ?Rva009AADF0PrintModes@@YAXPAURva009AADF0State@@@Z
// Ported from Open BFME 2 Code/Libraries/Source/VP6/debug.cpp.
void Rva009AADF0PrintModes(Rva009AADF0State *state)
{
    void *stream = fopen("modes.txt", "a");
    fprintf(stream, "Frame %d\n\n", Rva0134C940);
    for (unsigned int row = 3; row < state->rows - 3; ++row) {
        if (state->interlaced == 1) {
            for (unsigned int column = 3; column < state->columns - 3; ++column)
                fprintf(stream, "%d", state->interlacedModes[row * state->columns + column]);
            fprintf(stream, "   ");
        }
        for (unsigned int column = 3; column < state->columns - 3; ++column)
            fprintf(stream, "%d", state->modes[row * state->columns + column]);
        fprintf(stream, "   ");
        for (unsigned int column = 3; column < state->columns - 3; ++column)
            fprintf(stream, "%3d:%-3d", state->motionVectors[row * state->columns + column].x,
                state->motionVectors[row * state->columns + column].y);
        fprintf(stream, "\n");
    }
    fprintf(stream, "\n");
    fprintf(stream, "\n");
    fclose(stream);
    ++Rva0134C940;
}
