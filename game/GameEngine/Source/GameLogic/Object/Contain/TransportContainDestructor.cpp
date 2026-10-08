// TransportContain complete destructor at retail 0x0022CC80 (77 bytes).
// ??_GTransportContain (0x0022D0B0) calls it through ILT 0x0003FF49, pinned
// ??1TransportContain@@MAE@XZ (ilt_oracle: MAE exact at 0x0022CC80, UAE
// contradicted). The body re-seats the ten vftables of TransportContain's
// sub-objects in ascending displacement order and tail-jumps to
// ??1OpenContain@@UAE@XZ through ILT 0x00039D6A.
//
// The vftables are named by the decorated symbols dir32_addresses.csv records
// for them; novtable keeps this TU from emitting second copies.

extern "C" const void *__identifier("??_7TransportContain@@6BTransportContainBase@@@")[];
extern "C" const void *__identifier("??_7TransportContain@@6BTransportContainIface1@@@")[];
extern "C" const void *__identifier("??_7TransportContain@@6BTransportContainIface2@@@")[];
extern "C" const void *__identifier("??_7TransportContain@@6BTransportContainIface3@@@")[];
extern "C" const void *__identifier("??_7TransportContain@@6BTransportContainIface4@@@")[];
extern "C" const void *__identifier("??_7TransportContain@@6BTransportContainIface5@@@")[];
extern "C" const void *__identifier("??_7TransportContain@@6BTransportContainIface6@@@")[];
extern "C" const void *__identifier("??_7TransportContain@@6BTransportContainIface7@@@")[];
extern "C" const void *__identifier("??_7TransportContain@@6BTransportContainIface8@@@")[];
extern "C" const void *__identifier("??_7TransportContain@@6BTransportContainIface9@@@")[];

class OpenContain
{
public:
	virtual ~OpenContain();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TransportContain.h
class __declspec(novtable) TransportContain : public OpenContain
{
protected:
	virtual ~TransportContain();
};

#define TRANSPORT_CONTAIN_VPTR(offset, table) \
	(*(const void *volatile *)((unsigned char *)this + (offset)) = (const void *)__identifier(table))

TransportContain::~TransportContain()
{
	TRANSPORT_CONTAIN_VPTR(0x00, "??_7TransportContain@@6BTransportContainBase@@@");
	TRANSPORT_CONTAIN_VPTR(0x0C, "??_7TransportContain@@6BTransportContainIface1@@@");
	TRANSPORT_CONTAIN_VPTR(0x10, "??_7TransportContain@@6BTransportContainIface2@@@");
	TRANSPORT_CONTAIN_VPTR(0x20, "??_7TransportContain@@6BTransportContainIface3@@@");
	TRANSPORT_CONTAIN_VPTR(0x24, "??_7TransportContain@@6BTransportContainIface4@@@");
	TRANSPORT_CONTAIN_VPTR(0x28, "??_7TransportContain@@6BTransportContainIface5@@@");
	TRANSPORT_CONTAIN_VPTR(0x2C, "??_7TransportContain@@6BTransportContainIface6@@@");
	TRANSPORT_CONTAIN_VPTR(0x30, "??_7TransportContain@@6BTransportContainIface7@@@");
	TRANSPORT_CONTAIN_VPTR(0x34, "??_7TransportContain@@6BTransportContainIface8@@@");
	TRANSPORT_CONTAIN_VPTR(0xD4, "??_7TransportContain@@6BTransportContainIface9@@@");
}
