#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <math.h>
using namespace std;

ifstream f("test.in");
ofstream g("test.out");
long long tmp[100000001];
bool verifsort (long long A[], int Lungime)
{
    for (int i=1; i<Lungime; i++)
        if ( A[i] > A[i+1] )
            return 0;
    return 1;
}

void cpy (long long Arr[], long long C[],int Lungime)
{
    for (int i=1; i<=Lungime; i++)
        C[i]=Arr[i];
}
void BubbleSort (long long Array[], int dimensiune)
{
    for (int i=1; i <= dimensiune; i++)
        for (int j=1; j <= dimensiune; j++)
            if (Array[j] > Array[j+1])
                swap (Array[j],Array[j+1]);
}

void CountSort (long long Array[],int Lungime)
{
    int ValMax = 0;
    int cont = 0;
    for (int i=1; i <= Lungime; i++)
        if (Array[i] > ValMax)
            ValMax = Array[i];
    int Fr[ ValMax ];
    for (int i=0; i <= ValMax; i++)
        Fr[ i ] = 0;
    for(int i=1; i <= Lungime; i++)
        Fr[ Array[i] ] ++;
    for (int i=0; i <= ValMax; i++)
        for (int j=1; j <= Fr[i]; j++)
            Array[ ++cont ] = i;

}


void MergeSort1(long long A[], int st, int dr)
{
    if(st < dr)
    {
        int m = (st + dr) / 2;
        MergeSort1 (A, st, m);
        MergeSort1 (A, m + 1, dr);
        int i = st;
        int j = m + 1;
        int k = 0;
        while (i <= m && j <= dr)
            if( A[i] < A[j])
                tmp[++k] = A[i++];
            else
                tmp[++k] = A[j++];
        while (i <= m)
            tmp[++k] = A[i++];
        while (j <= dr)
            tmp[++k] = A[j++];
        for (i = st ; i <= dr ; i ++)
            A[i] = tmp[++j];
    }
}

void QuickSort(long long v[], int st, int dr)
{
	if(st < dr)
	{
		int m = (st + dr) / 2;
		swap (v[st],v[m]);
		int i = st , j = dr, d = 0;
		while(i < j)
		{
			if(v[i] > v[j])
			{
				swap(v[i],v[j]);
				d = 1 - d;
			}
			i += d;
			j -= 1 - d;
		}
		QuickSort(v, st , i - 1);
		QuickSort(v, i + 1 , dr);
	}
}
void RadixSort(long long A[],int Lungime)
{

    vector <long long> Bucket[256];
    int Max=0;
    int Nrcif=0;
    int shift =0;
    for (int i=1; i<=Lungime; i++)
    {
        if (A[i] > Max)
            Max = A[i];
    }
    while (Max!=0)
    {
        Nrcif++;
        Max = Max/256;
    }
    for (int cnt=1 ; cnt <= Nrcif; cnt++)
    {
        for (int i=1; i<= Lungime; i++)
            Bucket [ (A[i]>>shift)&255 ].push_back(A[i]);
        Lungime = 0;
        for (int i=0 ; i <= 255; i++)
        {
            for (size_t j=0; j<Bucket[i].size(); j++)
                A[++Lungime] = Bucket[i][j];
            Bucket[i].clear();
        }
        shift+= 8;
    }
}
long long nrneg (long long A[],int Lungime)
{
    for (int i=1; i<=Lungime; i++)
        if (A[i]<0)
            return 0;
    return 1;
}
long NrTeste, Lungime, Maxim;
long long  C[10000005];
long long A[10000005];
int main()
{
    f >> NrTeste;
    int OK=0;
    clock_t timp;
    for (int cnt=1; cnt<=NrTeste; cnt++)
    {
        f >> Lungime;
        f >> Maxim;
        for (int i = 1; i <= Lungime; i++)
            A [i] = rand() % Maxim + 1;
        g << "Testul numarul " << cnt << " are o lungime de " << Lungime << " numere mai mici sau egale decat " << Maxim << endl;

        if (Lungime < 100001)
        {
            cpy (A, C, Lungime);
            timp = clock();
            BubbleSort (C, Lungime);
            timp = clock() - timp;
            OK = verifsort (C,Lungime);
            if (OK==1)
                g << "BubbleSort a sortat corect numerele in " <<((float)timp)/CLOCKS_PER_SEC << endl;
            else
                g << "BubbleSort nu a sortat corect numerele." << endl;
        }
        else
            g << "BubbleSort nu poate sa fie aplicata pentru ca sunt generate prea multe numere." << endl;


        if (Maxim <= 10000001)
        {
            cpy (A, C, Lungime);
            timp = clock();
            CountSort (C, Lungime);
            timp = clock() - timp;
            OK = verifsort (C,Lungime);
            if (OK==1)
                g << "CountSort a sortat corect numerele in " << ((float)timp)/CLOCKS_PER_SEC  << endl;
            else
                g << "CountSort nu a sortat corect numerele" << endl;
        }
        else if (nrneg (A,Lungime)==0)
            g << "CountSort nu poate sa fie aplicata pentru ca sunt citite numere negative" << endl;
        else
            g << "CountSort nu poate sa fie aplicata pentru ca valoarea maxima este prea mare" << endl;

        cpy (A, C, Lungime);
        timp = clock();
        sort (C+1, C+Lungime+1);
        timp = clock() - timp;
        OK = verifsort (C, Lungime);
        if (OK==1)
            g << "Sortarea STL dureaza " << ((double)timp)/CLOCKS_PER_SEC << endl;
        else
            g << "Sortarea STL nu a sortat corect." << endl;


        cpy (A, C, Lungime);
        timp = clock();
        QuickSort (C, 1, Lungime);
        timp = clock() - timp;
        OK = verifsort (C,Lungime);
        if (OK==1)
            g << "QuickSort a sortat corect numerele in " << ((double)timp)/CLOCKS_PER_SEC << endl;
        else
            g << "QuickSort nu a sortat corect numerele." << endl;


        cpy (A, C, Lungime);
        timp = clock();
        MergeSort1 (C, 1, Lungime);
        timp = clock() - timp;
        OK = verifsort (C,Lungime);
        if (OK==1)
            g << "MergeSort a sortat corect numerele in " << ((double)timp)/CLOCKS_PER_SEC << endl;
        else
            g << "MergeSort nu a sortat corect numerele." << endl;


        cpy (A, C, Lungime);
        timp = clock();
        RadixSort (C,  Lungime);
        timp = clock() - timp;
        OK = verifsort (C,Lungime);
        if (OK==1)
            g << "RadixSort a sortat corect numerele in " << ((double)timp)/CLOCKS_PER_SEC << endl;
        else
            g << "RadixSort nu a sortat corect numerele." << endl;

        g << endl;
    }
    return 0;
}
