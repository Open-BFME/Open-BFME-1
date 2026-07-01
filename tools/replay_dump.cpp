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
        std::cout << "{\"message_type\":" << entry.first << ",\"count\":" << entry.second << "}";
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
