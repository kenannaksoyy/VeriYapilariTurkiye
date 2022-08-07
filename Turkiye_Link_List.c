#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct sehirler
{
    char sehirismi[50];
    char bolgeismi[50];
    char plakano[50];
    int intplakano;
    char komsusehirisim[20][50];
    int komsusayisi;
} shrlr[1000];

struct dugumsehir
{
    int dsplaka;
    int dskomsusayisi;
    char dssehir[50];
    char dsbolge[50];
    struct dugumkomsu *dkilk;
    struct dugumsehir *dsonceki;
    struct dugumsehir *dssonraki;
};
typedef struct dugumsehir ds;

ds *dsilk=NULL,*dsson=NULL;
ds *dsgezici=NULL;

struct dugumkomsu
{
    int dkplakano;
    struct dugumkomsu *dksonraki;
};
typedef struct dugumkomsu dk;



void listeolustur(int plaka,int komsusayisii, char sehirismi[50], char bolge[50])
{

    ds *yenid = (ds*)malloc(sizeof(ds));
    yenid->dsplaka=plaka;
    yenid->dskomsusayisi=komsusayisii;
    strcpy(yenid->dssehir,sehirismi);
    strcpy(yenid->dsbolge,bolge);
    yenid->dkilk=NULL;

    if(dsilk==NULL)
    {
        yenid->dssonraki=NULL;
        yenid->dsonceki=NULL;
        dsilk=yenid;
        dsson=yenid;

        return ;
    }
    else
    {


        dsgezici=dsilk;
        if((dsgezici->dsplaka) > (yenid->dsplaka) && dsgezici==dsilk)
        {
            yenid->dssonraki=dsgezici;
            yenid->dsonceki=NULL;
            dsgezici->dsonceki=yenid;
            dsilk = yenid;
            return ;
        }

        while(dsgezici->dssonraki!=NULL && (dsgezici->dssonraki->dsplaka) < (yenid->dsplaka))
        {
            dsgezici = dsgezici->dssonraki;

        }

        if(dsgezici->dssonraki==NULL)
        {
            dsgezici->dssonraki = yenid;
            yenid->dsonceki= dsgezici;
            yenid->dssonraki = NULL;
            dsson =yenid;
            return ;
        }
        ds *ttemp = dsgezici->dssonraki;
        dsgezici->dssonraki = yenid;
        yenid ->dssonraki =ttemp;
        yenid ->dsonceki = dsgezici;
        ttemp->dsonceki = yenid;
        return ;
    }

}

void bolgesehirgoster(char bolgeismi[50])
{
    ds *gezici=dsilk;
    printf("%s Bolgesindeki sehirler\n",bolgeismi);
    while(gezici!=NULL)
    {
        if (strcmp(gezici->dsbolge,bolgeismi)==0)
        {
            printf("Sehir Plakasi %d Sehir Ismi %s Sehir Bolgesi %s Sehir Komsusayisi %d\n",gezici->dsplaka,gezici->dssehir,gezici->dsbolge,gezici->dskomsusayisi);
        }
        gezici=gezici->dssonraki;
    }
}

void sehirbilgisigosterisimgirerek(char sehirismi[50])
{
    ds *gezici=dsilk;
    printf("Sehir ismi ile arama yapilmistir\n");
    while(gezici!=NULL)
    {
        if (strcmp(gezici->dssehir,sehirismi)==0)
        {
            printf("Sehir Plakasi %d Sehir Ismi %s Sehir Bolgesi %s Sehir Komsusayisi %d\n",gezici->dsplaka,gezici->dssehir,gezici->dsbolge,gezici->dskomsusayisi);
            return;
        }
        gezici=gezici->dssonraki;
    }
    printf("%s sehir kayitta yok \n",sehirismi);

}
void sehirbilgisigosterplakagirerek(int plaka)
{
    ds *gezici=dsilk;
    printf("Plaka no ile arama yapilmistir\n");
    while(gezici!=NULL)
    {
        if (gezici->dsplaka==plaka)
        {
            printf("Sehir Plakasi %d Sehir Ismi %s Sehir Bolgesi %s Sehir Komsusayisi %d \n",gezici->dsplaka,gezici->dssehir,gezici->dsbolge,gezici->dskomsusayisi);
            return;
        }
        gezici=gezici->dssonraki;
    }


    printf("%d plakali kayit yok\n",plaka);
}
int plakavarmi(int plakano)
{
    ds *gezici=dsilk;
    while(gezici!=NULL)
    {
        if (gezici->dsplaka==plakano)
        {
            return 0;
        }
        gezici=gezici->dssonraki;
    }
    return 1;

}
int sehirvarmi(char sehir[50])
{
    ds *gezici=dsilk;
    while(gezici!=NULL)
    {
        if (strcmp(gezici->dssehir,sehir)==0)
        {
            return 0;
        }
        gezici=gezici->dssonraki;
    }
    return 1;

}
void basindansilme()
{
    if(dsilk!=NULL)
    {
        if(dsilk->dssonraki!=NULL)
        {
            ds *temp2=dsilk;
            dsilk=dsilk->dssonraki;
            free(temp2);
        }
        else
        {
            free(dsilk);
            dsilk=NULL;
        }
    }
}
void elemansilme(int plakano)
{

    if(dsilk->dsplaka==plakano)
    {
        basindansilme();
    }
    else if(dsson->dsplaka==plakano)
    {

        ds *temps=dsson;
        dsson=dsson->dsonceki;
        free(temps);
        dsson->dssonraki=NULL;
    }
    else
    {

        ds *temp=dsilk;
        while(temp->dssonraki->dsplaka!=plakano)
        {

            temp=temp->dssonraki;
        }
        ds *temp1=temp->dssonraki->dssonraki;
        ds *temp2=temp;
        free(temp->dssonraki);
        temp2->dssonraki=temp1;

    }

}
void basindansilmeisimile()
{
    if(dsilk!=NULL)
    {
        if(dsilk->dssonraki!=NULL)
        {
            ds *temp2=dsilk;
            dsilk=dsilk->dssonraki;
            free(temp2);
        }
        else
        {
            free(dsilk);
            dsilk=NULL;
        }
    }
}
void elemansilmeisimile(char sehirismi[50])
{

    if(strcmp(dsilk->dssehir,sehirismi)==0)
    {
        basindansilmeisimile();
    }
    else if(strcmp(dsson->dssehir,sehirismi)==0)
    {

        ds *temps=dsson;
        dsson=dsson->dsonceki;
        free(temps);
        dsson->dssonraki=NULL;
    }
    else
    {

        ds *temp=dsilk;
        while(strcmp(temp->dssonraki->dssehir,sehirismi)!=0)
        {
            temp=temp->dssonraki;
        }
        ds *temp1=temp->dssonraki->dssonraki;
        ds *temp2=temp;
        free(temp->dssonraki);
        temp2->dssonraki=temp1;

    }

}
void komsudugumolustur(int fsehirsayisi)
{
    ds *gezici=dsilk;
    int i,j,k;
    while(gezici!=NULL)
    {
        for(i=0; i<fsehirsayisi; i++)
        {
            if(gezici->dsplaka==shrlr[i].intplakano)
            {

                for(j=0; j<gezici->dskomsusayisi; j++)
                {

                    ds *gezici2=dsilk;
                    while(gezici2!=NULL)
                    {

                        if(strcmp(shrlr[i].komsusehirisim[j],gezici2->dssehir)==0)
                        {

                            if(gezici->dkilk==NULL)
                            {

                                gezici->dkilk=(dk*)malloc(sizeof(dk));
                                gezici->dkilk->dkplakano=gezici2->dsplaka;
                                gezici->dkilk->dksonraki=NULL;

                            }
                            else
                            {
                                if((gezici->dkilk->dkplakano) > (gezici2->dsplaka))
                                {
                                    dk *yenii=(dk*)malloc(sizeof(dk));
                                    yenii->dkplakano=gezici2->dsplaka;
                                    yenii->dksonraki=gezici->dkilk;
                                    gezici->dkilk=yenii;


                                }
                                else{
                                    dk *gecici=gezici->dkilk;
                                    dk *yenii=(dk*)malloc(sizeof(dk));
                                    yenii->dkplakano=gezici2->dsplaka;
                                    while(gecici!=NULL){

                                        if(gecici->dksonraki==NULL && (gecici->dkplakano)<=(gezici2->dsplaka)){
                                            yenii->dksonraki=NULL;
                                            gecici->dksonraki=yenii;
                                            break;
                                        }
                                        if((gecici->dksonraki->dkplakano) >(gezici2->dsplaka)){
                                            yenii->dksonraki=gecici->dksonraki;
                                            gecici->dksonraki=yenii;
                                            break;
                                        }
                                        gecici=gecici->dksonraki;
                                    }
                                }
                            }


                        }

                        gezici2=gezici2->dssonraki;

                    }


                }

            }
        }
        gezici=gezici->dssonraki;
    }
}


void Listele()
{
    ds  *liste=dsilk;
    while(liste!=NULL)
    {
        printf("Sehir Plakasi %d Sehir Ismi %s Sehir Bolgesi %s Sehir Komsu Sayisi %d Komsular Plakasi ",liste->dsplaka,liste->dssehir,liste->dsbolge,liste->dskomsusayisi);
        dk *dkliste=liste->dkilk;
        while(dkliste!=NULL){
            printf("%d ",dkliste->dkplakano);
            dkliste=dkliste->dksonraki;
        }
        printf("\n");
        liste=liste->dssonraki;
    }

}

int main()
{
    char dosyayolu[100]="C:\\Users\\emrey\\OneDrive\\Masaüstü\\sehirler\\sehirler.txt";
    FILE *dosya;
    char satirvirgulkontrol;
    int sehirsayisi=-1;
    int virgulsayisi=0;
    char tum[1000];
    if((dosya=fopen(dosyayolu,"r"))!=NULL)
    {

        while(!feof(dosya))
        {
            satirvirgulkontrol=getc(dosya);

            if(satirvirgulkontrol=='\n')
            {
                shrlr[sehirsayisi].komsusayisi=virgulsayisi-2;
                sehirsayisi=sehirsayisi+1;
                virgulsayisi=0;
            }
            if(satirvirgulkontrol==',')
            {
                virgulsayisi=virgulsayisi+1;
            }


        }
    }
    fclose(dosya);
    char satirr[200];
    int satirsayisi=0;
    const char virgul[2]=",";
    char *token;
    int komsusayac=0;
    int silinenplaka;
    int silinenisim[50];
    if((dosya=fopen(dosyayolu,"r"))!=NULL)
    {

        while(!feof(dosya))
        {
            satirvirgulkontrol=getc(dosya);
            if(satirvirgulkontrol=='\n' && satirsayisi<sehirsayisi )
            {
                fscanf(dosya,"%s",&satirr);
                token = strtok(satirr, virgul);
                strcpy(shrlr[satirsayisi].plakano,token);
                shrlr[satirsayisi].intplakano=atoi(shrlr[satirsayisi].plakano);
                token = strtok(NULL,virgul);
                strcpy(shrlr[satirsayisi].sehirismi,token);
                token = strtok(NULL,virgul);
                strcpy(shrlr[satirsayisi].bolgeismi,token);
                token = strtok(NULL,virgul);

                while( token != NULL )
                {
                    strcpy(shrlr[satirsayisi].komsusehirisim[komsusayac],token);
                    komsusayac=komsusayac+1;
                    token = strtok(NULL,virgul);

                }
                satirsayisi=satirsayisi+1;
                komsusayac=0;

            }
        }
    }
    fclose(dosya);
    int i1,i2;
    for(i1=0; i1<sehirsayisi; i1++)
    {
        printf("%d ",shrlr[i1].intplakano);
        printf("%s ",shrlr[i1].sehirismi);
        printf("%s ",shrlr[i1].bolgeismi);
        for(i2=0; i2<shrlr[i1].komsusayisi; i2++)
        {
            printf("%s ",shrlr[i1].komsusehirisim[i2]);
        }
        printf("\n");
    }

    for(i1=0; i1<sehirsayisi; i1++)
    {
        listeolustur(shrlr[i1].intplakano,shrlr[i1].komsusayisi,shrlr[i1].sehirismi,shrlr[i1].bolgeismi);

    }
    Listele();


    printf("\n");
    int a=1;
    int a1=1;
    int a3=1;
    int secim;
    char arasehir[50];
    int araplaka;
    char arabolge[50];
    char eklesehir[50];
    int ekleplaka;
    char eklebolge[50];
    int eklekomsusayisi;
    int a4=1;
    komsudugumolustur(sehirsayisi);


    printf("\nListi gormek icin 1\n");
    printf("Sehir ismi ile arama yapmak icin 2\n");
    printf("Plaka no ile arama yapmak icin 3\n");
    printf("Ayni bolgede bulunan sehirlerin bilgileri icin 4\n");
    printf("Liste eleman eklemek icin 5\n");
    printf("Listte eleman silmek icin 6\n");
    printf("Listte sehir ismi ile elaman silmek icin 7\n");
    printf("Programi kapatmak icin 0\n");
    printf("\nSeciminizi giriniz\n");
    scanf("%d",&secim);
    while(secim!=0)
    {

        if(secim==1)
        {
            Listele();
        }
        else if(secim==2)
        {
            printf("\nArancak sehir ismini giriniz\n");
            scanf("%s",&arasehir);
            sehirbilgisigosterisimgirerek(arasehir);
        }
        else if(secim==3)
        {
            printf("\nAranacak sehir plakasini giriniz\n");
            scanf("%d",&araplaka);
            sehirbilgisigosterplakagirerek(araplaka);
        }
        else if(secim==4)
        {
            printf("\nBolge ismini giriniz\n");
            scanf("%s",&arabolge);
            bolgesehirgoster(arabolge);

        }
        else if(secim==5)
        {
            printf("\nEklemek istediginiz plakasi\n");
            scanf("%d",&ekleplaka);
            a= plakavarmi(ekleplaka);
            if(a==0)
            {
                printf("\nAyni plaka nolu sehir var\n");
            }
            else
            {
                printf("\nGirilen plaka ile uyusan sehir yok \n");
                printf("Sehir ismi girin\n");
                scanf("%s",&eklesehir);
                a1=sehirvarmi(eklesehir);
                if(a1==0)
                {
                    printf("\nAyni isimli sehir var\n");
                }
                else
                {
                    printf("\nGirilen sehir ve plaka yeni kayit icin uygun\n");
                    printf("\nSehir bolgesini giriniz\n");
                    scanf("%s",&eklebolge);
                    printf("\nSehir komsusayisi giriniz\n");
                    scanf("%d",&eklekomsusayisi);
                    listeolustur(ekleplaka,eklekomsusayisi,eklesehir,eklebolge);
                    Listele();

                }

            }


        }
        else if(secim==6)
        {
            printf("\nSilinmek istenen sehir plakasi girin\n");
            scanf("%d",&silinenplaka);
            a3=plakavarmi(silinenplaka);
            if(a3==0)
            {
                elemansilme(silinenplaka);
                Listele();
            }
            else
            {
                printf("Silinicek plaka kaydi listte yok\n");
            }

        }
        else if(secim==7)
        {
            printf("\nSilinmek istenen sehir ismini giriniz\n");
            scanf("%s",silinenisim);
            a4=sehirvarmi(silinenisim);
            if(a4==0)
            {
                elemansilmeisimile(silinenisim);
                Listele();
            }
            else
            {
                printf("Silinecek sehir ismi kaydi listte yok\n");
            }

        }
        else if(secim==0)
        {
            printf("\nProgram bitmistir\n");
        }

        printf("\n\nListi gormek icin 1\n");
        printf("Sehir ismi ile arama yapmak icin 2\n");
        printf("Plaka no ile arama yapmak icin 3\n");
        printf("Ayni bolgede bulunan sehirlerin bilgileri icin 4\n");
        printf("Liste eleman eklemek icin 5\n");
        printf("Listte plaka ile eleman silmek icin 6\n");
        printf("Listte sehir ismi ile elaman silmek icin 7\n");
        printf("Programi sonlandirmak icin 0\n");
        printf("\nSeciminizi giriniz\n");
        scanf("%d",&secim);

    }

    return 0;
}
