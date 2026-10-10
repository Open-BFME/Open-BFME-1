// cl: /DNDEBUG /MD /GX

void j_0001e6aa();
void j_00006767();
void j_0001cd87();
void j_0002f676();
// Retail four-slot pointer table at VA0111A5A0; targets are exact ILT rows.
extern "C" const void *g_Va0111A5A0[4] = {
    reinterpret_cast<const void *>(&j_0001e6aa),
    reinterpret_cast<const void *>(&j_00006767),
    reinterpret_cast<const void *>(&j_0001cd87),
    reinterpret_cast<const void *>(&j_0002f676),
};
extern "C" const void *bfmeVftNetCommandMsg[];
#pragma comment(linker, "/alternatename:_bfmeVftNetCommandMsg=??_7NetCommandMsg@@6B@")

class BFMENetRequestPlayerLeaveCommandMsg
{
public:
	void *construct();
	void destruct();
	void setRequestedPlayerID(int playerID);
	int getRequestedPlayerID();
};

// BFME command type 7 is NETCOMMANDTYPE_REQUESTPLAYERLEAVE, not ZH run-ahead.
void *BFMENetRequestPlayerLeaveCommandMsg::construct()
{
	char *base = reinterpret_cast<char *>(this);
	*reinterpret_cast<unsigned int *>(base + 0x08) = 0xffffffff;
	*reinterpret_cast<unsigned short *>(base + 0x10) = 0;
	*reinterpret_cast<unsigned int *>(base + 0x0c) = 0;
	*reinterpret_cast<unsigned int *>(base + 0x04) = 0;
	*reinterpret_cast<unsigned int *>(base + 0x18) = 1;
	*reinterpret_cast<unsigned int *>(base) = reinterpret_cast<unsigned int>(g_Va0111A5A0);
	*reinterpret_cast<unsigned int *>(base + 0x14) = 7;
	*reinterpret_cast<unsigned int *>(base + 0x1c) = 0xffffffff;
	return this;
}

void BFMENetRequestPlayerLeaveCommandMsg::destruct()
{
	*reinterpret_cast<unsigned int *>(this) =
		reinterpret_cast<unsigned int>(bfmeVftNetCommandMsg);
}

void BFMENetRequestPlayerLeaveCommandMsg::setRequestedPlayerID(int playerID)
{
	*reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x1c) = playerID;
}

int BFMENetRequestPlayerLeaveCommandMsg::getRequestedPlayerID()
{
	return *reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x1c);
}
