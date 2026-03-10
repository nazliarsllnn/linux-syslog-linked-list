# Linux Syslog Yönetimi - Bağlı Liste Uygulaması

Bu proje, Linux işletim sistemindeki **Syslog** (Sistem Günlükleri) mekanizmasını modellemek ve bu verileri **Çift Bağlı Liste (Doubly Linked List)** veri yapısı kullanarak verimli bir şekilde yönetmek amacıyla geliştirilmiştir.

## Proje Hakkında
Bu uygulama, sistemde oluşan olay kayıtlarını dinamik olarak bellekte tutar, kronolojik olarak sıralar ve çift yönlü erişim imkanı sunar. Yazılım, bellek yönetimini (Dynamic Memory Management) esas alarak geliştirilmiştir.

### Kullanılan Teknolojiler ve Yapılar
* **Dil:** C
* **Veri Yapısı:** Çift Bağlı Liste (Doubly Linked List)
* **Kütüphaneler:** `stdio.h`, `stdlib.h`, `string.h`, `time.h`

## Teknik Detaylar

### 1. Syslog Mekanizması
Syslog, sistem çekirdeği ve uygulamalar tarafından üretilen log mesajlarını standartlaştıran bir protokoldür. Bu projede her log kaydı; **Zaman Damgası (Timestamp)**, **Öncelik Seviyesi (Priority)** ve **Mesaj (Message)** bileşenlerinden oluşmaktadır.

### 2. Neden Çift Bağlı Liste?
Projede Çift Bağlı Liste tercih edilmesinin temel nedenleri şunlardır:
- **Dinamik Boyutlandırma:** Log sayısının belirsiz olduğu durumlarda, dizilerin aksine bellekten sadece ihtiyaç duyulan miktar kadar alan ayrılır ($O(1)$ insertion).
- **Çift Yönlü Gezinme:** `prev` ve `next` işaretçileri sayesinde loglar arasında hem geçmişe hem de güncele doğru analiz yapılabilir.
- **Verimli Silme:** Belirli bir log kaydının silinmesi gerektiğinde, komşu düğümlere doğrudan erişim sağlandığı için tek yönlü listeye göre daha hızlıdır.

## Kurulum ve Çalıştırma

Kodun derlenmesi için bir C derleyicisine (GCC önerilir) ihtiyacınız vardır.
