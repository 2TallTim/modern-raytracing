CC=c++
CFLAGS = --std=c++14 -Wall -O3 -lpthread

all: raytrace

OFILES=sphere.o hitable_list.o rng.o raytrace.o bvh.o

raytrace: $(OFILES)
	$(CC) $(OFILES) $(CFLAGS) -o $@

%.o: %.cpp %.hpp
	$(CC) -c $(CFLAGS) $<

test: raytrace
	./raytrace test.ppm

clean:
	rm -rf *.o 