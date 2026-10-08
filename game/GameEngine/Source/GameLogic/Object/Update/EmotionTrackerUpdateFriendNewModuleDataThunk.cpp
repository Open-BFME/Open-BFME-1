// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: EmotionTrackerUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class EmotionTrackerUpdateModuleData
{
public:
	EmotionTrackerUpdateModuleData();
	virtual ~EmotionTrackerUpdateModuleData();

private:
	unsigned char m_pad[0x38];
};

class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

extern "C" void __cdecl __identifier("EmotionTrackerUpdateFieldParse")();

class EmotionTrackerUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@EmotionTrackerUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *EmotionTrackerUpdate::friend_newModuleData(INI *ini)
{
	EmotionTrackerUpdateModuleData *data = new EmotionTrackerUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>(__identifier("EmotionTrackerUpdateFieldParse")));
	return (ModuleData *)data;
}

// Retail's factory at EmotionTrackerUpdate pushes 0x00417FD5 here (see
// ?friend_newModuleData@EmotionTrackerUpdate@@SAPAVModuleData@@PAVINI@@@Z), and the only
// symbol the build defines at that address is the five-byte ILT thunk
// ?j_00017fd5@@YAXXZ (game/gen_small/gthunks_026.cpp), a `jmp` to 0x00290E30, the
// module-data class's static field-parse builder.  The old
// `extern "C" EmotionTrackerUpdateFieldParse` was invented in this TU and nothing
// defines it; the thunk is retail's real spelling of this operand.
