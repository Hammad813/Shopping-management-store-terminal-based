#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>
#include <map>
using namespace std;

bool idValidation(string idString)
{
    for (int i = 0; i < idString.size(); ++i)
    {
        if (!isdigit(idString[i]))
        {
            return false;
        }
    }
    if (idString.empty())
    {
        return false;
    }
    for (int i = 0; i < idString.size(); ++i)
    {
        if (idString[i] == ' ')
        {
            return false;
        }
    }
    return true;
}

bool stringValidation(string str)
{
    if (str.empty())
    {
        return false;
    }

    bool containSpacesOnly = false;
    for (int i = 0; i < str.size(); ++i)
    {
        if (str[i] != ' ')
        {
            containSpacesOnly = true;
            break;
        }
    }

    if (!containSpacesOnly)
    {
        return false;
    }

    return true;
}
bool adminStringValidation(string str)
{
    if (str.empty())
    {
        return false;
    }
    for (int i = 0; i < str.size(); ++i)
    {
        if (str[i] == ' ')
        {
            return false;
            break;
        }
    }
    return true;
}

class FileHandling // class to managme ids
{
protected:
    vector<string> userEmails;
    vector<string> userNames;
    vector<string> userPasswords;
    vector<string> newIDs;
    vector<string> oldIDs;
    string productId;
    vector<string> oldUserNames;
    vector<string> oldPasswords;

public:
    void writeNewId(string id)
    {
        ofstream outfile("IDFile.txt", ios_base::app);
        outfile << id << "\n";
        outfile.close();
    }

    void readOldIdDetails()
    {
        ifstream infile("IDFile.txt");
        string idLine;
        while (getline(infile, idLine))
        {
            oldIDs.push_back(idLine);
        }
        infile.close();
    }
    bool idVerification(string idString)
    {
        readOldIdDetails();
        for (int i = 0; i < oldIDs.size(); ++i)
        {
            if (idString == oldIDs[i])
            {
                return false;
            }
        }
        return true;
    }

    int newProductIdStore() // to store new product id
    {
        while (true)
        {
            cout << "\n\tEnter Product Id :\t";
            string productId;
            getline(cin, productId);

            // Check if productId is numeric and greater than 0
            if (idValidation(productId) && stoi(productId) > 0)
            {
                if (idVerification(productId))
                {
                    newIDs.push_back(productId);
                    writeNewId(productId);
                    return stoi(productId);
                }
                else
                {
                    cout << "\n\tThis product id already exists!";
                }
            }
            else
            {
                cout << "\n\tInvalid Product Id! Please enter a numeric ID greater than 0.";
            }
        }
    }
    void writeAdminDetails()
    {
        ofstream outfile("Admin File.txt", ios_base::trunc); // Clear the file before writing
        for (size_t i = 0; i < oldUserNames.size(); ++i)
        {
            outfile << oldUserNames[i] << " " << oldPasswords[i] << "\n";
        }
        outfile.close();
    }

    // Read admin details from the file
    void readAdminDetails()
    {
        ifstream infile("Admin File.txt");
        oldUserNames.clear();
        oldPasswords.clear();
        string adminRecordLine;
        while (getline(infile, adminRecordLine))
        {
            stringstream iss(adminRecordLine);
            string userName, password;
            iss >> userName >> password;
            oldUserNames.push_back(userName);
            oldPasswords.push_back(password);
        }
        infile.close();
    }
    void readUserDetails()
    {
        userEmails.clear();
        userNames.clear();
        userPasswords.clear();
        ifstream file("users.txt");
        string email, name, password;
        while (file >> email >> name >> password)
        {
            userEmails.push_back(email);
            userNames.push_back(name);
            userPasswords.push_back(password);
        }
        file.close();
    }

    void writeUserDetails(const string &email, const string &name, const string &password)
    {
        ofstream file("users.txt", ios::app);
        file << email << " " << name << " " << password << endl;
        file.close();
    }
};

class Product : public FileHandling // class to store products record
{
private:
    string name;
    string description;
    double price;
    int id;
    bool available;

public:
    // Constructor
    Product(string name = "", string description = "", double price = 0.0, int id = 0, bool available = true)
        : name(name), description(description), price(price), id(id), available(available) {}

    // Getter Methods
    string getName() const { return name; }
    string getDescription() const { return description; }
    double getPrice() const { return price; }
    int getId() const { return id; }
    bool isAvailable() const { return available; }

    // Setter Methods
    void setName(const string &newName) { name = newName; }
    void setDescription(const string &newDescription) { description = newDescription; }
    void setPrice(double newPrice) { price = newPrice; }
    void setAvailability(bool newAvailability) { available = newAvailability; }
};

class AllProducts // class to pent record
{
protected:
    int pantCount;
    int shirtCount;
    int suitCount;
    int frockCount;
    int shoeCount;
    int jewelryCount;

public:
    Product suitProducts[50];
    Product pantProducts[50];
    Product shirtProducts[50];
    Product frockProducts[50];
    Product shoeProducts[50];
    Product jewelryProducts[50];
    // AllProducts()
    // {
    //     pantProducts[0] = Product("Gray Cotton Pant", "Size: Small, Color: Gray", 700, 1001);
    //     pantProducts[1] = Product("Black Denim Pant", "Size: Medium, Color: Black", 750, 1002);
    //     pantProducts[2] = Product("Blue Jeans Pant", "Size: Large, Color: Blue", 800, 1003);
    //     pantProducts[3] = Product("Beige Chino Pant", "Size: Small, Color: Beige", 720, 1004);
    //     pantProducts[4] = Product("Khaki Cargo Pant", "Size: Large, Color: Khaki", 780, 1005);
    //     pantCount = 5;
    //     shirtProducts[0] = Product("Gray Cotton T-Shirt", "Size: Small, Color: Gray", 700, 2001);
    //     shirtProducts[1] = Product("White Linen Shirt", "Size: Medium, Color: White", 750, 2002);
    //     shirtProducts[2] = Product("Blue Denim Shirt", "Size: Large, Color: Blue", 800, 2003);
    //     shirtProducts[3] = Product("Black Polo T-Shirt", "Size: Small, Color: Black", 720, 2004);
    //     shirtProducts[4] = Product("Red Checkered Shirt", "Size: Large, Color: Red", 780, 2005);
    //     shirtCount = 5;
    //     suitProducts[0] = Product("Navy Blue 3-Piece Suit", "Includes Coat, Vest, Pants", 2000, 3001);
    //     suitProducts[1] = Product("Black Tuxedo Suit", "Includes Coat, Pants, Bowtie", 2500, 3002);
    //     suitProducts[2] = Product("Gray Slim Fit Suit", "Includes Coat, Pants", 1800, 3003);
    //     suitProducts[3] = Product("Brown Tweed Suit", "Includes Coat, Pants", 2200, 3004);
    //     suitProducts[4] = Product("Blue Pinstripe Suit", "Includes Coat, Pants", 1900, 3005);
    //     suitCount = 5;
    //     shoeProducts[0] = Product("Black Leather Heels", "Size: 7, Color: Black", 900, 5001);
    //     shoeProducts[1] = Product("White Sneakers", "Size: 8, Color: White", 800, 5002);
    //     shoeProducts[2] = Product("Red Ballet Flats", "Size: 6, Color: Red", 700, 5003);
    //     shoeProducts[3] = Product("Blue Wedge Sandals", "Size: 9, Color: Blue", 1000, 5004);
    //     shoeProducts[4] = Product("Pink Slippers", "Size: 7, Color: Pink", 600, 5005);
    //     shoeCount = 5;
    //     frockProducts[0] = Product("Pink Floral Frock", "Size: Small, Color: Pink", 1200, 4001);
    //     frockProducts[1] = Product("Blue Party Frock", "Size: Medium, Color: Blue", 1500, 4002);
    //     frockProducts[2] = Product("Yellow Summer Frock", "Size: Large, Color: Yellow", 1100, 4003);
    //     frockProducts[3] = Product("White Lace Frock", "Size: Small, Color: White", 1300, 4004);
    //     frockProducts[4] = Product("Red Polka Dot Frock", "Size: Medium, Color: Red", 1400, 4005);
    //     frockCount = 5;
    //     jewelryProducts[0] = Product("Gold Necklace Set", "Includes Necklace, Earrings", 3000, 6001);
    //     jewelryProducts[1] = Product("Silver Bracelet Set", "Includes Bracelet, Ring", 2500, 6002);
    //     jewelryProducts[2] = Product("Pearl Earrings Set", "Includes Earrings, Hairpin", 2800, 6003);
    //     jewelryProducts[3] = Product("Diamond Pendant Set", "Includes Pendant, Chain", 3500, 6004);
    //     jewelryProducts[4] = Product("Ruby Bangle Set", "Includes Bangles, Anklet", 3200, 6005);
    //     jewelryCount = 5;
    // }

    // Getter methods for product counts
    int getPantCount() const { return pantCount; }
    int getShirtCount() const { return shirtCount; }
    int getSuitCount() const { return suitCount; }
    int getFrockCount() const { return frockCount; }
    int getShoeCount() const { return shoeCount; }
    int getJewelryCount() const { return jewelryCount; }
    void saveAllProductsToFile()
    {
        // Helper function to save a product array
        auto saveProductsToFile = [](const string &fileName, Product products[], int count)
        {
            ofstream file(fileName, ios::trunc);
            if (file)
            {
                for (int i = 0; i < count; ++i)
                {
                    file << products[i].getId() << "|"
                         << products[i].getName() << "|"
                         << products[i].getDescription() << "|"
                         << products[i].getPrice() << "|"
                         << products[i].isAvailable() << endl;
                }
                file.close();
            }
            else
            {
                cout << "Error: Could not open file " << fileName << " for writing." << endl;
            }
        };

        // Save all product categories
        saveProductsToFile("Pants.txt", pantProducts, pantCount);
        saveProductsToFile("Shirts.txt", shirtProducts, shirtCount);
        saveProductsToFile("Suits.txt", suitProducts, suitCount);
        saveProductsToFile("Frocks.txt", frockProducts, frockCount);
        saveProductsToFile("Shoes.txt", shoeProducts, shoeCount);
        saveProductsToFile("Jewelry.txt", jewelryProducts, jewelryCount);
    }
    void loadAllProductsFromFile()
    {
        // Helper function to validate double
        auto isValidDouble = [](const string &str) -> bool
        {
            if (str.empty())
                return false;
            bool hasDecimal = false;
            for (char c : str)
            {
                if (isdigit(c))
                    continue;
                if (c == '.' && !hasDecimal)
                {
                    hasDecimal = true;
                    continue;
                }
                return false;
            }
            return true;
        };

        // Helper function to load products from a file
        auto loadProductsFromFile = [&](const string &fileName, Product products[], int &count, int maxCount)
        {
            ifstream file(fileName);
            if (file)
            {
                string line;
                count = 0; // Reset count before loading
                while (getline(file, line))
                {
                    stringstream ss(line);
                    string idStr, name, desc, priceStr, availStr;

                    getline(ss, idStr, '|');
                    getline(ss, name, '|');
                    getline(ss, desc, '|');
                    getline(ss, priceStr, '|');
                    getline(ss, availStr, '|');

                    try
                    {
                        // Validate and parse fields
                        int id = stoi(idStr);
                        if (!isValidDouble(priceStr))
                            throw std::invalid_argument("Invalid price");
                        double price = stod(priceStr);
                        bool available = (availStr == "1");

                        // Add product to array
                        if (count < maxCount)
                        {
                            products[count++] = Product(name, desc, price, id, available);
                        }
                        else
                        {
                            cout << "Error: Maximum product count exceeded in " << fileName << endl;
                        }
                    }
                    catch (const std::exception &e)
                    {
                        cout << "Error parsing line in " << fileName << ": " << line << " - " << e.what() << endl;
                    }
                }
                file.close();
            }
            else
            {
                cout << "Error: Could not open file " << fileName << endl;
            }
        };
        // Load all product categories
        loadProductsFromFile("Pants.txt", pantProducts, pantCount, 50);
        loadProductsFromFile("Shirts.txt", shirtProducts, shirtCount, 50);
        loadProductsFromFile("Suits.txt", suitProducts, suitCount, 50);
        loadProductsFromFile("Frocks.txt", frockProducts, frockCount, 50);
        loadProductsFromFile("Shoes.txt", shoeProducts, shoeCount, 50);
        loadProductsFromFile("Jewelry.txt", jewelryProducts, jewelryCount, 50);
    }

    void allGentsProductDisplay() const
    {
        userPantDisplay();
        userShirtDisplay();
        userSuitDisplay();
    }
    void allLadiesProductDisplay() const
    {
        userFrockDisplay();
        userShoeDisplay();
        userJewelryDisplay();
    }
    void allProductsAdminRecord() const
    {
        displayAdminGentsRecord();
        displayAdminLadiesRecord();
    }
    void displayUserGentsShirts() const
    {
        userShirtDisplay();
    }

    void displayUserGentsPants() const
    {
        userPantDisplay();
    }

    void displayUserGentsSuits() const
    {
        userSuitDisplay();
    }

    void displayAdminGentsRecord() const
    {
        adminPantDisplay();
        adminShirtDisplay();
        adminSuitDisplay();
    }
    void userPantDisplay() const
    {
        cout << "\n\n\tGents Available Pants:";
        for (int i = 0; i < pantCount; i++)
        {
            if (pantProducts[i].isAvailable())
            {
                cout << "\n\n\tName: " << pantProducts[i].getName();
                cout << "\n\tDescription: " << pantProducts[i].getDescription();
                cout << "\n\tPrice: " << pantProducts[i].getPrice();
                cout << "\n\tID: " << pantProducts[i].getId() << endl;
            }
        }
    }
    void adminPantDisplay() const
    {
        cout << "\n\n\tAdmin - Gents Available Pants:";

        for (int i = 0; i < pantCount; i++)
        {
            cout << "\n\n\tName: " << pantProducts[i].getName();
            cout << "\n\tPrice: " << pantProducts[i].getPrice();
            cout << "\n\tID: " << pantProducts[i].getId();
            cout << "\n\tAvailability: " << (pantProducts[i].isAvailable() ? "Available" : "Not Available") << endl;
        }
    }

    void addMultiplePants()
    {
        int numPantsToAdd;
        cout << "\n\tAvailable Pents in Store : " << pantCount;
        while (true)
        {
            string stringNum;
            cout << "\n\tHow many pants do you want to add more: ";
            getline(cin, stringNum);
            if (idValidation(stringNum))
            {
                if ((stoi(stringNum) + pantCount) <= 50)
                {
                    numPantsToAdd = stoi(stringNum);
                    break;
                }
                else
                {
                    cout << "\n\tMaximum 50 Pants can store only";
                }
            }
            cout << "\n\tInvalid number!";
        }
        for (int i = 0; i < numPantsToAdd; ++i)
        {
            string name, description;
            double price;
            int id;
            cout << "\n\n\tEnter Pant " << (i + 1) << " details:\n";
            while (true)
            {
                cout << "\tName :\t";
                getline(cin, name);
                if (stringValidation(name))
                {
                    break;
                }
                cout << "\n\tInvalid Pent Name!\n";
            }
            while (true)
            {
                cout << "\tDescription: ";
                getline(cin, description);
                if (stringValidation(description))
                {
                    break;
                }
                cout << "\n\tInvalid Pant Description!\n";
            }
            while (true)
            {
                string stringPrice;
                cout << "\tPrice:\t\t";
                getline(cin, stringPrice);
                if (idValidation(stringPrice))
                {
                    price = stod(stringPrice);
                    break;
                }
                cout << "\n\tInvalid Price!\n";
            }
            id = pantProducts->newProductIdStore();
            if (pantCount < 50)
            {
                pantProducts[pantCount++] = Product(name, description, price, id);
                cout << "\n\tPant added successfully!\n";
                // Save changes to the file
                saveAllProductsToFile();
            }
            else
            {
                cout << "\n\tMaximum number of pants reached!\n";
                break;
            }
        }
    }

    void userShirtDisplay() const
    {
        cout << "\n\n\tGents Available Shirts:";
        for (int i = 0; i < shirtCount; i++)
        {
            if (shirtProducts[i].isAvailable())
            {
                cout << "\n\n\tName: " << shirtProducts[i].getName();
                cout << "\n\tDescription: " << shirtProducts[i].getDescription();
                cout << "\n\tPrice: " << shirtProducts[i].getPrice();
                cout << "\n\tID: " << shirtProducts[i].getId() << endl;
            }
        }
    }

    void adminShirtDisplay() const
    {
        cout << "\n\n\tAdmin - Gents Available Shirts:";
        for (int i = 0; i < shirtCount; i++)
        {
            cout << "\n\n\tName: " << shirtProducts[i].getName();
            cout << "\n\tPrice: " << shirtProducts[i].getPrice();
            cout << "\n\tID: " << shirtProducts[i].getId();
            cout << "\n\tAvailability: " << (shirtProducts[i].isAvailable() ? "Available" : "Not Available") << endl;
        }
    }

    void addMultipleShirts()
    {
        int numShirtsToAdd;
        cout << "\n\tAvailable Shirts in Store : " << shirtCount;
        while (true)
        {
            string stringNum;
            cout << "\n\tHow many shirts do you want to add more: ";
            getline(cin, stringNum);
            if (idValidation(stringNum))
            {
                if ((stoi(stringNum) + shirtCount) <= 50)
                {
                    numShirtsToAdd = stoi(stringNum);
                    break;
                }
                else
                {
                    cout << "\n\tMaximum 50 Shirts can be stored only";
                }
            }
            cout << "\n\tInvalid number!";
        }
        for (int i = 0; i < numShirtsToAdd; ++i)
        {
            string name, description;
            double price;
            int id;
            cout << "\n\n\tEnter Shirt " << (i + 1) << " details:\n";
            while (true)
            {
                cout << "\tName :\t";
                getline(cin, name);
                if (stringValidation(name))
                {
                    break;
                }
                cout << "\n\tInvalid Shirt Name!\n";
            }
            while (true)
            {
                cout << "\tDescription: ";
                getline(cin, description);
                if (stringValidation(description))
                {
                    break;
                }
                cout << "\n\tInvalid Shirt Description!\n";
            }
            while (true)
            {
                string stringPrice;
                cout << "\tPrice:\t\t";
                getline(cin, stringPrice);
                if (idValidation(stringPrice))
                {
                    price = stod(stringPrice);
                    break;
                }
                cout << "\n\tInvalid Price!\n";
            }
            id = shirtProducts->newProductIdStore();
            if (shirtCount < 50)
            {
                shirtProducts[shirtCount++] = Product(name, description, price, id);
                cout << "\n\tShirt added successfully!\n";
                saveAllProductsToFile();
            }
            else
            {
                cout << "\n\tMaximum number of shirts reached!\n";
                break;
            }
        }
    }
    void userSuitDisplay() const
    {
        cout << "\n\n\tGents Available Suits:";
        for (int i = 0; i < suitCount; i++)
        {
            if (suitProducts[i].isAvailable())
            {
                cout << "\n\n\tName: " << suitProducts[i].getName();
                cout << "\n\tDescription: " << suitProducts[i].getDescription();
                cout << "\n\tPrice: " << suitProducts[i].getPrice();
                cout << "\n\tID: " << suitProducts[i].getId() << endl;
            }
        }
    }

    void adminSuitDisplay() const
    {
        cout << "\n\n\tAdmin - Gents Available Suits:";
        for (int i = 0; i < suitCount; i++)
        {
            cout << "\n\n\tName: " << suitProducts[i].getName();
            cout << "\n\tPrice: " << suitProducts[i].getPrice();
            cout << "\n\tID: " << suitProducts[i].getId();
            cout << "\n\tAvailability: " << (suitProducts[i].isAvailable() ? "Available" : "Not Available") << endl;
        }
    }

    void addMultipleSuits()
    {
        int numSuitsToAdd;
        cout << "\n\tAvailable Suits in Store : " << suitCount;
        while (true)
        {
            string stringNum;
            cout << "\n\tHow many suits do you want to add more: ";
            getline(cin, stringNum);
            if (idValidation(stringNum))
            {
                if ((stoi(stringNum) + suitCount) <= 50)
                {
                    numSuitsToAdd = stoi(stringNum);
                    break;
                }
                else
                {
                    cout << "\n\tMaximum 50 Suits can be stored only";
                }
            }
            cout << "\n\tInvalid number!";
        }
        for (int i = 0; i < numSuitsToAdd; ++i)
        {
            string name, description;
            double price;
            int id;
            cout << "\n\n\tEnter Suit " << (i + 1) << " details:\n";
            while (true)
            {
                cout << "\tName :\t";
                getline(cin, name);
                if (stringValidation(name))
                {
                    break;
                }
                cout << "\n\tInvalid Suit Name!\n";
            }
            while (true)
            {
                cout << "\tDescription: ";
                getline(cin, description);
                if (stringValidation(description))
                {
                    break;
                }
                cout << "\n\tInvalid Suit Description!\n";
            }
            while (true)
            {
                string stringPrice;
                cout << "\tPrice:\t\t";
                getline(cin, stringPrice);
                if (idValidation(stringPrice))
                {
                    price = stod(stringPrice);
                    break;
                }
                cout << "\n\tInvalid Price!\n";
            }
            id = suitProducts->newProductIdStore();
            if (suitCount < 50)
            {
                suitProducts[suitCount++] = Product(name, description, price, id);
                cout << "\n\tSuit added successfully!\n";
                saveAllProductsToFile();
            }
            else
            {
                cout << "\n\tMaximum number of suits reached!\n";
                break;
            }
        }
    }
    void displayUserLadiesFrocks() const
    {
        userFrockDisplay();
    }

    void displayUserLadiesShoes() const
    {
        userShoeDisplay();
    }

    void displayUserLadiesJewelrySets() const
    {
        userJewelryDisplay();
    }
    void displayAdminLadiesRecord() const
    {
        adminFrockDisplay();
        adminShoeDisplay();
        adminJewelryDisplay();
    }
    void userFrockDisplay() const
    {
        cout << "\n\n\tLadies Available Frocks:";
        for (int i = 0; i < frockCount; i++)
        {
            if (frockProducts[i].isAvailable())
            {
                cout << "\n\n\tName: " << frockProducts[i].getName();
                cout << "\n\tDescription: " << frockProducts[i].getDescription();
                cout << "\n\tPrice: " << frockProducts[i].getPrice();
                cout << "\n\tID: " << frockProducts[i].getId() << endl;
            }
        }
    }

    void adminFrockDisplay() const
    {
        cout << "\n\n\tAdmin - Ladies Available Frocks:";
        for (int i = 0; i < frockCount; i++)
        {
            cout << "\n\n\tName: " << frockProducts[i].getName();
            cout << "\n\tPrice: " << frockProducts[i].getPrice();
            cout << "\n\tID: " << frockProducts[i].getId();
            cout << "\n\tAvailability: " << (frockProducts[i].isAvailable() ? "Available" : "Not Available") << endl;
        }
    }

    void addMultipleFrocks()
    {
        int numFrocksToAdd;
        cout << "\n\tAvailable Frocks in Store : " << frockCount;
        while (true)
        {
            string stringNum;
            cout << "\n\tHow many frocks do you want to add more: ";
            getline(cin, stringNum);
            if (idValidation(stringNum))
            {
                if ((stoi(stringNum) + frockCount) <= 50)
                {
                    numFrocksToAdd = stoi(stringNum);
                    break;
                }
                else
                {
                    cout << "\n\tMaximum 50 Frocks can be stored only";
                }
            }
            cout << "\n\tInvalid number!";
        }
        for (int i = 0; i < numFrocksToAdd; ++i)
        {
            string name, description;
            double price;
            int id;
            cout << "\n\n\tEnter Frock " << (i + 1) << " details:\n";
            while (true)
            {
                cout << "\tName :\t";
                getline(cin, name);
                if (stringValidation(name))
                {
                    break;
                }
                cout << "\n\tInvalid Frock Name!\n";
            }
            while (true)
            {
                cout << "\tDescription: ";
                getline(cin, description);
                if (stringValidation(description))
                {
                    break;
                }
                cout << "\n\tInvalid Frock Description!\n";
            }
            while (true)
            {
                string stringPrice;
                cout << "\tPrice:\t\t";
                getline(cin, stringPrice);
                if (idValidation(stringPrice))
                {
                    price = stod(stringPrice);
                    break;
                }
                cout << "\n\tInvalid Price!\n";
            }
            id = frockProducts->newProductIdStore();
            if (frockCount < 50)
            {
                frockProducts[frockCount++] = Product(name, description, price, id);
                cout << "\n\tFrock added successfully!\n";
                saveAllProductsToFile();
            }
            else
            {
                cout << "\n\tMaximum number of frocks reached!\n";
                break;
            }
        }
    }
    void userShoeDisplay() const
    {
        cout << "\n\n\tLadies Available Shoes:";
        for (int i = 0; i < shoeCount; i++)
        {
            if (shoeProducts[i].isAvailable())
            {
                cout << "\n\n\tName: " << shoeProducts[i].getName();
                cout << "\n\tDescription: " << shoeProducts[i].getDescription();
                cout << "\n\tPrice: " << shoeProducts[i].getPrice();
                cout << "\n\tID: " << shoeProducts[i].getId() << endl;
            }
        }
    }

    void adminShoeDisplay() const
    {
        cout << "\n\n\tAdmin - Ladies Available Shoes:";
        for (int i = 0; i < shoeCount; i++)
        {
            cout << "\n\n\tName: " << shoeProducts[i].getName();
            cout << "\n\tPrice: " << shoeProducts[i].getPrice();
            cout << "\n\tID: " << shoeProducts[i].getId();
            cout << "\n\tAvailability: " << (shoeProducts[i].isAvailable() ? "Available" : "Not Available") << endl;
        }
    }

    void addMultipleShoes()
    {
        int numShoesToAdd;
        cout << "\n\tAvailable Shoes in Store : " << shoeCount;
        while (true)
        {
            string stringNum;
            cout << "\n\tHow many shoes do you want to add more: ";
            getline(cin, stringNum);
            if (idValidation(stringNum))
            {
                if ((stoi(stringNum) + shoeCount) <= 50)
                {
                    numShoesToAdd = stoi(stringNum);
                    break;
                }
                else
                {
                    cout << "\n\tMaximum 50 Shoes can be stored only";
                }
            }
            cout << "\n\tInvalid number!";
        }
        for (int i = 0; i < numShoesToAdd; ++i)
        {
            string name, description;
            double price;
            int id;
            cout << "\n\n\tEnter Shoe " << (i + 1) << " details:\n";
            while (true)
            {
                cout << "\tName :\t";
                getline(cin, name);
                if (stringValidation(name))
                {
                    break;
                }
                cout << "\n\tInvalid Shoe Name!\n";
            }
            while (true)
            {
                cout << "\tDescription: ";
                getline(cin, description);
                if (stringValidation(description))
                {
                    break;
                }
                cout << "\n\tInvalid Shoe Description!\n";
            }
            while (true)
            {
                string stringPrice;
                cout << "\tPrice:\t\t";
                getline(cin, stringPrice);
                if (idValidation(stringPrice))
                {
                    price = stod(stringPrice);
                    break;
                }
                cout << "\n\tInvalid Price!\n";
            }
            id = shoeProducts->newProductIdStore();
            if (shoeCount < 50)
            {
                shoeProducts[shoeCount++] = Product(name, description, price, id);
                cout << "\n\tShoe added successfully!\n";
                saveAllProductsToFile();
            }
            else
            {
                cout << "\n\tMaximum number of shoes reached!\n";
                break;
            }
        }
    }
    void userJewelryDisplay() const
    {
        cout << "\n\n\tLadies Available Jewelry Sets:";
        for (int i = 0; i < jewelryCount; i++)
        {
            if (jewelryProducts[i].isAvailable())
            {
                cout << "\n\n\tName: " << jewelryProducts[i].getName();
                cout << "\n\tDescription: " << jewelryProducts[i].getDescription();
                cout << "\n\tPrice: " << jewelryProducts[i].getPrice();
                cout << "\n\tID: " << jewelryProducts[i].getId() << endl;
            }
        }
    }

    void adminJewelryDisplay() const
    {
        cout << "\n\n\tAdmin - Ladies Available Jewelry Sets:";
        for (int i = 0; i < jewelryCount; i++)
        {
            cout << "\n\n\tName: " << jewelryProducts[i].getName();
            cout << "\n\tPrice: " << jewelryProducts[i].getPrice();
            cout << "\n\tID: " << jewelryProducts[i].getId();
            cout << "\n\tAvailability: " << (jewelryProducts[i].isAvailable() ? "Available" : "Not Available") << endl;
        }
    }

    void addMultipleJewelrySets()
    {
        int numJewelrySetsToAdd;
        cout << "\n\tAvailable Jewelry Sets in Store : " << jewelryCount;
        while (true)
        {
            string stringNum;
            cout << "\n\tHow many jewelry sets do you want to add more: ";
            getline(cin, stringNum);
            if (idValidation(stringNum))
            {
                if ((stoi(stringNum) + jewelryCount) <= 50)
                {
                    numJewelrySetsToAdd = stoi(stringNum);
                    break;
                }
                else
                {
                    cout << "\n\tMaximum 50 Jewelry Sets can be stored only";
                }
            }
            cout << "\n\tInvalid number!";
        }
        for (int i = 0; i < numJewelrySetsToAdd; ++i)
        {
            string name, description;
            double price;
            int id;
            cout << "\n\n\tEnter Jewelry Set " << (i + 1) << " details:\n";
            while (true)
            {
                cout << "\tName :\t";
                getline(cin, name);
                if (stringValidation(name))
                {
                    break;
                }
                cout << "\n\tInvalid Jewelry Set Name!\n";
            }
            while (true)
            {
                cout << "\tDescription: ";
                getline(cin, description);
                if (stringValidation(description))
                {
                    break;
                }
                cout << "\n\tInvalid Jewelry Set Description!\n";
            }
            while (true)
            {
                string stringPrice;
                cout << "\tPrice:\t\t";
                getline(cin, stringPrice);
                if (idValidation(stringPrice))
                {
                    price = stod(stringPrice);
                    break;
                }
                cout << "\n\tInvalid Price!\n";
            }
            id = jewelryProducts->newProductIdStore();
            if (jewelryCount < 50)
            {
                jewelryProducts[jewelryCount++] = Product(name, description, price, id);
                cout << "\n\tJewelry Set added successfully!\n";
                saveAllProductsToFile();
            }
            else
            {
                cout << "\n\tMaximum number of Jewelry Sets reached!\n";
                break;
            }
        }
    }
};

class AdminLogin : protected FileHandling
{
private:
    string name;
    string password;

public:
    // string getName()
    // {
    //     return name;
    // }
    bool oldAdminLogin()
    {
        readAdminDetails();
        system("cls");
        int attempts = 0;

        while (attempts < 3)
        {
            cout << "\n\tAdmin Login\n";
            while (true)
            {
                cout << "\n\tEnter Admin Username :\t";
                getline(cin, name);
                if (adminStringValidation(name))
                {
                    break;
                }
                cout << "\n\tInvalid name!";
            }

            // Check if the username exists
            for (int i = 0; i < oldUserNames.size(); ++i)
            {
                if (name == oldUserNames[i])
                {
                    while (true)
                    {
                        cout << "\tEnter Admin Password :\t";
                        getline(cin, password);
                        if (adminStringValidation(password))
                        {
                            break;
                        }
                        cout << "\n\tInvalid Input!\n";
                    }

                    // If the password matches, set the admin name and return true
                    if (password == oldPasswords[i])
                    {
                        // Set the admin name here
                        cout << "\n\tAdmin Log-In ";
                        for (int i = 0; i < 5; i++)
                        {
                            cout << ".";
                            Sleep(400);
                        }
                        cout << "\n\tLog-In Successful!";
                        return true;
                    }
                    else
                    {
                        cout << "\n\tInvalid Password!";
                        attempts++;
                        if (attempts >= 3)
                        {
                            cout << "\n\tToo many failed attempts. Returning to main menu.";
                            return false;
                        }
                        cout << "\n\tAttempt " << attempts << " of 3.\n";
                    }
                }
            }

            system("cls");
            cout << "\n\tAdmin Not Found!";
            attempts++;
            if (attempts >= 3)
            {
                cout << "\n\tToo many failed attempts. Returning to main menu.";
                return false;
            }
            cout << "\n\tAttempt " << attempts << " of 3.\n";
        }

        return false;
    }

    void newAdminRegistration()
    {
        system("cls");
        cout << "\n\tAdmin Registration\n";
        while (true)
        {
            cout << "\n\tEnter Admin Username :\t";
            getline(cin, name);
            if (adminStringValidation(name))
            {
                readAdminDetails();
                bool found = false;
                for (int i = 0; i < oldUserNames.size(); ++i)
                {
                    if (name == oldUserNames[i])
                    {
                        found = true;
                        break;
                    }
                }
                if (found)
                {
                    cout << "\n\tAdmin username already exists!";
                }
                else
                {
                    break;
                }
            }
            else
            {
                cout << "\n\tInvalid User name!";
            }
        }

        while (true)
        {
            cout << "\tEnter Admin Password :\t";
            getline(cin, password);
            if (adminStringValidation(password))
            {
                break;
            }
            cout << "\n\tInvalid Input!\n";
        }

        // Now add the new admin to the vectors
        oldUserNames.push_back(name);
        oldPasswords.push_back(password);

        // Write all admin details back to the file (overwrite the file)
        writeAdminDetails();
        cout << "\n\tRegistration ";
        for (int i = 0; i < 5; i++)
        {
            cout << ".";
            Sleep(400);
        }
        cout << "\n\tRegistration Successful!";
    }

    void removeAdmin()
    {
        system("cls");
        cout << "\n\tRemove Admin\n";

        string usernameToRemove, passwordToRemove;
        int attempts = 3;

        // Attempt to verify admin identity for 3 times
        while (attempts > 0)
        {
            cout << "\n\tEnter Admin Username: ";
            getline(cin, usernameToRemove);

            cout << "\tEnter Admin Password: ";
            getline(cin, passwordToRemove);

            readAdminDetails();

            // Check if the username and password match
            for (int i = 0; i < oldUserNames.size(); ++i)
            {
                if (usernameToRemove == oldUserNames[i] && passwordToRemove == oldPasswords[i])
                {
                    // Found the admin to be removed
                    oldUserNames.erase(oldUserNames.begin() + i);
                    oldPasswords.erase(oldPasswords.begin() + i);

                    // Update the admin file after removal
                    writeAdminDetails();
                    cout << "\n\tAdmin Removed Successfully!";
                    return;
                }
            }

            // If not found, reduce the attempts
            attempts--;
            cout << "\n\tInvalid username or password! You have " << attempts << " attempt(s) left.\n";
        }

        // If all attempts are exhausted
        cout << "\n\tFailed to remove admin. Please try again later.\n";
    }
};

bool searchingLoop(string searchCriteria, AllProducts &allProducts);
bool deleteLoop(int productId, AllProducts &allProducts);

class CartBuyAndCheckOut
{
protected:
    struct UserCart
    {
        int cartItemsId = 0;
        int soldItemsId = 0;
        string customerName;
        double paidPayment[50];
        double totalPaidPayment = 0;
        int quantityOfSoldsItems[50];
        Product cartProduct[50];
        Product soldProduct[50];
    };

    map<string, UserCart> userCarts;

public:
    CartBuyAndCheckOut() {}

    void addCart(const string &userEmail, int id, AllProducts &allProducts)
    {
        if (userCarts[userEmail].cartItemsId < 50)
        {
            bool productAdded = false;

            // Check in pant products
            for (int i = 0; i < allProducts.getPantCount(); ++i)
            {
                if (allProducts.pantProducts[i].getId() == id)
                {
                    userCarts[userEmail].cartProduct[userCarts[userEmail].cartItemsId] = allProducts.pantProducts[i];
                    productAdded = true;
                    break;
                }
            }

            // Check in shirt products
            if (!productAdded)
            {
                for (int i = 0; i < allProducts.getShirtCount(); ++i)
                {
                    if (allProducts.shirtProducts[i].getId() == id)
                    {
                        userCarts[userEmail].cartProduct[userCarts[userEmail].cartItemsId] = allProducts.shirtProducts[i];
                        productAdded = true;
                        break;
                    }
                }
            }

            // Check in suit products
            if (!productAdded)
            {
                for (int i = 0; i < allProducts.getSuitCount(); ++i)
                {
                    if (allProducts.suitProducts[i].getId() == id)
                    {
                        userCarts[userEmail].cartProduct[userCarts[userEmail].cartItemsId] = allProducts.suitProducts[i];
                        productAdded = true;
                        break;
                    }
                }
            }

            // Check in frock products
            if (!productAdded)
            {
                for (int i = 0; i < allProducts.getFrockCount(); ++i)
                {
                    if (allProducts.frockProducts[i].getId() == id)
                    {
                        userCarts[userEmail].cartProduct[userCarts[userEmail].cartItemsId] = allProducts.frockProducts[i];
                        productAdded = true;
                        break;
                    }
                }
            }

            // Check in shoe products
            if (!productAdded)
            {
                for (int i = 0; i < allProducts.getShoeCount(); ++i)
                {
                    if (allProducts.shoeProducts[i].getId() == id)
                    {
                        userCarts[userEmail].cartProduct[userCarts[userEmail].cartItemsId] = allProducts.shoeProducts[i];
                        productAdded = true;
                        break;
                    }
                }
            }

            // Check in jewelry products
            if (!productAdded)
            {
                for (int i = 0; i < allProducts.getJewelryCount(); ++i)
                {
                    if (allProducts.jewelryProducts[i].getId() == id)
                    {
                        userCarts[userEmail].cartProduct[userCarts[userEmail].cartItemsId] = allProducts.jewelryProducts[i];
                        productAdded = true;
                        break;
                    }
                }
            }

            if (productAdded)
            {
                userCarts[userEmail].cartItemsId++;
            }
            else
            {
                cout << "\n\tProduct with ID " << id << " not found.";
            }
        }
        else
        {
            cout << "\n\tYour Product Cart limit is full";
        }
    }
    void showCart(const string &userEmail, AllProducts &allProducts)
    {
        if (userCarts[userEmail].cartItemsId == 0)
        {
            cout << "\n\tYour cart is empty." << endl;
        }
        else
        {
            // system("cls");
            cout << "\n\tItems in your cart: " << userCarts[userEmail].cartItemsId;
            for (int i = 0; i < userCarts[userEmail].cartItemsId; ++i)
            {
                cout << "\n\n\tProduct ID: " << userCarts[userEmail].cartProduct[i].getId();
                cout << "\n\tProduct Name: " << userCarts[userEmail].cartProduct[i].getName();
                cout << "\n\tProduct Price: " << userCarts[userEmail].cartProduct[i].getPrice();
            }
        }
    }

    void clearCart(const string &userEmail)
    {
        userCarts[userEmail].cartItemsId = 0;
    }
    void clearPaymentRecord(const string &userEmail)
    {
        userCarts[userEmail].soldItemsId = 0;
        userCarts[userEmail].totalPaidPayment = 0;
        cout << "\n\tPayment Record cleared successfully for " << userEmail;
    }
    // int getCartId()
    // {
    //     return cartItemsId;
    // }
    double calculateTotalBill(const string &userEmail)
    {
        double totalBill = 0.0;
        for (int i = 0; i < userCarts[userEmail].cartItemsId; ++i)
        {
            totalBill += userCarts[userEmail].cartProduct[i].getPrice();
        }
        return totalBill;
    }

    void payBill(const string &userEmail, double totalBill)
    {
        while (true)
        {
            cout << "\n\n\tTotal bill: " << totalBill << " Pkr";
            string stringAmount;
            while (true)
            {
                cout << "\n\tEnter the amount to pay: ";
                getline(cin, stringAmount);
                if (idValidation(stringAmount))
                {
                    break;
                }
                cout << "\n\tInvalid Amount!";
            }
            double amountPaid = stod(stringAmount);
            if (amountPaid >= totalBill)
            {
                double change = amountPaid - totalBill;
                while (true)
                {
                    cout << "\n\tPlease Enter Your Name : ";
                    getline(cin, userCarts[userEmail].customerName);
                    if (stringValidation(userCarts[userEmail].customerName))
                    {
                        break;
                    }
                    cout << "\n\tInvalid Name!";
                }
                userCarts[userEmail].paidPayment[userCarts[userEmail].soldItemsId] = totalBill;
                userCarts[userEmail].totalPaidPayment += totalBill;
                userCarts[userEmail].quantityOfSoldsItems[userCarts[userEmail].soldItemsId] = userCarts[userEmail].cartItemsId;
                userCarts[userEmail].soldProduct[userCarts[userEmail].soldItemsId] = userCarts[userEmail].cartProduct[userCarts[userEmail].cartItemsId];
                userCarts[userEmail].soldItemsId++;
                cout << "\n\tChange: " << change << " Pkr\n";
                cout << "\n\tHappy Shopping";
                clearCart(userEmail);
                break;
            }
            else
            {
                cout << "\n\tInsufficient amount. Please pay the total bill amount.\n";
            }
        }
    }
    void buyProduct(const string &userEmail, AllProducts &allProducts)
    {
        string searchCriteria;
        while (true)
        {
            cout << "\n\tSearch a Product to buy (Name, Description, Id): ";
            getline(cin, searchCriteria);
            if (stringValidation(searchCriteria) && searchCriteria != "0")
            {
                break;
            }
            cout << "\n\tInvalid Input! Please try again." << endl;
        }
        bool found = false;
        found = searchingLoop(searchCriteria, allProducts);
        if (found)
        {
            string searchBuy;
            while (true)
            {
                cout << "\n\tEnter id of Product that you want to buy : ";
                getline(cin, searchBuy);
                if (idValidation(searchBuy) && searchBuy != "0")
                {
                    break;
                }
                cout << "\n\tInvalid ID!";
            }
            found = false;
            found = searchingLoop(searchBuy, allProducts);
            if (found)
            {
                // system("cls");
                cout << "\n\tProduct Added Successfully to Cart";
                addCart(userEmail, stoi(searchBuy), allProducts);
            }
        }
        if (!found)
        {
            cout << "\n\tNo matching product found.\n";
        }
    }

    void cancelOrder(const string &userEmail, int id)
    {
        if (userCarts[userEmail].cartItemsId == 0)
        {
            cout << "\n\tYour cart is empty. No orders to cancel." << endl;
        }
        else
        {
            int index = -1;
            for (int i = 0; i < userCarts[userEmail].cartItemsId; ++i)
            {
                if (userCarts[userEmail].cartProduct[i].getId() == id)
                {
                    index = i;
                    break;
                }
            }
            if (index != -1)
            {
                for (int i = index; i < userCarts[userEmail].cartItemsId - 1; ++i)
                {
                    userCarts[userEmail].cartProduct[i] = userCarts[userEmail].cartProduct[i + 1];
                }
                userCarts[userEmail].cartItemsId--;
                cout << "\n\tProduct with ID " << id << " has been removed from your cart.";
            }
            else
            {
                cout << "\n\tProduct with ID " << id << " not found in your cart.";
            }
        }
    }

    void cartAndCheackOutProduct(AllProducts &allProducts, const string &userEmail)
    {
        string choice;
        while (true)
        {
            cout << "\n\n\t _________________________________________\n";
            cout << "\t|\t\tCart & Checkout   \t  |\n";
            cout << "\t|_________________________________________|\n";
            cout << "\t|   |" << setw(39) << "|\n";
            cout << "\t| 1 |  View Cart" << setw(28) << "|\n";
            cout << "\t| 2 |  Checkout" << setw(29) << "|\n";
            cout << "\t| 3 |  Cancel Order" << setw(25) << "|\n"; // New option for canceling order
            cout << "\t| 0 |  Back" << setw(33) << "|\n";
            cout << "\t|   |" << setw(39) << "|\n";
            cout << "\t|___|_____________________________________|\n";
            while (true)
            {
                cout << "\n\tEnter your choice: ";
                getline(cin, choice);
                if (idValidation(choice))
                {
                    break;
                }
                cout << "\n\tInvalid Input!";
            }
            if (choice == "1")
            {
                system("cls");
                showCart(userEmail, allProducts);
            }
            else if (choice == "2")
            {
                system("cls");
                if (userCarts[userEmail].cartItemsId != 0)
                {
                    double totalBill = calculateTotalBill(userEmail);
                    payBill(userEmail, totalBill);
                }
                else
                {
                    cout << "\n\tYour cart is empty." << endl;
                }
            }
            else if (choice == "3")
            {
                system("cls");
                if (userCarts[userEmail].cartItemsId == 0)
                {
                    cout << "\n\tYour cart is empty. No orders to cancel." << endl;
                }
                else
                {
                    int id;
                    cout << "\n\tEnter the Product ID you want to cancel: ";
                    cin >> id;
                    cancelOrder(userEmail, id);
                }
            }
            else if (choice == "0")
            {
                system("cls");
                break;
            }
            else
            {
                system("cls");
                cout << "\n\tInvalid Choice!\n";
            }
        }
    }

    void checkPayment()
    {
        bool paymentFound = false; // Track if any payment is found

        // Iterate over all users in the userCarts map
        for (const auto &userCartPair : userCarts)
        {
            const string &userEmail = userCartPair.first;
            const UserCart &userCart = userCartPair.second;

            if (userCart.soldItemsId > 0)
            { // Check if this user has payment records
                paymentFound = true;
                cout << "\n\n\tPayment records for user: " << userEmail;
                double runningTotal = 0; // Initialize running total for each user

                for (int i = 0; i < userCart.soldItemsId; ++i)
                {
                    runningTotal += userCart.paidPayment[i]; // Add the current payment to the running total
                    cout << "\n\n\tPayment " << i + 1 << ":";
                    cout << "\n\tCustomer Name: " << userCart.customerName;
                    cout << "\n\tAmount Paid: " << userCart.paidPayment[i] << " Pkr";
                    cout << "\n\tTotal Paid So Far: " << userCart.paidPayment[i] << " Pkr"; // Show only the current payment amount here
                }

                // Display the final total amount paid
                cout << "\n\n\tTotal Paid for " << userEmail << ": " << runningTotal << " Pkr";
            }
        }

        if (!paymentFound)
        {
            cout << "\n\tNo payment records found for any users.";
        }
    }

    void paymentRecord()
    {
        string choice;
        while (true)
        {
            cout << "\n\n\t _________________________________________";
            cout << "\n\t|\tPayment Record Management   \t  |";
            cout << "\n\t|_________________________________________|";
            cout << "\n\t|   |" << setw(38) << "|";
            cout << "\n\t| 1 |  Check Payment Records" << setw(15) << "|";
            cout << "\n\t| 2 |  Clear Payment Records" << setw(15) << "|";
            cout << "\n\t| 0 |  Back" << setw(32) << "|";
            cout << "\n\t|___|_____________________________________|";

            while (true)
            {
                cout << "\n\tEnter your choice: ";
                getline(cin, choice);
                if (idValidation(choice))
                {
                    break;
                }
                cout << "\n\tInvalid Input!";
            }

            if (choice == "1")
            {
                system("cls");
                checkPayment(); // No need to pass userEmail, show all records
            }
            else if (choice == "2")
            {
                system("cls");

                // Iterate over all users to check if there's any payment to clear
                bool hasPaymentRecords = false;
                for (const auto &userCartPair : userCarts)
                {
                    if (userCartPair.second.soldItemsId > 0)
                    {
                        hasPaymentRecords = true;
                        break;
                    }
                }

                if (hasPaymentRecords)
                {
                    // Clear all payment records for all users
                    for (auto &userCartPair : userCarts)
                    {
                        userCartPair.second.soldItemsId = 0;
                    }
                    cout << "\n\tPayment records cleared successfully.";
                }
                else
                {
                    cout << "\n\tNo payment records found!";
                }
            }
            else if (choice == "0")
            {
                system("cls");
                break;
            }
            else
            {
                system("cls");
                cout << "\tInvalid choice. Please try again.\n";
            }
        }
    }
};
void modifyProduct(AllProducts &allProducts) {
    string modifyId;

    // Prompt user to enter the product ID
    cout << "\n\tEnter the ID of the Product you want to modify: ";
    getline(cin, modifyId);

    try {
        int productId = stoi(modifyId);  // Convert to integer
        bool found = false;

        // Helper function to modify a specific product
        auto modify = [](Product &product) {
            string newName, newDescription, newPriceStr, newAvailabilityStr;

            // Modify Name
            cout << "\n\tEnter new name (" << product.getName() << "): ";
            getline(cin, newName);
            if (!newName.empty()) {
                product.setName(newName);  // Use setter to update name
            }

            // Modify Description
            cout << "\tEnter new description (" << product.getDescription() << "): ";
            getline(cin, newDescription);
            if (!newDescription.empty()) {
                product.setDescription(newDescription);  // Use setter to update description
            }

            // Modify Price
            cout << "\tEnter new price (" << product.getPrice() << "): ";
            getline(cin, newPriceStr);
            if (!newPriceStr.empty()) {
                try {
                    double newPrice = stod(newPriceStr);
                    product.setPrice(newPrice);  // Use setter to update price
                } catch (const exception &) {
                    cout << "\tInvalid price entered! Keeping the current price.\n";
                }
            }

            // Modify Availability
            cout << "\tEnter new availability (1 for available, 0 for unavailable, current: " << product.isAvailable() << "): ";
            getline(cin, newAvailabilityStr);
            if (!newAvailabilityStr.empty()) {
                if (newAvailabilityStr == "1") {
                    product.setAvailability(true);  // Use setter to update availability
                } else if (newAvailabilityStr == "0") {
                    product.setAvailability(false);  // Use setter to update availability
                } else {
                    cout << "\tInvalid availability value! Keeping the current availability.\n";
                }
            }
        };

        // Search in Pants
        for (int i = 0; i < allProducts.getPantCount(); ++i) {
            if (allProducts.pantProducts[i].getId() == productId) {
                modify(allProducts.pantProducts[i]);
                found = true;
                cout << "\n\tPant with ID " << productId << " modified successfully!\n";
                break;
            }
        }

        // Search in Shirts
        for (int i = 0; i < allProducts.getShirtCount(); ++i) {
            if (allProducts.shirtProducts[i].getId() == productId) {
                modify(allProducts.shirtProducts[i]);
                found = true;
                cout << "\n\tShirt with ID " << productId << " modified successfully!\n";
                break;
            }
        }

        // Repeat for other categories: Suits, Frocks, Shoes, Jewelry
        for (int i = 0; i < allProducts.getSuitCount(); ++i) {
            if (allProducts.suitProducts[i].getId() == productId) {
                modify(allProducts.suitProducts[i]);
                found = true;
                cout << "\n\tSuit with ID " << productId << " modified successfully!\n";
                break;
            }
        }

        for (int i = 0; i < allProducts.getFrockCount(); ++i) {
            if (allProducts.frockProducts[i].getId() == productId) {
                modify(allProducts.frockProducts[i]);
                found = true;
                cout << "\n\tFrock with ID " << productId << " modified successfully!\n";
                break;
            }
        }

        for (int i = 0; i < allProducts.getShoeCount(); ++i) {
            if (allProducts.shoeProducts[i].getId() == productId) {
                modify(allProducts.shoeProducts[i]);
                found = true;
                cout << "\n\tShoe with ID " << productId << " modified successfully!\n";
                break;
            }
        }

        for (int i = 0; i < allProducts.getJewelryCount(); ++i) {
            if (allProducts.jewelryProducts[i].getId() == productId) {
                modify(allProducts.jewelryProducts[i]);
                found = true;
                cout << "\n\tJewelry with ID " << productId << " modified successfully!\n";
                break;
            }
        }

        if (!found) {
            cout << "\n\tProduct with ID " << productId << " not found!\n";
        } else {
            // Save changes to file
            allProducts.saveAllProductsToFile();
        }

    } catch (const std::invalid_argument &) {
        cout << "\n\tInvalid input! Please enter a valid numeric ID.\n";
    } catch (const std::out_of_range &) {
        cout << "\n\tID out of range! Please enter a smaller number.\n";
    }
}

string mainPage(AllProducts &allProducts)
{
    string choice;
    while (true)
    {
        cout << "\n\n\t _________________________________________\n";
        cout << "\t|\tE - COMMERCE Store   \t\t  |\n";
        cout << "\t|_________________________________________|\n";
        cout << "\t|   |" << setw(39) << "|\n";
        cout << "\t| 1 |  Admin  " << setw(30) << "|\n";
        cout << "\t| 2 |  User   " << setw(30) << "|\n";
        cout << "\t| 0 |  Exit " << setw(32) << "|\n";
        cout << "\t|   |" << setw(39) << "|\n";
        cout << "\t|___|_____________________________________|\n";
        while (true)
        {
            cout << "\n\tPress a key to continue ... ";
            getline(cin, choice);
            if (idValidation(choice))
            {
                break;
            }
            cout << "\n\tInvalid Input!";
        }
        if (choice == "1" || choice == "2" || choice == "0")
        {
            return choice;
            break;
        }
        else
        {
            system("cls");
            cout << "\n\tInvalid Choice!\n";
        }
    }
}

bool searchingLoop(string searchCriteria, AllProducts &allProducts)
{
    bool found = false;
    bool matchingProduct = false; // Flag to track if a product is found

    // Check Pants Products
    for (int i = 0; i < allProducts.getPantCount(); ++i)
    {
        if (!allProducts.pantProducts[i].getName().empty() &&
            (allProducts.pantProducts[i].getName().find(searchCriteria) != string::npos ||
             allProducts.pantProducts[i].getDescription().find(searchCriteria) != string::npos ||
             to_string(allProducts.pantProducts[i].getId()).find(searchCriteria) != string::npos))
        {
            if (allProducts.pantProducts[i].isAvailable())
            {
                if (!matchingProduct)
                {
                    cout << "\nMatching Products Found:";
                    matchingProduct = true;
                }

                cout << "\nPants - Name: " << allProducts.pantProducts[i].getName();
                cout << "\nDescription: " << allProducts.pantProducts[i].getDescription();
                cout << "\nPrice: " << allProducts.pantProducts[i].getPrice();
                cout << "\nID: " << allProducts.pantProducts[i].getId() << endl;
                found = true;
            }
        }
    }

    // Check Shirt Products
    for (int i = 0; i < allProducts.getShirtCount(); ++i)
    {
        if (!allProducts.shirtProducts[i].getName().empty() &&
            (allProducts.shirtProducts[i].getName().find(searchCriteria) != string::npos ||
             allProducts.shirtProducts[i].getDescription().find(searchCriteria) != string::npos ||
             to_string(allProducts.shirtProducts[i].getId()).find(searchCriteria) != string::npos))
        {
            if (allProducts.shirtProducts[i].isAvailable())
            {
                if (!matchingProduct)
                {
                    cout << "\nMatching Products Found:";
                    matchingProduct = true;
                }
                cout << "\nShirt - Name: " << allProducts.shirtProducts[i].getName();
                cout << "\nDescription: " << allProducts.shirtProducts[i].getDescription();
                cout << "\nPrice: " << allProducts.shirtProducts[i].getPrice();
                cout << "\nID: " << allProducts.shirtProducts[i].getId() << endl;
                found = true;
            }
        }
    }

    // Check Suit Products
    for (int i = 0; i < allProducts.getSuitCount(); ++i)
    {
        if (!allProducts.suitProducts[i].getName().empty() &&
            (allProducts.suitProducts[i].getName().find(searchCriteria) != string::npos ||
             allProducts.suitProducts[i].getDescription().find(searchCriteria) != string::npos ||
             to_string(allProducts.suitProducts[i].getId()).find(searchCriteria) != string::npos))
        {
            if (allProducts.suitProducts[i].isAvailable())
            {
                if (!matchingProduct)
                {
                    cout << "\nMatching Products Found:";
                    matchingProduct = true;
                }
                cout << "\nSuit - Name: " << allProducts.suitProducts[i].getName();
                cout << "\nDescription: " << allProducts.suitProducts[i].getDescription();
                cout << "\nPrice: " << allProducts.suitProducts[i].getPrice();
                cout << "\nID: " << allProducts.suitProducts[i].getId() << endl;
                found = true;
            }
        }
    }

    // Check Frock Products
    for (int i = 0; i < allProducts.getFrockCount(); ++i)
    {
        if (!allProducts.frockProducts[i].getName().empty() &&
            (allProducts.frockProducts[i].getName().find(searchCriteria) != string::npos ||
             allProducts.frockProducts[i].getDescription().find(searchCriteria) != string::npos ||
             to_string(allProducts.frockProducts[i].getId()).find(searchCriteria) != string::npos))
        {
            if (allProducts.frockProducts[i].isAvailable())
            {
                if (!matchingProduct)
                {
                    cout << "\nMatching Products Found:";
                    matchingProduct = true;
                }
                cout << "\nFrock - Name: " << allProducts.frockProducts[i].getName();
                cout << "\nDescription: " << allProducts.frockProducts[i].getDescription();
                cout << "\nPrice: " << allProducts.frockProducts[i].getPrice();
                cout << "\nID: " << allProducts.frockProducts[i].getId() << endl;
                found = true;
            }
        }
    }

    // Check Shoe Products
    for (int i = 0; i < allProducts.getShoeCount(); ++i)
    {
        if (!allProducts.shoeProducts[i].getName().empty() &&
            (allProducts.shoeProducts[i].getName().find(searchCriteria) != string::npos ||
             allProducts.shoeProducts[i].getDescription().find(searchCriteria) != string::npos ||
             to_string(allProducts.shoeProducts[i].getId()).find(searchCriteria) != string::npos))
        {
            if (allProducts.shoeProducts[i].isAvailable())
            {
                if (!matchingProduct)
                {
                    cout << "\nMatching Products Found:";
                    matchingProduct = true;
                }
                cout << "\nShoe - Name: " << allProducts.shoeProducts[i].getName();
                cout << "\nDescription: " << allProducts.shoeProducts[i].getDescription();
                cout << "\nPrice: " << allProducts.shoeProducts[i].getPrice();
                cout << "\nID: " << allProducts.shoeProducts[i].getId() << endl;
                found = true;
            }
        }
    }

    // Check Jewelry Products
    for (int i = 0; i < allProducts.getJewelryCount(); ++i)
    {
        if (!allProducts.jewelryProducts[i].getName().empty() &&
            (allProducts.jewelryProducts[i].getName().find(searchCriteria) != string::npos ||
             allProducts.jewelryProducts[i].getDescription().find(searchCriteria) != string::npos ||
             to_string(allProducts.jewelryProducts[i].getId()).find(searchCriteria) != string::npos))
        {
            if (allProducts.jewelryProducts[i].isAvailable())
            {
                if (!matchingProduct)
                {
                    cout << "\nMatching Products Found:";
                    matchingProduct = true;
                }
                cout << "\nJewelry - Name: " << allProducts.jewelryProducts[i].getName();
                cout << "\nDescription: " << allProducts.jewelryProducts[i].getDescription();
                cout << "\nPrice: " << allProducts.jewelryProducts[i].getPrice();
                cout << "\nID: " << allProducts.jewelryProducts[i].getId() << endl;
                found = true;
            }
        }
    }

    return found;
}

bool deleteLoop(int productId, AllProducts &allProducts)
{
    bool found = false;
    for (int i = 0; i < 50; ++i)
    {
        if (allProducts.pantProducts[i].getId() == productId && allProducts.pantProducts[i].isAvailable())
        {
            found = true;
            allProducts.pantProducts[i].setAvailability(false);
            cout << "\n\tProduct with ID " << productId << " deleted successfully!\n";
            break;
        }
        if (allProducts.shirtProducts[i].getId() == productId && allProducts.shirtProducts[i].isAvailable())
        {
            found = true;
            allProducts.shirtProducts[i].setAvailability(false);
            cout << "\n\tProduct with ID " << productId << " deleted successfully!\n";
            break;
        }
        if (allProducts.suitProducts[i].getId() == productId && allProducts.suitProducts[i].isAvailable())
        {
            found = true;
            allProducts.suitProducts[i].setAvailability(false);
            cout << "\n\tProduct with ID " << productId << " deleted successfully!\n";
            break;
        }
        if (allProducts.frockProducts[i].getId() == productId && allProducts.frockProducts[i].isAvailable())
        {
            found = true;
            allProducts.frockProducts[i].setAvailability(false);
            cout << "\n\tProduct with ID " << productId << " deleted successfully!\n";
            break;
        }
        if (allProducts.shoeProducts[i].getId() == productId && allProducts.shoeProducts[i].isAvailable())
        {
            found = true;
            allProducts.shoeProducts[i].setAvailability(false);
            cout << "\n\tProduct with ID " << productId << " deleted successfully!\n";
            break;
        }
        if (allProducts.jewelryProducts[i].getId() == productId && allProducts.jewelryProducts[i].isAvailable())
        {
            found = true;
            allProducts.jewelryProducts[i].setAvailability(false);
            cout << "\n\tProduct with ID " << productId << " deleted successfully!\n";
            break;
        }
    }

    if (!found)
    {
        cout << "\n\tProduct with ID " << productId << " not found.\n";
    }

    return found;
}

void display(AllProducts &allProducts)
{
    string choice;
    while (true)
    {
        cout << "\n\n\t _________________________________________\n";
        cout << "\t|\tDisplay Product   \t\t  |\n";
        cout << "\t|_________________________________________|\n";
        cout << "\t|   |" << setw(39) << "|\n";
        cout << "\t| 1 |  Gents Product" << setw(24) << "|\n";
        cout << "\t| 2 |  Ladies Product" << setw(23) << "|\n";
        cout << "\t| 3 |  Display All Products" << setw(17) << "|\n";
        cout << "\t| 0 |  Back" << setw(33) << "|\n";
        cout << "\t|   |" << setw(39) << "|\n";
        cout << "\t|___|_____________________________________|\n";
        while (true)
        {
            cout << "\n\tEnter your choice: ";
            getline(cin, choice);
            if (idValidation(choice))
            {
                break;
            }
            cout << "\n\tInvalid Input!";
        }
        if (choice == "1")
        {
            string gentsChoice;
            while (true)
            {
                cout << "\n\n\t _________________________________________\n";
                cout << "\t|\tDisplay Gents Product   \t  |\n";
                cout << "\t|_________________________________________|\n";
                cout << "\t|   |" << setw(39) << "|\n";
                cout << "\t| 1 |  Pants" << setw(32) << "|\n";
                cout << "\t| 2 |  Shirts" << setw(31) << "|\n";
                cout << "\t| 3 |  Suits" << setw(32) << "|\n";
                cout << "\t| 4 |  All Products" << setw(25) << "|\n";
                cout << "\t| 0 |  Back" << setw(33) << "|\n";
                cout << "\t|   |" << setw(39) << "|\n";
                cout << "\t|___|_____________________________________|\n";
                while (true)
                {
                    cout << "\n\tEnter your choice: ";
                    getline(cin, gentsChoice);
                    if (idValidation(gentsChoice))
                    {
                        break;
                    }
                    cout << "\n\tInvalid Input!";
                }
                if (gentsChoice == "1")
                {
                    system("cls");
                    allProducts.displayUserGentsPants();
                }
                else if (gentsChoice == "2")
                {
                    system("cls");
                    allProducts.displayUserGentsShirts();
                }
                else if (gentsChoice == "3")
                {
                    system("cls");
                    allProducts.displayUserGentsSuits();
                }
                else if (gentsChoice == "4")
                {
                    system("cls");
                    allProducts.allGentsProductDisplay();
                }
                else if (gentsChoice == "0")
                {
                    system("cls");
                    break;
                }
                else
                {
                    system("cls");
                    cout << "\n\tInvalid Choice!\n";
                }
            }
        }
        else if (choice == "2")
        {
            string ladiesChoice;
            while (true)
            {
                cout << "\n\n\t _________________________________________\n";
                cout << "\t|\tDisplay Ladies Product   \t  |\n";
                cout << "\t|_________________________________________|\n";
                cout << "\t|   |" << setw(39) << "|\n";
                cout << "\t| 1 |  Frocks" << setw(31) << "|\n";
                cout << "\t| 2 |  Shoes" << setw(32) << "|\n";
                cout << "\t| 3 |  Jewelry Sets" << setw(25) << "|\n";
                cout << "\t| 4 |  All Products" << setw(25) << "|\n";
                cout << "\t| 0 |  Back" << setw(33) << "|\n";
                cout << "\t|   |" << setw(39) << "|\n";
                cout << "\t|___|_____________________________________|\n";
                while (true)
                {
                    cout << "\n\tEnter your choice: ";
                    getline(cin, ladiesChoice);
                    if (idValidation(ladiesChoice))
                    {
                        break;
                    }
                    cout << "\n\tInvalid Input!";
                }
                if (ladiesChoice == "1")
                {
                    system("cls");
                    allProducts.displayUserLadiesFrocks();
                }
                else if (ladiesChoice == "2")
                {
                    system("cls");
                    allProducts.displayUserLadiesShoes();
                }
                else if (ladiesChoice == "3")
                {
                    system("cls");
                    allProducts.displayUserLadiesJewelrySets();
                }
                else if (ladiesChoice == "4")
                {
                    system("cls");
                    allProducts.allLadiesProductDisplay();
                }
                else if (ladiesChoice == "0")
                {
                    system("cls");
                    break;
                }
                else
                {
                    system("cls");
                    cout << "\n\tInvalid Choice!\n";
                }
            }
        }

        else if (choice == "3")
        {
            system("cls");
            allProducts.allGentsProductDisplay();
            allProducts.allLadiesProductDisplay();
        }
        else if (choice == "0")
        {
            system("cls");
            break;
        }
        else
        {
            system("cls");
            cout << "\n\tInvalid Choice!\n";
        }
    }
}

void searchProducts(AllProducts &allProducts)
{
    string searchCriteria;
    while (true)
    {
        cout << "\n\tSearch Any Product by Name, Description or Id: ";
        getline(cin, searchCriteria);
        if (stringValidation(searchCriteria) && searchCriteria != "0")
        {
            break;
        }
        cout << "\n\tInvalid Search! Please try again.\n";
    }
    bool found = false;

    found = searchingLoop(searchCriteria, allProducts);
    if (!found)
    {
        cout << "\n\tNo matching product found.\n";
    }
}

void addProduct(AllProducts &allProducts)
{
    while (true)
    {
        string choice;
        cout << "\n\t _________________________________________\n";
        cout << "\t|\t\tAdd Product   \t\t  |\n";
        cout << "\t|_________________________________________|\n";
        cout << "\t|   |" << setw(39) << "|\n";
        cout << "\t| 1 |  Pants" << setw(32) << "|\n";
        cout << "\t| 2 |  Shirts" << setw(31) << "|\n";
        cout << "\t| 3 |  Suits" << setw(32) << "|\n";
        cout << "\t| 4 |  Frocks" << setw(31) << "|\n";
        cout << "\t| 5 |  Shoes" << setw(32) << "|\n";
        cout << "\t| 6 |  Jewelry Sets" << setw(25) << "|\n";
        cout << "\t| 0 |  Back" << setw(33) << "|\n";
        cout << "\t|   |" << setw(39) << "|\n";
        cout << "\t|___|_____________________________________|\n";
        while (true)
        {
            cout << "\n\tEnter your choice: ";
            getline(cin, choice);
            if (idValidation(choice))
            {
                break;
            }
            cout << "\n\tInvalid Input!";
        }
        if (choice == "1")
        {
            system("cls");
            allProducts.addMultiplePants();
        }
        else if (choice == "2")
        {
            system("cls");
            allProducts.addMultipleShirts();
        }
        else if (choice == "3")
        {
            system("cls");
            allProducts.addMultipleSuits();
        }
        else if (choice == "4")
        {
            system("cls");
            allProducts.addMultipleFrocks();
        }
        else if (choice == "5")
        {
            system("cls");
            allProducts.addMultipleShoes();
        }
        else if (choice == "6")
        {
            system("cls");
            allProducts.addMultipleJewelrySets();
        }
        else if (choice == "0")
        {
            system("cls");
            break;
        }
        else
        {
            cout << "\n\tInvalid category choice!\n";
        }
    }
}
void deleteById(AllProducts &allProducts)
{
    string deleteId;

    while (true)
    {
        cout << "\n\tEnter ID of the Product you want to delete: ";
        getline(cin, deleteId);

        // Validate if the input is a valid number (ID)
        if (idValidation(deleteId))
        {
            try
            {
                int productId = stoi(deleteId); // Safely convert to integer
                bool found = false;

                // Check and delete from Pants
                for (int i = 0; i < allProducts.getPantCount(); ++i)
                {
                    if (allProducts.pantProducts[i].getId() == productId && allProducts.pantProducts[i].isAvailable())
                    {
                        allProducts.pantProducts[i].setAvailability(false); // Mark as unavailable
                        found = true;
                        cout << "\n\tPant with ID " << productId << " deleted successfully!";
                        break;
                    }
                }

                // Check and delete from Shirts
                for (int i = 0; i < allProducts.getShirtCount(); ++i)
                {
                    if (allProducts.shirtProducts[i].getId() == productId && allProducts.shirtProducts[i].isAvailable())
                    {
                        allProducts.shirtProducts[i].setAvailability(false); // Mark as unavailable
                        found = true;
                        cout << "\n\tShirt with ID " << productId << " deleted successfully!";
                        break;
                    }
                }

                // Repeat for other product categories: Suits, Frocks, Shoes, Jewelry
                for (int i = 0; i < allProducts.getSuitCount(); ++i)
                {
                    if (allProducts.suitProducts[i].getId() == productId && allProducts.suitProducts[i].isAvailable())
                    {
                        allProducts.suitProducts[i].setAvailability(false); // Mark as unavailable
                        found = true;
                        cout << "\n\tSuit with ID " << productId << " deleted successfully!";
                        break;
                    }
                }

                for (int i = 0; i < allProducts.getFrockCount(); ++i)
                {
                    if (allProducts.frockProducts[i].getId() == productId && allProducts.frockProducts[i].isAvailable())
                    {
                        allProducts.frockProducts[i].setAvailability(false); // Mark as unavailable
                        found = true;
                        cout << "\n\tFrock with ID " << productId << " deleted successfully!";
                        break;
                    }
                }

                for (int i = 0; i < allProducts.getShoeCount(); ++i)
                {
                    if (allProducts.shoeProducts[i].getId() == productId && allProducts.shoeProducts[i].isAvailable())
                    {
                        allProducts.shoeProducts[i].setAvailability(false); // Mark as unavailable
                        found = true;
                        cout << "\n\tShoe with ID " << productId << " deleted successfully!";
                        break;
                    }
                }

                for (int i = 0; i < allProducts.getJewelryCount(); ++i)
                {
                    if (allProducts.jewelryProducts[i].getId() == productId && allProducts.jewelryProducts[i].isAvailable())
                    {
                        allProducts.jewelryProducts[i].setAvailability(false); // Mark as unavailable
                        found = true;
                        cout << "\n\tJewelry with ID " << productId << " deleted successfully!";
                        break;
                    }
                }

                if (!found)
                {
                    cout << "\n\tProduct with ID " << productId << " not found!";
                }
                else
                {
                    // After marking product as deleted, save changes to the file
                    allProducts.saveAllProductsToFile();
                }
                break; // Exit the loop after processing deletion
            }
            catch (const std::invalid_argument &e)
            {
                cout << "\n\tInvalid ID! Please enter a valid numeric ID.";
            }
            catch (const std::out_of_range &e)
            {
                cout << "\n\tID out of range! Please enter a smaller number.";
            }
        }
        else
        {
            cout << "\n\tInvalid ID!";
        }
    }
}

void searchAndDelete(AllProducts &allProducts)
{
    string deleteCriteria;
    while (true)
    {
        cout << "\n\tSearch for delete Product by Name, Description, or Id: ";
        getline(cin, deleteCriteria);

        if (stringValidation(deleteCriteria) && deleteCriteria != "0") // Ensure "0" is not a valid input
        {
            break;
        }
        cout << "\n\tInvalid Search! Please try again.\n";
    }

    bool found = false;
    found = searchingLoop(deleteCriteria, allProducts);

    if (!found)
    {
        cout << "\n\tNo matching product found.\n";
    }
    else
    {
        deleteById(allProducts);
    }
}
void deleteProduct(AllProducts &allProducts)
{
    while (true)
    {
        cout << "\n\n\t _________________________________________";
        cout << "\n\t|\tDelete Product   \t\t  |";
        cout << "\n\t|_________________________________________|";
        cout << "\n\t|   |" << setw(38) << "|";
        cout << "\n\t| 1 |  Search and Delete " << setw(18) << "|";
        cout << "\n\t| 2 |  Delete by Product ID" << setw(16) << "|";
        cout << "\n\t| 0 |  Back" << setw(32) << "|";
        cout << "\n\t|___|_____________________________________|";
        string choice;
        while (true)
        {
            cout << "\n\tEnter your choice: ";
            getline(cin, choice);
            if (idValidation(choice))
            {
                break;
            }
            cout << "\n\tInvalid Input!";
        }

        if (choice == "1")
        {
            system("cls");
            searchAndDelete(allProducts);
        }
        else if (choice == "2")
        {
            system("cls");
            deleteById(allProducts);
        }
        else if (choice == "0")
        {
            system("cls");
            break;
        }
        else
        {
            cout << "\n\tInvalid choice!\n";
        }
    }
}

class UserLogin : public FileHandling
{
private:
    string email, name, password;

public:
    string getEmail()
    {
        return email;
    }
    bool userSignUp()
    {
        system("cls");
        cout << "\n\tUser Sign-Up\n";

        // Input name
        while (true)
        {
            cout << "\n\tEnter your name: ";
            getline(cin, name);
            if (stringValidation(name))
            {
                break;
            }
            cout << "\n\tInvalid name! Must be at least 3 characters.";
        }

        // Input email
        while (true)
        {
            cout << "\n\tEnter your email: ";
            getline(cin, email);
            if (email.find('@') != string::npos && email.find('.') != string::npos)
                break;
            cout << "\n\tInvalid email format!";
        }

        // Input password
        while (true)
        {
            cout << "\n\tEnter your password (6+ characters): ";
            getline(cin, password);
            if (password.length() >= 6)
                break;
            cout << "\n\tPassword too short!";
        }

        readUserDetails();
        for (const auto &existingEmail : userEmails)
        {
            if (email == existingEmail)
            {
                cout << "\n\tEmail already registered! Try logging in.";
                return false; // Return false if the email is already registered
            }
        }

        writeUserDetails(email, name, password);
        cout << "\n\tSign-Up Successful! Welcome, " << name << "!";
        return true; // Return true for a successful sign-up
    }

    bool userLogin()
    {
        readUserDetails();
        system("cls");
        int attempts = 0;

        while (attempts < 3)
        {
            cout << "\n\tUser Login\n";

            // Input email
            while (true)
            {
                cout << "\n\tEnter your email: ";
                getline(cin, email);
                if (email.find('@') != string::npos && email.find('.') != string::npos)
                    break;
                cout << "\n\tInvalid email format!";
            }

            // Input password
            cout << "\n\tEnter your password: ";
            getline(cin, password);

            // Check credentials
            for (size_t i = 0; i < userEmails.size(); ++i)
            {
                if (userEmails[i] == email && userPasswords[i] == password)
                {
                    // cout << "\n\tWelcome back, " << userNames[i] << "!";
                    return true;
                }
            }

            system("cls");
            cout << "\n\tInvalid credentials!";
            attempts++;
            if (attempts < 3)
            {
                cout << "\n\tAttempt " << attempts << " of 3.";
            }
            else
            {
                cout << "\n\tToo many failed attempts. Returning to main menu.";
                return false;
            }
        }

        return false;
    }

    bool forgotPassword()
    {
        readUserDetails();
        system("cls");
        cout << "\n\tForgot Password\n";
        while (true)
        {
            cout << "\n\tEnter your email: ";
            getline(cin, email);
            if (email.find('@') != string::npos && email.find('.') != string::npos)
                break;
            cout << "\n\tInvalid email format!";
        }
        cout << "\n\tEnter your username: ";
        getline(cin, name);
        for (size_t i = 0; i < userEmails.size(); ++i)
        {
            if (userEmails[i] == email && userNames[i] == name)
            {
                cout << "\n\tUser verified. Please enter your new password (6+ characters): ";
                while (true)
                {
                    getline(cin, password);
                    if (password.length() >= 6)
                    {
                        userPasswords[i] = password;
                        ofstream file("users.txt");
                        for (size_t j = 0; j < userEmails.size(); ++j)
                        {
                            file << userEmails[j] << " " << userNames[j] << " " << userPasswords[j] << "\n";
                        }
                        file.close();
                        cout << "\n\tPassword reset successful!";
                        return true;
                    }
                    cout << "\n\tPassword too short! Please enter a password with at least 6 characters.";
                }
            }
        }
        cout << "\n\tUser not found or information does not match!";
        return false;
    }
};

// Function to show the user menu
void showUserMenu(AllProducts &allProductsObject, CartBuyAndCheckOut &cartBuyAndCheckOutObject, const string &userEmail)
{
    string choice;
    while (true)
    {
        cout << "\n\n\t _________________________________________\n";
        cout << "\t|\t\tUser   \t\t\t  |\n";
        cout << "\t|_________________________________________|\n";
        cout << "\t|   |" << setw(39) << "|\n";
        cout << "\t| 1 |  Display Products" << setw(21) << "|\n";
        cout << "\t| 2 |  Browse Products" << setw(22) << "|\n";
        cout << "\t| 3 |  Buy Product" << setw(26) << "|\n";
        cout << "\t| 4 |  Cart & Pay-Out" << setw(23) << "|\n";
        cout << "\t| 0 |  Back" << setw(33) << "|\n";
        cout << "\t|   |" << setw(39) << "|\n";
        cout << "\t|___|_____________________________________|\n";
        while (true)
        {
            cout << "\n\tPress a key to continue ... ";
            getline(cin, choice);
            if (idValidation(choice))
            {
                break;
            }
            cout << "\n\tInvalid Input!";
        }
        if (choice == "1")
        {
            system("cls");
            display(allProductsObject);
        }
        else if (choice == "2")
        {
            system("cls");
            searchProducts(allProductsObject);
        }
        else if (choice == "3")
        {
            system("cls");
            cartBuyAndCheckOutObject.buyProduct(userEmail, allProductsObject);
        }
        else if (choice == "4")
        {
            system("cls");
            cartBuyAndCheckOutObject.cartAndCheackOutProduct(allProductsObject, userEmail);
        }
        else if (choice == "0")
        {
            system("cls");
            break;
        }
        else
        {
            system("cls");
            cout << "\n\tWrong Option!\n";
        }
    }
}
int main()
{
    AllProducts allProductsObject;
    AdminLogin adminLogin;
    CartBuyAndCheckOut cartBuyAndCheckOutObject;
    UserLogin userLogin;
    allProductsObject.loadAllProductsFromFile();
    while (true)
    {
        string choice = mainPage(allProductsObject);
        if (choice == "1")
        {
            bool adminVerification;
            adminVerification = adminLogin.oldAdminLogin();
            if (adminVerification == true)
            {
                string choice;
                while (true)
                {
                    cout << "\n\n\t _________________________________________\n";
                    cout << "\t|\t\tAdmin   \t\t  |\n";
                    cout << "\t|_________________________________________|\n";
                    cout << "\t|   |" << setw(39) << "|\n";
                    cout << "\t| 1 |  Available Products" << setw(19) << "|\n";
                    cout << "\t| 2 |  Add New Products" << setw(21) << "|\n";
                    cout << "\t| 3 |  Delete Products" << setw(22) << "|\n";
                    cout << "\t| 4 |  Modify product" << setw(23) << "|\n";
                    cout << "\t| 5 |  Payment Record" << setw(23) << "|\n";
                    cout << "\t| 6 |  Add Another Admin" << setw(20) << "|\n";
                    cout << "\t| 7 |  Remove Other Admin" << setw(19) << "|\n";
                    cout << "\t| 0 |  Log-Out" << setw(30) << "|\n";
                    cout << "\t|   |" << setw(39) << "|\n";
                    cout << "\t|___|_____________________________________|\n";
                    while (true)
                    {
                        cout << "\n\tPress a key to continue ... ";
                        getline(cin, choice);
                        if (idValidation(choice))
                        {
                            break;
                        }
                        cout << "\n\tInvalid Input!";
                    }
                    if (choice == "1")
                    {
                        system("cls");
                        allProductsObject.allProductsAdminRecord();
                    }
                    else if (choice == "2")
                    {
                        system("cls");
                        addProduct(allProductsObject);
                    }
                    else if (choice == "3")
                    {
                        system("cls");
                        deleteProduct(allProductsObject);
                    }
                    else if (choice == "4")
                    {
                        system("cls");
                        modifyProduct(allProductsObject);
                        break;
                    }
                    else if (choice == "5")
                    {
                        system("cls");
                        cartBuyAndCheckOutObject.paymentRecord();
                    }
                    else if (choice == "6")
                    {
                        system("cls");
                        adminLogin.newAdminRegistration();
                    }
                    else if (choice == "7")
                    {
                        system("cls");
                        // remove admin with correct username and password
                        adminLogin.removeAdmin();
                    }
                    else if (choice == "0")
                    {
                        system("cls");
                        break;
                    }
                    else // wrong option
                    {
                        system("cls");
                        cout << "\n\tWrong Option!\n";
                    }
                }
            }
        }
        else if (choice == "2")
        {
            // User Menu
            system("cls");
            string userOption;
            while (true)
            {
                cout << "\n\n\t _________________________________________\n";
                cout << "\t|\t\tUser Options\t\t  |\n";
                cout << "\t|_________________________________________|\n";
                cout << "\t|   |" << setw(39) << "|\n";
                cout << "\t| 1 |  Login" << setw(32) << "|\n";
                cout << "\t| 2 |  Sign Up" << setw(30) << "|\n";
                cout << "\t| 3 |  Forgot Password" << setw(22) << "|\n";
                cout << "\t| 0 |  Back" << setw(33) << "|\n";
                cout << "\t|   |" << setw(39) << "|\n";
                cout << "\t|___|_____________________________________|\n";
                cout << "\n\tEnter your choice: ";
                getline(cin, userOption);

                if (userOption == "1")
                {
                    if (userLogin.userLogin())
                    {
                        system("cls");
                        cout << "\n\tLogin successful!";
                        string userEmail = userLogin.getEmail(); // Assuming getEmail() retrieves the logged-in user's email
                        // Redirect to user menu after successful login
                        showUserMenu(allProductsObject, cartBuyAndCheckOutObject, userEmail);
                    }
                    else
                    {
                        cout << "\n\tLogin failed. Please try again.";
                    }
                }
                else if (userOption == "2")
                {
                    if (userLogin.userSignUp())
                    {
                        // cout << "\n\tSign-Up successful! Redirecting to user menu...";
                        string userEmail = userLogin.getEmail(); // Assuming getEmail() retrieves the new user's email
                        // Directly access user menu after successful sign-up
                        showUserMenu(allProductsObject, cartBuyAndCheckOutObject, userEmail);
                    }
                    else
                    {
                        cout << "\n\tSign-Up failed. Please try again.";
                    }
                }
                else if (userOption == "3")
                {
                    if (userLogin.forgotPassword())
                    {
                    }
                }
                else if (userOption == "0")
                {
                    system("cls");
                    break;
                }
                else
                {
                    system("cls");
                    cout << "\n\tInvalid choice!";
                }
            }
        }
        else if (choice == "0")
        {
            cout << "\n\n\t Thanks for using\n\t Good bye ... \n\n\n";
            break;
        }
    }
}