/*
 * This file is in the public domain.
 *
 * Author: Kyle Isom <kyle@tyrfingr.is>
 */

#include <sys/types.h>

#include <stdlib.h>
#include <unistd.h>
#include "def.h"

int
callgocommand(char *prog)
{
	char	*cmd[] = {"sh", "-c", NULL, NULL};

	cmd[2] = prog;
	if (FALSE == shellcmdoutput(cmd, NULL, 0, 1)) {
		return(FALSE);
	}

	if ((curbp->b_flag & (BFCHG | BFDIRTY)) == 0) {
		if (fchecktime(curbp) != TRUE) {
			curbp->b_flag |= BFDIRTY;
		}
	}

	if ((curbp->b_flag & (BFDIRTY | BFIGNDIRTY)) == BFDIRTY) {
		if ((FALSE) == dorevert()) {
			return (FALSE);
		}
		redraw(0, 0);
		eerase();
		ewprintf("%s updated.", curbp->b_fname);
	}
	return (TRUE);
}

int
goimports(int f, int n)
{
	int	 rv = FALSE;
	char	*cmd = NULL;
	char	*gopath = NULL;

	if (NULL == (gopath = getenv("GOPATH"))) {
		ewprintf("GOPATH not set.");
		return (FALSE);
	}

	if (-1 == asprintf(&cmd, "%s/bin/goimports -l -w %s", gopath, curbp->b_fname)) {
		return (FALSE);
	}

	rv = callgocommand(cmd);
	free(cmd);
	return rv;
}

int
gobuild(int f, int n)
{
	char	  wd[NFILEN+1];
	int	  rv = FALSE;

	if (NULL == getcwd(wd, NFILEN)) {
		ewprintf("Working directory is too long.");
		return (FALSE);
	} else if (-1 == chdir(curbp->b_cwd)) {
		ewprintf("Failed to change directory.");
		return (FALSE);
	}

	ewprintf("Building package...");
	rv = callgocommand("go build");
	if (-1 == chdir(wd)) {
		ewprintf("Failed to change directory.");
		return (FALSE);
	}
	return rv;
}

int
gobuildall(int f, int n)
{
	char	  wd[NFILEN+1];
	int	  rv = FALSE;

	if (NULL == getcwd(wd, NFILEN)) {
		ewprintf("Working directory is too long.");
		return (FALSE);
	} else if (-1 == chdir(curbp->b_cwd)) {
		ewprintf("Failed to change directory.");
		return (FALSE);
	}

	ewprintf("Building all subpackages...");
	rv = callgocommand("go build ./...");
	if (-1 == chdir(wd)) {
		ewprintf("Failed to change directory.");
		return (FALSE);
	}
	return rv;
}

int
gotestcover(int f, int n)
{
	char	  wd[NFILEN+1];
	int	  rv = FALSE;

	if (NULL == getcwd(wd, NFILEN)) {
		ewprintf("Working directory is too long.");
		return (FALSE);
	} else if (-1 == chdir(curbp->b_cwd)) {
		ewprintf("Failed to change directory.");
		return (FALSE);
	}

	ewprintf("Testing with code coverage...");
	rv = callgocommand("go test -cover");
	if (-1 == chdir(wd)) {
		ewprintf("Failed to change directory.");
		return (FALSE);
	}
	return rv;
}

int
gotest(int f, int n)
{
	char	  wd[NFILEN+1];
	int	  rv = FALSE;

	if (NULL == getcwd(wd, NFILEN)) {
		ewprintf("Working directory is too long.");
		return (FALSE);
	} else if (-1 == chdir(curbp->b_cwd)) {
		ewprintf("Failed to change directory.");
		return (FALSE);
	}

	ewprintf("Testing current package...");
	rv = callgocommand("go test");
	if (-1 == chdir(wd)) {
		ewprintf("Failed to change directory.");
		return (FALSE);
	}
	return rv;
}

int
gotestall(int f, int n)
{
	char	  wd[NFILEN+1];
	int	  rv = FALSE;

	if (NULL == getcwd(wd, NFILEN)) {
		ewprintf("Working directory is too long.");
		return (FALSE);
	} else if (-1 == chdir(curbp->b_cwd)) {
		ewprintf("Failed to change directory.");
		return (FALSE);
	}

	ewprintf("Testing all subpackages...");
	rv = callgocommand("go test ./...");
	if (-1 == chdir(wd)) {
		ewprintf("Failed to change directory.");
		return (FALSE);
	}
	return rv;
}

int
goinstall(int f, int n)
{
	char	  wd[NFILEN+1];
	int	  rv = FALSE;

	if (NULL == getcwd(wd, NFILEN)) {
		ewprintf("Working directory is too long.");
		return (FALSE);
	} else if (-1 == chdir(curbp->b_cwd)) {
		ewprintf("Failed to change directory.");
		return (FALSE);
	}

	ewprintf("Installing current package...");
	rv = callgocommand("go install ./...");
	if (-1 == chdir(wd)) {
		ewprintf("Failed to change directory.");
		return (FALSE);
	}
	return rv;
}

int
goinstallall(int f, int n)
{
	char	  wd[NFILEN+1];
	int	  rv = FALSE;

	if (NULL == getcwd(wd, NFILEN)) {
		ewprintf("Working directory is too long.");
		return (FALSE);
	} else if (-1 == chdir(curbp->b_cwd)) {
		ewprintf("Failed to change directory.");
		return (FALSE);
	}

	ewprintf("Installing all subpackages...");
	rv = callgocommand("go install ./...");
	if (-1 == chdir(wd)) {
		ewprintf("Failed to change directory.");
		return (FALSE);
	}
	return rv;
}

