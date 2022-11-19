#pragma once
#define _POSIX_THREAD_SAFE_FUNCTIONS
#include "ansi_colour.h"

#define LOG_ERROR   ANSI_RED    "error"   ANSI_RESET
#define LOG_WARNING ANSI_YELLOW "warning" ANSI_RESET
#define LOG_INFO    ANSI_GREEN  "info"    ANSI_RESET
#define LOG_STREAM stderr

void __lprintf(const char *tag, const char *fmt, ...);

#include <stdio.h>
#ifdef __FILENAME__
#define ___FNANE __FILENAME__
#else
#define ___FNANE __FILE__
#endif

#define lprintf fprintf(LOG_STREAM, "(" ANSI_YELLOW "%s" ANSI_RESET \
				":" ANSI_YELLOW "%d" ANSI_RESET ") \t", ___FNANE, __LINE__ ),\
				__lprintf

