#include <stdio.h>
#include <stdlib.h>


int max(int x, int y)
{
    return (x > y) ? x : y;
}


void knapSack(int W,int wt[],int val[],int n)
{

	int i, w;
	/* Sonucları yazdıracağımız txt dosyasını oluşturur */
	FILE *dosya = fopen("DinamiKnapsack.txt", "w");
	/*c de aþýrý büyük diziler bellek alanýnda deðerleri tutacak yeterli uzunkukta yer bulamayacaðý için pointer kullandým */
    int (*arr)[W+1] = calloc(n+1, sizeof*arr);
    int dizi[n];

    /*knapsack algoritmasýnda sonucu yani ulaþýlan en büyük deðeri burda buluruz
      knapsak tablosundaki son deðer*/
	for (i = 0; i <= n; i++)
    {
		for (w = 0; w <= W; w++)
        {
			if (i == 0 || w == 0)
			{
				arr[i][w] = 0;
			}
			else if (wt[i - 1] <= w)
			{
				arr[i][w] = max(val[i - 1] + arr[i - 1][w - wt[i - 1]], arr[i - 1][w]);
			}
			else
			{
				arr[i][w] = arr[i - 1][w];
			}
		}
	}

	int sonuc = arr[n][W];
    fprintf(dosya,"%d \n",sonuc);

    /*item sayýsý kadar dönerek dizinin tüm elemanlarýna 0 atandý*/
    for(int a=0;a<n;a++)
     {
        dizi[a]=0;
     }

	/*Hangi aðýrlýklardan alýyor*/
	w = W;
	fprintf(dosya,"Kullanilan itemler:");
	for (i = n; i > 0 && sonuc > 0; i--)
    {
		if (sonuc == arr[i - 1][w])
        {
			continue;
		}
		else
        {
            /* agýrlýgýn bulundugu indise 1 atar*/
            dizi[i-1]=1;
            /*Cantaya alýnan agýrlýklarý bulur*/
			fprintf(dosya," %d ", wt[i - 1]);
			sonuc = sonuc - val[i - 1];
			w = w - wt[i - 1];
		}
	}
    fprintf(dosya,"\n");
    printf("islem Basari ile tamamlandi ve DinamiKnapsack..txt dosyasina yazdirildi \n");

    /*item sayýsý kadar dönerek else(63.satýr) kýsmýnda eklemeler yapýlan diziyi yazdýrýr*/
	for(int b = 0; b < n; b++)
    {
      fprintf(dosya,"%d",dizi[b]);
    }

    /*tahsis edilen alaný boþaltýr*/
	free(arr);
    /*dosyaya yazma işlemini bitirir*/
    fclose(dosya);
}


/*10000 lik txt için max değeri bulan bir fonksiyon*/
void knapSack2(int W,int wt[],int val[],int n)
{
    int i ,w;
    FILE *dosya = fopen("DinamiKnapsack.txt", "w");
    int (*arr)= malloc(sizeof(int)*W+1);
    memset(arr, 0, sizeof(arr));

   // printf("a");
    for (int i = 1; i < n + 1; i++)
    {
        for (int w = W; w >= 0; w--)
        {

            if (wt[i - 1] <= w)
            {
                arr[w] = max(arr[w],arr[w - wt[i - 1]] + val[i - 1]);
            }
        }
    }

    printf("Sonuc DinamiKnapsack.txt dosyasina yazdirildi");
    fprintf(dosya,"Cantanin Max agirligi:%d",arr[W]);

}

void GreegyKnapsack(int W,int wt[],int val[],int n)
{
    int dizi[n];
    int item;
    int sonuc=0;

    FILE *dosya = fopen("GreedyCikti.txt", "w");
    printf("item sayisi(n):%d\n", n);
    printf("kapasite(W):%d\n\n", W);
    fprintf(dosya,"item sayisi(n):%d\n", n);
    fprintf(dosya,"kapasite(W):%d\n\n", W);

    for (int i = 0; i < n; ++i)
        dizi[i] = 0;


    while (W > 0)
    {
        item = -1;
        for (int i = 0; i < n; ++i)
            if ((dizi[i] == 0) &&
                ((item == -1) || ((float) val[i] / wt[i] > (float) val[item] / wt[item])))
                item = i;

        dizi[item] = 1;
        W -= wt[item];
        sonuc += val[item];
        if (W >= 0){
            printf("[%d val , %d wt] ", val[item], wt[item]);
            fprintf(dosya,"[%d val, %d wt] ", val[item], wt[item]);
            printf("-kalan W:[%d]\n",W);
            fprintf(dosya,"-kalan W:[%d]\n",W);
        }
        else
        {
            printf("[%d val , %d wt]", val[item], wt[item]);
            fprintf(dosya,"[%d val , %d wt] ", val[item], wt[item]);
            sonuc -= val[item];
            printf("-kalan W:[%d] negatif oldugu icin yer kalmadi!! \n\n",W);
            fprintf(dosya,"-kalan W:[%d] negatif oldugu icin yer kalmadi!! \n\n",W);
        }
    }

    printf("Cantanin Max agirligi:%d\n\n", sonuc);
    fprintf(dosya,"Cantanin Max agirligi:%d\n", sonuc);
    printf("Sonuc GreedyCikti.txt dosyasina yazdirildi!\n");

}

int main()
{
    //dosya okuma islemi
    FILE* file = fopen ("ks_4_0.txt", "r");

    if (file == NULL)
    {
      printf ("Dosya Bulunamadi.");
      return 1;
    }

    int n, W;
    int i = 0;
    /*ilk satirin ilk sutununu= toplam item sayisi*/
    fscanf (file, "%d", &i);
    n = i;
    /*Ýlk satirin ikinci sutunu= Kapasite */
    fscanf(file, "%d", &i);
    W = i;

    int val[n];
    int wt[n];
    int j = 0;

    for (j = 0; j<n; j++)
    {
        fscanf(file, "%d", &i);
        val[j] = i;

        fscanf(file, "%d", &i);
        wt[j] = i;
    }

    /*Secime gore knapsack */
    int sec;
    printf("Dinamik Knapsack[1] (4luk ve 100luk icin kullanilabilir)\nDinamik Knapsack[2] (10000lik icin kullanilabilir)\nGreedy Knapsack[3]\n:");
    scanf("%d",&sec);

    if(sec==1)
    {
        knapSack(W, wt, val, n);
    }
    else if(sec==2)
    {
        knapSack2(W, wt, val, n);
    }
    else if(sec==3)
    {
        GreegyKnapsack(W, wt, val, n);
    }
    else
        printf("Hatali secim yaptiniz");

    return 0;
}





