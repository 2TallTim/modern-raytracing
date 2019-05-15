CC=c++
CFLAGS = --std=c++14 -Wall

all: raytrace

OFILES=raytrace.o vec3.o

raytrace: $(OFILES)
	$(CC) $(OFILES) $(CFLAGS) -o $@
	echo $@

%.o: %.cpp
	$(CC) -c $(CFLAGS) $<
test:
	./raytrace > test.ppm

clean:
	rm -rf *.o 