#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * LogNode Yapısı:
 * Bu yapı, her bir Syslog kaydını temsil eden bir düğüm (node) birimidir.
 * Çift bağlı liste (Doubly Linked List) prensibiyle tasarlanmıştır.
 */
typedef struct LogNode {
    char timestamp[32];   // Kaydın tam olarak ne zaman oluştuğunu tutan karakter dizisi.
    int priority;         // Mesajın önem derecesi (0: En yüksek/Acil, 7: En düşük/Hata Ayıklama).
    char message[256];    // Sistemin veya kullanıcının ürettiği log mesajı metni.
    struct LogNode* next; // Listedeki bir sonraki günlük kaydına işaret eden pointer.
    struct LogNode* prev; // Listedeki bir önceki günlük kaydına işaret eden pointer (Geriye dönük analiz için).
} LogNode;

/**
 * create_log_node Fonksiyonu:
 * Bellekten dinamik olarak yer ayırarak yeni bir günlük düğümü oluşturur.
 * Neden: Log sayısı önceden bilinmediği için heap bellek yönetimi (malloc) kullanılmıştır.
 */
LogNode* create_log_node(int priority, const char* msg) {
    // malloc ile düğüm büyüklüğünde bellek tahsis edilir.
    LogNode* newNode = (LogNode*)malloc(sizeof(LogNode));
    
    // Bellek yetersizliği durumunda programın çökmesini engellemek için kontrol yapılır.
    if (newNode == NULL) {
        printf("Hata: Dinamik bellek tahsisi basarisiz oldu!\n");
        return NULL;
    }

    // time.h kütüphanesi fonksiyonları ile o anki sistem saati saniye hassasiyetinde alınır.
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    // strftime: Zaman verisini okunabilir "YIL-AY-GUN SAAT:DAKIKA:SANIYE" formatına çevirir.
    strftime(newNode->timestamp, 32, "%Y-%m-%d %H:%M:%S", timeinfo);

    // Parametre olarak gelen öncelik ve mesaj bilgileri düğüme kopyalanır.
    newNode->priority = priority;
    strncpy(newNode->message, msg, 256); // strncpy: Buffer overflow (taşma) riskini önlemek için güvenli kopyalama yapar.
    
    // Yeni düğüm henüz bir listeye bağlanmadığı için uçları boş (NULL) bırakılır.
    newNode->next = NULL;
    newNode->prev = NULL;
    
    return newNode;
}

/**
 * add_log Fonksiyonu:
 * Yeni oluşturulan log düğümünü listenin en sonuna ekler.
 * Neden: Log kayıtları zaman sırasına göre (FIFO - First In First Out) tutulmalıdır.
 */
void add_log(LogNode** head, int priority, const char* msg) {
    // Önce eklenecek veri için bellek hazırlanır.
    LogNode* newNode = create_log_node(priority, msg);
    
    // Eğer liste henüz boşsa, yeni düğüm listenin ilk elemanı (Head) olur.
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    // Liste boş değilse, listenin son düğümünü bulmak için 'temp' ile tarama yapılır.
    LogNode* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    // Bağlantılar kurulur: Son düğümün 'sonrası' yeni düğüm, yeni düğümün 'öncesi' ise eski son düğüm olur.
    temp->next = newNode;
    newNode->prev = temp;
}

/**
 * display_logs Fonksiyonu:
 * Baştan başlayarak tüm listeyi ekrana yazdırır.
 * Bu fonksiyon, sistem günlüğünün okunabilir bir raporunu sunar.
 */
void display_logs(LogNode* head) {
    printf("\n--- LINUX SISTEM GUNLUKLERI (SYSLOG) ---\n");
    LogNode* temp = head;
    
    // temp pointer'ı NULL olana kadar (listenin sonuna kadar) ilerler.
    while (temp != NULL) {
        printf("[%s] [Seviye: %d] >> %s\n", 
               temp->timestamp, temp->priority, temp->message);
        temp = temp->next;
    }
    printf("----------------------------------------\n");
}

/**
 * free_logs Fonksiyonu:
 * Program sonlanırken malloc ile ayrılan tüm belleği işletim sistemine iade eder.
 * Neden: "Memory Leak" (Bellek Sızıntısı) oluşmasını engellemek için her düğüm tek tek free edilmelidir.
 */
void free_logs(LogNode* head) {
    LogNode* temp;
    while (head != NULL) {
        temp = head;       // Silinecek düğüm işaretlenir.
        head = head->next; // Bir sonraki düğüme geçilir.
        free(temp);        // İşaretlenen düğüm bellekten temizlenir.
    }
}

int main() {
    // Listenin başlangıç noktası (Kök pointer).
    LogNode* syslog_list = NULL;

    // Simülasyon: Örnek günlük kayıtlarının sisteme işlenmesi.
    add_log(&syslog_list, 1, "Sistem baslatildi. Kernel yukleniyor.");
    add_log(&syslog_list, 2, "Kullanici giris denemesi: admin");
    add_log(&syslog_list, 0, "UYARI: Islemci sicakligi kritik seviyeye ulasti!");
    add_log(&syslog_list, 4, "Ağ baglantisi kuruldu: eth0");

    // Mevcut logların kullanıcıya sunulması.
    display_logs(syslog_list);

    // Program biterken kaynakların temizlenmesi.
    free_logs(syslog_list);

    return 0;
}
