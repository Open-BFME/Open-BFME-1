// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
#include "cpudetect.h"
// Retail starts are preceded by INT3; each six-byte body ends RET then INT3.
// Opaque names preserve address identity; global targets agree with CPUDetectClass.
// VA 0x0134EDE4: HasCPUIDInstruction; cpudetect.h::Has_CPUID_Instruction.
bool Rva009DE5A0Query() { return CPUDetectClass::Has_CPUID_Instruction(); }
// VA 0x0134EDE5: HasRDTSCInstruction; cpudetect.h::Has_RDTSC_Instruction.
bool Rva009DE5B0Query() { return CPUDetectClass::Has_RDTSC_Instruction(); }
// VA 0x0134EDE9: HasMMXSupport; cpudetect.h::Has_MMX_Instruction_Set.
bool Rva009DE5C0Query() { return CPUDetectClass::Has_MMX_Instruction_Set(); }
// VA 0x0134EDE6: HasSSESupport; cpudetect.h::Has_SSE_Instruction_Set.
bool Rva009DE5D0Query() { return CPUDetectClass::Has_SSE_Instruction_Set(); }
// VA 0x0134EDE7: HasSSE2Support; cpudetect.h::Has_SSE2_Instruction_Set.
bool Rva009DE5E0Query() { return CPUDetectClass::Has_SSE2_Instruction_Set(); }
// VA 0x0134EDEA: Has3DNowSupport; cpudetect.h::Has_3DNow_Instruction_Set.
bool Rva009DE5F0Query() { return CPUDetectClass::Has_3DNow_Instruction_Set(); }
// VA 0x0134EDEB: HasExtended3DNowSupport; cpudetect.h::Has_Extended_3DNow_Instruction_Set.
bool Rva009DE600Query() { return CPUDetectClass::Has_Extended_3DNow_Instruction_Set(); }
// VA 0x0134ED20: FeatureBits; cpudetect.h::Get_Feature_Bits.
unsigned Rva009DE610Query() { return CPUDetectClass::Get_Feature_Bits(); }
// VA 0x0134EDAC: ExtendedFeatureBits; cpudetect.h::Get_Extended_Feature_Bits.
unsigned Rva009DE620Query() { return CPUDetectClass::Get_Extended_Feature_Bits(); }
// VA 0x0134ED1C: L2CacheSize; cpudetect.h::Get_L2_Cache_Size.
unsigned Rva009DE630Query() { return CPUDetectClass::Get_L2_Cache_Size(); }
// VA 0x0134ED64: L2CacheLineSize; cpudetect.h::Get_L2_Cache_Line_Size.
unsigned Rva009DE640Query() { return CPUDetectClass::Get_L2_Cache_Line_Size(); }
// VA 0x0134ED68: L2CacheSetAssociative; cpudetect.h::Get_L2_Cache_Set_Associative.
unsigned Rva009DE650Query() { return CPUDetectClass::Get_L2_Cache_Set_Associative(); }
// VA 0x0134ED08: L1DataCacheSize; cpudetect.h::Get_L1_Data_Cache_Size.
unsigned Rva009DE660Query() { return CPUDetectClass::Get_L1_Data_Cache_Size(); }
// VA 0x0134ED7C: L1DataCacheLineSize; cpudetect.h::Get_L1_Data_Cache_Line_Size.
unsigned Rva009DE670Query() { return CPUDetectClass::Get_L1_Data_Cache_Line_Size(); }
// VA 0x0134EDC4: L1DataCacheSetAssociative; cpudetect.h::Get_L1_Data_Cache_Set_Associative.
unsigned Rva009DE680Query() { return CPUDetectClass::Get_L1_Data_Cache_Set_Associative(); }
// VA 0x0134ED98: L1InstructionCacheSize; cpudetect.h::Get_L1_Instruction_Cache_Size.
unsigned Rva009DE690Query() { return CPUDetectClass::Get_L1_Instruction_Cache_Size(); }
// VA 0x0134ED80: L1InstructionCacheLineSize; cpudetect.h::Get_L1_Instruction_Cache_Line_Size.
unsigned Rva009DE6A0Query() { return CPUDetectClass::Get_L1_Instruction_Cache_Line_Size(); }
// VA 0x0134ED18: L1InstructionCacheSetAssociative; cpudetect.h::Get_L1_Instruction_Cache_Set_Associative.
unsigned Rva009DE6B0Query() { return CPUDetectClass::Get_L1_Instruction_Cache_Set_Associative(); }
// VA 0x0134EDB8: L1InstructionTraceCacheSize; cpudetect.h::Get_L1_Instruction_Trace_Cache_Size.
unsigned Rva009DE6C0Query() { return CPUDetectClass::Get_L1_Instruction_Trace_Cache_Size(); }
// VA 0x0134ED60: AvailablePhysicalMemory; cpudetect.h::Get_Available_Physical_Memory.
unsigned Rva009DE6D0Query() { return CPUDetectClass::Get_Available_Physical_Memory(); }
// VA 0x0134ED88: TotalPageMemory; cpudetect.h::Get_Total_Page_File_Size.
unsigned Rva009DE6E0Query() { return CPUDetectClass::Get_Total_Page_File_Size(); }
// VA 0x0134ED74: AvailablePageMemory; cpudetect.h::Get_Available_Page_File_Size.
unsigned Rva009DE6F0Query() { return CPUDetectClass::Get_Available_Page_File_Size(); }
// VA 0x0134ED84: TotalVirtualMemory; cpudetect.h::Get_Total_Virtual_Memory.
unsigned Rva009DE700Query() { return CPUDetectClass::Get_Total_Virtual_Memory(); }
// VA 0x0134ED14: AvailableVirtualMemory; cpudetect.h::Get_Available_Virtual_Memory.
unsigned Rva009DE710Query() { return CPUDetectClass::Get_Available_Virtual_Memory(); }
// VA 0x0134EDE0: ProcessorType; cpudetect.h::Get_Processor_Type.
unsigned Rva009DE720Query() { return CPUDetectClass::Get_Processor_Type(); }
// VA 0x0134ED24: ProcessorString; cpudetect.h::Get_Processor_String.
const char* Rva009DE730Query() { return CPUDetectClass::Get_Processor_String(); }
