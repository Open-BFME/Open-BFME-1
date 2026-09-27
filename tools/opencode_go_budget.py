"""Account-wide Go meters. Only GET the source-verified provider endpoint.

No billing reconstruction, credential discovery, dashboard scraping or inference.
The cache is separate from router schema so old clients can share router state.
"""
from contextlib import contextmanager
from datetime import datetime
from email.utils import parsedate_to_datetime
import json
import math
import os
import sqlite3
import time
import urllib.error
import urllib.request

URL = 'https://opencode.ai/zen/go/v1/usage'
TOKEN_ENV = 'OPENCODE_GO_USAGE_API_KEY'
DEFAULTS = dict(refresh_seconds=300, stale_seconds=900, timeout_seconds=10,
                normal_remaining=70, economical_remaining=30, restricted_remaining=10,
                economical_max_cost=2, restricted_cheap_failures=3)


def config(c):
    options = c.get('go_budget', {})
    if not isinstance(options, dict) or set(options) - set(DEFAULTS):
        raise ValueError('unknown go_budget configuration field')
    p = {**DEFAULTS, **options}
    for k, v in p.items():
        if type(v) not in (int, float) or not math.isfinite(v) or v <= 0:
            raise ValueError('go_budget values must be positive finite numbers')
    if not 100 > p['normal_remaining'] > p['economical_remaining'] > p['restricted_remaining'] > 0:
        raise ValueError('go_budget thresholds must descend within (0,100)')
    if p['refresh_seconds'] < 60 or p['stale_seconds'] < p['refresh_seconds']:
        raise ValueError('go_budget refresh >= 60 seconds and stale >= refresh required')
    if p['timeout_seconds'] > 30 or type(p['restricted_cheap_failures']) is not int:
        raise ValueError('go_budget timeout <= 30 and integer failure count required')
    return p


def timestamp(value):
    if not isinstance(value, str):
        raise ValueError('reset timestamp must be ISO 8601 with timezone')
    dt = datetime.fromisoformat(value.replace('Z', '+00:00'))
    if dt.tzinfo is None:
        raise ValueError('reset timestamp lacks timezone')
    return dt.timestamp()


def parse_usage(data):
    """Strict source-verified schema; unknown fields tolerated, partial meters not."""
    windows = {}
    for remote, local in (('rolling', '5h'), ('weekly', 'weekly'), ('monthly', 'monthly')):
        row = data['usage'][remote]
        used = row['percent']
        if type(used) not in (int, float) or not math.isfinite(used) or not 0 <= used <= 100:
            raise ValueError('invalid usage percent')
        if row['status'] not in ('ok', 'rate-limited'):
            raise ValueError('unknown provider quota status')
        timestamp(row['resetsAt'])
        windows[local] = dict(used_percent=used, remaining_percent=100-used,
            resets_at=row['resetsAt'], status=row['status'], authoritative=True,
            remaining_basis='100 minus provider percent; inherits provider rounding')
    return windows


@contextmanager
def database(state):
    state.mkdir(parents=True, exist_ok=True, mode=0o700)
    db = sqlite3.connect(state / 'go-budget.sqlite', timeout=5)
    try:
        db.execute('CREATE TABLE IF NOT EXISTS cache (id INTEGER PRIMARY KEY CHECK(id=1), value TEXT NOT NULL)')
        with db:
            yield db
    finally:
        db.close()


def read(db):
    row = db.execute('SELECT value FROM cache WHERE id=1').fetchone()
    value = json.loads(row[0]) if row else {}
    if not isinstance(value, dict):
        raise ValueError('invalid cache')
    for key in ('observed_at', 'last_attempt', 'next_refresh', 'quota_at'):
        if key in value and (type(value[key]) not in (int, float) or not math.isfinite(value[key])):
            raise ValueError('invalid cache time')
    if 'windows' in value:
        if set(value['windows']) != {'5h', 'weekly', 'monthly'}:
            raise ValueError('incomplete cached windows')
        for w in value['windows'].values():
            used = w['used_percent']
            if type(used) not in (int, float) or not math.isfinite(used) or not 0 <= used <= 100 or w['remaining_percent'] != 100-used or w['status'] not in ('ok', 'rate-limited'):
                raise ValueError('invalid cached meter')
            timestamp(w['resets_at'])
        if 'observed_at' not in value:
            raise ValueError('missing observation time')
    return value


def write(db, value):
    db.execute('INSERT INTO cache VALUES (1,?) ON CONFLICT(id) DO UPDATE SET value=excluded.value',
               (json.dumps(value),))


class NoRedirect(urllib.request.HTTPRedirectHandler):
    # Never forward a bearer credential to a different endpoint/host.
    def redirect_request(self, req, fp, code, msg, headers, newurl):
        return None


def fetch(token, timeout):
    request = urllib.request.Request(URL, headers={'Authorization': 'Bearer '+token,
                                                   'Accept': 'application/json'})
    with urllib.request.build_opener(NoRedirect).open(request, timeout=timeout) as response:
        raw = response.read(65537)
        if len(raw) > 65536:
            raise ValueError('oversized usage response')
        return parse_usage(json.loads(raw))


def refresh(state, c, now=None, fetcher=fetch):
    """Cross-process refresh lease; never hold a DB transaction across network IO."""
    live_clock = now is None
    now = time.time() if now is None else now
    p = config(c)
    with database(state) as db:
        db.execute('BEGIN IMMEDIATE')
        cache = read(db)
        if now < cache.get('next_refresh', 0):
            return False
        cache.update(last_attempt=now, next_refresh=now+p['refresh_seconds'])
        write(db, cache)
    error, windows, retry = None, None, p['refresh_seconds']
    token = os.environ.get(TOKEN_ENV)
    try:
        if not token:
            error = 'credentials_missing'
        else:
            windows = fetcher(token, p['timeout_seconds'])
            if any(timestamp(w['resets_at']) <= (time.time() if live_clock else now) for w in windows.values()):
                windows = None
                error = 'usage_reset_elapsed_during_refresh'
    except urllib.error.HTTPError as exc:
        error = 'usage_http_' + str(exc.code)
        # API throttle is a monitoring failure, not evidence of inference exhaustion.
        value = exc.headers.get('Retry-After', '') if exc.headers else ''
        if value.isdigit():
            retry = max(retry, int(value))
        elif value:
            try:
                retry = max(retry, parsedate_to_datetime(value).timestamp()-now)
            except (ValueError, TypeError, OverflowError):
                pass
        exc.close()
    except (OSError, ValueError, KeyError, TypeError, OverflowError):
        error = 'usage_unavailable_or_invalid'
    with database(state) as db:
        db.execute('BEGIN IMMEDIATE')
        cache = read(db)  # preserve quota events arriving during the GET
        if cache.get('last_attempt') != now:
            return False
        cache.update(error=error, next_refresh=max(cache.get('next_refresh', 0), now+retry))
        if windows is not None:
            cache.update(windows=windows, observed_at=now)
            if cache.get('quota_at', float('inf')) <= now and all(
                    w['status'] == 'ok' and w['remaining_percent'] > 0 for w in windows.values()):
                cache.pop('quota_at', None)
        write(db, cache)
    return windows is not None


def quota(state, c, now=None):
    now = time.time() if now is None else now
    with database(state) as db:
        db.execute('BEGIN IMMEDIATE')
        cache = read(db)
        cache.update(quota_at=now, next_refresh=max(cache.get('next_refresh', 0),
                     now+config(c)['refresh_seconds']))
        write(db, cache)


def snapshot(state, c, now=None):
    now = time.time() if now is None else now
    p = config(c)
    try:
        with database(state) as db:
            cache = read(db)
    except (OSError, sqlite3.Error, ValueError, TypeError, KeyError, OverflowError):
        cache = {'error': 'cache_unavailable'}
    windows = cache.get('windows', {})
    age = now-cache['observed_at'] if 'observed_at' in cache else None
    stale = age is None or age < 0 or age >= p['stale_seconds'] or any(
        timestamp(w['resets_at']) <= now for w in windows.values())
    exhausted = 'quota_at' in cache or any(w['status'] == 'rate-limited' or
                    w['remaining_percent'] == 0 for w in windows.values())
    remaining = windows.get('5h', {}).get('remaining_percent')
    mode = ('exhausted' if exhausted else 'stale' if stale else
            'normal' if remaining > p['normal_remaining'] else
            'economical' if remaining >= p['economical_remaining'] else
            'restricted' if remaining >= p['restricted_remaining'] else 'conservation')
    return dict(source=URL, authoritative=bool(windows), windows=windows,
        observed_at=cache.get('observed_at'), age_seconds=None if age is None else round(age, 1),
        stale=stale, refresh_failed=bool(cache.get('error')), error=cache.get('error'),
        next_refresh=cache.get('next_refresh'), pacing_mode=mode, exhausted=exhausted,
        quota_error_at=cache.get('quota_at'), refresh_seconds=p['refresh_seconds'],
        max_metered_workers=1 if mode in ('stale', 'conservation') else None)


def economical(model, c):
    cost = model.get('relative_cost')
    return (cost is not None and cost <= config(c)['economical_max_cost'] and
            not model.get('escalation_only', model['tier'] == 'escalation'))


def reason(model, job, budget, c, failed=()):
    if not model.get('metered', True):
        return None
    mode = budget['pacing_mode']
    cheap = economical(model, c)
    justification = bool(job.get('budget_justification', '').strip())
    if mode == 'exhausted':
        return 'budget.account_exhausted'
    if mode == 'stale':
        return None if cheap else 'budget.monitoring_stale'
    if mode == 'conservation':
        return None if cheap and justification else 'budget.conservation_requires_economical_justified_task'
    if mode == 'restricted' and not cheap:
        cheap_ids = {m['id'] for m in c['models'] if economical(m, c)}
        if not (job['tier'] == 'escalation' and justification and
                len(set(failed) & cheap_ids) >= config(c)['restricted_cheap_failures']):
            return 'budget.restricted_requires_valuable_blocker_and_cheap_failures'
    if mode == 'economical' and not cheap and not (job['tier'] == 'escalation' and justification):
        return 'budget.economical_requires_justified_escalation'
    return None
