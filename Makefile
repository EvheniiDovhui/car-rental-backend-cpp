CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Iinclude/** -Ilibs/crow/include -Ilibs/asio/include

LDFLAGS = -lws2_32 -lmswsock

SRC = $(wildcard src/*.cpp src/**/*.cpp)
OUT = build/server

all: $(OUT)

$(OUT): main.cpp $(SRC)
	$(CXX) $(CXXFLAGS) main.cpp $(SRC) -o $(OUT) $(LDFLAGS)

run:
	./build/server

clean:
	rm -rf build/*.o $(OUT)
