
CC = g++

COMPILE = $(CC) $(INCLUDES) ${FLAGS} $(LIBS)

SRC_DIR = .
DST_DIR = .

TARGET = planner

INCLUDES= -I/usr/include

LIBS = -L/usr/lib

OSFLAGS = -Dlinux
CFLAGS = -O3 -Wall -g
FLAGS = ${OSFLAGS} ${CFLAGS}

LDFLAGS = -lgsl -lgslcblas

SRCS = mdp.cpp policy.cpp utils.cpp matrix.cpp algorithms.cpp planner.cpp

OBJS = $(SRCS:.cpp=.o)

all::	$(TARGET)

.cpp.o:
	$(COMPILE) -c -o $@ $(@F:%.o=%.cpp)

planner: $(OBJS)
	$(COMPILE) -o $@ $(OBJS) ${LDFLAGS}

clean:
	rm -f $(TARGET) $(OBJS) *~

