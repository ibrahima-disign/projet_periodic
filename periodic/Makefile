CC=gcc
CFLAGS=-Wall -D_POSIX_C_SOURCE=200809L -std=c99 -O2 -g
LDFLAGS=-g
TARGET=period
LIBS=-lm

all: $(TARGET)
$(TARGET): period.o message.o helpers.o
			$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)
			
launch_daemon.o : header.h
message.o : message.h header.h
period.o : helpers.h header.h
helpers.o : helpers.h message.h header.h 
periodic.o : helpers.h message.h header.h

clean:
			rm -f *.o core fic now when now periodic launch_daemon message
mrproper: clean
			rm -f $(TARGET) 
