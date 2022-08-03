#include <iostream>
#include <fstream>
#include <cfloat>
#include <cmath>


using namespace std;


int main() {

int N = 300, i, j, time, tmax, timestep; //,seed = 99999999;
double pi, length, lx, ly, v0, vx, vy, eta, rcut;
double dx, dy, r, arg, avgtheta, noise, sumx, sumy, avgvel;
double x[N], y[N], theta[N], num[N], den[N];


// inputs:
length = 7.0; lx = length/2.0, ly = lx, v0 = 0.03, eta = 0.0;
rcut = 1.0, tmax = 100, timestep = 1;

pi = 4.0*atan(1.0);


ofstream yazmaDosyasi;
yazmaDosyasi.open("vicsek1.dat");


// initial configuration:
for (int i = 1; i <= N; i++) 
{
	x[i] = 2.0 * ((double)rand() / (double)RAND_MAX - 0.5)*lx;
	y[i] = 2.0 * ((double)rand() / (double)RAND_MAX - 0.5)*ly;
    theta[i] = 2.0*((double)rand() / (double)RAND_MAX)*pi;
    vx = v0*cos(theta[i]);
    vy = v0*sin(theta[i]);
    
//    cout << x[i]<<"  "<<y[i]<<"  "<<theta[i]<<"  "<<vx<<"  "<<vy;
//    cout << endl;
//    cout << pow(vx*vx + vy*vy, 0.5);
//    cout << endl;
}




// time iteration:
avgvel = 0.0;
for (time = 1; time<=tmax; time++)
    {
	  sumx = 0.0, sumy = 0.0;
	  
	  for (i = 1; i<=N; i++)
	     {
			 num[i] = sin(theta[i]);
			 den[i] = cos(theta[i]);
			 
			 for (j=1; j<=N; j++)
			    {
					dx = (x[i]-x[j])-round((x[i]-x[j])/(2.0*lx))*2.0*lx;
					dy = (y[i]-y[j])-round((y[i]-y[j])/(2.0*ly))*2.0*ly;
					r = pow(dx*dx + dy*dy, 0.5);
					    if (r <= rcut)
					       {
							   num[i]=num[i]+sin(theta[j]);
							   den[i]=den[i]+cos(theta[j]);
							}
							
				}  // j loop ends here.
				
				arg = abs( num[i]/den[i] );
				
				    if (num[i]>=0.0 && den[i]>=0.0)
				       {
						   avgtheta = atan(arg);
						}
				    else if (num[i]>=0.0 && den[i]<=0.0)
				       {
						   avgtheta = pi - atan(arg);
						}
					else if (num[i]<=0.0 && den[i]<=0.0)
				       {
						   avgtheta = pi + atan(arg);
						}
					else if (num[i]<=0.0 && den[i]>=0.0)
				       {
						   avgtheta = 2.0*pi - atan(arg);
						}
						
			noise = eta*( ( (double)rand() / (double)RAND_MAX) - 0.5 );		
			theta[i] = avgtheta + noise;
			vx = v0*cos(theta[i]); 	
			vy = v0*sin(theta[i]);
			x[i] = x[i] + vx*timestep;  
			y[i] = y[i] + vy*timestep;
			
			// periodic boundry conditions apply:
			x[i] = x[i] - 2.0*( int(x[i]/lx) )*lx;
			y[i] = y[i] - 2.0*( int(y[i]/ly) )*ly;
			
		 }	// i loop ends here.
		
		 for (i=1; i<=N; i++)
		    {
				sumx = sumx + v0*cos(theta[i]);
				sumy = sumy + v0*sin(theta[i]);
				vx = v0*cos(theta[i]);
				vy = v0*sin(theta[i]);
				
yazmaDosyasi<<x[i]<<" "<<y[i]<<" "<<theta[i]<<" "<<2.0*vx<<" "<<2.0*vy;
yazmaDosyasi << endl;	 
			 } // 
			 
		 avgvel = avgvel + pow(sumx*sumx + sumy*sumy,0.5)/(v0*N);
		 
		
    }   // time loop ends here.

        avgvel = avgvel / tmax;
        cout << "average normalised velocity = " << avgvel;

yazmaDosyasi.close();

return 0;

}
