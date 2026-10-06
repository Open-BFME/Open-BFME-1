#!/usr/bin/env python3
"""Exact layout of every private class view, read from the compiler.

WHY. Deciding whether a unit's private copy of a class is the canonical
class needs its real layout: field offsets and sizes, base offsets, sizeof
and the virtual slots with their argument types. Regex over the class body
cannot give that (inline padding arrays, typedef'd members, bases declared
elsewhere), and cl 13.10 has no /d1reportSingleClassLayout. What it does have
is CodeView: compiling the unit with its own flags plus -Z7 puts every type it
saw into .debug$T, and that record is the compiler's own answer.

THE TRAP. VC7.1 CodeView gives every introducing overload of one name the
same vbaseoff (the group's highest slot), and lays the group out in reverse
declaration order. Taking the CodeView offset at face value names the wrong
slot for every overload but the last. `--probe` compiles a toy class and
compares the slots read here with the offsets the compiler encodes in its
own vcall thunks (??_9@$B<n>AE); it must agree before any slot evidence is
trusted.

CACHE. Objects go to build/class_layouts/. An entry is reused when the
command line, the source and every header /showIncludes listed for it hash
the same (the same receipt rule build.py uses); the parsed layouts are keyed
by the digest of the object's .debug$T section, so two inputs that compile
to the same type stream share one parse.

    python3 tools/class_layouts.py FILE...              all private views, JSON
    python3 tools/class_layouts.py --class Coord3D FILE  one class
    python3 tools/class_layouts.py --probe               slot-order self-check
"""
import argparse
import hashlib
import importlib.util
import json
import re
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
CACHE = ROOT / "build" / "class_layouts"

# A namespace-scope class head opening a body (class_views.HEAD's rule).
HEAD = re.compile(r"^[ \t]*(?:class|struct)[ \t]+(?:__declspec\([^)]*\)\s+)?([A-Za-z_]\w*)\s*(?::[^{;]*)?\{", re.M)
COMMENT = re.compile(r"//[^\n]*|/\*.*?\*/", re.S)

PRIM = {0x03: ("void", 0), 0x10: ("char", 1), 0x20: ("uchar", 1), 0x70: ("char", 1), 0x68: ("int8", 1),
        0x69: ("uint8", 1), 0x11: ("short", 2), 0x21: ("ushort", 2), 0x72: ("short", 2), 0x73: ("ushort", 2),
        0x12: ("long", 4), 0x22: ("ulong", 4), 0x74: ("int", 4), 0x75: ("uint", 4), 0x13: ("int64", 8),
        0x23: ("uint64", 8), 0x76: ("int64", 8), 0x77: ("uint64", 8), 0x40: ("float", 4), 0x41: ("double", 8),
        0x42: ("ldouble", 8), 0x30: ("bool", 1), 0x71: ("wchar", 2), 0x31: ("bool16", 2), 0x32: ("bool32", 4)}
# LF_CLASS/LF_STRUCTURE in the 16-bit-name (_ST) and zero-terminated forms.
CLASS_KINDS = {0x1004: True, 0x1005: True, 0x1504: False, 0x1505: False}
# The VC7.1 overload rule (see THE TRAP). Off reproduces the naive reading;
# tools/tests/test_class_layouts.py uses that as the probe's positive control.
REVERSED_GROUPS = True


def build_module():
    spec = importlib.util.spec_from_file_location("repo_build", ROOT / "tools" / "build.py")
    module = importlib.util.module_from_spec(spec)
    sys.path.insert(0, str(ROOT / "tools"))
    spec.loader.exec_module(module)
    return module


# ---------------------------------------------------------------- CodeView

def coff_sections(data):
    count, optional = struct.unpack_from("<H", data, 2)[0], struct.unpack_from("<H", data, 16)[0]
    offset = 20 + optional
    for _ in range(count):
        name = data[offset:offset + 8].rstrip(b"\0")
        size, pointer = struct.unpack_from("<I", data, offset + 16)[0], struct.unpack_from("<I", data, offset + 20)[0]
        yield name, data[pointer:pointer + size]
        offset += 40


def coff_symbols(data):
    """Names in the COFF symbol table (aux records skipped)."""
    table, count = struct.unpack_from("<II", data, 8)
    strings = table + 18 * count
    index = 0
    while index < count:
        entry = table + 18 * index
        raw = data[entry:entry + 8]
        if raw[:4] == b"\0\0\0\0":
            start = strings + struct.unpack_from("<I", raw, 4)[0]
            name = data[start:data.index(b"\0", start)]
        else:
            name = raw.rstrip(b"\0")
        yield name.decode("latin-1")
        index += 1 + data[entry + 17]


def numeric(blob, pos):
    value = struct.unpack_from("<H", blob, pos)[0]
    if value < 0x8000:
        return value, pos + 2
    fmt, size = {0x8000: ("<b", 1), 0x8001: ("<h", 2), 0x8002: ("<H", 2), 0x8003: ("<i", 4),
                 0x8004: ("<I", 4), 0x8009: ("<q", 8), 0x800A: ("<Q", 8)}[value]
    return struct.unpack_from(fmt, blob, pos + 2)[0], pos + 2 + size


def name_at(blob, pos, pascal):
    if pascal:
        length = blob[pos]
        return blob[pos + 1:pos + 1 + length].decode("latin-1"), pos + 1 + length
    end = blob.index(b"\0", pos)
    return blob[pos:end].decode("latin-1"), end + 1


class TypeStream:
    def __init__(self, stream):
        if struct.unpack_from("<I", stream, 0)[0] not in (1, 2, 4):
            raise ValueError("not a CodeView type stream")
        self.records, pos, index = {}, 4, 0x1000
        while pos + 4 <= len(stream):
            length, kind = struct.unpack_from("<HH", stream, pos)
            self.records[index] = (kind, stream[pos + 4:pos + 2 + length])
            pos += 2 + length
            index += 1

    def name(self, ti):
        if ti < 0x1000:
            return PRIM.get(ti & 0xFF, ("p%x" % (ti & 0xFF), 0))[0] + ("*" if (ti >> 8) & 7 else "")
        kind, blob = self.records.get(ti, (0, b""))
        if kind in CLASS_KINDS:
            _, pos = numeric(blob, 16)
            return name_at(blob, pos, CLASS_KINDS[kind])[0]
        if kind == 0x1002:
            return self.name(struct.unpack_from("<I", blob, 0)[0]) + "*"
        if kind == 0x1001:
            return self.name(struct.unpack_from("<I", blob, 0)[0])
        if kind in (0x1003, 0x1503):
            return "%s[%d]" % (self.name(struct.unpack_from("<I", blob, 0)[0]), numeric(blob, 8)[0])
        if kind in (0x1007, 0x1507):
            return "enum"
        return "bitfield" if kind == 0x1205 else "k%x" % kind

    def size(self, ti):
        if ti < 0x1000:
            return 4 if (ti >> 8) & 7 else PRIM.get(ti & 0xFF, ("", 0))[1]
        kind, blob = self.records.get(ti, (0, b""))
        if kind == 0x1002 or kind in (0x1007, 0x1507):
            return 4
        if kind == 0x1001:
            return self.size(struct.unpack_from("<I", blob, 0)[0])
        if kind in (0x1003, 0x1503):
            return numeric(blob, 8)[0]
        if kind in CLASS_KINDS:
            return numeric(blob, 16)[0]
        return 0

    def signature(self, ti):
        kind, blob = self.records.get(ti, (0, b""))
        if kind != 0x1009:
            return "(?)"
        arglist = struct.unpack_from("<I", blob, 16)[0]
        akind, ablob = self.records.get(arglist, (0, b""))
        args = []
        if akind == 0x1201:
            count = struct.unpack_from("<I", ablob, 0)[0]
            args = [self.name(struct.unpack_from("<I", ablob, 4 + 4 * i)[0]) for i in range(count)]
        return "(" + ",".join(args) + ")"

    def fields(self, ti, out):
        _, blob = self.records[ti]
        pos = 0
        while pos < len(blob):
            while pos < len(blob) and blob[pos] >= 0xF0:
                pos += 1
            if pos + 2 > len(blob):
                break
            sub = struct.unpack_from("<H", blob, pos)[0]
            pos += 2
            if sub == 0x1400:                                   # base class
                index = struct.unpack_from("<I", blob, pos + 2)[0]
                offset, pos = numeric(blob, pos + 6)
                out["bases"].append([self.name(index), offset])
            elif sub in (0x1401, 0x1402):                       # virtual base
                index = struct.unpack_from("<I", blob, pos + 2)[0]
                _, pos = numeric(blob, pos + 10)
                _, pos = numeric(blob, pos)
                out["bases"].append(["virtual " + self.name(index), -1])
            elif sub in (0x1405, 0x150D):                       # data member
                index = struct.unpack_from("<I", blob, pos + 2)[0]
                offset, pos = numeric(blob, pos + 6)
                name, pos = name_at(blob, pos, sub == 0x1405)
                out["fields"].append([offset, name, self.name(index), self.size(index)])
            elif sub in (0x1406, 0x150E):                       # static member
                name, pos = name_at(blob, pos + 6, sub == 0x1406)
                out["statics"].append(name)
            elif sub in (0x1407, 0x150F):                       # overloaded method
                _, methodlist = struct.unpack_from("<HI", blob, pos)
                name, pos = name_at(blob, pos + 6, sub == 0x1407)
                out["methods"].add(name)
                _, mblob = self.records[methodlist]
                q, groups = 0, {}
                while q < len(mblob):
                    attr, _, ty = struct.unpack_from("<HHI", mblob, q)
                    q += 8
                    prop = (attr >> 2) & 7
                    if prop in (4, 6):                          # introducing virtual
                        groups.setdefault(struct.unpack_from("<I", mblob, q)[0], []).append(name + self.signature(ty))
                        q += 4
                    if prop in (1, 4, 5, 6):
                        out["virtual"].add(name)
                # Every intro overload carries the group's HIGHEST slot; the
                # list runs in reverse declaration order, which is the order the
                # compiler assigns slots in (checked by --probe).
                for top, members in groups.items():
                    for i, member in enumerate(members):
                        slot = top - 4 * (len(members) - 1) + 4 * i if REVERSED_GROUPS else top
                        out["vslots"].setdefault(slot, member)
            elif sub in (0x140B, 0x1511):                       # single method
                attr, index = struct.unpack_from("<HI", blob, pos)
                pos += 6
                prop, slot = (attr >> 2) & 7, None
                if prop in (4, 6):
                    slot = struct.unpack_from("<I", blob, pos)[0]
                    pos += 4
                name, pos = name_at(blob, pos, sub == 0x140B)
                out["methods"].add(name)
                if slot is not None:
                    out["vslots"][slot] = name + self.signature(index)
                if prop in (1, 4, 5, 6):
                    out["virtual"].add(name)
            elif sub in (0x1408, 0x1510, 0x140D, 0x1512):       # nested type / static method alias
                _, pos = name_at(blob, pos + 6, sub in (0x1408, 0x140D))
            elif sub == 0x1409:                                 # vfptr
                out["vfptr"] = True
                pos += 6
            elif sub in (0x1404, 0x140A):                       # continuation / vfunc tab
                if sub == 0x1404:
                    self.fields(struct.unpack_from("<I", blob, pos + 2)[0], out)
                pos += 6
            elif sub in (0x1403, 0x150C):
                _, pos = name_at(blob, pos + 6, sub == 0x1403)
            elif sub in (0x0403, 0x1502):                       # enumerator
                _, pos = numeric(blob, pos + 2)
                _, pos = name_at(blob, pos, sub == 0x0403)
            else:
                out["unparsed"] = sub
                break

    def classes(self):
        found = {}
        for ti, (kind, blob) in self.records.items():
            if kind not in CLASS_KINDS:
                continue
            _, prop, fieldlist = struct.unpack_from("<HHI", blob, 0)
            size, pos = numeric(blob, 16)
            name, _ = name_at(blob, pos, CLASS_KINDS[kind])
            if prop & 0x80:                                     # forward reference
                found.setdefault(name, {"fwd": True})
                continue
            out = {"fwd": False, "key": "class" if kind in (0x1004, 0x1504) else "struct", "size": size,
                   "bases": [], "fields": [], "statics": [], "methods": set(), "virtual": set(),
                   "vslots": {}, "vfptr": False}
            if fieldlist:
                self.fields(fieldlist, out)
            out["methods"], out["virtual"] = sorted(out["methods"]), sorted(out["virtual"])
            out["vslots"] = {str(k // 4): v for k, v in sorted(out["vslots"].items())}
            found[name] = out
        return found


def type_stream(obj_bytes):
    return b"".join(data for name, data in coff_sections(obj_bytes) if name == b".debug$T")


# ---------------------------------------------------------------- compile + cache

def class_bodies(text):
    """Names of classes `text` declares a namespace-scope body for (private views)."""
    stripped = COMMENT.sub("", text)
    names = []
    for match in HEAD.finditer(stripped):
        before = stripped[:match.start()].rstrip()
        if re.search(r"template\s*<[^;{}]*>$", before):
            continue
        names.append(match.group(1))
    return names


def sha(data):
    return hashlib.sha256(data).hexdigest()


def file_sha(path):
    try:
        return sha(Path(path).read_bytes())
    except OSError:
        return "missing"


def compile_layouts(source, builder=None, use_cache=True, extra_flags=()):
    """{class: layout} for every class in the unit's type stream; raises on compile error."""
    builder = builder or build_module()
    source = (ROOT / source).resolve()
    rel = source.relative_to(ROOT).as_posix()
    stem = re.sub(r"[^\w.-]", "_", rel)
    CACHE.mkdir(parents=True, exist_ok=True)
    obj, meta = CACHE / (stem + ".obj"), CACHE / (stem + ".json")
    command, env = builder.compiler_command(source, ROOT / "build" / "_class_layouts.obj")
    command = [a for a in command if not a.startswith(("-Fo", "/Fo"))]
    command[-1:-1] = [*extra_flags, "-Fo" + obj.relative_to(ROOT).as_posix(), "-Z7", "-showIncludes"]
    key = sha("\0".join(command).encode() + source.read_bytes())
    if use_cache and meta.exists():
        cached = json.loads(meta.read_text(encoding="utf-8"))
        if cached.get("key") == key and all(file_sha(p) == h for p, h in cached["headers"].items()):
            parsed = CACHE / ("types_" + cached["types"] + ".json")
            if parsed.exists():
                return json.loads(parsed.read_text(encoding="utf-8"))
    done = subprocess.run(command, cwd=ROOT, env=env, capture_output=True, text=True, errors="replace")
    if done.returncode:
        errors = re.findall(r"error (C\d+)[^\n]*", done.stdout + done.stderr)
        raise RuntimeError(f"{rel}: compile failed: " + ("; ".join(errors[:3]) or (done.stdout + done.stderr)[-400:]))
    headers = {}
    for line in done.stdout.splitlines():
        found = re.match(r"Note: including file:\s*(.+)$", line)
        if found:
            path = found.group(1).strip()
            headers[path] = file_sha(path)
    stream = type_stream(obj.read_bytes())
    digest = sha(stream)
    parsed = CACHE / ("types_" + digest + ".json")
    if use_cache and parsed.exists():
        result = json.loads(parsed.read_text(encoding="utf-8"))
    else:
        result = TypeStream(stream).classes() if stream else {}
        if REVERSED_GROUPS:                     # never cache the control's naive parse
            parsed.write_text(json.dumps(result), encoding="utf-8")
    meta.write_text(json.dumps({"key": key, "headers": headers, "types": digest}), encoding="utf-8")
    return result


def private_views(source, builder=None, only=None, use_cache=True):
    """{class: layout} for the classes the unit itself declares (plus their bases)."""
    text = (ROOT / source).read_text(encoding="latin-1")
    declared = [c for c in class_bodies(text) if not only or c in only]
    if not declared:
        return {}
    every = compile_layouts(source, builder, use_cache)
    out = {}
    for name in declared:
        layout = every.get(name)
        if layout is None:
            continue
        out[name] = layout
        for base, _ in layout.get("bases", []):
            if base in every and base not in out:
                out[base] = dict(every[base], base_only=True)
    return out


# ---------------------------------------------------------------- the slot-order probe

PROBE = """\
class Probe {
public:
    virtual ~Probe();
    virtual int f(int);
    virtual int f(float);
    virtual int f(char *);
    virtual void g();
    virtual int h(short);
    virtual int h(double);
};
int (Probe::*probe_f_int)(int) = &Probe::f;
int (Probe::*probe_f_float)(float) = &Probe::f;
int (Probe::*probe_f_char)(char *) = &Probe::f;
void (Probe::*probe_g)() = &Probe::g;
int (Probe::*probe_h_short)(short) = &Probe::h;
int (Probe::*probe_h_double)(double) = &Probe::h;
"""


def mangled_number(text):
    """MSVC encoded number: 0-9 -> 1-10, else hex digits A-P terminated by '@'."""
    if text[0].isdigit():
        return int(text[0]) + 1, text[1:]
    end = text.index("@")
    value = 0
    for char in text[:end]:
        value = value * 16 + (ord(char) - ord("A"))
    return value, text[end + 1:]


def run_probe(builder=None):
    """[(slot, CodeView name, thunk-proved name)] and whether they all agree."""
    builder = builder or build_module()
    CACHE.mkdir(parents=True, exist_ok=True)
    source = CACHE / "slot_probe.cpp"
    source.write_text(PROBE, encoding="utf-8")
    layout = compile_layouts(source.relative_to(ROOT), builder, use_cache=False)["Probe"]
    obj = CACHE / ("build_class_layouts_slot_probe.cpp.obj")
    data = obj.read_bytes()
    thunks = {}
    for name in coff_symbols(data):
        found = re.match(r"\?\?_9@\$B(.+?)AE$", name)
        if found:
            thunks[mangled_number(found.group(1))[0] // 4] = name
    # Which overload each thunk serves: the data symbol initialised with it.
    relocs = probe_initialisers(data)
    proved = {slot: relocs.get(thunk) for slot, thunk in thunks.items()}
    rows, ok = [], bool(proved)
    for slot, member in sorted(proved.items()):
        cv = layout["vslots"].get(str(slot), "")
        rows.append((slot, cv, member))
        ok &= cv == member
    return rows, ok


def probe_initialisers(data):
    """{thunk symbol: 'f(int)'-style member} from the .data relocations of the probe."""
    names = list(coff_symbols_indexed(data))
    out = {}
    table = struct.unpack_from("<I", data, 8)[0]
    count, optional = struct.unpack_from("<H", data, 2)[0], struct.unpack_from("<H", data, 16)[0]
    spell = {"probe_f_int": "f(int)", "probe_f_float": "f(float)", "probe_f_char": "f(char*)",
             "probe_g": "g()", "probe_h_short": "h(short)", "probe_h_double": "h(double)"}
    symbols_at = {}
    for index, name, value, section in names:
        for key, member in spell.items():
            if re.match(r"\?" + key + "@@", name):
                symbols_at[(section, value)] = member
    for number in range(count):
        header = 20 + optional + 40 * number
        relocs, nrel = struct.unpack_from("<I", data, header + 24)[0], struct.unpack_from("<H", data, header + 32)[0]
        for r in range(nrel):
            vaddr, symbol, _ = struct.unpack_from("<IIH", data, relocs + 10 * r)
            target = next((n for i, n, _, _ in names if i == symbol), "")
            member = symbols_at.get((number + 1, vaddr))
            if member and target.startswith("??_9"):
                out[target] = member
    del table
    return out


def coff_symbols_indexed(data):
    table, count = struct.unpack_from("<II", data, 8)
    strings = table + 18 * count
    index = 0
    while index < count:
        entry = table + 18 * index
        raw = data[entry:entry + 8]
        if raw[:4] == b"\0\0\0\0":
            start = strings + struct.unpack_from("<I", raw, 4)[0]
            name = data[start:data.index(b"\0", start)]
        else:
            name = raw.rstrip(b"\0")
        value, section = struct.unpack_from("<Ih", data, entry + 8)
        yield index, name.decode("latin-1"), value, section
        index += 1 + data[entry + 17]


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("files", nargs="*")
    parser.add_argument("--class", dest="names", action="append")
    parser.add_argument("--no-cache", action="store_true")
    parser.add_argument("--probe", action="store_true")
    args = parser.parse_args(argv)
    builder = build_module()
    if args.probe:
        rows, ok = run_probe(builder)
        for slot, cv, proved in rows:
            print(f"  slot {slot}: codeview {cv:<14} thunk {proved}")
        print("slot order: " + ("OK" if ok else "MISMATCH (do not trust CodeView slot evidence)"))
        return 0 if ok else 1
    out, bad = {}, 0
    for path in args.files:
        try:
            out[path] = private_views(path, builder, set(args.names or ()), not args.no_cache)
        except RuntimeError as exc:
            out[path] = {"error": str(exc)}
            bad = 1
    json.dump(out, sys.stdout, indent=1, sort_keys=True)
    print()
    return bad


if __name__ == "__main__":
    sys.exit(main())
