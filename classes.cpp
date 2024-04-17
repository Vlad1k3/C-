#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class ResourceManagementSystem {
public:
    void createGroup(const string& groupName) {
        string command = "sudo cgcreate -g cpu,memory:" + groupName;
        system(command.c_str());
    }

    void executeApplication(const string& groupName, const string& programName) {
        string commandowner = "sudo chown ssofixd /sys/fs/cgroup/" + groupName + "/cgroup.subtree_control /sys/fs/cgroup/" + groupName + "/cgroup.procs /sys/fs/cgroup/cgroup.subtree_control /sys/fs/cgroup/cgroup.procs";
        string execCommand = "cgexec -g cpu,memory:" + groupName + " " + programName;
        cout << commandowner << endl;
        cout << execCommand << endl;
        system(commandowner.c_str());
        system(execCommand.c_str());
    }

    void deleteGroup(const string& groupName) {
        string deleteCommand = "sudo cgdelete " + groupName;
        cout << "Group " << groupName << " has been deleted." << endl;
        system(deleteCommand.c_str());
    }

    void setupGroup(const string& groupName, const string& memoryLimit) {
        string setupCommand = "sudo cgset -r memory.max=" + memoryLimit + "M " + groupName;
        system(setupCommand.c_str());
    }
};

int main(){
    ResourceManagementSystem rms;
    int choice;
    string groupName, programName, memoryLimit;

    while (true) { 
        cout << "1. Create Group" << endl;
        cout << "2. Execute Application" << endl;
        cout << "3. Delete Group" << endl;
        cout << "4. Setup" << endl;
        cout << "5. Display all groups" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the name of the group to create: ";
                cin >> groupName;
                rms.createGroup(groupName);
                break;
            
            case 2:
                cout << "Enter the group name to execute under: ";
                cin >> groupName;
                cout << "Enter the program to execute: ";
                cin >> programName;
                rms.executeApplication(groupName, programName);
                break;

            case 3:
                cout << "Enter the name of the group to delete: ";
                cin >> groupName;
                rms.deleteGroup(groupName);
                break;
            
            case 4:
                cout << "Enter the name of the group to setup: ";
                cin >> groupName;
                cout << "Enter the memory limit (in MB): ";
                cin >> memoryLimit;
                rms.setupGroup(groupName, memoryLimit);
                break;

            case 5:
                system("ls /sys/fs/cgroup");
                break;

            case 6:
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}
