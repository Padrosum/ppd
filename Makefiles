# Değişken Tanımlamaları
CC = gcc
CFLAGS = -Wall -Wextra -O2 -D_GNU_SOURCE
LDFLAGS = -lm
TARGET = ppd
# Derlenecek nesne dosyaları
OBJ = main.o cJSON.o

# Varsayılan hedef (Sadece 'make' yazınca çalışır)
all: $(TARGET)

# Ana programı bağlama (Linking)
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)
	@echo "--- [✔] ppd başarıyla derlendi! ---"

# .c dosyalarını .o dosyalarına dönüştürme (Compiling)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Temizlik: Derleme artıklarını siler
clean:
	rm -f *.o $(TARGET)
	@echo "--- [!] Temizlik tamamlandı. ---"

# Kurulum: Programı /usr/local/bin altına kopyalar
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/
	@echo "--- [✔] ppd sisteme kuruldu. Artık her yerden çağırabilirsin! ---"

# Kaldırma
uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)
	@echo "--- [!] ppd sistemden kaldırıldı. ---"
