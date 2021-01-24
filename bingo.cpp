/**
  * Bingo program
  * v0.1-beta
  **/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <unistd.h>
#include <bits/stdc++.h> 

#define N 35        // Number of numbers drawn
#define Nmax 49     // Drawing set limit
#define Nl 7        // Ukupan broj brojeva u listićima

using namespace std;

struct Broj {          
    int b;
    double V;
};

vector<int> Unos_k ();
void Ispis_krugova(vector<vector<int>> num);
void Calc_n (vector<vector<int>> num, struct Broj b[]);
void Ispis_n(struct Broj a[]);
void Calc_V (struct Broj numers[], int s);
void Sort_V (struct Broj numers[]);
void Ispis_V(struct Broj numers[]);
void Gen_L (struct Broj numers[]);
vector<int> Rnd_num(int a, int b);



int main() {
    
    vector<vector<int>> Komb;
   
    int opt=1;
    while (opt==1) {
        cout << "Select: " << endl << "1: Enter a combination" << endl << "2: Extraction: " << endl << "0: Exit: " << endl;
        //fflush( stdin );
        cin >> opt;
        if (opt == 1) 
           Komb.push_back(Unos_k());
    }
    
    Ispis_krugova(Komb);  
    
    if (opt == 2) {
        
        struct Broj brj[Nmax];
        Calc_n (Komb, brj);
        Ispis_n(brj);
        Calc_V (brj, Komb.size());
        Sort_V (brj);
        Ispis_V(brj);
        Gen_L(brj);
        
    }
    else return 0;
    return 0;
}

vector<int> Unos_k() {
    cout << endl << "Unesite kombinaciju: " << endl;
    int t;
    vector<int> tmp;
    for (int i=0; i<7; i++) {
        cin >> t;
        if (t>=1 && t<=49) 
            tmp.push_back(t);
        else i--;
    }
    return tmp;
}

void Calc_n (vector<vector<int>> num, struct Broj b[]) {
    for (int i=0; i<Nmax; i++) {
        b[i].b = i+1;
        b[i].V = 0;
    }
    
    for(int i=0; i<num.size(); i++) 
        for (int j=0; j<Nl; j++) 
            b[num[i][j]-1].V++; 
}

void Calc_V(struct Broj numers[], int s) {
    for (int i=0; i<Nmax; i++) {
        numers[i].V /= (double) s;     // probability calculation
    }
}

void Sort_V(struct Broj numers[]) {
    struct Broj tmp;                        // sorting by probability
    for (int i=0; i<Nmax-1; i++)
        for (int j=i+1; j<Nmax; j++) {
            if (numers[i].V < numers[j].V) {
                tmp = numers[i];
                numers[i] = numers[j];
                numers[j] = tmp;
            }
        }    
}

void Gen_L(struct Broj numers[]) {
    vector<int> krug;
    bool dob = true;
    cout << endl << "Tražim kombinaciju: " << endl;
    do {
        krug= Rnd_num(N, Nmax);
  
        dob = false;
        for (int i=0; i<krug.size(); i++) 
            for (int j=0; j<Nmax; j++) {
                if (numers[j].b == krug[i] && numers[j].V >= numers[0].V) {
                     dob = true;
                    //  if (dob) cout << endl << "Broj najvece vjv!" << endl;
                    break;
                }
            }
    } while(dob && krug.size() != Nmax);    
        
    sort(krug.begin(), krug.end()); 
    
    cout << endl << "Drawn combination: " << endl;
    for (int i=0; i<krug.size(); i++) {
        printf ("%2d ", krug[i]);
    } 
}


void Ispis_krugova(vector<vector<int>> num) {
    cout << "Unijeli ste: " << endl;
    for (int i=0; i<num.size(); i++) {
        for (int j=0; j<Nl; j++) 
           printf("%2d ", num[i][j]);
        cout << endl;
    }
}

void Ispis_n(struct Broj a[]) {
    cout << endl << "Repetitions by numbers: " << endl ;
    for (int i=0; i<Nmax; i++) {
        printf ("\n%2d %1.2lf", a[i].b, a[i].V );
    }
}

void Ispis_V(struct Broj numers[]) {
    cout << endl << "Sorted probability by numbers: " << endl ;
    for (int i=0; i<Nmax; i++) {
        printf ("\n%2d %.4lf", numers[i].b, numers[i].V );
    }
}



vector<int> Rnd_num(int a, int b) {
    //srand(time(NULL));
    vector<int> num;
    int r;
    int i, j;
    bool ima;
    
    for (i=0; i<a; i++) {
        r = (rand()%b)+1;
        ima = false;

        for (j=0; j<i; j++) {
            if (r == num[j]) ima = true;
        }
        
        if (ima == false) 
            num.push_back(r);
        else i--;
    }
    //sleep(1);
    return num;
}
