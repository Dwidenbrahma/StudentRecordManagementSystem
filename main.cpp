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

            studenID = studentId;
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

        ifstream inFile("student_database.txt"); // Open the file for reading

            if (!inFile) {
                cerr << "Error opening file!" << endl;
            return 1;
        }

        string searchID = id; // The ID you want to find
        string line;

        while (getline(inFile, line)) {
            size_t idPos = line.find(searchID);
            if (idPos != string::npos) {
                cout << searchID << ": " << line << endl;
          
                break; // Exit the loop after finding the line
        }

        cout << "Not found ";
    }

    inFile.close();
    return 0;
}

};

int main(){

cout << "####################################################################################### \n";
cout << "\t\tSTUDENT RECORD MANAGEMENT SYSTEM \n";
cout << "###################################################################################### \n";

Student object;
int id, age;
string seacrhId, firstName, lastName, fatherName, gender, address;

int choice;

   


while(true){


    cout << "Enter Your Choice :\n ";
    cout << "1) Add Student Record \n 2) View Student Info \n 3) Exit: ";
    cin >> choice;





    switch (choice)
        {
            case 1:
            system("cls");
            cout << "Enter ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter  Age: ";
            cin >> age;
            cin.ignore();
            cout << "Enter First Name: ";
            cin >> firstName;
            cin.ignore();
            cout << "Enter Last Name: ";
            cin >> lastName;
            cin.ignore();
            cout << "Enter Father Name: ";
            cin >> fatherName;
            cin.ignore();
            cout << "Enter Gender: ";
            cin >> gender;
            cin.ignore();
            cout << "Enter Address: ";
            cin >> address;
            cin.ignore();
            object.addNewStudent(id, age, firstName, lastName, fatherName, gender, address);

            break;
        case 2:
            system("cls");
            cout << "Enter Student ID: ";
            cin >> id;
            object.getDataByID(seacrhId);
            break;
        case 3:
                return 0;

        default:
                cout << "Please Enter correct Choice! ";
                break;
    }

    cout << "---------Press Enter Key to Continue---------";
    cin.ignore();
    cin.get();
    system("cls");
}

    


return 0;
}
