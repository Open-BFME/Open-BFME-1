// cl: /DNDEBUG /MD /EHsc
// Open-BFME-1: VS2003 ATL's Windows 9x fallback for
// GetEnvironmentVariableW.  The matched selector at 0x0005F880 installs this
// routine through the retail ILT at 0x0002BF49 on Win9x.

#include <malloc.h>
#include <stdlib.h>

typedef unsigned short WCHAR;
typedef unsigned long DWORD;
typedef unsigned long ULONG;
typedef unsigned int UINT;

typedef UINT (__stdcall *W3AtlAcpProc)(void);

extern "C"
{
	__declspec(dllimport) int __stdcall lstrlenW(const WCHAR *text);
	__declspec(dllimport) int __stdcall WideCharToMultiByte(UINT codePage,
		DWORD flags, const WCHAR *wide, int wideCount, char *narrow,
		int narrowCount, const char *defaultChar, int *usedDefaultChar);
	__declspec(dllimport) int __stdcall MultiByteToWideChar(UINT codePage,
		DWORD flags, const char *narrow, int narrowCount, WCHAR *wide,
		int wideCount);
	__declspec(dllimport) DWORD __stdcall GetEnvironmentVariableA(
		const char *name, char *buffer, DWORD size);
	__declspec(dllimport) DWORD __stdcall GetLastError(void);
}

namespace ATL
{
	extern W3AtlAcpProc g_pfnGetThreadACP;

	inline UINT __stdcall _AtlGetConversionACP() throw()
	{
		return g_pfnGetThreadACP();
	}

	__declspec(noreturn) void __stdcall AtlThrow(long result);

	__declspec(noinline) __declspec(noreturn) inline void __stdcall
	AtlThrowLastWin32(void)
	{
		DWORD error = GetLastError();
		AtlThrow((long)error <= 0 ? (long)error :
			(long)((error & 0xFFFF) | 0x80070000));
	}

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

	template <int BufferLength = 128>
	class CW2AEX
	{
	public:
		CW2AEX(const WCHAR *source) throw(...) : m_text(m_buffer)
		{
			Init(source, _AtlGetConversionACP());
		}

		~CW2AEX() throw()
		{
			if (m_text != m_buffer)
				free(m_text);
		}

		operator char *() const throw()
		{
			return m_text;
		}

	private:
		void Init(const WCHAR *source, UINT codePage) throw(...)
		{
			if (source == 0)
			{
				m_text = 0;
				return;
			}

			int wideLength = lstrlenW(source) + 1;
			int narrowLength = wideLength * 2;
			if (narrowLength > BufferLength)
			{
				m_text = static_cast<char *>(malloc(narrowLength));
				if (m_text == 0)
					AtlThrow(0x8007000E);
			}

			if (WideCharToMultiByte(codePage, 0, source, wideLength,
				m_text, narrowLength, 0, 0) == 0)
			{
				AtlThrowLastWin32();
			}
		}

		char *m_text;
		char m_buffer[BufferLength];
	};

	typedef CW2AEX<> CW2A;

	DWORD __stdcall GetEnvironmentVariableWFake(const WCHAR *name,
		WCHAR *buffer, DWORD size)
	{
		ULONG narrowSize;
		ULONG wideSize;
		CTempBuffer<char> narrowBuffer;
		CW2A narrowName(name);

		narrowSize = GetEnvironmentVariableA(narrowName, 0, 0);
		if (narrowSize == 0)
			return 0;

		narrowBuffer.Allocate(narrowSize * 2);
		GetEnvironmentVariableA(narrowName, narrowBuffer, narrowSize);

		wideSize = MultiByteToWideChar(_AtlGetConversionACP(), 0,
			narrowBuffer, -1, 0, 0);
		if (size == 0)
			return wideSize;

		MultiByteToWideChar(_AtlGetConversionACP(), 0, narrowBuffer, -1,
			buffer, wideSize);
		return wideSize;
	}
}
