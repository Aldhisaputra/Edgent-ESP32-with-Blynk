# 🚀 Edgent ESP32 + Sensor Gas MQ2 (Versi Disesuaikan)

Project ini adalah implementasi **Blynk Edgent** menggunakan **board ESP32 Dev Module** yang telah **disesuaikan** dari tutorial YouTube berikut:

📺 Tutorial referensi: [Blynk Edgent OTA & WiFi Setup ESP32](https://www.youtube.com/watch?v=AbiJ40biYfo)

Saya menggunakan **example dari Blynk** dan melakukan penyesuaian agar dapat berjalan pada **ESP32 Dev Module** dengan tambahan **sensor gas MQ2** dan **kabel jumper**. Proyek ini juga mendukung konfigurasi WiFi melalui captive portal dan pembaruan firmware secara OTA.

---

## 🧰 Komponen yang Digunakan

- ✅ ESP32 Dev Module
- ✅ Sensor gas MQ2
- ✅ Kabel jumper
- ✅ Aplikasi Blynk IoT (Android/iOS)
- ✅ Arduino IDE (dengan board ESP32 dan Blynk Library)

---

## 📁 Struktur File Proyek

| File             | Fungsi                                                                 |
|------------------|------------------------------------------------------------------------|
| `Edgent_ESP32.ino` | Sketch utama yang digunakan untuk ESP32                               |
| `BlynkEdgent.h`     | Menjalankan proses Edgent (WiFi, OTA, dll)                           |
| `BlynkState.h`      | Status sistem (config, connect, OTA, dsb)                            |
| `ConfigStore.h`     | Menyimpan konfigurasi WiFi dan token                                 |
| `ConfigMode.h`      | Menyediakan captive portal konfigurasi WiFi                          |
| `Console.h`         | Konsol interaktif via terminal Blynk                                 |
| `Indicator.h`       | Mengatur LED status (indikasi koneksi)                              |
| `OTA.h`             | Proses OTA firmware update melalui URL                               |
| `ResetButton.h`     | Mengatur tombol fisik untuk reset konfigurasi WiFi                   |

---

## ⚙️ Fitur

- 🔌 Setup WiFi lewat Captive Portal
- ☁️ Koneksi ke Blynk Cloud
- 🔁 OTA (Over-the-Air) Firmware Update
- 🟢 Indikator LED koneksi
- 🧪 Integrasi dengan sensor gas **MQ2**
- 📱 Kontrol & monitoring melalui aplikasi Blynk

---

## 🛠️ Langkah Penggunaan

1. Buka `Edgent_ESP32.ino` di Arduino IDE
2. Pastikan semua file `.h` ada di satu folder yang sama
3. Ubah `BLYNK_TEMPLATE_ID` dan `BLYNK_TEMPLATE_NAME` di sketch sesuai dengan milikmu dari Blynk Console
4. Hubungkan sensor MQ2 ke ESP32 sesuai diagram di bawah
5. Upload ke board **ESP32 Dev Module**
6. Sambungkan ke WiFi melalui hotspot yang muncul
7. Lanjutkan konfigurasi dan monitoring dari aplikasi Blynk

---

## 🔌 Diagram Koneksi ESP32 ke Sensor MQ2

+------------------+             +---------------+
|     ESP32 Dev    |             |   Sensor MQ2   |
|     Module       |             |               |
|                  |             |               |
|  GPIO 34 (A0)    +------------>+   AO           |
|  GND             +------------>+   GND          |
|  3V3             +------------>+   VCC          |
+------------------+             +---------------+


> ⚠️ MQ2 hanya kompatibel dengan **pin analog**, contohnya **GPIO34** atau **GPIO36** pada ESP32  
> Gunakan **tegangan 3.3V (3V3)** dari ESP32, bukan VIN

---

## 🧪 Contoh Kode Pembacaan Sensor MQ2

Tambahkan kode ini di bagian `loop()` atau fungsi `run()` untuk membaca nilai analog dari sensor MQ2:

```cpp
int mq2Value = analogRead(34); // Ganti dengan pin yang kamu pakai
Serial.print("Gas Value: ");
Serial.println(mq2Value);

// Jika ingin kirim ke Blynk
Blynk.virtualWrite(V0, mq2Value);


💬 Catatan
Meski mengikuti referensi dari YouTube, project ini menggunakan source code dari examples Blynk Edgent yang telah dimodifikasi agar sesuai dengan:

Board: ESP32 Dev Module

Sensor: Gas MQ2


👤 Author
Dikembangkan untuk pembelajaran dan eksperimen IoT menggunakan ESP32, Blynk, dan sensor MQ2.

Kebutuhan pemantauan gas secara real-time
