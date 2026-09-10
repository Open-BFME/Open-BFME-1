#!/usr/bin/env python3
"""What the bytes we do NOT hold are worth to each deterministic mechanism.

`progress.py` answers "how much of retail rebuilds from source we hold".
This answers the next question: of the bytes that do not, which ones a known
deterministic mechanism can already claim, how much those mechanisms overlap,
and — for the mechanisms with a landing recipe — which exact rows to hand
`tools/land_wave.py`.

Everything is re-derived from the repository at HEAD: the ledger, the retail
image and reverse/ghidra_functions.csv. Nothing is read back from a previous
run, because a stale accounting CSV that still parses is the one failure this
tool exists to prevent.

Universe. A "not-held range" is one unique (rva, size) inside .text whose best
provenance lane (progress.source_lane) is not one of authored/vendored/
generated/library:

  genasm     matched ledger row sourced from Code/gen_asm/ — retail's own bytes
             re-encoded under a synthetic name, holding a boundary only
  naked      the same idea from a naked/__emit .cpp or a .asm dump
  unclaimed  a ghidra function that overlaps no matched row at all

Mechanisms (the tag letters are the ones the spike report uses):

  A  pool-a-alias           reloc-free body byte-identical to a held-lane row's
  B  zh-exact-multi         ZH exact-multi placement starts here, size agrees
  C  gen-small-skeleton     <=16B body matching a probed skeleton (or a thunk)
  D  gen-small-tgrid-twin   17-2048B skeleton == a matched gen_small row's
  E  gen-small-family-twin  17-2048B skeleton == another matched held C++ row's
  F  new-skeleton-clusters  <=16B new-skeleton cluster with >=10 members
  G1 funclet-sweep          FuncInfo-owned funclet whose owner has a held C++ row
  G2 funclet-cascade        FuncInfo-owned funclet whose owner is a dump row
  H  lib-member             masked .lib member match
  I  gen-uw-mshape          unclaimed D-other funclet with mov[/add]/jmp shape

B and H cannot be re-derived from the repository — they need the ZH placement
index and the lib-member match table, which live outside it. Ask for them and
you must pass the evidence file; there is no silent skip.

Only A has a landing recipe that needs no new source file: the held twin's TU
already compiles, so the not-held copy lands as one more row on that TU with an
`object-symbol=` note, exactly like the 460 `C++ alias` rows already in the
ledger. `wave --mech A` writes that CSV. Every other mechanism has to emit
source first (that is what gen_small.py does), so asking for its wave fails
loudly rather than pretending.

The alias rows carry a synthetic `?a_<rva>@@YAXXZ` name in the same family as
the `?d_<rva>@@YAXXZ` dumps they supersede: what is recovered is that these
bytes rebuild from a TU we hold, not which function they were. A recovered
identity replaces the name later, the way it does for any gen row — and the
notes lead with `gen-alias;` so that check_csv can enforce it. Without that
prefix check_csv reads a synthetic name and a real one over the same range as
an ICF alias group and lets BOTH stand (check_csv.py:173-190); with it, the
placeholder is the one that must yield. The `;` costs nothing: build.py's
`object-symbol=` and progress.py's gen-lane test both anchor on `^` or `;`.

Subcommands
  report            per-mechanism byte accounting over the not-held universe
  wave --mech A     write a wave CSV for tools/land_wave.py
"""
import argparse
import bisect
import collections
import csv
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as B
import gen_small as G
import progress

ROOT = B.ROOT
HELD_LANES = ("authored", "vendored", "generated", "library")
# Derivable from the repository alone.
SELF_CONTAINED = ("A", "C", "D", "E", "F", "G1", "G2", "I")
# Mechanism -> the flag whose evidence file it cannot be measured without.
EVIDENCE_FLAG = {"B": "--zh-exact-multi", "H": "--lib-matches"}
ALL_MECHS = ("A", "B", "C", "D", "E", "F", "G1", "G2", "H", "I")
SUBKINDS = ("genasm", "naked", "unclaimed")
LIB_SUFFIXES = {".lib", ".obj"}
ALIAS_NOTE = "C++ alias"
# check_csv keys the placeholder-must-yield rule on notes STARTING with "gen-".
ALIAS_NOTE_PREFIX = "gen-alias;"
OBJECT_SYMBOL_RE = re.compile(r"(?:^|;)object-symbol=([^;]+)")


# --------------------------------------------------------------------------
# retail image
# --------------------------------------------------------------------------

class Image:
    """One in-memory copy of the retail image, addressed by RVA."""

    def __init__(self):
        self.data = B.EXE.read_bytes()
        self.sections = B.pe_sections(self.data)

    def body(self, rva, size):
        offset = B.rva_to_file_offset(self.sections, rva)
        body = self.data[offset:offset + size]
        if len(body) != size:
            raise SystemExit(f"wave_accounting: 0x{rva:08X}+{size} runs past the end of "
                             f"{B.EXE.name} — the image and the ledger disagree")
        return body


def rel32_probe():
    """has_rel32(body): does this body contain a self-relative displacement?

    A body with a REL32 in it is not aliasable: the gate re-encodes that
    displacement from the row's own target_rva, so the identical bytes that made
    the twin look interesting cannot survive at a second address. Bodies capstone
    cannot fully decode count as unsafe for the same reason — an undecoded tail
    is an unexamined displacement.
    """
    try:
        import capstone
    except ImportError as exc:
        raise SystemExit("wave_accounting: capstone is required to tell a reloc-free body "
                         f"from an aliasable one ({exc}); pip install capstone")
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

    def has_rel32(body):
        decoded = 0
        for ins in md.disasm(body, 0):
            decoded += len(ins.bytes)
            raw = ins.bytes
            if raw[0] in (0xE8, 0xE9):
                return True
            if len(raw) >= 2 and raw[0] == 0x0F and 0x80 <= raw[1] <= 0x8F:
                return True
        return decoded < len(body)

    return has_rel32


# --------------------------------------------------------------------------
# universe
# --------------------------------------------------------------------------

class Universe:
    """Ranges of .text partitioned into held / not-held, with their rows."""

    def __init__(self):
        matched = progress.matched_at(None)
        notes = progress.notes_at(None)
        naked = progress.naked_cpp_rows_at(matched, None)
        self.text_start, text_size = progress.retail_text()
        self.text_end = self.text_start + text_size

        lanes = collections.defaultdict(set)
        self.rows = collections.defaultdict(list)
        for key, (size, source) in matched.items():
            rva = int(key[1], 16)
            if rva < self.text_start or rva + size > self.text_end:
                continue
            lane = progress.source_lane(source, notes[key], key in naked)
            lanes[(rva, size)].add(lane)
            self.rows[(rva, size)].append({
                "name": key[0], "rva": rva, "size": size,
                "source": source, "notes": notes[key], "lane": lane})

        self.held = set()
        self.not_held = {}
        for key, key_lanes in lanes.items():
            lane = self.best_lane(key_lanes)
            if lane in HELD_LANES:
                self.held.add(key)
            elif lane == "dump":
                sources = {row["source"] for row in self.rows[key]}
                self.not_held[key] = ("genasm"
                                      if any(s.startswith(G.DUMP_DIR_PREFIX) for s in sources)
                                      else "naked")
            else:
                raise SystemExit(f"wave_accounting: 0x{key[0]:08X}/{key[1]}B resolved to "
                                 f"unexpected lane {lane!r}")

        self.ghidra_names = {}
        for rva, size in self._add_unclaimed(lanes):
            self.not_held[(rva, size)] = "unclaimed"

    @staticmethod
    def best_lane(lanes):
        for lane in progress.SOURCE_LANES:
            if lane in lanes:
                return lane
        raise SystemExit(f"wave_accounting: no known provenance lane in {sorted(lanes)}")

    def _add_unclaimed(self, lanes):
        """Ghidra functions overlapping no matched row — the never-claimed lane."""
        intervals = sorted((rva, rva + size) for (rva, size) in lanes)
        starts = [start for start, _ in intervals]
        max_end, running = [], 0
        for _, end in intervals:
            running = max(running, end)
            max_end.append(running)

        def overlaps(rva, size):
            i = bisect.bisect_right(starts, rva + size - 1) - 1
            while i >= 0 and max_end[i] > rva:
                if intervals[i][1] > rva and intervals[i][0] < rva + size:
                    return True
                i -= 1
            return False

        path = ROOT / "reverse" / "ghidra_functions.csv"
        if not path.exists():
            raise SystemExit(f"wave_accounting: {path} is missing — the unclaimed lane cannot "
                             "be measured without the ghidra inventory")
        out = []
        with path.open(newline="", encoding="utf-8") as handle:
            for row in csv.DictReader(handle):
                rva, size = int(row["rva"], 16), int(row["size"])
                self.ghidra_names[rva] = row["name"]
                if rva < self.text_start or rva + size > self.text_end or size < 3:
                    continue
                if not overlaps(rva, size):
                    out.append((rva, size))
        return out

    def subkind_totals(self):
        rows, byte_count = collections.Counter(), collections.Counter()
        for key, sub in self.not_held.items():
            rows[sub] += 1
            byte_count[sub] += key[1]
        return rows, byte_count


# --------------------------------------------------------------------------
# mechanisms — each returns {(rva, size): evidence}
# --------------------------------------------------------------------------

def mech_a(uni, image):
    """Reloc-free bodies that a held-lane row already reproduces byte for byte.

    Evidence is the list of held rows sharing those exact bytes, best lane
    first: any one of them is an owner the not-held copy can be claimed on.
    """
    has_rel32 = rel32_probe()
    groups = collections.defaultdict(lambda: ([], []))
    for key in uni.held:
        groups[image.body(*key)][0].append(key)
    for key in uni.not_held:
        groups[image.body(*key)][1].append(key)

    out = {}
    for body, (held, not_held) in groups.items():
        if not held or not not_held or has_rel32(body):
            continue
        models = sorted((row for key in held for row in uni.rows[key]), key=model_rank)
        for key in not_held:
            out[key] = models
    return out


def model_rank(row):
    """Best owner first: earliest lane, real TU before a prebuilt .lib."""
    return (progress.SOURCE_LANES.index(row["lane"]),
            Path(row["source"]).suffix.lower() in LIB_SUFFIXES,
            row["source"], row["name"])


def mech_b(uni, image, path):
    """ZH exact-multi placements that start at a not-held range's start."""
    sizes = collections.defaultdict(set)
    for entry in json.loads(Path(path).read_text(encoding="utf-8")):
        for address in entry["addresses"]:
            sizes[address].add(entry["size"])
    out = {}
    for (rva, size) in uni.not_held:
        if rva in sizes and any(abs(size - s) <= 3 for s in sizes[rva]):
            out[(rva, size)] = sorted(sizes[rva])
    return out


def small_classes(uni, image):
    """(tagged-by-C, {shape: [keys]}) over the <=16B dump ranges."""
    entries = G.load_ghidra()
    ownership, _ = G.funcinfo_ownership(entries)
    tagged, clusters = {}, collections.defaultdict(list)
    for (rva, size), sub in uni.not_held.items():
        if sub == "unclaimed" or size > G.SMALL_MAX:
            continue
        body = image.body(rva, size)
        if (size == 5 and body[0] == 0xE9) or (size == 6 and body[:2] == b"\xff\x25"):
            tagged[(rva, size)] = "thunk"
            continue
        try:
            skeleton, _ = G.match_skeleton(body, rva)
        except G.FormatError:
            skeleton = None
        if skeleton is not None:
            tagged[(rva, size)] = skeleton
        elif rva not in ownership:
            shape = G.shape(body)
            if shape is not None:
                clusters[shape].append((rva, size))
    return tagged, clusters, ownership


def mech_f(clusters, minimum=10):
    out = {}
    for shape, keys in clusters.items():
        if len(keys) < minimum:
            continue
        for key in keys:
            out[key] = f"{len(keys)} members"
    return out


def mech_de(uni, image, ownership):
    """Mid-size dump bodies whose instruction shape a matched held C++ row has."""
    models = collections.defaultdict(set)
    for row in B.load_all_function_rows():
        if row["status"] != "matched" or not row["source"].endswith(G.FAMILY_SOURCES):
            continue
        size = int(row["target_size"])
        if not G.FAMILY_MIN <= size <= G.FAMILY_MAX:
            continue
        rva = int(row["target_rva"], 16)
        if (rva, size) not in uni.held:
            continue
        shape = G.shape(image.body(rva, size))
        if shape is not None:
            models[shape].add(row["source"])

    d, e = {}, {}
    for (rva, size), sub in uni.not_held.items():
        if sub == "unclaimed" or not G.FAMILY_MIN <= size <= G.FAMILY_MAX or rva in ownership:
            continue
        shape = G.shape(image.body(rva, size))
        sources = models.get(shape)
        if not sources:
            continue
        target = d if any(s.startswith("Code/gen_small/") for s in sources) else e
        target[(rva, size)] = sorted(sources)[0]
    return d, e


def mech_g(uni, ownership):
    """FuncInfo-owned funclets, split by whether the owner is held or a dump."""
    rows_at = collections.defaultdict(list)
    for key, rows in uni.rows.items():
        for row in rows:
            rows_at[key[0]].append(row)

    def owner_kind(owner):
        held = dump = False
        for row in rows_at.get(owner, ()):
            key = (owner, row["size"])
            if key in uni.held and row["source"].endswith(G.FAMILY_SOURCES):
                held = True
            elif key in uni.not_held:
                dump = True
        return "held" if held else ("dump" if dump else "other")

    g1, g2 = {}, {}
    for (rva, size), sub in uni.not_held.items():
        if sub == "unclaimed" or rva not in ownership:
            continue
        kind = owner_kind(ownership[rva])
        if kind == "held":
            g1[(rva, size)] = f"owner 0x{ownership[rva]:08X}"
        elif kind == "dump":
            g2[(rva, size)] = f"owner 0x{ownership[rva]:08X}"
    return g1, g2


def mech_h(uni, path):
    """Masked .lib member matches, keyed to the range that starts where they do."""
    starts = {rva: (rva, size) for (rva, size) in uni.not_held}
    out, off_boundary = {}, 0
    with Path(path).open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            rva, size = int(row["rva"], 16), int(row["size"])
            key = starts.get(rva)
            if key is None:
                off_boundary += size
            else:
                out[key] = row.get("kind", "lib-member")
    if off_boundary:
        print(f"  H: {off_boundary:,d} B of matches start off any known range boundary "
              "and are not counted", file=sys.stderr)
    return out


def mech_i(uni, image):
    """Unclaimed Unwind@/Catch@ funclets with the mov[/add]/jmp shape gen_uw emits."""
    try:
        import capstone
    except ImportError as exc:
        raise SystemExit(f"wave_accounting: capstone is required for mechanism I ({exc})")
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    out = {}
    for (rva, size), sub in uni.not_held.items():
        if sub != "unclaimed":
            continue
        if not uni.ghidra_names.get(rva, "").startswith(("Unwind@", "Catch@")):
            continue
        body = image.body(rva, size)
        # gen_uw already owns its own A/B/C ladder shapes; those are not new work.
        if size == 8 and body[0] == 0x8D and body[1] == 0x4D and body[3] == 0xE9:
            continue
        if (size == 11 and body[0] == 0x8B and body[1] == 0x45 and body[3] == 0x50
                and body[4] == 0xE8 and body[9] == 0x59 and body[10] == 0xC3):
            continue
        decoded, mnemonics = 0, []
        for ins in md.disasm(body, 0):
            decoded += len(ins.bytes)
            mnemonics.append(ins.mnemonic)
        if decoded < len(body):
            continue
        shape = " ".join(mnemonics)
        if shape in ("mov add jmp", "mov jmp"):
            out[(rva, size)] = shape
    return out


def compute(mechs, uni, image, args):
    """{mech: {(rva, size): evidence}} for exactly the mechanisms asked for."""
    for mech in mechs:
        flag = EVIDENCE_FLAG.get(mech)
        if flag and not getattr(args, flag.lstrip("-").replace("-", "_")):
            raise SystemExit(f"wave_accounting: mechanism {mech} cannot be derived from this "
                             f"repository — it needs the evidence file behind {flag}. "
                             f"Pass it, or drop {mech} from --mech.")
    tags = {}
    if "A" in mechs:
        tags["A"] = mech_a(uni, image)
    if "B" in mechs:
        tags["B"] = mech_b(uni, image, args.zh_exact_multi)
    ownership = None
    if {"C", "F", "D", "E"} & set(mechs):
        tagged, clusters, ownership = small_classes(uni, image)
        if "C" in mechs:
            tags["C"] = tagged
        if "F" in mechs:
            tags["F"] = mech_f(clusters)
    if {"D", "E", "G1", "G2"} & set(mechs) and ownership is None:
        ownership, _ = G.funcinfo_ownership(G.load_ghidra())
    if {"D", "E"} & set(mechs):
        d, e = mech_de(uni, image, ownership)
        if "D" in mechs:
            tags["D"] = d
        if "E" in mechs:
            tags["E"] = e
    if {"G1", "G2"} & set(mechs):
        g1, g2 = mech_g(uni, ownership)
        if "G1" in mechs:
            tags["G1"] = g1
        if "G2" in mechs:
            tags["G2"] = g2
    if "H" in mechs:
        tags["H"] = mech_h(uni, args.lib_matches)
    if "I" in mechs:
        tags["I"] = mech_i(uni, image)
    return tags


# --------------------------------------------------------------------------
# report
# --------------------------------------------------------------------------

def merged_bytes(keys):
    total, last_end = 0, -1
    for rva, size in sorted(keys):
        end = rva + size
        if rva > last_end:
            total += size
            last_end = end
        elif end > last_end:
            total += end - last_end
            last_end = end
    return total


def cmd_report(args):
    mechs = parse_mechs(args.mech, default=SELF_CONTAINED)
    uni = Universe()
    image = Image()
    rows, byte_count = uni.subkind_totals()
    print("not-held universe (unique .text ranges):")
    for sub in SUBKINDS:
        print(f"  {sub:10s} {rows[sub]:7d} ranges {byte_count[sub]:11,d} B")
    print(f"  {'TOTAL':10s} {sum(rows.values()):7d} ranges {sum(byte_count.values()):11,d} B")

    tags = compute(mechs, uni, image, args)
    print(f"\nmechanisms: {', '.join(mechs)}")
    print(f"{'mech':6s} {'ranges':>8s} {'bytes':>12s} {'exclusive':>12s}   by subkind")
    union = merged_bytes({key for keys in tags.values() for key in keys})
    for mech in mechs:
        keys = tags[mech]
        others = {key for other in mechs if other != mech for key in tags[other]}
        by_sub = collections.Counter()
        for key in keys:
            by_sub[uni.not_held[key]] += key[1]
        detail = ", ".join(f"{sub}={by_sub[sub]:,d}" for sub in SUBKINDS if by_sub[sub])
        print(f"{mech:6s} {len(keys):8d} {merged_bytes(keys):12,d} "
              f"{union - merged_bytes(others):12,d}   {detail}")
    print(f"{'UNION':6s} {'':8s} {union:12,d}")
    denominator = real_code_bytes()
    print(f"\nunion is +{union / denominator * 100:.2f} pp of the {denominator:,d} B of real "
          "code, the denominator progress.py reports against")


def real_code_bytes():
    """.text minus its 0xCC padding — progress.py's own denominator.

    Taken from progress.py rather than summed out of this tool's universe: the
    two sets do not add up (padding, and ranges no lane covers), so a locally
    derived denominator would print pp that quietly mean something else than the
    headline metric's pp.
    """
    text_start, text_size = progress.retail_text()
    _padding, denominator = progress.real_code_denominator(text_start, text_size)
    return denominator


# --------------------------------------------------------------------------
# wave emission
# --------------------------------------------------------------------------

def object_symbol(row):
    """The COFF symbol whose bytes this row is verified against."""
    match = OBJECT_SYMBOL_RE.search(row["notes"])
    return match.group(1) if match else row["name"]


def alias_owners(models, limit):
    """[(source, notes)] owners for an alias row, best first, deduplicated."""
    owners, seen = [], set()
    for row in models:
        if Path(row["source"]).suffix.lower() in LIB_SUFFIXES:
            continue  # a .lib row is compared masked; it proves too little to alias
        key = (row["source"], object_symbol(row))
        if key in seen:
            continue
        seen.add(key)
        owners.append((row["source"],
                       f"{ALIAS_NOTE_PREFIX}object-symbol={key[1]};{ALIAS_NOTE}"))
        if len(owners) > limit:
            break
    return owners


def cmd_wave(args):
    if args.mech != "A":
        raise SystemExit(f"wave_accounting: mechanism {args.mech} has no landing recipe here — "
                         "only A lands as plain rows on a TU that already compiles. B/C/D/E/F/"
                         "G/I must emit source first (tools/gen_small.py), H must attach a "
                         "library member.")
    uni = Universe()
    image = Image()
    candidates = mech_a(uni, image)

    ledger_names = {row["name"] for rows in uni.rows.values() for row in rows}
    wanted = {"genasm"} | ({"unclaimed"} if args.include_unclaimed else set())
    picked, skipped = [], collections.Counter()
    for key, models in sorted(candidates.items()):
        rva, size = key
        sub = uni.not_held[key]
        if sub not in wanted:
            skipped[f"subkind {sub} not requested"] += 1
            continue
        if size < args.min_size:
            skipped[f"smaller than --min-size {args.min_size}"] += 1
            continue
        here = uni.rows.get(key, [])
        if sub == "genasm":
            # validate_rows supersedes exactly one Code/gen_asm/ row of the same
            # extent. Anything else at this address is a boundary dispute, and a
            # single one of them would abort the whole wave.
            if len(here) != 1 or not here[0]["source"].startswith(G.DUMP_DIR_PREFIX):
                skipped["address carries more than a lone gen_asm dump row"] += 1
                continue
        elif here:
            skipped["unclaimed range already carries a row"] += 1
            continue
        owners = alias_owners(models, args.alternates)
        if not owners:
            skipped["every twin lives in a prebuilt .lib"] += 1
            continue
        name = G.thunk_symbol("a", rva)
        if name in ledger_names:
            skipped[f"{name} already in the ledger"] += 1
            continue
        picked.append({"name": name, "rva": rva, "size": size, "owners": owners})

    # Concentrate a wave on as few TUs as possible: the gate recompiles and
    # re-verifies every row of every TU a wave touches, so twenty rows spread
    # over twenty TUs cost twenty full-TU verifies to prove the same bytes.
    by_source = collections.defaultdict(list)
    for row in picked:
        by_source[row["owners"][0][0]].append(row)
    order = sorted(by_source, key=lambda s: (-len(by_source[s]), s))
    if args.max_sources:
        order = order[:args.max_sources]
    wave = []
    for source in order:
        for row in sorted(by_source[source], key=lambda r: r["rva"]):
            if args.limit and len(wave) >= args.limit:
                break
            wave.append(row)
        if args.limit and len(wave) >= args.limit:
            break

    if not wave:
        raise SystemExit("wave_accounting: mechanism A produced no landable row under these "
                         f"filters ({len(candidates)} tagged range(s); skipped: "
                         + ", ".join(f"{n} {reason}" for reason, n in skipped.most_common())
                         + ")")

    columns = ["name", "rva", "size", "source", "notes"]
    depth = max(len(row["owners"]) for row in wave)
    for i in range(1, depth):
        columns += [f"alt{i}_source", f"alt{i}_notes"]
    out = Path(args.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    with out.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, columns, lineterminator="\n")
        writer.writeheader()
        for row in wave:
            record = {"name": row["name"], "rva": f"0x{row['rva']:08X}", "size": row["size"],
                      "source": row["owners"][0][0], "notes": row["owners"][0][1]}
            for i, (source, notes) in enumerate(row["owners"][1:], start=1):
                record[f"alt{i}_source"] = source
                record[f"alt{i}_notes"] = notes
            writer.writerow(record)

    total = sum(row["size"] for row in wave)
    print(f"wave_accounting: {len(wave)} row(s), {total:,d} byte(s) over "
          f"{len({r['owners'][0][0] for r in wave})} TU(s) -> {out}")
    print(f"  mechanism A tagged {len(candidates)} range(s) "
          f"({merged_bytes(candidates):,d} B) at HEAD")
    for reason, count in skipped.most_common():
        print(f"  skipped {count}: {reason}")


def parse_mechs(value, default):
    if not value:
        return list(default)
    mechs = [m.strip().upper() for m in value.split(",") if m.strip()]
    unknown = [m for m in mechs if m not in ALL_MECHS]
    if unknown:
        raise SystemExit(f"wave_accounting: unknown mechanism(s) {', '.join(unknown)}; "
                         f"known: {', '.join(ALL_MECHS)}")
    return mechs


def main(argv=None):
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)

    report = sub.add_parser("report", help="per-mechanism accounting over the not-held universe")
    report.add_argument("--mech", help=f"comma-separated subset (default: "
                                       f"{','.join(SELF_CONTAINED)})")
    report.add_argument("--zh-exact-multi", help="JSON placement index required by mechanism B")
    report.add_argument("--lib-matches", help="lib_matches.csv required by mechanism H")
    report.set_defaults(func=cmd_report)

    wave = sub.add_parser("wave", help="write a wave CSV for tools/land_wave.py")
    wave.add_argument("--mech", required=True, help="mechanism to emit (only A lands as rows)")
    wave.add_argument("--out", required=True, help="destination CSV")
    wave.add_argument("--limit", type=int, default=0, help="stop after this many rows")
    wave.add_argument("--min-size", type=int, default=1, help="skip bodies smaller than this")
    wave.add_argument("--max-sources", type=int, default=0,
                      help="draw from at most this many owner TUs")
    wave.add_argument("--alternates", type=int, default=2,
                      help="alternate owner TUs to record per row for the retry path")
    wave.add_argument("--include-unclaimed", action="store_true",
                      help="also claim ranges no ledger row covers (boundary from ghidra only)")
    wave.set_defaults(func=cmd_wave)

    args = parser.parse_args(argv)
    args.func(args)


if __name__ == "__main__":
    main()
