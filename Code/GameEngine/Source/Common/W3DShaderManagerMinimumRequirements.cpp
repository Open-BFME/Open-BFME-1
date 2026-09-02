// cl: /DNDEBUG /MD

enum ChipsetType { DC_UNKNOWN = 0 };
enum CpuType { XX = 0, P3 = 1, P4 = 2, K7 = 3 };

class CPUDetectClass
{
public:
	enum ProcessorManufacturerType { MANUFACTURER_INTEL = 1, MANUFACTURER_AMD = 3 };
	enum AMDProcessorType { AMD_PROCESSOR_ATHLON_025 = 15 };
	enum IntelProcessorType { INTEL_PROCESSOR_PENTIUM_III_MODEL_7 = 22, INTEL_PROCESSOR_PENTIUM4 = 29 };

	static ProcessorManufacturerType ProcessorManufacturer;
	static AMDProcessorType AMDProcessor;
	static IntelProcessorType IntelProcessor;
	static int ProcessorSpeed;
	static unsigned int TotalPhysicalMemory;
};

extern "C" void RunBenchmark(int, void *, float *, float *, float *);

class BfmeChipsetDetector
{
public:
	static void detect();
};

class W3DShaderManager
{
public:
	static ChipsetType getChipset();
	static bool testMinimumRequirements(ChipsetType *videoChipType, CpuType *cpuType,
		int *cpuFreq, int *numRAM, float *intBenchIndex, float *floatBenchIndex, float *memBenchIndex);

protected:
	static ChipsetType m_currentChipset;
};

bool W3DShaderManager::testMinimumRequirements(ChipsetType *videoChipType, CpuType *cpuType,
	int *cpuFreq, int *numRAM, float *intBenchIndex, float *floatBenchIndex, float *memBenchIndex)
{
	if (videoChipType) {
		BfmeChipsetDetector::detect();
		*videoChipType = m_currentChipset;
	}

	if (cpuType) {
		*cpuType = XX;
		if (CPUDetectClass::ProcessorManufacturer == CPUDetectClass::MANUFACTURER_AMD &&
			CPUDetectClass::AMDProcessor >= CPUDetectClass::AMD_PROCESSOR_ATHLON_025)
			*cpuType = K7;
		if (CPUDetectClass::ProcessorManufacturer == CPUDetectClass::MANUFACTURER_INTEL &&
			CPUDetectClass::IntelProcessor >= CPUDetectClass::INTEL_PROCESSOR_PENTIUM_III_MODEL_7)
			*cpuType = P3;
		if (CPUDetectClass::ProcessorManufacturer == CPUDetectClass::MANUFACTURER_INTEL &&
			CPUDetectClass::IntelProcessor >= CPUDetectClass::INTEL_PROCESSOR_PENTIUM4)
			*cpuType = P4;
	}

	if (cpuFreq)
		*cpuFreq = CPUDetectClass::ProcessorSpeed;
	if (numRAM)
		*numRAM = CPUDetectClass::TotalPhysicalMemory;
	if (intBenchIndex && floatBenchIndex && memBenchIndex)
		RunBenchmark(0, 0, floatBenchIndex, intBenchIndex, memBenchIndex);

	return true;
}
