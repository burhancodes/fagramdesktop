# 💻 [FAgram Desktop][fagram_desktop] – Unofficial Telegram client based on [Telegram Desktop][telegram_desktop]

This is the complete source code of FAgram Desktop.

[![Version](https://badge.fury.io/gh/telegramdesktop%2Ftdesktop.svg)](https://github.com/telegramdesktop/tdesktop/releases)
[![Build Status](https://github.com/fajox1/fagramdesktop/workflows/Windows./badge.svg)](https://github.com/fajox1/fagramdestkop/actions)

The source code is published under GPLv3 with OpenSSL exception, the license is available [here][license].

<a href="https://t.me/FAgramNews">
<img alt="Telegram" src="https://img.shields.io/badge/Telegram_Channel-0a0a0a?style=for-the-badge&logo=telegram">
</a>
<a href="https://t.me/FAgramChat">
<img alt="Telegram" src="https://img.shields.io/badge/Telegram_Chat-0a0a0a?style=for-the-badge&logo=telegram">
</a>

## Supported systems

The latest version is available for

* [Windows 7 and above (64 bit)](https://telegram.org/dl/desktop/win64) ([portable](https://telegram.org/dl/desktop/win64_portable))
* [Windows 7 and above (32 bit)](https://telegram.org/dl/desktop/win) ([portable](https://telegram.org/dl/desktop/win_portable))

## Third-party

* Qt 6 ([LGPL](http://doc.qt.io/qt-6/lgpl.html)) and Qt 5.15 ([LGPL](http://doc.qt.io/qt-5/lgpl.html)) slightly patched
* OpenSSL 3.2.1 ([Apache License 2.0](https://www.openssl.org/source/apache-license-2.0.txt))
* WebRTC ([New BSD License](https://github.com/desktop-app/tg_owt/blob/master/LICENSE))
* zlib 1.2.11 ([zlib License](http://www.zlib.net/zlib_license.html))
* LZMA SDK 9.20 ([public domain](http://www.7-zip.org/sdk.html))
* liblzma ([public domain](http://tukaani.org/xz/))
* Google Breakpad ([License](https://chromium.googlesource.com/breakpad/breakpad/+/master/LICENSE))
* Google Crashpad ([Apache License 2.0](https://chromium.googlesource.com/crashpad/crashpad/+/master/LICENSE))
* GYP ([BSD License](https://github.com/bnoordhuis/gyp/blob/master/LICENSE))
* Ninja ([Apache License 2.0](https://github.com/ninja-build/ninja/blob/master/COPYING))
* OpenAL Soft ([LGPL](https://github.com/kcat/openal-soft/blob/master/COPYING))
* Opus codec ([BSD License](http://www.opus-codec.org/license/))
* FFmpeg ([LGPL](https://www.ffmpeg.org/legal.html))
* Guideline Support Library ([MIT License](https://github.com/Microsoft/GSL/blob/master/LICENSE))
* Range-v3 ([Boost License](https://github.com/ericniebler/range-v3/blob/master/LICENSE.txt))
* Open Sans font ([Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0.html))
* Vazir font ([SIL Open Font License 1.1](https://github.com/rastikerdar/vazir-font/blob/master/OFL.txt))
* Emoji alpha codes ([MIT License](https://github.com/emojione/emojione/blob/master/extras/alpha-codes/LICENSE.md))
* xxHash ([BSD License](https://github.com/Cyan4973/xxHash/blob/dev/LICENSE))
* QR Code generator ([MIT License](https://github.com/nayuki/QR-Code-generator#license))
* CMake ([New BSD License](https://github.com/Kitware/CMake/blob/master/Copyright.txt))
* Hunspell ([LGPL](https://github.com/hunspell/hunspell/blob/master/COPYING.LESSER))

## Build instructions

* Windows [(32-bit)][win32] [(64-bit)][win64]
* [macOS][mac]
* [GNU/Linux using Docker][linux]

[//]: # (LINKS)
[fagram]: https://t.me/FAgramNews
[fagram_desktop]: https://desktop.telegram.org
[telegram_desktop]: https://github.com/telegramdesktop/tdesktop
[telegram_api]: https://core.telegram.org
[telegram_proto]: https://core.telegram.org/mtproto
[license]: LICENSE
[win32]: docs/building-win.md
[win64]: docs/building-win-x64.md
[mac]: docs/building-mac.md
[linux]: docs/building-linux.md
[preview_image]: https://raw.githubusercontent.com/telegramdesktop/tdesktop/dev/docs/assets/preview.png "Preview of FAgram Deskop"
