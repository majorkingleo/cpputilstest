#!/usr/bin/env bash
cd "$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"  # cd current directory

SOURCE_ENCODING="ISO-8859"

iconv -f ${SOURCE_ENCODING} -t utf16le < in.txt > expected-utf16le.txt
iconv -f ${SOURCE_ENCODING} -t utf32le < in.txt > expected-utf32le.txt

