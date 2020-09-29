/*
PRAKTIKUM KRIPTOGRAFI - PROGRAM HILL CIPHER
Nama			: Hana Meilina, Sharashena Chairani, Salma Alifia Shafira
NPM				: 140810180012, 140810180022, 140810180058
*/

#include <iostream>
using namespace std;

typedef int matriks[5][5];

// CipherText (Ct) = Pt x K
// PlainText (Pt) = Ct x K^-1
// Key (K)  = Pt^-1 x Ct

void isiMatriks(matriks& x, int nBaris, int nKolom){
	for (int i=0; i<nBaris; i++){
		for (int j=0; j<nKolom; j++) {
			cout<<"Data ke-["<<i+1<<","<<j+1 <<"] : "; 
			cin>>x[i][j];
		}
    }
}

void cetakMatriks(matriks x, int nBaris, int nKolom){
	for (int i=0; i<nBaris; i++) {
		for (int j=0; j<nKolom; j++) {
			cout<<" "<< x[i][j] << " ";
		}
		cout<<endl;
	}	
}

void kali (matriks x, matriks y, int nBaris, int nKolom){
int i,j,k;
matriks d;
	
	for(i = 0; i < nBaris; ++i)			//inisiasi isi matriks perkalian anggotanya adalah 0
        for(j = 0; j < nKolom; ++j)
        {
            d[i][j]=0;
        }

    for(i = 0; i < nBaris; ++i)			// Operasi Perkalian
        for(j = 0; j < nKolom; ++j)
            for(k = 0; k < nKolom; ++k)
            {
                d[i][j] += x[i][k] * y[k][j];
            }

    cout << endl << "Hasil Matriks [2x1] : " << endl;  // Output

    for(i=0;i<2;i++){
		for(j=0;j<1;j++){
			d[i][j]%=26;
	        cout << "  " << d[i][j]<<" ";
		}
		cout<<endl<<endl;
	}

	cout<<endl;
	printf("Hasil : ");
	for(i=0;i<2;i++){
		for(j=0;j<1;j++){
			printf("%c",d[i][j]+'a');
		}
	}
	printf("\n");
	cout<<endl;
}

void keyKali (matriks x, matriks y, int nBaris, int nKolom){
int i,j,k;
matriks d;

	for(i = 0; i < nBaris; ++i)			//inisiasi isi matriks perkalian anggotanya adalah 0
        for(j = 0; j < nKolom; ++j)
        {
            d[i][j]=0;
        }

    for(i = 0; i < nBaris; ++i)			// Operasi Perkalian
        for(j = 0; j < nKolom; ++j)
            for(k = 0; k < nKolom; ++k)
            {
                d[i][j] += x[i][k] * y[k][j];
            }

    for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			d[i][j]%=26;
	        cout << "  " << d[i][j]<<" ";
		}
		cout<<endl<<endl;				// Output
	}
}

float gcd(int a, int b) {				//Euclidean Algorithm untuk mendapatkan X
    bool flag = false;
    if (b > a) {
        flag = true;
        swap(a, b);
    }

    int x = 1;
    int y = 0;
    int g = a;
    int r = 0;
    int s = 1;
    int t = b;

    while (t > 0) {
        int q = g / t;
        int u = x - q*r;
        int v = y - q*s;
        int w = g - q*t;
        x = r;
        y = s;
        g = t;
        r = u;
        s = v;
        t = w;
    }

    if (flag) {
        return y;
    } else {
        return x;
    }
}

float modDiv(int d) {
    int x = gcd(d, 26);

    x = (x < 0 ? x + 26 : x);
    return (x % 26);
}

void inverse(matriks x, matriks& y){
	int a = x[0][0];
	int b = x[0][1];
	int c = x[1][0];
	int d = x[1][1];

	int det = (a*d) - (b*c);
	
	int mod=modDiv(det);

	y[0][0] = (mod*d);
	y[0][1] = (mod*b*(-1));
	y[1][0] = (mod*c*(-1));
	y[1][1] = (mod*a);

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{	
			y[i][j]%=26; 

			if(y[i][j] < 0){
				y[i][j]+=26; 
			}
		}
	}
	cetakMatriks(y,2,2);
}

void textToNumber(char text[], matriks& textMatrix){
int i,j;
	for(i=0;i<2;i++){
		for(j=0;j<1;j++){
			textMatrix[i][j]=text[i]-'a';
		}
	}

	cetakMatriks(textMatrix,2,1);
}

void newtextToNumber(char text[], matriks& textMatrix){

	textMatrix[0][0] = text[0]-'a';
	textMatrix[0][1] = text[2]-'a';
	textMatrix[1][0] = text[1]-'a';
	textMatrix[1][1] = text[3]-'a';

	cetakMatriks(textMatrix,2,2);
}

void enkripsi() {
  matriks x;          // variabel array x bertipe matriks
  matriks y;

  char text[10];


  cout<<"\t ENKRIPSI HILL CIPHER\n";
  cout<<"Masukkan 2 Karakter PlainText : "; cin>>(" %s",text);

  
  cout<<endl<<"Masukkan Matriks Key 2x2 : "<<endl;
  isiMatriks(x,2,2);cout<<endl;

  cout<<"\nMatriks Key 2x2 : "<<endl;
  cetakMatriks(x,2,2);

  cout<<"\nMatriks Plaintext 2x1 : "<<endl;
  textToNumber(text,y);
  kali(x,y,2,2);
}

void dekripsi() {
  matriks x;          // variabel array x bertipe matriks
  matriks y;
  matriks z;

  char text[10];

  cout<<"\t DEKRIPSI HILL CIPHER\n";
  cout<<"Masukkan 2 Karakter CipherText : "; cin>>(" %s",text);

  
  cout<<"\nMasukkan Matriks Key 2x2 : "<<endl;
  isiMatriks(x,2,2);

  cout<<"\nMatriks Key 2x2 : "<<endl;
  cetakMatriks(x,2,2);

  cout<<"\nMatriks CipherText 2x1 : "<<endl;
  textToNumber(text,y);

  cout<<"\nInverse Matriks Key 2x2 : "<<endl;
  inverse(x,z);

  kali(z,y,2,2);
}

void kunciK(){
	matriks x,y,z;

	char pText[10];
	char cText[10];

	cout<<"\t MENCARI KUNCI K HILL CIPHER\n";
	cout<<"Masukkan 4 Karakter Plaintext : "; cin>>(" %s",pText);  	
	cout<<"Masukkan 4 Karakter CipherText : "; cin>>(" %s",cText);

	cout<<"Matriks PlainText 2x2 : "<<endl;
  	newtextToNumber(pText,x);

	cout<<"Matriks CipherText 2x2 : "<<endl;
  	newtextToNumber(cText,y);

	cout<<"Invers Matriks PlainText 2x2 : "<<endl;
  	inverse(x,z);  	

  	cout<<"Matriks Key adalah : "<<endl;
  	keyKali(z,y,2,2);
}

int main(){
	int pilih;
	char jawab;
	do{
		system("cls");
		cout<<"\t PRAKTIKUM KRIPTOGRAFI - PROGRAM HILL CIPHER (m = 2)"<<endl;

		cout<<"Pilihan : "<<endl;
		cout<<"1. Enkripsi"<<endl;
		cout<<"2. Dekripsi"<<endl;
		cout<<"3. Mencari Kunci K"<<endl;
		cout<<"4. Exit"<<endl<<endl;
		cout<<"Pilih :";
		cin>>pilih;
		
		switch(pilih){
			case 1:
				system("cls");
				enkripsi();
				break;
			case 2:
				system("cls");
				dekripsi();
				break;
			case 3:
				system("cls");
				kunciK();
				break;
			case 4:
				cout<<"\nProgram Selesai";
				return 0;
				break;
			default :
				cout<<"\nAngka tidak valid!"<<endl;
				break;	
		}
		cout<<"Ulangi Program? (Y/N) : "; cin>>jawab;
	} while(jawab=='y' || jawab=='Y' );	
}
