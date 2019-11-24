default: all

tstatus: tstatus.c
	gcc -o $@ tstatus.c

send-status: send-status.c
	gcc -o $@ send-status.c

all: tstatus send-status

clean:
	rm ./tstatus ./send-status
