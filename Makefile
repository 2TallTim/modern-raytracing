CC=c++
CFLAGS = --std=c++14 -Wall -g

all: raytrace

OFILES=sphere.o hitable_list.o rng.o raytrace.o

raytrace: $(OFILES)
	$(CC) $(OFILES) $(CFLAGS) -o $@

%.o: %.cpp %.hpp
	$(CC) -c $(CFLAGS) $<

test: raytrace
	./raytrace > test.ppm

clean:
	rm -rf *.o 