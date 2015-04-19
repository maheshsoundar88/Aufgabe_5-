// Aufgabe_5.cpp : Defines the entry point for the console application.
//Bitte _CRT_SECURE_NO_WARNINGS hinzufügen unter Projekt->Properties->C/C++->Preprocessor->Preprocessor Definitions

#include "stdafx.h"
#include <iostream>
#include <io.h>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int FileSort(char* file[3]);
bool AscendSort(const char*, const char*);  //ansteigend anordnen
void ToLower(char*); //Kleinbuchstaben 

int _tmain(int argc, _TCHAR* argv[])
{
	char* file[3];
	file[0] = "file1.txt"; //Diese Dateien werden in C:\Users\....\Downloads\.. erstellt
	file[1] = "file2.txt";
	file[2] = "file3.txt";

	int error = FileSort(file);
	if (error == 0)
		printf("Prozess hat mit Fehlern beendet\n");
	else
		printf("SUCCESS\n");

	return 0;
}

int FileSort(char* file[3])
{
	char* userprofile = getenv("USERPROFILE");
	if (!userprofile)
	{
		printf("Keine USERPROFILE environment variable\n");
		return 0;
	}

	char linedata[100];
	char dest_folder[3][100];

	for (int i = 0; i < 2; i++)   //Eingabe Dateien Erstellen
	{	
		strcpy(dest_folder[i], userprofile);
		strcat(dest_folder[i], "\\Downloads\\");
		strcat(dest_folder[i], file[i]);

		ofstream infile;
		infile.open(dest_folder[i], ios::out);
		if (!infile.is_open())
		{
			printf("%s nicht erstellt\n",file[i]);
			return 0;
		}
		char option[10] = "Y";
		printf("%s:\n", file[i]);
		while (strcmp(option, "Y") == 0 || strcmp(option,"y") == 0)
		{
			printf("Geben Sie die Textzeile ein\n");
			scanf("%s", linedata);
			infile << linedata << endl;
			printf("Noch eine Textzeile? Geben Sie Y oder N ein\n");
			scanf("%s", option);
		}
		infile.close();
	}

	//Ausgabe Datei Erstellen
	strcpy(dest_folder[2], userprofile);
	strcat(dest_folder[2], "\\Downloads\\");
	strcat(dest_folder[2], file[2]);
	fstream outfile;
	outfile.open(dest_folder[2], ios::out);
	if (!outfile.is_open())
	{
		printf("%s nicht erstellt\n", file[2]);
		return 0;
	}

	//Mischen - Schreiben die Inhalte den Eingabedateien in der Ausgabedatei
	bool file1_incomplete = true;
	bool file2_incomplete = true;
	vector <char*> lines;
	char line1[100];
	ifstream infile1;
	infile1.open(dest_folder[0],ios::in);
	if (!infile1.is_open())
	{
		printf("%s konnte nicht geöffnet werden\n", file[0]);
		return 0;
	}
	ifstream infile2;
	infile2.open(dest_folder[1], ios::in);
	if (!infile2.is_open())
	{
		printf("%s konnte nicht geöffnet werden\n", file[1]);
		return 0;
	}

	while (file1_incomplete || file2_incomplete)
		{
			if (!infile1.eof())
			{
				infile1.getline(line1, 99);
				if ((strcmp(line1,"")))
				{
					outfile << line1 << endl;
				}
			}
			else
			{
				file1_incomplete = false;
			}

			if (!infile2.eof())
			{
				infile2.getline(line1, 99);
				if ((strcmp(line1, "")))
				{
					outfile << line1 << endl;
				}
			}
			else
			{
				file2_incomplete = false;
			}
		}
	infile1.close();
	infile2.close();
	outfile.close();

	//sortieren durch vectors
	outfile.open(dest_folder[2], ios::in);
	if (!outfile.is_open())
	{
		printf("%s konnte nicht geöffnet werden\n", file[1]);
		return 0;
	}
	while (!outfile.eof())
	{
		outfile.getline(line1, 99);
		if ((line1) && (strcmp(line1, "")))
		{
			char* line = new char[strlen(line1) + 1];
			strcpy(line, line1);
			lines.push_back(line);
		}
	}
	sort(lines.begin(), lines.end(), AscendSort); //sortieren die Textzeilen durch vectors
	outfile.close();

	//Ausgabe Datei schreiben und Vector löschen
	outfile.open(dest_folder[2], ios::out | ios::trunc);
	if (!lines.size())
	{
		printf("Error: Datei nicht gemischt in %s", file[2]);
		return 0;
	}
	for (int i = 0; i < lines.size(); i++)
	{
		outfile << lines[i] << endl;
		delete[] lines[i];
	}
	lines.clear();
	outfile.close();

	return 1;
}

bool AscendSort(const char* string1, const char* string2)
{
	int nLen = 0;
	char firststring[100]; 
	char secondstring[100];
	strcpy(firststring, string1);  //Eine Kopie der Original-String
	strcpy(secondstring, string2); //Eine Kopie der Original-String

	ToLower(firststring);  // Umwandlung Kleinbuchstaben
	ToLower(secondstring); // Umwandlung Kleinbuchstaben

	int len_str1 = strlen(firststring);
	int len_str2 = strlen(secondstring);
	if (len_str1 < len_str2)
		nLen = len_str1;
	else
		nLen = len_str2;

	//vergleichen
	for (int i = 0; i < nLen; i++)  
	{
	if (firststring[i] < secondstring[i])
		return 1;
	else if(firststring[i] == secondstring[i])
		continue;
	else
		return 0;
	}
}

void ToLower(char* lowerstring)
{
	for (int i = 0; i < strlen(lowerstring); i++)
	{
		lowerstring[i] = tolower(lowerstring[i]);
	}
}