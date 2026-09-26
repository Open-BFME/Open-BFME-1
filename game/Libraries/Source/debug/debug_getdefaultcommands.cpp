// cl: /DNDEBUG /MD /EHa /Oy-
// BFME DebugGetDefaultCommands (0x0005CC10).  Zero Hour twin:
// debug_getdefaultcommands.cpp, kept in its own file so the game can override
// it.  Retail reaches this body only through ILT 0x0000344A, called only from
// Debug::PostStaticInit (0x0088B18B) where Zero Hour calls
// DebugGetDefaultCommands; BFME's override returns NULL (xor eax,eax; ret).

const char *DebugGetDefaultCommands(void)
{
  return 0;
}
