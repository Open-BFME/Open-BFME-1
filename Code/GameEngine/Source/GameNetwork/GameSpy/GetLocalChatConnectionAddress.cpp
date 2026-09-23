// ?GetLocalChatConnectionAddress@@YA_NVAsciiString@@GAAI@Z
// partial score=1.0 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x00639E50, 1100 bytes (1078 bytes of code, a 2-byte pad, and the
// five-entry switch table at +0x438): BFME's GetLocalChatConnectionAddress,
// the ZH GameSpyGameInfo.cpp helper.  Identity: the "inetmib1.dll",
// "snmpapi.dll" and four SnmpExtension/SnmpUtilMem GetProcAddress literals,
// the SNMP tcpConnTable walk and the ConnInfoStruct vector (push_back at
// 0x00639DF0) are the ZH body line for line.
//
// BFME differences from ZH, all read from the retail bytes: no DEBUG_LOG, the
// first query is SNMP_PDU_GET and every later one SNMP_PDU_GETNEXT, the bind
// is reached through bind_list_ptr->list (reloaded after every call), the OID
// buffer is allocated into bind->name.ids, and it is freed first.  The
// AsciiString is BFME's (8-byte header), not the ZH headers', which is why
// this cannot live in StagingRoomGameInfo.cpp.
//
// ONE PIN MISSING: the connection vector's destructor
// ??1?$vector@UtConnInfoStruct@@V?$allocator@UtConnInfoStruct@@@_STL@@@_STL@@QAE@XZ
// has no ledger or symbols.csv name.  Retail calls it at 0x00007BDF (ILT to
// 0x00638F30, ledger ?clear@Rva00638F30@@QAEXXZ); the EH unwind for state 1
// at 0x00C416A8 does `lea ecx,[ebp-0x40]; jmp 0x00007BDF` on the same vector.

#include <string.h>
#include <vector>
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef unsigned char BYTE;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef int BOOL;
typedef long AsnInteger32;
typedef long AsnInteger;
typedef void *HANDLE;
typedef void *LPVOID;
typedef struct HINSTANCE__ *HINSTANCE;
typedef int (__stdcall *FARPROC)();

#define NULL 0
#define SNMP_PDU_GET 0xA0
#define SNMP_PDU_GETNEXT 0xA1
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

struct hostent
{
	char *h_name;
	char **h_aliases;
	short h_addrtype;
	short h_length;
	char **h_addr_list;
};

extern "C" __declspec(dllimport) struct hostent * __stdcall gethostbyname(const char *name);
extern "C" __declspec(dllimport) unsigned long __stdcall htonl(unsigned long hostlong);
extern "C" __declspec(dllimport) HINSTANCE __stdcall LoadLibraryA(const char *name);
extern "C" __declspec(dllimport) BOOL __stdcall FreeLibrary(HINSTANCE module);
extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(HINSTANCE module, const char *name);
extern "C" __declspec(dllimport) DWORD __stdcall GetTickCount(void);

typedef struct {
	UINT idLength;
	UINT *ids;
} AsnObjectIdentifier;

typedef struct {
	BYTE *stream;
	UINT length;
	BOOL dynamic;
} AsnOctetString;

typedef struct {
	BYTE asnType;
	union {
		AsnInteger32 number;
		AsnOctetString address;
	} asnValue;
} AsnAny;

typedef struct {
	AsnObjectIdentifier name;
	AsnAny value;
} SnmpVarBind;

typedef struct {
	SnmpVarBind *list;
	UINT len;
} SnmpVarBindList;

typedef SnmpVarBind RFC1157VarBind;
typedef SnmpVarBindList RFC1157VarBindList;

BOOL (__stdcall *SnmpExtensionInitPtr)(DWORD dwUpTimeReference, HANDLE *phSubagentTrapEvent, AsnObjectIdentifier *pFirstSupportedRegion);
BOOL (__stdcall *SnmpExtensionQueryPtr)(BYTE bPduType, RFC1157VarBindList *pVarBindList, AsnInteger32 *pErrorStatus, AsnInteger32 *pErrorIndex);
LPVOID (__stdcall *SnmpUtilMemAllocPtr)(DWORD bytes);
void (__stdcall *SnmpUtilMemFreePtr)(LPVOID pMem);

typedef struct tConnInfoStruct {
	unsigned int State;
	unsigned long LocalIP;
	unsigned short LocalPort;
	unsigned long RemoteIP;
	unsigned short RemotePort;
} ConnInfoStruct;

static inline const char *rvaText(const AsciiString &name)
{
	const char *data = *(const char * const *)&name;
	return data ? data + 8 : "";
}

Bool GetLocalChatConnectionAddress(AsciiString serverName, UnsignedShort serverPort, UnsignedInt& localIP)
{
	enum {
		CLOSED = 1,
		LISTENING,
		SYN_SENT,
		SEN_RECEIVED,
		ESTABLISHED,
		FIN_WAIT,
		FIN_WAIT2,
		CLOSE_WAIT,
		LAST_ACK,
		CLOSING,
		TIME_WAIT,
		DELETE_TCB
	};

	enum {
		tcpConnState = 1,
		tcpConnLocalAddress,
		tcpConnLocalPort,
		tcpConnRemAddress,
		tcpConnRemPort
	};

	unsigned long serverAddress;
	unsigned long remoteAddress;
	HANDLE trap_handle;
	AsnObjectIdentifier first_supported_region;
	std::vector<ConnInfoStruct> connectionVector;
	int last_field;
	int index;
	AsnInteger error_status;
	AsnInteger error_index;
	int conn_entry_type;
	Bool found;

	struct hostent *host_info = gethostbyname(rvaText(serverName));
	if (!host_info) {
		return(false);
	}

	memcpy(&serverAddress, &host_info->h_addr_list[0][0], 4);
	serverAddress = htonl(serverAddress);

	HINSTANCE mib_ii_dll = LoadLibraryA("inetmib1.dll");
	if (mib_ii_dll == NULL) {
		return(false);
	}

	HINSTANCE snmpapi_dll = LoadLibraryA("snmpapi.dll");
	if (snmpapi_dll == NULL) {
		FreeLibrary(mib_ii_dll);
		return(false);
	}

	SnmpExtensionInitPtr = (int (__stdcall *)(unsigned long,void ** ,AsnObjectIdentifier *)) GetProcAddress(mib_ii_dll, "SnmpExtensionInit");
	SnmpExtensionQueryPtr = (int (__stdcall *)(unsigned char,SnmpVarBindList *,long *,long *)) GetProcAddress(mib_ii_dll, "SnmpExtensionQuery");
	SnmpUtilMemAllocPtr = (void *(__stdcall *)(unsigned long)) GetProcAddress(snmpapi_dll, "SnmpUtilMemAlloc");
	SnmpUtilMemFreePtr = (void (__stdcall *)(void *)) GetProcAddress(snmpapi_dll, "SnmpUtilMemFree");
	if (SnmpExtensionInitPtr == NULL || SnmpExtensionQueryPtr == NULL || SnmpUtilMemAllocPtr == NULL || SnmpUtilMemFreePtr == NULL) {
		FreeLibrary(snmpapi_dll);
		FreeLibrary(mib_ii_dll);
		return(false);
	}

	RFC1157VarBindList *bind_list_ptr = (RFC1157VarBindList *) SnmpUtilMemAllocPtr(sizeof(RFC1157VarBindList));
	bind_list_ptr->list = (RFC1157VarBind *) SnmpUtilMemAllocPtr(sizeof(RFC1157VarBind));
	bind_list_ptr->len = 1;

	int ok = SnmpExtensionInitPtr(GetTickCount(), &trap_handle, &first_supported_region);
	if (!ok) {
		SnmpUtilMemFreePtr(bind_list_ptr->list);
		SnmpUtilMemFreePtr(bind_list_ptr);
		FreeLibrary(snmpapi_dll);
		FreeLibrary(mib_ii_dll);
		return(false);
	}

	unsigned int mib_ii_name[] = {1,3,6,1,2,1,6,13,1,1};
	bind_list_ptr->list->name.idLength = ARRAY_SIZE(mib_ii_name);
	bind_list_ptr->list->name.ids = (unsigned int *) SnmpUtilMemAllocPtr(sizeof(mib_ii_name));
	memcpy(bind_list_ptr->list->name.ids, mib_ii_name, sizeof(mib_ii_name));

	last_field = 1;
	index = 0;
	BYTE pdu_type = SNMP_PDU_GET;

	while (true) {
		if (!SnmpExtensionQueryPtr(pdu_type, bind_list_ptr, &error_status, &error_index)) {
			SnmpUtilMemFreePtr(bind_list_ptr->list->name.ids);
			SnmpUtilMemFreePtr(bind_list_ptr->list);
			SnmpUtilMemFreePtr(bind_list_ptr);
			FreeLibrary(snmpapi_dll);
			FreeLibrary(mib_ii_dll);
			return(false);
		}

		if (bind_list_ptr->list->name.idLength < ARRAY_SIZE(mib_ii_name)) {
			break;
		}

		if (pdu_type == SNMP_PDU_GET) {
			pdu_type = SNMP_PDU_GETNEXT;
		}

		conn_entry_type = bind_list_ptr->list->name.ids[ARRAY_SIZE(mib_ii_name) - 1];

		if (last_field != conn_entry_type) {
			index = 0;
			last_field = conn_entry_type;
		}

		switch (conn_entry_type) {
			case tcpConnState:
			{
				ConnInfoStruct new_conn;
				new_conn.State = bind_list_ptr->list->value.asnValue.number;
				connectionVector.push_back(new_conn);
				break;
			}

			case tcpConnLocalAddress:
				connectionVector[index].LocalIP = *((unsigned long*)bind_list_ptr->list->value.asnValue.address.stream);
				index++;
				break;

			case tcpConnLocalPort:
				connectionVector[index].LocalPort = bind_list_ptr->list->value.asnValue.number;
				index++;
				break;

			case tcpConnRemAddress:
				connectionVector[index].RemoteIP = *((unsigned long*)bind_list_ptr->list->value.asnValue.address.stream);
				index++;
				break;

			case tcpConnRemPort:
				connectionVector[index].RemotePort = bind_list_ptr->list->value.asnValue.number;
				index++;
				break;
		}
	}

	SnmpUtilMemFreePtr(bind_list_ptr->list->name.ids);
	SnmpUtilMemFreePtr(bind_list_ptr->list);
	SnmpUtilMemFreePtr(bind_list_ptr);

	found = false;
	for (Int i=0; i<connectionVector.size(); ++i) {
		ConnInfoStruct connection = connectionVector[i];

		remoteAddress = htonl(connection.RemoteIP);

		if (!found && memcmp(&remoteAddress, &serverAddress, 4) == 0) {
			if (serverPort == 0 || serverPort == connection.RemotePort) {
				if (connection.State == ESTABLISHED) {
					localIP = connection.LocalIP;
					found = true;
				}
			}
		}
	}

	FreeLibrary(snmpapi_dll);
	FreeLibrary(mib_ii_dll);
	return(found);
}

