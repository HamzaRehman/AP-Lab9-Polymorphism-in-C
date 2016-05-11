CXX = gcc
OUTPUT_FLAGS = -o
COMPILE_FLAGS = -c
OBJS = task-01.o classes.o
PHONY_FILES = *.o

task-01 : ${OBJS}
	${CXX} ${OUTPUT_FLAGS} $@ ${OBJS}
	make clean

task-01.o : task-01.c
	${CXX} ${COMPILE_FLAGS} task-01.c

classes.o : classes.c
	${CXX} ${COMPILE_FLAGS} classes.c

clean :
	rm -rf ${PHONY_FILES}
