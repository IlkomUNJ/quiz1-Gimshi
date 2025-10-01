#include <iostream>
#include <vector>
#include <algorithm>
#include "bank_customer.h"
#include "buyer.h"

enum PrimaryPrompt{LOGIN, REGISTER, EXIT};
enum RegisterPrompt{BUYER, SELLER, BACK};
enum LoginPrompt{ACCOUNT_STATUS, UPGRADE_ACCOUNT, CREATE_BANK_ACCOUNT, BROWSE_STORE, ORDER_FUNCTIONALITY, PAYMENT_FUNCTIONALITY, LOGOUT, DELETE_ACCOUNT, CHECK_INVENTORY, ADD_ITEM, REMOVE_ITEM, VIEW_ORDERS, EXIT_TO_MAIN_MENU, EXIT_PROGRAM};

using namespace std;


int main() {
    vector<Buyer> buyers;
    // Dummy data
    BankCustomer dummy1(1, "Alice", 1000.0);
    BankCustomer dummy2(2, "Bob", 500.0);
    buyers.push_back(Buyer(1, "Alice", dummy1));
    buyers.push_back(Buyer(2, "Bob", dummy2));
    // Set buyerIdCounter ke ID terbesar + 1
    int buyerIdCounter = 1;
    for (const auto& b : buyers) {
        if (b.getId() >= buyerIdCounter) buyerIdCounter = b.getId() + 1;
    }
    PrimaryPrompt prompt = LOGIN;
    LoginPrompt loginPrompt; // deklarasi di luar switch-case
    while (prompt != EXIT) {
        cout << "Select an option: " << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        int choice;
        cin >> choice;
        prompt = static_cast<PrimaryPrompt>(choice - 1);
        switch (prompt) {
            case LOGIN:
                cout << "Login selected." << endl;
                if (buyers.empty()) {
                    cout << "No registered accounts found. Please register first." << endl;
                    break;
                }
                cout << "Registered Accounts:" << endl;
                for (const auto& buyer : buyers) {
                    cout << "ID: " << buyer.getId() << ", Name: " << buyer.getName() << endl;
                }
                int loginId;
                cout << "Enter Buyer ID to login: ";
                cin >> loginId;
                for (auto &buyer : buyers) {
                    if (buyer.getId() == loginId) {
                        cout << "Login successful. Welcome, " << buyer.getName() << "!" << endl;
                        break;
                    }
                    else{
                        cout << "Login failed. Buyer ID not found." << endl;
                        break;
                    }
                }
                loginPrompt = ACCOUNT_STATUS;
                while(loginPrompt != LOGOUT && loginPrompt != DELETE_ACCOUNT){
                    cout << "Select an option: " << endl;
                    cout << "1. Check Account Status" << endl;
                    cout << "2. Upgrade Account to Seller" << endl;
                    cout << "3. Create Banking Account" << endl;
                    cout << "4. Browse Store Functionality" << endl;
                    cout << "5. Order Functionality" << endl;
                    cout << "6. Payment Functionality" << endl;
                    cout << "7. Logout" << endl;
                    cout << "8. Delete Account" << endl;
                    int loginOption;
                    LoginPrompt loginPrompt; 
                    cin >> loginOption;
                    loginPrompt = static_cast<LoginPrompt>(loginOption - 1);
                    switch (loginPrompt) {
                        case ACCOUNT_STATUS: {
                            cout << "Checking Account Status." << endl;
                            bool found = false;
                            for (auto& buyer : buyers) {
                                if (buyer.getId() == loginId) {
                                    cout << "Buyer ID: " << buyer.getId() << ", Name: " << buyer.getName() << endl;
                                    cout << "Bank Account Details:" << endl;
                                    buyer.getAccount().printInfo();
                                    found = true;
                                    break;
                                }
                            }
                            if(!found) {
                                cout << "No Registered Account with this ID" << endl;
                            }
                            break;
                        }
                        case UPGRADE_ACCOUNT: {
                            cout << "Upgrading Account to Seller." << endl;
                            auto it = std::find_if(buyers.begin(), buyers.end(), [loginId](const Buyer& b) { return b.getId() == loginId; });
                            if (it == buyers.end()) {
                                cout << "Buyer not found. Cannot upgrade." << endl;
                                break;
                            }
                            if (it->getAccount().getId() == 0) {
                                cout << "Cannot upgrade to Seller without a linked banking account." << endl;
                                break;
                            }
                            string storeName, storeAddress, storePhone, storeEmail;
                            cout << "Enter Store Name: ";
                            cin >> storeName;
                            cout << "Enter Store Address: ";
                            cin >> storeAddress;
                            cout << "Enter Store Phone Number: ";
                            cin >> storePhone;
                            cout << "Enter Store Email: ";
                            cin >> storeEmail;
                            cout << "Seller account registered and linked to Buyer ID: " << it->getId() << endl;
                            break;
                        }
                        case CREATE_BANK_ACCOUNT:{
                            cout << "Creating Banking Account." << endl;

                            break;
                        }
                        case BROWSE_STORE:{
                            cout << "Browsing Store Functionality." << endl;
                            break;
                        }
                        case ORDER_FUNCTIONALITY: {
                            cout << "Accessing Order Functionality." << endl;
                            break;
                        }
                        case PAYMENT_FUNCTIONALITY: {                        
                            cout << "Accessing Payment Functionality." << endl;
                            break;
                        }
                        case LOGOUT: {
                            cout << "Logging out." << endl;
                            break;
                        }
                        case DELETE_ACCOUNT: {
                            cout << "Deleting Account." << endl;
                            break;
                        }
                        default: {
                            cout << "Invalid option." << endl;
                            break;
                        }
                    }
 
                }
                
                /* if Login is selected, based on authority then provide options:
                assume user is logged in as Buyer for now
                1. Chek Account Status (will display if user is Buyer or Seller or both and linked banking account status)
                Will display Buyer, Seller and Banking Account details
                2. Upgrade Account to Seller
                Will prompt user to enter Seller details and create a Seller account linked to Buyer account
                Will reject if a user dont have a banking account linked
                3. Create Banking Account (if not already linked), will be replaced with banking functions
                Must provides: initial deposit amount, Address, Phone number, Email
                Banking functions will provides: Balance checking, Transaction History, Deposit, Withdraw
                4. Browse Store Functionality
                Will display all stores initially
                Need to select a store to browse each store inventory
                Will display all items in the store inventory
                After selecting an item, will display item details and option to add to cart
                After adding to cart, will notify user item is added to cart
                5. Order Functionality
                Will display all items in cart
                Will provide option to remove item from cart
                Will provide option to checkout
                After checkout invoide will be generated (will go to payment functionality)
                6. Payment Functionality
                Will display all listed invoices
                Pick an invoice to pay
                Will display invoice details and total amount
                Will provide option to pay invoice
                Payment is done through confirmation dialogue
                In confirmation dialogue, will display account balance as precursor
                User will need to manually enter invoice id to pay
                After paying balance will be redacted from buyer and added to the responding seller account
                After payment, order status will be changed to paid
                7. Logout (return to main menu)
                Display confirmation dialogue
                If confirmed, return to main menu
                If not, return to Buyer menu
                8. Delete Account (remove both Buyer and Seller account and relevant banking account)
                Display confirmation dialogue
                If confirmed, delete account and return to main menu
                If not, return to Buyer menu
                assume user is logged in as Seller for now
                9. Check Inventory
                10. Add Item to Inventory
                11. Remove Item from Inventory
                12. View Orders (will display all orders placed to this seller
                Only orders with paid status will be listed
                Order details will listing items, quantity, total amount, buyer details, order status (paid, cancelled, completed)
                extra functions
                9. Exit to main Menu
                10. Exit Program
                **/
                break;
            case REGISTER: {
                bool doneRegister = false;
                while (!doneRegister) {
                    cout << "Register selected." << endl;
                    cout << "Select an option: " << endl;
                    cout << "1. Register as Buyer" << endl;
                    cout << "2. Register as Seller" << endl;
                    cout << "3. Back" << endl;
                    int regOption;
                    cin >> regOption;
                    RegisterPrompt regPrompt = static_cast<RegisterPrompt>(regOption - 1);
                    switch (regPrompt) {
                        case BUYER: {
                            cout << "Registering as Buyer." << endl;
                            string name, address, phone, email;
                            cout << "Enter Name: ";
                            cin >> name;
                            cout << "Enter Address: ";
                            cin >> address;
                            cout << "Enter Phone Number: ";
                            cin >> phone;
                            cout << "Enter Email: ";
                            cin >> email;
                            int newBuyerId = buyerIdCounter++;
                            double initialDeposit = 0.0;
                            BankCustomer newCustomer(newBuyerId, name, initialDeposit);
                            Buyer newBuyer(newBuyerId, name, newCustomer);
                            buyers.push_back(newBuyer);
                            cout << "Buyer registered successfully with ID: " << newBuyerId << endl;
                            break;
                        }
                        case SELLER:
                            cout << "Registering as Seller." << endl;

                            break;
                        case BACK: {
                            cout << "Going back to main menu." << endl;
                            doneRegister = true;
                            break;
                        }
                        default: {
                            cout << "Invalid option." << endl;
                            break;
                        }
                    }
                }
                break;
            }
                /* if register is selected then went throuhh registration process:
                1. Create a new Buyer Account
                Must provides: Name, Home Address, Phone number, Email
                2. Option to create a Seller Account (will be linked to Buyer account)
                Must provides: Store Name, Store Address, Store Phone number, Store Email
                After finished immediately logged in as Buyer/Seller
                */
                break;
            case EXIT:
                cout << "Exiting." << std::endl;
                break;
            default:
                cout << "Invalid option." << endl;
                break;
        }
        cout << endl;
    }

    //BankCustomer customer1(1, "Alice", 1000.0);
    //Buyer buyer1(1, customer1.getName(), customer1);
    return 1;
}