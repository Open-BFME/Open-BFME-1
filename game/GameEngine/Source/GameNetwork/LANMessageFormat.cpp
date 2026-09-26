// cl: /DNDEBUG /MD /EHsc /O2 /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

// LAN message ordinals and their wire descriptions are preserved in the
// shipped image. Keep each switch arm separate: the retail formatter builds
// the temporary format string independently in each case.
#define FORMAT_LAN_MESSAGE(NUMBER, NAME, DESCRIPTION) \
	case NUMBER: result.format(AsciiString("%s(%d) %s"), NAME, NUMBER, DESCRIPTION); break

AsciiString GetMessageTypeString(unsigned int type)
{
	AsciiString result;
	switch (type)
	{
	FORMAT_LAN_MESSAGE(0, "LANMessage::MSG_REQUEST_LOCATIONS", "Hey, where is everybody?");
	FORMAT_LAN_MESSAGE(1, "LANMessage::MSG_GAME_ANNOUNCE", "Here I am, and here's my game info!");
	FORMAT_LAN_MESSAGE(2, "LANMessage::MSG_LOBBY_ANNOUNCE", "Hey, I'm in the lobby!");
	FORMAT_LAN_MESSAGE(3, "LANMessage::MSG_REQUEST_JOIN", "Let me in!  Let me in!");
	FORMAT_LAN_MESSAGE(4, "LANMessage::MSG_JOIN_ACCEPT", "Okay, you can join.");
	FORMAT_LAN_MESSAGE(5, "LANMessage::MSG_JOIN_DENY", "Go away!  We don't want any!");
	FORMAT_LAN_MESSAGE(6, "LANMessage::MSG_REQUEST_GAME_LEAVE", "The joiner wants to leave the game");
	FORMAT_LAN_MESSAGE(7, "LANMessage::MSG_REQUEST_LOBBY_LEAVE", "I'm leaving the lobby");
	FORMAT_LAN_MESSAGE(8, "LANMessage::MSG_REQUEST_HOST_LEAVE", "The host wants to leave the game");
	FORMAT_LAN_MESSAGE(9, "LANMessage::MSG_SET_ACCEPT", "I'm cool with everything as is.");
	FORMAT_LAN_MESSAGE(10, "LANMessage::MSG_MAP_AVAILABILITY", "I do / do not, have the map.");
	FORMAT_LAN_MESSAGE(11, "LANMessage::MSG_CHAT", "Just spouting my mouth off");
	FORMAT_LAN_MESSAGE(12, "LANMessage::MSG_ENABLE_MPSETUP_UI", "Enable/Disable your MP setup screen. Showns 'Continue the game' message box.");
	FORMAT_LAN_MESSAGE(13, "LANMessage::MSG_GAME_START", "Hold on, we're starting!");
	FORMAT_LAN_MESSAGE(14, "LANMessage::MSG_GAME_START_TIMER", "The game will start in N seconds");
	FORMAT_LAN_MESSAGE(15, "LANMessage::MSG_GAME_OPTIONS", "Here's some info about the game.");
	FORMAT_LAN_MESSAGE(16, "LANMessage::MSG_INACTIVE", "I've alt-tabbed out.  Unaccept me cause I'm a poo-flinging monkey.");
	FORMAT_LAN_MESSAGE(17, "LANMessage::MSG_REQUEST_GAME_INFO", "For direct connect, get the game info from a specific IP Address");
	FORMAT_LAN_MESSAGE(18, "LANMessage::MSG_GAME_OPTIONS_PACKED", "Here's all the info about the game, from the host.");
	default: result.format(AsciiString("Unknown Message type %d"), type); break;
	}
	return result;
}
#undef FORMAT_LAN_MESSAGE
