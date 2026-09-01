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

__declspec(dllimport) void * __cdecl realloc(void *memory, unsigned int size);
__declspec(dllimport) void __cdecl free(void *memory);
void * __cdecl memset(void *dest, int value, unsigned int count);

ciModeChange *ciParseMode(char *mode, char **params, int numParams)
{
	CHATBool enable;
	int c;
	ciModeChange *changes = 0;
	int numChanges = 0;
	ciModeChange *change;
	int modeChange;
	CHATBool addParam = 0;
	void *tempPtr;

	if (*mode == '+')
		enable = 1;
	else if (*mode == '-')
		enable = 0;
	else
		return 0;
	mode++;

	do
	{
		c = *mode++;
		switch (c)
		{
		case '+':
			enable = 1;
			modeChange = -1;
			break;
		case '-':
			enable = 0;
			modeChange = -1;
			break;
		case '\0':
			modeChange = MODE_END;
			addParam = 0;
			break;
		case 'i':
			modeChange = MODE_INVITE_ONLY;
			addParam = 0;
			break;
		case 'l':
			modeChange = MODE_LIMIT;
			addParam = 1;
			break;
		case 'p':
			modeChange = MODE_PRIVATE;
			addParam = 0;
			break;
		case 's':
			modeChange = MODE_SECRET;
			addParam = 0;
			break;
		case 'k':
			modeChange = MODE_KEY;
			addParam = 1;
			break;
		case 'm':
			modeChange = MODE_MODERATED;
			addParam = 0;
			break;
		case 'n':
			modeChange = MODE_NO_EXTERNAL_MESSAGES;
			addParam = 0;
			break;
		case 't':
			modeChange = MODE_ONLY_OPS_CHANGE_TOPIC;
			addParam = 0;
			break;
		case 'o':
			modeChange = MODE_OP;
			addParam = 1;
			break;
		case 'v':
			modeChange = MODE_VOICE;
			addParam = 1;
			break;
		case 'b':
			modeChange = MODE_BAN;
			addParam = 1;
			break;
		case 'u':
			modeChange = MODE_USERS_HIDDEN;
			addParam = 0;
			break;
		case 'w':
			modeChange = MODE_RECEIVE_WALLOPS;
			addParam = 0;
			break;
		case 'e':
			modeChange = MODE_OPS_OBEY_CHANNEL_LIMIT;
			addParam = 0;
			break;
		default:
			modeChange = -1;
		}

		if (modeChange != -1)
		{
			tempPtr = realloc(changes,
				sizeof(ciModeChange) * (numChanges + 1));
			if (tempPtr == 0)
			{
				free(changes);
				return 0;
			}
			changes = (ciModeChange *)tempPtr;
			change = &changes[numChanges++];
			memset(change, 0, sizeof(ciModeChange));
			change->enable = enable;
			change->mode = modeChange;
			if (addParam)
			{
				if (numParams > 0)
				{
					change->param = *params++;
					numParams--;
				}
				else
					change->param = 0;
			}
		}
	}
	while (c != '\0');

	return changes;
}
