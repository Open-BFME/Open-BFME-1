#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

enum ArgumentDataType {
    ARGUMENTDATATYPE_INTEGER,
    ARGUMENTDATATYPE_REAL,
    ARGUMENTDATATYPE_BOOLEAN,
    ARGUMENTDATATYPE_OBJECTID,
    ARGUMENTDATATYPE_DRAWABLEID,
    ARGUMENTDATATYPE_TEAMID,
    ARGUMENTDATATYPE_SQUADID,
    ARGUMENTDATATYPE_LOCATION,
    ARGUMENTDATATYPE_PIXEL,
    ARGUMENTDATATYPE_PIXELREGION,
    ARGUMENTDATATYPE_TIMESTAMP,
    ARGUMENTDATATYPE_WIDECHAR,
    ARGUMENTDATATYPE_UNKNOWN
};

struct Reader {
    explicit Reader(const char *path) : file(path, std::ios::binary)
    {
        if (!file) {
            throw std::runtime_error(std::string("could not open ") + path);
        }
    }

    std::ifstream file;

    std::uint8_t u8()
    {
        char c = 0;
        read(&c, 1);
        return static_cast<std::uint8_t>(c);
    }

    std::uint16_t u16()
    {
        unsigned char b[2];
        read(reinterpret_cast<char *>(b), sizeof(b));
        return static_cast<std::uint16_t>(b[0] | (b[1] << 8));
    }

    std::uint32_t u32()
    {
        unsigned char b[4];
        read(reinterpret_cast<char *>(b), sizeof(b));
        return static_cast<std::uint32_t>(b[0] | (b[1] << 8) | (b[2] << 16) | (b[3] << 24));
    }

    float f32()
    {
        std::uint32_t bits = u32();
        float value = 0.0f;
        std::memcpy(&value, &bits, sizeof(value));
        return value;
    }

    std::string asciiZ()
    {
        std::string out;
        for (;;) {
            char c = 0;
            read(&c, 1);
            if (c == 0) {
                return out;
            }
            out.push_back(c);
        }
    }

    std::string utf16Z()
    {
        std::string out;
        for (;;) {
            std::uint16_t c = u16();
            if (c == 0) {
                return out;
            }
            appendUtf8(out, c);
        }
    }

    std::uint64_t position()
    {
        return static_cast<std::uint64_t>(file.tellg());
    }

    bool atEnd()
    {
        file.peek();
        return file.eof();
    }

private:
    void read(char *data, std::streamsize size)
    {
        file.read(data, size);
        if (file.gcount() != size) {
            throw std::runtime_error("truncated replay");
        }
    }

    static void appendUtf8(std::string &out, std::uint16_t c)
    {
        if (c < 0x80) {
            out.push_back(static_cast<char>(c));
        } else if (c < 0x800) {
            out.push_back(static_cast<char>(0xc0 | (c >> 6)));
            out.push_back(static_cast<char>(0x80 | (c & 0x3f)));
        } else {
            out.push_back(static_cast<char>(0xe0 | (c >> 12)));
            out.push_back(static_cast<char>(0x80 | ((c >> 6) & 0x3f)));
            out.push_back(static_cast<char>(0x80 | (c & 0x3f)));
        }
    }
};

struct TypeRun {
    std::uint8_t type;
    std::uint8_t count;
};

struct HeaderInfo {
    std::uint32_t frameCount = 0;
    std::uint32_t maxFps = 0;
};

struct PlayerSummary {
    std::uint64_t commands = 0;
    std::uint32_t firstFrame = 0;
    std::uint32_t lastFrame = 0;
};

struct Summary {
    std::uint32_t frameCount = 0;
    std::uint32_t maxFps = 0;
    std::uint32_t lastCommandFrame = 0;
    std::uint64_t commands = 0;
    std::map<std::int32_t, PlayerSummary> players;
    std::map<std::uint32_t, std::uint64_t> messageTypes;
};

struct SlotInfo {
    std::string state;
    std::string name;
    std::uint32_t ip = 0;
    std::uint32_t port = 0;
    bool accepted = false;
    bool hasMap = false;
    int color = -1;
    int playerTemplate = -1;
    int startPosition = -1;
    int team = -1;
    int nat = -1;
};

struct GameOptions {
    int mapContentsMask = 0;
    std::string portableMapPath;
    std::uint32_t mapCrc = 0;
    std::uint32_t mapSize = 0;
    int seed = 0;
    int crcInterval = 0;
    std::vector<SlotInfo> slots;
};

std::vector<std::string> split(const std::string &text, char delimiter)
{
    std::vector<std::string> out;
    std::string current;
    for (char c : text) {
        if (c == delimiter) {
            out.push_back(current);
            current.clear();
        } else {
            current.push_back(c);
        }
    }
    out.push_back(current);
    return out;
}

int parseInt(const std::string &text)
{
    char *end = 0;
    long value = std::strtol(text.c_str(), &end, 10);
    if (*end != 0) {
        throw std::runtime_error("invalid decimal integer in game options");
    }
    return static_cast<int>(value);
}

std::uint32_t parseHex(const std::string &text)
{
    char *end = 0;
    unsigned long value = std::strtoul(text.c_str(), &end, 16);
    if (*end != 0) {
        throw std::runtime_error("invalid hex integer in game options");
    }
    return static_cast<std::uint32_t>(value);
}

void jsonString(std::ostream &out, const std::string &s)
{
    out << '"';
    for (char c : s) {
        switch (c) {
            case '\\': out << "\\\\"; break;
            case '"': out << "\\\""; break;
            case '\b': out << "\\b"; break;
            case '\f': out << "\\f"; break;
            case '\n': out << "\\n"; break;
            case '\r': out << "\\r"; break;
            case '\t': out << "\\t"; break;
            default:
                if (static_cast<unsigned char>(c) < 0x20) {
                    out << "\\u" << std::hex << std::setw(4) << std::setfill('0')
                        << static_cast<int>(static_cast<unsigned char>(c))
                        << std::dec << std::setfill(' ');
                } else {
                    out << c;
                }
        }
    }
    out << '"';
}

const char *typeName(std::uint8_t type)
{
    switch (type) {
        case ARGUMENTDATATYPE_INTEGER: return "integer";
        case ARGUMENTDATATYPE_REAL: return "real";
        case ARGUMENTDATATYPE_BOOLEAN: return "boolean";
        case ARGUMENTDATATYPE_OBJECTID: return "object_id";
        case ARGUMENTDATATYPE_DRAWABLEID: return "drawable_id";
        case ARGUMENTDATATYPE_TEAMID: return "team_id";
        case ARGUMENTDATATYPE_SQUADID: return "squad_id";
        case ARGUMENTDATATYPE_LOCATION: return "location";
        case ARGUMENTDATATYPE_PIXEL: return "pixel";
        case ARGUMENTDATATYPE_PIXELREGION: return "pixel_region";
        case ARGUMENTDATATYPE_TIMESTAMP: return "timestamp";
        case ARGUMENTDATATYPE_WIDECHAR: return "widechar";
        case ARGUMENTDATATYPE_UNKNOWN: return "unknown";
        default: return "invalid";
    }
}

const char *messageName(std::uint32_t type)
{
    struct MessageName {
        std::uint32_t type;
        const char *name;
    };
    static const MessageName names[] = {
        {33, "MSG_META_SAVE_VIEW1"},
        {34, "MSG_META_SAVE_VIEW2"},
        {35, "MSG_META_SAVE_VIEW3"},
        {36, "MSG_META_SAVE_VIEW4"},
        {37, "MSG_META_SAVE_VIEW5"},
        {38, "MSG_META_SAVE_VIEW6"},
        {39, "MSG_META_SAVE_VIEW7"},
        {40, "MSG_META_SAVE_VIEW8"},
        {41, "MSG_META_VIEW_VIEW1"},
        {42, "MSG_META_VIEW_VIEW2"},
        {43, "MSG_META_VIEW_VIEW3"},
        {44, "MSG_META_VIEW_VIEW4"},
        {45, "MSG_META_VIEW_VIEW5"},
        {46, "MSG_META_VIEW_VIEW6"},
        {47, "MSG_META_VIEW_VIEW7"},
        {48, "MSG_META_VIEW_VIEW8"},
        {49, "MSG_META_CREATE_TEAM0"},
        {50, "MSG_META_CREATE_TEAM1"},
        {51, "MSG_META_CREATE_TEAM2"},
        {52, "MSG_META_CREATE_TEAM3"},
        {53, "MSG_META_CREATE_TEAM4"},
        {54, "MSG_META_CREATE_TEAM5"},
        {55, "MSG_META_CREATE_TEAM6"},
        {56, "MSG_META_CREATE_TEAM7"},
        {57, "MSG_META_CREATE_TEAM8"},
        {58, "MSG_META_CREATE_TEAM9"},
        {59, "MSG_META_SELECT_TEAM0"},
        {60, "MSG_META_SELECT_TEAM1"},
        {61, "MSG_META_SELECT_TEAM2"},
        {62, "MSG_META_SELECT_TEAM3"},
        {63, "MSG_META_SELECT_TEAM4"},
        {64, "MSG_META_SELECT_TEAM5"},
        {65, "MSG_META_SELECT_TEAM6"},
        {66, "MSG_META_SELECT_TEAM7"},
        {67, "MSG_META_SELECT_TEAM8"},
        {68, "MSG_META_SELECT_TEAM9"},
        {69, "MSG_META_ADD_TEAM0"},
        {70, "MSG_META_ADD_TEAM1"},
        {71, "MSG_META_ADD_TEAM2"},
        {72, "MSG_META_ADD_TEAM3"},
        {73, "MSG_META_ADD_TEAM4"},
        {74, "MSG_META_ADD_TEAM5"},
        {75, "MSG_META_ADD_TEAM6"},
        {76, "MSG_META_ADD_TEAM7"},
        {77, "MSG_META_ADD_TEAM8"},
        {78, "MSG_META_ADD_TEAM9"},
        {79, "MSG_META_VIEW_TEAM0"},
        {80, "MSG_META_VIEW_TEAM1"},
        {81, "MSG_META_VIEW_TEAM2"},
        {82, "MSG_META_VIEW_TEAM3"},
        {83, "MSG_META_VIEW_TEAM4"},
        {84, "MSG_META_VIEW_TEAM5"},
        {85, "MSG_META_VIEW_TEAM6"},
        {86, "MSG_META_VIEW_TEAM7"},
        {87, "MSG_META_VIEW_TEAM8"},
        {88, "MSG_META_VIEW_TEAM9"},
        {89, "MSG_META_SELECT_MATCHING_UNITS"},
        {90, "MSG_META_SELECT_NEXT_UNIT"},
        {91, "MSG_META_SELECT_PREV_UNIT"},
        {92, "MSG_META_SELECT_NEXT_WORKER"},
        {93, "MSG_META_SELECT_PREV_WORKER"},
        {94, "MSG_META_VIEW_HOME_BASE"},
        {95, "MSG_META_VIEW_LAST_RADAR_EVENT"},
        {96, "MSG_META_SELECT_HERO"},
        {97, "MSG_META_SELECT_ALL"},
        {98, "MSG_META_SCATTER"},
        {99, "MSG_META_STOP"},
        {100, "MSG_META_DEPLOY"},
        {101, "MSG_META_CREATE_FORMATION"},
        {102, "MSG_META_AUTO_SAVE"},
        {103, "MSG_META_FOLLOW"},
        {104, "MSG_META_CHAT_PLAYERS"},
        {105, "MSG_META_CHAT_BUDDIES"},
        {106, "MSG_META_CHAT_ALLIES"},
        {107, "MSG_META_CHAT_EVERYONE"},
        {108, "MSG_META_DIPLOMACY"},
        {109, "MSG_META_OPTIONS"},
        {110, "MSG_META_TOGGLE_LOWER_DETAILS"},
        {111, "MSG_META_TOGGLE_CONTROL_BAR"},
        {112, "MSG_META_BEGIN_PATH_BUILD"},
        {113, "MSG_META_END_PATH_BUILD"},
        {114, "MSG_META_BEGIN_FORCEATTACK"},
        {115, "MSG_META_END_FORCEATTACK"},
        {116, "MSG_META_BEGIN_FORCEMOVE"},
        {117, "MSG_META_END_FORCEMOVE"},
        {118, "MSG_META_BEGIN_WAYPOINTS"},
        {119, "MSG_META_END_WAYPOINTS"},
        {120, "MSG_META_BEGIN_PREFER_SELECTION"},
        {121, "MSG_META_END_PREFER_SELECTION"},
        {122, "MSG_META_TAKE_SCREENSHOT"},
        {123, "MSG_META_ALL_CHEER"},
        {124, "MSG_META_TOGGLE_ATTACKMOVE"},
        {125, "MSG_META_BEGIN_CAMERA_ROTATE_LEFT"},
        {126, "MSG_META_END_CAMERA_ROTATE_LEFT"},
        {127, "MSG_META_BEGIN_CAMERA_ROTATE_RIGHT"},
        {128, "MSG_META_END_CAMERA_ROTATE_RIGHT"},
        {129, "MSG_META_BEGIN_CAMERA_ZOOM_IN"},
        {130, "MSG_META_END_CAMERA_ZOOM_IN"},
        {131, "MSG_META_BEGIN_CAMERA_ZOOM_OUT"},
        {132, "MSG_META_END_CAMERA_ZOOM_OUT"},
        {133, "MSG_META_CAMERA_RESET"},
        {134, "MSG_META_BEGIN_CAMERA_SCROLL_LEFT"},
        {135, "MSG_META_END_CAMERA_SCROLL_LEFT"},
        {136, "MSG_META_BEGIN_CAMERA_SCROLL_RIGHT"},
        {137, "MSG_META_END_CAMERA_SCROLL_RIGHT"},
        {138, "MSG_META_BEGIN_CAMERA_SCROLL_UP"},
        {139, "MSG_META_END_CAMERA_SCROLL_UP"},
        {140, "MSG_META_BEGIN_CAMERA_SCROLL_DOWN"},
        {141, "MSG_META_END_CAMERA_SCROLL_DOWN"},
        {142, "MSG_META_PLACE_BEACON"},
        {143, "MSG_META_DELETE_BEACON"},
        {144, "MSG_META_SPELL_STORE"},
        {145, "MSG_META_DEMO_PERFORM_STATISTICAL_DUMP"},
        {146, "MSG_META_TOGGLE_FAST_FORWARD_MODE"},
        {1001, "MSG_CREATE_SELECTED_GROUP"},
        {1002, "MSG_CREATE_SELECTED_GROUP_NO_SOUND"},
        {1003, "MSG_DESTROY_SELECTED_GROUP"},
        {1004, "MSG_REMOVE_FROM_SELECTED_GROUP"},
        {1005, "MSG_CREATE_TEAM0"},
        {1006, "MSG_CREATE_TEAM1"},
        {1007, "MSG_CREATE_TEAM2"},
        {1008, "MSG_CREATE_TEAM3"},
        {1009, "MSG_CREATE_TEAM4"},
        {1010, "MSG_CREATE_TEAM5"},
        {1011, "MSG_CREATE_TEAM6"},
        {1012, "MSG_CREATE_TEAM7"},
        {1013, "MSG_CREATE_TEAM8"},
        {1014, "MSG_CREATE_TEAM9"},
        {1015, "MSG_SELECT_TEAM0"},
        {1016, "MSG_SELECT_TEAM1"},
        {1017, "MSG_SELECT_TEAM2"},
        {1018, "MSG_SELECT_TEAM3"},
        {1019, "MSG_SELECT_TEAM4"},
        {1020, "MSG_SELECT_TEAM5"},
        {1021, "MSG_SELECT_TEAM6"},
        {1022, "MSG_SELECT_TEAM7"},
        {1023, "MSG_SELECT_TEAM8"},
        {1024, "MSG_SELECT_TEAM9"},
        {1025, "MSG_ADD_TEAM0"},
        {1026, "MSG_ADD_TEAM1"},
        {1027, "MSG_ADD_TEAM2"},
        {1028, "MSG_ADD_TEAM3"},
        {1029, "MSG_ADD_TEAM4"},
        {1030, "MSG_ADD_TEAM5"},
        {1031, "MSG_ADD_TEAM6"},
        {1032, "MSG_ADD_TEAM7"},
        {1033, "MSG_ADD_TEAM8"},
        {1034, "MSG_ADD_TEAM9"},
        {1035, "MSG_DO_ATTACKSQUAD"},
        {1036, "MSG_DO_WEAPON"},
        {1037, "MSG_DO_WEAPON_AT_LOCATION"},
        {1038, "MSG_DO_WEAPON_AT_OBJECT"},
        {1039, "MSG_DO_SPECIAL_POWER"},
        {1040, "MSG_DO_SPECIAL_POWER_AT_LOCATION"},
        {1041, "MSG_DO_SPECIAL_POWER_AT_OBJECT"},
        {1042, "MSG_SET_RALLY_POINT"},
        {1043, "MSG_PURCHASE_SCIENCE"},
        {1044, "MSG_QUEUE_UPGRADE"},
        {1045, "MSG_CANCEL_UPGRADE"},
        {1046, "MSG_QUEUE_UNIT_CREATE"},
        {1047, "MSG_CANCEL_UNIT_CREATE"},
        {1048, "MSG_FOUNDATION_CONSTRUCT"},
        {1049, "MSG_UNUSED"},
        {1050, "MSG_DOZER_CANCEL_CONSTRUCT"},
        {1051, "MSG_SELL"},
        {1052, "MSG_EXIT"},
        {1053, "MSG_EVACUATE"},
        {1054, "MSG_EVACUATE_CONTESTERS"},
        {1055, "MSG_SACRIFICE"},
        {1056, "MSG_COMBATDROP_AT_LOCATION"},
        {1057, "MSG_COMBATDROP_AT_OBJECT"},
        {1058, "MSG_COMBINE_HORDES_WITH_OBJECT"},
        {1059, "MSG_AREA_SELECTION"},
        {1060, "MSG_DO_ATTACK_OBJECT"},
        {1061, "MSG_DO_FORCE_ATTACK_OBJECT"},
        {1062, "MSG_DO_FORCE_ATTACK_GROUND"},
        {1063, "MSG_GET_REPAIRED"},
        {1064, "MSG_GET_HEALED"},
        {1065, "MSG_DO_REPAIR"},
        {1066, "MSG_RESUME_CONSTRUCTION"},
        {1067, "MSG_ENTER"},
        {1068, "MSG_DOCK"},
        {1069, "MSG_HARVEST"},
        {1070, "MSG_DO_MOVETO"},
        {1071, "MSG_DO_ATTACKMOVETO"},
        {1072, "MSG_DO_FORCEMOVETO"},
        {1073, "MSG_ADD_WAYPOINT"},
        {1074, "MSG_DO_GUARD_POSITION"},
        {1075, "MSG_DO_GUARD_OBJECT"},
        {1076, "MSG_DO_STOP"},
        {1077, "MSG_DO_SCATTER"},
        {1078, "MSG_OPEN_GATE"},
        {1079, "MSG_DO_CHEER"},
        {1080, "MSG_CLOSE_GATE"},
        {1081, "MSG_SWITCH_WEAPONS"},
        {1082, "MSG_CONVERT_TO_CARBOMB"},
        {1083, "MSG_CAPTUREBUILDING"},
        {1084, "MSG_CASTLE_UNPACK"},
        {1085, "MSG_CASTLE_PACK"},
        {1086, "MSG_CASTLE_UNPACK_EXPLICIT_OBJECT"},
        {1087, "MSG_SNIPE_VEHICLE"},
        {1088, "MSG_DO_SPECIAL_POWER_OVERRIDE_DESTINATION"},
        {1089, "MSG_DO_SALVAGE"},
        {1090, "MSG_CLEAR_INGAME_POPUP_MESSAGE"},
        {1091, "MSG_PLACE_BEACON"},
        {1092, "MSG_REMOVE_BEACON"},
        {1093, "MSG_SET_BEACON_TEXT"},
        {1094, "MSG_SET_REPLAY_CAMERA"},
        {1095, "MSG_SELF_DESTRUCT"},
        {1096, "MSG_CREATE_FORMATION"},
        {1097, "MSG_LOGIC_CRC"},
        {1098, "MSG_SET_MINE_CLEARING_DETAIL"},
        {1099, "MSG_DO_USER1"},
        {1100, "MSG_DO_USER2"},
        {1101, "MSG_DO_USER3"},
        {1102, "MSG_DO_USER4"},
        {1103, "MSG_MOVE_ARMY_TO_POSITION"},
        {1104, "MSG_AUTO_SAVE"},
        {1105, "MSG_CHANGE_CAMERA_ARRIVED_AT_WAYPOINTID"},
        {1106, "MSG_HORDE_TOGGLE_FORMATION"},
        {1107, "MSG_ONE_RING"},
        {1108, "MSG_CREW_EVACUATE"},
        {1109, "MSG_DO_SPELLBOOK_SPECIAL_POWER"},
        {1110, "MSG_WEAPONSET_TOGGLE"},
        {1111, "MSG_DO_AUTO_ABILITY"},
        {1112, "MSG_DO_AUTO_ABILITY_WEAPON"},
        {1113, "MSG_REVIVE"},
        {1114, "MSG_TOGGLE_NO_AUTO_ACQUIRE"},
        {1115, "MSG_WAKE_AUTO_PICKUP"},
        {1116, "MSG_START_SELF_REPAIR"},
        {1117, "MSG_SUMMON_REINFORCEMENTS"},
        {1118, "MSG_CALL_IN_REINFORCEMENTS"},
        {1119, "MSG_HORDE_SET_FORMATION"},
        {1120, "MSG_CREATE_SELECT_ALL_GROUP"},
        {1121, "MSG_ENABLE_RETALIATION_MODE"},
        {2007, "MSG_JOIN_HORDE_HINT"},
        {2008, "MSG_CAN_GRAB_HINT"},
    };

    std::size_t first = 0;
    std::size_t count = sizeof(names) / sizeof(names[0]);
    while (count != 0) {
        std::size_t step = count / 2;
        std::size_t index = first + step;
        if (names[index].type < type) {
            first = index + 1;
            count -= step + 1;
        } else {
            count = step;
        }
    }

    if (first < sizeof(names) / sizeof(names[0]) && names[first].type == type) {
        return names[first].name;
    }
    return 0;
}

SlotInfo parseSlot(const std::string &raw)
{
    if (raw.empty()) {
        throw std::runtime_error("empty slot entry in game options");
    }

    SlotInfo slot;
    if (raw[0] == 'H') {
        std::vector<std::string> fields = split(raw, ',');
        if (fields.size() != 9 || fields[0].size() < 2 || fields[3].size() != 2) {
            throw std::runtime_error("invalid human slot entry in game options");
        }
        slot.state = "human";
        slot.name = fields[0].substr(1);
        slot.ip = parseHex(fields[1]);
        slot.port = static_cast<std::uint32_t>(parseInt(fields[2]));
        slot.accepted = fields[3][0] == 'T';
        slot.hasMap = fields[3][1] == 'T';
        slot.color = parseInt(fields[4]);
        slot.playerTemplate = parseInt(fields[5]);
        slot.startPosition = parseInt(fields[6]);
        slot.team = parseInt(fields[7]);
        slot.nat = parseInt(fields[8]);
    } else if (raw[0] == 'C') {
        std::vector<std::string> fields = split(raw, ',');
        if (fields.size() != 5 || fields[0].size() != 2) {
            throw std::runtime_error("invalid AI slot entry in game options");
        }
        switch (fields[0][1]) {
            case 'E': slot.state = "easy_ai"; break;
            case 'M': slot.state = "medium_ai"; break;
            case 'H': slot.state = "brutal_ai"; break;
            default: throw std::runtime_error("invalid AI difficulty in game options");
        }
        slot.accepted = true;
        slot.hasMap = true;
        slot.color = parseInt(fields[1]);
        slot.playerTemplate = parseInt(fields[2]);
        slot.startPosition = parseInt(fields[3]);
        slot.team = parseInt(fields[4]);
    } else if (raw == "O") {
        slot.state = "open";
    } else if (raw == "X") {
        slot.state = "closed";
    } else {
        throw std::runtime_error("unknown slot entry in game options");
    }

    return slot;
}

GameOptions parseGameOptions(const std::string &text)
{
    GameOptions options;
    bool sawMap = false;
    bool sawMapCrc = false;
    bool sawMapSize = false;
    bool sawSeed = false;
    bool sawCrc = false;
    bool sawSlots = false;

    for (const std::string &pair : split(text, ';')) {
        if (pair.empty()) {
            continue;
        }

        std::size_t equals = pair.find('=');
        if (equals == std::string::npos) {
            throw std::runtime_error("invalid key/value pair in game options");
        }
        std::string key = pair.substr(0, equals);
        std::string value = pair.substr(equals + 1);
        if (value.empty()) {
            throw std::runtime_error("empty value in game options");
        }

        if (key == "M") {
            if (value.size() < 2) {
                throw std::runtime_error("invalid map entry in game options");
            }
            options.mapContentsMask = static_cast<int>(parseHex(value.substr(0, 2)));
            options.portableMapPath = value.substr(2);
            sawMap = true;
        } else if (key == "MC") {
            options.mapCrc = parseHex(value);
            sawMapCrc = true;
        } else if (key == "MS") {
            options.mapSize = static_cast<std::uint32_t>(parseInt(value));
            sawMapSize = true;
        } else if (key == "SD") {
            options.seed = parseInt(value);
            sawSeed = true;
        } else if (key == "C") {
            options.crcInterval = parseInt(value);
            sawCrc = true;
        } else if (key == "S") {
            std::vector<std::string> rawSlots = split(value, ':');
            for (const std::string &rawSlot : rawSlots) {
                if (!rawSlot.empty()) {
                    options.slots.push_back(parseSlot(rawSlot));
                }
            }
            if (options.slots.size() != 8) {
                throw std::runtime_error("slot list does not contain eight slots");
            }
            sawSlots = true;
        } else {
            throw std::runtime_error("unknown key in game options");
        }
    }

    if (!sawMap || !sawMapCrc || !sawMapSize || !sawSeed || !sawCrc || !sawSlots) {
        throw std::runtime_error("missing key in game options");
    }
    return options;
}

void emitGameOptions(const GameOptions &game)
{
    std::cout << ",\"game_info\":{\"map_contents_mask\":" << game.mapContentsMask;
    std::cout << ",\"portable_map_path\":";
    jsonString(std::cout, game.portableMapPath);
    std::cout << ",\"map_crc\":" << game.mapCrc;
    std::cout << ",\"map_size\":" << game.mapSize;
    std::cout << ",\"seed\":" << game.seed;
    std::cout << ",\"crc_interval\":" << game.crcInterval;
    std::cout << ",\"slots\":[";
    for (std::size_t i = 0; i < game.slots.size(); ++i) {
        const SlotInfo &slot = game.slots[i];
        if (i != 0) {
            std::cout << ',';
        }
        std::cout << "{\"index\":" << i << ",\"state\":";
        jsonString(std::cout, slot.state);
        std::cout << ",\"name\":";
        jsonString(std::cout, slot.name);
        std::cout << ",\"ip\":" << slot.ip;
        std::cout << ",\"port\":" << slot.port;
        std::cout << ",\"accepted\":" << (slot.accepted ? "true" : "false");
        std::cout << ",\"has_map\":" << (slot.hasMap ? "true" : "false");
        std::cout << ",\"color\":" << slot.color;
        std::cout << ",\"player_template\":" << slot.playerTemplate;
        std::cout << ",\"start_position\":" << slot.startPosition;
        std::cout << ",\"team\":" << slot.team;
        std::cout << ",\"nat\":" << slot.nat;
        std::cout << "}";
    }
    std::cout << "]}";
}

HeaderInfo emitHeader(Reader &reader)
{
    char magic[8];
    reader.file.read(magic, sizeof(magic));
    if (reader.file.gcount() != sizeof(magic) || std::memcmp(magic, "BFMEREPL", sizeof(magic)) != 0) {
        throw std::runtime_error("not a BFME replay");
    }

    std::uint32_t startTime = reader.u32();
    std::uint32_t endTime = reader.u32();
    std::uint32_t frameCount = reader.u32();
    std::uint32_t desync = reader.u32();
    std::uint32_t quitEarly = reader.u32();
    std::uint8_t unknownFlag = reader.u8();
    std::uint8_t disconnects[8];
    for (std::uint8_t &disconnect : disconnects) {
        disconnect = reader.u8();
    }

    std::string replayName = reader.utf16Z();
    std::uint16_t year = reader.u16();
    std::uint16_t month = reader.u16();
    std::uint16_t dayOfWeek = reader.u16();
    std::uint16_t day = reader.u16();
    std::uint16_t hour = reader.u16();
    std::uint16_t minute = reader.u16();
    std::uint16_t second = reader.u16();
    std::uint16_t milliseconds = reader.u16();
    std::string version = reader.utf16Z();
    std::string buildTime = reader.utf16Z();
    std::uint32_t versionNumber = reader.u32();
    std::uint32_t exeCrc = reader.u32();
    std::uint32_t iniCrc = reader.u32();
    std::uint8_t official = reader.u8();
    std::uint32_t seed = reader.u32();
    std::string gameOptions = reader.asciiZ();
    GameOptions parsedGameOptions = parseGameOptions(gameOptions);
    std::string localPlayerIndex = reader.asciiZ();
    std::uint32_t difficulty = reader.u32();
    std::uint32_t originalGameMode = reader.u32();
    std::uint32_t rankPoints = reader.u32();
    std::uint32_t maxFps = reader.u32();

    std::cout << "{\"kind\":\"header\"";
    std::cout << ",\"start_time\":" << startTime;
    std::cout << ",\"end_time\":" << endTime;
    std::cout << ",\"frame_count\":" << frameCount;
    std::cout << ",\"desync\":" << desync;
    std::cout << ",\"quit_early\":" << quitEarly;
    std::cout << ",\"unknown_flag\":" << static_cast<int>(unknownFlag);
    std::cout << ",\"player_disconnects\":[";
    for (int i = 0; i < 8; ++i) {
        if (i != 0) {
            std::cout << ',';
        }
        std::cout << static_cast<int>(disconnects[i]);
    }
    std::cout << "]";
    std::cout << ",\"replay_name\":";
    jsonString(std::cout, replayName);
    std::cout << ",\"system_time\":{\"year\":" << year << ",\"month\":" << month
              << ",\"day_of_week\":" << dayOfWeek << ",\"day\":" << day
              << ",\"hour\":" << hour << ",\"minute\":" << minute
              << ",\"second\":" << second << ",\"milliseconds\":" << milliseconds << "}";
    std::cout << ",\"version\":";
    jsonString(std::cout, version);
    std::cout << ",\"build_time\":";
    jsonString(std::cout, buildTime);
    std::cout << ",\"version_number\":" << versionNumber;
    std::cout << ",\"exe_crc\":" << exeCrc;
    std::cout << ",\"ini_crc\":" << iniCrc;
    std::cout << ",\"official\":" << static_cast<int>(official);
    std::cout << ",\"seed\":" << seed;
    std::cout << ",\"game_options\":";
    jsonString(std::cout, gameOptions);
    emitGameOptions(parsedGameOptions);
    std::cout << ",\"local_player_index\":";
    jsonString(std::cout, localPlayerIndex);
    std::cout << ",\"difficulty\":" << difficulty;
    std::cout << ",\"original_game_mode\":" << originalGameMode;
    std::cout << ",\"rank_points\":" << rankPoints;
    std::cout << ",\"max_fps\":" << maxFps;
    std::cout << ",\"command_stream_offset\":" << reader.position();
    std::cout << "}\n";

    HeaderInfo info;
    info.frameCount = frameCount;
    info.maxFps = maxFps;
    return info;
}

void emitArgument(Reader &reader, std::uint8_t type)
{
    std::cout << "{\"type\":\"" << typeName(type) << "\",\"value\":";
    switch (type) {
        case ARGUMENTDATATYPE_INTEGER:
        case ARGUMENTDATATYPE_OBJECTID:
        case ARGUMENTDATATYPE_DRAWABLEID:
        case ARGUMENTDATATYPE_TEAMID:
        case ARGUMENTDATATYPE_SQUADID:
        case ARGUMENTDATATYPE_TIMESTAMP:
            std::cout << reader.u32();
            break;
        case ARGUMENTDATATYPE_REAL:
            std::cout << reader.f32();
            break;
        case ARGUMENTDATATYPE_BOOLEAN:
            std::cout << static_cast<int>(reader.u8());
            break;
        case ARGUMENTDATATYPE_LOCATION:
            std::cout << "{\"x\":" << reader.f32() << ",\"y\":" << reader.f32()
                      << ",\"z\":" << reader.f32() << "}";
            break;
        case ARGUMENTDATATYPE_PIXEL:
            std::cout << "{\"x\":" << reader.u32() << ",\"y\":" << reader.u32() << "}";
            break;
        case ARGUMENTDATATYPE_PIXELREGION:
            std::cout << "{\"lo\":{\"x\":" << reader.u32() << ",\"y\":" << reader.u32()
                      << "},\"hi\":{\"x\":" << reader.u32() << ",\"y\":" << reader.u32() << "}}";
            break;
        case ARGUMENTDATATYPE_WIDECHAR:
            std::cout << reader.u16();
            break;
        default:
            throw std::runtime_error("unknown argument type in command stream");
    }
    std::cout << "}";
}

bool emitCommand(Reader &reader, Summary &summary)
{
    if (reader.atEnd()) {
        return false;
    }

    std::uint32_t frame = reader.u32();
    std::uint32_t messageType = reader.u32();
    std::int32_t playerIndex = static_cast<std::int32_t>(reader.u32());
    std::uint8_t numTypes = reader.u8();
    std::vector<TypeRun> runs;
    int totalArgs = 0;
    for (std::uint8_t i = 0; i < numTypes; ++i) {
        TypeRun run = {reader.u8(), reader.u8()};
        runs.push_back(run);
        totalArgs += run.count;
    }

    ++summary.commands;
    summary.lastCommandFrame = frame;
    ++summary.messageTypes[messageType];
    PlayerSummary &player = summary.players[playerIndex];
    if (player.commands == 0) {
        player.firstFrame = frame;
    }
    ++player.commands;
    player.lastFrame = frame;

    std::cout << "{\"kind\":\"command\",\"offset\":" << reader.position();
    std::cout << ",\"frame\":" << frame;
    std::cout << ",\"message_type\":" << messageType;
    if (const char *name = messageName(messageType)) {
        std::cout << ",\"message_name\":\"" << name << "\"";
    }
    std::cout << ",\"player_index\":" << playerIndex;
    std::cout << ",\"type_runs\":[";
    for (std::size_t i = 0; i < runs.size(); ++i) {
        if (i != 0) {
            std::cout << ',';
        }
        std::cout << "{\"type\":\"" << typeName(runs[i].type) << "\",\"count\":"
                  << static_cast<int>(runs[i].count) << "}";
    }
    std::cout << "],\"arguments\":[";

    int emitted = 0;
    for (const TypeRun &run : runs) {
        for (std::uint8_t i = 0; i < run.count; ++i) {
            if (emitted != 0) {
                std::cout << ',';
            }
            emitArgument(reader, run.type);
            ++emitted;
        }
    }
    if (emitted != totalArgs) {
        throw std::runtime_error("argument count mismatch");
    }
    std::cout << "]}\n";
    return true;
}

void emitSummary(const Summary &summary)
{
    std::cout << "{\"kind\":\"summary\",\"commands\":" << summary.commands;
    std::cout << ",\"frame_count\":" << summary.frameCount;
    std::cout << ",\"last_command_frame\":" << summary.lastCommandFrame;
    std::cout << ",\"max_fps\":" << summary.maxFps;
    std::cout << ",\"players\":[";
    bool first = true;
    for (const auto &entry : summary.players) {
        if (!first) {
            std::cout << ',';
        }
        first = false;
        const PlayerSummary &player = entry.second;
        std::cout << "{\"player_index\":" << entry.first;
        std::cout << ",\"commands\":" << player.commands;
        std::cout << ",\"first_frame\":" << player.firstFrame;
        std::cout << ",\"last_frame\":" << player.lastFrame;
        if (summary.frameCount != 0 && summary.maxFps != 0) {
            double apm = static_cast<double>(player.commands) * summary.maxFps * 60.0 / summary.frameCount;
            std::cout << ",\"apm_by_max_fps\":" << apm;
        }
        std::cout << "}";
    }
    std::cout << "],\"message_types\":[";
    first = true;
    for (const auto &entry : summary.messageTypes) {
        if (!first) {
            std::cout << ',';
        }
        first = false;
        std::cout << "{\"message_type\":" << entry.first;
        if (const char *name = messageName(entry.first)) {
            std::cout << ",\"message_name\":\"" << name << "\"";
        }
        std::cout << ",\"count\":" << entry.second << "}";
    }
    std::cout << "]}\n";
}

} // namespace

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "usage: replay_dump <file.rep>\n";
        return 2;
    }

    try {
        Reader reader(argv[1]);
        HeaderInfo header = emitHeader(reader);
        Summary summary;
        summary.frameCount = header.frameCount;
        summary.maxFps = header.maxFps;
        while (emitCommand(reader, summary)) {
        }
        emitSummary(summary);
    } catch (const std::exception &ex) {
        std::cerr << "replay_dump: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}
