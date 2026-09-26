// ?d_007f65e0@@YAXXZ
// partial score=0.96 date=2026-09-26
// cl: /O2 /GS
class Rva007E8810Message {
public:
 bool hasError(); int getError();
 char m_head[0x28]; int m_txn;
};
class Rva007FBC60Game {
public:
 Rva007FBC60Game(Rva007E8810Message *msg);
 int m_lid; int m_gid; Rva007E8810Message *m_msg;
 int m_ap; int m_jp; int m_qp; int m_mp; int m_p; int m_nf;
 bool m_f; bool m_pw; char m_n[0x80]; char m_hn[0x80];
 __int64 m_hu; char m_v[0x40]; char m_i[0x20];
 char m_platform[0x20]; int m_join;
};
struct Rva00802A90Query;
class Rva00802A90Owner { public: bool go(Rva00802A90Query *, int, int); };
class Rva007F65E0Listener {
public:
 virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
 virtual void v04(); virtual void onLobbyCounts(int, int); virtual void v06();
 virtual void notify(int, int, int);
};
class Rva007F65E0Owner {
public:
 virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
 virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
 virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
 virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
 virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
 virtual void v20(); virtual Rva00802A90Owner *findGameLobby(int lid);
 void handleGameLobbyReply(Rva007E8810Message *msg, int flag);
private:
 char m_pad000[0x18]; Rva007F65E0Listener *m_listener;
};
void Rva007F65E0Owner::handleGameLobbyReply(Rva007E8810Message *msg, int flag)
{
 Rva007FBC60Game game(msg);
 bool done = false;
 volatile int gid = game.m_gid;
 int lid = game.m_lid;
 if (msg->hasError())
  m_listener->notify(lid, gid, msg->getError());
 if (Rva00802A90Owner *lobby = findGameLobby(lid)) {
  msg = (Rva007E8810Message *)msg->m_txn;
  done = lobby->go((Rva00802A90Query *)&game, flag, (int)msg);
 }
 m_listener->notify(lid, gid, 0);
 if (done) m_listener->onLobbyCounts(lid, 0);
}
