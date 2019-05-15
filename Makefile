CC=c++
CFLAGS = --std=c++14 -Wall

all: raytrace

OFILES=vec3.o ray.o raytrace.o sphere.o hitable.o hitable_list.o rng.o

raytrace: $(OFILES)
	$(CC) $(OFILES) $(CFLAGS) -o $@

%.o: %.cpp %.hpp
	$(CC) -c $(CFLAGS) $<

test: raytrace
	./raytrace > test.ppm

clean:
	rm -rf *.o 