#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "tstatus.h"

int
main (int argc, char **argv)
{
	struct sockaddr_un addr;
	char *mesg;
	int sock_fd;

	if (argc > 1)
		mesg = argv[1];
	else
		return -1;

	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

	if ((sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket error\n");
		return -1;
	}

	if (sendto(sock_fd, mesg, strnlen(mesg, MAX_STATUS_LEN), 0, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) < 1)
	{
		perror("sendto error\n");
		return -1;
	}

	close(sock_fd);
	return 0;
}
