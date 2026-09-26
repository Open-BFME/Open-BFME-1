#pragma once
// <winsock.h> stand-in for the vendored GameSpy SDK (C sources). Layouts and the
// FD_* macro expansions are what drive codegen here, so they mirror the real
// PlatformSDK exactly; see windows.h next door for how that is proven.
#ifndef GAMESPY_WINSOCK_SHIM_H
#define GAMESPY_WINSOCK_SHIM_H

#include <windows.h>

typedef unsigned int SOCKET;
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;

struct in_addr {
	union {
		struct { u_char s_b1, s_b2, s_b3, s_b4; } S_un_b;
		struct { u_short s_w1, s_w2; } S_un_w;
		u_long S_addr;
	} S_un;
#define s_addr S_un.S_addr
};
typedef struct in_addr IN_ADDR, *PIN_ADDR, *LPIN_ADDR;

struct sockaddr {
	u_short sa_family;
	char sa_data[14];
};
typedef struct sockaddr SOCKADDR, *PSOCKADDR, *LPSOCKADDR;

struct sockaddr_in {
	short sin_family;
	u_short sin_port;
	struct in_addr sin_addr;
	char sin_zero[8];
};
typedef struct sockaddr_in SOCKADDR_IN, *PSOCKADDR_IN, *LPSOCKADDR_IN;

struct hostent {
	char *h_name;
	char **h_aliases;
	short h_addrtype;
	short h_length;
	char **h_addr_list;
#define h_addr h_addr_list[0]
};
typedef struct hostent HOSTENT, *PHOSTENT, *LPHOSTENT;

struct servent {
	char *s_name;
	char **s_aliases;
	short s_port;
	char *s_proto;
};

typedef struct WSAData {
	WORD wVersion;
	WORD wHighVersion;
	char szDescription[257];
	char szSystemStatus[129];
	unsigned short iMaxSockets;
	unsigned short iMaxUdpDg;
	char *lpVendorInfo;
} WSADATA, *LPWSADATA;

#define MAKEWORD(a, b) ((WORD)(((BYTE)(a)) | (((WORD)((BYTE)(b))) << 8)))

#define AF_INET 2
#define AF_UNSPEC 0
#define PF_INET AF_INET
#define SOCK_STREAM 1
#define SOCK_DGRAM 2
#define IPPROTO_IP 0
#define IPPROTO_TCP 6
#define IPPROTO_UDP 17
#define SOL_SOCKET 0xffff
#define SO_DEBUG 0x0001
#define SO_REUSEADDR 0x0004
#define SO_KEEPALIVE 0x0008
#define SO_DONTROUTE 0x0010
#define SO_BROADCAST 0x0020
#define SO_LINGER 0x0080
#define SO_SNDBUF 0x1001
#define SO_RCVBUF 0x1002
#define SO_ERROR 0x1007
#define TCP_NODELAY 0x0001
#define MSG_PEEK 0x2
#define SD_RECEIVE 0x00
#define SD_SEND 0x01
#define SD_BOTH 0x02
#define FIONBIO 0x8004667e
#define FIONREAD 0x4004667f
#define INADDR_ANY 0x00000000
#define INADDR_LOOPBACK 0x7f000001
#define INADDR_NONE 0xffffffff
#define INADDR_BROADCAST 0xffffffff
#define INVALID_SOCKET ((SOCKET)~0)
#define SOCKET_ERROR (-1)

#define WSABASEERR 10000
#define WSAEINTR 10004
#define WSAEBADF 10009
#define WSAEACCES 10013
#define WSAEFAULT 10014
#define WSAEINVAL 10022
#define WSAEMFILE 10024
#define WSAEWOULDBLOCK 10035
#define WSAEINPROGRESS 10036
#define WSAEALREADY 10037
#define WSAENOTSOCK 10038
#define WSAEDESTADDRREQ 10039
#define WSAEMSGSIZE 10040
#define WSAEPROTOTYPE 10041
#define WSAENOPROTOOPT 10042
#define WSAEPROTONOSUPPORT 10043
#define WSAESOCKTNOSUPPORT 10044
#define WSAEOPNOTSUPP 10045
#define WSAEPFNOSUPPORT 10046
#define WSAEAFNOSUPPORT 10047
#define WSAEADDRINUSE 10048
#define WSAEADDRNOTAVAIL 10049
#define WSAENETDOWN 10050
#define WSAENETUNREACH 10051
#define WSAENETRESET 10052
#define WSAECONNABORTED 10053
#define WSAECONNRESET 10054
#define WSAENOBUFS 10055
#define WSAEISCONN 10056
#define WSAENOTCONN 10057
#define WSAESHUTDOWN 10058
#define WSAETOOMANYREFS 10059
#define WSAETIMEDOUT 10060
#define WSAECONNREFUSED 10061
#define WSAELOOP 10062
#define WSAENAMETOOLONG 10063
#define WSAEHOSTDOWN 10064
#define WSAEHOSTUNREACH 10065
#define WSAENOTEMPTY 10066
#define WSAEPROCLIM 10067
#define WSAEUSERS 10068
#define WSAEDQUOT 10069
#define WSAESTALE 10070
#define WSAEREMOTE 10071
#define WSAEDISCON 10101
#define WSASYSNOTREADY 10091
#define WSAVERNOTSUPPORTED 10092
#define WSANOTINITIALISED 10093
#define WSAHOST_NOT_FOUND 11001
#define WSATRY_AGAIN 11002
#define WSANO_RECOVERY 11003
#define WSANO_DATA 11004
#define h_errno WSAGetLastError()

#define FD_SETSIZE 64
typedef struct fd_set {
	u_int fd_count;
	SOCKET fd_array[FD_SETSIZE];
} fd_set;

struct timeval {
	long tv_sec;
	long tv_usec;
};

#ifdef __cplusplus
extern "C" {
#endif

int __stdcall __WSAFDIsSet(SOCKET, fd_set *);

#define FD_ZERO(set) (((fd_set *)(set))->fd_count = 0)
#define FD_SET(fd, set) do { \
	u_int __i; \
	for (__i = 0; __i < ((fd_set *)(set))->fd_count; __i++) { \
		if (((fd_set *)(set))->fd_array[__i] == (fd)) break; \
	} \
	if (__i == ((fd_set *)(set))->fd_count) { \
		if (((fd_set *)(set))->fd_count < FD_SETSIZE) { \
			((fd_set *)(set))->fd_array[__i] = (fd); \
			((fd_set *)(set))->fd_count++; \
		} \
	} \
} while (0)
#define FD_ISSET(fd, set) __WSAFDIsSet((SOCKET)(fd), (fd_set *)(set))

int __stdcall select(int, fd_set *, fd_set *, fd_set *, const struct timeval *);
int __stdcall listen(SOCKET, int);
SOCKET __stdcall accept(SOCKET, struct sockaddr *, int *);
int __stdcall recv(SOCKET, char *, int, int);
int __stdcall getpeername(SOCKET, struct sockaddr *, int *);
int __stdcall WSAStartup(WORD, LPWSADATA);
int __stdcall WSACleanup(void);
int __stdcall WSAGetLastError(void);
void __stdcall WSASetLastError(int);
SOCKET __stdcall socket(int, int, int);
int __stdcall closesocket(SOCKET);
int __stdcall shutdown(SOCKET, int);
int __stdcall bind(SOCKET, const struct sockaddr *, int);
int __stdcall connect(SOCKET, const struct sockaddr *, int);
int __stdcall getsockname(SOCKET, struct sockaddr *, int *);
int __stdcall ioctlsocket(SOCKET, long, u_long *);
int __stdcall send(SOCKET, const char *, int, int);
int __stdcall sendto(SOCKET, const char *, int, int, const struct sockaddr *, int);
int __stdcall recvfrom(SOCKET, char *, int, int, struct sockaddr *, int *);
int __stdcall setsockopt(SOCKET, int, int, const char *, int);
int __stdcall getsockopt(SOCKET, int, int, char *, int *);
u_short __stdcall htons(u_short);
u_short __stdcall ntohs(u_short);
u_long __stdcall htonl(u_long);
u_long __stdcall ntohl(u_long);
u_long __stdcall inet_addr(const char *);
char *__stdcall inet_ntoa(struct in_addr);
struct hostent *__stdcall gethostbyname(const char *);
struct hostent *__stdcall gethostbyaddr(const char *, int, int);
struct servent *__stdcall getservbyname(const char *, const char *);
int __stdcall gethostname(char *, int);

#ifdef __cplusplus
}
#endif

#endif
