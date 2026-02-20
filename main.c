#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "cJSON.h"

#define COLOR_RESET  "\x1b[0m"
#define COLOR_CYAN   "\x1b[36m"
#define COLOR_GREEN  "\x1b[32m"
#define COLOR_RED    "\x1b[31m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BOLD   "\x1b[1m"

const char* CONFIG_FILE = "repos.json";
// BURAYI KENDİ REPO LİNKİNLE DEĞİŞTİR:
const char* REMOTE_REPO_URL = "https://raw.githubusercontent.com/padrosum/ppd-repos/main/repos.json";

void print_banner() {
    printf(COLOR_CYAN COLOR_BOLD "\n--- Padros Packet Downloader (ppd) ---\n" COLOR_RESET);
}

char* read_config() {
    FILE *f = fopen(CONFIG_FILE, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *data = malloc(len + 1);
    fread(data, 1, len, f);
    fclose(f);
    data[len] = '\0';
    return data;
}

// Tek bir paketi kuran temel fonksiyon
int perform_install(const char *name, const char *url) {
    char target[256], source[256], cmd[1024], mv_cmd[1024];
    sprintf(target, "/usr/local/bin/%s", name);
    sprintf(source, "/tmp/%s", name);

    printf(COLOR_YELLOW "[*] İşlem yapılıyor: %s...\n" COLOR_RESET, name);
    
    sprintf(cmd, "curl -sL %s -o %s", url, source);
    if (system(cmd) != 0) return -1;

    sprintf(mv_cmd, "sudo mv %s %s", source, target);
    if (system(mv_cmd) == 0) {
        chmod(target, 0755);
        return 0;
    }
    return -1;
}

// ppd repos: Uzaktaki JSON dosyasını indirir
void update_repos_list() {
    printf(COLOR_CYAN "[*] Uzak repo listesi güncelleniyor...\n" COLOR_RESET);
    char cmd[512];
    sprintf(cmd, "curl -sL %s -o %s", REMOTE_REPO_URL, CONFIG_FILE);
    if (system(cmd) == 0) {
        printf(COLOR_GREEN "[✔] Repo listesi başarıyla güncellendi!\n" COLOR_RESET);
    } else {
        printf(COLOR_RED "[!] Repo listesi indirilemedi.\n" COLOR_RESET);
    }
}

// ppd update: JSON içindeki tüm paketleri force update yapar
void update_all_packages() {
    char *raw = read_config();
    if (!raw) {
        printf(COLOR_RED "[!] repos.json bulunamadı. Önce 'ppd repos' yapın.\n" COLOR_RESET);
        return;
    }
    cJSON *root = cJSON_Parse(raw);
    cJSON *packages = cJSON_GetObjectItem(root, "packages");
    cJSON *pkg = NULL;

    printf(COLOR_CYAN "[*] Tüm paketler güncelleniyor (Force Update)...\n" COLOR_RESET);
    cJSON_ArrayForEach(pkg, packages) {
        const char *name = cJSON_GetObjectItem(pkg, "name")->valuestring;
        const char *url = cJSON_GetObjectItem(pkg, "url")->valuestring;
        
        if (perform_install(name, url) == 0) {
            printf(COLOR_GREEN "[✔] %s güncellendi.\n" COLOR_RESET, name);
        } else {
            printf(COLOR_RED "[!] %s güncellenemedi!\n" COLOR_RESET, name);
        }
    }
    cJSON_Delete(root);
    free(raw);
}

// ppd install <name> için arama motoru
void install_package(const char *name) {
    char *raw = read_config();
    if (!raw) return;
    cJSON *root = cJSON_Parse(raw);
    cJSON *packages = cJSON_GetObjectItem(root, "packages");
    cJSON *pkg = NULL;
    int found = 0;

    cJSON_ArrayForEach(pkg, packages) {
        if (strcmp(cJSON_GetObjectItem(pkg, "name")->valuestring, name) == 0) {
            perform_install(name, cJSON_GetObjectItem(pkg, "url")->valuestring);
            printf(COLOR_GREEN "[+] %s kuruldu.\n" COLOR_RESET, name);
            found = 1;
            break;
        }
    }
    if (!found) printf(COLOR_RED "[!] Paket bulunamadı.\n" COLOR_RESET);
    cJSON_Delete(root);
    free(raw);
}

int main(int argc, char *argv[]) {
    print_banner();
    if (argc < 2) {
        printf("Komutlar:\n  ppd repos          - Uzak listeyi güncelle\n  ppd update         - Tüm paketleri güncelle\n  ppd install <isim> - Paketi kur\n");
        return 1;
    }

    if (strcmp(argv[1], "repos") == 0) {
        update_repos_list();
    } else if (strcmp(argv[1], "update") == 0) {
        update_all_packages();
    } else if (strcmp(argv[1], "install") == 0 && argc == 3) {
        install_package(argv[2]);
    } else {
        printf(COLOR_RED "[!] Geçersiz komut.\n" COLOR_RESET);
    }
    return 0;
}
