// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib

#include "always.h"
#include "win.h"
#include "mmsys.h"
#include <stdlib.h>

// ?Get_RDTSC_CPU_Speed@@YAHXZ
int Get_RDTSC_CPU_Speed(void)
{
	LARGE_INTEGER t0;
	LARGE_INTEGER t1;
	LARGE_INTEGER count_freq;
	DWORD stamp0;
	DWORD stamp1;
	DWORD speed = 0;

	if (QueryPerformanceFrequency(&count_freq))
	{
		QueryPerformanceCounter(&t0);
		__asm
		{
			pushad
			cpuid
			rdtsc
			mov stamp0, eax
			popad
		}

		DWORD now = timeGetTime();
		DWORD until = now + 5;
		while (now < until)
		{
			now = timeGetTime();
		}

		QueryPerformanceCounter(&t1);
		__asm
		{
			pushad
			cpuid
			rdtsc
			mov stamp1, eax
			popad
		}

		DWORD cycles = stamp1 - stamp0;
		DWORD ticks = t1.LowPart - t0.LowPart;
		double measured = (double)cycles;
		measured *= (double)count_freq.LowPart;
		measured /= (double)ticks;
		speed = (int)(measured * 0.000001);
	}

	DWORD rounded_200 = ((3 * speed + 100) / 200) * 200;
	rounded_200 = rounded_200 / 3;
	DWORD rounded_50 = ((speed + 25) / 50) * 50;
	if ((DWORD)abs((int)(rounded_50 - speed)) < (DWORD)abs((int)(rounded_200 - speed)))
		return rounded_50;
	if (rounded_200 == 666)
		return 667;
	return rounded_200;
}
