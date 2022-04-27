/*
Georgia Vachon Westerlund
Sitansh Mehta 
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_SPACES = 50;
const int MAX_CHANGE = 25;

int read (ifstream &fin, bool c_professor[], string c_name[]);
int readDataToArrays (ifstream&fin, bool r_professor[], string r_name[]);
void removeCurrent (string c_name[], bool c_professor[], string nameFind);
int checkSpotAvailability (string c_name[], bool c_professor[], 
						   bool profStatus);
bool assignSpot (string c_name[], bool c_professor[], string assignName, 
				 bool assignStatus);
void moveFacultyStaff (string c_name[], bool c_professor[], bool a_professor[]);
void outputToFile (ofstream & fout, string c_name[], bool c_professor[]);

int main() 
{
	ifstream finC("parking_current.txt");
	ifstream finR("parking_remove.txt");
	ifstream finA("parking_add.txt");
	ofstream fout("parking_update.txt");

    if (!finC || !finR || !finA)
    {
        cout << "File not Opened." << endl;
        return EXIT_FAILURE;
    }

	bool c_professor [MAX_SPACES] = {false};
	string c_name [MAX_SPACES];
	
    bool a_professor [MAX_CHANGE] = {false};
    string a_name [MAX_CHANGE]; 

    bool r_professor [MAX_CHANGE] = {false};
    string r_name [MAX_CHANGE];

	int numCurrent = read (finC, c_professor, c_name); 
    int numRemove = readDataToArrays (finR, r_professor, r_name);
	int numAdd = readDataToArrays (finA, a_professor, a_name);
		
	for (int removeCount = 0; removeCount < numRemove; removeCount++)
  	{
  		string nameFind = r_name[removeCount];
  		removeCurrent (c_name, c_professor, nameFind);
  	}
	
	moveFacultyStaff (c_name, c_professor, a_professor);

	for (int addCount = 0; addCount < numAdd; addCount++)
	{
		assignSpot (c_name, c_professor, a_name[addCount], 
					a_professor[addCount]);
	}
	
	outputToFile (fout, c_name, c_professor);
	
	finC.close();
    finR.close();
    finA.close();
	fout.close();
	
	return EXIT_SUCCESS;
}



// Function (b)
int read (ifstream&fin, bool c_professor[], string c_name[])
{	
    int numReads = 0;
    
	bool prof = false;
    string name = "";
   	int space = 0;
    
    while (numReads < MAX_SPACES && fin >> prof >> name >> space)
	{
        int index = space - 1;
        
        c_professor[index] = prof;
        c_name[index] = name;
		        
        numReads++;
	}
		
	return numReads;
}


// Function (c)
int readDataToArrays (ifstream&fin, bool r_professor[], string r_name[])
{
	int numReadsAR = 0;
    
    bool profAR = false;
   	string nameAR = "";
    int spaceAR = 0;
    
	while (numReadsAR < MAX_CHANGE && fin >> profAR >> nameAR)
	{	
		r_professor[numReadsAR] = profAR;
        r_name[numReadsAR] = nameAR;
        
        numReadsAR++;
	}
	
	return numReadsAR;
}


// Function (d)
void removeCurrent (string c_name[], bool c_professor[], string findName)
{  	
  	for (int currentCount = 0; currentCount <= MAX_SPACES; currentCount++)
  	{
  		 if (findName == c_name[currentCount])
    	{			
			c_name[currentCount] = "";
			c_professor[currentCount] = 0;
    	}
	}
}


// Function (e)
int checkSpotAvailability (string c_name[], bool c_professor[], bool profStatus)
{
	int lowestAvailable = -1;
	int spotsFull = 0;
	int lotFull = 0;
	
	for (int availIndex = 0; availIndex < MAX_SPACES && lowestAvailable == -1; 
		 availIndex++)
	{
		if (c_name[availIndex] == "")
		{
			if (profStatus == true && availIndex <= 24)
			{
				lowestAvailable = availIndex;
			}
			else if(profStatus == false && availIndex > 24)
			{
				lowestAvailable = availIndex;
			}	
		}
	}
	
	return lowestAvailable;
}


// Function (f)
bool assignSpot (string c_name[], bool c_professor[], string assignName, 
				 bool assignStatus)
{
	int lotSpace = checkSpotAvailability (c_name, c_professor, assignStatus);
	
	if (lotSpace==-1)
	{
		cout << assignName << " could not be assigned a parking spot." << endl;
		
		return false;
	}
	else
	{
		c_name[lotSpace] = assignName;
		c_professor[lotSpace] = assignStatus;
			
		return true;
	}
}


// Function (g)
void moveFacultyStaff (string c_name[], bool c_professor[], bool a_professor[])
{
	for (int moveCount = 25; moveCount < MAX_SPACES; moveCount++)
	{	
		if (c_professor[moveCount] == true)
		{			
			string tempName = c_name[moveCount];
			bool tempStatus = c_professor[moveCount];
			removeCurrent (c_name, c_professor, c_name[moveCount]);	
			assignSpot (c_name, c_professor, tempName, tempStatus);
		}
	}
}


// Function (h)
void outputToFile (ofstream & fout, string c_name[], bool c_professor[])
{
	for (int outputCount = 0; outputCount < MAX_SPACES; outputCount++)
	{
		if (c_name[outputCount] != "")
		{
			fout << c_professor[outputCount] << " " << c_name[outputCount] 
				 << " " << outputCount + 1 << endl;
		}
	}
}


/*
Console output:

Swayer_Tim could not be assigned a parking spot.
Sheng_Gloria could not be assigned a parking spot.


File output:

1 Bishop_Bill 1
1 Nairn_David 2
1 Meunier_Sarah 3
1 Dunbar_Fiona 4
1 Lau_David 5
1 Owen_Bill 6
1 Lokker_Shirley 7
1 Saad_John 8
1 Trelford_Ryan 9
0 Kim_Chuck 10
1 Davison_Dan 11
1 Kennings_Andrew 12
1 Hasan_Anwar 13
1 Brown_Natalie 14
0 Patel_Muhammad 15
1 Chandrashekar_Naveen 16
1 Stachowsky_Michael 17
1 Babaee_Reza 18
1 Harder_Douglas 20
1 Consell_Ryan 21
1 Mansour_Firas 23
1 Cramer_Zachary 24
1 Hamilton_Jordan 25
0 Yeum_Alla 26
0 English_Lisa 27
0 Windsor_Harry 28
0 Nassar_Ahmed 29
0 Lacroix_Cheryl 30
0 Hitchinson_Joan 31
0 Reed_Jim 32
0 Martins_Joshua 33
0 Tung_Clive 34
0 Ladouceur_Yvonne 35
0 Oh_Henry 36
0 Mansour_Ali 37
0 Lim_Lilian 38
0 Zurell_Katie 39
0 Zhang_Yung-Yee 40
0 Wiens_Rosa 41
0 Chen_Ben 42
0 El-Hag_William 43
0 Mayer_Adam 44
0 Parks_Flora 45
0 Unger_Charles 46
0 Zalewski_Mary 47
0 Allen_Adrian 48
0 ElShaSha_Ahmed 49
0 Reddock_Julia 50
*/
