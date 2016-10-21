
LIB = ./lib
BIN = ./bin
SRC = ./src
TEST = ./result
NAME = 
FLAGS = -O4 -Wunused-result

chromosome:
	mkdir -p $(LIB)
	gcc $(FLAGS) -c $(SRC)/chromosome.cpp -o $(LIB)/chromosome.o

population:
	mkdir -p $(LIB)
	gcc $(FLAGS) -c $(SRC)/population.cpp -o $(LIB)/population.o

image:
	mkdir -p $(LIB)
	gcc $(FLAGS) -c $(SRC)/image.cpp -o $(LIB)/image.o

utils:
	make image
	gcc $(FLAGS) -c $(SRC)/tsp_utils.cpp -o $(LIB)/tsp_utils.o	

library:
	make chromosome
	make population
	make image
	make utils

ex1:
	make chromosome
	mkdir -p $(BIN)
	gcc $(FLAGS) \
	$(SRC)/exercise1.cpp -o $(BIN)/exercise1.bin \
	$(LIB)/chromosome.o

ex2:
	make library
	mkdir -p $(BIN)
	gcc $(FLAGS) \
	$(SRC)/exercise2.cpp -o $(BIN)/exercise2.bin \
	$(LIB)/chromosome.o \
	$(LIB)/population.o \
	$(LIB)/image.o \
	$(LIB)/tsp_utils.o -lm

ex3:
	make library
	mkdir -p $(BIN)
	gcc $(FLAGS) \
	$(SRC)/exercise3.cpp -o $(BIN)/exercise3.bin \
	$(LIB)/chromosome.o \
	$(LIB)/population.o \
	$(LIB)/image.o \
	$(LIB)/tsp_utils.o -lm


run1:
	mkdir -p $(TEST)
	$(BIN)/exercise1.bin
	mkdir -p $(TEST)/exercise1
	mv $(TEST)/*.txt ./$(TEST)/exercise1

run2:
	mkdir -p $(TEST)
	$(BIN)/exercise2.bin
	mkdir -p $(TEST)/exercise2
	mv $(TEST)/*.gif ./$(TEST)/exercise2
	mv $(TEST)/*.txt ./$(TEST)/exercise2

run3: 
	mkdir -p $(TEST)
	for size in 10 50 100 500 ; do \
		for mutation in 1 10 50 ; do \
			for i in 1 2 3 ; do \
				$(BIN)/exercise3.bin "$$mutation" "$$size" ; \
				mkdir -p $(TEST)/exercise3/"$$size"_"$$mutation"_"$$i" ; \
				mv $(TEST)/*.gif ./$(TEST)/exercise3/"$$size"_"$$mutation"_"$$i" ; \
				mv $(TEST)/*.txt ./$(TEST)/exercise3/"$$size"_"$$mutation"_"$$i" ; \
			done \
		done \
	done

all:
	make ex1 > /dev/null
	make ex2 > /dev/null
	make ex3 > /dev/null
	make run1
	make run2
	make run3

clean_test:
	rm -f -r $(TEST)

clean_lib:
	rm -f -r $(LIB)

clean_bin:
	rm -r -f $(BIN)

clean:
	@make clean_test
	@make clean_lib
	@make clean_bin

