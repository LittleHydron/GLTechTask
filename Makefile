CC := g++
CFLAGS := -std=c++17 -Wall -Wextra -IFileSearchLibrary -IThreadPoolLibrary
LDFLAGS := -pthread

APP_SRC := app/main.cpp
APP_OBJ := $(patsubst %.cpp, %.o, $(APP_SRC))

FileSearch_SRC := FileSearchLibrary/FileSearch.cpp
FileSearch_OBJ := $(patsubst %.cpp, %.o, $(FileSearch_SRC))
FileSearch_LIB := libFileSearch.a

ThreadPool_SRC := ThreadPoolLibrary/ThreadPool.cpp
ThreadPool_OBJ := $(patsubst %.cpp, %.o, $(ThreadPool_SRC))
ThreadPool_LIB := libThreadPool.a

.PHONY: all clean

all: $(FileSearch_LIB) $(ThreadPool_LIB) GLTechTask

GLTechTask: $(APP_OBJ) $(FileSearch_LIB) $(ThreadPool_LIB)
	$(CC) $(CFLAGS) $(LDFLAGS) $(APP_OBJ) -L. -lFileSearch -lThreadPool -o $@

$(APP_OBJ): $(APP_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(FileSearch_LIB): $(FileSearch_OBJ)
	ar rcs $@ $^

$(FileSearch_OBJ): $(FileSearch_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(ThreadPool_LIB): $(ThreadPool_OBJ)
	ar rcs $@ $^

$(ThreadPool_OBJ): $(ThreadPool_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f GLTechTask $(APP_OBJ) $(FileSearch_OBJ) $(ThreadPool_OBJ) $(FileSearch_LIB) $(ThreadPool_LIB)
