#!/usr/bin/env bash
# One-time per-clone setup. Run after every fresh clone (git does not enable
# tracked hooks or upstream tracking on its own).
set -euo pipefail

ROOT="$(git rev-parse --show-toplevel)"
cd "$ROOT"

git config core.hooksPath .githooks

# Agents work in a loop of pull --rebase / push against one shared master;
# tracking makes divergence visible in `git status`, pull.rebase makes a bare
# `git pull` do the right thing, and a non-interactive editor keeps rebases
# from hanging the session inside vim.
git branch --set-upstream-to=origin/master master 2>/dev/null \
    || echo "note: no origin/master yet; set upstream after first fetch"
git config pull.rebase true
git config core.editor true
# name_corrections.json is a JSON list every rename landing appends to; this
# driver merges it as a set of entries instead of stopping the rebase.
git config merge.jsonlist.name "JSON list ledger (tools/merge_json_list.py)"
git config merge.jsonlist.driver "python3 tools/merge_json_list.py %O %A %B"

echo "core.hooksPath=$(git config --get core.hooksPath)"
echo "upstream=$(git rev-parse --abbrev-ref --symbolic-full-name '@{u}' 2>/dev/null || echo unset)"
echo "pull.rebase=$(git config --get pull.rebase) core.editor=$(git config --get core.editor)"
