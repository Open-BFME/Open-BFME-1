// cl: /DNDEBUG /MD /EHsc
// Open-BFME-1: Windows 9x fallback installed by the matched wide API thunk at
// 0x0005EB60.  The implementation is the VS2003 ATL CompareStringWFake body:
// its conversion macros use a guarded stack allocation below 1024 bytes and
// a linked heap-buffer manager otherwise.

#include <malloc.h>
#include <stdlib.h>

typedef unsigned short WCHAR;
typedef unsigned long DWORD;
typedef unsigned long LCID;
typedef unsigned int UINT;

typedef UINT (__stdcall *W3AtlAcpProc)(void);

extern "C"
{
	__declspec(dllimport) int __stdcall lstrlenW(const WCHAR *text);
	__declspec(dllimport) int __stdcall CompareStringA(LCID locale, DWORD flags,
		const char *string1, int length1, const char *string2, int length2);
}

namespace ATL
{
	extern W3AtlAcpProc g_pfnGetThreadACP;

	inline UINT __stdcall _AtlGetConversionACP() throw()
	{
		return g_pfnGetThreadACP();
	}

	char *__stdcall AtlW2AHelper(char *destination, const WCHAR *source,
		int destinationLength, UINT codePage) throw();

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

	namespace _ATL_SAFE_ALLOCA_IMPL
	{
		bool __cdecl _AtlVerifyStackAvailable(unsigned long bytes);

		template <class Allocator>
		class CAtlSafeAllocBufferManager
		{
		private:
			struct CAtlSafeAllocBufferNode
			{
				CAtlSafeAllocBufferNode *m_pNext;
				unsigned char m_pad[4];

				void *GetData()
				{
					return this + 1;
				}
			};

			CAtlSafeAllocBufferNode *m_pHead;

		public:
			CAtlSafeAllocBufferManager() : m_pHead(0) {}

			void *Allocate(size_t bytes)
			{
				CAtlSafeAllocBufferNode *node =
					(CAtlSafeAllocBufferNode *)Allocator::Allocate(
						bytes + sizeof(CAtlSafeAllocBufferNode));
				if (node == 0)
					return 0;

				node->m_pNext = m_pHead;
				m_pHead = node;
				return node->GetData();
			}

			~CAtlSafeAllocBufferManager()
			{
				while (m_pHead != 0)
				{
					CAtlSafeAllocBufferNode *node = m_pHead;
					m_pHead = m_pHead->m_pNext;
					Allocator::Free(node);
				}
			}
		};
	}
}

#define W3_SAFE_ALLOCA(manager, bytes) \
	(((bytes) <= 1024 && \
	ATL::_ATL_SAFE_ALLOCA_IMPL::_AtlVerifyStackAvailable(bytes)) \
	? _alloca(bytes) : (manager).Allocate(bytes))

#define W3_USES_CONVERSION_EX \
	int _convert_ex; (_convert_ex); \
	UINT _acp_ex = ATL::_AtlGetConversionACP(); (_acp_ex); \
	const WCHAR *_lpw_ex; (_lpw_ex); \
	const char *_lpa_ex; (_lpa_ex); \
	ATL::_ATL_SAFE_ALLOCA_IMPL::CAtlSafeAllocBufferManager<ATL::CCRTAllocator> \
		_AtlSafeAllocaManager

#define W3_W2A_EX(text) \
	(((_lpw_ex = (text)) == 0) ? 0 : \
	(_convert_ex = (lstrlenW(_lpw_ex) + 1) * sizeof(WCHAR), \
	ATL::AtlW2AHelper( \
		(char *)W3_SAFE_ALLOCA(_AtlSafeAllocaManager, _convert_ex), \
		_lpw_ex, _convert_ex, _acp_ex)))

namespace ATL
{
int __stdcall CompareStringWFake(LCID locale, DWORD flags,
	const WCHAR *string1, int length1, const WCHAR *string2, int length2)
{
	W3_USES_CONVERSION_EX;

	const char *ansi1 = 0;
	if (string1 != 0)
	{
		ansi1 = W3_W2A_EX(string1);
		if (ansi1 == 0)
			ATL::AtlThrow(0x8007000E);
	}

	const char *ansi2 = 0;
	if (string2 != 0)
	{
		ansi2 = W3_W2A_EX(string2);
		if (ansi2 == 0)
			ATL::AtlThrow(0x8007000E);
	}

	return CompareStringA(locale, flags, ansi1, length1, ansi2, length2);
}
}
