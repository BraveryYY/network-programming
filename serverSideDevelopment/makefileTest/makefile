Object = file.o file2.o

HelloWorld:$(Object)
	@echo liking....
	@g++ $(Object) -o HelloWorld
file.o:file.h

file2.o:file.h

clean:
	@echo cleaning
	@rm -rf *.o HelloWorld
