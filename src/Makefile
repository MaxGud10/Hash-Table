# .PHONY: all clean rebuild
# CC=g++
# ASM=nasm
# ASMFLAGS = -fwin64
# CFLAGS = -O3 -mavx -masm=intel
# WARNINGS=-Wshadow -Winit-self -Wcast-align -Wundef -Wfloat-equal -Winline -Wredundant-decls \
#  	 -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default \
# 	 -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy \
# 	 -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers \
# 	 -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing \
# 	 -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE 
# SOURCES_CPP = main.cpp HashTable/hash_table_func.cpp HashTable/hash_table_log.cpp HashTable/hash_func.cpp \
# 	      DoubleLinkedList/fast_list_func.cpp DoubleLinkedList/fast_list_log.cpp \
#               TextPreparer/text_preparer.cpp
# SOURCES_ASM = DoubleLinkedList/my_strcmp.asm	 		 
# OBJECTS=$(SOURCES_CPP:.cpp=.o) $(SOURCES_ASM:.asm=.o)
# EXECUTABLE=hash_table_test

# all: $(EXECUTABLE)

# $(EXECUTABLE): $(OBJECTS)
# 	$(CC) $(WARNINGS) $(CFLAGS) $^ -o $@

# %.o : %.cpp
# 	$(CC) $(WARNINGS) -c $(CFLAGS) $< -o $@                    

# %.o : %.asm  
# 	$(ASM) $(ASMFLAGS) $< -o $@

# clean:
# 	 rm -f *.o hash_table_test
# 	 rm -f DoubleLinkedList/*.o
# 	 rm -f HashTable/*.o
# 	 rm -f TextPreparer/*.o

# rebuild: clean all

.PHONY: all clean rebuild profile perf-report hotspot

CC := g++
ASM := nasm
ASMFLAGS := -fwin64
CFLAGS := -O3 -mavx -mavx2 -masm=intel 
INPUT_FILE := hamlet.txt


WARNINGS := -Wshadow -Winit-self -Wcast-align -Wundef -Wfloat-equal -Winline \
            -Wredundant-decls -Wunreachable-code -Wmissing-declarations \
            -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ \
            -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion \
            -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 \
            -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers \
            -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo \
            -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel \
            -Wtype-limits -Wwrite-strings -Werror=vla -DNDEBUG -D_EJUDGE_CLIENT_SIDE

SOURCES_CPP := main.cpp \
               HashTable/hash_table_func.cpp \
               HashTable/hash_table_log.cpp \
               HashTable/hash_func.cpp \
               DoubleLinkedList/fast_list_func.cpp \
               DoubleLinkedList/fast_list_log.cpp \
               TextPreparer/text_preparer.cpp

SOURCES_ASM = DoubleLinkedList/my_strcmp.asm	 		 
OBJECTS=$(SOURCES_CPP:.cpp=.o) $(SOURCES_ASM:.asm=.o)
EXECUTABLE := hash_table_test

PERF_PATH := /usr/lib/linux-tools/$(shell ls /usr/lib/linux-tools/ | head -1)/perf

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(WARNINGS) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(WARNINGS) -c $(CFLAGS) $< -o $@

%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -f *.o $(EXECUTABLE)
	rm -f DoubleLinkedList/*.o
	rm -f HashTable/*.o
	rm -f TextPreparer/*.o
	rm -f perf.data gmon.out callgrind.out.*


rebuild: clean all

profile:
	$(PERF_PATH) record -g ./$(EXECUTABLE) $(INPUT_FILE)

perf-report:
	$(PERF_PATH) report -n --stdio

hotspot: profile
	hotspot perf.data

profile-gprof:
	$(MAKE) CFLAGS="$(CFLAGS) -pg" rebuild
	./$(EXECUTABLE)
	gprof ./$(EXECUTABLE) gmon.out > gprof-analysis.txt

profile-valgrind:
	valgrind --tool=callgrind --callgrind-out-file=callgrind.out ./$(EXECUTABLE)