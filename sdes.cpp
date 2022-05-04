/*
Implementation of Simplified DES algoritm

*/


#include<iostream>

using namespace std;

static string key1="", key2="";		

void IP(string &p)
{
	int temp[] = {2,6,3,1,4,8,5,7};
	string ans = "";
	for(int i = 0; i < 8; ++i)
	{
		ans = ans + p[temp[i]-1];
	}
	p = ans;
}

string expand(string s)
{
	int temp[] = {4,1,2,3,2,3,4,1};
	string ans;
	for(int i = 0; i < 8; ++i)
	{
		ans = ans + s[temp[i]-1];
	}
	return ans;
}

void x(string &ex, const string &k, int end)
{
	for(int i = 0; i < end; ++i)
	{
		if(ex[i]==k[i])		//if both bits are same then make that bit 0
			ex[i] = '0';
			
		else
			ex[i] = '1';
	}
	
}

string matrix(string ex)
{
	int row, col;
	string ans;
	string s0[4][4] = {
					{"01", "00", "11", "10"},
					{"11", "10", "01", "00"},
					{"00", "10", "01", "11"},
					{"11", "01", "11", "10"}
					};
					
	string s1[4][4] = {
					{"00", "01", "10", "11"},
					{"10", "00", "01", "11"},
					{"11", "00", "01", "00"},
					{"10", "01", "00", "11"}
					};
	
	//check first four bits and decide the row
	if(ex[0]=='0' && ex[3]=='0')
		row = 0;
	else if(ex[0]=='0' && ex[3]=='1')
		row = 1;
	else if(ex[0]=='1' && ex[3]=='0')
		row = 2;
	else
		row = 3;
	
	//check column
	if(ex[1]=='0' && ex[2]=='0')
		col = 0;
	else if(ex[1]=='0' && ex[2]=='1')
		col = 1;
	else if(ex[1]=='1' && ex[2]=='0')
		col = 2;
	else
		col = 3;
	
	ans = ans + s0[row][col];
	
	if(ex[4]=='0' && ex[7]=='0')
		row = 0;
	else if(ex[4]=='0' && ex[7]=='1')
		row = 1;
	else if(ex[4]=='1' && ex[7]=='0')
		row = 2;
	else
		row = 3;
	
	if(ex[5]=='0' && ex[6]=='0')
		col = 0;
	else if(ex[5]=='0' && ex[6]=='1')
		col = 1;
	else if(ex[5]=='1' && ex[6]=='0')
		col = 2;
	else
		col = 3;
		
	ans = ans + s1[row][col];
	return ans;
	
}

void p4(string &p)	
{
	int temp[] = {2,4,3,1};
	string ans;
	for(int i = 0; i < 4; ++i)
	{
		ans = ans + p[temp[i]-1];
	}
	p = ans;
}

void IPinv(string &p)
{
	int temp[] = {4,1,3,5,7,2,8,6};
	string ans;
	for(int i = 0; i< 8; ++i)
	{
		ans = ans + p[temp[i]-1];
	}
	p = ans;
}

string encrypt(string &pt, const string &k, int shift)
{
	string p4bit;						//4 bit string
	string ex = expand(pt.substr(4));								
	
	x(ex, k, 8);						//8 bit processing			
		
	p4bit = matrix(ex);			
	p4(p4bit);
	
	x(p4bit, pt.substr(0,4), 4);		//4 bit processing
	
	ex = p4bit + pt.substr(4);
	
	//swap 4 bits if shift is 1
	if(shift==1)
	{
		string temp = ex.substr(0,4);
		ex = ex.substr(4);
		ex = ex + temp;
	}
	else
		IPinv(ex);
		
	//cout << ex << endl;
	return ex;	
}


void p8(string &p, string &key)
{
	//6 3 7 4 8 5 10 9
	int temp[] = {6,3,7,4,8,5,10,9};
	for(int i = 0; i < 8; ++i)
	{
		key = key + p[temp[i]-1]; 
	} 
	
}


void shiftleft(string &p, int shift)
{
	
	string arr = "";
	int x = shift;
	
	//for first 5 bit
	int i;
	for(i = 0; i < (5-shift); ++i)
	{
		arr = arr + p[x];
		++x;
	}
	arr = arr + p[0];
	//cout << arr << endl;
	
	
	if(shift==2)
	{
		arr = arr + p[1];
	}
	
	//for first 5 bits
	x = 5+shift;
	for(i = x; i < 10; ++i)
	{
		arr = arr + p[x];
		++x;
	}
	arr = arr + p[5];
	if(shift==2)
	{
		
		arr = arr + p[6];
	}
	p = arr;
	
}

int main()
{
	string plaintext, key, p10, ciphertext;
	
	int round = 2;
	
	cout << "Enter plaintext(8-bits): ";
	cin >> plaintext;
	
	cout << "Enter the key(10-bits): ";
	cin >> key;
	
	//create p10(10 bit permutattion)
	int temp[] = {3,5,2,7,4,10,1,9,8,6};		//p10 sequence of transformation
	
	for(int i = 0; i < 10; ++i)
	{
		p10 = p10 + key[temp[i]-1];
	}
	
	int shift = 1;
	while(round > 0)
	{
		shiftleft(p10, shift);		//send p10 to leftshift
		if(shift==1)
		{
			p8(p10, key1);		
			IP(plaintext);				
			plaintext = encrypt(plaintext, key1, shift);		
		}
		else
		{
			p8(p10, key2);		//generate the key
			plaintext = encrypt(plaintext, key2, shift);
		}
		
		--round;
		++shift;
	}
	cout << "ciphertext: " << plaintext << endl;
	
}
