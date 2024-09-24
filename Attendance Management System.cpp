// Admin Login :: username == user , password == pass
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <windows.h>
#include <cstring>
#include <iomanip>
using namespace std;

void menu();
void student();
void admin();
void showattandance(string eno);
void markattandance();
void adminmenu();
void newstudent();
void studentsdata();
void attandanceofstudent(); 
void removestudent();
void save();
void load();

struct student{
	string name;
	string fname;	
	string address;
	string enrollment;
	string pass;
};

struct student s[100];
int SD=0;

string attandance[100][6];
int att=0;

void student(){
	p:
	system("cls");
	cout<<"                             Student Attandance Management System        \n\n";
	if(SD==0){
		cout<<"No Student Data Available...\n";
		getch();
	}
	else{
		cout<<"      Student Login  \n\n";
		bool login = false;
		string s_no,s_pass;
		cout<<"Enrollment : ";
		cin>>s_no;
		cout<<"Password : ";
		cin>>s_pass;
		bool found = false;
		int data = -1;
		for(int i =0;i<SD;i++){
			if(s_no == s[i].enrollment ){
				found = true;
				if(found == true){
					if(s_pass == s[i].pass){
						login = true;
						data = i;
					}
					else{
						cout<<"\nPassword Not Matched...\n";
						getch();
						goto p;
					}
				}				
			}
		} // for
		
		if(data != -1){
			t:
			system("cls");
			cout<<"==================================================================\n";
			cout<<s[data].name<<"\t\t"<<s[data].enrollment<<"\n";
			cout<<"==================================================================\n\n";
			int choice;
			cout<<"1.Show Attandance  \n0.Log Out \nEnter Choice : ";
			cin>>choice;
			switch(choice){
				case 1: showattandance(s[data].enrollment); goto t; break;
				default: cout<<"\nLogging Out..."; Sleep(500); break;
			}
					
		}		
	}//else	
	menu();
}

void showattandance(string eno){
	system("cls");
	cout<<"                             Attandance of The Week  \n\n";
	bool found = false;	
	for(int i=0;i<att;i++){
		if(attandance[i][0] == eno){
			cout<<left<<setw(20)<<"Enrollment"<<setw(5)<<"Mon"<<setw(5)<<"Tue"<<setw(5)<<"Wed"<<setw(5)<<"Thu"<<setw(5)<<"Fri"<<endl;
			found = true;
			cout<<left<<setw(20)<<attandance[i][0];
			for(int j=1;j<6;j++){
				cout<<left<<setw(5)<<attandance[i][j];
			}
			getch();
			break;
		}
	}
	if(found == false){
		cout<<"\nEnrollment no not found...\n";
		getch();
	}
}

void admin(){
	p:
	system("cls");
	cout<<"                             Student Attandance Management System        \n\n";
	cout<<"      Admin Login  \n\n";
	string user,pass;
	cout<<"Username : ";
	cin>>user;
	cout<<"Password : ";
	cin>>pass;
	if(user=="admin"){
		if(pass=="pass"){
			cout<<"\nLog in Successfull...\n";
			Sleep(500);
			adminmenu();
		}
		else{
			cout<<"\nPassword not matched...\n";
			goto p;
		}
	}
	else{
		cout<<"\nUsername not matched...\n";
		goto p;
	}
	menu();
}

void adminmenu(){
	system("cls");
	cout<<"                             Student Attandance Management System        \n\n";
	cout<<" 1.Register New Student \n 2.Students Data \n 3.Mark Attandance \n 4.Attandance of The week \n 5.Remove Student Details \n 0.Log out \n Enter choice : ";
	int choice;
	cin>>choice;
	switch(choice){
		case 1: newstudent();  break;
		case 2: studentsdata();   break;
		case 3: markattandance();   break;
		case 4: attandanceofstudent();  break;
		case 5: removestudent(); break;
	}
	save();
	load();	
}

void newstudent(){
	cout<<"\n\nEnter New Student Details ";
	cout<<"\n Name : ";
	cin.ignore();
	getline(cin,s[SD].name);
	cout<<"\n Father Name : ";
	getline(cin,s[SD].fname);
	cout<<"\n Enrollment No : ";
	getline(cin,s[SD].enrollment);
	attandance[att][0]=s[SD].enrollment;
	cout<<"\n Address : ";
	getline(cin,s[SD].address);
	cout<<"\n Password of Student account : ";
	cin>>s[SD].pass;
	SD++;
	for(int c=1;c<6;c++){
		attandance[att][c]='_';
	}
	att++;
	save();
	load();
	cout<<"\nData Added to files..";
	Sleep(1100);
	adminmenu();
}

void studentsdata(){
	system("cls");
	cout<<"                             Student Records  \n\n";
	cout<<left<<setw(15)<<"Enrollment"<<setw(20)<<"Name"<<setw(20)<<"Father Name"<<setw(20)<<"Address"<<setw(20)<<"Account Password"<<endl;
	for(int i=0;i<SD;i++){
		cout<<left<<setw(15)<<s[i].enrollment<<setw(20)<<s[i].name<<setw(20)<<s[i].fname<<setw(20)<<s[i].address<<setw(20)<<s[i].pass<<endl;
	}
	getch();
	adminmenu();
}

void markattandance(){
	system("cls");
	cout<<"                             Mark Attandance  \n\n";
	int day;	
	cout<<" 1.Monday \n 2.Tuesday \n 3.Wednesday \n 4.Thursday \n 5.Friday \n";
	p:
	cin>>day;
	if( day > 5 || day <1){
		cout<<"Enter Valid Option... ";
		goto p;
	}
	cout<<left<<setw(15)<<"Enrollment No"<<setw(20)<<"Name"<<setw(5)<<"P/A"<<endl;
	for(int i=0;i<att;i++){
		cout<<left<<setw(15)<<attandance[i][0]<<setw(20)<<s[i].name;
		cin>>attandance[i][day];
		if(attandance[i][day] == "P" || attandance[i][day] == "p"){
			attandance[i][day] = "P";
		}
		else if(attandance[i][day] == "A" || attandance[i][day] == "a"){
			attandance[i][day] = "A";
		}
		else{
			attandance[i][day] = "_";
		}
	}
	
	cout<<"Attandance Marked Successfull...";
	getch();
	adminmenu();
}

void attandanceofstudent(){
	system("cls");
	cout<<"                             Attandance of The Week  \n\n";
	cout<<left<<setw(15)<<"Enrollment"<<setw(5)<<"Mon"<<setw(5)<<"Tue"<<setw(5)<<"Wed"<<setw(5)<<"Thu"<<setw(5)<<"Fri"<<endl;
	for(int i=0;i<att;i++){
		cout<<left<<setw(15)<<attandance[i][0];
		for(int j=1;j<6;j++){
			cout<<left<<setw(5)<<attandance[i][j];
			if( j==5){
				cout<<endl;
			}
		}
	}
	getch();
	adminmenu();
}

void removestudent(){
	system("cls");
	cout<<"                             Remove Student Records  \n\n";
	string eno;
	cout<<"Enter Enrollment No : ";
	cin>>eno;
	for(int i=0;i<SD;i++){
		if(s[i].enrollment == eno){
			s[i].enrollment = "DD";
		}
	}
	for(int i=0;i<att;i++){
		if(attandance[i][0] == eno){
			attandance[i][0] = "DD";
		}
	}
	save();
	load();
	cout<<"\nData removed...";
	adminmenu();
}

void load(){
	SD = 0;
	att = 0;
	ifstream file1("student_data.txt");
	if(file1.is_open()){
		while(!file1.eof()){
			
			getline(file1,s[SD].enrollment);
			getline(file1,s[SD].name);
			getline(file1,s[SD].fname);
			getline(file1,s[SD].address);
			getline(file1,s[SD].pass);
			if(file1.eof()){
				break;
			}
			SD++;
		}
	}
	
	ifstream file3("attandance.txt");
	if(file3.is_open()){
		while(!file3.eof()){
			for(int j=0;j<6;j++){
				file3>>attandance[att][j];
				if(attandance[att][j] == "DD"){
					file3>>attandance[att][j];
				}
			}
			file3.ignore();
			if(file3.eof()){
				break;
			}
			att++;
		}
	}
}

void save(){
	ofstream file2("student_data.txt");
	for(int i=0;i<SD;i++){
		if(s[i].enrollment == "DD"){
			continue;
		}
		else{
			file2<<s[i].enrollment<<endl;
			file2<<s[i].name <<endl;
			file2<<s[i].fname <<endl;
			file2<<s[i].address <<endl;
			file2<<s[i].pass<<endl;
		}
	}
	
	ofstream file4("attandance.txt");
	for(int i=0;i<att;i++){
		if(attandance[i][0] == "DD"){
			continue;
		}
		else{
			for(int j=0;j<6;j++){
				file4<<attandance[i][j]<<" ";
			}
		}
		file4<<endl;
	}
}

void menu(){
	system("cls");
	cout<<"                             Student Attandance Management System        \n\n";
	int choice;
	cout<<"1.Student Login \n2.Admin Login \n0.Exit\nEnter choice : ";
	cin>>choice;
	switch (choice){
		case 1: student(); break;
		case 2: admin(); break;
		case 0: cout<<"\n\nExiting Program..."; Sleep(500); break;
	}
}

int main(){
	
	load();
	menu();
	return 0;
	
}
