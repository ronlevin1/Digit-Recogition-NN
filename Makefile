CC=g++
CXXFLAGS= -Wall -Wvla -Wextra -Werror -g -std=c++14
LDFLAGS= -lm
HEADERS= Matrix.h Activation.h Dense.h MlpNetwork.h
OBJS= Matrix.o Activation.o Dense.o MlpNetwork.o main.o

%.o : %.c


mlpnetwork: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJS) : $(HEADERS)

.PHONY: clean
clean:
	rm -rf *.o
	rm -rf mlpnetwork

# CLA:
# $./mlpnetwork parameters/w1 parameters/w2 parameters/w3 parameters/w4 images/b1 images/b2 images/b3 images/b4
#