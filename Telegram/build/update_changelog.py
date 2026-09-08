#!/usr/bin/env python3
import argparse
import datetime
import os
import re
import subprocess
import sys

REPO_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
CHANGELOG_PATH = os.path.join(REPO_ROOT, 'changelog.txt')
SET_VERSION_PATH = os.path.join(REPO_ROOT, 'Telegram', 'build', 'set_version.py')


def parse_version_string(ver_raw, force_beta=False):
    ver = ver_raw.strip()
    is_beta = force_beta
    if ver.endswith('.beta'):
        is_beta = True
        ver = ver[:-5]
    elif ver.endswith('beta'):
        is_beta = True
        ver = ver[:-4].strip()

    match = re.match(r'^(\d+)\.(\d+)(\.(\d+))?$', ver)
    if not match:
        raise ValueError(f"Invalid version format: '{ver_raw}'. Expected format: X.Y or X.Y.Z")

    major = match.group(1)
    minor = match.group(2)
    patch = match.group(4) if match.group(4) else '0'

    version_str = f"{major}.{minor}.{patch}"
    version_small = version_str if patch != '0' else f"{major}.{minor}"
    return version_str, version_small, is_beta


def has_changelog_entry(content, version_str, version_small):
    for line in content.splitlines():
        if line.startswith(version_str + ' ') or line.startswith(version_small + ' '):
            return True
    return False


def build_entry_block(version_str, is_beta, date_str, entries):
    header = f"{version_str} beta ({date_str})" if is_beta else f"{version_str} ({date_str})"
    lines = [header]
    if not entries:
        entries = ["Beta release"] if is_beta else ["Bug fixes and performance improvements"]

    for entry in entries:
        entry = entry.strip()
        if not entry.startswith('-') and not entry.startswith('—') and not entry.startswith('*'):
            entry = f"- {entry}"
        lines.append(entry)

    return "\n".join(lines) + "\n\n"


def update_changelog(version_str, version_small, is_beta, date_str, entries, force=False):
    if not os.path.isfile(CHANGELOG_PATH):
        content = ""
    else:
        with open(CHANGELOG_PATH, 'r', encoding='utf-8') as f:
            content = f.read()

    already_exists = has_changelog_entry(content, version_str, version_small)
    if already_exists and not force:
        print(f"Changelog entry for {version_str} already exists in changelog.txt")
        return False

    new_block = build_entry_block(version_str, is_beta, date_str, entries)

    if already_exists and force:
        pattern = rf"^({re.escape(version_str)}|{re.escape(version_small)})\s+.*?(?=\n[0-9]+\.[0-9]+|\Z)"
        content = re.sub(pattern, new_block.strip(), content, flags=re.DOTALL | re.MULTILINE)
        final_content = content
    else:
        final_content = new_block + content.lstrip()

    with open(CHANGELOG_PATH, 'w', encoding='utf-8', newline='\n') as f:
        f.write(final_content)

    print(f"Added changelog entry for {version_str}{' beta' if is_beta else ''} ({date_str}) to changelog.txt")
    return True


def main():
    parser = argparse.ArgumentParser(description="Update changelog.txt for version bumping")
    parser.add_argument("version", nargs="?", default=None,
                        help="Target version (e.g. 2.5.4, 2.5.4.beta)")
    parser.add_argument("-beta", "--beta", action="store_true",
                        help="Format entry as beta (e.g. '2.5.4 beta (DD.MM.YY)')")
    parser.add_argument("-d", "--date", default=None,
                        help="Changelog date in DD.MM.YY format (default: today)")
    parser.add_argument("-e", "-m", "--entry", action="append", dest="entries",
                        help="Changelog bullet point (can be repeated)")
    parser.add_argument("--check", action="store_true",
                        help="Check if changelog entry exists and exit (0 if exists, 1 if missing)")
    parser.add_argument("-f", "--force", action="store_true",
                        help="Force update entry if it already exists")
    parser.add_argument("--bump", action="store_true",
                        help="Run set_version.py after updating changelog")
    args = parser.parse_args()

    if not args.version:
        version_file = os.path.join(REPO_ROOT, 'Telegram', 'build', 'version')
        if os.path.isfile(version_file):
            with open(version_file, 'r', encoding='utf-8') as f:
                for line in f:
                    parts = line.strip().split()
                    if len(parts) >= 2 and parts[0] == 'AppVersionStr':
                        args.version = parts[1]
                        break

    if not args.version:
        print("Error: Version must be provided or present in Telegram/build/version", file=sys.stderr)
        sys.exit(1)

    try:
        version_str, version_small, is_beta = parse_version_string(args.version, force_beta=args.beta)
    except ValueError as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)

    date_str = args.date or datetime.datetime.now().strftime("%d.%m.%y")

    if args.check:
        if not os.path.isfile(CHANGELOG_PATH):
            sys.exit(1)
        with open(CHANGELOG_PATH, 'r', encoding='utf-8') as f:
            content = f.read()
        if has_changelog_entry(content, version_str, version_small):
            print(f"Changelog entry for {version_str} exists.")
            sys.exit(0)
        else:
            print(f"Changelog entry for {version_str} not found.", file=sys.stderr)
            sys.exit(1)

    update_changelog(version_str, version_small, is_beta, date_str, args.entries, force=args.force)

    if args.bump:
        cmd = [sys.executable, SET_VERSION_PATH, version_str]
        if is_beta:
            cmd.append("-beta")
        print(f"Running: {' '.join(cmd)}")
        result = subprocess.run(cmd)
        sys.exit(result.returncode)


if __name__ == '__main__':
    main()
