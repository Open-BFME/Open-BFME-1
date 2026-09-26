// cl: /O2
extern "C" __declspec(dllimport) void __stdcall AIL_set_redist_directory(const char *);
extern "C" __declspec(dllimport) int __stdcall AIL_set_3D_sample_info(void *, void *);
extern "C" __declspec(dllimport) void __stdcall AIL_set_file_callbacks(void *, void *, void *, void *);
extern "C" __declspec(dllimport) void __stdcall AIL_service_stream(void *, int);
extern "C" __declspec(dllimport) unsigned int __stdcall AIL_ms_count();
extern "C" __declspec(dllimport) void __stdcall AIL_mem_free_lock(void *);
void __stdcall Rva009F8AC0SetRedistDirectory(const char *p) { AIL_set_redist_directory(p); }
int __stdcall Rva009F8AC6Set3DSampleInfo(void *sample, void *info) { return AIL_set_3D_sample_info(sample, info); }
void __stdcall Rva009F8ACCSetFileCallbacks(void *a, void *b, void *c, void *d) { AIL_set_file_callbacks(a, b, c, d); }
void __stdcall Rva009F8AD2ServiceStream(void *stream, int fillup) { AIL_service_stream(stream, fillup); }
unsigned int __stdcall Rva009F8AD8Milliseconds() { return AIL_ms_count(); }
void __stdcall Rva009F8ADEFreeLockedMemory(void *p) { AIL_mem_free_lock(p); }
