AM_CPPFLAGS = -I$(top_srcdir)/include $(BOOST_CFLAGS)

bin_PROGRAMS = parser learner

parser_SOURCES = include/frameelem.h include/framestring.h include/lexicon.h include/lexiconentry.h include/pregroupparser.h include/pregroup.h include/group.h include/groupparser.h src/frameelem.cpp src/framestring.cpp src/main-parser.cpp src/pregroupparser.cpp src/pregroup.cpp src/group.cpp src/groupparser.cpp 
parser_LDADD = $(BOOST_LIBS)

learner_SOURCES = include/frameelem.h include/framestring.h include/lexicon.h include/lexiconentry.h include/pregroupparser.h include/pregroup.h include/learning.h include/group.h include/groupparser.h src/frameelem.cpp src/framestring.cpp src/main-learner.cpp src/learning.cpp src/pregroupparser.cpp src/pregroup.cpp src/group.cpp src/groupparser.cpp
learner_LDADD = $(BOOST_LIBS)


