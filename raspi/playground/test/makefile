CC = gcc
DIALECT = c99
OPTIMIZATION = -O0
CFLAGS = -std=$(DIALECT) $(OPTIMIZATION) -Wall
RM = rm -rf
TARGET = hello

SRCDIR = src
OBJDIR = obj
BUILD = build

DIRSTRUCT = $(shell find $(SRCDIR) -type d)

SRCS = $(shell find $(SRCDIR) -name '*.c')
OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))

all: $(BUILD)/$(TARGET)

$(BUILD)/$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	@echo "============="
	@echo "Linking the target $@"
	@echo "============="
	$(CC) $(OBJS) $(LDFLAGS) -o $@
	@echo -- Link finished --

$(OBJDIR)/%.o: %.c
	@echo '> Building C file $<'
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

#buildrepo:
#	@$(call make-repo)

#define make-repo
#   for dir in $(SRCDIRS); \
#   do \
#	mkdir -p $(OBJDIR)/$$dir; \
#   done
#endef

.PHONY: all clean

clean:
	@echo 'Cleaning...Done!'
	@$(RM) $(OBJDIR) $(BUILD)

