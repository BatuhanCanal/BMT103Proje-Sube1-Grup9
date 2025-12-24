#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Dosya isimlerini ve dosya işaretçilerini tutmak için yapı tanımı
typedef struct {
    char input_filename[100];
    char output_filename[100];
    FILE *input_file;
    FILE *output_file;
} DosyaIslemleri;

// Sesli harf kontrolü yapacak fonksiyonun prototipi
int is_vowel(char ch);

int main() {
    DosyaIslemleri islem;
    int ch; // Okunan karakteri tutmak için
    int i;
    int nokta_index = -1;

    // --- DEĞİŞİKLİK BURADA ---
    // Kullanıcı geçerli bir dosya adı girene kadar programı kilitleyen döngü
    while (1) {
        printf("Dosya adini giriniz: ");
        scanf("%s", islem.input_filename);

        // Dosyayı okuma modunda ('r') açmayı dene
        islem.input_file = fopen(islem.input_filename, "r");

        if (islem.input_file != NULL) {
            break; // Dosya başarıyla açıldıysa döngüden çık
        } else {
            // Dosya yoksa hata ver ve tekrar sor
            printf("Hata: Dosya bulunamadi, lutfen gecerli bir isim giriniz.\n");
            printf("---\n");
        }
    }
    // -------------------------

    // Giriş dosyasının adını çıkış değişkenine kopyala
    strcpy(islem.output_filename, islem.input_filename);

    // Dosya uzantısını (örn: .txt) bulup silmek için sondan başa tarama
    int uzunluk = strlen(islem.output_filename);
    for (i = uzunluk - 1; i >= 0; i--) {
        if (islem.output_filename[i] == '.') {
            nokta_index = i;
            break;
        }
    }

    // Eğer nokta bulunduysa, oraya string sonlandırma karakteri koy (uzantıyı kes)
    if (nokta_index != -1) {
        islem.output_filename[nokta_index] = '\0';
    }

    // Kesilen ismin sonuna yeni uzantıyı ekle
    strcat(islem.output_filename, ".ssz");

    // Yeni dosyayı yazma modunda ('w') oluştur
    islem.output_file = fopen(islem.output_filename, "w");
    if (islem.output_file == NULL) {
        printf("Dosya olusturulamadi.\n");
        fclose(islem.input_file);
        return 1;
    }

    // Dosya sonuna (EOF) gelene kadar karakter karakter oku
    while ((ch = fgetc(islem.input_file)) != EOF) {
        // Eğer karakter sesli harf DEĞİLSE, çıkış dosyasına yaz
        if (is_vowel(ch) == 0) {
            fputc(ch, islem.output_file);
        }
    }

    // Açılan dosyaları kapat (hafıza yönetimi için önemli)
    fclose(islem.input_file);
    fclose(islem.output_file);

    printf("---------------------------------------------\n");
    printf("%s nin sessiz harfleri %s ye kopyalandi\n", islem.input_filename, islem.output_filename);

    return 0;
}

// Karakterin sesli olup olmadığını kontrol eden fonksiyon
int is_vowel(char ch) {
    // Büyük-küçük harf duyarlılığını kaldırmak için karakteri küçült
    char kucuk = tolower(ch);

    // Sesli harflerden biriyse 1 (true) döndür
    if (kucuk == 'a' || kucuk == 'e' || kucuk == 'i' || kucuk == 'o' || kucuk == 'u') {
        return 1;
    }
    // Değilse 0 (false) döndür
    return 0;
}