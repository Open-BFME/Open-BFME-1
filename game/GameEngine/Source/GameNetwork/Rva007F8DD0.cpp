// cl: /O2 /MD
// Retain the existing callee ABI view and result conversion used by the
// matched TID/PID caller008037A0; no alternate getter identity is introduced.
class BfmeThingRF
{
public:
    void *bfmeGoRF(void *key, void *defaultValue);
};
// Retail .data VA 0x012C3B28 holds the pointer to "errorCode" (VA 0x0112B948).
const char *g_va012C3B28 = "errorCode";
class Rva007F8DD0
{
public:
    int method(BfmeThingRF *message);
};
int Rva007F8DD0::method(BfmeThingRF *message)
{
    return (int)(long)message->bfmeGoRF((void *)g_va012C3B28, 0);
}
