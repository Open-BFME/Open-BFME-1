// _ciApplyChangesToMode
// partial score=0.84 date=2026-09-01
// GameSpy Chat SDK -- chatHandlers.c, 2007 release.

typedef int CHATBool;

enum
{
	MODE_END,
	MODE_BAN,
	MODE_INVITE_ONLY,
	MODE_LIMIT,
	MODE_PRIVATE,
	MODE_SECRET,
	MODE_KEY,
	MODE_MODERATED,
	MODE_NO_EXTERNAL_MESSAGES,
	MODE_ONLY_OPS_CHANGE_TOPIC,
	MODE_OP,
	MODE_VOICE,
	MODE_USERS_HIDDEN,
	MODE_RECEIVE_WALLOPS,
	MODE_OPS_OBEY_CHANNEL_LIMIT
};

typedef struct ciModeChange
{
	int mode;
	CHATBool enable;
	char *param;
} ciModeChange;

typedef struct CHATChannelMode
{
	CHATBool InviteOnly;
	CHATBool Private;
	CHATBool Secret;
	CHATBool Moderated;
	CHATBool NoExternalMessages;
	CHATBool OnlyOpsChangeTopic;
	CHATBool OpsObeyChannelLimit;
	int Limit;
	char *Ops;
} CHATChannelMode;

__declspec(dllimport) int __cdecl atoi(const char *string);

void ciApplyChangesToMode(CHATChannelMode *mode, ciModeChange *changes)
{
	ciModeChange *change;

	for (change = changes; change->mode != MODE_END; change++)
	{
		switch (change->mode)
		{
		case MODE_BAN:
			break;
		case MODE_INVITE_ONLY:
			mode->InviteOnly = change->enable;
			break;
		case MODE_LIMIT:
			if (change->enable && change->param)
				mode->Limit = atoi(change->param);
			else
				mode->Limit = 0;
			break;
		case MODE_PRIVATE:
			mode->Private = change->enable;
			break;
		case MODE_SECRET:
			mode->Secret = change->enable;
			break;
		case MODE_KEY:
			break;
		case MODE_MODERATED:
			mode->Moderated = change->enable;
			break;
		case MODE_NO_EXTERNAL_MESSAGES:
			mode->NoExternalMessages = change->enable;
			break;
		case MODE_ONLY_OPS_CHANGE_TOPIC:
			mode->OnlyOpsChangeTopic = change->enable;
			break;
		case MODE_OP:
		case MODE_VOICE:
		case MODE_USERS_HIDDEN:
		case MODE_RECEIVE_WALLOPS:
			break;
		case MODE_OPS_OBEY_CHANNEL_LIMIT:
			mode->OpsObeyChannelLimit = change->enable;
			break;
		}
	}
}
