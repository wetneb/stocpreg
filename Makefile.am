AM_CPPFLAGS = -I$(top_srcdir)/include $(BOOST_CFLAGS)

bin_PROGRAMS = parser learner morphism ccgbank

parser_SOURCES = include/frameelem.h include/framestring.h include/lexicon.h include/lexiconentry.h include/pregroupparser.h include/pregroup.h include/group.h include/groupparser.h include/morphism.h include/grouppregroup.h src/frameelem.cpp src/framestring.cpp src/main-parser.cpp src/pregroupparser.cpp src/pregroup.cpp src/group.cpp src/groupparser.cpp src/grouppregroup.cpp 
parser_LDADD = $(BOOST_LIBS)

learner_SOURCES = include/frameelem.h include/framestring.h include/lexicon.h include/lexiconentry.h include/pregroupparser.h include/pregroup.h include/learning.h include/group.h include/groupparser.h include/morphism.h include/grouppregroup.h src/frameelem.cpp src/framestring.cpp src/main-learner.cpp src/learning.cpp src/pregroupparser.cpp src/pregroup.cpp src/group.cpp src/groupparser.cpp src/grouppregroup.cpp
learner_LDADD = $(BOOST_LIBS)

morphism_SOURCES = include/lexicon.h include/lexiconentry.h include/pregroup.h include/group.h include/morphism.h include/grouppregroup.h src/pregroup.cpp src/group.cpp src/grouppregroup.cpp src/main-morphism.cpp
morphism_LDADD = $(BOOST_LIBS)

ccgbank_SOURCES = include/ccg.h src/ccg.cpp src/main-ccgbank.cpp include/morphism.h include/pregroup.h src/pregroup.cpp
ccgbank_LDADD = 

