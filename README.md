# C++ Gemini AI Assistant (Kurumsal Sürüm v3)

Bu proje, **Ziraat Teknoloji** stajım sürecinde geliştirilmiş, C++ dili üzerinden **Google Gemini API** entegrasyonu sağlayan kurumsal düzeyde bir yapay zeka asistanıdır. 

Proje, HTTP istekleri ve JSON veri manipülasyonunu tamamen C++ backend'i üzerinden yöneterek kullanıcılara dinamik, hafızalı (context-aware) ve dosya analiz yeteneğine sahip bir konsol arayüzü sunar.

---

## 🚀 Öne Çıkan Özellikler

- **Hafızalı Sohbet (Context Management):** Asistan, kullanıcının önceki mesajlarını aklında tutarak akıllı diyaloglar sürdürebilir.
- **Güvenli API Anahtarı Yönetimi:** API anahtarınız (Gemini API Key) kodun içine gömülmez; Windows ortam değişkenleri (`Environment Variables`) üzerinden güvenli bir şekilde çekilir.
- **`/ozetle` (Dosya Okuma & Özetleme):** Yerel bilgisayardaki `.txt` dosyalarının yollarını alarak içeriği otomatik okur ve yapay zeka yardımıyla analiz edip özet çıkarır.
- **`/temizle` (Hafıza Yönetimi):** Sohbet geçmişini (context JSON yapısını) sıfırlayarak yeni bir konuya temiz bir şekilde başlamayı sağlar.
- **Gelişmiş Türkçe Desteği:** Konsol giriş ve çıkış kodlaması Windows API'leri (`SetConsoleOutputCP`) ile UTF-8 olarak konfigüre edilmiştir.

---

## 🛠️ Kullanılan Teknolojiler ve Kütüphaneler

- **Dil:** C++ (C++17 ve üzeri)
- **Kütüphaneler:**
  - **[CPR (C++ Requests)](https://github.com/libcpr/cpr):** HTTP POST istekleri ile API ile haberleşmek için kullanılan modern bir ağ kütüphanesi.
  - **[nlohmann/json](https://github.com/nlohmann/json):** C++ için endüstri standardı JSON serileştirme ve deserileştirme kütüphanesi.
  - **Windows API:** Konsolun Türkçe karakterleri desteklemesi için UTF-8 kodlama ayarları.

---

## 💻 Kurulum ve Çalıştırma

### 1. Gereksinimler
Projenin derlenebilmesi için `cpr` ve `nlohmann/json` kütüphanelerinin projenize (örneğin vcpkg veya NuGet paket yöneticisi ile Visual Studio'ya) dahil edilmesi gerekmektedir.

### 2. API Anahtarını Tanımlama (Önemli)
Programın çalışabilmesi için işletim sisteminize `GEMINI_API_KEY` ortam değişkenini tanımlamalısınız.

**Windows için:**
1. Başlat menüsüne "Ortam Değişkenleri" yazın ve açın.
2. "Yeni..." butonuna tıklayın.
3. Değişken Adı: `GEMINI_API_KEY`
4. Değişken Değeri: `[SİZİN_GEMINI_API_ANAHTARINIZ]`
5. Sistemi veya Visual Studio'yu yeniden başlatın.

### 3. Çalıştırma
Projeyi klonlayıp kendi derleyiciniz ile derleyebilirsiniz:
```bash
git clone https://github.com/iremidilkozan/Gemini-CPP-Assistant.git
