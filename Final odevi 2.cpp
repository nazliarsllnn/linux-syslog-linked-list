#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Syslog kayýtlarýný temsil eden yapý (Node)
typedef struct LogNode {
    char timestamp[32];   // Logun oluþtuðu zaman
    int priority;         // Öncelik seviyesi (0: Acil, 1: Hata, 2: Bilgi vb.)
    char message[256];    // Log mesajý
    struct LogNode* next; // Bir sonraki düðüm
    struct LogNode* prev; // Bir önceki düðüm (Çift baðlý liste özelliði)
} LogNode;

// Yeni bir log düðümü oluþturma fonksiyonu
LogNode* create_log_node(int priority, const char* msg) {
    LogNode* newNode = (LogNode*)malloc(sizeof(LogNode));
    if (newNode == NULL) {
        printf("Bellek hatasi!\n");
        return NULL;
    }

    // Sistem zamanýný al
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(newNode->timestamp, 32, "%Y-%m-%d %H:%M:%S", timeinfo);

    newNode->priority = priority;
    strncpy(newNode->message, msg, 256);
    newNode->next = NULL;
    newNode->prev = NULL;
    
    return newNode;
}

// Listeye yeni log ekleme (Sona ekleme - FIFO mantýðý)
void add_log(LogNode** head, int priority, const char* msg) {
    LogNode* newNode = create_log_node(priority, msg);
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    LogNode* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    temp->next = newNode;
    newNode->prev = temp;
}

// Loglarý baþtan sona listeleme
void display_logs(LogNode* head) {
    printf("\n--- SISTEM GUNLUKLERI (SYSLOG) ---\n");
    LogNode* temp = head;
    while (temp != NULL) {
        printf("[%s] Oncelik: %d | Mesaj: %s\n", 
               temp->timestamp, temp->priority, temp->message);
        temp = temp->next;
    }
}

// Belleði serbest býrakma (Memory management)
void free_logs(LogNode* head) {
    LogNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    LogNode* syslog_list = NULL;

    // Örnek log kayýtlarý ekleyelim
    add_log(&syslog_list, 1, "Sistem baslatildi.");
    add_log(&syslog_list, 2, "Kullanici giris yapti: admin");
    add_log(&syslog_list, 0, "KRITIK: Disk doluluk orani %95!");

    // Loglarý ekranda göster
    display_logs(syslog_list);

    // Program kapanmadan belleði temizle
    free_logs(syslog_list);

    return 0;
}
