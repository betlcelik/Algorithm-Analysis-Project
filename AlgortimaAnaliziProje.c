#include<stdio.h>
#include<locale.h>
#include<stdlib.h>
#include<string.h>
#define MAX 8

typedef struct renk{
	char name[MAX];
	int value;
}RENK;

int isSafe(int **matrix,int n,int row);
int shiftRightTheRow(int **matrix,int n,int row);
int arrangeTheMatrix(int **matrix,RENK **renkler,int n,int row,int *count,int mustShift,int detail);
void printWithNames(int **matrix,int n,RENK **arr);
void takeColorMatrix(int **matrix,int n,RENK **renkler);


int main(){
	setlocale(LC_ALL, "Turkish"); 
	int choice=0;
	int n=0,i,j,k;
	int **oyunTahtasi,*count;
	char string[MAX];
	RENK *renkler[MAX];
	
	while(choice != 4 )
	{
		printf("Yapmak istediðiniz iþlemi seçiniz\n1->Renkler Matrisini Oluþturma\n2->Normal Modda Çalýþtýrma\n3->Detay Modda Çalýþtýrma\n4->Çýkýþ\nSeçiminiz : ");
		scanf("%d",&choice);
		
		if(choice == 1)
		{
				printf("Oyun tahtasý boyutunu belirleyiniz \nNOT : Berlirlediðiniz boyut 3'ten küçük 8'den büyük olmamalý\nBoyut:\n ");
	    		scanf("%d",&n);
	    		
	    		//Kullanýcý geçerli bir boyut girene kadar deðer almaya devam eder
				while(n<3 || n > 8)
				 {
					printf("Oyun tahtasý boyutunu belirleyiniz \nNOT : Berlirlediðiniz boyut 3'ten küçük 8'den büyük olmamalý\nBoyut:\n ");
	    			scanf("%d",&n);
				}
				
				//belirtilen boyuta göre matris için bellekte yer ayrýlýr
				oyunTahtasi = (int**)malloc(n*sizeof(int*));
				
				//arrangeTheMatrix fonksiyonunda kullanýlmak üzere her satýra kaç defa shift-right iþleminin yapýldýðýný tutan dizi için bellekte yer ayrýlýr
				count = (int*) malloc (n * sizeof(int));
				
				
				//ilk durumda hiçbir satýraiþlem yapýlmadýðý için ilgili dizinin tüm elemanlarý sýfýrlanýr
				for(i=0;i<n;i++)
				{
					count[i]=0;
				}
				
				//kullanýcýdan alýnan eleman sayýsýna göre matrisi oluþturmak için takeColorMatrix fonksiyonu çaðrýlýr
				takeColorMatrix(oyunTahtasi,n,renkler);
				
			
		}
		//Normal modda çalýþtýrma 
		else if(choice == 2) 
		{
			//normal modda çalýþtýrýldýðý için detail parametresi dýfýr olrak gönderilir
			if(arrangeTheMatrix(oyunTahtasi,renkler,n,1,count,0,0) == 1)
			{
		    printf("Düzenlenen renk matrisi\n");
		    printWithNames(oyunTahtasi,n,renkler);
	        }
	        else
			{
		    printf("Girdiðiniz renk matrisi için bir sonuç oluþturulamadý \n");
	  	   
	       }
	   }
	   //detay modda çalýþtýrma
	    else if(choice == 3)
	    { 
	        if(arrangeTheMatrix(oyunTahtasi,renkler,n,1,count,0,1) == 1)
			{
		   	 	printf("Düzenlenen renk matrisi\n");
		    	printWithNames(oyunTahtasi,n,renkler);
	        }
	        else
			{
				arrangeTheMatrix(oyunTahtasi,renkler,n,1,count,0,1) ;
		    	printf("Girdiðiniz renk matrisi için bir sonuç oluþturulamadý \n");
	  	   
	        }
	    
	   }
	   else
	   {
	   	if(choice != 4)
	   	 printf("Geçerli bir deðer girmediniz !!");
	   }
		
		printf("\n");	
	}
	printf("Çýkýþ yapýldý");

return 0;	
}

//girilen n sayýsýna göre kullanýcýdan renk matrisini alýr
void takeColorMatrix(int **matrix,int n,RENK **renkler)
{
	char string[MAX];
	int i,j,k;
	
	for(i=0;i<n;i++)
	{
		matrix[i]=(int*)malloc(n*sizeof(int));
	}
		
	//matriste bulunan renkleri tutacak dizi için bellekte yer ayrýlýr	
	for(i=0;i<n;i++)
	{
		renkler[i]=malloc(sizeof(RENK));
	}
	
					
	for(i=0;i<n;i++)
	{
		printf("\n%d. satýr \n",i);
		for(j=0;j<n;j++)
		{
			
			scanf("%s",string);
			
			//matrisin ilk satýrýnda girilen renkler bir struct dizisine atanýr
			if(i==0)
			{
	        	strcpy(renkler[j]->name,string);
	        	renkler[j]->value=j;
	       		matrix[i][j] = renkler[j]->value;
			}
			//iþlem kolaylýðý için kullanýcýn girdiði renklerin 
			//oluþturulan struct dizisine göre deðeri bulunur ve integer özellikteki matrise atanýr
			else
			{
				k=0;
				while(strcmp(string,renkler[k]->name) != 0)
				{
					k++;
				}
				
				matrix[i][j]=renkler[k]->value;
			}

		}
	    
	}
				
				printf("Girmiþ olduðunuz matris : \n");
				printWithNames(matrix,n,renkler);	
}



int arrangeTheMatrix(int **matrix,RENK **renkler,int n,int row,int *count,int mustShift,int detail)
{
	//row == n ise tüm satýrlar için kontrol saðlanmýþtýr
	if(row == n)
	{
		return 1;	
	}
	
	//iþlemler sonucunda ilk satýra dönülmüþ ve burda da n-1 adet shift gerçekleþmiþse tüm yollar denenmiþ ancak sonuç elde edilememiþtir 
	if(count[0] == n)
	{
		return -1;
	}
	
	//mustShift deðiþkeni iþlemlere baþlamadan önce ilgili satýr için bir defa shift-right iþlemi yapýlmasý gerektiðini belirtir
	if(mustShift == 1)
	{
		shiftRightTheRow(matrix,n,row);
		count[row]++;
	}
	
	
	if(row != 0) 
	{
		if(count[row] == n-1)
		{
			count[row]=0;
			arrangeTheMatrix(matrix,renkler,n,row-1,count,1,detail);	
		}
			//bulunduðumuz satýr için isSafe fonksiyonu çaðýrýlarak öceki satýrlarla karþýlaþtýrma yapýlýr 
	
	if(isSafe(matrix,n,row) == 1) //isSafe fonksiyonu 1 deðerini dönmüþse önceki satýrlardaki deðerler ayný deðere sahip olan bir sütun yoktur
	{
		//detay mod seçilmiþse bir satýr üzerinde iþlem bittiðinde matris ekrana yazdýrýlýr 
		if(detail == 1) 
		{
			printWithNames(matrix,n,renkler);
		}
		printf("\n");
		
		arrangeTheMatrix(matrix,renkler,n,row+1,count,0,detail);   //bir sonraki satýr için fonksiyon çaðrýlýr
	}
	
	//eðer isSafe fonksiyonu sonuç olarak 1 deðerini dönmemiþse çakýþan sütunlar vardýr 
	//bulunduðumuz satýrda shift-right iþlemi yapýlarak sütunlarýn çakýþmasýný engellemeyi deneriz 
	//bir satýrda en fazla n-1 defa shift iþlemi yapýlabilir n. shift iþlemi baþlangýç durumuna döner 
	else
	{ 
		if(count[row] != n-1)
		{
		//shiftRightTheRow(matrix,n,row);  //bulunduðumuz satýrda shift iþlemi yaparýz ve yeni oluþan durum için tekrar fonksiyonu çaðýrýrýz
		//count[row]++;                    //bulunduðumuz satýrda shift iþlemi yaptýmðýmýz için ilgili dizide artýrma iþlemi yapýlýr
		arrangeTheMatrix(matrix,renkler,n,row,count,1,detail);
		
		}
		else
		{
			//eðer n-1 shift-right iþlemi sonucunda düzelmediyse bir önceki satýra geri dönülür
			//bulunduðumuz satýrla ilgili count sýfýrlanýr
	
			count[row]=0;
			arrangeTheMatrix(matrix,renkler,n,row-1,count,1,detail);
		}	
	}
	}
	else
	{
		arrangeTheMatrix(matrix,renkler,n,row+1,count,0,detail);
	}

	
	
}

int isSafe(int **matrix,int n,int row)
{
	int i,j;
	
	for(i=0;i<row;i++)
	{ 
		for(j = 0;j<n;j++)
		{
			if(matrix[i][j] == matrix[row][j])
			
				return -1;     //önceki satýrlarda ayný renk varsa -1 deðerini döner
			
		}
		
	}
	
	return 1;   //döngüden çýktýysa önceki satýrlarda çakýþan deðer yoktur 
	
}


//verilen satýr numarasýnda saða kaydýrma iþlemini gerçekleþtirir
int shiftRightTheRow(int **matrix,int n,int row)
{
	int tmp,i;
	tmp=matrix[row][n-1];
	
	for(i=n-1;i>=1;i--)
	{
		matrix[row][i]=matrix[row][i-1];
		
	}
	matrix[row][0]=tmp;

}

//integer tipindeki matrisin deðerlerini ilgili struct yapýsýndaki renk isimleriyle ekrana yazdýrýr
void printWithNames(int **matrix,int n,RENK **arr)
{
	int i,j,k;
	RENK *tmp;
	
	//matrisin her elemaný için renkler dizisi taranýr eþleþen deðerin ismi ekrana yazdýrýlýr
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			k=0;
			tmp=arr[k];
			while(tmp->value != matrix[i][j])
			{
			  k++;
			  tmp=arr[k];	
			}
			 
			printf("%s\t",tmp->name);  
		}
		printf("\n");
		
	}
	
	
}
	
	
