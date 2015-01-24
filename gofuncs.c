/*
 * This file is in the public domain.
 *
 * Author: Kyle Isom <kyle@tyrfingr.is>
 */

#include <sys/types.h>

#include "def.h"

int
goimports(int f, int n)
{
	char	*cmd = NULL;

	if (f & FFARG) {
		/* not implemented yet */
	}

	if (-1 == asprintf(&cmd, "goimports -l -w %s", curbp->b_fname)) {
		return (FALSE);
	}
	
	if (-1 == system(cmd)) {
		return (FALSE);
	}

	if ((TRUE) == checkdirty(curbp)) {
		if ((FALSE) == revertbuffer(FFARG,0)) {
			return (FALSE);
		}
	}

	return redraw(0, 0);
}
