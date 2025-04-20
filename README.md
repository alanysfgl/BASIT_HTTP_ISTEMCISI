# BASIT_HTTP_ISTEMCISI


Bu proje, temel HTTP isteklerini yapmak için bir C++ istemcisi uygular. Kullanıcılar, URL girerek HTTP yanıtlarını alabilirler. Proje, HTTP 301 ve 302 yönlendirmelerini takip etme yeteneğine de sahiptir. Bu istemci, temel olarak TCP bağlantısı kurarak HTTP sunucularına GET istekleri gönderir ve yanıtları alır.

## Özellikler
- **GET İstekleri**: Kullanıcıların belirttiği URL'lere GET istekleri gönderir.
- **Yönlendirmeleri Takip Etme**: HTTP 301 ve 302 yönlendirmelerini otomatik olarak takip eder.
- **Bağlantı Yönetimi**: WinSock kütüphanesi kullanılarak TCP/IP bağlantıları yönetilir.

## Gereksinimler
- **C++ Derleyici** (Örneğin, `g++` veya Visual Studio)
- **WinSock Kütüphanesi** (Windows üzerinde çalışır)

## Kurulum ve Derleme
1. Projeyi bilgisayarınıza indirin.
2. C++ derleyicisini kullanarak projeyi derleyin.
   - Örnek: `g++ main.cpp -o http_client -lws2_32`
3. Programı çalıştırın.

## Kullanım
1. Programı çalıştırdığınızda, kullanıcıdan bir URL girilmesi istenir.
2. URL'yi girdikten sonra, HTTP yanıtı terminalde görüntülenir.
3. HTTP yanıtı:
   - Başlıklar (Headers) ve içerik (Body) şeklinde iki ana bölümde gösterilir.
   - Eğer URL yönlendirilmişse, 301 veya 302 HTTP durum koduyla birlikte yönlendirme adresi de gösterilir.

Örnek kullanım:
```bash
winsock baslatildi
lutfen URL giriniz: http://google.com
