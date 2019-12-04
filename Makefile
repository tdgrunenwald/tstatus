all: tstatus send-status

tstatus: tstatus.h
send-status: tstatus.h

clean:
	rm tstatus send-status

.PHONY: all clean
