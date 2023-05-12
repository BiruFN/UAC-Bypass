#pragma once

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
// Windows ヘッダー ファイル
#include <windows.h>

#include "detours.h"

#include <consoleapi.h>
#include <winscard.h>
#include <Psapi.h>

#include <cstdio>
#include <iostream>
#include <string>
#include <locale>
