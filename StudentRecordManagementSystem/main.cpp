#include<iostream>
#include<fstream>
#include<ostream>
using namespace std;

class Student{


    private:
        int studenID, age;
        string firstName, lastName, fatherName, gender, address;
   
    public:
        void addNewStudent(int studentId, int age, string firstName, string lastName, string fatherName, string gender, string address){

            studentId = studenID;
            age = age;
            firstName = firstName;
            lastName = lastName;
            fatherName = fatherName;
            gender = gender;
            address = address;

            ofstream myfileIn("student_database.txt", ios::app);


            if(!myfileIn){
                cout << " File not Found ";

            }else{
                cout << "Your Data Has Been Recorded ";
                myfileIn << studenID << " " << age << " " << firstName << " " << lastName << " " << fatherName << " " << gender << " " << address<<endl;

            }

            myfileIn.close();
        };

    int getDataByID(string id){

        ifstream inFile("studen_database.txt"); // Open the file for reading

            if (!inFile) {
                cerr << "Error opening file!" << endl;
            return 1;
        }

        string searchID = id; // The ID you want to find
        string line;

        while (getline(inFile, line)) {
            size_t idPos = line.find("ID: " + searchID);
            if (idPos != string::npos) {
                cout << searchID << ": " << line << endl;
          
                break; // Exit the loop after finding the line
        }
    }

    inFile.close();
    return 0;
}

};

int main(){

cout << "####################################################################################### \n";
cout << "\t\tSTUDENT RECORD MANAGEMENT SYSTEM \n";
cout << "###################################################################################### \n";

int choice;
cout << "Enter Your Choice :\n ";
cout << "1) Add Student Record \n 2) View Student Info 4) exit";
cin >> choice;



do{

    switch (choice)
{
case 1:
    /* code */
    break;
case 2:
default:
    break;
}
} while (choice == 4);

return 0;
}
