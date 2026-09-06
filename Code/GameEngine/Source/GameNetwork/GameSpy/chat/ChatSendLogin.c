// cl: /DNDEBUG /MD -Ireference/shims/gamespy
// GameSpy Chat SDK login-message selection; retail RVA008602B0.
#include <string.h>
typedef void *CHAT;
typedef struct ciConnection {
 unsigned char beforeSocket[0x1c];
 unsigned char chatSocket[4];
 unsigned char beforeNamespace[0x4ac - 0x20];
 int namespaceID;
 char email[0x40];
 char profilenick[0x20];
 char uniquenick[0x40];
 char password[0x20];
 char authtoken[0x100];
 char partnerchallenge[0x100];
 unsigned char beforeLoginType[0x8a8 - 0x770];
 int loginType;
} ciConnection;
void ciSocketSendf(void *socket, const char *format, ...);
void MD5Digest(unsigned char *input, unsigned int length, char output[33]);
void ciSendLogin(CHAT chat)
{
 char passwordHash[33];
 ciConnection *connection = (ciConnection *)chat;
 if (connection->loginType == 3) {
  ciSocketSendf(&connection->chatSocket, "LOGINPREAUTH %s %s", connection->authtoken, connection->partnerchallenge);
  return;
 }
 MD5Digest((unsigned char *)connection->password, strlen(connection->password), passwordHash);
 if (connection->loginType == 1) {
  ciSocketSendf(&connection->chatSocket, "LOGIN %d %s %s", connection->namespaceID, connection->uniquenick, passwordHash);
 } else if (connection->loginType == 2) {
  ciSocketSendf(&connection->chatSocket, "LOGIN %d * %s :%s@%s", connection->namespaceID, passwordHash, connection->profilenick, connection->email);
 }
}
