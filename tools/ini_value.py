#!/usr/bin/env python3
"""What value does the GAME load for an INI key? Not what the binary compiles in.

    python3 tools/ini_value.py NetworkRunAheadSlack NetworkDisconnectTime
    python3 tools/ini_value.py --all-network
    python3 tools/ini_value.py --grep 'Network.*'

A GlobalData field has TWO values and they are routinely different. The `imm32`
in the defaults block is what the binary compiles in; the value the process runs
on comes from `GameData.ini`, and `_patch222.big` overrides `ini.big` field by
field. 378 GlobalData fields are INI-parseable, so for any of them the
disassembled constant is a starting point and not an answer.

This has produced wrong published numbers twice in this project. Both times the
constant was read correctly out of the image and quoted as behaviour:

  NetworkDisconnectTime      compiled  5000   shipped  15000   (3x)
  NetworkPlayerTimeoutTime   compiled 60000   shipped 100000
  NetworkKeepAliveDelay      compiled    20   shipped    360   (18x)

A stall was divided by the compiled 5000 ms to state how close a player came to
being dropped, overstating the risk threefold; and "voted out after 60 seconds"
was wrong by forty. Neither error was visible from the disassembly, and neither
needed a running game to avoid -- the archives are on disk.

Reads the archives directly, so it needs no running process and no debugger:
BIG format is a header, a table of (offset, size, name), then the payload.
"""
import argparse
import io
import re
import struct
import sys
from pathlib import Path

# Later archives win, field by field. This is the game's own load order and the
# reason a value read from ini.big alone can still be wrong.
ARCHIVES = ("ini.big", "_patch222.big")
GAME_DIRS = (Path.home() / ".wine/drive_c/BFME1",
             Path.home() / "bfme-test/wine1/drive_c/BFME1")


def entries(path):
    """(name, bytes) for every file in a BIG archive.

    Sizes and offsets are BIG-endian while the archive size is little-endian,
    which is the one detail worth stating: reading them the same way yields
    plausible garbage rather than an error.
    """
    blob = path.read_bytes()
    if blob[:4] not in (b"BIGF", b"BIG4"):
        raise SystemExit(f"{path}: not a BIG archive (magic {blob[:4]!r})")
    count, _first = struct.unpack_from(">II", blob, 8)
    pos = 16
    for _ in range(count):
        offset, size = struct.unpack_from(">II", blob, pos)
        pos += 8
        end = blob.index(b"\0", pos)
        name = blob[pos:end].decode("latin-1")
        pos = end + 1
        yield name, blob[offset:offset + size]


def game_dir(explicit=None):
    for candidate in ([Path(explicit)] if explicit else list(GAME_DIRS)):
        if (candidate / "ini.big").exists():
            return candidate
    raise SystemExit(
        "no BFME install found. Looked in:\n  " + "\n  ".join(str(d) for d in GAME_DIRS) +
        "\nPass --game-dir, or read the value from a live process instead.")


def gamedata(root):
    """Every GameData.ini found, in load order, latest last."""
    found = []
    for archive in ARCHIVES:
        path = root / archive
        if not path.exists():
            continue
        for name, body in entries(path):
            if name.lower().endswith("data\\ini\\gamedata.ini") or \
               name.lower().endswith("data/ini/gamedata.ini"):
                found.append((archive, body))
    if not found:
        raise SystemExit(f"no Data/INI/GameData.ini in {ARCHIVES} under {root}")
    return found


# `Key = Value` with optional whitespace and an optional trailing comment.
ASSIGN = re.compile(r"^\s*([A-Za-z_][A-Za-z0-9_]*)\s*=\s*([^;#\r\n]+)")


def values(body):
    out = {}
    for line in io.StringIO(body.decode("latin-1")):
        m = ASSIGN.match(line)
        if m:
            out[m.group(1)] = m.group(2).strip()
    return out


def resolve(root):
    """key -> (value, which archive supplied it). Later archives override."""
    merged = {}
    for archive, body in gamedata(root):
        for key, value in values(body).items():
            merged[key] = (value, archive)
    return merged


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("keys", nargs="*", help="INI key names, exact")
    ap.add_argument("--grep", metavar="RE", help="every key matching a regex")
    ap.add_argument("--all-network", action="store_true",
                    help="the nine Network* GlobalData fields")
    ap.add_argument("--game-dir")
    a = ap.parse_args()

    root = game_dir(a.game_dir)
    merged = resolve(root)
    print(f"# {root}  ({', '.join(ARCHIVES)}, later overrides earlier)\n")

    wanted = list(a.keys)
    if a.all_network:
        wanted += [k for k in merged if k.startswith("Network")]
    if a.grep:
        wanted += [k for k in merged if re.fullmatch(a.grep, k)]
    if not wanted:
        ap.error("give a key, --grep, or --all-network")

    for key in dict.fromkeys(wanted):
        if key in merged:
            value, archive = merged[key]
            print(f"  {key:36s} {value:>10s}   from {archive}")
        else:
            # Not an error: an absent key means the compiled default DOES stand.
            print(f"  {key:36s} {'(not set)':>10s}   compiled default applies")
    return 0


if __name__ == "__main__":
    sys.exit(main())
