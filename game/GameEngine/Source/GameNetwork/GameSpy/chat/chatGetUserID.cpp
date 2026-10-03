// cl: /O2 /MD
// Retail RVA 0x008606F0, 11 bytes. The matched peerGetUserID at 0x00857480
// forwards its chat connection here with a direct E9 at 0x00857494 and names
// chatGetUserID in peerMainBlockingOperations.cpp. Retail reads the signed
// user ID at connection+0x8AC and returns before INT3 at 0x008606FB.
// Keep the local ABI view opaque: this does not declare the complete connection.
extern "C" int chatGetUserID(void *chat)
{
    return *(const int *)((const char *)chat + 0x8ac);
}
