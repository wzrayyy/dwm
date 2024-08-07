/* See LICENSE file for copyright and license details. */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

void
die(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	if (fmt[0] && fmt[strlen(fmt)-1] == ':') {
		fputc(' ', stderr);
		perror(NULL);
	} else {
		fputc('\n', stderr);
	}

	exit(1);
}

void *
ecalloc(size_t nmemb, size_t size)
{
	void *p;

	if (!(p = calloc(nmemb, size)))
		die("calloc:");
	return p;
}

void
notify(const char *fmt, ...)
{
	va_list ap;
	char cmd[1024] = "nt() { notify-send \"$*\"; }; nt  ";
	int cmd_size = strlen(cmd)-1;

	va_start(ap, fmt);
	vsnprintf(cmd+cmd_size, 1024-cmd_size, fmt, ap);
	va_end(ap);

	system(cmd);
}
