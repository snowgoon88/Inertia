# Standard things
# saves the variable $(d) that holds the current directory on the stack,
# and sets it to the current directory given in $(dir), 
# which was passed as a parameter by the parent rules.mk

sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)

# Subdirectories, if any, in random order

#dir	:= $(d)/test
#include		$(dir)/Rules.mk

# Next, we create an immediately evaluated variable $(OBJS_common) 
# that holds all the objects in that directory.
# We also create $(DEPS_common), which lists any automatic dependency files 
# generated later on.
# To the global variable $(CLEAN), we add the files that the rules present here 
# may create, i.e. the ones we want deleted by a make clean command.)

# Local rules and target
CORE_SRC_$(d)	:= $(d)/ship.cc $(d)/ship.h \
                   $(d)/coord_ang.cc $(d)/coord_ang.h \
                   $(d)/ref_frame.cc $(d)/ref_frame.h \
                   $(d)/utils.cc $(d)/utils.cc

CORE_OBJS_$(d)	:= $(d)/ship.o \
                   $(d)/coord_ang.o \
                   $(d)/ref_frame.o \
                   $(d)/utils.o

CORE_DEPS_$(d)	:= $(CORE_OBJS_$(d):%=%.d)

TGTS_SRC_$(d)   := $(d)/view_ship.cc

TGTS_$(d)	:= $(TGTS_SRC_$(d):%.cc=%)

DEPS_$(d)	:= $(TGTS_$(d):%=%.d)

#TGT_BIN		:= $(TGT_BIN) verbose_$(d) $(TGTS_$(d))
#TGT_BIN		:= $(TGT_BIN) $(CORE_OBJS_$(d))

TAR_SRC		:= $(TAR_SRC) $(CORE_SRC_$(d)) $(d)$/rules.mk

CLEAN		:= $(CLEAN) $(CORE_OBJS_$(d)) $(CORE_DEPS_$(d)) \
                   $(TGTS_$(d)) $(DEPS_$(d))
VERYCLEAN	:= $(VERYCLEAN) $(d)/*~

TAG_FILES	:= $(TAG_FILES) $(CORE_SRC_$(d))

# target local
# TGT_LIB		:= $(TGT_LIB) verbose_$(d) $(TGTS_$(d))

# global target
TGT_BIN		:= $(TGT_BIN) $(TGTS_$(d))

# Now we list the dependency relations relevant to the files in this subdirectory.
# Most importantly, while generating the objects listed here, we want to set 
# the target-specific compiler flags $(CF_TGT) to include a flag that adds 
# this directory to the include path, so that local headers may be included 
# using #include <localfile.h>, which is, as said, more portable 
# than local includes when the source directory is not the current directory.)


# Local CFLAGS
# Force remake if rules are changed
$(CORE_OBJS_$(d)):	$(d)/rules.mk

$(CORE_OBJS_$(d)): 	CF_TGT := -I$(d) -I/opt/local/include \
                                  -Wno-deprecated \
                                  -I$(SCIGL_ROOT)

# Local libs
# Force remake if rules are changed
$(TGTS_$(d)): $(d)/rules.mk

$(TGTS_$(d)):	CF_TGT := -I$(SCIGL_ROOT) -I$(d) -I/opt/local/include \
                          -I$(GLFW_HOME)/include \
                          -I$(ANTTW_HOME)/include \
                          -I$(INERTIA_ROOT)/src 
#                         -I$(EIGEN_ROOT)

ifeq ($(PLATFORM), Darwin)
$(TGTS_$(d)):	LF_TGT := -framework OpenGL -framework Cocoa \
                          -L/opt/local/lib \
                          -L$(ANTTW_HOME)/lib \
                          -lGLEW
#                         -lboost_program_options -lboost_thread-mt
$(TGTS_$(d)):	LL_TGT :=  $(CORE_OBJS_$(d)) \
                          lib/libscigl.a \
                          $(GLFW_HOME)/lib/cocoa/libglfw.a \
                          $(ANTTW_HOME)/lib/libAntTweakBar.dylib
else
$(TGTS_$(d)):	LF_TGT := -lGL -lGLU \
                          -L/opt/local/lib \
                          -lGLEW 
#                         -lboost_program_options -lboost_thread-mt
$(TGTS_$(d)):	LL_TGT :=  $(CORE_OBJS_$(d)) \
                          lib/libscigl.a \
                          $(GLFW_HOME)/lib/libglfw.a -pthread -lglfw -lGL -lX11 -lXrandr -lm

endif


#$(TGTS_$(d)):	LF_TGT := 

# $(TGTS_$(d)):	LL_TGT := $(GDK_LIBS) $(GTK_LIBS) \
# 			  $(UTILS_LIBS) \
# 	                  $(VID_LIBS) $(GST_LIBS) $(OPENCV_LIBS) \
# 	                  -lgthread-2.0 -lboost_thread

#$(CORE_OBJS_$(d)):	CF_TGT := -I. -I$(d) $(shell pkg-config --cflags gtkmm-2.4)
#$(OBJS_$(d)):	LF_TGT := -lgsl -lgslcblas -lm 
#$(OBJS_$(d)):	LL_TGT := $(S_LL_INET) cpp/core.a dana-cpp/dana.a

# $(d)/test_neurone:	$(d)/test_neurone.cc $(CORE_OBJS_$(d)) 
#			$(COMPLINK)

$(d)/view_ship:	$(d)/view_ship.cc $(CORE_OBJS_$(d))
	@echo "***** Generating $@"
	$(COMPLINK)

.PHONY : verbose_$(d)
verbose_$(d): $(TGTS_$(d))
	@echo "**** Generating $^"

# As a last step, we restore the value of the current directory variable $(d) 
# by taking it from the current location on the stack, and we "decrement" 
# the stack pointer by stripping away the .x suffix 
# we added at the top of this file.

# Standard things

-include	$(CORE_DEPS_$(d))

d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))

