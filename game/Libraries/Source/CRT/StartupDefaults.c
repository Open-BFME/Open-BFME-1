// cl: /O1 /MD
#include <math.h>

// Keep the native merr.obj flag and callback together so its strong archive member stays unselected.
int __defaultmatherr = 1;
int _commode = 0;
int _adjust_fdiv;
int _newmode = 0;
int _dowildcard = 0;

int __cdecl _matherr(struct _exception *error)
{
    return 0;
}
