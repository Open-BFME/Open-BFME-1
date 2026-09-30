#!/usr/bin/env python3
"""Check that each cleanup-funclet pin binds retail's unwind state, not just its bytes.

A funclet row names a compiler label (`$L4571`, via `object-symbol=` or as its
row name). Several labels in one object are often byte-identical -- the same
destructor call for two temporaries -- so a byte gate accepts any of them and
label renumbering after a header change can silently rebind a row to another
unwind state. This check decides the label from the EH tables instead:

  object  parent P's section relocates `push offset H` to its EH handler stub
          H (`mov eax, offset FuncInfo; jmp ___CxxFrameHandler`); FuncInfo
          (magic 0x19930520) -> unwind map; entry s = (toState, action label).
  retail  the same relocation offsets read in retail's bytes at P's ledgered
          address give H, then FuncInfo, then the unwind map; entry s =
          (toState, action address). maxState and every toState must agree.
  verdict for a row at retail address F pinned to label L: the labels at every
          state whose retail action is F. `proven` when that is exactly {L},
          `wrong` when L is another label of the object, `stale` when the
          object no longer defines L (build.py then re-finds the body by bytes
          alone; the fix for both is the state's label),
          `split` when retail's states for F carry several distinct labels,
          `unprovable` when no parent with a ledgered address, matching
          tables and F among its actions exists in the object.
A pin is `ambiguous` when another label in its section has the same bytes and
the same relocation targets (what the byte gate alone cannot separate).

  python3 tools/eh_state_pins.py [--commit SHA | --source FILE ...] [--objects-root DIR]
      [--fix --model M]      # repoint wrong/stale rows' labels (apply_fixes)

Objects come from build/match (build.py's output); a row whose object is
missing is `unprovable (no object)`, never skipped. Report: build/eh_state_pins/.
"""
import argparse
import collections
import csv
import io
import json
import re
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
from reloc_ledger import parse_coff  # noqa: E402

OUT = ROOT / "build" / "eh_state_pins"
EH_MAGIC = 0x19930520
DIR32 = 0x0006
LABEL = re.compile(r"^\$L\d+$")
OBJECT_SYMBOL = re.compile(r"(?:^|;)object-symbol=([^;]+)")


class Obj:
    """One COFF object: symbols by name, relocation lookups, EH tables."""

    def __init__(self, data):
        self.sections, self.symbols = parse_coff(data)
        self.defined = collections.defaultdict(list)
        for s in self.symbols.values():
            if s["section"] > 0:
                self.defined[s["name"]].append(s)
        self.reloc = {}
        for sec in self.sections:
            for where, index, kind in sec["relocs"]:
                self.reloc[(sec["number"], where)] = (self.symbols[index], kind)

    def target(self, section, offset):
        hit = self.reloc.get((section, offset))
        return hit[0] if hit and hit[1] == DIR32 else None

    def u32(self, sym, offset=0):
        body = self.sections[sym["section"] - 1]["body"]
        return struct.unpack_from("<I", body, sym["value"] + offset)[0]

    def handler_of(self, parent):
        """(offset in parent, handler symbol, FuncInfo symbol) for each EH
        handler stub the parent's code references."""
        sec = self.sections[parent["section"] - 1]
        out = []
        for where, index, kind in sec["relocs"]:
            h = self.symbols[index]
            if kind != DIR32 or h["section"] <= 0 or where < parent["value"]:
                continue
            hbody = self.sections[h["section"] - 1]["body"]
            if not hbody or hbody[h["value"]:h["value"] + 1] != b"\xB8":
                continue
            fi = self.target(h["section"], h["value"] + 1)
            if fi and fi["section"] > 0 and self.sections[fi["section"] - 1]["body"] \
                    and self.u32(fi) == EH_MAGIC:
                out.append((where - parent["value"], h, fi))
        return out

    def unwind(self, fi):
        """[(toState, action symbol name or None)] of a FuncInfo."""
        states = self.u32(fi, 4)
        umap = self.target(fi["section"], fi["value"] + 8)
        if umap is None:
            return []
        rows = []
        for s in range(states):
            to = struct.unpack("<i", struct.pack("<I", self.u32(umap, 8 * s)))[0]
            action = self.target(umap["section"], umap["value"] + 8 * s + 4)
            rows.append((to, action["name"] if action else None))
        return rows

    def signature(self, label):
        """Bytes of a label's code up to the next symbol in its section, with
        each relocation field replaced by its target name."""
        sym = self.defined[label][0]
        sec = self.sections[sym["section"] - 1]
        later = sorted({s["value"] for s in self.symbols.values()
                        if s["section"] == sym["section"] and s["value"] > sym["value"]})
        end = later[0] if later else sec["size"]
        body = bytearray(sec["body"][sym["value"]:end])
        names = []
        for where in range(sym["value"], end):
            hit = self.reloc.get((sym["section"], where))
            if hit:
                body[where - sym["value"]:where - sym["value"] + 4] = b"\0\0\0\0"
                names.append((where - sym["value"], hit[0]["name"], hit[1]))
        return bytes(body), tuple(names)


class Retail:
    def __init__(self, exe=build.EXE):
        import pefile
        pe = pefile.PE(str(exe), fast_load=True)
        self.base = pe.OPTIONAL_HEADER.ImageBase
        self.image = pe.get_memory_mapped_image()

    def u32(self, rva):
        if rva < 0 or rva + 4 > len(self.image):
            return None
        return struct.unpack_from("<I", self.image, rva)[0]

    def action_index(self):
        """{action rva: [(FuncInfo rva, state)]} over every FuncInfo in the image
        (magic dword, sane maxState, unwind map inside the image)."""
        if getattr(self, "_actions", None) is None:
            self._actions = collections.defaultdict(list)
            magic = struct.pack("<I", EH_MAGIC)
            at = self.image.find(magic)
            while at != -1:
                states, umap = self.u32(at + 4), self.u32(at + 8)
                inside = umap and 0 < umap - self.base < len(self.image) - 8 * (states or 0)
                if at % 4 == 0 and states and states < 4096 and inside:
                    for s in range(states):
                        action = self.u32(umap - self.base + 8 * s + 4)
                        if action:
                            self._actions[action - self.base].append((at, s))
                at = self.image.find(magic, at + 4)
        return self._actions

    def unwind(self, parent_rva, handler_offset):
        """[(toState, action rva or None)] reached from the parent's retail bytes."""
        h = self.u32(parent_rva + handler_offset)
        if h is None:
            return None
        h -= self.base
        if self.image[h:h + 1] != b"\xB8":
            return None
        fi = self.u32(h + 1)
        if fi is None or self.u32(fi - self.base) != EH_MAGIC:
            return None
        fi -= self.base
        states, umap = self.u32(fi + 4), self.u32(fi + 8)
        if umap is None or states is None or states > 4096:
            return None
        umap -= self.base
        out = []
        for s in range(states):
            to, action = self.u32(umap + 8 * s), self.u32(umap + 8 * s + 4)
            if to is None:
                return None
            out.append((struct.unpack("<i", struct.pack("<I", to))[0], action - self.base if action else None))
        return out


def label_of(row):
    m = OBJECT_SYMBOL.search(row.get("notes") or "")
    name = m.group(1) if m else row["name"]
    return name if LABEL.match(name) else None


def tables(obj, rows_by_symbol, retail):
    """[{parent, ours, theirs}] for every ledgered parent in the object that has
    an EH handler; `theirs` is None when retail's bytes do not lead to a FuncInfo."""
    out = []
    for name, rva in rows_by_symbol.items():
        for parent in obj.defined.get(name, [])[:1]:
            if not obj.sections[parent["section"] - 1]["flags"] & 0x20:
                continue
            for offset, _, fi in obj.handler_of(parent):
                out.append({"parent": name, "ours": obj.unwind(fi), "theirs": retail.unwind(rva, offset)})
    return out


def judge(obj, eh_tables, row, label):
    """Verdict dict for one funclet row (see module doc)."""
    f = int(row["target_rva"], 16)
    found = []
    for t in eh_tables:
        ours, theirs = t["ours"], t["theirs"]
        if not theirs or not any(a == f for _, a in theirs):
            continue
        if [x for x, _ in ours] != [x for x, _ in theirs]:
            found.append({"parent": t["parent"], "tables": "differ"})
            continue
        states = [i for i, (_, a) in enumerate(theirs) if a == f]
        found.append({"parent": t["parent"], "states": states, "labels": sorted({ours[i][1] for i in states})})
    agreeing = [x for x in found if "labels" in x]
    labels = sorted({lab for x in agreeing for lab in x["labels"]})
    present = label in obj.defined
    # the look-alikes of the pinned label, or of the state's label when the pin is gone
    probe = label if present else (labels[0] if len(labels) == 1 and labels[0] in obj.defined else None)
    twins = []
    if probe:
        sig = obj.signature(probe)
        twins = sorted(n for n in obj.defined if LABEL.match(n) and n != probe and obj.signature(n) == sig)
    base = {"twins": twins, "ambiguous": bool(twins), "parents": found, "pin_defined": present}
    if not agreeing:
        why = "tables differ" if found else "no ledgered parent in this object reaches this address"
        return {**base, "verdict": "unprovable", "why": why}
    if labels == [label]:
        return {**base, "verdict": "proven"}
    if len(labels) > 1:
        return {**base, "verdict": "split", "labels": labels}
    return {**base, "verdict": "wrong" if present else "stale", "correct": labels[0]}


def apply_fixes(fixes, model):
    """Repoint each row's object-symbol label to its state's label, under
    add_match's ledger lock, then byte-verify every touched source (build.py,
    at most 8 sources per call); any failure restores the ledger untouched.

    Only the notes field changes, and only in rows whose object-symbol names
    the old label and that hold no quoted field; anything else is reported."""
    import ledger_io
    from portable_lock import lock, unlock
    functions = build.FUNCTIONS
    lock_file = (functions.parent / ".add_match.lock").open("a")
    lock(lock_file, exclusive=True, wait_notice="eh_state_pins: waiting for the ledger lock...")
    try:
        raw = functions.read_bytes()
        out, sources, skipped = [], set(), []
        for payload, term in ledger_io.split_records(raw):
            f = ledger_io.fields(payload)
            key = (f[0], int(f[2], 16)) if len(f) > 6 and f[2].startswith("0x") else None
            if key in fixes:
                old, new, states = fixes.pop(key)
                tag = f"object-symbol={old}"
                if b'"' in payload or tag not in f[6].split(";"):
                    skipped.append(f"{f[0]} 0x{key[1]:08X}")
                else:
                    notes = ";".join(f"object-symbol={new}" if n == tag else n for n in f[6].split(";"))
                    evidence = (f"eh-state-pin {old}->{new}: retail unwind map ({states}) binds this address "
                                f"to {new};repin-model={model}").replace(",", " ")
                    f[6] = f"{notes};{evidence}"
                    payload = ",".join(f).encode("utf-8")
                    sources.add(f[4])
            out.append(payload + term)
        skipped += [f"{n} 0x{r:08X} (row not found)" for n, r in fixes]
        ledger_io.atomic_write_bytes(functions, b"".join(out))
        ordered = sorted(sources)
        failed = []
        for i in range(0, len(ordered), 8):
            batch = ordered[i:i + 8]
            proc = subprocess.run([sys.executable, str(ROOT / "tools" / "build.py"), *batch], cwd=ROOT,
                                  capture_output=True, text=True)
            if proc.returncode:
                failed.append((batch, proc.stdout[-2000:] + proc.stderr[-1000:]))
                break
        if failed:
            ledger_io.atomic_write_bytes(functions, raw)
            raise SystemExit("eh_state_pins: verification failed, ledger restored:\n" + failed[0][1])
        print(f"repinned rows in {len(sources)} source(s), all byte-verified; skipped {len(skipped)}")
        for line in skipped:
            print(f"  skipped {line}")
    finally:
        unlock(lock_file)
        lock_file.close()


def rows_from_commit(sha):
    """Funclet rows a commit added or changed, as they stand now."""
    diff = subprocess.run(["git", "show", sha, "--format=", "--", "targets/game/reverse/functions.csv"],
                          cwd=ROOT, capture_output=True, text=True, encoding="utf-8").stdout
    keys = set()
    for line in diff.splitlines():
        if line.startswith("+") and not line.startswith("+++"):
            parts = next(csv.reader(io.StringIO(line[1:])))
            if len(parts) > 3:
                keys.add(parts[2].upper())
    return keys


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--commit", help="only rows this commit added or changed")
    ap.add_argument("--source", action="append", default=[], help="only rows of this source")
    ap.add_argument("--objects-root", type=Path, help="checkout whose build/match holds the objects")
    ap.add_argument("--out", type=Path, default=OUT)
    ap.add_argument("--fix", action="store_true", help="repoint `wrong` rows (add_match --replace-existing)")
    ap.add_argument("--model")
    args = ap.parse_args(argv)
    if args.fix and not args.model:
        ap.error("--fix needs --model")
    rows = build.load_function_rows()
    wanted_rvas = rows_from_commit(args.commit) if args.commit else None
    targets = [r for r in rows if label_of(r) and (wanted_rvas is None or r["target_rva"].upper() in wanted_rvas)
               and (not args.source or r["source"] in args.source)]
    by_object = collections.defaultdict(list)
    for r in rows:
        try:
            by_object[build.row_object(r)].append(r)
        except SystemExit:
            continue
    retail = Retail()
    results, cache = [], {}
    for row in targets:
        obj_path = build.row_object(row)
        if args.objects_root:
            obj_path = args.objects_root / obj_path.relative_to(ROOT)
        if obj_path not in cache:
            obj = Obj(obj_path.read_bytes()) if obj_path.exists() else None
            local = {build.ledger_object_symbol(r): int(r["target_rva"], 16) for r in by_object[build.row_object(row)]
                     if not label_of(r)}
            cache[obj_path] = (obj, tables(obj, local, retail) if obj else None)
        obj, eh_tables = cache[obj_path]
        label = label_of(row)
        if obj is None:
            verdict = {"verdict": "unprovable", "why": "no object", "ambiguous": None}
        else:
            verdict = judge(obj, eh_tables, row, label)
        if verdict["verdict"] == "unprovable":
            # what retail itself binds the address to, for whoever repairs the row
            verdict["retail_states"] = [f"FuncInfo 0x{fi:08X} state {st}" for fi, st in
                                        retail.action_index().get(int(row["target_rva"], 16), [])]
        results.append({"name": row["name"], "rva": row["target_rva"], "source": row["source"], "label": label,
                        **verdict})
    args.out.mkdir(parents=True, exist_ok=True)
    (args.out / "report.json").write_text(json.dumps(results, indent=1), encoding="utf-8")
    table = collections.Counter((r["verdict"], "ambiguous" if r.get("ambiguous") else
                                 ("unique" if r.get("ambiguous") is False else "unknown")) for r in results)
    print(f"{len(results)} funclet pin(s)")
    for (verdict, kind), n in sorted(table.items()):
        print(f"  {verdict:10} {kind:9} {n}")
    for r in results:
        if r["verdict"] in ("wrong", "split") or (r["verdict"] == "stale" and r.get("ambiguous")):
            print(f"  {r['verdict']}: {r['rva']} {r['name']} pinned {r['label']} -> "
                  f"{r.get('correct') or r.get('labels')} ({r['source']})")
    if args.fix:
        fixes = {}
        for r in results:
            if r["verdict"] in ("wrong", "stale"):
                states = "; ".join(f"{p['parent']} states {p['states']}" for p in r["parents"] if "states" in p)
                fixes[(r["name"], int(r["rva"], 16))] = (r["label"], r["correct"], states)
        apply_fixes(fixes, args.model)
    return 1 if any(r["verdict"] in ("wrong", "stale", "split") for r in results) else 0


if __name__ == "__main__":
    sys.exit(main())
