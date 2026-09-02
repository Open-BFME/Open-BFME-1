// stlport
// STLport 4.5.3 Win32 CRT-descriptor mode translation.

namespace _SgI {

struct ioinfo
{
    long osfhnd;
    char osfile;
    char pipech;
    char reserved[30];
};

extern "C" __declspec(dllimport) ioinfo *__pioinfo[];

static int flag_to_openmode(int mode)
{
    int result;
    switch (mode & 3)
    {
    case 0:
        result = 8;
        break;
    case 1:
        result = 16;
        break;
    case 2:
        result = 8 | 16;
        break;
    }
    if (mode & 8)
        result |= 1;
    if (mode & 0x8000)
        result |= 4;
    return result;
}

int _get_osfflags(int fd, void *osHandle)
{
    char dosflags = __pioinfo[fd >> 5][fd & 31].osfile;
    int mode = 0;

    (void)osHandle;
    if (dosflags & 0x20)
        mode |= 8;
    if (dosflags & (char)0x80)
        mode |= 0x4000;
    else
        mode |= 0x8000;
    if (dosflags & 0x04)
        mode |= 2;

    return flag_to_openmode(mode);
}

}
