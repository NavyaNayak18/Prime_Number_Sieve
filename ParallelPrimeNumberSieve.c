#include <stdlib.h>
#include <math.h>
#define n 100 
#define l 10
#define m 100
boolean Prime[11][101]; 
int i, j, k, num, loc, s, t; 
int stream commchan[11]; 
#define endmarker -1 

void primeProcess(int processID) 
{
  int p = 1; 
  int c; 
  int startInt = (processID-1)*m + 1;  
  int s;
  
  recv(commchan[processID], p); 
  while (p != endmarker) {
   	c = 1;
	s = startInt;
	while (((s % p) != 0) && (c < m)) {
	  s++; c++;
	}
	while (c <= m) {
	  Prime[processID][c] = FALSE;
	  c += p;
	}
    recv(commchan[processID], p); 
  } 
}

main( ) {
  
  for (i = 1; i <= l; i++)
	for (j = 1; j <= m; j++) 
      Prime[i][j] = TRUE; 
  for (i = 2; i <= l; i++)
	  fork primeProcess(i); 
  for (num = 2; num <= sqrt(n); num++)
    if (Prime[1][num]) {
	  for (k = 2; k <= l; k++)
		send(commchan[k], num);
      loc = num + num;
	  while (loc <= m) {
  	    Prime[1][loc] = False;
	    loc = loc + num;
      } 
	} 
  for (i = 2; i <= l; i++) send(commchan[i], endmarker); 
  for (i = 2; i <= l; i++) join; 
  cout << "Prime numbers: " << endl;
  for (i = 2; i <= 100; i++) { 
	s = ((i-1) / m) + 1;
	t = ((i-1) % m) + 1;  
    if (Prime[s][t]) cout << i << " " << endl; 
  } 
}