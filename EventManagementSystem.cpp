#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <vector>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <random>
#include <regex>
#include <format>
using namespace std;

struct Event {
	string event_no;
	string event_name;
	string event_desc;
	string event_date;
	string event_time;
	string event_location;
	string event_status;
	string event_startTime;
	string event_endTime;
};

struct Registration {
	string orderID;
	string name;
	string ic;
	string email;
	string concertName;
	string concertDate;
	string seatCategory;
	string merchandiseItems;
	double totalAmount = 0.0;
};

struct Payment {
	string orderID;
	string name;
	string ic;
	string email;
	string concertName;
	string concertDate;
	string seatCategory;
	double amount;
	string status;
	Payment() : amount(0.0) {}
};

struct Ticket {
	int selectedEvent = 0;
	string issue;
	string description;
	string status;
	string ticketID;
};

struct Review {
	string custName;
	string custContact;
	string category;
	string subject;
	string description;
	string status = "Pending";
	string remark;
	string reviewID;
};

struct Merchandise {
	int eventNumber;
	string eventName;
	string productName;
	double price = 0.0;
	int stockQuantity = 0;
};

// function declaration
void logo();
void mainMenu(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter);
void userMenu(vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises);
void organiserLogin(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter);
void orgMenu(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter);
void manage_Event(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter);
void addEventInfo(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter);
void viewEventInfo(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter);
void updateEventInfo(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter);
void dltEventInfo(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter);
void viewMarketingEvent(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter);
void random3_marketingEvent();

void eventRegistration(vector<Merchandise>& merchandises);
void registerForEvent(vector<Merchandise>& merchandises);
void viewRegistrationsByIC();
void updateRegistration();
void deleteRegistration();
void paymentMenu();
void paymentProcess();
void displayReceipt(const Payment& p);
void viewPaymentStatusByIC();

void monitoringMenu(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter);
void raiseTicket(vector<Ticket>& tickets, int& ticketCounter);
void viewTicket(vector<Ticket>& tickets);
void updateTicket(vector<Ticket>& tickets);
void deleteTicket(vector<Ticket>& tickets);
void leaveReview(vector<Review>& reviews, int& reviewCount);
void handleReview(vector<Review>& reviews, int& reviewCount);
void merchandiseMenu(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter);
void createMerchandise(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises);
void deleteMerchandise(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter);
void displayMerchandiseMenu(vector<Merchandise>& merchandises);
double createAddOn(vector<Merchandise>& merchandises, string& merchandiseDetails, int selectedEventNumber, string seatCategory);

int main() {

	string staffArr[5][3] = {
		{"S01", "Joan", "123"},
		{"S02", "Shawn", "shawn123"},
		{"S03", "Stella", "stella1224"},
		{"S04", "Sandy Lim", "sandyy1314"},
		{"S05", "Alex Lee", "alex0908"}
	};

	vector<Review> reviews;
	int ticketCounter = 1;
	int reviewCount = 1;

	vector<Merchandise> merchandises;

	mainMenu(staffArr, reviews, reviewCount, merchandises, ticketCounter);

	return 0;
}

void logo() {

	system("color 03");
	cout << endl;
	cout << setw(130) << " _     _             ____  _                  _   _ " << endl;
	cout << setw(130) << "| |   (_)_   _____  |  _ \\| | __ _ _ __   ___| |_| |" << endl;
	cout << setw(130) << "| |   | \\ \\ / / _ \\ | |_) | |/ _` | '_ \\ / _ \\ __| |" << endl;
	cout << setw(130) << "| |___| |\\ V /  __/ |  __/| | (_| | | | |  __/ |_|_|" << endl;
	cout << setw(130) << "|_____|_| \\_/ \\___| |_|   |_|\\__,_|_| |_|\\___|\\__(_)" << endl;

}

// main menu
void mainMenu(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter) {

	string loginChoice;
	int loginInt;

	while (true) {

		logo();
		random3_marketingEvent();
		cout << "Press Enter to Start ...\n";
		cin.get();
		cin.ignore();

		system("color 07");
		system("cls");
		cout << string(68, '=') << endl;
		cout << format("{:>50}", "FESTIVAL CONCERT MANAGEMENT SYSTEM") << endl;
		cout << string(68, '=') << endl;
		cout << "1. User" << endl;
		cout << "2. Organiser" << endl;
		cout << "3. Exit" << endl;

		do {
			cout << "\nEnter your choice (1/2/3): ";
			cin >> loginChoice;

			bool valid = true;
			for (char c : loginChoice) {
				// if not digit will return false
				if (!isdigit(c)) {
					valid = false;
					break;
				}
			}

			if (!valid) {
				cout << "Invalid input, please enter number only!" << endl;
				continue;
			}

			loginInt = stoi(loginChoice); // stoi is string convert to int
			if (loginInt < 1 || loginInt > 3) {
				cout << "Error: Please enter only 1, 2, or 3!\n";
				continue;
			}
			break;

		} while (true);

		system("cls");

		switch (loginInt) {
		case 1:
			userMenu(reviews, reviewCount, merchandises);
			break;
		case 2:
			organiserLogin(staffArr, reviews, reviewCount, merchandises, ticketCounter);
			break;
		case 3:
			exit(0);
			break;
		}
	}
}

// User Menu
void userMenu(vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises) {
	int opt = 0;
	do {
		cout << "\n================= User Menu Page =================\n";
		cout << "1. Event Registration\n";
		cout << "2. Payment & Checkout\n";
		cout << "3. View My Registrations (by IC)\n";
		cout << "4. Leave Review / Compliant" << endl;
		cout << "5. Display Merchandise Menu" << endl;
		cout << "0. Back to Main Menu\n";

		while (true) {
			cout << "Enter choice (1-5 or 0 to exit): ";
			if (cin >> opt) {
				if (opt >= 0 && opt <= 5) {
					break;
				}
				else {
					cout << "Invalid choice. Please enter a number between 0 and 5.\n";
				}
			}
			else {
				cout << "Invalid input. Please enter a number between 0 and 5.\n";
				cin.clear();
			}
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		switch (opt) {
		case 1:
			system("cls");
			eventRegistration(merchandises);
			break;
		case 2:
			system("cls");
			paymentMenu();
			break;
		case 3:
			system("cls");
			viewRegistrationsByIC();
			break;
		case 4:
			system("cls");
			leaveReview(reviews, reviewCount);
			break;
		case 5:
			system("cls");
			displayMerchandiseMenu(merchandises);
			break;
		case 0:
			cout << "Returning to main menu...\n";
			system("cls");
			break;
		default:
			cout << "Invalid choice. Try again.\n";
		}
	} while (opt != 0);
}

// Registration
void eventRegistration(vector<Merchandise>& merchandises) {
	int opt = 0;
	do {
		cout << "\n=== Event Registration Menu ===\n";
		cout << "1. Register for Event\n";
		cout << "2. View My Registrations (by IC)\n";
		cout << "3. Update Registration (by Order ID)\n";
		cout << "4. Delete Registration (by Order ID)\n";
		cout << "0. Back\n";
		cout << "Enter choice: ";
		if (!(cin >> opt)) {
			cout << "Invalid input. Please enter a number.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		switch (opt) {
		case 1:
			registerForEvent(merchandises);
			break;
		case 2:
			viewRegistrationsByIC();
			break;
		case 3:
			updateRegistration();
			break;
		case 4:
			deleteRegistration();
			break;
		case 0:
			system("cls");
			break;
		default: cout << "Invalid.\n";
		}
	} while (opt != 0);
}

string trim(const string& s) {
	size_t start = s.find_first_not_of(" \t\r\n");
	size_t end = s.find_last_not_of(" \t\r\n");
	return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

static string makeShortOrderID(int number) {
	ostringstream oss;
	oss << "O" << setw(4) << setfill('0') << number;
	return oss.str();
}

double priceForCategory(const string& cat) {
	if (cat == "Premium") return 150.00;
	return 80.00;
}

// Reads events Info_Event.txt
static vector<Event> loadEventsFromInfo() {
	vector<Event> list;
	ifstream in("Info_Event.txt");
	string line;

	if (getline(in, line)) {}
	if (getline(in, line)) {}

	while (getline(in, line)) {
		if (line.empty()) continue;
		vector<string> fields;
		string field;
		stringstream ss(line);
		while (getline(ss, field, '|')) {
			size_t start = field.find_first_not_of(" \t\r");
			size_t end = field.find_last_not_of(" \t\r");
			fields.push_back(start == string::npos ? "" : field.substr(start, end - start + 1));
		}
		if (fields.size() != 7) continue;
		Event evt;
		evt.event_no = fields[0];
		evt.event_name = fields[1];
		evt.event_desc = fields[2];
		evt.event_date = fields[3];
		evt.event_time = fields[4];
		evt.event_location = fields[5];
		evt.event_status = fields[6];
		if (evt.event_status == "Active")
			list.push_back(evt);
	}
	return list;
}

void appendRegistrationToFile(const Registration& r) {
	ofstream out("event_registration.txt", ios::app);
	out << r.orderID << "|" << r.name << "|" << r.ic << "|" << r.email << "|"
		<< r.concertName << "|" << r.concertDate << "|" << r.seatCategory << "|" << r.merchandiseItems
		<< "|" << fixed << setprecision(2) << r.totalAmount << endl;
}

vector<Registration> loadAllRegistrations() {
	vector<Registration> out;
	ifstream in("event_registration.txt");
	if (!in) return out;
	string line;
	while (getline(in, line)) {
		if (line.empty()) continue;
		stringstream ss(line);
		Registration r;
		getline(ss, r.orderID, '|');
		getline(ss, r.name, '|');
		getline(ss, r.ic, '|');
		getline(ss, r.email, '|');
		getline(ss, r.concertName, '|');
		getline(ss, r.concertDate, '|');
		getline(ss, r.seatCategory, '|');
		getline(ss, r.merchandiseItems, '|');
		string amount;
		getline(ss, amount, '|');
		r.totalAmount = amount.empty() ? 0.0 : stod(amount);
		out.push_back(r);
	}
	in.close();
	return out;
}

// Validation
bool validateName(const std::string& name) {
	return !name.empty() && std::regex_match(name, std::regex(R"([A-Za-z ]+)"));
}

bool validateIC(const std::string& ic) {
	return ic.length() == 12 && all_of(ic.begin(), ic.end(),
		[](unsigned char c) { return isdigit(c); });
}

bool validateEmail(const std::string& mail) {
	return std::regex_match(mail, std::regex(R"((\w+)(\.?[\w-]+)*@([\w-]+\.)+[A-Za-z]{2,})"));
}

int getLastOrderNum() {
	std::ifstream in("event_registration.txt");
	std::string line, oid;
	int maxNum = 0;
	while (std::getline(in, line)) {
		if (line.size() > 1 && line[0] == 'O') {
			size_t pos = line.find('|');
			if (pos != std::string::npos)
				oid = line.substr(0, pos);
			else
				oid = line;

			try {
				int num = std::stoi(oid.substr(1));
				if (num > maxNum) maxNum = num;
			}
			catch (...) {}
		}
	}
	return maxNum;
}

void registerForEvent(vector<Merchandise>& merchandises) {
	char addOn;
	string merchandiseDetails = "None";

	//show "Active" events for registration
	vector<Event> events = loadEventsFromInfo();
	if (events.empty()) {
		cout << "\nNo events available for registration.\n";
		return;
	}

	cout << "\n=== Available Events ===\n";
	for (size_t i = 0; i < events.size(); ++i) {
		cout << (i + 1) << ". " << events[i].event_name
			<< " | " << events[i].event_date
			<< " | " << events[i].event_time
			<< " | " << events[i].event_location << endl;
	}
	cout << "--------------------------------------\n";

	int sel;
	do {
		cout << "Select event number (1-" << events.size() << "): ";
		if (!(cin >> sel) || sel < 1 || sel >(int)events.size()) {
			cout << "Invalid selection. Please enter a valid number between 1 and " << events.size() << ".\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	} while (true);

	Registration r;

	cout << "Enter your full name: ";
	getline(cin, r.name);
	while (!validateName(r.name)) {
		cout << "Invalid name! Please use letters and spaces only. Try again: ";
		getline(cin, r.name);
	}

	cout << "Enter IC number (12 digits): ";
	getline(cin, r.ic);
	while (!validateIC(r.ic)) {
		cout << "Invalid IC! Must be exactly 12 digits. Try again: ";
		getline(cin, r.ic);
	}

	cout << "Enter email (XXX@gmail.com): ";
	getline(cin, r.email);
	while (!validateEmail(r.email)) {
		cout << "Invalid email format! Try again: ";
		getline(cin, r.email);
	}

	int cat;
	do {
		cout << "Choose seating category (1. Premium / 2. Regular): ";
		if (!(cin >> cat) || (cat != 1 && cat != 2)) {
			cout << "Invalid seat category. Please enter 1 or 2.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	} while (true);
	r.seatCategory = (cat == 1 ? "Premium" : "Regular");

	// Merchandise add-ons prompt
	do {
		cout << "Add Ons for Merchandise(s)? (Y for Yes, N for No): ";
		cin >> addOn;
		if (addOn == 'y' || addOn == 'Y' || addOn == 'n' || addOn == 'N')
			break;
		cout << "Invalid input. Please enter Y or N.\n";
	} while (true);

	double merchandiseTotal = 0.0;
	double ticketPrice = priceForCategory(r.seatCategory);

	// Merchandise selection only if user wants add-ons
	if (addOn == 'y' || addOn == 'Y') {
		merchandiseTotal = createAddOn(merchandises, merchandiseDetails, sel, r.seatCategory);
	}

	// Fill registration details
	r.concertName = events[sel - 1].event_name;
	r.concertDate = events[sel - 1].event_date;
	r.orderID = makeShortOrderID(getLastOrderNum() + 1);
	r.merchandiseItems = merchandiseDetails;
	r.totalAmount = (addOn == 'y' || addOn == 'Y') ? merchandiseTotal : ticketPrice;

	appendRegistrationToFile(r);
	cout << "\nRegistered successfully! Your Order ID: " << r.orderID << endl;
	cout << "\nPress enter to continue...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // eat leftover newline
	cin.get();
	system("cls");
}

void displayOrder(const Registration& reg) {
	cout << "\n============================================================\n";
	cout << "\t\tYour Order ";
	cout << "\n============================================================\n";
	cout << std::format("Order ID       : {}\n", reg.orderID);
	cout << std::format("Name           : {}\n", reg.name);
	cout << std::format("IC             : {}\n", reg.ic);
	cout << std::format("Email          : {}\n", reg.email);
	cout << std::format("Concert        : {}\n", reg.concertName);
	cout << std::format("Date           : {}\n", reg.concertDate);
	cout << std::format("Seating Type   : {}\n", reg.seatCategory);

	cout << "\n----------- Purchase Summary --------------\n";
	cout << format("{:<23}{:>4}{:>17}{:>15}",
		"Item", "Qty", "Unit Price (RM)", "Total (RM)") << endl;
	cout << string(61, '-') << endl;

	// Ticket row
	double ticketPrice = priceForCategory(reg.seatCategory);
	cout << format("{:<23}{:>4}{:>17.2f}{:>15.2f}",
		reg.seatCategory + " Ticket", 1, ticketPrice, ticketPrice) << endl;

	// Merchandise rows
	if (reg.merchandiseItems != "None" && !reg.merchandiseItems.empty()) {
		string itemsStr = reg.merchandiseItems;
		stringstream itemSS(itemsStr);
		string detail;

		while (getline(itemSS, detail, ';')) {
			stringstream detailSS(detail);
			string productName, qtyStr, unitPriceStr, totalStr;

			detailSS >> productName >> qtyStr >> unitPriceStr >> totalStr;
			if (!productName.empty() && !qtyStr.empty() && !unitPriceStr.empty() && !totalStr.empty()) {
				int quantity = stoi(qtyStr);
				double unitPrice = stod(unitPriceStr);
				double total = stod(totalStr);

				cout << format("{:<23}{:>4}{:>17.2f}{:>15.2f}",
					productName, quantity, unitPrice, total) << endl;
			}
		}
	}

	// Totals
	double subtotal = 0.0;
	double discount = 0.0;

	if (reg.merchandiseItems != "None" && !reg.merchandiseItems.empty()) {
		subtotal = (reg.totalAmount - ticketPrice) / 0.9;
		discount = -subtotal * 0.1;
	}

	cout << string(61, '-') << endl;
	cout << format("{:<30}{:>29.2f}", "Ticket Price (RM):", ticketPrice) << endl;

	if (reg.merchandiseItems != "None" && !reg.merchandiseItems.empty()) {
		cout << format("{:<30}{:>29.2f}", "Merchandise Subtotal (RM):", subtotal) << endl;
		cout << format("{:<30}{:>29.2f}", "Bundle Discount (10%):", discount) << endl;
	}

	cout << format("{:<30}{:>29.2f}", "Final Amount (RM):", reg.totalAmount) << endl;
	cout << "============================\n";
}

// View Resgistration
void viewRegistrationsByIC() {
	cout << "Enter your IC to view registrations: ";
	string ic;
	cin >> ic;

	vector<Registration> regs = loadAllRegistrations();
	bool found = false;

	for (const Registration& r : regs) {
		if (r.ic == ic) {
			displayOrder(r);
			found = true;
		}
	}

	if (!found) {
		cout << "No registrations found for IC: " << ic << "\n";
	}

	cout << "\nPress Enter to continue...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
	system("cls");
}


// ===== Update Registration =====
void updateRegistration() {
	vector<Registration> regs = loadAllRegistrations();
	if (regs.empty()) {
		cout << "No registrations to update.\n";
		return;
	}

	cout << "Enter Order ID to update: ";
	string id;
	cin >> id;
	bool updated = false;

	for (Registration& r : regs) {
		if (r.orderID == id) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "New email (blank to keep): ";
			string s;
			getline(cin, s);
			if (!s.empty()) r.email = s;

			cout << "Change seating? (1 Premium / 2 Regular / 0 keep): ";
			int c;
			cin >> c;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			string oldCategory = r.seatCategory;
			if (c == 1) r.seatCategory = "Premium";
			else if (c == 2) r.seatCategory = "Regular";

			// Recalculate total
			double oldTicketPrice = priceForCategory(oldCategory);
			double newTicketPrice = priceForCategory(r.seatCategory);
			double merchandisePart = r.totalAmount - oldTicketPrice;

			if (merchandisePart < 0) merchandisePart = 0.0;
			r.totalAmount = newTicketPrice + merchandisePart;

			updated = true;

			// Save updates
			ofstream out("event_registration.txt", ios::trunc);
			for (const Registration& w : regs) {
				out << std::format("{}|{}|{}|{}|{}|{}|{}|{}|{:.2f}\n",
					w.orderID, w.name, w.ic, w.email,
					w.concertName, w.concertDate, w.seatCategory,
					w.merchandiseItems, w.totalAmount);
			}

			cout << "\nRegistration updated successfully.\n";
			displayOrder(r);
			break;
		}
	}

	if (!updated) {
		cout << "Order ID not found.\n";
	}

	cout << "\nPress Enter to continue...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
	system("cls");
}


void deleteRegistration() {
	vector<Registration> regs = loadAllRegistrations();
	if (regs.empty()) {
		cout << "No registrations.\n";
		return;
	}

	cout << "Enter Order ID to delete: ";
	string id;
	cin >> id;
	bool removed = false;

	for (auto it = regs.begin(); it != regs.end(); ++it) {
		if (it->orderID == id) {
			cout << "\nYou are about to delete this registration:\n";
			displayOrder(*it);

			cout << "\nAre you sure? (Y/N): ";
			char confirm;
			cin >> confirm;
			if (toupper(confirm) == 'Y') {
				regs.erase(it);
				removed = true;
			}
			break;
		}
	}

	if (removed) {
		ofstream out("event_registration.txt", ios::trunc);
		for (const Registration& w : regs) {
			out << std::format("{}|{}|{}|{}|{}|{}|{}|{}|{:.2f}\n",
				w.orderID, w.name, w.ic, w.email,
				w.concertName, w.concertDate, w.seatCategory,
				w.merchandiseItems, w.totalAmount);
		}
		cout << "\nRegistration deleted successfully.\n";
	}
	else {
		cout << "Order ID not found or deletion cancelled.\n";
	}

	cout << "\nPress Enter to continue...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
	system("cls");
}

// Load all payments from file
vector<Payment> loadPayments() {
	vector<Payment> out;
	ifstream in("payments.txt");
	if (!in) return out;
	string line;
	while (getline(in, line)) {
		if (line.empty()) continue;
		stringstream ss(line);
		Payment p;
		string amt;
		getline(ss, p.orderID, '|');
		getline(ss, p.ic, '|');
		getline(ss, p.email, '|');
		getline(ss, p.concertName, '|');
		getline(ss, p.concertDate, '|');
		getline(ss, p.seatCategory, '|');
		getline(ss, amt, '|');
		p.amount = amt.empty() ? 0.0 : stod(amt);
		getline(ss, p.status, '|');
		out.push_back(p);
	}
	in.close();
	return out;
}

// Save all payments to file
void savePayments(const vector<Payment>& all) {
	ofstream out("payments.txt", ios::trunc);
	for (size_t i = 0; i < all.size(); ++i) {
		const Payment& p = all[i];
		out << p.orderID << "|" << p.ic << "|" << p.email << "|" << p.concertName << "|" << p.concertDate
			<< "|" << p.seatCategory << "|" << p.amount << "|" << p.status << "|" << endl;
	}
	out.close();
}

// Find registration by orderID in event_registration.txt
bool findRegistrationByOrder(const string& orderID, string& outIC, string& outEmail, string& outConcert, string& outDate, string& outSeat) {
	ifstream in("event_registration.txt");
	if (!in) return false;
	string line;
	while (getline(in, line)) {
		if (line.empty()) continue;
		stringstream ss(line);
		string id;
		getline(ss, id, '|');
		if (trim(id) == trim(orderID)) {
			string name; getline(ss, name, '|');
			getline(ss, outIC, '|');
			getline(ss, outEmail, '|');
			getline(ss, outConcert, '|');
			getline(ss, outDate, '|');
			getline(ss, outSeat, '|');
			in.close();
			return true;
		}
	}
	in.close();
	return false;
}

void displayReceipt(const Payment& p) {
	cout << "\n============================================================\n";
	cout << "\t\tPAYMENT RECEIPT ";
	cout << "\n============================================================\n";
	cout << "\nUser Info\n";
	cout << format("{:<20}: {}\n", "Order ID", p.orderID);
	cout << format("{:<20}: {}\n", "IC", p.ic);
	cout << format("{:<20}: {}\n", "Email", p.email);
	cout << format("{:<20}: {}\n", "Concert", p.concertName);
	cout << format("{:<20}: {}\n", "Date", p.concertDate);
	cout << format("{:<20}: {}\n", "Seating Type", p.seatCategory);

	// Read the complete registration line from file
	ifstream in("event_registration.txt");
	if (in) {
		string line;
		while (getline(in, line)) {
			if (line.empty()) continue;

			stringstream ss(line);
			string id;
			getline(ss, id, '|');

			if (trim(id) == trim(p.orderID)) {
				// Found the registration - parse all fields
				Registration reg;
				string amountStr;

				reg.orderID = trim(id);
				getline(ss, reg.name, '|');
				getline(ss, reg.ic, '|');
				getline(ss, reg.email, '|');
				getline(ss, reg.concertName, '|');
				getline(ss, reg.concertDate, '|');
				getline(ss, reg.seatCategory, '|');
				getline(ss, reg.merchandiseItems, '|');
				getline(ss, amountStr, '|');

				reg.totalAmount = amountStr.empty() ? 0.0 : stod(amountStr);

				// Display detailed purchase breakdown
				cout << "\n----------- Purchase Summary --------------\n";
				cout << "\nItems purchased:\n\n";
				cout << format("{:<23}{:>4}{:>17}{:>15}", "Item", "Qty", "Unit Price (RM)", "Total (RM)") << endl;
				cout << string(61, '-') << endl;

				double ticketPrice = priceForCategory(reg.seatCategory);
				cout << format("{:<23}{:>4}{:>17.2f}{:>15.2f}", reg.seatCategory + " Ticket", "1", ticketPrice, ticketPrice) << endl;

				// Parse and display merchandise items if available
				if (reg.merchandiseItems != "None" && !reg.merchandiseItems.empty()) {
					string itemsStr = reg.merchandiseItems;
					vector<string> items;
					stringstream itemSS(itemsStr);
					string item;

					while (getline(itemSS, item, ';')) {
						items.push_back(trim(item));
					}

					for (const string& detail : items) {
						// Parse each merchandise detail
						stringstream detailSS(detail);
						string productName, qtyStr, unitPriceStr, totalStr;

						getline(detailSS, productName, ' ');
						getline(detailSS, qtyStr, ' ');
						getline(detailSS, unitPriceStr, ' ');
						getline(detailSS, totalStr, ' ');

						if (!productName.empty() && !qtyStr.empty() && !unitPriceStr.empty() && !totalStr.empty()) {
							int quantity = stoi(qtyStr);
							double unitPrice = stod(unitPriceStr);
							double total = stod(totalStr);

							cout << format("{:<23}{:>4}{:>17.2f}{:>15.2f}", productName, quantity, unitPrice, total) << endl;
						}
					}
				}

				// Calculate and display totals
				double subtotal = 0.0;
				double discount = 0.0;

				if (reg.merchandiseItems != "None" && !reg.merchandiseItems.empty()) {
					subtotal = (reg.totalAmount - ticketPrice) / 0.9;
					discount = -subtotal * 0.1;
				}

				cout << string(61, '-') << endl;
				cout << format("{:<30}{:>29.2f}", "Ticket Price (RM):", ticketPrice) << endl;

				if (reg.merchandiseItems != "None" && !reg.merchandiseItems.empty()) {
					cout << format("{:<30}{:>29.2f}", "Merchandise Subtotal (RM):", subtotal) << endl;
					cout << format("{:<30}{:>29.2f}", "Bundle Discount (10%):", discount) << endl;
				}

				cout << format("{:<30}{:>29.2f}", "Final Amount (RM):", reg.totalAmount) << endl;
				break;
			}
		}
		in.close();
	}
	cout << "\n============================================================\n";
	cout << format("{:<20}: {}\n", "Payment Status", p.status);
	cout << "\n============================================================\n";
}

void paymentProcess() {
	cout << "Enter Order ID to pay: ";
	string oid;
	cin >> oid;

	vector<Payment> all = loadPayments();
	for (const auto& p : all) {
		if (trim(p.orderID) == trim(oid) && p.status == "Paid") {
			cout << "\nThis order has already been paid.\n";
			displayReceipt(p);
			cout << "\nPress Enter to continue...";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
			system("cls");
			return;
		}
	}

	// Load registration details
	vector<Registration> regs = loadAllRegistrations();
	Registration* found = nullptr;
	for (auto& r : regs) {
		if (trim(r.orderID) == trim(oid)) {
			found = &r;
			break;
		}
	}

	if (!found) {
		cout << "Order ID not found in registrations.\n";
		return;
	}

	// Build payment record
	Payment p;
	p.orderID = found->orderID;
	p.ic = found->ic;
	p.email = found->email;
	p.concertName = found->concertName;
	p.concertDate = found->concertDate;
	p.seatCategory = found->seatCategory;
	p.amount = found->totalAmount;
	p.status = "Pending";

	displayReceipt(p);

	// Confirm payment
	char c;
	do {
		cout << "Confirm payment? (Y/N): ";
		cin >> c;
		if (c == 'Y' || c == 'y' || c == 'N' || c == 'n') break;
		cout << "Invalid input. Please enter Y or N.\n";
	} while (true);

	if (toupper(c) == 'Y') {
		string cardNumber;
		do {
			cout << "Enter your 16-digit card number: ";
			cin >> cardNumber;

			bool valid = (cardNumber.size() == 16 && all_of(cardNumber.begin(), cardNumber.end(), ::isdigit));
			if (!valid) {
				cout << "Invalid card number! Must be exactly 16 digits.\n";
			}
			else {
				cout << "Card number accepted.\n";
				break;
			}
		} while (true);

		// Finalize payment
		p.status = "Paid";
		vector<Payment> all = loadPayments();
		all.push_back(p);
		savePayments(all);

		cout << "Payment successful.\n";
		displayReceipt(p);

		cout << "\nPress Enter to continue...";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get();
		system("cls");
	}
	else {
		cout << "Payment cancelled.\n";
		cout << "\nPress Enter to continue...";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get();
		system("cls");
	}
}

// View Payment
void viewPaymentStatusByIC() {
	cout << "Enter your IC to view payment status: ";
	string ic;
	cin >> ic;

	vector<Registration> regs = loadAllRegistrations();
	vector<Payment> pays = loadPayments();

	bool found = false;

	for (const Registration& r : regs) {
		if (r.ic == ic) {
			found = true;

			// Create a Payment object with the necessary data
			Payment p;
			p.orderID = r.orderID;
			p.ic = r.ic;
			p.email = r.email;
			p.concertName = r.concertName;
			p.concertDate = r.concertDate;
			p.seatCategory = r.seatCategory;
			p.amount = r.totalAmount;

			// Set payment status
			p.status = "Not Paid / Pending";
			for (const Payment& payment : pays) {
				if (trim(payment.orderID) == trim(r.orderID)) {
					p.status = payment.status;
					break;
				}
			}

			displayReceipt(p);
		}
	}

	if (!found) {
		cout << "No registrations found for IC: " << ic << "\n";
	}

	cout << "\nPress Enter to continue...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
	system("cls");
}

// Payment Menu
void paymentMenu() {
	int opt = 0;
	do {
		cout << "\n=== Payment & Checkout ===\n";
		cout << "1. Pay for Order (enter Order ID)\n";
		cout << "2. View My Payment Status (by IC)\n";
		cout << "0. Back\n";

		while (true) {
			cout << "Enter choice (0 to 2): ";
			if (cin >> opt) {
				if (opt >= 0 && opt <= 2) break;
				cout << "Invalid choice. Please enter 0, 1, or 2.\n";
			}
			else {
				cout << "Invalid input. Please enter a number (0 to 2).\n";
				cin.clear();
			}
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		switch (opt) {
		case 1: paymentProcess(); break;
		case 2: viewPaymentStatusByIC(); break;
		case 0: break;
		}
	} while (opt != 0);
}

// staff login page
void organiserLogin(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter) {
	string orgID, password;
	bool loginSuccess = false;
	int attempt = 0;
	const int MAX_ATTEMPTS = 3;

	do {
		cout << "================= Organiser Login Page =================" << endl;
		cout << "Enter your ID: ";
		cin >> orgID;
		cout << "Enter password: ";
		cin >> password;

		system("cls");

		for (int i = 0; i < 5; i++) {
			if (orgID == staffArr[i][0] && password == staffArr[i][2]) {
				cout << "\nLogin Successful. Welcome, " << staffArr[i][1] << "!\n\n";
				loginSuccess = true;
				orgMenu(staffArr, reviews, reviewCount, merchandises, ticketCounter);
				break;
			}
		}

		if (!loginSuccess) {
			cout << "Login failed (" << attempt + 1 << "/" << MAX_ATTEMPTS << "). Invalid ID or password.\n\n";
			attempt++;
		}

	} while (!loginSuccess && attempt < MAX_ATTEMPTS);

	if (!loginSuccess) {
		cout << "Press enter to return back main menu page...";
		cin.ignore();
		cin.get();
	}
	return;

	system("cls");

}

// organiser menu
void orgMenu(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter) {
	char org_Menu;

	do {
		cout << format("{:=^50}\n", " Organiser Menu Page ") << endl;
		cout << "1) Manage Events" << endl;
		cout << "2) Marketing" << endl;
		cout << "3) Monitoring" << endl;
		cout << "4) Merchandising" << endl;
		cout << "5) Back to menu page" << endl;
		cout << "Enter your choice (1-5): ";
		cin >> org_Menu;

		if (!isdigit(org_Menu) || (org_Menu < '1' || org_Menu > '5')) {
			cout << "Invalid input! Please enter 1-5 only!\n" << endl;
		}

	} while (!isdigit(org_Menu) || (org_Menu < '1' || org_Menu > '5'));

	system("cls");

	switch (org_Menu) {
	case '1':
		manage_Event(staffArr, reviews, reviewCount, merchandises, ticketCounter);
		break;
	case '2':
		viewMarketingEvent(staffArr, reviews, reviewCount, merchandises, ticketCounter);
		break;
	case '3':
		monitoringMenu(staffArr, reviews, reviewCount, merchandises, ticketCounter);
		break;
	case '4':
		merchandiseMenu(staffArr, reviews, reviewCount, merchandises, ticketCounter);
		break;
	case '5':
		mainMenu(staffArr, reviews, reviewCount, merchandises, ticketCounter);
		break;
	default:
		return;
	}
}

// event menu
void manage_Event(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter) {
	char eventManage;

	do {
		cout << format("{:=^40}\n", "Manage Event Page") << endl;
		cout << "a) Create an event\n";
		cout << "b) View an event\n";
		cout << "c) Update an event\n";
		cout << "d) Delete an event\n";
		cout << "e) Back to menu page\n";
		cout << "Enter your choice(a-e): ";
		cin >> eventManage;

		eventManage = tolower(eventManage);

		if (eventManage != 'a' && eventManage != 'b' && eventManage != 'c' && eventManage != 'd' && eventManage != 'e') {
			cout << "Invalid input. Please enter a-e only!" << endl;
		}

	} while (eventManage != 'a' && eventManage != 'b' && eventManage != 'c' && eventManage != 'd' && eventManage != 'e');

	system("cls");

	switch (eventManage) {
	case 'a':
		addEventInfo(staffArr, reviews, reviewCount, merchandises, ticketCounter);
		break;
	case 'b':
		viewEventInfo(staffArr, reviews, reviewCount, merchandises, ticketCounter);
		break;
	case 'c':
		updateEventInfo(staffArr, reviews, reviewCount, merchandises, ticketCounter);
		break;
	case 'd':
		dltEventInfo(staffArr, reviews, reviewCount, merchandises, ticketCounter);
		break;
	case 'e':
		orgMenu(staffArr, reviews, reviewCount, merchandises, ticketCounter);
		break;
	default:
		cout << "Please enter a/b/c/d/e only.";
	}
}

string getValidatedInput(const string& prompt) {
	string input;
	do {
		cout << prompt;
		getline(cin, input);
		if (input.empty()) {
			cout << "Input cannot be empty. Please try again.\n";
		}
	} while (input.empty());
	return input;
}

string getValidatedDate(const string& prompt) {
	regex datePattern(R"(\d{2}/\d{2}/\d{4})");
	string input;
	do {
		cout << prompt;
		getline(cin, input);
		if (!regex_match(input, datePattern)) {
			cout << "Invalid date format. Use DD/MM/YYYY.\n";
		}
	} while (!regex_match(input, datePattern));
	return input;
}

// add event
void addEventInfo(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter) {
	Event evt;
	char choice;

	do {
		cout << format("{:=^40}\n", "Add an Event") << endl;
		cin.ignore();

		evt.event_name = getValidatedInput("Enter Event Name: ");
		evt.event_desc = getValidatedInput("Enter Description: ");
		evt.event_date = getValidatedDate("Enter Date (DD/MM/YYYY): ");
		evt.event_startTime = getValidatedInput("Enter Start Time: ");
		evt.event_endTime = getValidatedInput("Enter End Time: ");
		evt.event_location = getValidatedInput("Enter Location: ");
		evt.event_status = getValidatedInput("Enter Status: ");

		int eventNo = 1;

		ifstream inFile("Info_Event.txt");
		bool exists = inFile.good();

		ofstream file("Info_Event.txt", ios::app);
		//ios - input/output stram
		//app - append
		if (!exists) {
			file << format("{:<5}| {:<30}| {:<80}| {:<13}| {:<24}| {:<30}| {:<15}\n", "No", "Event Name", "Description", "Date", "Time Range", "Location", "Status");

			file << format("{:=^210}\n", "") << endl;
		}

		// Count current number of events
		string line;
		while (getline(inFile, line)) {
			if (line.find('|') != string::npos && isdigit(line[0])) {
				eventNo++;
			}
		}
		inFile.close();

		file << left << setw(5) << eventNo << "| " << setw(30) << evt.event_name << "| " << setw(80) << evt.event_desc << "| " << setw(13) << evt.event_date << "| " << setw(24) << (evt.event_startTime + " - " + evt.event_endTime) << "| " << setw(30) << evt.event_location << "| " << setw(15) << evt.event_status << endl;

		file.close();

		cout << "\nEvent saved! Add another? (Y/N): ";
		cin >> choice;
		while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
			cout << "\nInvalid input. Please enter Y or N: ";
			cin >> choice;
		}

	} while (choice == 'Y' || choice == 'y');

	cout << "Press Enter to Back ...\n";
	cin.get();
	cin.ignore();
	system("cls");
	manage_Event(staffArr, reviews, reviewCount, merchandises, ticketCounter);
}

// view event
void viewEventInfo(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter) {
	ifstream file("Info_Event.txt");
	vector<string> lines;
	string line;

	while (getline(file, line)) {
		if (!line.empty()) {
			lines.push_back(line);
		}
	}
	file.close();

	if (lines.size() <= 2) {
		cout << "No event details found!\n";
		manage_Event(staffArr, reviews, reviewCount, merchandises, ticketCounter);
	}

	cout << format("{:~^203}\n", " Event Info ") << endl;
	for (const string& l : lines) {
		cout << l << endl;
	}
	cout << format("{:=^203}\n", "") << endl;

	cout << "Press Enter to Back ...\n";
	cin.get();
	cin.ignore();
	system("cls");
	manage_Event(staffArr, reviews, reviewCount, merchandises, ticketCounter);

}

//check digit
bool isDigit(const string& str) {
	for (char c : str) {
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}

// update event
void updateEventInfo(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter) {
	ifstream file("Info_Event.txt");
	vector<string> lines;
	string line;

	while (getline(file, line)) {
		if (!line.empty()) lines.push_back(line);
	}
	file.close();

	if (lines.size() <= 2) {
		cout << "No event to update.\n";
		manage_Event(staffArr, reviews, reviewCount, merchandises, ticketCounter);
	}

	string updateNo;
	int updateNo_int;

	cout << "\n========== Event List ==========\n";
	for (int i = 2; i < lines.size(); i++) {
		cout << lines[i] << endl;
	}

	cout << "Enter the event number to update: ";
	cin >> updateNo;
	cin.ignore();

	if (!isDigit(updateNo)) {
		cout << "Invalid input. Please enter a number.\n";
		manage_Event(staffArr, reviews, reviewCount, merchandises, ticketCounter);
		return;
	}
	updateNo_int = stoi(updateNo);

	if (updateNo_int < 1 || updateNo_int >(lines.size() - 2)) {
		cout << "Invalid number.\n";
		manage_Event(staffArr, reviews, reviewCount, merchandises, ticketCounter);
	}

	string& eventLine = lines[updateNo_int + 1];

	vector<string> fields;
	string field;
	stringstream ss(eventLine);
	while (getline(ss, field, '|')) {

		size_t start = field.find_first_not_of(" \t");
		size_t end = field.find_last_not_of(" \t");
		if (start != string::npos)
			fields.push_back(field.substr(start, end - start + 1));
		else
			fields.push_back("");
	}

	while (fields.size() < 8) {
		fields.push_back("");
	}

	int choice;
	do {
		cout << "\nWhich field do you want to update?\n";
		cout << "1. Event Name\n";
		cout << "2. Description\n";
		cout << "3. Date (DD/MM/YYYY)\n";
		cout << "4. Start/End Time\n";
		cout << "5. Location\n";
		cout << "6. Status\n";
		cout << "Enter choice: ";
		cin >> choice;
		cin.ignore();

		if (choice < 1 || choice > 6) {
			cout << "Invalid choice.\n";
			return;
		}
	} while (choice < 1 || choice > 6);


	string newValue;
	newValue = getValidatedInput("Enter new value:");

	fields[choice] = newValue;

	ostringstream newLine;
	newLine << format("{:<5}| {:<30}| {:<80}| {:<13}| {:<24}| {:<30}| {:<15}",
		fields[0], fields[1], fields[2], fields[3], fields[4], fields[5], fields[6]);

	eventLine = newLine.str();

	ofstream out("Info_Event.txt", ios::trunc);
	for (const string& l : lines) {
		out << l << endl;
	}
	out.close();

	cout << "Event updated successfully!\n";
	cout << "Press Enter to Back ...\n";
	cin.ignore();
	system("cls");
	manage_Event(staffArr, reviews, reviewCount, merchandises, ticketCounter);
}

void dltEventInfo(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter) {
	ifstream file("Info_Event.txt");
	vector<string> lines;
	string line;

	while (getline(file, line)) {
		lines.push_back(line);
	}
	file.close();

	if (lines.size() <= 2) {
		cout << "No event to delete.\n";
		manage_Event(staffArr, reviews, reviewCount, merchandises, ticketCounter);
	}

	cout << "\n========== Event List ==========\n";
	for (int i = 2; i < lines.size(); i++) {
		cout << lines[i] << endl;
	}

	string deleteNo;
	int deleteNo_int;

	cout << "Enter the event number to delete: ";
	cin >> deleteNo;

	if (!isDigit(deleteNo)) {
		cout << "Invalid input. Please enter a number.\n";
		manage_Event(staffArr, reviews, reviewCount, merchandises, ticketCounter);
		return;
	}
	deleteNo_int = stoi(deleteNo);

	if (deleteNo_int < 1 || deleteNo_int >(lines.size() - 2)) {
		cout << "Invalid number.\n";
		manage_Event(staffArr, reviews, reviewCount, merchandises, ticketCounter);
	}

	lines.erase(lines.begin() + deleteNo_int + 1);

	for (int i = 2, num = 1; i < lines.size(); ++i, ++num) {
		size_t pos = lines[i].find('|');
		if (pos != string::npos) {
			string rest = lines[i].substr(pos);
			ostringstream newLine;
			newLine << left << setw(5) << num << rest;
			lines[i] = newLine.str();
		}
	}

	ofstream out("Info_Event.txt", ios::trunc);
	for (const string& l : lines) {
		out << l << endl;
	}

	cout << "Event deleted successfully!!\n";
	cout << "Press Enter to Back ...\n";
	cin.get();
	cin.ignore();
	system("cls");
	manage_Event(staffArr, reviews, reviewCount, merchandises, ticketCounter);
}

// event marketing
void viewMarketingEvent(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter) {
	ifstream file("Info_Event.txt");
	if (!file.is_open()) {
		cout << "Failed to open Info_Event.txt\n";
		return;
	}

	vector<string> lines;
	string line;
	while (getline(file, line)) {
		if (!line.empty()) {
			lines.push_back(line);
		}
	}
	file.close();

	if (lines.size() <= 2) {
		cout << "No event details found!\n";
		return;
	}

	cout << format("{:~^203}\n", " Event Marketing ") << endl;

	for (const string& l : lines) {
		cout << l << endl;
	}
	cout << format("{:=^203}\n", "") << endl;

	cout << "Press Enter to Back ...\n";
	cin.get();
	cin.ignore();
	system("cls");
	orgMenu(staffArr, reviews, reviewCount, merchandises, ticketCounter);
}

void random3_marketingEvent() {
	ifstream file("Info_Event.txt");
	if (!file.is_open()) {
		cout << "Failed to open Info_Event.txt\n";
		return;
	}

	vector<string> lines;
	string line;
	while (getline(file, line)) {
		if (!line.empty()) {
			lines.push_back(line);
		}
	}
	file.close();

	if (lines.size() <= 2) {
		cout << "No event details found!\n";
		return;
	}

	vector<string> ads(lines.begin() + 2, lines.end());

	int numAds = 3;
	if (numAds > ads.size()) numAds = ads.size();

	srand(time(0));
	shuffle(ads.begin(), ads.end(), default_random_engine(time(0)));

	cout << format("{:~^203}\n", " Event Ads ");

	for (int i = 0; i < numAds; ++i) {
		cout << ads[i] << endl;
	}

	cout << format("{:=^203}\n", "");
}

void monitoringMenu(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter) {

	int selection;
	static vector<Ticket> tickets;

	do {
		system("cls");
		cout << "==============================================================" << endl;
		cout << format("{:>45}", "Welcome to Monitoring Module!") << endl;
		cout << "==============================================================" << endl;
		cout << "\n1. Raise Ticket" << endl;
		cout << "2. View Ticket" << endl;
		cout << "3. Mark Ticket As Solved" << endl;
		cout << "4. Delete Ticket" << endl;
		cout << "5. Handling Customer Feedback" << endl;
		cout << "6. Back to Previous Page" << endl;

		do {
			cout << "\nPlease select from 1-6: ";
			cin >> selection;
			if (selection >= 1 && selection <= 6) {
				break;
			}
			else {
				cout << "Invalid selection, please select 1-6 only" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
			}
		} while (true);

		switch (selection) {
		case 1:
			raiseTicket(tickets, ticketCounter);
			break;
		case 2:
			viewTicket(tickets);
			break;
		case 3:
			updateTicket(tickets);
			break;
		case 4:
			deleteTicket(tickets);
			break;
		case 5:
			handleReview(reviews, reviewCount);
			break;
		case 6:
			orgMenu(staffArr, reviews, reviewCount, merchandises, ticketCounter);
			return;
		}
	} while (selection != 6);
}

void displayBriefEvent() {

	// read all events from file
	ifstream file("Info_Event.txt");
	vector<string> lines;
	string line;

	while (getline(file, line)) {
		if (!line.empty()) {
			lines.push_back(line);
		}
	}
	file.close();

	// check valid data
	if (lines.size() <= 2) {
		cout << "No events found!" << endl;
		return;
	}

	cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~ Available Events ~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
	cout << format("{:<10}{:<40}{}", "No", "Event Name", "Event Status") << endl;
	cout << format("{:<10}{:<40}{}\n", "==", "==========", "============") << endl;

	// start from line 2 to skip header 
	for (int i = 2; i < lines.size(); i++) {
		string eventLine = lines[i];

		vector<string> parts;
		string part;

		for (int j = 0; j < eventLine.length(); j++) {
			if (eventLine[j] == '|') {
				// remove spaces
				while (!part.empty() && part[0] == ' ') {
					part.erase(0, 1);
				}
				while (!part.empty() && part.back() == ' ') {
					part.pop_back();
				}
				parts.push_back(part);
				part = "";
			}
			else {
				part += eventLine[j];
			}
		}

		while (!part.empty() && part[0] == ' ') {
			part.erase(0, 1);
		}
		while (!part.empty() && part.back() == ' ') {
			part.pop_back();
		}
		parts.push_back(part);

		// display event number, name, status
		if (parts.size() >= 7) {
			cout << format("{:<10}{:<40}{:<20}", parts[0], parts[1], parts[6]) << endl;
		}
	}
}

string retrieveEventName(int eventNumber) {
	ifstream file("Info_Event.txt");
	vector<string> lines;
	string line;

	while (getline(file, line)) {
		if (!line.empty()) {
			lines.push_back(line);
		}
	}
	file.close();

	// data validation (range check)
	if (eventNumber <1 || eventNumber >(lines.size() - 2)) {
		return "Unknown Event";
	}

	string eventName = lines[eventNumber + 1]; // skip the header
	stringstream ss(eventName);
	string field;

	getline(ss, field, '|'); // skip event number
	getline(ss, field, '|'); // retrieve event name

	return trim(field);
}

void raiseTicket(vector<Ticket>& tickets, int& ticketCounter) {

	Ticket newTicket;
	char confirmation;
	int totalEvents;

	system("cls");
	cout << "==============================================================" << endl;
	cout << format("{:>39}", "Raise New Ticket") << endl;
	cout << "==============================================================" << endl;
	displayBriefEvent();

	ifstream file("Info_Event.txt");
	vector<string> lines;
	string line;
	while (getline(file, line)) {
		if (!line.empty()) {
			lines.push_back(line);
		}
	}
	file.close();
	totalEvents = lines.size() - 2;

	if (totalEvents > 0) {
		do {
			cout << "\nPlease select the event: ";
			cin >> newTicket.selectedEvent;
			if (newTicket.selectedEvent >= 1 && newTicket.selectedEvent <= totalEvents) {
				break;
			}
			else {
				cout << "Invalid number, please enter number between 1-" << totalEvents << endl;
				cin.clear();
				cin.ignore(1000, '\n');
			}
		} while (true);
	}

	cin.ignore();

	do {
		cout << "Enter issue title: ";
		getline(cin, newTicket.issue);
		if (!newTicket.issue.empty()) {
			break;
		}
		else {
			cout << "Issue title cannot be empty! Please try again" << endl;
		}
	} while (true);

	do {
		cout << "Enter issue description: " << endl;
		getline(cin, newTicket.description);
		if (!newTicket.description.empty()) {
			break;
		}
		else {
			cout << "Issue description cannot be empty! Please try again" << endl;
		}
	} while (true);

	newTicket.ticketID = format("T{:04}", ticketCounter);
	newTicket.status = "Pending";
	tickets.push_back(newTicket);

	cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~ Ticket Summary ~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
	cout << format("{:<20}{:>42}", "Event Selected:", newTicket.selectedEvent) << endl;
	cout << format("{:<20}{:>42}", "Issue:", newTicket.issue) << endl;
	cout << format("{:<20}\n{}", "Description:", newTicket.description) << endl;

	do {
		cout << "\nConfirm for submission? (Y for Yes, N for No): ";
		cin >> confirmation;

		if (confirmation == 'Y' || confirmation == 'y' || confirmation == 'N' || confirmation == 'n') {
			break;
		}
		else {
			cout << "Invalid input, please enter Y or N" << endl;
		}
	} while (true);

	if (confirmation == 'Y' || confirmation == 'y') {
		ticketCounter++;
		cout << "\nTicket submitted successfully!" << endl;
		cout << "Your ticket ID is: " << newTicket.ticketID << endl;
		cout << "Status: " << newTicket.status << endl;
		cout << "Thank you for reporting the issue! Relevant team will follow up ASAP" << endl;
		cout << "\nPress enter to continue...";
	}
	else if (confirmation == 'N' || confirmation == 'n') {
		tickets.pop_back(); // remove ticket from vector if user enter no
		cout << "\nTicket submission cancelled!" << endl;
		cout << "\nPress enter to continue...";
	}

	cin.ignore();
	cin.get();
}

void viewTicket(vector<Ticket>& tickets) {

	string searchTicketID;
	bool found = false;
	int viewOption;

	system("cls");
	cout << "==============================================================" << endl;
	cout << format("{:>37}", "View Tickets") << endl;
	cout << "==============================================================" << endl;

	// check if tickets exist
	if (tickets.empty()) {
		cout << "\nNo tickets available" << endl;
		cout << "\nPress enter to continue...";
		cin.ignore();
		cin.get();
		return;
	}

	cout << "\nViewing Option" << endl;
	cout << "1. View All Tickets" << endl;
	cout << "2. View Particular Tickets" << endl;

	do {
		cout << "\nPlease select 1 or 2: ";
		cin >> viewOption;

		if (viewOption == 1 || viewOption == 2) {
			break;
		}
		else {
			cout << "Please enter 1 or 2 only" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
	} while (true);

	// display all tickets
	if (viewOption == 1) {
		cout << "\n\n~~~~~~~~~~~~~~~~~~~~~ All Tickets Summary ~~~~~~~~~~~~~~~~~~~~\n" << endl;
		for (int i = 0; i < tickets.size(); i++) {
			cout << format("===== Ticket {} =====", i + 1) << endl;
			cout << format("{:<20}{:>42}", "Ticket ID:", tickets[i].ticketID) << endl;
			cout << format("{:<20}{:>42}", "Event Selected:", tickets[i].selectedEvent) << endl;
			cout << format("{:<20}{:>42}", "Issue:", tickets[i].issue) << endl;
			cout << format("{:<20}{:>42}", "Status:", tickets[i].status) << endl;
			cout << "Description:\n" << tickets[i].description << endl;
		}
	}
	// search ticket ID
	else if (viewOption == 2) {
		cin.ignore();
		cout << "\nEnter Ticket ID to Search: ";
		cin >> searchTicketID;

		cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~ Ticket Details ~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

		for (int i = 0; i < tickets.size(); i++) {
			if (tickets[i].ticketID == searchTicketID) {
				found = true;
				cout << format("{:<20}{:>42}", "Ticket ID:", tickets[i].ticketID) << endl;
				cout << format("{:<20}{:>42}", "Event Selected:", tickets[i].selectedEvent) << endl;
				cout << format("{:<20}{:>42}", "Issue:", tickets[i].issue) << endl;
				cout << format("{:<20}{:>42}", "Description:", tickets[i].description) << endl;
				cout << format("{:<20}{:>42}", "Status:", tickets[i].status) << endl;
				break;
			}
		}
		if (!found) {
			cout << "Ticket ID " << searchTicketID << " not found!" << endl;
		}
	}

	cout << "\nPress enter to continue...";
	cin.ignore();
	cin.get();
}

// mark the ticket as solved
void updateTicket(vector<Ticket>& tickets) {

	string searchTicketID;
	char markAsSolved;
	bool found = false;
	int ticketIndex = -1;

	system("cls");
	cout << "==============================================================" << endl;
	cout << format("{:>36}", "Update Tickets") << endl;
	cout << "==============================================================" << endl;

	if (tickets.empty()) {
		cout << "\nNo tickets available" << endl;
		cout << "\nPress enter to continue...";
		cin.ignore();
		cin.get();
		return;
	}

	cout << "\nEnter Ticket ID to Search: ";
	cin >> searchTicketID;

	cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~ Ticket Details ~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

	for (int i = 0; i < tickets.size(); i++) {
		if (tickets[i].ticketID == searchTicketID) {
			ticketIndex = i;
			found = true;
			cout << format("{:<20}{:>42}", "Ticket ID:", tickets[i].ticketID) << endl;
			cout << format("{:<20}{:>42}", "Event Selected:", tickets[i].selectedEvent) << endl;
			cout << format("{:<20}{:>42}", "Issue:", tickets[i].issue) << endl;
			cout << format("{:<20}{:>42}", "Status:", tickets[i].status) << endl;
			cout << "Description:\n" << tickets[i].description << endl;
			break;
		}
	}

	if (!found) {
		cout << "Ticket ID '" << searchTicketID << "' not found!" << endl;
		cout << "Press enter to continue...";
		cin.ignore();
		cin.get();
		return;
	}

	if (tickets[ticketIndex].status == "Solved") {
		cout << "\nThis ticket is already marked as solved!" << endl;
		cout << "Press enter to continue...";
		cin.ignore();
		cin.get();
		return;
	}

	do {
		cout << "\nMark the ticket as solved? (Y for Yes, N for No): ";
		cin >> markAsSolved;

		if (markAsSolved == 'Y' || markAsSolved == 'y' || markAsSolved == 'N' || markAsSolved == 'n') {
			break;
		}
		else {
			cout << "Error: Please enter only Y or N!" << endl;
		}
	} while (true);

	if (markAsSolved == 'Y' || markAsSolved == 'y') {
		tickets[ticketIndex].status = "Solved";
		cout << "\nTicket " << searchTicketID << " has been marked as solved!" << endl;
	}
	else if (markAsSolved == 'N' || markAsSolved == 'n') {
		cout << "\n\nTicket status remains unchanged." << endl;
	}

	cout << "Press enter to continue...";
	cin.ignore();
	cin.get();
}

void deleteTicket(vector<Ticket>& tickets) {

	string ticketID;
	bool found = false;
	char confirmation;

	system("cls");
	cout << "==============================================================" << endl;
	cout << format("{:>37}", "Delete Ticket") << endl;
	cout << "==============================================================" << endl;


	if (tickets.empty()) {
		cout << "\nNo tickets available to delete." << endl;
		cout << "\nPress enter to continue...";
		cin.ignore();
		cin.get();
		return;
	}

	do {
		cout << "\nPlease enter ticket ID to delete: ";
		cin.ignore();
		getline(cin, ticketID);
		if (!ticketID.empty()) {
			break;
		}
		else {
			cout << "Ticket ID cannot be empty! Please try again" << endl;
		}
	} while (true);

	for (int i = 0; i < tickets.size(); i++) {
		if (tickets[i].ticketID == ticketID) {
			found = true;

			// unable to delete ticket that aldy solved
			if (tickets[i].status == "Solved") {
				cout << "Ticket unable to delete due to status <Solved>" << endl;
				break;
			}
			cout << "\n~~~~~~~~~~~~~~~~~~~~~ Ticket to Delete ~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
			cout << format("{:<20}{:>42}", "Ticket ID:", tickets[i].ticketID) << endl;
			cout << format("{:<20}{:>42}", "Event Selected:", tickets[i].selectedEvent) << endl;
			cout << format("{:<20}{:>42}", "Issue:", tickets[i].issue) << endl;
			cout << format("{:<20}{:>42}", "Status:", tickets[i].status) << endl;
			cout << "Description:\n" << tickets[i].description << endl;

			do {
				cout << "Confirm delete ticket? (Y for Yes, N for No): ";
				cin >> confirmation;

				if (confirmation == 'Y' || confirmation == 'y' || confirmation == 'N' || confirmation == 'n') {
					break;
				}
				else {
					cout << "Error: Please enter only Y or N!" << endl;
				}
			} while (true);

			if (confirmation == 'Y' || confirmation == 'y') {
				tickets[i] = tickets[tickets.size() - 1];
				tickets.pop_back();
				cout << "\nTicket ID " << ticketID << " successfully deleted!" << endl;
			}
			else {
				cout << "\nTicket deletion cancelled!" << endl;
			}
			break;
		}
	}
	if (!found) {
		cout << "Ticket " << ticketID << " not found!" << endl;
	}

	cout << "\nPress enter to continue...";
	cin.ignore();
	cin.get();
}

void leaveReview(vector<Review>& reviews, int& reviewCount) {

	static vector<Review> newReview; // store multiple reviews

	Review review;
	string categories[5] = { "Service", "Payment", "Staff Behavior", "Technical Issue", "Others" };
	int choice;
	char confirmation;

	system("cls");
	cout << "==============================================================" << endl;
	cout << format("{:>42}", "Leave Review / Complaint") << endl;
	cout << "==============================================================" << endl;
	cin.ignore();

	do {
		cout << "Your Name: ";
		getline(cin, review.custName);
		if (!review.custName.empty()) {
			break;
		}
		else {
			cout << "Name cannot be empty! Please try again" << endl;
		}
	} while (true);

	do {
		cout << "Contact Number: ";
		getline(cin, review.custContact);
		if (!review.custContact.empty()) {
			break;
		}
		else {
			cout << "Contact number cannot be empty! Please try again" << endl;
		}
	} while (true);

	cout << "\n~~~~~ Category ~~~~~" << endl;
	for (int i = 0; i < 5; i++) {
		cout << (i + 1) << ". " << categories[i] << endl;
	}
	do {
		cout << "\nPlease select category from 1-5: ";
		cin >> choice;
		if (choice >= 1 && choice <= 5) {
			break;
		}
		else {
			cout << "Invalid input, please select only 1-5!" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
	} while (true);

	review.category = categories[choice - 1];
	cin.ignore();

	do {
		cout << "\nEnter subject: " << endl;
		getline(cin, review.subject);
		if (!review.subject.empty()) {
			break;
		}
		else {
			cout << "Subject cannot be empty! Please try again" << endl;
		}
	} while (true);

	do {
		cout << "\nEnter issue description: " << endl;
		getline(cin, review.description);
		if (!review.description.empty()) {
			break;
		}
		else {
			cout << "Issue description cannot be empty! Please try again" << endl;
		}
	} while (true);

	review.reviewID = format("R{:04}", reviewCount);

	cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~ Review Summary ~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
	cout << format("{:<20}{:>42}", "Customer Name:", review.custName) << endl;
	cout << format("{:<20}{:>42}", "Contact:", review.custContact) << endl;
	cout << format("{:<20}{:>42}", "Category:", review.category) << endl;
	cout << format("{:<20}{:>42}", "Subject:", review.subject) << endl;
	cout << format("{:<20}", "Description:") << endl;
	cout << review.description << endl;

	do {
		cout << "\nConfirm submission? (Y for Yes, N for No): ";
		cin >> confirmation;

		if (confirmation == 'Y' || confirmation == 'y' || confirmation == 'N' || confirmation == 'n') {
			break;
		}
		else {
			cout << "Error: Please enter only Y or N!" << endl;
		}
	} while (true);

	if (confirmation == 'Y' || confirmation == 'y') {
		reviews.push_back(review);
		reviewCount++;
		cout << "\nReview submitted successfully!" << endl;
		cout << "Your review ID is: " << review.reviewID << endl;
		cout << "Thank you for your feedback! We will review your feedback and get back to you soon." << endl;
	}
	else if (confirmation == 'N' || confirmation == 'n') {
		cout << "\nReview submission cancelled!" << endl;
	}

	cout << "\nPress enter to continue...";
	cin.ignore();
	cin.get();
}

void handleReview(vector<Review>& reviews, int& reviewCount) {

	int choice;
	string reviewID;
	bool found = false;

	system("cls");
	cout << "==============================================================" << endl;
	cout << format("{:>45}", "Customer Feedback Management") << endl;
	cout << "==============================================================" << endl;

	if (reviews.empty()) {
		cout << "\nNo customer reviews available." << endl;
		cout << "Press enter to continue...";
		cin.ignore();
		cin.get();
		return;
	}

	cout << "\nViewing Option" << endl;
	cout << "1. View Pending Feedback" << endl;
	cout << "2. View Solved Feedback" << endl;

	do {
		cout << "\nPlease select 1 or 2: ";
		cin >> choice;
		if (choice == 1 || choice == 2) {
			break;
		}
		else {
			cout << "Please enter 1 or 2 only" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
	} while (true);

	bool hasPending = false;
	bool hasSolved = false;

	// show pending feedback
	if (choice == 1) {
		cout << "\n~~~~~~~~~~~~~~~~~ Pending Customer Reviews ~~~~~~~~~~~~~~~~~~~\n" << endl;
		for (int i = 0; i < reviews.size(); i++) {
			if (reviews[i].status == "Pending") {
				hasPending = true;
				cout << format("===== Review {} =====", i + 1) << endl;
				cout << format("{:<20}{:>42}", "Review ID:", reviews[i].reviewID) << endl;
				cout << format("{:<20}{:>42}", "Customer:", reviews[i].custName) << endl;
				cout << format("{:<20}{:>42}", "Contact:", reviews[i].custContact) << endl;
				cout << format("{:<20}{:>42}", "Category:", reviews[i].category) << endl;
				cout << format("{:<20}{:>42}", "Subject:", reviews[i].subject) << endl;
				cout << format("{:<20}{:>42}", "Status:", reviews[i].status) << endl;
				cout << "Description: " << endl;
				cout << reviews[i].description << endl;
				if (!reviews[i].remark.empty()) {
					cout << "Staff Remark: " << endl;
					cout << reviews[i].remark << endl;
				}
				cout << endl;
			}
		}
		if (!hasPending) {
			cout << "No pending reviews found" << endl;
		}
	}

	// show solved cases 
	else if (choice == 2) {
		cout << "\n~~~~~~~~~~~~~~~~~ Solved Customer Reviews ~~~~~~~~~~~~~~~~~~~~\n" << endl;
		for (int i = 0; i < reviews.size(); i++) {
			if (reviews[i].status == "Solved") {
				hasSolved = true;
				cout << format("===== Review {} =====", i + 1) << endl;
				cout << format("{:<20}{:>42}", "Review ID:", reviews[i].reviewID) << endl;
				cout << format("{:<20}{:>42}", "Customer:", reviews[i].custName) << endl;
				cout << format("{:<20}{:>42}", "Contact:", reviews[i].custContact) << endl;
				cout << format("{:<20}{:>42}", "Category:", reviews[i].category) << endl;
				cout << format("{:<20}{:>42}", "Subject:", reviews[i].subject) << endl;
				cout << format("{:<20}{:>42}", "Status:", reviews[i].status) << endl;
				cout << "Description: " << endl;
				cout << reviews[i].description << endl;
				cout << "Staff Remark: " << endl;
				cout << reviews[i].remark << endl;
				cout << endl;
			}
		}
		if (!hasSolved) {
			cout << "No solved reviews found" << endl;
		}
	}

	// Only ask for Review ID if there are pending reviews and user select option 1
	if (choice == 1 && hasPending) {
		cout << "Enter Review ID to handle: ";
		cin >> reviewID;
		for (int i = 0; i < reviews.size(); i++) {
			if (reviews[i].reviewID == reviewID) {
				found = true;
				if (reviews[i].status == "Solved") {
					cout << "\nThis review is already solved!" << endl;
				}
				else {
					cout << "Add your remark: ";
					cin.ignore();
					getline(cin, reviews[i].remark);
					reviews[i].status = "Solved";
					cout << "\nReview " << reviewID << " has been handled and marked as solved!" << endl;
				}
				break;
			}
		}
		if (!found) {
			cout << "\nReview ID not found!" << endl;
		}
	}

	cout << "\nPress enter to continue...";
	cin.ignore();
	cin.get();
}

void merchandiseMenu(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter) {

	int selection;

	do {
		system("cls");
		cout << "==============================================================" << endl;
		cout << format("{:>47}", "Welcome to Merchandising Module!") << endl;
		cout << "==============================================================" << endl;
		cout << "\n1. Create Merchandise" << endl;
		cout << "2. Delete Merchandise" << endl;
		cout << "3. Back to Previous Page" << endl;

		do {
			cout << "\nPlease select from 1-3: ";
			cin >> selection;
			if (selection >= 1 && selection <= 3) {
				break;
			}
			else {
				cout << "Invalid selection, please select 1-3 only" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
			}
		} while (true);

		switch (selection) {
		case 1:
			createMerchandise(staffArr, reviews, reviewCount, merchandises);
			break;
		case 2:
			deleteMerchandise(staffArr, reviews, reviewCount, merchandises, ticketCounter);
			break;
		case 3:
			orgMenu(staffArr, reviews, reviewCount, merchandises, ticketCounter);
			break;
		}
	} while (selection != 3);
}

// organiser create merchandise menu
void createMerchandise(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises) {

	int selection = 0;
	int num;
	char confirmation;
	int totalEvents;
	string selectedEvent;

	system("cls");
	cout << "==============================================================" << endl;
	cout << format("{:>38}", "Add Merchandise") << endl;
	cout << "==============================================================" << endl;

	displayBriefEvent();

	ifstream file("Info_Event.txt");
	vector<string> lines;
	string line;
	while (getline(file, line)) {
		if (!line.empty()) {
			lines.push_back(line);
		}
	}
	file.close();
	totalEvents = lines.size() - 2;

	if (totalEvents > 0) {
		do {
			cout << "\nPlease select the event: ";
			cin >> selection;
			if (selection >= 1 && selection <= totalEvents) {
				break;
			}
			else {
				cout << "Invalid selection, please select between 1-" << totalEvents << endl;
				cin.clear();
				cin.ignore(1000, '\n');
			}
		} while (true);
	}

	selectedEvent = retrieveEventName(selection);

	bool existingFound = false;
	int existingCount = 0; // to avoid confusing, clearly shown how many merchandises
	for (int i = 0; i < merchandises.size(); i++) {
		if (merchandises[i].eventNumber == selection) { // if got previous record then retrieve
			if (!existingFound) {
				existingFound = true;
				cout << "\n============== Existing Merchandise for Event " << selection << " ==============\n" << endl;
				cout << format("{:<7}{:<35}{:<13}{:>7}", "No.", "Product Name", "Price (RM)", "Stock") << "\n" << endl;
			}
			existingCount++;
			cout << format("{:<7}{:<35}{:<13.2f}{:>7}", existingCount, merchandises[i].productName, merchandises[i].price, merchandises[i].stockQuantity) << endl;
			cout << "\n";
		}
	}

	// no then display appropriate message 
	if (!existingFound) {
		cout << "No existing merchandise for the event now" << endl;
	}


	do {
		// enter the merchandise
		cout << "\nPlease enter the number of merchandise need to add (type): ";
		cin >> num;
		if (num > 0) {
			break;
		}
		else {
			cout << "Invalid input, please enter positive number" << totalEvents << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
	} while (true);

	vector<Merchandise> newMerchandises(num);

	for (int i = 0; i < num; i++) {
		cout << "\nEnter details for merchandise " << (existingCount + i + 1) << ": " << endl;
		cout << "=================================" << endl;
		cin.ignore();

		newMerchandises[i].eventNumber = selection;
		newMerchandises[i].eventName = selectedEvent;

		do {
			cout << "Product Name: ";
			getline(cin, newMerchandises[i].productName);
			if (!newMerchandises[i].productName.empty()) {
				break;
			}
			else {
				cout << "Product name cannot be empty! Please try again" << endl;
			}
		} while (true);

		do {
			cout << "Price (RM): ";
			cin >> newMerchandises[i].price;
			if (newMerchandises[i].price > 0) {
				break;
			}
			else {
				cout << "Price must be greater than 0!" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
			}
		} while (true);

		cin.ignore();

		do {
			cout << "Initial Stock Quantity: ";
			cin >> newMerchandises[i].stockQuantity;
			if (newMerchandises[i].stockQuantity > 0) {
				break;
			}
			else {
				cout << "Please enter a valid number, stock must greather than 0" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
			}
		} while (true);
	}

	cout << "\n==============================================================" << endl;
	cout << format("{:>34}", "Summary") << endl;
	cout << "==============================================================" << endl;
	for (int i = 0; i < num; i++) {
		cout << format("\nMerchandise {}", existingCount + i + 1) << endl;
		cout << "=============" << endl;
		cout << format("{:<20}{:>42}", "Product Name:", newMerchandises[i].productName) << endl;
		cout << format("{:<20}{:>42.2f}", "Price (RM):", newMerchandises[i].price) << endl;
		cout << format("{:<20}{:>42}", "Stock Quantity:", newMerchandises[i].stockQuantity) << endl;
	}

	do {
		cout << "\nAre you confirm to save? (Y for Yes, N for No): ";
		cin >> confirmation;

		if (confirmation == 'Y' || confirmation == 'y' || confirmation == 'N' || confirmation == 'n') {
			break;
		}
		else {
			cout << "Error: Please enter only Y or N!" << endl;
		}
	} while (true);

	if (confirmation == 'Y' || confirmation == 'y') {
		merchandises.insert(merchandises.end(), newMerchandises.begin(), newMerchandises.end());
		cout << "\nMerchandise(s) successfully saved!" << endl;
	}
	else {
		cout << "\nMerchandise(s) won't save!" << endl;
	}

	cout << "Please press enter to continue...";
	cin.ignore();
	cin.get();
	return;
}

void deleteMerchandise(string staffArr[][3], vector<Review>& reviews, int& reviewCount, vector<Merchandise>& merchandises, int& ticketCounter) {

	int eventChoice;
	int deleteChoice;
	char confirmation;

	system("cls");
	cout << "==============================================================" << endl;
	cout << format("{:>42}", "Delete Merchandise") << endl;
	cout << "==============================================================" << endl;

	displayBriefEvent();

	// Get event selection
	ifstream file("Info_Event.txt");
	vector<string> lines;
	string line;
	while (getline(file, line)) {
		if (!line.empty()) lines.push_back(line);
	}
	file.close();
	int totalEvents = lines.size() - 2;

	do {
		cout << "\nPlease select the event: ";
		cin >> eventChoice;
		if (eventChoice >= 1 && eventChoice <= totalEvents) {
			break;
		}
		else {
			cout << "Invalid selection, please select between 1-" << totalEvents << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
	} while (true);

	// Show merchandise for selected event
	vector<int> merchandiseIndex;
	int count = 0;

	for (int i = 0; i < merchandises.size(); i++) {
		if (merchandises[i].eventNumber == eventChoice) {
			count++;
			merchandiseIndex.push_back(i);
		}
	}

	if (count == 0) {
		cout << "No merchandise found for this event.\n";
		cout << "Press enter to continue...";
		cin.ignore();
		cin.get();
		merchandiseMenu(staffArr, reviews, reviewCount, merchandises, ticketCounter);
		return;
	}
	else {
		cout << "\n============== Existing Merchandise for Event " << eventChoice << " ==============\n" << endl;
		cout << format("{:<7}{:<35}{:<13}{:>7}", "No.", "Product Name", "Price (RM)", "Stock") << "\n" << endl;
		for (int i = 0; i < count; i++) {
			int index = merchandiseIndex[i];
			cout << format("{:<7}{:<35}{:<13.2f}{:>7}", i + 1, merchandises[index].productName, merchandises[index].price, merchandises[index].stockQuantity) << endl;
		}
	}

	do {
		cout << "\nSelect merchandise to delete (1-" << count << "): ";
		cin >> deleteChoice;
		if (deleteChoice >= 1 && deleteChoice <= count) {
			break;
		}
		else {
			cout << "Invalid selection!" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
	} while (true);

	int index = merchandiseIndex[deleteChoice - 1];

	cout << "\n\n===== Merchandise to Delete =====" << endl;
	cout << format("Product: {}\nPrice: RM {:.2f}\nStock: {}\n", merchandises[index].productName, merchandises[index].price, merchandises[index].stockQuantity);

	do {
		cout << "\nConfirm deletetion? (Y for Yes, N for No): ";
		cin >> confirmation;
		if (confirmation == 'Y' || confirmation == 'y' || confirmation == 'N' || confirmation == 'n') {
			break;
		}
		else {
			cout << "Please enter Y or N" << endl;
		}
	} while (true);

	if (confirmation == 'Y' || confirmation == 'y') {
		merchandises.erase(merchandises.begin() + index);
		cout << "\nSuccessfully deleted!" << endl;
	}
	else {
		cout << "Deletion cancelled!" << endl;
	}

	cout << "Press enter to continue...";
	cin.ignore();
	cin.get();
}

// show merchandise menu to user
void displayMerchandiseMenu(vector<Merchandise>& merchandises) {

	int choice;
	string eventName;

	displayBriefEvent();

	ifstream file("Info_Event.txt");
	vector<string> lines;
	string line;
	while (getline(file, line)) {
		if (!line.empty()) {
			lines.push_back(line);
		}
	}
	file.close();
	int totalEvents = lines.size() - 2;

	do {
		cout << "\nPlease select the event to display merchandise menu: ";
		cin >> choice;
		if (choice >= 1 && choice <= totalEvents) {
			break;
		}
		else {
			cout << "Invalid selection, please select between 1-" << totalEvents << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
	} while (true);

	eventName = retrieveEventName(choice);
	cout << "\n==============================================================" << endl;
	cout << format("{:>38}", "Merchandise Menu") << endl;
	cout << "==============================================================\n" << endl;
	cout << "Event " << choice << ": " << eventName << "\n" << endl;

	// filter merchandise for the selected event
	vector<Merchandise> eventMerchandise;
	for (int i = 0; i < merchandises.size(); i++) {
		if (merchandises[i].eventNumber == choice) {
			eventMerchandise.push_back(merchandises[i]);
		}
	}

	// check any merchandise exists for this event
	if (eventMerchandise.empty()) {
		cout << "No merchandise available for " << eventName << "." << endl;
		cout << "\nPress enter to continue...";
		cin.ignore();
		cin.get();
		return;
	}

	cout << format("{:<7}{:<35}{:<13}{:>7}", "No.", "Product Name", "Price (RM)", "Stock") << "\n" << endl;

	// display filtered merchandise for the selected event
	for (int i = 0; i < eventMerchandise.size(); ++i) {
		cout << format("{:<7}{:<35}{:<13.2f}{:>7}", i + 1, eventMerchandise[i].productName, eventMerchandise[i].price, eventMerchandise[i].stockQuantity) << endl;
	}

	cout << "\nPress enter to continue...";
	cin.ignore();
	cin.get();
}

// users can addon merchandise with 10% discount applied
double createAddOn(vector<Merchandise>& merchandises, string& merchandiseDetails, int selectedEventNumber, string seatCategory) {

	double subtotal = 0.0;
	int choice, quantity;
	char confirmation;
	vector<string> purchaseDetails;
	double total;
	string detail;
	double finalPrice, discount;
	// retrive ticket price
	double ticketPrice = priceForCategory(seatCategory);
	int displayCount = 0;
	vector<int> index;

	for (int i = 0; i < merchandises.size(); i++) {
		if (merchandises[i].eventNumber == selectedEventNumber && merchandises[i].stockQuantity > 0) {
			displayCount++;
			index.push_back(i);
		}
	}

	if (index.empty()) {
		cout << "No merchandise available for this event" << endl;
		merchandiseDetails = "None";
		return 0.0;
	}
	else {
		cout << "\n=================== Available Merchandise ==================\n\n";
		cout << format("{:<5}{:<35}{:<13}{:>7}", "No.", "Product Name", "Price (RM)", "Stock") << "\n" << endl;
		for (int i = 0; i < index.size(); i++) {
			int merchandiseIndex = index[i];
			cout << format("{:<5}{:<35}{:<13.2f}{:>7}", i + 1, merchandises[merchandiseIndex].productName, merchandises[merchandiseIndex].price, merchandises[merchandiseIndex].stockQuantity) << endl;
		}
	}

	do {
		do {
			cout << "\n\nPlease select the merchandise(s) you wish to purchase: ";
			cin >> choice;
			if (choice >= 1 && choice <= index.size()) {
				break;
			}
			else {
				cout << "Invalid choice, please select number between 1-" << index.size() << endl;
				cin.clear();
				cin.ignore();
			}
		} while (true);

		int selectedIndex = index[choice - 1];

		do {
			cout << "Please enter the quantity: ";
			cin >> quantity;
			if (quantity > 0) {
				if (quantity <= merchandises[selectedIndex].stockQuantity) {
					break;
				}
				else {
					cout << "Insufficient stock! Only " << merchandises[selectedIndex].stockQuantity << " available now" << endl;
				}
			}
			else {
				cout << "Invalid quantity! Please enter a positive number" << endl;
				cin.clear();
				cin.ignore();
			}
		} while (true);

		total = quantity * merchandises[selectedIndex].price;
		subtotal += total;

		// update stock
		merchandises[selectedIndex].stockQuantity -= quantity;

		detail = format("{:<23}{:>4}{:>17.2f}{:>15.2f}", merchandises[selectedIndex].productName, quantity, merchandises[selectedIndex].price, total);
		purchaseDetails.push_back(detail);

		cout << "\nYour Cart:\n\n";
		cout << format("{:<23}{:>4}{:>17}{:>15}", "Item", "Qty", "Unit Price (RM)", "Total (RM)") << endl;
		cout << string(61, '-') << endl;
		cout << format("{:<23}{:>4}{:>17.2f}{:>15.2f}", seatCategory + " Ticket", "1", ticketPrice, ticketPrice) << endl;
		// update the items inside cart
		for (string cart : purchaseDetails) {
			cout << cart << endl;
		}

		cout << string(61, '-') << endl;

		do {
			cout << "\nAdd more items (Y/N): ";
			cin >> confirmation;

			if (confirmation == 'Y' || confirmation == 'y' || confirmation == 'N' || confirmation == 'n') {
				break;
			}
			else {
				cout << "Error: Please enter only Y or N!" << endl;
			}
		} while (true);

	} while (confirmation == 'Y' || confirmation == 'y');

	discount = subtotal * -0.1;
	finalPrice = subtotal + discount + ticketPrice;

	merchandiseDetails = "";
	for (int i = 0; i < purchaseDetails.size(); i++) {
		merchandiseDetails += purchaseDetails[i];
		if (i < purchaseDetails.size() - 1) {
			merchandiseDetails += "; ";
		}
	}

	cout << "\n==================== Purchase Summary =======================" << endl;
	cout << "\nItems purchased:\n\n";
	cout << format("{:<23}{:>4}{:>17}{:>15}", "Item", "Qty", "Unit Price (RM)", "Total (RM)") << endl;
	cout << "\n" << endl;
	cout << format("{:<23}{:>4}{:>17.2f}{:>15.2f}", seatCategory + " Ticket", "1", ticketPrice, ticketPrice) << endl;
	for (string& detail : purchaseDetails) {
		cout << detail << endl;
	}
	cout << "\n\n";
	cout << format("{:<30}{:>29.2f}", "Ticket Price (RM):", ticketPrice) << endl;
	cout << format("{:<30}{:>29.2f}", "Merchandise Subtotal (RM):", subtotal) << endl;
	cout << format("{:<30}{:>29.2f}", "Bundle Discount (10%): ", discount) << endl;
	cout << format("{:<30}{:>29.2f}", "Final Price (RM): ", finalPrice) << endl;
	return finalPrice;
}
