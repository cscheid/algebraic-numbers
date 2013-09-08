#include "complex.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "algebraic.h"
#include "SDL/SDL.h"
using namespace std;
char nonconvergent;// int fq[5001];

double frnd()
{
	return ((double)rand())/RAND_MAX;
}
double frnd(double arg)
{
	return frnd()*arg;
}





/** Recursive Newton's method root finding.
 * c is a list of complex numbers, representing the polynomial c[0]+c[1]*z+c[2]*z^2*...c[o]*z^o
 * o is the order of the polynomial c. (so there are o+1 elements of c)
 * pr is a pointer to a vector of roots of the polynomial.
 */
void findroots_inner(Complex *c,const unsigned o,vector<Complex> *pr)
{
        Complex r; //root
      	/*for(int n=0;n<=o;n++)
	{
		cout<<c[n]<<" ";
	}*/	
	//cout<<endl;
	if (o==1)
        {   //base case : the equation c[0]+c[1]*z=0 can be solved easily. 
                r=Complex()-c[0]/c[1];
		pr->push_back(r);
                return;
        }
	 
	
	//Pick a random complex number, then calculate r -> r-f(r)/f'(r). If the difference between the old root and 
	//the new root is small enough, exit. If j reaches a certain number, we pick a new root and start over. If
	//we've picked a bunch of new roots and still haven't converged, then exit (counted by i).
	//f=function = c[0]+c[1]*r+c[2]*r^2+...+c[o]*r^o
	//d=derivative=c[1]+2*c[2]*r+3*c[3]*r^2+...+o*c[o]*r^(o-1)
	//p is the power, multiplied by r each for loop. (1,r,r^2,r^3 etc)
	//ors is the old root.

	Complex f,d,p,ors;
	int i=0,j=500;
        do
        {
		if (j==500) {r=frnd(2)-1+I*(frnd(2)-1); j=0;} else j++;
		if (i>=5000) {nonconvergent=1; break;}
		i++;
                ors=r; f=Complex(0,0); d=Complex(0,0); p=Complex(1,0);
                for (int n=0;n<o;n++,p*=r)
                {
                        f+=p*c[n];
                        d+=p*c[n+1]*(n+1);
                }
		f+=p*c[o];
		/*if(i<15){	
		SDL_Delay(100);
	cout<<r<<" "<<f<<" "<<d<<" "<<(r-f/d)<<endl;}*/
                r-=f/d;
		//cout<<r<<endl;
		if(i==4999)
		cout<<(r-ors).length2()<<endl;
        } while ((r-ors).length2()>1e-4);
	//cout<<(int)nonconvergent<<" A "<<r<<endl;
	cout<<i<<" "<<(int)nonconvergent<<endl;
	//fq[i]++;
        pr->push_back(r); //add the root

	//this method divides the polynomial by the root r through synthetic division
        for (int n=o;n>0;n--) c[n-1]+=r*c[n];
        for (int n=0;n<o;n++) c[n]=c[n+1];
       
       	//we've calculated c=(z-r)*c'. (where c' is the divided polynomial). Now we can call the function again until we have
	//c=(z-r1)(z-r2)...(z-ro).	
	findroots_inner(c,o-1,pr);
}

// c[0] to c[o] are coeffs of 1 to x^o;
vector<Complex> findroots(Complex *c,const unsigned o)
{        
	vector<Complex> r=vector<Complex>();
        findroots_inner(c,o,&r);
        return r;
}


//This method finds all the points to plot.
//The majority of the code is for generating polynomials. You want polynomial 
vector<Point> precalc(const int maxh)
{
	
        vector<Point> ret=vector<Point>(); Point p;
        int h,i,j,k,nz,l,sp;
	//for (i=0;i<=5000;i++) fq[i]=0;
        int temps=0,eqns=0,roots=0;
        for (h=2;h<=maxh;h++) // Complexity measure sum(|c_n|+1)
        {
                p.h=h;
                int *t=new int[h];
                for (i=(1<<(h-1))-1;i>=0;i-=2) // 2 step stops t[k-1] being zero
                {
                        t[0]=0;
                        for (j=h-2,k=0;j>=0;j--)
                                if ((i>>j)&1) t[k]++; else {k++; t[k]=0;}
                        temps++;
                        if (k==0) continue; // k is the order
                        p.o=k;
                        //p.o=t[k];
                        nz=0;
                        for (j=k;j>=0;j--) if (t[j]!=0) nz++;
                        for (j=(1<<(nz-1))-1;j>=0;j--) // Signs loop
                        {
                                Complex *c=new Complex[k+1];
                                for (l=k,sp=1;l>=0;l--)
                                        if (t[l]==0 || l==k) 
						c[l]=Complex(t[l],0);
                                        else {
						c[l]=Complex(j&sp?t[l]:-t[l],0);
					       	sp<<=1;
					}
                                eqns++;
                                nonconvergent=0;
				//Complex *cc=new Complex[k+1]; 
				//memcpy(cc,c,(k+1)*sizeof(Complex));
                                vector<Complex> retroots=findroots(c,k);
                                if (!nonconvergent)
                                	for (l=k-1;l>=0;l--){
                                        	roots++;
                                       	 	p.x=retroots.at(l).x; p.y=retroots.at(l).y;
                                        	ret.push_back(p);
                                	}
                                else
                                	{
						//FILE *out=fopen("nonconv.log","at");
						//for (l=k;l>=0;l--) fprintf(out,"%+lg*z^%d%s",cc[l].re,l,(l?"":"\n"));
						//fclose(out);
                                	}
                                delete[] c;
				//delete[] cc;
                        }
                }
                delete[] t;
        }
        //FILE *out=fopen("stats.txt","at");
        //fprintf(out,"temps=%d eqns=%d roots=%d\n",temps,eqns,roots);
        //fclose(out);
	//out=fopen("histoiters.csv","wt");
	//for (i=0;i<=5000;i++) fprintf(out,"%d,%d\n",i,fq[i]);
	//fclose(out);
        return ret;
}
 


