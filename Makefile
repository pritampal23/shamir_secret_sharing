CC = g++
CFLAGS = -c

#Basic implementation of Shamir Secret Sharing

secret_sharing: secret_sharing.o PowerMod.o reconstruct.o
	$(CC) PowerMod.o reconstruct.o secret_sharing.o -lntl -lgmp -lm
secret_sharing.o: secret_sharing.cpp
	$(CC) $(CFLAGS) secret_sharing.cpp 
PowerMod.o: PowerMod.cpp
	$(CC) $(CFLAGS) PowerMod.cpp
reconstruct.o: reconstruct.cpp
	$(CC) $(CFLAGS) reconstruct.cpp

#Clean the executables
CLEAN:
	rm -rf *.o *.ou
