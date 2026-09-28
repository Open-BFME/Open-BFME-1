// cl: /DNDEBUG /MD /EHs-c-
// This is the six-byte Miles shutdown import veneer registered with atexit.
// Start proof: retail 0x009F8AB0 pushes VA 0x00DF8AA0 as the callback argument
// to the independently identified CRT atexit at RVA 0x009F6E26. Thus the
// reference is an executable entry point, not a pointer to ordinary data.
// End proof: indirect tail jump through the PE import slot for
// mss32!_AIL_shutdown@0, followed immediately by ten int3 bytes.
// The address remains in the name because other shutdown veneers also exist.
extern "C" __declspec(dllimport) void __stdcall AIL_shutdown();
extern "C" void __stdcall Rva009F8AA0() { AIL_shutdown(); }
