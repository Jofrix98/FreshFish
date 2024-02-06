CXX = g++
CXXFLAGS += -g -Wall

GRAPHICS_FLAGS = $(shell pkg-config --cflags librsvg-2.0)
GRAPHICS_CXXFLAGS = $(if $(GRAPHICS_FLAGS),$(GRAPHICS_FLAGS),-DNO_GRAPHICS)

LDFLAGS += $(shell pkg-config --libs librsvg-2.0)

.DEFAULT_GOAL := all

debug:

all: debug

SOURCES =
SOURCES += constantes.cpp
SOURCES += position.cpp
SOURCES += melangeur.cpp
SOURCES += console_pad.cpp
SOURCES += pioche.cpp
SOURCES += joueur.cpp
SOURCES += partie.cpp

DRAW_SOURCES =
DRAW_SOURCES += plateau.cpp

OBJECTS = $(SOURCES:.cpp=.o)
DRAW_OBJECTS = $(DRAW_SOURCES:.cpp=.o)

$(OBJECTS) : %.o : %.cpp
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

$(DRAW_OBJECTS) : %.o : %.cpp
	$(CXX) -MMD $(CXXFLAGS) $(GRAPHICS_CXXFLAGS) -c $< -o $@

CLEAN_OBJECTS = $(OBJECTS) $(DRAW_OBJECTS)
TARGETS = 

########## test_graphe ##########

GRAPHE_SOURCES = test_graphe.cpp
GRAPHE_OBJECTS = $(GRAPHE_SOURCES:.cpp=.o)

test_graphe : $(GRAPHE_OBJECTS) $(OBJECTS) $(DRAW_OBJECTS)
	$(CXX) -MMD $^ -o $@ $(LDFLAGS)
	
$(GRAPHE_OBJECTS): %.o : %.cpp
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

all : test_graphe
TARGETS += test_graphe
CLEAN_OBJECTS += $(GRAPHE_OBJECTS)

########## test_routes ##########

ROUTES_SOURCES = test_routes.cpp
ROUTES_OBJECTS = $(ROUTES_SOURCES:.cpp=.o)

test_routes : $(ROUTES_OBJECTS) $(OBJECTS) $(DRAW_OBJECTS)
	$(CXX) -MMD $^ -o $@ $(LDFLAGS)
	
$(ROUTES_OBJECTS): %.o : %.cpp
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

all : test_routes
TARGETS += test_routes
CLEAN_OBJECTS += $(ROUTES_OBJECTS)

########## test_partie ##########

PARTIE_SOURCES = test_partie.cpp
PARTIE_OBJECTS = $(PARTIE_SOURCES:.cpp=.o)

test_partie : $(PARTIE_OBJECTS) $(OBJECTS) $(DRAW_OBJECTS)
	$(CXX) -MMD $^ -o $@ $(LDFLAGS)
	
$(PARTIE_OBJECTS): %.o : %.cpp
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

all : test_partie
TARGETS += test_partie
CLEAN_OBJECTS += $(PARTIE_OBJECTS)

########## cleanup ##########
DEPS = $(CLEAN_OBJECTS:.o=.d)

clean:
	@rm -f $(DEPS) $(TARGETS) $(CLEAN_OBJECTS)

-include $(DEPS)
