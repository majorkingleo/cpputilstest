#!/usr/bin/env bash
cd "$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"  # cd current directory

iconv -f ASCII -t utf16le < in.txt > expected-utf16le.txt
iconv -f ASCII -t utf32le < in.txt > expected-utf32le.txt
