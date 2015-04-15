#include <stdio.h>
#include <math.h>
#include "classifier.h"
int main()
{
        int hh[140][140];
        int hv[140][140];
        int vv[140][140];
        int meanhh[129][129];
        int meanhv[129][129];
        int meanvv[129][129];
        int varhh[129][129];
        int varhv[129][129];
        int varvv[129][129];
        int vvband[16641];
        int hvband[16641];
        int hhband[16641];
        int win=2,n,i,j,a,b,c=0,sumhh,sumhv,sumvv;
        FILE *fphh;
        FILE *fphh1;
        FILE *fphv;
        FILE *fphv1;
        FILE *fpvv;
        FILE *fpvv1;
        fphh = fopen("hhdata.txt","rb");
        fphh1 = fopen("hhwriteup.txt","w");
        fphv = fopen("hvdata.txt","rb");
        fphv1 = fopen("hvwriteup.txt","w");
        fpvv = fopen("vvdata.txt","rb");
        fpvv1 = fopen("vvwriteup.txt","w");
        for (i = 0; i < 128; i++)
        {
            for(j=0;j<128;j++){
            fscanf(fphh,"%d",&hh[i][j]);
            fscanf(fphv,"%d",&hv[i][j]);
            fscanf(fpvv,"%d",&vv[i][j]);
            }
        }
        fprintf(fphh1,"The DATA FILE----------------------\n\n\n\n");
        fprintf(fphv1,"The DATA FILE----------------------\n\n\n\n");
        fprintf(fpvv1,"The DATA FILE----------------------\n\n\n\n");
        for (i = 0; i < 129; i++)
        {
            for(j=0;j<129;j++){
                fprintf(fphh1,"%d\t",hh[i][j]);
                fprintf(fphv1,"%d\t",hv[i][j]);
                fprintf(fpvv1,"%d\t",vv[i][j]);
            }
            fprintf(fphh1,"\n");
            fprintf(fphv1,"\n");
            fprintf(fpvv1,"\n");
        }
        for (i = 2; i < 129; i++)
        {
            for(j=2;j<129;j++){
                sumhh = 0;
                sumhv = 0;
                sumvv = 0;
                for(a=-2;a<=2;a++){
                    for(b=-2;b<=2;b++){
                        sumhh = sumhh + hh[i+a][j+b];
                        sumhv = sumhv + hv[i+a][j+b];
                        sumvv = sumvv + vv[i+a][j+b];
                    }
                }
                meanhh[i-2][j-2] = sumhh/25;
                meanhv[i-2][j-2] = sumhv/25;
                meanvv[i-2][j-2] = sumvv/25;
                //(float)sumhh/(float)(n*n);
            }
        }
        fprintf(fphh1,"The MEAN FILE----------------------\n\n\n\n");
        fprintf(fphv1,"The MEAN FILE----------------------\n\n\n\n");
        fprintf(fpvv1,"The MEAN FILE----------------------\n\n\n\n");
        for (i = 0; i < 128; i++)
        {
            for(j=0;j<128;j++){
                fprintf(fphh1,"%d\t",meanhh[i][j]);
                fprintf(fphv1,"%d\t",meanhv[i][j]);
                fprintf(fpvv1,"%d\t",meanvv[i][j]);
            }
            fprintf(fphh1,"\n");
            fprintf(fphv1,"\n");
            fprintf(fpvv1,"\n");
        }
        for (i = 2; i < 129; i++)
        {
            for(j=2;j<129;j++){
                sumhh = 0;
                sumhv = 0;
                sumvv = 0;
                for(a=-2;a<=2;a++){
                    for(b=-2;b<=2;b++){
                        sumhh = sumhh + (hh[i+a][j+b]-meanhh[i][j])*(hh[i+a][j+b]-meanhh[i][j]);
                        sumhv = sumhv + (hv[i+a][j+b]-meanhv[i][j])*(hv[i+a][j+b]-meanhv[i][j]);
                        sumvv = sumvv + (vv[i+a][j+b]-meanvv[i][j])*(vv[i+a][j+b]-meanvv[i][j]);
                    }
                }
                varhh[i-2][j-2] = sqrt(sumhh/24);
                varhv[i-2][j-2] = sqrt(sumhv/24);
                varvv[i-2][j-2] = sqrt(sumvv/24);
                //(float)sumhh/(float)(n*n);
            }
        }
        fprintf(fphh1,"The varhhIANCE FILE----------------------\n\n\n\n");
        fprintf(fphv1,"The varhhIANCE FILE----------------------\n\n\n\n");
        fprintf(fpvv1,"The varhhIANCE FILE----------------------\n\n\n\n");
        for (i = 0; i < 128; i++)
        {
            for(j=0;j<128;j++){
                fprintf(fphh1,"%d\t",varhh[i][j]);
                fprintf(fphv1,"%d\t",varhv[i][j]);
                fprintf(fpvv1,"%d\t",varvv[i][j]);
            }
            fprintf(fphh1,"\n");
            fprintf(fphv1,"\n");
            fprintf(fpvv1,"\n");
        }
        for (i = 0; i < 128; i++)
        {
            for(j=0;j<128;j++){
                vvband[c] = varhh[i][j];
                hvband[c] = varhv[i][j];
                hhband[c] = varhh[i][j];
                c++;
            }
        }
        classification(hhband,hvband,vvband);
        printf("\n");
        return 0;
}
