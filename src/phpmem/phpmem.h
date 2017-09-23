#pragma once

#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <winnt.h>
#include <psapi.h>
#include <stdlib.h>

#define PHP_COMPILER_ID "VC14"
#define ZEND_DEBUG 0
#define ZEND_WIN32 1
#define PHP_WIN32 1
#include <php.h>

#define PHPMEM_NAME "phpmem"
#define PHPMEM_VERSION "1.0.0"
#include "memory.h"
#include "zend_args.h"
#include "class.h"

#pragma comment(lib, "php7.lib")