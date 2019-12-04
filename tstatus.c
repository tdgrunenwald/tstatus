#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "tstatus.h"

int
main(int argc, char **argv)
{
	struct sockaddr_un addr;
	int sock_fd, bytes_read;
	char buffer[MAX_STATUS_LEN];

	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

	if ((sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket error\n");
		return -1;
	}

	unlink(SOCKET_PATH);
	if (bind(sock_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1)
	{
		perror("bind error\n");
		return -1;
	}

	while (1)
	{
		if ((bytes_read = recvfrom(sock_fd, buffer, 500, 0, NULL, NULL)) == -1)
		{
			perror("recvfrom error\n");
			return bytes_read;
		}
		else
		{
			printf("read %u bytes: %.*s\n", bytes_read, bytes_read, buffer);
		}
	}

	close(sock_fd);
	return 0;
}
