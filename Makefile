CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall
SRCS = main.cpp network.cpp util.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = router


all: $(TARGET)


$(TARGET): $(OBJS)
$(CXX) $(CXXFLAGS) -o $@ $(OBJS)


%.o: %.cpp
$(CXX) $(CXXFLAGS) -c $<


clean:
rm -f $(OBJS) $(TARGET)