#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <windows.h>

using json = nlohmann::json;

// YENI: Sadece API ile iletisim kurmaktan sorumlu ozel fonksiyonumuz
std::string geminiyeSor(const json& konusmaGecmisi, const std::string& apiKey) {
    std::string url = "https://generativelanguage.googleapis.com/v1beta/models/gemini-3.5-flash:generateContent?key=" + apiKey;

    json istekGovdesi;
    istekGovdesi["contents"] = konusmaGecmisi;

    cpr::Response r = cpr::Post(cpr::Url{ url },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ istekGovdesi.dump() });

    if (r.status_code == 200) {
        try {
            json cevapJson = json::parse(r.text);
            return cevapJson["candidates"][0]["content"]["parts"][0]["text"];
        }
        catch (const std::exception& e) {
            return "[Hata: Cevap okunamadi - " + std::string(e.what()) + "]";
        }
    }
    else {
        return "[Sunucu Hatasi: " + std::to_string(r.status_code) + " - " + r.text + "]";
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    
    const char* env_p = std::getenv("GEMINI_API_KEY");
    if (env_p == nullptr) {
        std::cout << "[Kritik Hata]: GEMINI_API_KEY ortam degiskeni bulunamadi!\n";
        std::cout << "Lutfen Windows Ortam Degiskenlerini kontrol edin.\n";
        return 1; // Programı güvenli bir şekilde kapat
    }
    std::string apiKey = env_p;

    std::cout << "--- Ziraat AI Asistan (Kurumsal Surum v3) Baslatildi ---\n";
    std::cout << "(Komutlar: 'cikis', '/temizle', '/ozetle')\n\n";

    json konusmaGecmisi = json::array();

    while (true) {
        std::string kullaniciSorusu;
        std::cout << "Sen: ";
        std::getline(std::cin, kullaniciSorusu);

        if (kullaniciSorusu == "cikis" || kullaniciSorusu == "çıkış") {
            std::cout << "Gorusmek uzere!\n";
            break;
        }

        if (kullaniciSorusu == "/temizle") {
            konusmaGecmisi.clear();
            std::cout << "[Sistem: Hafiza basariyla temizlendi.]\n\n";
            continue;
        }

        if (kullaniciSorusu == "/ozetle") {
            std::cout << "[Sistem: Lutfen ozetlenecek .txt dosyasinin tam yolunu girin]\n";
            std::cout << "Dosya Yolu: ";

            std::string dosyaYolu;
            std::getline(std::cin, dosyaYolu);

            std::ifstream dosya(dosyaYolu);

            if (dosya.is_open()) {
                std::stringstream buffer;
                buffer << dosya.rdbuf();
                std::string dosyaIcerigi = buffer.str();
                dosya.close();

                std::cout << "[Sistem: Dosya basariyla okundu. Ozet hazirlaniyor...]\n";
                kullaniciSorusu = "Lutfen asagidaki metni dikkatlice oku ve en onemli noktalari cikararak bana anlasilir bir ozet hazirla:\n\n" + dosyaIcerigi;
            }
            else {
                std::cout << "[Hata: Dosya bulunamadi veya acilamadi! Lutfen yolu kontrol edin.]\n\n";
                continue;
            }
        }

        if (kullaniciSorusu.empty()) {
            continue;
        }

        // 1. Kullanıcı sorusunu hafızaya ekle
        konusmaGecmisi.push_back({
            {"role", "user"},
            {"parts", json::array({{{"text", kullaniciSorusu}}})}
            });

        std::cout << "Asistan dusunuyor...\n";

        // 2. Karmaşık kodlar yerine sadece fonksiyonumuzu çağırıyoruz
        std::string asistanCevabi = geminiyeSor(konusmaGecmisi, apiKey);

        std::cout << "Asistan: \n" << asistanCevabi << "\n\n";

        // 3. Hata dönmediyse cevabı hafızaya ekle, döndüyse hatalı soruyu sil
        if (asistanCevabi.find("[Hata:") == std::string::npos && asistanCevabi.find("[Sunucu Hatasi:") == std::string::npos) {
            konusmaGecmisi.push_back({
                {"role", "model"},
                {"parts", json::array({{{"text", asistanCevabi}}})}
                });
        }
        else {
            konusmaGecmisi.erase(konusmaGecmisi.end() - 1);
        }
    }

    return 0;
}