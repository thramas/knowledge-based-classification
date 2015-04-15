#include<stdio.h>
void classification(int hh[16641],int hv[16641],int vv[16641])
{

    int label[16641] = {-1};
    int i;int val;int one=0,two=0,three=0,four=0;
    FILE *fpoint1,*fpoint2,*fpoint3;
    fpoint1 = fopen("hhband.txt","w");
    fpoint2 = fopen("hvband.txt","w");
    fpoint3 = fopen("vvband.txt","w");
    for(i=0;i<10000;i++){
        fprintf(fpoint1,"%d ",hh[i]);
        fprintf(fpoint2,"%d ",hv[i]);
        fprintf(fpoint3,"%d ",vv[i]);
    }
    for(i=0;i<10000;i++){
            if(hv[i]!=0)
                val = hv[i]/vv[i];
            else
                val = -9999;
            if(hv[i]<30){
                if(hv[i]>=18){//label for further branching------left child of first branching
                        if(hv[i] < 25){
                            three++;//label for bare soil-------right child of second decision
                        }
                        else{
                        two++;//label for short vegetation
                        }
                    }
                    else {
                        four++;//label for urban
                    }//label for water-------right child of first decision
            }
            else {
                   one++;
            }
            }
    //printf("%d %d %d %d",one,two,three,four);
    printf("Water percentage=%f\n",(one/10000.0)*100);
        printf("Bare Soil percentage=%f\n",(two/10000.0)*100);
        printf("Vegetation percentage=%f\n",(three/10000.0)*100);
        printf("Unclassified percentage=%f\n",((four)/10000.0)*100);
    return;
}
