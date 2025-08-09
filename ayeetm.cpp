#include <iostream>
#include <string>
using namespace std;

void showBalance(double balance);
double deposit();
double withdraw(double balance);

struct user {
    string name;
    int pin;
    double balance;

    double transactions[10]; // stores last 10 transactions (positive: deposit, negative: withdraw)
    int transIndex;          // next index to write (0..9)
    int totalTrans;          // total transactions recorded (keeps growing)
};
       
       
        int atmNotes2000 = 10;
         int atmNotes500 = 20;
        int atmNotes100 = 50;
 
 bool dispenseCash(int amount) {
    int notes2000 = 0, notes500 = 0, notes100 = 0;
    int leftover = amount;

    // Try max 2000 notes
    notes2000 = min(leftover / 2000, atmNotes2000);
    leftover -= notes2000 * 2000;

    // Try max 500 notes
    notes500 = min(leftover / 500, atmNotes500);
    leftover -= notes500 * 500;

    // Try max 100 notes
    notes100 = min(leftover / 100, atmNotes100);
    leftover -= notes100 * 100;

    if (leftover == 0) {
        atmNotes2000 -= notes2000;
        atmNotes500 -= notes500;
        atmNotes100 -= notes100;

        cout << "Please collect your cash:\n";
        if (notes2000 > 0) cout << "Rs.2000 x " << notes2000 << "\n";
        if (notes500 > 0) cout << "Rs.500 x " << notes500 << "\n";
        if (notes100 > 0) cout << "Rs.100 x " << notes100 << "\n";

        return true;
    } else {
        // Try reducing 2000 notes and adjust smaller notes
        for (int reduce2000 = notes2000 - 1; reduce2000 >= 0; reduce2000--) {
            int tempLeftover = amount - reduce2000 * 2000;

            int temp500 = min(tempLeftover / 500, atmNotes500);
            tempLeftover -= temp500 * 500;

            int temp100 = min(tempLeftover / 100, atmNotes100);
            tempLeftover -= temp100 * 100;

            if (tempLeftover == 0) {
                atmNotes2000 -= reduce2000;
                atmNotes500 -= temp500;
                atmNotes100 -= temp100;

                cout << "Please collect your cash:\n";
                if (reduce2000 > 0) cout << "Rs.2000 x " << reduce2000 << "\n";
                if (temp500 > 0) cout << "Rs.500 x " << temp500 << "\n";
                if (temp100 > 0) cout << "Rs.100 x " << temp100 << "\n";

                return true;
            }
        }

        cout << "Cannot dispense the exact amount with available denominations.\n";
        return false;
    }
}

      int loginUser(user users[], int userCount) {
    string name;
    int pin;
    cout << "Enter the username:\n";
    cin >> name;
    cout << "Enter the pin:\n";
    cin >> pin;

    for (int i = 0; i < userCount; i++) {
        if (users[i].name == name && users[i].pin == pin) {
            cout << "login success!\n";
            return i; // Return index of logged-in user
        }
    }
    cout << "login failed.\n";
    return -1; // Login failed
}
    
          
int main() {
    user users[5] = {
        {"adi", 1234, 10000}, {"rahul", 5678, 50000}
    };
        
        int usercount=2;
        
    for (int i = 0; i < 2; i++) {
        users[i].transIndex = 0;
        users[i].totalTrans = 0;
        for (int j = 0; j < 10; j++) users[i].transactions[j] = 0.0;
    }

         cout << "Welcome to Laxmi Cheat Funds:\n";
              int index = loginUser(users, 2);  // 2 is number of users
                if (index == -1) {
             return 0; // exit program if login fails
             }
                int choice = 0;

    do {
        cout <<        "************************\n";
        cout <<          " choose the options below:\n";
        cout <<          " ************************\n";
        cout <<             "1.showbalance\n";
        cout <<             "2.deposit money\n";
        cout <<             "3.withdraw money\n";
        cout <<              "4.exit\n";
        cout <<               "5.show last transactions\n"; 
		cout<<                "6.change the pin\n";
		cout<<                "7. logout\n";
		
		  // added menu line for transactions
        cin >> choice;

        switch (choice) {
            case 1: {
                showBalance(users[index].balance);
                break;
            }
            case 2: {
                double amt = deposit();
                if (amt > 0) {
                    users[index].balance += amt;
                    // save transaction (positive)
                    users[index].transactions[users[index].transIndex] = amt;
                    users[index].transIndex = (users[index].transIndex + 1) % 10;
                    users[index].totalTrans++;
                }
                cout << "the amount is deposited and \n";
                showBalance(users[index].balance);
                break;
            }
            case 3: {
               double amtwithdraw = withdraw(users[index].balance);
                     if (amtwithdraw > 0) {
                            if (dispenseCash((int)amtwithdraw)) {
                              users[index].balance -= amtwithdraw;
                          users[index].transactions[users[index].transIndex] = -amtwithdraw;
                                    users[index].transIndex = (users[index].transIndex + 1) % 10;
                                        users[index].totalTrans++;
                                } else {
                                 cout << "Withdrawal failed due to denomination availability.\n";
                             }
}
            showBalance(users[index].balance);

                break;
            }
          
            
            case 4: {
                cout << "exiting...\n";
                break;
            }
            case 5: {
                // show last transactions for current user
                cout << "\nLast Transactions:\n";
                int count = (users[index].totalTrans < 10) ? users[index].totalTrans : 10;
                int start = (users[index].totalTrans < 10) ? 0 : users[index].transIndex;
                for (int i = 0; i < count; i++) {
                    int pos = (start + i) % 10;
                    double t = users[index].transactions[pos];
                    if (t > 0)
                        cout << "Deposit rs: +" << t << endl;
                    else
                        cout << "Withdraw rs: " << t << endl;
                }
                break;
            }
            
            case 6: {
				   
				   int oldpin, newpin,confirmpin;
				   cout<<"enter current pin: ";
				   cin>>oldpin;
				   if(oldpin!=users[index].pin){
				   	
				   	cout<<"incorrect pin:"<<endl;
				   	break;
				   }
				   cout<<"enter new pin(4digits):\n";
				   cin>>newpin;
				   cout<<"confirm the new pin\n";
				   cin>>confirmpin;
				   
				   if(newpin!=confirmpin){
				   	cout<<"pin does not matched:\n";
				   	
				   }
				   else if(newpin<1000||newpin>9999){
				   	cout<<"pin must be of 4 digits:\n";
				   	
				   }
				   
	        	else{
	        		
			users[index].pin=newpin;
			cout<<"pin has changed :\n";
			
		}		   
		     break;
	}        
	
	         
	         case 7: {
    cout << "Logging out...\n";
    index = loginUser(users, 2);
    if (index == -1) {
        cout << "Failed to login again. Exiting...\n";
        return 0;
    }
    break;
}

            default:
            	
                cout << "invalid choice\n";
        }
    } while (choice != 4);

    return 0;
}

void showBalance(double balance) {
    cout << "your balance is rs:\n" << balance << endl;
}

double deposit() {
    double amount = 0;
    cout << "enter amount to be deposited:\n";
    cin >> amount;

    if (amount > 0) {
        return amount;
    } else {
        cout << "that is  not a valid amount:\n";
        return 0;
    }
}

double withdraw(double balance) {
    double amount = 0;
    cout << "enter amount to be withdrawn:\n";
    cin >> amount;

    if (amount > balance) {
        cout << "insufficient funds\n";
        return 0;
    } else if (amount < 0) {
        cout << "that is  not a valid amount\n";
        return 0;
    } else {
        return amount;
    }
}

