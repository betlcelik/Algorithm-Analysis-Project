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
		printf("Yapmak istedi�iniz i�lemi se�iniz\n1->Renkler Matrisini Olu�turma\n2->Normal Modda �al��t�rma\n3->Detay Modda �al��t�rma\n4->��k��\nSe�iminiz : ");
		scanf("%d",&choice);
		
		if(choice == 1)
		{
				printf("Oyun tahtas� boyutunu belirleyiniz \nNOT : Berlirledi�iniz boyut 3'ten k���k 8'den b�y�k olmamal�\nBoyut:\n ");
	    		scanf("%d",&n);
	    		
	    		//Kullan�c� ge�erli bir boyut girene kadar de�er almaya devam eder
				while(n<3 || n > 8)
				 {
					printf("Oyun tahtas� boyutunu belirleyiniz \nNOT : Berlirledi�iniz boyut 3'ten k���k 8'den b�y�k olmamal�\nBoyut:\n ");
	    			scanf("%d",&n);
				}
				
				//belirtilen boyuta g�re matris i�in bellekte yer ayr�l�r
				oyunTahtasi = (int**)malloc(n*sizeof(int*));
				
				//arrangeTheMatrix fonksiyonunda kullan�lmak �zere her sat�ra ka� defa shift-right i�leminin yap�ld���n� tutan dizi i�in bellekte yer ayr�l�r
				count = (int*) malloc (n * sizeof(int));
				
				
				//ilk durumda hi�bir sat�rai�lem yap�lmad��� i�in ilgili dizinin t�m elemanlar� s�f�rlan�r
				for(i=0;i<n;i++)
				{
					count[i]=0;
				}
				
				//kullan�c�dan al�nan eleman say�s�na g�re matrisi olu�turmak i�in takeColorMatrix fonksiyonu �a�r�l�r
				takeColorMatrix(oyunTahtasi,n,renkler);
				
			
		}
		//Normal modda �al��t�rma 
		else if(choice == 2) 
		{
			//normal modda �al��t�r�ld��� i�in detail parametresi d�f�r olrak g�nderilir
			if(arrangeTheMatrix(oyunTahtasi,renkler,n,1,count,0,0) == 1)
			{
		    printf("D�zenlenen renk matrisi\n");
		    printWithNames(oyunTahtasi,n,renkler);
	        }
	        else
			{
		    printf("Girdi�iniz renk matrisi i�in bir sonu� olu�turulamad� \n");
	  	   
	       }
	   }
	   //detay modda �al��t�rma
	    else if(choice == 3)
	    { 
	        if(arrangeTheMatrix(oyunTahtasi,renkler,n,1,count,0,1) == 1)
			{
		   	 	printf("D�zenlenen renk matrisi\n");
		    	printWithNames(oyunTahtasi,n,renkler);
	        }
	        else
			{
				arrangeTheMatrix(oyunTahtasi,renkler,n,1,count,0,1) ;
		    	printf("Girdi�iniz renk matrisi i�in bir sonu� olu�turulamad� \n");
	  	   
	        }
	    
	   }
	   else
	   {
	   	if(choice != 4)
	   	 printf("Ge�erli bir de�er girmediniz !!");
	   }
		
		printf("\n");	
	}
	printf("��k�� yap�ld�");

return 0;	
}

//girilen n say�s�na g�re kullan�c�dan renk matrisini al�r
void takeColorMatrix(int **matrix,int n,RENK **renkler)
{
	char string[MAX];
	int i,j,k;
	
	for(i=0;i<n;i++)
	{
		matrix[i]=(int*)malloc(n*sizeof(int));
	}
		
	//matriste bulunan renkleri tutacak dizi i�in bellekte yer ayr�l�r	
	for(i=0;i<n;i++)
	{
		renkler[i]=malloc(sizeof(RENK));
	}
	
					
	for(i=0;i<n;i++)
	{
		printf("\n%d. sat�r \n",i);
		for(j=0;j<n;j++)
		{
			
			scanf("%s",string);
			
			//matrisin ilk sat�r�nda girilen renkler bir struct dizisine atan�r
			if(i==0)
			{
	        	strcpy(renkler[j]->name,string);
	        	renkler[j]->value=j;
	       		matrix[i][j] = renkler[j]->value;
			}
			//i�lem kolayl��� i�in kullan�c�n girdi�i renklerin 
			//olu�turulan struct dizisine g�re de�eri bulunur ve integer �zellikteki matrise atan�r
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
				
				printf("Girmi� oldu�unuz matris : \n");
				printWithNames(matrix,n,renkler);	
}



int arrangeTheMatrix(int **matrix,RENK **renkler,int n,int row,int *count,int mustShift,int detail)
{
	//row == n ise t�m sat�rlar i�in kontrol sa�lanm��t�r
	if(row == n)
	{
		return 1;	
	}
	
	//i�lemler sonucunda ilk sat�ra d�n�lm�� ve burda da n-1 adet shift ger�ekle�mi�se t�m yollar denenmi� ancak sonu� elde edilememi�tir 
	if(count[0] == n)
	{
		return -1;
	}
	
	//mustShift de�i�keni i�lemlere ba�lamadan �nce ilgili sat�r i�in bir defa shift-right i�lemi yap�lmas� gerekti�ini belirtir
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
			//bulundu�umuz sat�r i�in isSafe fonksiyonu �a��r�larak �ceki sat�rlarla kar��la�t�rma yap�l�r 
	
	if(isSafe(matrix,n,row) == 1) //isSafe fonksiyonu 1 de�erini d�nm��se �nceki sat�rlardaki de�erler ayn� de�ere sahip olan bir s�tun yoktur
	{
		//detay mod se�ilmi�se bir sat�r �zerinde i�lem bitti�inde matris ekrana yazd�r�l�r 
		if(detail == 1) 
		{
			printWithNames(matrix,n,renkler);
		}
		printf("\n");
		
		arrangeTheMatrix(matrix,renkler,n,row+1,count,0,detail);   //bir sonraki sat�r i�in fonksiyon �a�r�l�r
	}
	
	//e�er isSafe fonksiyonu sonu� olarak 1 de�erini d�nmemi�se �ak��an s�tunlar vard�r 
	//bulundu�umuz sat�rda shift-right i�lemi yap�larak s�tunlar�n �ak��mas�n� engellemeyi deneriz 
	//bir sat�rda en fazla n-1 defa shift i�lemi yap�labilir n. shift i�lemi ba�lang�� durumuna d�ner 
	else
	{ 
		if(count[row] != n-1)
		{
		//shiftRightTheRow(matrix,n,row);  //bulundu�umuz sat�rda shift i�lemi yapar�z ve yeni olu�an durum i�in tekrar fonksiyonu �a��r�r�z
		//count[row]++;                    //bulundu�umuz sat�rda shift i�lemi yapt�m��m�z i�in ilgili dizide art�rma i�lemi yap�l�r
		arrangeTheMatrix(matrix,renkler,n,row,count,1,detail);
		
		}
		else
		{
			//e�er n-1 shift-right i�lemi sonucunda d�zelmediyse bir �nceki sat�ra geri d�n�l�r
			//bulundu�umuz sat�rla ilgili count s�f�rlan�r
	
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
			
				return -1;     //�nceki sat�rlarda ayn� renk varsa -1 de�erini d�ner
			
		}
		
	}
	
	return 1;   //d�ng�den ��kt�ysa �nceki sat�rlarda �ak��an de�er yoktur 
	
}


//verilen sat�r numaras�nda sa�a kayd�rma i�lemini ger�ekle�tirir
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

//integer tipindeki matrisin de�erlerini ilgili struct yap�s�ndaki renk isimleriyle ekrana yazd�r�r
void printWithNames(int **matrix,int n,RENK **arr)
{
	int i,j,k;
	RENK *tmp;
	
	//matrisin her eleman� i�in renkler dizisi taran�r e�le�en de�erin ismi ekrana yazd�r�l�r
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
	
	
