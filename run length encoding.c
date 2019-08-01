#include <stdio.h>
#include <stdlib.h>

int* satir_satir(int mtr[][4], int *array, int row, int col) { //matrisi satir satir diziye aktarma fonksiyonu
    int i=0, j, k;
    for(j=0; j<row; j++){ 
            if (j %2 == 0){ 
                for(k=0; k<col; k++){                   //satir sayisinin cift oldugu durumlarda sutunu 0'dan baslayarak gezer
                    array[i] = mtr[j][k];
                    i++;
                }
            } else
                for(k=col-1; k>-1; k--){                //satir sayisinin tek oldugu durumda sutunu tersten gezer
                    array[i] = mtr[j][k];
                    i++;
                }
            }
    return array;
}

int *sutun_sutun(int mtr[][4], int *array, int row, int col) { //matrisi sutun sutun diziye aktarma fonksiyonu
    int i=0, j, k;
    for(j=0; j<col; j++){ 
            if (j %2 == 0){
                for(k=0; k<row; k++){                   //sutun sayisinin cift oldugu durumlarda satiri 0'dan baslayarak gezer
                    array[i] = mtr[k][j];
                    i++;
                }
            } else
                for(k=row-1; k>-1; k--){                //sutun sayisinin tek oldugu durumlarda satiri tersten gezer
                    array[i] = mtr[k][j];
                    i++;
                }
            }
    return array;
}

void run_lenght_encoding(int (*fun1)(), int (*fun2)(), int tercih, int mtr[][4], int row, int col){ //sikistirma yapacak fonksiyon
    int *array, i, j, k, *encoded, count;
    float oran;
    
    array = (int*) calloc(row*col, sizeof(int));        //matris taraninca tutacak olan array
    
    if (tercih==0)
        array = fun1(mtr, array, row, col);             //tercihe gore satir satir ya da sutun sutun matri taramasi
    else
        array = fun2(mtr, array, row, col);
    
    printf("Taranmis dizi: \n");
    for(i=0; i<row*col; i++){                           //tarama islemi sonucu olmusmus arrayin yazdirilmasi
        printf("%d ", array[i]);
     }
    printf("\n");
    
    k = 2;
    encoded = (int*) calloc(k, sizeof(int));            //sikistirilmis dizi icin yer acilmasi
    i =0; j=0;
    
    while(i<row*col) {                                  //taranmis dizinin tamami gezilene kadar devam eden dongu
        count = 1;
        
        while(array[i]==array[i+1]) {                   //arka arkaya ayni elemanlarin gelmesi durumunda donguye girer
            i++;
            count++;                                    //elemanlari sayar
        }
        encoded[j] = count;                             //sikistirilmis diziye once sayac atanir
        encoded[j+1] = array[i];                        //sikistirilan eleman atanir
        i++;
        j+=2;
        encoded = realloc(encoded, (k+2)*sizeof(int));  //realloc ile dizide yeni yer acilir
        k +=2; //
    }
    
    printf("Sikistirilmis dizi: \n");
    for(i=0; i<j; i++){                                 //sikistirilmis dizi yazdirilir
        printf("%d ", encoded[i]);
    }
    printf("\n");
    oran = (float)(row*col-j)/(row*col);
    printf("Sikistirma orani: %.2f \n", oran);
}

int main(int argc, char **argv)
{
    int row=5, col=4, i, j, tercih, *encoded, *eleman;
    int mtr[5][4] = {{ 3,3,3,3},
                    { 8,8,3,3},
                    { 8,5,6,7},
                    { 1,4,2,2},
                    { 1,9,9,9}};
    printf("MATRIS: \n");
    
    for(i=0; i<row; i++){
        for(j=0; j<col; j++){
            printf("%d ", mtr[i][j]);
        }
        printf("\n");
    }
    printf("Matrisi tarama sekli nasil olsun? Giriniz: \n");
    printf("(Satir satir tarama icin: 0, Sutun sutun tarama icin: 1) \n");
    scanf("%d", &tercih);
    run_lenght_encoding(satir_satir, sutun_sutun, tercih, mtr, row, col);
    
   
	return 0;
}
