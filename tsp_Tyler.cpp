#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <math.h>
#include <bits/stdc++.h>

using namespace std;
struct city
{
	int index;
	int x;
	int y;
	int dis;//the distance from the current city to the next city.
};
int city_distance(struct city a, struct city b)
{

	int p = pow((a.x-b.x), 2);
	int q = pow((a.y-b.y), 2);	
	//	cout << a.x << ", " << a.y << endl;
	//	cout << (a.y-b.y) << ", " << q << endl;
	double r = sqrt(p+q);
	//	cout << r << endl;
	int k = round(r);
	return k;
}

struct city nearest_neighbour(int i, int num,  struct city *tour)
{
	//	printf("%d, %d, %d\n", tour[i].index, tour[i].x, tour[i].y);
	struct city temp;
	int size = num;
	int mindis = 9999999;
	int index;
	if (i == 0)
	{
		return tour[0];
	}
	else if (i == size -1)
	{
		return tour[i];
	}
	else
	{
		for(int j = i; j < size; j++)
		{
			//cout <<"distance is " <<  city_distance(tour[i-1], tour[j]) << endl;
			//	cout <<  "current index is " << tour[j].x << ", " << tour[j].y << endl;
			//	mindis = city_distance(tour[i-1], tour[j]);
			if (mindis >= city_distance(tour[i-1], tour[j]))
			{
				mindis = city_distance(tour[i-1], tour[j]);
				index = j;
			}
		}
		//	cout << "index is " << index <<"current index is " << i<< endl;
		//cout << tour[i].x << "return" << tour[i].y << endl; 
		temp = tour[i];	
		tour[i] = tour[index];
		tour[index] = temp;
		//	cout << "a is "<< tour[i].index << ", " << tour[i].x<<", "  << tour[i].y << endl;
		//	cout << "b is " << tour[index].index << "," << tour[index].x <<", " << tour[index].y << endl;	 	
		return tour[i];
	}

}

int tour_distance(struct city* tour, int num)
{
	int sum = 0;
	for (int i=0; i < num - 1; i++)
	{
		sum = sum + city_distance(tour[i], tour[i+1]);
	}
	return (sum + city_distance(tour[num-1], tour[0]));
}

void Swap(int i, int j, struct city* tour, struct city* tour_new, int num)
{
	struct city temp;
	if((i == 0)&&(j == 1))
	{
		for(int w=2; w < num; w++)
			tour_new[w] = tour[w];
		tour_new[0] = tour[1];
		tour_new[1] = tour[0];
	}
	else if((i==num-2)&&(j==num-1))
	{
		for(int w=0; w < num-2; w++)
			tour_new[w] = tour[w];
		tour_new[num-2] = tour[num-1];
		tour_new[num-1] = tour[num-2];
	}
	else if((i == j-1)&&(i!=0)&&(j!=num-1))
	{
		for(int w=0; w<i; w++)
			tour_new[w] = tour[w];
		tour_new[i] = tour[j];
		tour_new[j] = tour[i];
		for(int w=j+1; w<num; w++)
			tour_new[w] = tour[w];
	}
	else{
		for (int w = 0; w <= i-1; w++)
		{
			tour_new[w] = tour[w];
		}

		for (int w = i; w < j+1; w++)
		{
			tour_new[w] = tour[j+i-w];
		}
		for (int w = j+1; w < num; w++)
		{
			tour_new[w] = tour[w];
		}
	}
}
/*
   struct city* algorithm_2_opt(struct city *tour, int num)
   {
   int improve = 0;
   struct city *tour_new = (struct city*) malloc(num * sizeof(struct city));
   while (improve < 20)
   {
   int best_distance = tour_distance(tour, num);
   for (int i = 0; i < num-1; i++)
   {	
   for (int j=i+1; j < num; j++)
   {
   Swap(i, j, tour, tour_new, num);		
   int new_distance = tour_distance(tour_new, num);
   if(new_distance < best_distance)
   {
   tour = tour_new;
   best_distance = new_distance;
   }
   }
   improve++;
   }
   }
   for (int i = 0; i < num; i++)
   {
   printf("%d, %d, %d\n", tour_new[i].index, tour_new[i].x, tour_new[i].y);
   }

   return tour_new;
   }
   */
//struct city *tour_new = (struct city*) malloc(num * sizeof(struct city));
//Swap(i, j, tour, tour_new, num);
//struct city* algorithm_2_opt

struct city* algorithm_2_opt(struct city* tour_nn, int num)
{
	/*	struct city *tour_1 = (struct city*) malloc(num * sizeof(struct city));
		Swap(2,4, tour_nn, tour_1, num);
		for (int i = 0; i < num; i++)
		{
		printf("%d, %d, %d\n", tour_1[i].index, tour_1[i].x, tour_1[i].y);
		} 
		*/
	struct city *tour_1 = (struct city*) malloc(num * sizeof(struct city));
	int new_distance;
	int best_distance = tour_distance(tour_nn, num);
//	cout << tour_distance(tour_nn, num) << endl;
	int improve = 0;
//	while(improve < 10)
//	{
		for (int i = 0; i < num-1; i++)
		{
			for (int j = i+1; j < num; j++)
			{
				Swap(i,j, tour_nn, tour_1, num);
		/*		printf("i = %d, j = %d\n", i, j);
				for (int i = 0; i < num; i++)
				{
					printf("%d, %d, %d\n", tour_1[i].index, tour_1[i].x, tour_1[i].y);
				}
				printf("sum is %d\n, ", tour_distance(tour_1,num));
				printf("\n");
		*/		new_distance = tour_distance(tour_1, num);
				if (new_distance < best_distance)
				{
			//		cout <<"new_distance is "<< new_distance << endl;
	//				improve = 0;
					best_distance = new_distance;
					for (int k=0; k<num; k++)
					{
						tour_nn[k] = tour_1[k];
					}
				}
			}
		}
//		improve++;
//	}
/*
	for (int i = 0; i < num; i++)
	{
		printf("%d, %d, %d\n", tour_nn[i].index, tour_nn[i].x, tour_nn[i].y);
	}
	printf("sum is %d\n, ", best_distance);
	printf("\n");
*/
	return tour_nn;
}

int get_city_info_and_outputfile(const char *fileinput, const char *fileoutput)
{
	int num = 0;
	int i = 0;
	int ch;
	int buffer;
	char str[200];

	//get the total number of cities
	FILE * pFile_1;
	pFile_1 = fopen(fileinput, "r");	
	while (EOF != (ch=getc(pFile_1)))
	{
		if ('\n' == ch)
			++num;
	}
	fclose(pFile_1);

	//begin to collect the data.
	FILE * pFile;
	pFile = fopen(fileinput, "r");
	struct city *tour = (struct city*) malloc(num * sizeof(struct city));

	while(fgets(str, 200, pFile))
	{
		char *pch;
		pch = strtok(str," ");
		int k = 0;
		while (pch != NULL)
		{
			buffer = atoi(pch);
			pch = strtok(NULL, " ");

			if (k == 0)
			{
				tour[i].index = i;
			}
			else if (k == 1)
			{
				tour[i].x = buffer;
			}
			else
			{
				tour[i].y = buffer;
			}
			k++;
		}
		tour[i].dis = 11;
		i++;
	}
	fclose(pFile_1);
	/*
	   for(int j=0; j<num; j++)
	   {
	   printf("%d, %d, %d\n", tour[j].index, tour[j].x, tour[j].y);
	   }	*/
	struct city *tour_nn = (struct city*) malloc(num * sizeof(struct city));
	struct city *tour_new = (struct city*) malloc(num * sizeof(struct city));
	printf("The list of cities: \n");
	for (int j = 0; j < num; j++)
	{
		printf("%d, %d, %d\n", tour[j].index, tour[j].x, tour[j].y);
	}
	printf("\n");
	for (int i = 0; i < num; i++)
	{
		tour_nn[i] = nearest_neighbour(i, num, tour);
	}
	/*	for (int i = 0; i < num; i++)
		{
		printf("%d, %f, %f\n", tour[i].index, tour[i].x, tour_nn[i].y);
		}
		*/
	printf("The nearest neighbour tour: \n");
	for (int i = 0; i < num; i++)
	{
		printf("%d, %d, %d\n", tour_nn[i].index, tour_nn[i].x, tour_nn[i].y);
	}
	printf("\n");
	tour_new = algorithm_2_opt(tour_nn, num);
		for (int i = 0; i < num; i++)
		{
		printf("%d, %d, %d\n", tour_new[i].index, tour_new[i].x, tour_new[i].y);
		}
		printf("\n");
			
	int total_distance = tour_distance(tour_new, num);
	
	   FILE * ofile;
	   ofile = fopen(fileoutput, "w");

	   
	   fprintf(ofile, "Total Distance: %d \n", total_distance);
	   //fprintf(ofile, "\n");

	   printf("Total Distance: %d\n", total_distance);

	   for (int i=0; i<num; i++)
	   {
	   fprintf(ofile, "City %i: %d\n", i+1,tour_new[i].index);
	   }
	   for (int i=0; i<num; i++)
	   {
	   printf("City %i: %d\n", i+1, tour_new[i].index);
	   }
	   fclose(ofile);
	   printf("\n");
	  
	//	int sum = 0;
	/*	for (int i=0; i < num; i++)
		{
		if (i == num - 1)
		{
		sum = sum + city_distance(tour_new[i], tour_new[0]);
		}
		else
		{
		cout << city_distance(tour_new[i], tour_new[i+1]) << endl;	
		sum = sum + city_distance(tour_new[i], tour_new[i+1]);
		printf("sum is %d\n", sum);
		}
		}
		printf("%d\n", sum);
		*/
	/*
	   for (int i=0; i < num - 1; i++)
	   {
	   sum = sum + city_distance(tour[i], tour[i+1]);
	   }
	   printf("%d\n",(sum + city_distance(tour[num-1], tour[0])));
	   */
//	printf("\n");
	/*
	   struct city *tour_1 = (struct city*) malloc(num * sizeof(struct city));
	   Swap(0,4, tour_nn, tour_1, num);
	   for (int i = 0; i < num; i++)
	   {
	   printf("%d, %d, %d\n", tour_1[i].index, tour_1[i].x, tour_1[i].y);
	   }
	   printf("\n");
	   */
}

int main(int argc, char *argv[])
{
	string filename(argv[1]);
	string fileoutput(argv[1]);
	fileoutput.erase(fileoutput.end()-4,fileoutput.end());
	const char * c = filename.c_str();
	const char * d = fileoutput.c_str();
	char e[100];
	strcpy(e,d);
	strcat (e, ".txt.tour");
	get_city_info_and_outputfile(c, e);
	return 0;
}
