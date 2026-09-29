// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Four EA Apt ActionScript handlers that do nothing in BFME, each a lone
// `ret` in the opcode table based at 0x00ED5A68 (see
// AptActionInterpreterStoreRegister.cpp for how the base is fixed):
//   0x00 End            retail 0x008C56F0 (table slot 0x00ED5A68)
//   0x08 ToggleQuality  retail 0x008C5760 (table slot 0x00ED5A88)
//   0x09 StopSounds     retail 0x008C5770 (table slot 0x00ED5A8C)
//   0x8A WaitForFrame   retail 0x008C5A50 (table slot 0x00ED5C90)

class AptActionInterpreter
{
public:
	struct LocalContextT;

	static void _FunctionAptActionEnd(AptActionInterpreter *interpreter, LocalContextT *context);
	static void _FunctionAptActionToggleQuality(AptActionInterpreter *interpreter, LocalContextT *context);
	static void _FunctionAptActionStopSounds(AptActionInterpreter *interpreter, LocalContextT *context);
	static void _FunctionAptActionWaitForFrame(AptActionInterpreter *interpreter, LocalContextT *context);
};

void AptActionInterpreter::_FunctionAptActionEnd(AptActionInterpreter *, LocalContextT *)
{
}

void AptActionInterpreter::_FunctionAptActionToggleQuality(AptActionInterpreter *, LocalContextT *)
{
}

void AptActionInterpreter::_FunctionAptActionStopSounds(AptActionInterpreter *, LocalContextT *)
{
}

void AptActionInterpreter::_FunctionAptActionWaitForFrame(AptActionInterpreter *, LocalContextT *)
{
}
