DIR_INC = ./include 
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin

SRC = $(wildcard ${DIR_SRC}/*.c)  
OBJ = $(patsubst %.c,${DIR_OBJ}/%.o,$(notdir ${SRC})) 

TARGET = seek_io copy tee_command cp_command

BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = gcc
CFLAGS = -g -Wall -I${DIR_INC}

#${BIN_TARGET} : ${OBJ}
#	$(CC)  $(OBJ)  -o  $@

all:$(TARGET)   #设置了一个最终目标，是生成两个可执行文件，否则只会生成seek_io一个可执行文件（默认）
	@echo ....

seek_io:$(filter-out $(DIR_OBJ)/copy.o $(DIR_OBJ)/tee_command.o $(DIR_OBJ)/cp_command.o,$(OBJ))
	$(CC) $^ -o $(DIR_BIN)/$@

copy:$(filter-out $(DIR_OBJ)/seek_io.o $(DIR_OBJ)/tee_command.o $(DIR_OBJ)/cp_command.o,$(OBJ))
	$(CC) $^ -o $(DIR_BIN)/$@

tee_command:$(filter-out $(DIR_OBJ)/seek_io.o $(DIR_OBJ)/copy.o $(DIR_OBJ)/cp_command.o,$(OBJ))
	$(CC) $^ -o $(DIR_BIN)/$@

cp_command:$(filter-out $(DIR_OBJ)/seek_io.o $(DIR_OBJ)/copy.o $(DIR_OBJ)/tee_command.o,$(OBJ))
	$(CC) $^ -o $(DIR_BIN)/$@
    
${DIR_OBJ}/%.o : ${DIR_SRC}/%.c 
	$(CC) $(CFLAGS)  -c  $< -o $@ 
.PHONY:clean
clean:
	#find ${DIR_OBJ} -name *.o -exec rm -rf {}
	-rm $(DIR_OBJ)/*.o
