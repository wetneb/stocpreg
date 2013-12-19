AM_CPPFLAGS = -I$(top_srcdir)/include $(BOOST_CFLAGS)

bin_PROGRAMS = parser learner

parser_SOURCES = include/frameelem.h include/framestring.h include/lexicon.h include/parser.h include/pregroup.h include/group.h src/frameelem.cpp src/framestring.cpp src/main-parser.cpp src/parser.cpp src/pregroup.cpp src/lexicon.cpp src/group.cpp 
parser_LDADD = $(BOOST_LIBS)

learner_SOURCES = include/frameelem.h include/framestring.h include/lexicon.h include/parser.h include/pregroup.h include/learning.h include/group.h src/frameelem.cpp src/framestring.cpp src/main-learner.cpp src/learning.cpp src/parser.cpp src/pregroup.cpp src/lexicon.cpp src/group.cpp
learner_LDADD = $(BOOST_LIBS)


