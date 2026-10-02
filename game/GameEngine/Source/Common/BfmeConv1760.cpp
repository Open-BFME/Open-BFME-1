class BfmeEntryBV
{
public:
	unsigned char m_bfmeHeadBV[8];
	void *m_bfmeKeyBV;
	int m_bfmeKindBV;
	unsigned short m_bfmeIdBV;
	unsigned char m_bfmePadBV[2];
	int m_bfmeTagBV;
};

class BfmeNodeBV
{
public:
	BfmeEntryBV *m_bfmeEntryBV;
	BfmeNodeBV *m_bfmeNextBV;
};

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = 0,
	NETCOMMANDTYPE_ACKBOTH,
	NETCOMMANDTYPE_ACKSTAGE1,
	NETCOMMANDTYPE_FRAMEINFO,
	NETCOMMANDTYPE_GAMECOMMAND,
	NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY,
	NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY,
	NETCOMMANDTYPE_REQUESTPLAYERLEAVE,
	NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME,
	NETCOMMANDTYPE_REQUESTFRAMEDATA,
	NETCOMMANDTYPE_PLAYERLEAVE,
	NETCOMMANDTYPE_DESTROYPLAYER,
	NETCOMMANDTYPE_KEEPALIVE,
	NETCOMMANDTYPE_DISCONNECTCHAT,
	NETCOMMANDTYPE_CHAT,
	NETCOMMANDTYPE_PROGRESS,
	NETCOMMANDTYPE_LOADCOMPLETE,
	NETCOMMANDTYPE_TIMEOUTSTART,
	NETCOMMANDTYPE_WRAPPER,
	NETCOMMANDTYPE_FILE,
	NETCOMMANDTYPE_FILEANNOUNCE,
	NETCOMMANDTYPE_FILEPROGRESS,
	NETCOMMANDTYPE_UNUSED22,
	NETCOMMANDTYPE_UNUSED23,
	NETCOMMANDTYPE_DISCONNECTKEEPALIVE,
	NETCOMMANDTYPE_DISCONNECTPLAYER,
	NETCOMMANDTYPE_DISCONNECTVOTE,
	NETCOMMANDTYPE_DISCONNECTFRAME,
	NETCOMMANDTYPE_DISCONNECTSCREENOFF
};

int DoesCommandRequireACommandID(NetCommandType type);

class BfmeOwnBV
{
public:
	BfmeNodeBV *bfmeFindBV(unsigned short id, unsigned char kind, void *key);

	unsigned char m_bfmeHeadBV[4];
	BfmeNodeBV *m_bfmeListBV;
};

BfmeNodeBV *BfmeOwnBV::bfmeFindBV(unsigned short id, unsigned char kind, void *key)
{
	for (BfmeNodeBV *node = m_bfmeListBV; node != 0; node = node->m_bfmeNextBV)
	{
		int tag = node->m_bfmeEntryBV->m_bfmeTagBV;

		if (!(char)DoesCommandRequireACommandID((NetCommandType)tag))
			continue;

		if (node->m_bfmeEntryBV->m_bfmeIdBV != id)
			continue;

		if (node->m_bfmeEntryBV->m_bfmeKindBV != kind)
			continue;

		if (node->m_bfmeEntryBV->m_bfmeKeyBV == key)
			return node;
	}

	return 0;
}
