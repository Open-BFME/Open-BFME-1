#include <windows.h>
void __cdecl map_test_entry(void) {
    HANDLE file, mapping;
    LPVOID base, view;
    file = CreateFileA("minimal-map.tmp", GENERIC_READ | GENERIC_WRITE, 0, 0,
        CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_DELETE_ON_CLOSE, 0);
    if (file == INVALID_HANDLE_VALUE) ExitProcess(1);
    mapping = CreateFileMappingA(file, 0, PAGE_READWRITE, 0, 262144, 0);
    if (!mapping) ExitProcess(2);
    base = VirtualAlloc(0, 262144, MEM_RESERVE | MEM_TOP_DOWN, PAGE_READWRITE);
    if (!base) ExitProcess(3);
    if (!VirtualFree(base, 0, MEM_RELEASE)) ExitProcess(4);
    view = MapViewOfFileEx(mapping, FILE_MAP_ALL_ACCESS, 0, 0, 262144, base);
    if (!view) ExitProcess(5);
    if (view != base) ExitProcess(6);
    ((unsigned char *)view)[0] = 0xA5;
    ((unsigned char *)view)[262143] = 0x5A;
    if (!UnmapViewOfFile(view)) ExitProcess(7);
    if (!CloseHandle(mapping)) ExitProcess(8);
    if (!CloseHandle(file)) ExitProcess(9);
    ExitProcess(0);
}
