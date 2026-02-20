# 📦 ppd (Padros Packet Downloader)

![License](https://img.shields.io/badge/license-MIT-blue.svg) 
![Language](https://img.shields.io/badge/language-C-orange.svg) 
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey.svg)

**ppd**, kişisel GitHub repolarımdaki araçları ve betikleri merkezi bir yerden yönetmek, kurmak ve güncellemek için geliştirdiğim minimalist bir paket yöneticisidir. 🚀

## 🌟 Neden ppd?

Kendi **mikro Linux dağıtımım** (BusyBox tabanlı, minimalist bir OS projesi) üzerinde çalışırken, sistem araçlarımı ve kendi yazdığım binary'leri hızlıca kuracak hafif bir çözüme ihtiyaç duydum. Mevcut paket yöneticileri (pacman, apt vb.) çok hantal kalıyordu. 

**ppd**, C dili ile doğrudan sistem çağrılarını kullanarak:
* 📥 GitHub üzerinden doğrudan binary çeker.
* 📂 Dosyaları `/usr/local/bin` altına taşır.
* 🔐 Gerekli çalıştırma izinlerini (`chmod +x`) otomatik verir.
* 🔍 Kendi JSON tabanlı repo listeniz içinde arama yapmanıza olanak tanır.

---

## ✨ Özellikler

- **Hafif ve Hızlı:** C dili ile yazıldı, minimal kaynak tüketir.
- **Merkezi Yönetim:** Uzaktaki bir `repos.json` dosyasını çekerek tüm araç listesini günceller (`ppd repos`).
- **Toplu Güncelleme:** Tek komutla tüm araçları force-update yapar (`ppd update`).
- **Gelişmiş Arama:** Paket ismi içinde hızlıca arama yapmanızı sağlar (`ppd search`).
- **Renkli Arayüz:** Terminalde okunabilir ve şık status mesajları sunar.

---

## 🛠️ Kurulum

Sisteminizde `gcc`, `make` ve `curl` yüklü olmalıdır.

```bash
# Repo'yu klonlayın
git clone https://github.com/Padrosum/ppd.git
cd ppd

# Derleyin
make

# Sisteme kurun
sudo make install
