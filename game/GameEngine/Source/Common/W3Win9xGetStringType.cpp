// cl: /DNDEBUG /MD /EHsc
// Open-BFME-1: VS2003 ATL's Windows 9x fallback for GetStringTypeExW.
// The matched selector at 0x0005FA00 installs this routine through the retail
// ILT at 0x000144D4 when GetVersion identifies the Win9x platform family.

#include <malloc.h>
#include <stdlib.h>

typedef unsigned short WCHAR;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned long LCID;
typedef unsigned int UINT;

typedef UINT (__stdcall *W3AtlAcpProc)(void);

extern "C"
{
	__declspec(dllimport) int __stdcall WideCharToMultiByte(UINT codePage,
		DWORD flags, const WCHAR *wide, int wideCount, char *narrow,
		int narrowCount, const char *defaultChar, int *usedDefaultChar);
	__declspec(dllimport) int __stdcall GetStringTypeExA(LCID locale,
		DWORD infoType, const char *source, int count, WORD *charType);
}

namespace ATL
{
	extern W3AtlAcpProc g_pfnGetThreadACP;

	inline UINT __stdcall _AtlGetConversionACP() throw()
	{
		return g_pfnGetThreadACP();
	}

	__declspec(noreturn) void __stdcall AtlThrow(long result);

	class CCRTAllocator
	{
	public:
		static void *Allocate(size_t bytes) throw()
		{
			return malloc(bytes);
		}

		static void Free(void *memory) throw()
		{
			free(memory);
		}
	};

	template <typename T, int FixedBytes = 128, class Allocator = CCRTAllocator>
	class CTempBuffer
	{
	public:
		CTempBuffer() throw() : m_p(0) {}

		~CTempBuffer() throw()
		{
			if (m_p != reinterpret_cast<T *>(m_fixedBuffer))
				FreeHeap();
		}

		operator T *() const throw()
		{
			return m_p;
		}

		T *Allocate(size_t elements) throw(...)
		{
			return AllocateBytes(elements * sizeof(T));
		}

		T *AllocateBytes(size_t bytes)
		{
			if (bytes > FixedBytes)
				AllocateHeap(bytes);
			else
				m_p = reinterpret_cast<T *>(m_fixedBuffer);
			return m_p;
		}

	private:
		__declspec(noinline) void AllocateHeap(size_t bytes)
		{
			T *p = static_cast<T *>(Allocator::Allocate(bytes));
			if (p == 0)
				AtlThrow(0x8007000E);
			m_p = p;
		}

		__declspec(noinline) void FreeHeap() throw()
		{
			Allocator::Free(m_p);
		}

		T *m_p;
		unsigned char m_fixedBuffer[FixedBytes];
	};

	int __stdcall GetStringTypeExWFake(LCID locale, DWORD infoType,
		const WCHAR *source, int count, WORD *charType)
	{
		int narrowCount;
		CTempBuffer<char> narrow;

		narrowCount = WideCharToMultiByte(_AtlGetConversionACP(), 0,
			source, count, 0, 0, 0, 0);
		narrow.Allocate(narrowCount);
		WideCharToMultiByte(_AtlGetConversionACP(), 0, source, count,
			narrow, narrowCount, 0, 0);

		if (count == -1)
			narrowCount = -1;

		return GetStringTypeExA(locale, infoType, narrow, narrowCount,
			charType);
	}
}
