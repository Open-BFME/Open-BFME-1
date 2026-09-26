// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <string>
#include <stdlib.h>

// BFME's persistent-storage login worker; source provenance and its corrected
// member ABI are documented in targets/game/reverse/identity_evidence/006549c0-storage-login.md.
class PSThreadClass {
private:
    bool tryLogin(int id, std::string nick, std::string password, std::string email);
    char rvaPrefix00[0x50];
    bool m_loginOK;
    bool m_doneTryingToLogin;
};
extern "C" {
void GenerateAuthA(char *, char *, char *);
char *GetChallenge(void *);
int IsStatsConnected();
int PersistThink();
}
char *BFMEDuplicateString(const char *) throw();
class Rva006549C0BuddyView {public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();virtual void slot10();virtual void slot14();virtual void slot18();virtual void slot1C();virtual void slot20();virtual void slot24();virtual void slot28();
 virtual const char *slot2C();virtual const char *slot30();
};
extern Rva006549C0BuddyView *Rva012F71B4Buddy;
extern "C" void PreAuthenticatePlayerPartner(int,char*,char*,void(__cdecl*)(int,int,int,char*,void*),void*);
// Existing opaque symbol: independent retail body at 006517E0 is a cdecl
// callback with five arguments; argument 5 is the thread, argument 3 is status.
void d_006517e0();
bool PSThreadClass::tryLogin(int id,std::string nick,std::string password,std::string email)
{
 char validate[33];
 m_loginOK=false;m_doneTryingToLogin=false;
 char *token=BFMEDuplicateString(Rva012F71B4Buddy->slot2C());
 char *challenge=BFMEDuplicateString(Rva012F71B4Buddy->slot30());
 GenerateAuthA(GetChallenge(0),challenge,validate);
 PreAuthenticatePlayerPartner(id,token,validate,(void(__cdecl*)(int,int,int,char*,void*))d_006517e0,this);
 free(token);free(challenge);
 while(!m_doneTryingToLogin && IsStatsConnected())PersistThink();
 return m_loginOK;
}
