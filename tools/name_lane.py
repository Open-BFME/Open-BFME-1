#!/usr/bin/env python3
"""Name what no binary names. Any model proposes names; a name lands only when a model from a
different vendor proposed the same one independently.

    python3 tools/name_lane.py next --model MODEL     one file of placeholder names, with evidence
    python3 tools/name_lane.py submit ANSWER.json --session ID
    python3 tools/name_lane.py apply                  land agreed names, byte-gated, one commit per file
    python3 tools/name_lane.py status                 readable-names progress
    python3 tools/name_lane.py check --staged         (pre-commit) placeholders renamed by hand

Why two models: in the 2026-09-29 spike (targets/game/reverse/analysis/naming_spikes.md) a name
two different models proposed independently was accurate 80% of the time and never misleading;
one model alone was about 60% accurate and 2-9% misleading. Models from one vendor share
training data, so their agreement is weaker evidence. Votes are stored as hashes salted with
their key, so a session cannot copy an earlier proposal to fake agreement: a name's text enters
the repo only once a second vendor matches it.
"""
import argparse
import collections
import csv
import datetime
import difflib
import functools
import hashlib
import io
import json
import random
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import readability_metric as RM  # noqa: E402

REVERSE = ROOT / "targets/game/reverse"
VOTES, AGREED = REVERSE / "name_votes.csv", REVERSE / "name_agreed.csv"
LEDGER = REVERSE / "functions.csv"
STORED = [LEDGER, REVERSE / "symbols.csv", REVERSE / "dir32_addresses.csv"]
TOMBSTONES, ADOPT_BLOCKED = REVERSE / "deleted_rows.csv", REVERSE / "header_adopt_blocked.tsv"
CORRECTIONS, DISPUTES = REVERSE / "name_corrections.json", REVERSE / "identity_evidence/name-lane-disputes.md"
EA = REVERSE / "ea_evidence.csv"
ZH = ROOT / "inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code"   # ea_evidence.ZH, without its pefile import
SESSIONS = ROOT / "build/name_lane"
GENERATED = ("game/gen_asm/", "game/gen_small/")
COLUMNS = {VOTES: ["key", "hash", "model", "session", "date"], AGREED: ["key", "name", "models", "status", "date"]}

NONCODE = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', re.S)
WORD = re.compile(r"\b[A-Za-z_]\w*\b")
DECL = re.compile(r"^[ \t]*(?:class|struct)[ \t]+([A-Za-z_]\w*)\b[^;{()]*\{", re.M)
ENUM = re.compile(r"^[ \t]*enum[ \t]+([A-Za-z_]\w*)\b[^;{()]*\{", re.M)
BRACE = re.compile(r"[{}]")
PREPROCESSOR = re.compile(r"^[ \t]*#(?:[^\n]*\\\n)*[^\n]*", re.M)
LOCAL = re.compile(r"(?:^|[;{}(])\s*(?:(?:const|static|unsigned|signed|struct|class)\s+)*"
                   r"([A-Za-z_][\w:]*)[\s*&]+([A-Za-z_]\w*)\s*(?=[=;\[,)])")
FUNC = re.compile(r"^[ \t]*(?:[A-Za-z_][\w:<>,*& \t]*?[\s*&])?((?:[A-Za-z_]\w*::)*)(~?[A-Za-z_]\w*)[ \t]*"
                  r"\(([^;{}()]*(?:\([^()]*\)[^;{}()]*)*)\)\s*(?:const\s*)?(?::[^;{]*)?\{", re.M)
MANGLED = re.compile(r"\?([A-Za-z_]\w*)@((?:[A-Za-z_]\w*@)*)@")
FAMILY = re.compile(r"(?:a|d|dup|sub|uw|eh|tg|fun|nullsub|loc|j)_[0-9A-Fa-f]+")
OFFSET = re.compile(r"(?:m_)?[a-z][A-Za-z]*?_?(?:0x)?(?=[0-9a-fA-F]*\d)[0-9a-fA-F]{2,}")
OPAQUE = re.compile(r"[a-z]{1,2}Var\d+|local_[0-9a-fA-F]+|param_\d+|(?:in|extraout)_[A-Z]{2,3}|[av]\d{1,2}")
HEXRUN = re.compile(r"(?i)(?=(?:[0-9a-f]*\d){3})[0-9a-f]{6,8}")
# Calibrated on 300 sampled parameters and locals against a blind gpt-5.6-sol judge (agreed on 284).
WEAK_LOCAL = re.compile(r"(?i)[a-hl-z]|(?:tmp|temp)\w*|arg(?:ument)?\d*|[a-z]{1,2}\d+")
PAD = re.compile(r"(?:m_)?_?(?:pad|padding|gap|unused|reserved|filler|spare)", re.I)
KEYWORDS = set("""alignas alignof asm auto bool break case catch char class const const_cast continue default delete do
double dynamic_cast else enum explicit export extern false float for friend goto if inline int long mutable namespace new
operator private protected public register reinterpret_cast return short signed sizeof static static_cast struct switch
template this throw true try typedef typeid typename union unsigned using virtual void volatile wchar_t while NULL
__cdecl __stdcall __thiscall __fastcall __declspec __int64 __asm""".split())
GENERIC = {"data", "info", "value", "temp", "tmp", "helper", "thing", "stuff", "foo", "bar", "obj", "var", "func",
           "method", "unknown", "misc", "item", "object", "result", "ret", "field", "member", "param", "arg", "local"}
SYNONYMS = {"num": "count", "number": "count", "cnt": "count", "idx": "index", "len": "length", "pos": "position",
            "str": "string", "msg": "message", "btn": "button", "wnd": "window", "tex": "texture", "obj": "object"}
CLAUDE = ("opus", "sonnet", "haiku", "fable")
OTHERS = ("grok", "gemini", "llama", "qwen", "deepseek", "kimi", "glm", "mistral")
VENDORS = {"claude": "anthropic", "gpt": "openai", "o": "openai", "grok": "xai", "gemini": "google", "llama": "meta",
           "qwen": "alibaba", "deepseek": "deepseek", "kimi": "moonshot", "glm": "zhipu", "mistral": "mistral"}
NAMED = ("type", "member", "function")


def fail(message):
    sys.exit(f"name_lane: {message}")


@functools.lru_cache(maxsize=None)
def placeholder(word):
    """A name a converter invented: address-derived, Bfme*, an offset suffix, or a decompiler local."""
    return bool(RM.ADDRESSED.fullmatch(word) or re.search(r"(?i)(^|_)bfme", word) or re.search(r"[0-9A-F]{6,8}", word)
                or HEXRUN.search(word) or (OFFSET.fullmatch(word) and not PAD.match(word)) or OPAQUE.fullmatch(word))


def weak(kind, name):
    """A placeholder, or for a parameter or local also a single letter other than a loop counter,
    tmp/temp, arg, or a letter-and-digit stub (t2, e1)."""
    return placeholder(name) or (kind in ("param", "local") and bool(WEAK_LOCAL.fullmatch(name)))


def model_id(text):
    t = text.lower()
    for family in CLAUDE + OTHERS:
        if family in t:
            return f"claude-{family}" if family in CLAUDE else family
    m = re.search(r"gpt-[\w.-]+|\bo\d\b", t)
    if not m:
        fail(f"unknown model {text!r}: pass the model you are, e.g. opus, sonnet, haiku, gpt-5.6-sol, grok")
    return m.group(0)


def vendor(model):
    return VENDORS[re.match(r"[a-z]+", model).group(0)]


def git(*args, check=True):
    return subprocess.run(["git", *args], cwd=ROOT, capture_output=True,
                          text=True, encoding="utf-8", errors="replace", check=check).stdout


def read(rel):
    return (ROOT / rel).read_text(encoding="utf-8", errors="replace")


def strip(text):
    """Comments and literals blanked in place, so offsets into the result are offsets into text."""
    return NONCODE.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)), text)


def table(path):
    if not path.exists():
        return []
    rows = list(csv.DictReader(io.StringIO(path.read_text(encoding="utf-8"))))
    if rows and list(rows[0]) != COLUMNS[path]:
        fail(f"{path.name} has columns {list(rows[0])}, expected {COLUMNS[path]}")
    return rows


def append(path, rows):
    new = not path.exists()
    with path.open("a", encoding="utf-8", newline="") as f:
        w = csv.DictWriter(f, COLUMNS[path], lineterminator="\n")
        if new:
            w.writeheader()
        w.writerows(rows)


def agreed_state():
    """key -> row. Rows are append-only (union merges); disputed beats applied beats blocked beats stale
    beats agreed."""
    rank = {"agreed": 0, "stale": 1, "blocked": 2, "applied": 3, "disputed": 4}
    state = {}
    for a in table(AGREED):
        if a["key"] not in state or rank[a["status"].split(":")[0]] >= rank[state[a["key"]]["status"].split(":")[0]]:
            state[a["key"]] = a
    return state


def canon(name):
    """Word order, plurals and common abbreviations are style, not meaning: m_ladderComboBox
    and m_comboBoxLadder are one vote."""
    words = re.findall(r"[A-Z]+(?![a-z])|[A-Z]?[a-z]+|\d+", re.sub(r"^m_", "", name))
    words = [SYNONYMS.get(w.lower(), w.lower()) for w in words]
    return " ".join(sorted(w[:-1] if len(w) > 3 and w.endswith("s") else w for w in words))


def wins(mine, rivals):
    """Models from two vendors agree, and the name leads every rival by two votes: when another model
    named the thing differently, two models sharing a guess is not enough."""
    return len({vendor(m) for m in mine}) >= 2 and len(mine) - max(map(len, rivals), default=0) >= 2


def open_key(state, key):
    return key not in state or state[key]["status"].startswith("disputed")


def digest(key, name):
    return hashlib.sha256(f"{key}|{canon(name)}".encode()).hexdigest()[:24]


@functools.lru_cache(maxsize=None)
def spellings():
    known = collections.defaultdict(set)
    texts = [p.read_text(encoding="latin1") for p in ZH.rglob("*") if p.suffix.lower() in (".h", ".cpp", ".inl")]
    for text in texts + [EA.read_text(encoding="utf-8")]:
        for w in set(WORD.findall(text)):
            known[canon(w)].add(w)
    return known


def spelling(name, kind):
    """EA's or Zero Hour's own spelling of an agreed name when exactly one fits the kind: votes
    match case-blind, so otherwise the second voter's casing would land."""
    fits = [w for w in spellings().get(canon(name), ()) if not problem(kind, "", w, set(), collections.Counter())]
    return fits[0] if len(fits) == 1 else name


# ------------------------------------------------------------------ what a file owns

def close(code, brace):
    depth = 0
    for m in BRACE.finditer(code, brace):
        depth += 1 if m.group() == "{" else -1
        if depth == 0:
            return m.start()
    return len(code)


def functions_in(code):
    """[(scope, start, end, params)]: every function body; a repeated scope gets a #n suffix."""
    out, seen = [], collections.Counter()
    for m in FUNC.finditer(code):
        if m.group(2) in KEYWORDS:
            continue
        scope = m.group(1) + m.group(2)
        seen[scope] += 1
        out.append((scope + (f"#{seen[scope]}" if seen[scope] > 1 else ""), m.start(), close(code, m.end() - 1) + 1, m.group(3)))
    return out


def members(body):
    while True:
        flat = re.sub(r"\{[^{}]*\}", ";", body)
        if flat == body:
            break
        body = flat
    for stmt in re.sub(r"\b(?:public|private|protected)\s*:", ";", body).split(";"):
        if "(" in stmt or re.match(r"\s*(?:typedef|friend|using|enum|class|struct)\b", stmt):
            continue
        for d in stmt.split(","):
            m = re.search(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*(?::\s*\w+\s*)?$", d.strip())
            if m:
                yield m.group(1)


def param_names(params):
    for p in params.split(","):
        ids = [t for t in WORD.findall(p.split("=")[0]) if t not in KEYWORDS]
        if len(ids) >= 2:
            yield ids[-1]


def local_names(body):
    statements = {"return", "delete", "goto", "throw", "case", "new", "else", "do", "typedef", "using", "sizeof"}
    return [m.group(2) for m in LOCAL.finditer(body) if m.group(1) not in statements and m.group(2) not in KEYWORDS]


def global_names(code):
    """Variables declared at file scope, outside every brace block."""
    code, top, depth, last = PREPROCESSOR.sub("", code), [], 0, 0
    for m in BRACE.finditer(code):
        if m.group() == "{":
            depth += 1
            if depth == 1:
                top.append(code[last:m.start()])
        elif depth:
            depth -= 1
            if depth == 0:
                last = m.end()
                top.append(";")
    top.append(code[last:] if depth == 0 else "")
    for stmt in "".join(top).split(";"):
        if "(" in stmt or re.match(r"\s*(?:typedef|using|class|struct|enum|union|namespace|template|friend)\b", stmt):
            continue
        ids = [t for t in WORD.findall(stmt.split("=")[0].split("[")[0]) if t not in KEYWORDS]
        if len(ids) >= 2 or (ids and re.search(r"\b(?:int|char|bool|float|double|long|short|unsigned|void)\b", stmt)):
            yield ids[-1]


def declared(rel, text):
    """(kind, name) for everything a file names: itself, its types and their members, its functions
    with their parameters and locals, and its file-scope variables."""
    code = strip(text)
    out = [("file", Path(rel).stem)]
    for m in DECL.finditer(code):
        out.append(("type", m.group(1)))
        out += [("member", n) for n in members(code[m.end():close(code, m.end() - 1)]) if not PAD.match(n)]
    out += [("type", m.group(1)) for m in ENUM.finditer(code)]
    for scope, start, end, params in functions_in(code):
        out.append(("function", scope.split("#")[0].split("::")[-1]))
        out += [("param", n) for n in param_names(params)]
        out += [("local", n) for n in local_names(code[code.find("{", start):end])]
    return out + [("global", n) for n in global_names(code)]


def ledger_rows():
    rows = collections.defaultdict(list)
    for r in csv.DictReader(io.StringIO(LEDGER.read_text(encoding="utf-8", errors="replace"))):
        if r["status"] == "matched":
            rows[r["source"]].append(r)
    return rows


def ea_labelled():
    return {int(r["rva"], 16) for r in csv.DictReader(io.StringIO(EA.read_text(encoding="utf-8")))
            if r["kind"] == "name" and r["basis"] == "strong"}


def servable(rel, rows, ea):
    """Vendored files take their upstream's names, and EA-labelled rows belong to tools/ea_queue.py."""
    return "stlport" not in rel.lower() and not any(
        "vendored=" in (r["notes"] or "") or int(r["target_rva"], 16) in ea for r in rows.get(rel, []))


@functools.lru_cache(maxsize=None)
def real_types():
    """Classes some header declares, in game/ or the Zero Hour reference: the names a stand-in may take."""
    names = set()
    for f in git("ls-files", "game").split():
        if f.endswith((".h", ".inl")) and not f.startswith(GENERATED):
            names |= set(DECL.findall(strip(read(f))))
    for p in ZH.rglob("*.h"):
        names |= set(DECL.findall(strip(p.read_text(encoding="latin1"))))
    return names


@functools.lru_cache(maxsize=None)
def witnessed_members():
    """class -> member names name_oracle's layout witness puts in it."""
    import name_oracle
    out = collections.defaultdict(set)
    for (owner, _), (member, _, _) in name_oracle.load_witness().items():
        out[owner].add(member)
    return out


def member_owners(code):
    return {n: m.group(1) for m in DECL.finditer(code) for n in members(code[m.end():close(code, m.end() - 1)])}


def type_counts():
    """How many files define each type: renaming one copy of a shared type would split its name."""
    count = collections.Counter()
    for f in git("ls-files", "game").split():
        if f.endswith((".cpp", ".h", ".c", ".inl")) and not f.startswith(GENERATED):
            count.update(set(DECL.findall(strip(read(f)))))
    return count


def owned(rel, text, rows, types):
    """[(kind, scope, identifier)] that this file alone decides, in reading order."""
    code = strip(text)
    items = [("type", "", t) for t in dict.fromkeys(DECL.findall(code)) if placeholder(t) and types[t] <= 1]
    for m in DECL.finditer(code):
        for name in members(code[m.end():close(code, m.end() - 1)]):
            if placeholder(name) and len(re.findall(rf"\b{name}\b", code)) > 1:   # used, so not padding
                items.append(("member", "", name))
    scopes = collections.defaultdict(set)
    for r in rows.get(rel, []):
        if m := MANGLED.match(r["name"]):
            scopes[m.group(1)].add(m.group(2))
    for r in rows.get(rel, []):
        m = MANGLED.match(r["name"])
        # apply renames a method name file-wide, so one shared by several classes would rename bodies nobody voted on
        if (m and len(scopes[m.group(1)]) == 1 and placeholder(m.group(1)) and not FAMILY.fullmatch(m.group(1))
                and re.search(rf"\b{m.group(1)}\b", code)):
            items.append(("function", m.group(2), m.group(1)))
    od = bool(re.search(r"^//\s*cl:.*/Od", text[:600], re.M))
    for scope, start, end, params in functions_in(code):
        items += [("param", scope, n) for n in param_names(params) if weak("param", n)]
        if not od:            # /Od orders frame slots by identifier text: renaming a local moves bytes
            items += [("local", scope, n) for n in local_names(code[code.find("{", start):end]) if weak("local", n)]
    seen, out = set(), []
    for kind, scope, ident in items:
        slot = (scope, ident) if kind in ("param", "local") else ident
        if slot not in seen:
            seen.add(slot)
            out.append((kind, scope, ident))
    return out


def key_of(rel, kind, scope, ident):
    return f"{rel}|{kind}|{scope}|{ident}"


def answer_key(kind, scope, ident):
    return f"{scope}:{ident}" if kind in ("param", "local") else ident


# ------------------------------------------------------------------ commands

def cmd_next(args):
    model = model_id(args.model)
    rows, types, ea = ledger_rows(), type_counts(), ea_labelled()
    state = agreed_state()
    voted = collections.defaultdict(set)
    for v in table(VOTES):
        voted[v["key"].split("|")[0]].add(v["model"])
    files = [f for f in rows if f.endswith((".cpp", ".c")) and not f.startswith(GENERATED) and model not in voted[f]
             and f == (args.file or f) and servable(f, rows, ea)]
    random.shuffle(files)
    # another vendor named it: this vote is the one that can land names
    files.sort(key=lambda f: not {vendor(m) for m in voted[f]} - {vendor(model)})
    served = 0
    for rel in files:
        text = read(rel)
        if len(text) > 15000:
            continue
        items = [i for i in owned(rel, text, rows, types) if open_key(state, key_of(rel, *i))]
        if len(items) >= (1 if voted[rel] else 3):
            brief(rel, text, items, model, rows)
            served += 1
            if served == args.count:
                break
    if not served:
        print(f"No file is left for {model} to name.")
    return 0


def brief(rel, text, items, model, rows):
    sys.path.insert(0, str(ROOT / "tools/fleet"))
    import context_pack
    # neighbours say nothing about names, and every line here is paid for by the session reading it
    evidence = [line for r in rows[rel][:8] for line in context_pack.pack(int(r["target_rva"], 16))
                if not line.lstrip().startswith("landed neighbours")][:40]
    session = f"{datetime.datetime.now():%Y%m%d%H%M%S}-{random.randrange(16 ** 6):06x}"
    SESSIONS.mkdir(parents=True, exist_ok=True)
    (SESSIONS / f"{session}.json").write_text(json.dumps(
        {"file": rel, "model": model, "sha": hashlib.sha256(text.encode()).hexdigest(), "items": items}, indent=1))
    lines = text.splitlines()

    def declared_at(ident):
        declarator = re.compile(rf"(?:class|struct)\s+{re.escape(ident)}\b|[\w>*&]\s*[*&]?\s*\b{re.escape(ident)}\s*(?:\[[^\]]*\]\s*)*[;,=)]")
        uses = [l.strip() for l in lines if re.search(rf"\b{re.escape(ident)}\b", l)]
        return next((l for l in uses if declarator.search(l)), uses[0] if uses else "")[:90]

    listing = "\n".join(f"  {answer_key(k, s, i):44} {k:8} {declared_at(i)}" for k, s, i in items)
    print(f"""NAME THE PLACEHOLDERS IN {rel}  (session {session}, model {model})

This is decompiled BFME (SAGE engine) C++. A converter invented the names below from addresses,
offsets or decompiler slots. Give each the name its original EA programmer most likely used,
judging from what the code does and the evidence. Types CamelCase, members m_camelCase,
functions and methods camelCase unless the class already uses CamelCase, params and locals camelCase.
Answer "skip" when you cannot justify a name: a skip costs nothing, a wrong name misleads readers.
A name lands only when a model from a DIFFERENT VENDOR independently proposes the same one, so
your proposal must be your own: do not take names from, or show yours to, another model or session.
Write your answer with a file-writing tool, never inline in a shell command: other sessions on
this machine can read command lines. If a stand-in type IS a real class that a game or Zero Hour
header declares, answer that class's name.

Write a JSON object mapping each key below to a name or "skip", then run:
  python3 tools/name_lane.py submit <that file> --session {session}

{listing}

--- {rel}
{text}
--- evidence
""" + "\n".join(evidence) + "\n")


def problem(kind, old, new, file_words, types, owner=""):
    if not re.fullmatch(r"[A-Za-z_]\w*", new) or new in KEYWORDS:
        return "not a C++ identifier"
    if new == old or weak(kind, new):
        return "still a placeholder"
    if canon(new).replace(" ", "") in GENERIC and new not in witnessed_members().get(owner, ()):
        return "too generic to help a reader"
    if kind == "type" and not new[0].isupper():
        return "types are CamelCase"
    if kind == "member" and not re.fullmatch(r"m_[a-z]\w*", new):
        return "members are m_camelCase"
    if kind in ("param", "local") and not new[0].islower():
        return "params and locals are camelCase"
    if kind == "type" and types[new] and new not in real_types():
        return f"{new} is another file's stand-in, not a class any header declares"
    if kind in NAMED and new in file_words:
        return "collides with a name already in the file"
    return None


def cmd_submit(args):
    path = SESSIONS / f"{args.session}.json"
    if not path.exists():
        fail(f"unknown session {args.session}: run `next` in this checkout first")
    session = json.loads(path.read_text())
    rel, model = session["file"], session["model"]
    text = read(rel)
    if hashlib.sha256(text.encode()).hexdigest() != session["sha"]:
        fail(f"{rel} changed since `next` served it; run `next` again")
    answers = json.loads(Path(args.answer).read_text(encoding="utf-8"))
    unknown = set(answers) - {answer_key(*i) for i in session["items"]}
    if unknown:
        fail(f"keys not in this session: {', '.join(sorted(unknown)[:8])}")
    file_words, types, owners = set(WORD.findall(strip(text))), type_counts(), member_owners(strip(text))
    earlier = collections.defaultdict(lambda: collections.defaultdict(set))
    for v in table(VOTES):
        earlier[v["key"]][v["hash"]].add(v["model"])
    state = agreed_state()
    now = datetime.date.today().isoformat()
    votes, rejected, landed, taken = [], [], [], set()
    for kind, scope, ident in session["items"]:
        answer = str(answers.get(answer_key(kind, scope, ident), "skip")).strip()
        if answer.lower() == "skip":
            continue
        key = key_of(rel, kind, scope, ident)
        why = problem(kind, ident, answer, file_words, types, owners.get(ident, "") if kind == "member" else "")
        if not why and kind in NAMED and canon(answer) in taken:
            why = "the same name as another placeholder in this file"
        if not why and key in state and state[key]["status"].startswith("disputed") and canon(answer) == canon(state[key]["name"]):
            why = state[key]["status"]
        if why:
            rejected.append(f"{answer_key(kind, scope, ident)} -> {answer}: {why}")
            continue
        taken |= {canon(answer)} if kind in NAMED else set()
        h = digest(key, answer)
        votes.append({"key": key, "hash": h, "model": model, "session": args.session, "date": now})
        mine = earlier[key][h] | {model}
        if open_key(state, key) and wins(mine, [ms for h2, ms in earlier[key].items() if h2 != h]):
            landed.append({"key": key, "name": spelling(answer, kind), "models": "+".join(sorted(mine)),
                           "status": "agreed", "date": now})
            state[key] = landed[-1]
    if not votes:
        fail("no valid names to record" + "".join(f"\n  rejected: {r}" for r in rejected))
    append(VOTES, votes)
    if landed:
        append(AGREED, landed)
    path.unlink()
    for r in rejected:
        print("  rejected:", r)
    for a in landed:
        print(f"  AGREED: {a['key'].split('|')[-1]} -> {a['name']} ({a['models']})")
    print(f"{rel}: {len(votes)} vote(s) recorded as hashes, {len(rejected)} rejected, {len(landed)} newly agreed")
    done = commit([VOTES] + ([AGREED] if landed else []), f"name_lane: {model} votes on {Path(rel).name}, {len(landed)} name(s) agreed")
    if done.returncode:
        fail("commit refused:\n" + (done.stdout + done.stderr)[-3000:])
    print("Committed. " + ("Run `python3 tools/name_lane.py apply` to land the agreed names, then push."
                          if landed else "Push it; the names land when another vendor's model agrees."))
    return 0


def commit(paths, message):
    names = [str(Path(p).relative_to(ROOT)) if Path(p).is_absolute() else str(p) for p in paths]
    git("add", *names)
    return subprocess.run(["git", "commit", "-q", "--only", *names, "-m", message], cwd=ROOT, capture_output=True, text=True)


def rewrite_stored(renames, why="two models agreed"):
    """Every stored mangled name: ledger names and object-symbol= notes, pins, DIR32 names."""
    subs = []
    for kind, scope, old, new in renames:
        if kind == "type":
            subs.append((re.compile(rf"(?<=[@?VU01GE]){re.escape(old)}@"), f"{new}@"))
        else:
            subs.append((re.compile(re.escape(f"?{old}@{scope}@")), f"?{new}@{scope}@"))

    def each(m):
        name = m.group(0)
        for pattern, replacement in subs:
            name = pattern.sub(replacement, name)
        return name

    for path in STORED:
        text = path.read_bytes().decode("utf-8")
        new = re.sub(r"(?<![\w?@])\?[^,;\s\"]+", each, text)
        if new != text:
            path.write_bytes(new.encode("utf-8"))
        if path == LEDGER:
            # functions.csv union-merges: a renamed row returns from any older branch unless tombstoned
            renamed = [(a[0], a[2], b[0]) for a, b in zip(csv.reader(io.StringIO(text)), csv.reader(io.StringIO(new)))
                       if a and a[0] != b[0]]
            # a name put back (a dispute) was tombstoned when it was renamed away; check_csv would read it as resurrected
            back = {(name, int(rva, 16)) for _, rva, name in renamed}
            kept = [l for l in TOMBSTONES.read_bytes().decode("utf-8").splitlines(keepends=True)
                    if not ((r := next(csv.reader([l]), [])) and len(r) > 1 and re.fullmatch(r"0x[0-9A-Fa-f]+", r[1])
                            and (r[0], int(r[1], 16)) in back)]
            TOMBSTONES.write_bytes("".join(kept).encode("utf-8"))
            with TOMBSTONES.open("a", encoding="utf-8", newline="") as f:
                csv.writer(f, lineterminator="\n").writerows(
                    (old, rva, f"renamed to {name} by tools/name_lane.py: {why}") for old, rva, name in renamed)


def gate(rel):
    done = subprocess.run(["bash", "build.sh", rel], cwd=ROOT, capture_output=True, text=True)
    out = done.stdout + done.stderr
    if done.returncode == 0 and re.search(r"Functions: OK (\d+)/\1\b", out):
        return None
    return next((l.strip() for l in out.splitlines() if re.search(r"error|FAIL|MISMATCH", l)), f"build.sh exited {done.returncode}")


def rename(text, old, new, span=None):
    """old -> new in code and in mangled names quoted in comments. Prose keeps the words it was
    written with, and a string literal keeps its bytes."""
    lo, hi = span or (0, len(text))
    quoted = [m.span() for m in NONCODE.finditer(text)]
    out, last = [], 0
    for m in re.finditer(rf"(?<![A-Za-z0-9_]){re.escape(old)}(?![A-Za-z0-9_])", text):
        mangled = text[m.end():m.end() + 1] == "@" or text[m.start() - 1:m.start()] in ("?", "@")
        if not lo <= m.start() < hi or (any(s <= m.start() < e for s, e in quoted) and not mangled):
            continue
        out.append(text[last:m.start()] + new)
        last = m.end()
    return "".join(out) + text[last:]


def land(rel, renames, now, status="applied"):
    """Rename, byte-gate and commit one file's agreed names (or, for a dispute, put a landed name back).
    On any failure everything is put back and the reason returned: a refused file must not hold back
    the others."""
    dispute = status.startswith("disputed")
    spread = {rel}
    for kind, scope, ident, new, models, key in renames:
        if kind in ("type", "function"):
            hits = subprocess.run(["rg", "-lw", "--no-messages", ident, "game"], cwd=ROOT,
                                  capture_output=True, text=True).stdout.split()
            owner = scope.split("@")[0]
            # the owner must appear in code: a comment naming it does not make the file's own methods of that name its
            spread |= {f for f in hits if kind == "type" or not owner or re.search(rf"\b{owner}\b", strip(read(f)))}
    generated = sorted(f for f in spread if f.startswith(GENERATED))
    if generated:
        return f"a generated file names it: {generated[0]}"
    paths = [ROOT / f for f in sorted(spread)] + STORED + [TOMBSTONES, ADOPT_BLOCKED, AGREED] + ([CORRECTIONS, DISPUTES] if dispute else [])
    snapshot = {p: p.read_bytes() for p in paths if p.exists()}
    for f in spread:
        # bytes in, bytes out: CRLF sources and stray non-UTF-8 comment bytes must survive untouched
        text = (ROOT / f).read_bytes().decode("utf-8", "surrogateescape")
        spans = {sc: (s, e) for sc, s, e, _ in functions_in(strip(text))}
        for kind, scope, ident, new, models, key in renames:
            if kind in ("type", "function") or (f == rel and kind == "member"):
                text = rename(text, ident, new)
            elif f == rel and scope in spans:
                text = rename(text, ident, new, spans[scope])
        (ROOT / f).write_bytes(text.encode("utf-8", "surrogateescape"))
    rewrite_stored([(k, s, i, n) for k, s, i, n, _, _ in renames if k in ("type", "function")], status if dispute else "two models agreed")
    if any(k == "type" and n in real_types() for k, s, i, n, _, _ in renames):
        # the stand-in now carries its real class name, so name_oracle's witness can name its members
        subprocess.run([sys.executable, str(ROOT / "tools/name_oracle.py"), "--todo", "--apply", rel],
                       cwd=ROOT, capture_output=True, check=True)
    why = next((f"{f}: {w}" for f in sorted(spread) if f.endswith((".cpp", ".c")) and (w := gate(f))), None)
    if not why:
        append(AGREED, [{"key": key, "name": ident if dispute else new, "models": models, "status": status, "date": now}
                        for kind, scope, ident, new, models, key in renames])
        git("add", *[str(p.relative_to(ROOT)) for p in paths if p.exists()])
        if dispute:
            document_corrections(status)
        # the hook refuses any staged source that still redeclares a header's type; this swaps or records each one
        subprocess.run([sys.executable, str(ROOT / "tools/adopt_header.py"), "--fix-staged"], cwd=ROOT, check=True)
        done = commit([p for p in paths if p.exists()],
                      f"name_lane: {status} ({', '.join(r[2] for r in renames)} in {Path(rel).name})" if dispute
                      else f"name_lane: land {len(renames)} agreed name(s) in {Path(rel).name}")
        if done.returncode:
            out = (done.stdout + done.stderr).splitlines()
            why = "hook: " + " | ".join(l.strip() for l in out if l.startswith("  ") or "FAILED" in l)[:300]
    if why:
        git("reset", "-q", "--", *[str(p.relative_to(ROOT)) for p in paths if p.exists()])
        for p, data in snapshot.items():
            p.write_bytes(data)
    return why


def document_corrections(reason):
    """Putting a descriptive name back to its placeholder is what name_regression refuses unless an exact
    correction documents it; record one for each finding the staged revert produces."""
    import name_regression
    findings, _ = name_regression.check(ROOT, "HEAD", ":")
    raw = CORRECTIONS.read_bytes()
    entries = json.loads(raw)
    entries += [{**vars(f), "evidence": str(DISPUTES.relative_to(ROOT).as_posix()), "reason": reason} for f in findings]
    eol = "\r\n" if b"\r\n" in raw else "\n"      # keep the file's line endings: eol_guard refuses a whole-file rewrite
    CORRECTIONS.write_bytes((json.dumps(entries, indent=1) + "\n").replace("\n", eol).encode("utf-8"))
    git("add", str(CORRECTIONS.relative_to(ROOT)))


def cmd_dispute(args):
    """Put landed names in one file back to their placeholders in one byte-gated commit, and reopen them
    for votes; the disputed names are refused from then on. One commit per file, because name_regression
    matches a documented correction to the exact file text before and after, across the whole push."""
    state = agreed_state()
    for key in args.keys:
        if key not in state or state[key]["status"] != "applied":
            fail(f"{key}: no landed name to dispute")
    files = {key.split("|")[0] for key in args.keys}
    if len(files) != 1:
        fail(f"dispute one file at a time; these keys span {len(files)} files")
    renames = [(*key.split("|")[1:3], state[key]["name"], key.split("|")[3], state[key]["models"], key) for key in args.keys]
    rel = files.pop()
    before = DISPUTES.read_bytes() if DISPUTES.exists() else None
    if before is None:
        DISPUTES.write_text("# Names the naming lane landed and a review disputed\n\n", encoding="utf-8")
    with DISPUTES.open("a", encoding="utf-8") as f:
        f.writelines(f"- `{key}`: `{landed}` back to `{ident}`. {args.reason}\n" for _, _, landed, ident, _, key in renames)
    git("add", str(DISPUTES.relative_to(ROOT)))
    why = land(rel, renames, datetime.date.today().isoformat(), status=f"disputed: {args.reason}")
    if why:
        git("reset", "-q", "--", str(DISPUTES.relative_to(ROOT)))
        DISPUTES.write_bytes(before) if before is not None else DISPUTES.unlink()
        fail(f"could not put the names back: {why}")
    print(f"{', '.join(r[2] for r in renames)} put back in {rel}; reopened for new votes, refusing the disputed names. Push the commit.")
    return 0


def cmd_apply(args):
    rows, types, ea = ledger_rows(), type_counts(), ea_labelled()
    todo = collections.defaultdict(list)
    for key, a in agreed_state().items():
        if a["status"] == "agreed" or (args.retry_blocked and a["status"].startswith("blocked")):
            rel, kind, scope, ident = key.split("|")
            todo[rel].append((kind, scope, ident, a["name"], a["models"], key))
    if not todo:
        print("Nothing agreed is waiting to land.")
        return 0
    now = datetime.date.today().isoformat()
    unlanded, landed = [], 0

    def note(renames, status):
        unlanded.extend({"key": key, "name": new, "models": models, "status": status, "date": now}
                        for kind, scope, ident, new, models, key in renames)

    for rel, renames in sorted(todo.items()):
        live = set(owned(rel, read(rel), rows, types)) if (ROOT / rel).exists() and servable(rel, rows, ea) else set()
        note([r for r in renames if r[:3] not in live], "stale")
        renames = [r for r in renames if r[:3] in live]
        clash = collections.Counter(canon(r[3]) for r in renames if r[0] in NAMED)
        note([r for r in renames if r[0] in NAMED and clash[canon(r[3])] > 1], "blocked: the same name as another placeholder")
        renames = [r for r in renames if r[0] not in NAMED or clash[canon(r[3])] == 1]
        if not renames:
            continue
        why = land(rel, renames, now)
        if why:
            note(renames, f"blocked: {why[:150]}")
            print(f"{rel}: blocked, reverted: {why[:300]}")
        else:
            landed += len(renames)
            print(f"{rel}: {len(renames)} name(s) landed")
    if unlanded:
        append(AGREED, unlanded)
        done = commit([AGREED], f"name_lane: record {len(unlanded)} agreed name(s) that could not land")
        if done.returncode:
            fail("status commit refused:\n" + (done.stdout + done.stderr)[-3000:])
    print(f"landed {landed} name(s); {sum(e['status'].startswith('blocked') for e in unlanded)} blocked, "
          f"{sum(e['status'] == 'stale' for e in unlanded)} stale (the file changed or left the lane). Push the commits.")
    return 0


def inventory():
    """kind -> [names, placeholders] over every declaration in game/ source. Files, types, functions,
    members, parameters and locals count per declaration; a global counts once, however many
    files declare it extern."""
    count = collections.defaultdict(lambda: [0, 0])
    globals_seen = set()
    for f in git("ls-files", "game").split():
        if f.endswith((".cpp", ".c", ".h", ".inl")) and not f.startswith(GENERATED):
            for kind, name in declared(f, read(f)):
                if kind == "global":
                    if name in globals_seen:
                        continue
                    globals_seen.add(name)
                bad = weak(kind, name)
                count[kind][0] += 1
                count[kind][1] += bad
    return count


def readable():
    """(names, placeholders) summed over every kind of declaration."""
    count = inventory().values()
    return sum(c[0] for c in count), sum(c[1] for c in count)


def cmd_status(args):
    kinds = inventory()
    total, bad = sum(c[0] for c in kinds.values()), sum(c[1] for c in kinds.values())
    state = agreed_state().values()
    count = collections.Counter(a["status"].split(":")[0] for a in state)
    print(f"Readable names: {100 * (1 - bad / total):.2f}% ({total - bad:,} of {total:,} declared names); "
          f"placeholders left: {bad:,}")
    for kind, (n, b) in sorted(kinds.items(), key=lambda kv: -kv[1][1]):
        print(f"  {kind:9} {100 * (1 - b / n):6.2f}% readable  ({b:,} placeholders of {n:,})")
    print(f"votes: {len(table(VOTES)):,}; agreed: {len(state)} (landed {count['applied']}, waiting {count['agreed']}, "
          f"blocked {count['blocked']}, stale {count['stale']}, disputed {count['disputed']})")
    return 0


def retail_import_names():
    """API identifiers witnessed by retail's PE import table, without pin proposals."""
    import link_census

    names = set()
    for _dll, name, _slot in link_census._retail_import_entries():
        # Miles exports decorated stdcall names; the C identifier excludes
        # the leading underscore and argument-byte suffix. Keep ordinary
        # export names (including CRT names such as _vsnprintf) exact.
        decorated = re.fullmatch(r"_([A-Za-z_]\w*)@\d+", name)
        identifier = decorated.group(1) if decorated else name
        if WORD.fullmatch(identifier):
            names.add(identifier)
    return names


def cmd_check(args):
    """Refuse a placeholder swapped for a coined name outside the lane. Allowed replacements: an
    agreed name, an EA name, a retail import, or a name a header already declares (adoption)."""
    coined = collections.defaultdict(set)
    for f in git("diff", "--cached", "--name-only", "--diff-filter=M", "--no-renames").split():
        if not f.startswith("game/") or f.startswith(GENERATED) or not f.endswith((".cpp", ".c", ".h", ".inl")):
            continue
        old_code, new_code = strip(git("show", f"HEAD:{f}")), strip(git("show", f":{f}"))
        if not {w for w in WORD.findall(old_code) if placeholder(w)} - set(WORD.findall(new_code)):
            continue
        old, new = re.findall(r"[A-Za-z_]\w*|\S", old_code), re.findall(r"[A-Za-z_]\w*|\S", new_code)
        changed = [(old[a:b], new[c:d]) for op, a, b, c, d in
                   difflib.SequenceMatcher(None, old, new, autojunk=False).get_opcodes() if op != "equal"]
        # only a pure rename is a naming pass: conversions and identity work change code as well
        if all(len(x) == len(y) and all(WORD.fullmatch(t) for t in x + y) for x, y in changed):
            coined[f] |= {f"{was} -> {now}" for x, y in changed for was, now in zip(x, y)
                          if was != now and placeholder(was) and not placeholder(now)}
    if not any(coined.values()):
        return 0
    allowed = {a["name"] for a in agreed_state().values()}
    allowed |= {w for r in csv.DictReader(io.StringIO(EA.read_text(encoding="utf-8"))) if r["kind"] == "name"
                for w in WORD.findall(r["value"])}
    allowed |= {w for pin in STORED[1:] for w in WORD.findall(git("show", f":{pin.relative_to(ROOT).as_posix()}"))}
    allowed |= retail_import_names()

    def declared(word):
        if not (word[0].isupper() or word.startswith("m_")):
            return False          # a local, parameter or method has no header to adopt
        return (subprocess.run(["git", "grep", "-qw", word, "HEAD", "--", "*.h"], cwd=ROOT).returncode == 0
                or subprocess.run(["grep", "-rqw", "--include=*.h", word, str(ZH)]).returncode == 0)

    bad = {f: sorted(s for s in swaps if s.split(" -> ")[1] not in allowed and not declared(s.split(" -> ")[1]))
           for f, swaps in coined.items()}
    bad = {f: s for f, s in bad.items() if s}
    if bad:
        print("name_lane: placeholders renamed outside the naming lane. A name lands only when models from two vendors "
              "propose it: python3 tools/name_lane.py next --model <you>\n"
              + "\n".join(f"  {f}: {', '.join(s[:6])}" for f, s in bad.items()), file=sys.stderr)
        return 1
    return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    n = sub.add_parser("next")
    n.add_argument("--model", required=True, help="the model you are: opus, sonnet, gpt-5.6-sol, grok...")
    n.add_argument("--file", help="name this file instead of the next one in the queue")
    n.add_argument("--count", type=int, default=1, help="serve this many files in one go")
    s = sub.add_parser("submit")
    s.add_argument("answer")
    s.add_argument("--session", required=True)
    sub.add_parser("apply").add_argument("--retry-blocked", action="store_true",
                                         help="try names an earlier apply could not land again, e.g. after a fix")
    d = sub.add_parser("dispute")
    d.add_argument("keys", nargs="+", help="as name_agreed.csv spells them (file|kind|scope|placeholder), all in one file")
    d.add_argument("--reason", required=True, help="what the code shows against the landed name")
    sub.add_parser("status")
    sub.add_parser("check").add_argument("--staged", action="store_true", required=True)
    args = ap.parse_args()
    return {"next": cmd_next, "submit": cmd_submit, "apply": cmd_apply, "dispute": cmd_dispute, "status": cmd_status,
            "check": cmd_check}[args.cmd](args)


if __name__ == "__main__":
    sys.exit(main())
