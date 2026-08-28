// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// ResolveIP -- the Zero Hour GameNetwork/networkutil.cpp body, unchanged.
// Reached through the ILT thunk at 0x0003DC08 from LANAPI::SetLocalIP.
//
// What it needs that the vendored tree cannot give is BFME's AsciiString with
// StringBase<char>'s accessors VISIBLE INLINE: retail inlines getLength(),
// getCharAt() and str() here (movzx from Header+4, movsx from Header+8), while
// Code/Libraries/.../string_base.h only declares them and string_base.cpp holds
// the out-of-line bodies.  The slice below is that header's own layout --
// Header { int ref_count; unsigned short length; unsigned short capacity;
// char data[1]; } -- with string_base.cpp's own accessor bodies inlined, and
// nothing else.  ~AsciiString stays undefined so the call goes out of line to
// the retail body, as it does here.
struct hostent
{
	char *h_name;
	char **h_aliases;
	short h_addrtype;
	short h_length;
	char **h_addr_list;
};

struct in_addr
{
	unsigned long s_addr;
};

extern "C" __declspec(dllimport) int __cdecl isdigit(int c);
extern "C" __declspec(dllimport) unsigned long __stdcall inet_addr(const char *cp);
extern "C" __declspec(dllimport) unsigned long __stdcall ntohl(unsigned long netlong);
extern "C" __declspec(dllimport) struct hostent * __stdcall gethostbyname(const char *name);

typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

	int getLength() const { return m_data ? m_data->length : 0; }
	const char *str() const { return m_data ? &m_data->data[0] : (const char *)""; }
	char getCharAt(int index) const { return m_data ? m_data->data[index] : 0; }

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	Header *m_data;
};

/**
 * ResolveIP turns a string ("games2.westwood.com", or "192.168.0.1") into
 * a 32-bit unsigned integer.
 */
UnsignedInt ResolveIP(AsciiString host)
{
  struct hostent *hostStruct;
  struct in_addr *hostNode;

  if (host.getLength() == 0)
  {
	  return 0;
  }

  // String such as "127.0.0.1"
  if (isdigit(host.getCharAt(0)))
  {
    return ( ntohl(inet_addr(host.str())) );
  }

  // String such as "localhost"
  hostStruct = gethostbyname(host.str());
  if (hostStruct == 0)
  {
	  return 0;
  }
  hostNode = (struct in_addr *) hostStruct->h_addr_list[0];
  return ( ntohl(hostNode->s_addr) );
}
