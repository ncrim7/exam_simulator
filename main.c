#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void cevap_anahtari_uret(char cevap_anahtari[], int S);
void cevap_anahtari_yazdir(char cevap_anahtari[], int S);
void sinavi_uygula(char ogrenci_cevaplari[][100], char cevap_anahtari[], int N, int S, double B, double D);
void ogrenci_cevabini_yazdir(char ogrenci_cevaplari[][100], int ogrenci_ID, int S);
void ogrencileri_puanla(char ogrenci_cevaplari[][100], char cevap_anahtari[], double HBN[], int N, int S);
double sinif_ortalamasi_hesapla(double HBN[], int N);
double standart_sapma_hesapla(double ortalama, double HBN[], int N);
void T_skoru_hesapla(double ortalama, double HBN[], int N, double std, double T_skoru[]);
void harf_notu_olustur(double ortalama, double T_skoru[], int N, char harfnotu[][2]);

int main(){
    srand(time(NULL));
    int N, S;
    double B, D;
    do{
        printf("Ogrenci sayisini giriniz (max 100): ");
        scanf("%d", &N);
    }while(N > 100 || N < 0);

    do{
        printf("Soru sayisini giriniz (max 100):" );
        scanf("%d", &S);
    }while(S < 0 || S > 100);

    do{
        printf("Bos birakma ihtimalini giriniz (0.0 ~ 1.0): ");
        scanf("%lf", &B);
    }while(B < 0.0 || B > 1.0);

    do {
        printf("Dogru cevap verme ihtimalini giriniz (0.0 ~ 1.0): ");
        scanf("%lf", &D);
    }while(D < 0.0 || D > 1.0);

    char cevap_anahtari[S], ogrenci_cevaplari[N][100], ogrenci_harf_notlari[N][2];
    cevap_anahtari_uret(cevap_anahtari, S);
    cevap_anahtari_yazdir(cevap_anahtari, S);
    sinavi_uygula(ogrenci_cevaplari, cevap_anahtari, N, S, B, D);
    printf("\n");
    int i;
    for(i = 0; i < N; ++i){
        ogrenci_cevabini_yazdir(ogrenci_cevaplari, i, S);
    }
    double sinif_ortalama, std, HBN[N], T_skor[N];
    ogrencileri_puanla(ogrenci_cevaplari, cevap_anahtari, HBN, N, S);
    sinif_ortalama = sinif_ortalamasi_hesapla(HBN, N);
    std = standart_sapma_hesapla(sinif_ortalama, HBN, N);
    T_skoru_hesapla(sinif_ortalama, HBN, N, std, T_skor);
    harf_notu_olustur(sinif_ortalama, T_skor, N, ogrenci_harf_notlari);
    printf("Sinif ortalamasi : %.2lf, standart sapma: %.2lf\n\n\n", sinif_ortalama, std);
    printf("Ogrenci notlari:\n");
    for(i = 0; i < N; ++i){
        printf("%03d. ogrencinin HBN: %.2lf, T-skoru: %.2lf, harf notu: %c%c\n", i+1, HBN[i], T_skor[i], ogrenci_harf_notlari[i][0], ogrenci_harf_notlari[i][0]);
    }
    return 0;
}


void cevap_anahtari_uret(char cevap_anahtari[], int S){
    int i;
    for(i = 0; i < S; ++i)
        cevap_anahtari[i] =  'A' + (rand() % 5);
}

void cevap_anahtari_yazdir(char cevap_anahtari[], int S){
    int i;
    printf("Cevap Anahtari:\n");
    for(i = 0; i < S; ++i)
        printf("%03d:%c | ", i+1, cevap_anahtari[i]);
    printf("\n");
}

void sinavi_uygula(char ogrenci_cevaplari[][100], char cevap_anahtari[], int N, int S, double B, double D){
    srand(time(NULL));
    int i, j;
    double rastgeleSayi;
    double range = 1;
    double div = RAND_MAX / range;
    for(i = 0; i < N; ++i){
        for(j = 0; j < S; ++j){
            rastgeleSayi = (rand() / div);
             if(rastgeleSayi < B)
                 ogrenci_cevaplari[i][j] = 'X';
             else{
                 rastgeleSayi = (rand() / div);
                 if(rastgeleSayi >= 1.0 - D)
                     ogrenci_cevaplari[i][j] = cevap_anahtari[j];
                 else{
                     ogrenci_cevaplari[i][j] = 'A' + (rand() % 5);
                     while(ogrenci_cevaplari[i][j] == cevap_anahtari[j]){
                         ogrenci_cevaplari[i][j] = 'A' + (rand() % 5);
                     }
                 }
             }
        }
    }
}

void ogrenci_cevabini_yazdir(char ogrenci_cevaplari[][100], int ogrenci_ID, int S){
    int i;
    printf("%03d. ogrencinin cevaplari:\n", ogrenci_ID+1);
    for(i = 0; i < S; ++i){
        printf("%03d:%c | ", i+1, ogrenci_cevaplari[ogrenci_ID][i]);
    }
    printf("\n");
}

void ogrencileri_puanla(char ogrenci_cevaplari[][100], char cevap_anahtari[], double HBN[], int N, int S){
    int i, j, yanlisSoruSayisi, bosSoru;
    double soruPuani = 100/S;
    for(i = 0; i < N; ++i){
        bosSoru = 0;
        yanlisSoruSayisi = 0;
        for(j = 0; j < S; ++j){
            if(ogrenci_cevaplari[i][j] == 'X')
                bosSoru++;
            else if(ogrenci_cevaplari[i][j] != cevap_anahtari[j])
                yanlisSoruSayisi++;
        }
        HBN[i] = ( soruPuani * (S - (yanlisSoruSayisi + bosSoru)) ) - ( soruPuani * (yanlisSoruSayisi / 4.0) );
        if(HBN[i] < 0)
            HBN[i] = 0;
        //printf("%lf ", HBN[i]);
    }
}

double sinif_ortalamasi_hesapla(double HBN[], int N){
    double sinif_ortalamasi = 0;
    int i;
    for(i = 0; i < N; ++i){
        sinif_ortalamasi += HBN[i];
    }
    return (sinif_ortalamasi / N);
}

double standart_sapma_hesapla(double ortalama, double HBN[], int N){
    double std, toplam = 0;
    double sayi;
    int i;
    for(i = 0; i < N; ++i){
        sayi = HBN[i] - ortalama;
        toplam = toplam + (pow(sayi, 2));
    }
    toplam = toplam / N;
    double sonuc = sqrt(toplam);
    return sonuc;
}
void T_skoru_hesapla(double ortalama, double HBN[], int N, double std, double T_skoru[]){
    int i;
    for(i = 0; i < N; ++i){
        T_skoru[i] = 60 + (10 * ( (HBN[i] - ortalama) / std) );
    }
}

void harf_notu_olustur(double ortalama, double T_skoru[], int N, char harfnotu[][2]){
    int FF, FD1, FD2, DD1, DD2, DC1, DC2, CC1, CC2, CB1, CB2, BB1, BB2, BA1, BA2, AA, i;
    if( ortalama <=100 ){
        FF = 32;
        FD1 = 32;
        FD2 = 36.99;
        DD1 = 37;
        DD2 = 41.99;
        DC1 = 42;
        DC2 = 46.99;
        CC1 = 47;
        CC2 = 51.99;
        CB1 = 52;
        CB2 = 56.99;
        BB1 = 57;
        BB2 = 61.99;
        BA1 = 62;
        BA2 = 66.99;
        AA = 67;
    }
     if( ortalama <=80 ){
        FF += 2;
        FD1 += 2;
        FD2 += 2;
        DD1 += 2;
        DD2 += 2;
        DC1 += 2;
        DC2 += 2;
        CC1 += 2;
        CC2 += 2;
        CB1 += 2;
        CB2 += 2;
        BB1 += 2;
        BB2 += 2;
        BA1 += 2;
        BA2 += 2;
        AA += 2;
    }

     if( ortalama <=70 ){
        FF += 2;
        FD1 += 2;
        FD2 += 2;
        DD1 += 2;
        DD2 += 2;
        DC1 += 2;
        DC2 += 2;
        CC1 += 2;
        CC2 += 2;
        CB1 += 2;
        CB2 += 2;
        BB1 += 2;
        BB2 += 2;
        BA1 += 2;
        BA2 += 2;
        AA += 2;
    }

     if( ortalama <=62.5 ){
        FF += 2;
        FD1 += 2;
        FD2 += 2;
        DD1 += 2;
        DD2 += 2;
        DC1 += 2;
        DC2 += 2;
        CC1 += 2;
        CC2 += 2;
        CB1 += 2;
        CB2 += 2;
        BB1 += 2;
        BB2 += 2;
        BA1 += 2;
        BA2 += 2;
        AA += 2;
    }

    if( ortalama <=57.5 ){
        FF += 2;
        FD1 += 2;
        FD2 += 2;
        DD1 += 2;
        DD2 += 2;
        DC1 += 2;
        DC2 += 2;
        CC1 += 2;
        CC2 += 2;
        CB1 += 2;
        CB2 += 2;
        BB1 += 2;
        BB2 += 2;
        BA1 += 2;
        BA2 += 2;
        AA += 2;
    }

    if( ortalama <=52.5 ){
        FF += 2;
        FD1 += 2;
        FD2 += 2;
        DD1 += 2;
        DD2 += 2;
        DC1 += 2;
        DC2 += 2;
        CC1 += 2;
        CC2 += 2;
        CB1 += 2;
        CB2 += 2;
        BB1 += 2;
        BB2 += 2;
        BA1 += 2;
        BA2 += 2;
        AA += 2;
    }

    if( ortalama <=47.5 ){
        FF += 2;
        FD1 += 2;
        FD2 += 2;
        DD1 += 2;
        DD2 += 2;
        DC1 += 2;
        DC2 += 2;
        CC1 += 2;
        CC2 += 2;
        CB1 += 2;
        CB2 += 2;
        BB1 += 2;
        BB2 += 2;
        BA1 += 2;
        BA2 += 2;
        AA += 2;
    }
    if( ortalama <=42.5 ){
        FF += 2;
        FD1 += 2;
        FD2 += 2;
        DD1 += 2;
        DD2 += 2;
        DC1 += 2;
        DC2 += 2;
        CC1 += 2;
        CC2 += 2;
        CB1 += 2;
        CB2 += 2;
        BB1 += 2;
        BB2 += 2;
        BA1 += 2;
        BA2 += 2;
        AA += 2;
    }
    for(i = 0; i < N; ++i){
        if(T_skoru[i] < FF){
            harfnotu[i][0] = 'F';
            harfnotu[i][1] = 'F';
        }
        else if(FD1 <= T_skoru[i] && T_skoru[i] <= FD2){
            harfnotu[i][0] = 'F';
            harfnotu[i][1] = 'D';
        }
        else if(DD1 <= T_skoru[i] && T_skoru[i] <= DD2){
            harfnotu[i][0] = 'D';
            harfnotu[i][1] = 'D';
        }
        else if(DC1 <= T_skoru[i] && T_skoru[i] <= DC2){
            harfnotu[i][0] = 'D';
            harfnotu[i][1] = 'C';
        }
        else if(CC1 <= T_skoru[i] && T_skoru[i] <= CC2){
            harfnotu[i][0] = 'C';
            harfnotu[i][1] = 'C';
        }
        else if(CB1 <= T_skoru[i] && T_skoru[i] <= CB2){
            harfnotu[i][0] = 'C';
            harfnotu[i][1] = 'B';
        }
        else if(BB1 <= T_skoru[i] && T_skoru[i] <= BB2){
            harfnotu[i][0] = 'B';
            harfnotu[i][1] = 'B';
        }
        else if(BA1 <= T_skoru[i] && T_skoru[i] <= BA2){
            harfnotu[i][0] = 'B';
            harfnotu[i][1] = 'A';
        }
        else if(AA <= T_skoru[i] ){
            harfnotu[i][0] = 'A';
            harfnotu[i][1] = 'A';
        }
    }
}












