

#include <iostream>
#include "Python.h"
#include<fstream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;



bool sortcol(const vector<long long int>& v1, const vector<long long int>& v2) {
	return v1[0] > v2[0];
}

long long int getPolinomialRollHash(
	string const& str)
{
	int p = 31;
	int m = 1e9 + 9;
	long long int power_of_p = 1;
	long long int hash_val = 0;

	for (int i = 0; i < str.length(); i++) {
		hash_val = (hash_val + (str[i] - 'a' + 1) * power_of_p) % m;
		power_of_p = (power_of_p * p) % m;
	}

	return hash_val;
}


vector<string> getsuggestion(string &movie,string &final) {


	ofstream Mefile("myfile.txt");
	Mefile << movie;
	Mefile.close();

	Py_Initialize();

	
	PyRun_SimpleString("exec(open('read.py').read())");

	string myText;

	
	ifstream MyReadFile("myfile1.txt");

	
	while (getline(MyReadFile, myText)) {

		final += myText;
		final += " ";
	}

	
	MyReadFile.close();


	ofstream ffile("finalfile.txt");
	ffile << final;
	ffile.close();

	PyRun_SimpleString("exec(open('cosinepython.py').read())");


	string output;
	vector<string> result;
	
	ifstream MyoutputFile("output.txt");

	
	cout << endl;
	cout << "Suggestion based on previous searches : " << endl << endl;
	while (getline(MyoutputFile, output)) {
	
	
		result.push_back(output);
	}


	MyoutputFile.close();

	return result;
}


int main()
{
	vector<vector<long long int>> arr(12037, vector<long long int>(3));
	vector<string> arrstr(12037);
	for (int j = 0; j < 12037; j++) {
		arrstr.push_back("*");
	}
	vector<vector<long long int>> arrsort(12037, vector<long long int>(3));

	for (int p = 0; p < 12037; p++)
		for (int f = 0; f < 3; f++)
			arrsort[p][f] = arr[p][f];

	map <string, int> check;
	ifstream Myhastable("Hash.txt");

	int counter = 0;
	string word;
	int r = 0;
	while (!Myhastable.eof()) {
		
		
		if (Myhastable >> word) {
			if (r == 3) {
				r = 0;
				counter++;
			}
			arr[counter][r] = stoi(word);
			r++;
			
		}
		
		
	}
	Myhastable.close();
	
	ifstream Mymovies("movieshash.txt");

	int counter1 = 0;
	string word1;

	while (getline(Mymovies,word1)) {

			arrstr[counter1] = word1;
	
			counter1++;
		
	}

	Mymovies.close();
	


	string final = "";
	int i = 0;
	while (1) {
		if (i == 0) {
			string movie;
			int rating;
			vector<string> out;
			
			cout << "Enter a movie you like to watch : ";
			getline(cin, movie);
			
			cout << "Enter rating : ";
			cin >> rating;
			out = getsuggestion(movie, final);
			
			

			string correctmovie;
			string cmovie;
			ifstream Mytitle("title.txt");
			while (getline(Mytitle, cmovie))
			{
				correctmovie = cmovie;
			}
			check[correctmovie] = 1;
			long long int key = abs( getPolinomialRollHash(correctmovie));
			
			long long int uniquekey = key;


			
			key %= 12037;
			
				int counter = 0;
				while (arr[key][0] != 0 && counter < 12037 && arr[key][1] != uniquekey)
				{
					key = (key + counter + 12037) % 12037;
					counter++;
				}
			

			arr[key][0] = arr[key][0] + rating;
			arr[key][1] = uniquekey;
			arr[key][2] = key;
			arrstr[key] = correctmovie;

			ofstream Myhash("Hash.txt");
			for (int h = 0; h < 12037; h++) {
				Myhash << arr[h][0] << " "<<arr[h][1]<<" "<<arr[h][2] << endl;
			}

			for (int p = 0; p < 12037; p++)
				for (int f = 0; f < 3; f++)
					arrsort[p][f] = arr[p][f];


			Myhash.close();
			ofstream Mymoviehash("movieshash.txt");
			for (int h = 0; h < 12037; h++) {
				Mymoviehash << arrstr[h] <<endl;
			}

			Mymoviehash.close();

			for (auto& it : out)
				cout << it << endl;
		}
		cout << endl;
		cout << "If want to search another movie and improve recommendation list (TYPE 'y')";
		cout << endl;
		cout << "If want to refresh the recommendation list (TYPE 'r')";
		cout << endl;
		cout << "Exit (TYPE 'x')";
		cout << endl;
		cout << "Trending list (TYPE 't')";
		cout << endl;
		cout << "Enter choice : ";
		string in;
		
		cin >> in;
		
		string movie;
		int rating;
		vector<string> out;
		if (in == "y") {
			cout << endl;

			cin.ignore();
			cout << "Enter a movie you like to watch : ";
			getline(cin, movie);
			
			cout << "Enter rating : ";
			cin >> rating;
			
			out = getsuggestion(movie, final);

			string correctmovie;
			string cmovie;
			ifstream Mytitle("title.txt");
			while (getline(Mytitle, cmovie))
			{
				correctmovie = cmovie;
			}
			if (check[correctmovie] == 1) {
				cout << "MOVIE ALREADY RATED IN THIS SESSION" << endl;

			}
			else {
				check[correctmovie] = 1;
				long long int key = abs(getPolinomialRollHash(correctmovie));
				long long int uniquekey = key;

				key %= 12037;

				int counter = 0;
				while (arr[key][0] != 0 && counter < 12037 && arr[key][1] != uniquekey)
				{
					key = (key + counter + 12037) % 12037;
					counter++;
				}


				arr[key][0] = arr[key][0] + rating;
				arr[key][1] = uniquekey;
				arr[key][2] = key;
				arrstr[key] = correctmovie;

				ofstream Myhash("Hash.txt");
				for (int h = 0; h < 12037; h++) {
					Myhash << arr[h][0] << " " << arr[h][1] <<" "<<arr[h][2]<< endl;
				}

				Myhash.close();

				for (int p = 0; p < 12037; p++)
					for (int f = 0; f < 3; f++)
						arrsort[p][f] = arr[p][f];


				ofstream Mymoviehash("movieshash.txt");
				for (int h = 0; h < 12037; h++) {
					Mymoviehash << arrstr[h] << endl;
				}

				Mymoviehash.close();



				for (auto& it : out)
					cout << it << endl;
			}
		}
		else if (in == "r") {
			final = "";
			cout << "REFRESHED" << endl;
		}
		else if (in == "t") {
			cout << endl;
			cout << "TRENDING LIST : " << endl;
			sort(arrsort.begin(), arrsort.end(), sortcol);
			int k = 0;
			while(arrsort[k][0]){
				cout << arrstr[arrsort[k][2]] <<" "<<"      |||      Total Score(Till Date) : "<< arrsort[k][0]<< endl;
				if (k == 10)
					break;
				k++;

			}

		}

		else if (in == "x") {
			exit(0);
		}

		else
			cout << "INVALID INPUT" << endl;
		i++;
	}

}



