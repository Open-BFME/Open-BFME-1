// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Oy
//
// The GameSpy QR NAT-negotiate callback is a release no-op in Zero Hour.
// Thread_Function at 0x0064FB90 stores this callback at PEERCallbacks +0x68
// (the direct assignment is at 0x0064FCFC).  Its complete retail body is the
// single RET at 0x00642E00; the next registered no-op begins at 0x00642E10.
// This TU keeps the established Peer callback ABI without changing headers.

typedef void *PEER;

void QRNatNegotiateCallback(PEER peer, int cookie, void *param)
{
}
