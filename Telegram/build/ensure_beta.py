#!/usr/bin/env python3
import os
import re
import sys

REPO_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
VERSION_FILE = os.path.join(REPO_ROOT, 'Telegram', 'build', 'version')
CORE_VERSION_H = os.path.join(REPO_ROOT, 'Telegram', 'SourceFiles', 'core', 'version.h')
FA_VERSION_H = os.path.join(REPO_ROOT, 'Telegram', 'SourceFiles', 'fa', 'fa_version.h')


def update_file(path, replacements):
    with open(path, 'r', encoding='utf-8') as f:
        content = f.read()

    modified = content
    for pattern, repl in replacements:
        modified = re.sub(pattern, repl, modified)

    if modified != content:
        with open(path, 'w', encoding='utf-8', newline='\n') as f:
            f.write(modified)
        return True
    return False


def ensure_beta():
    changed = False

    if os.path.isfile(VERSION_FILE):
        with open(VERSION_FILE, 'r', encoding='utf-8') as f:
            lines = f.readlines()

        new_lines = []
        for line in lines:
            if re.match(r'^BetaChannel\s+\d', line):
                new_lines.append('BetaChannel        1\n')
                if not re.match(r'^BetaChannel\s+1', line):
                    changed = True
            elif re.match(r'^AppVersionOriginal\s+', line):
                parts = line.strip().split()
                orig_ver = parts[1] if len(parts) > 1 else ''
                if orig_ver and not orig_ver.endswith('beta') and not orig_ver.endswith('.beta'):
                    new_ver = orig_ver + '.beta'
                    new_lines.append(f'AppVersionOriginal {new_ver}\n')
                    changed = True
                else:
                    new_lines.append(line)
            else:
                new_lines.append(line)

        with open(VERSION_FILE, 'w', encoding='utf-8', newline='\n') as f:
            f.writelines(new_lines)

    if os.path.isfile(CORE_VERSION_H):
        if update_file(CORE_VERSION_H, [
            (r'constexpr auto AppBetaVersion = (false|true);', 'constexpr auto AppBetaVersion = true;')
        ]):
            changed = True

    if os.path.isfile(FA_VERSION_H):
        if update_file(FA_VERSION_H, [
            (r'constexpr auto AppFABetaVersion = (false|true);', 'constexpr auto AppFABetaVersion = true;')
        ]):
            changed = True

    print("Beta build configuration ensured.")
    return changed


if __name__ == '__main__':
    ensure_beta()
