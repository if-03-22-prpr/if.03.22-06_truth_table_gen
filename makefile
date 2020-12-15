CC				= gcc
CCLINK			= g++
LIBS			=
CCOPTIONS 		= -Wall -pedantic -std=c17 -g
LDOPTIONS		=
COMMON_HDRS     = config.h general.h shortcut.h
HDRS			= bool_operand.h bool_term.h test_tt_gen.h $(COMMON_HDRS)

TEST = test_truth_table_gen
PROGRAM = truth_table_gen

TESTOBJECT  = tt_gen_test_driver.o
MAINOBJECT  = tt_gen_main_driver.o
SHARED_OBJS = shortcut.o truth_table_gen.o 
TEST_OBJS   = test_bool_operand.o test_bool_term.o
MANI_OBJ    = bool_term.o bool_operand.o 
OBJS =      $(SHARED_OBJS) $(MANI_OBJ) $(TEST_OBJS)

DOXY            = doxygen

all: $(PROGRAM)
	./$(PROGRAM)

$(TEST): $(OBJS) $(TESTOBJECT)
	$(CCLINK) -o $@ $(LDOPTIONS) $(OBJS) $(TESTOBJECT)

$(PROGRAM): $(OBJS) $(MAINOBJECT)
	$(CCLINK) -o $@ $(LDOPTIONS) $(OBJS) $(MAINOBJECT)

.PHONY: clean cleanall doxy test setsample setassignment definesample defineassignment assignmentfolder

clean:
	rm -f $(PROGRAM) $(TEST) $(TESTOBJECT) $(MAINOBJECT) $(OBJS)

cleanall:
	rm -f $(PROGRAM) $(TEST) $(TESTOBJECT) $(MAINOBJECT) $(OBJS) index.html
	rm -R html

doxy:
	$(DOXY)
	ln -s html/index.html index.html

test: $(TEST)
	./$(TEST)

%.o: %.c
	$(CC) $(CCOPTIONS) -c $<

#sets project as sample solution
setsample:
	cp bool_operand.c.sample bool_operand.c
	cp bool_operand.h.sample bool_operand.h
	cp bool_term.c.sample bool_term.c
	cp bool_term.h.sample bool_term.h
	cp tt_gen_main_driver.c.sample tt_gen_main_driver.c

#sets project as assignment
setassignment:
	cp bool_operand.c.assignment bool_operand.c
	cp bool_operand.h.assignment bool_operand.h
	cp bool_term.c.assignment bool_term.c
	cp bool_term.h.assignment bool_term.h
	cp tt_gen_main_driver.c.assignment tt_gen_main_driver.c

# defines current state of project as sample solution
definesample:
	cp bool_operand.c bool_operand.c.sample
	cp bool_operand.h bool_operand.h.sample
	cp bool_term.c bool_term.c.sample
	cp bool_term.h bool_term.h.sample
	cp tt_gen_main_driver.c tt_gen_main_driver.c.sample

# defines current sate of project as assignment
defineassignment:
	cp bool_operand.c bool_operand.c.assignment
	cp bool_operand.h bool_operand.h.assignment
	cp bool_term.c bool_term.c.assignment
	cp bool_term.h bool_term.h.assignment
	cp tt_gen_main_driver.c tt_gen_main_driver.c.assignment

# creates a folder which can serve as a publishable assignment
assignmentfolder:
	make setassignment
	make doxy
	mkdir ../assignment
	cp -R * ../assignment
	rm ../assignment/*.sample
	rm ../assignment/*.assignment
	make cleanall
