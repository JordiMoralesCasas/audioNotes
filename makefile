# ======================
# Variables
# ======================
CC=g++
OPT=-Wall

final : out/main.o out/audio.o
	$(CC) $(OPT) out/main.o out/audio.o -o final -lm

out/main.o : lib/main.cpp
	$(CC) $(OPT) -c lib/main.cpp -o out/main.o -lm

out/audio.o : lib/audio.cpp
	$(CC) $(OPT) -c lib/audio.cpp -o out/audio.o -lm

# ======
# Clean
# ======
clean :
	rm -f out/*.o
realclean : clean
	rm -f final
