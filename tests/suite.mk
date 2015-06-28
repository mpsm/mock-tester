OBJDIR= testobj/$(SUITE)
SRCDIR= ../src
CC= gcc
CFLAGS= -DUNITTEST -I . -O0 -g

TESTOBJS=$(patsubst %.c,$(OBJDIR)/%.o,$(TESTSRCS))

all: $(OBJDIR)/test-$(SUITE).xml

$(OBJDIR)/test-$(SUITE).xml: $(OBJDIR)/test-$(SUITE)
	-CMOCKA_MESSAGE_OUTPUT=xml $< | grep -v "<?xml" | grep -v "testsuites>" > $@

$(OBJDIR)/test-$(SUITE): $(TESTOBJS)
	echo "#include \"tests.h\"\nRUN($(SUITE))" | $(CC) $(CFLAGS) $^ -o $@ -x c - -lcmocka

$(OBJDIR)/%.o: $(SRCDIR)/$(SUITE)/%.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f $(TESTOBJS) $(OBJDIR)/test-$(SUITE) $(OBJDIR)/test-$(SUITE).xml

