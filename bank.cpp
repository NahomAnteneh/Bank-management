#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct Customer {
	int account_number;
	string Name;
    string password;
	double balance;
	Customer* next;
	
	Customer(int acc_num, string name, string pass, double balance) : account_number(acc_num), Name(name), password(pass), balance(balance), next(NULL) {}
};

Customer* head = NULL;

static int account_number = 1000; // Add this line as a static variable

void add_customer(Customer customer) {
    Customer* new_customer = new Customer(account_number, customer.Name, customer.password, customer.balance);
    new_customer->next = head;
    head = new_customer;
    cout << "Customer added successfully! Your Account Number is: " << account_number << endl;
    account_number++;
}

void delete_customer(int account_number) {
	if(head == NULL) {
		cout << "Customer Not Found!" << endl;
		return;
	}
	
	if(head->account_number == account_number) {
		Customer* temp = head;
		head = head->next;
		delete temp;
		cout << "Customer deleted successfully!" << endl;
		return;
	}
	
	Customer* prev = head;
	Customer* curr = head->next;
	while(curr != NULL) {
		if(curr->account_number == account_number) {
			prev->next = curr->next;
			delete curr;
			cout << "Customer deleted successfully!" << endl;
            return;
		}
		prev = curr;
		curr = curr->next;
	}
	cout << "Customer Not Found!" << endl;
}

void delete_first_customer() {
	if (head == NULL) {
		cout << "Customer Not Found!" << endl;
		return;
	}

	Customer* temp = head;
	head = head->next;
	delete temp;

	cout << "First customer deleted successfully!" << endl;
}

void delete_last_customer() {
	if (head == NULL) {
		cout << "Customer Not Found!" << endl;
		return;
	}

	if (head->next == NULL) {
		delete head;
		head = NULL;
		cout << "Last customer deleted successfully!" << endl;
		return;
	}

	Customer* prev = NULL;
	Customer* curr = head;

	while (curr->next != NULL) {
		prev = curr;
		curr = curr->next;
	}

	delete curr;
	prev->next = NULL;

	cout << "Last customer deleted successfully!" << endl;
}


void display_all() {
    if (head == NULL) {
        cout << "There are no customers!" << endl;
        return;
    }
    cout << "All Customers" << endl;
    cout << "-----------------------------" << endl;

    Customer* current = head;
    while (current != NULL) {
        cout << "Account Number: " << current->account_number << endl;
        cout << "Name: " << current->Name << endl;
        cout << "Balance: " << fixed << setprecision(2) << current->balance << endl;
        cout << "-----------------------------" << endl;
        current = current->next;
    }
}

void save_data_to_file(string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        Customer* curr = head;
        while (curr != NULL) {
            file << curr->account_number << ", \"" << curr->Name << "\", \"" << curr->password << "\", " << curr->balance << endl;
            curr = curr->next;
        }
        file.close();
        cout << "Data saved to file!" << endl;
    } else {
        cout << "Failed to create file!" << endl;
    }
}

void load_data_from_file(string filename) {
    ifstream file(filename);
    if (file.is_open()) {
        head = NULL;
        int account_number;
        string name;
        string password;
        double balance;
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string account_number_str, name_str, password_str, balance_str;
            if (getline(ss, account_number_str, ',') && getline(ss, name_str, ',') && getline(ss, password_str, ',') && getline(ss, balance_str, ',')) {
                account_number = stoi(account_number_str); 
                name = name_str.substr(2, name_str.length() - 3);
                password = password_str.substr(2, password_str.length() - 3);
                balance = stod(balance_str);
                Customer customer(account_number, name, password, balance);
                add_customer(customer);
            }
        }
        file.close();
        cout << "Data Loaded From File!" << endl;
    } else {
        cout << "Failed to open file!" << endl;
    }
}


void check_balance(int account_number) {
	Customer* curr = head;
	while(curr != NULL) {
		if(curr->account_number == account_number) {
			cout << "Account Balance: " << fixed << setprecision(2) << curr->balance << endl;
			return;
		}
		curr = curr->next;
	}
	cout << "Customer Not Found!" << endl;
}

void deposit(int account_number, double amount) {
	if(head == NULL) {
        cout << "No Customers Found!" << endl;
        return;
    }
    Customer* current = head;
	while(current != NULL) {
		if(current->account_number == account_number) {
			current->balance += amount;
			cout << "Deposite Sucessful!" << endl;
			return;
		}
		current = current->next;
	}
	cout << "Customer Not Found!" << endl;
}

void withdraw(int account_number, double amount) {
	if(head == NULL) {
		cout << "No Customers Found!" << endl;
		return;
	}
	Customer* current = head;
	while(current != NULL) {
		if(current->account_number == account_number) {
			if(current->balance >= amount) {
				current->balance -= amount;
				cout << "Withdrawal successful!" << endl;
			} else {
				cout << "Insufficient Balance!" << endl;
			}
			return;
		}
		current = current->next;
	}
	cout << "Customer Not Found!" << endl;
}

bool login(Customer* head, int account_number, const string& password) {
    Customer* current = head;
    while (current != NULL) {
        if (current->account_number == account_number && current->password == password) {
            cout << "Login successful!" << endl;
            return true;
        }
        current = current->next;
    }
    cout << "Login failed! Invalid account number or password." << endl;
    return false;
}

void clear_screen() {
	system("cls");
}

Customer get_info() {
    clear_screen();
    int account_number;
    string name;
    string password;
    double balance;
        // cout << "Enter Account Number: ";
        // cin >> account_number;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Password: ";
        getline(cin, password);
        cout << "Enter Balance: ";
        cin >> balance;
        Customer customer = Customer(account_number, name, password, balance);
        return customer;
}

void print_home_window() {
    clear_screen();
    cout << "-----------------------------" << endl;
    cout << "Banking System By Linked List" << endl;
    cout << "-----------------------------" << endl;
    cout << "1. Create Account" << endl;
    cout << "2. Login for customer" << endl;
    cout << "3. Login for Admins" << endl;
    cout << "4. about us" << endl;
    cout << "5. Our services" << endl;
    cout << "6. Contact us" << endl;
    cout << "7. Exit" << endl;
    cout << "-----------------------------" << endl;
    cout << "Enter your choice: ";
}

void print_customer_window() {
    clear_screen();
    cout << "-----------------------------" << endl;
    cout << "Banking System Customer Page" << endl;
    cout << "-----------------------------" << endl;
    cout << "1. Check Balance" << endl;
    cout << "2. Deposit" << endl;
    cout << "3. Withdraw" << endl;
    cout << "4. Exit" << endl;
    cout << "-----------------------------" << endl;
    cout << "Enter your choice: ";
}

void print_admin_window() {
    clear_screen();
    cout << "-----------------------------" << endl;
    cout << "Banking System Admin Page" << endl;
    cout << "-----------------------------" << endl;
    cout << "1. Add Customer" << endl;
    cout << "2. Delete Customer by account no" << endl;
    cout << "3. Delete the first Customer" << endl;
    cout << "4. Delete the last customer" << endl;
    cout << "5. Display All Customers" << endl;
    cout << "6. Check Balance" << endl;
    cout << "7. Deposit" << endl;
    cout << "8. Withdraw" << endl;
    cout << "9. Exit" << endl;
    cout << "-----------------------------" << endl;
    cout << "Enter your choice: ";
}

void customer_space(int account_number) {
    while(true) {
        print_customer_window();
        int option;
        cin >> option;
        switch(option) {
        case 1: {
            check_balance(account_number);
	        cout << "Press any key to continue...";
            cin.ignore();
            cin.get();
            break;
        }
        case 2: {
            double amount;
            cout << "Enter Deposit Amount: ";
            cin >> amount;
            deposit(account_number, amount);
            cout << "Press any key to continue...";
            cin.ignore();
            cin.get();
            break;
        }
        case 3: {
            double amount;
            cout << "Enter Withdrawal Amount: ";
            cin >> amount;
            withdraw(account_number, amount);
            cout << "Press any key to continue...";
            cin.ignore();
            cin.get();
            break;
        }
        case 4: {
            return;
        }
        default: {
            cout << "You Entered Invalid Option" << endl;
        }
        }
    }
}

void admin_space() {
    int account_number;
    while(true) {
        print_admin_window();
        int option;
        cin >> option;
        switch (option) {
        case 1: {
            Customer customer = get_info();
            add_customer(customer);
            cout << "Press any key to continue...";
            cin.ignore();
            cin.get();
            break;
        }
        case 2: {
            clear_screen();
             cout << "Enter Account Number: ";
             cin >> account_number;
             delete_customer(account_number);
             cout << "Press any key to continue...";
             cin.ignore();
             cin.get();
             break;
        }
        case 3: {
            clear_screen();
            delete_first_customer();
            cout << "Press any key to continue...";
            cin.ignore();
            cin.get();
            break;
        }
        case 4: {
            clear_screen();
            delete_last_customer();
            cout << "Press any key to continue...";
            cin.ignore();
            cin.get();
            break;
        }
        case 5: {
            clear_screen();
	    	display_all();
	    	cout << "Press any key to continue...";
            cin.ignore();
            cin.get();
            break;
        }
        case 6: {
            clear_screen();
            cout << "Enter Account Number: ";
            cin >> account_number;
            check_balance(account_number);
	        cout << "Press any key to continue...";
            cin.ignore();
            cin.get();
            break;
        }
        case 7: {
            clear_screen();
            double amount;
            cout << "Enter Account Number: ";
            cin >> account_number;
            cout << "Enter Deposit Amount: ";
            cin >> amount;
            deposit(account_number, amount);
            cout << "Press any key to continue...";
            cin.ignore();
            cin.get();
            break;
        }
        case 8: {
            clear_screen();
            double amount;
            cout << "Enter Account Number: ";
            cin >> account_number;
            cout << "Enter Withdrawal Amount: ";
            cin >> amount;
            withdraw(account_number, amount);
            cout << "Press any key to continue...";
            cin.ignore();
            cin.get();
            break;
        }
        case 9: {
            return;
        }
        default:
            cout << "You Entered Invalid Option" << endl;
        }
    }
}

int main() {
    load_data_from_file("customer_data.txt");
    int account_number;
    string name;
    string password;
    double balance;
    bool authenticated;
    while(true) {
        print_home_window();
        int choice;
        cin >> choice;
        switch (choice) {
        case 1: {
            Customer customer = get_info();
            add_customer(customer);
            cout << "Please Login in the next page!" << endl;
            cout << "Press any key to continue...";
            cin.ignore();
            cin.get();
            break;
        }
        case 2: {
            clear_screen();
            for(int i = 3; i >= 0; i--) {
                cout << "Enter your account number: ";
                cin >> account_number;
                cout << "Enter your password: ";
                cin >> password;
                bool authenticated = login(head, account_number, password);
                if(authenticated) {
                    customer_space(account_number);
                    save_data_to_file("customer_data.txt");
                    return 0;
                } else {
                    cout << "You have " << i << " Tries left\n Please Enter the correct values!" << endl;
                }
            }
            break;
        }
        case 3: 
            clear_screen();
            int admin_id;
            for(int i = 3; i >= 0; i--) {
                cout << "Enter your Admin id: ";
                cin >> admin_id;
                cout << "Enter your password: ";
                cin >> password;
                if(admin_id == 1404607 && password == "admin") {
                   admin_space();
                   save_data_to_file("customer_data.txt");
                   return 0;
                } else {
                    cout << "You have " << i << " Tries left\n Please Enter the correct values!" << endl;
                }
            }
            break;
        
        case 4: {
            cout << "Welcome to our banking system!We are dedicated to providing efficient and secure \n financial services to our valued customers.Our system allows both customers and administrators to \nperform various banking operations with ease.\nFor Customers:\nOur user-friendly interface \nallows customers to access their accounts,check balances, make deposits, and withdraw funds.We\n prioritize the security of your personal information and employ robust authentication \nmechanisms to ensure the confidentiality of your data.We are always ready to assist you with any\n inquiries or concerns you may have.\nBest regards,\nNahom Anteneh\n";
            cout << "Press any key to continue...";
            cin.ignore();
            cin.get();
            break;
        }
        case 5: {
            cout << "At our banking system, we strive to provide a comprehensive range of\n services that cater to the financial needs of our customers those include: " << endl;
            cout << "1. Account Management:" << endl;
            cout << "   *Create new customer accounts with unique account numbers." << endl;
            cout << "   *Delete customer accounts if necessary." << endl;
            cout << "   *View a comprehensive list of all customer accounts." << endl;
            cout << "   *Check the balance of any customer's account." << endl;
            cout << "2. Secure Transactions:" << endl;
            cout << "   *Deposit funds into customer accounts securely." << endl;
            cout << "   *Withdraw funds from customer accounts while ensuring transaction integrity." << endl;
            cout << "   *Maintain accurate financial records for each transaction." << endl;
            cout << "3. User-Friendly Interface:" << endl;
            cout << "   *Intuitive and easy-to-use interface for customers and administrators." << endl;
            cout << "   *Simple login process for customers to access their accounts securely." << endl;
            cout << "   *Convenient navigation and menu options for seamless banking operations." << endl;
            cout << "4. Customer Support:" << endl;
            cout << "   *Dedicated customer support team to assist with any queries or concerns." << endl;
            cout << "   *Prompt response to customer inquiries regarding account details or transactions." << endl;
            cout << "   *Assistance in resolving any technical issues encountered during system usage." << endl;
            cout << "5. Data Security:" << endl;
            cout << "   *Stringent measures to protect customer data and ensure privacy." << endl;
            cout << "   *Robust authentication mechanisms to safeguard against unauthorized access." << endl;
            cout << "   *Regular system audits and updates to address potential vulnerabilities." << endl;
            cout << "6. Account Information:" << endl;
            cout << "   *Access detailed information about customer accounts, including names, balances, and passwords." << endl;
            cout << "   *Maintain accurate records of customer data and transactions." << endl;
            cout << "7. Financial Transactions:" << endl;
            cout << "   *Enable customers to make deposits into their accounts securely." << endl;
            cout << "   *Process withdrawals from customer accounts, ensuring accuracy and reliability." << endl;
            cout << "   *Track and update account balances in real-time." << endl;
            cout << "8. System Management:" << endl;
            cout << "   *Efficient management of customer accounts, ensuring smooth operation." << endl;
            cout << "   *Regular backups and data storage to prevent data loss." << endl;
            cout << "   *System optimization for enhanced performance and reliability." << endl;
            cout << "Press any key to continue...";
            cin.ignore();
            cin.get();
            break;
        }       
        case 6: {
            clear_screen();
            cout << "Contact Information:" << endl;
            cout << "Phone: +2519 6356 0385" << endl;
            cout << "Email: nahom.anteneh.ti@gmail.com" << endl;
            cout << "Address: Bahir Dar University" << endl;
            cout << "Github: @NahomAnteneh" << endl;
            cout << "We are available 24/7 to assist you with any inquiries or concerns you may have." << endl;
            cout << "Press any key to continue...";
            cin.ignore();
            cin.get();
            break;
            break;
        }
        case 7: {
            save_data_to_file("customer_data.txt");
            return 0;
        }
        default:
            cout << "You Entered Invalid Option" << endl;
        }
    }
    return 0;
}