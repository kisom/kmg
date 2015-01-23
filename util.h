/*
 * utility functions ported from OpenBSD's libutil
 */

#include <sys/types.h>

/*
 * fparseln() specific operation flags.
 */
#define FPARSELN_UNESCESC	0x01
#define FPARSELN_UNESCCONT	0x02
#define FPARSELN_UNESCCOMM	0x04
#define FPARSELN_UNESCREST	0x08
#define FPARSELN_UNESCALL	0x0f

char   *fparseln(FILE *, size_t *, size_t *, const char[3], int);

