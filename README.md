# Arduino Radar — LED ve Buzzer Uyarısı

Arduino Uno, HC-SR04 ve servo ile 15°–165° arasında mesafe taraması. Processing ekranı açı ve mesafeyi gösterir; 40 cm'den yakın nesneleri kırmızı çizgiyle işaretler.

## Dosyalar

- `arduino/Radar/Radar.ino`: Servo taraması, mesafe ölçümü, LED ve buzzer kontrolü.
- `processing/radar_tipi/radar_tipi.pde`: Radar görselleştirmesi.

## Bağlantılar

| Bileşen | Arduino Uno |
| --- | --- |
| HC-SR04 Trig | D13 |
| HC-SR04 Echo | D12 |
| HC-SR04 VCC / GND | 5V / GND |
| Servo sinyal | D9 |
| Servo besleme / GND | Uygun 5V kaynak / ortak GND |
| Aktif buzzer + / − | D4 / GND |
| Kırmızı LED | D5 |
| Sarı LED | D6 |
| Yeşil LED | D7 |

Her LED'in uzun bacağını ilgili pine 220–330 Ω direnç üzerinden, kısa bacağını GND'ye bağla. HC-SR04 sensörünü servonun üzerine sabitle; servo sensörü döndürmelidir. Harici servo beslemesi kullanırsan Arduino ile GND'lerini birleştir.

## Uyarılar

| Mesafe | LED | Buzzer |
| --- | --- | --- |
| 0 < mesafe ≤ 12 cm | Kırmızı | Her ölçümde kısa bip |
| 12 < mesafe ≤ 28 cm | Sarı | Bu aralıktaki her dördüncü ölçümde kısa bip |
| Mesafe > 28 cm veya geçersiz ölçüm | Yeşil | Kapalı |

Geçersiz ölçümde yeşil yanması cismin bulunmadığını garanti etmez. Bu proje eğitim amaçlı bir göstergedir.

Kod aktif buzzerı `digitalWrite()` ile sürer. Pasif buzzer için `tone()` / `noTone()` kullanılmalıdır.

## Çalıştırma

1. Arduino IDE Kütüphane Yöneticisi'nden **HCSR04 — Martin Sosic** ve **Servo — Arduino** kütüphanelerini kur. Derleme HCSR04 2.0.0, Servo 1.3.0 ve Arduino AVR Boards 1.8.8 ile doğrulandı.
2. `arduino/Radar/Radar.ino` dosyasını aç, kartı **Arduino Uno** seç ve kartın seri portunu seçerek yükle.
3. Arduino IDE'nin Seri Monitörünü kapat. Aynı portu aynı anda tek uygulama kullanmalıdır.
4. Processing'i **Java** modunda aç ve `processing/radar_tipi/radar_tipi.pde` dosyasını aç.
5. `new Serial(this, "/dev/ttyUSB0", 9600)` satırındaki portu bilgisayarına göre değiştir. Fedora/Linux için mevcut ayar `/dev/ttyUSB0`; Windows için örneğin `COM5`.
6. Processing'de **Run (▶)** düğmesine bas. Sensörün önüne 5–30 cm mesafede bir cisim koy.

Arduino 9600 baud hızında `açı,mesafe.` biçiminde veri gönderir; örnek: `90,19.`. İki dosyanın birlikte kullanılması gerekir; bariyer kodunun `Mesafe: ... cm` çıktısı bu arayüzle uyumlu değildir.

## Derleme

```bash
arduino-cli compile --fqbn arduino:avr:uno arduino/Radar
```
