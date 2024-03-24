#include <iostream>
using namespace std;

class Admin;
class Customers;
class Drivers;

// Rides class
class Rides
{
private:
    int id;
    string start_location;
    string end_location;
    string customer_email;
    string driver_email;
    int price;
    int kms_driven;

public:
    friend ostream &operator<<(ostream &output, const Rides &ride);
    // friend class Customers;
    friend class Drivers;

    // default constructor
    Rides()
    {
        id = 0;
        start_location = "";
        end_location = "";
        customer_email = "";
        price = 0;
        kms_driven = 0;
    }

    // parameterized constructor
    Rides(int id1, string start_l1, string end_l1, string customer_email1, int price1, int kms_driven1)
    {
        id = id1;
        start_location = start_l1;
        end_location = end_l1;
        customer_email = customer_email1;
        price = price1;
        kms_driven = kms_driven1;
    }

    void printRide()
    {
        cout << "Ride Details" << endl;
        cout << "id : " << id << endl
             << "Start Location : " << start_location << endl
             << "End Location : " << end_location << endl
             << "Customer Email : " << customer_email << endl
             << "Price : " << price << endl
             << "Kilometers Driven : " << kms_driven << endl;
    }

    // Setter functions
    void setId(int newId)
    {
        id = newId;
    }
    void setStartLocation(string newStartLoc)
    {
        start_location = newStartLoc;
    }
    void setEndLocation(string newEndLoc)
    {
        end_location = newEndLoc;
    }
    void setCustomerEmail(string newCustomerEmail)
    {
        customer_email = newCustomerEmail;
    }
    void setDriverEmail(string newDriverEmail)
    {
        driver_email = newDriverEmail;
    }
    void setPrice(int newPrice)
    {
        price = newPrice;
    }
    void setKmsDriven(int newKMS)
    {
        kms_driven = newKMS;
    }

    // Getter functions
    int getID()
    {
        return id;
    }
    string getStartLocation()
    {
        return start_location;
    }
    string getEndLocation()
    {
        return end_location;
    }
    string getCustomerEmail()
    {
        return customer_email;
    }
    string getDriverEmail()
    {
        return driver_email;
    }
    int getPrice()
    {
        return price;
    }
    int getKmsDriven()
    {
        return kms_driven;
    }
};

ostream &operator<<(ostream &output, const Rides &ride)
{
    output << "Ride Details" << endl;
    output << "id : " << ride.id << endl
           << "Start Location : " << ride.start_location << endl
           << "End Location : " << ride.end_location << endl
           << "Customer Email : " << ride.customer_email << endl
           << "Price : " << ride.price << endl
           << "Kilometers Driven : " << ride.kms_driven << endl;
    return output;
}

/*
a
b
c
d
e
f
g
*/

class Drivers
{
private:
    string name;
    string car_number;
    int rating;
    int contact_number;
    string email;
    bool authorized;
    bool available;
    Rides rides_list[100];
    int number_of_rides;

public:
    friend class Customers;
    friend ostream &operator<<(ostream &output, Drivers &driver);
    // default constructor
    Drivers()
    {
        name = "";
        car_number = "";
        rating = 0;
        contact_number = 0;
        email = "";
        authorized = false;
        available = false;
        for (int i = 0; i < 100; ++i)
        {
            rides_list[i] = Rides(); // Default constructor of Rides
        }
        number_of_rides = 0;
    }

    // Para constructor
    Drivers(string name1, string car_number1, int rating1, int contact_number1, string email1, bool auth1, bool available1, int ride_number, Rides ride, int number_of_rides1)
    {
        name = name1;
        car_number = car_number1;
        rating = rating1;
        contact_number = contact_number1;
        email = email1;
        authorized = auth1;
        available = available1;
        rides_list[ride_number] = ride;
        number_of_rides = number_of_rides1;
    }

    void printDetails()
    {
        cout << "Driver info : " << endl;
        cout << "Name : " << name << endl;
        cout << "Car Number : " << car_number << endl;
        cout << "Rating : " << rating << endl;
        cout << "Contact Number : " << contact_number << endl;
        cout << "Email : " << email << endl;
        cout << "Authorization Status: " << authorized << endl;
        cout << "Availablity Status : " << available << endl;
        cout << "Rides List : " << rides_list << endl;
        cout << "Number of Rides : " << number_of_rides << endl;
    }

    void printAllRides()
    {
        for (int i = 0; i < 100; i++)
        {
            cout << "\n List " << i << " : " << endl;
            cout << rides_list[i];
        }
    }

    // for earning I am using just the price of each ride taken by this driver and suming them, no costs taken in account.
    int earningsReport()
    {
        int money = 0;
        for (int i = 0; i < 100; i++)
        {
            money += rides_list[i].getPrice();
        }
        return money;
    }

    void completeCurrentRide()
    {
        // for completing the ride, just make driver available again and add 1 to number of rides of customer and driver
        available = true;
        number_of_rides = number_of_rides + 1; // driver's rides added 1
        // customer's 1 is added automatically when he places order.
    }

    // Setter functions
    void setName(string newName)
    {
        name = newName;
    }
    void setCarNumber(string newCarNumber)
    {
        car_number = newCarNumber;
    }
    void setRating(int newRating)
    {
        rating = newRating; ///////////////////////////////
    }
    void setContactumber(int newNumber)
    {
        contact_number = newNumber;
    }
    void setEmail(string newEmail)
    {
        email = newEmail;
    }
    void setAuthorized(bool newAuth)
    {
        authorized = newAuth;
    }
    void setAvailable(bool newAvail)
    {
        available = newAvail;
    }

    void setRideList(Rides newRide)
    {
        // Copy the new ride to rides_list
        for (int i = 0; i < 100; i++)
        {
            if (rides_list[i].getDriverEmail() == "")
            {
                rides_list[i] = newRide;
                number_of_rides++;
                return;
            }
        }
        cout << "Ride list is full";
    }

    void setNumberOfRides(int newNumberOfRides)
    {
        number_of_rides = newNumberOfRides;
    }

    // Getter functions
    string getName()
    {
        return name;
    }
    string getCarNumber()
    {
        return car_number;
    }
    int getRating()
    {
        return rating;
    }
    int getContactNumber()
    {
        return contact_number;
    }
    string getEmail()
    {
        return email;
    }
    bool getAuthorized()
    {
        return authorized;
    }
    bool getAvailable()
    {
        return available;
    }
    // Rides getRideList()
    // {
    //     for(int i = 0; i<100; i++)
    //     {
    //         rides_list[i];
    //     }
    // }
    const Rides *getRideList(int &size)
    {
        size = number_of_rides;
        return rides_list;
    }
};

ostream &operator<<(ostream &output, Drivers &driver)
{
    output << "Driver info : " << endl;
    output << "Name : " << driver.name << endl;
    output << "Car Number : " << driver.car_number << endl;
    output << "Rating : " << driver.rating << endl;
    output << "Contact Number : " << driver.contact_number << endl;
    output << "Email : " << driver.email << endl;
    output << "Authorization Status: " << driver.authorized << endl;
    output << "Availablity Status : " << driver.available << endl;
    output << "Rides List : " << endl;

    for (int i = 0; i < 100; i++)
    {
        output << "\n List " << i << " : " << endl;
        output << driver.rides_list[i];
    }

    output << "Number of Rides : " << driver.number_of_rides << endl;
    return output;
}

/*
a
b
c
d
e
f
g
*/

// Customer class
class Customers
{
private:
    string name;
    string email;
    int contact_number;
    bool authorized;
    Rides rides_list[100];
    int number_of_rides;

public:
    // Default constructor
    friend class Admin;
    friend ostream &operator<<(ostream &output, Customers &obj);
    friend Customers operator+(Customers Cust, const Rides &newRide);
    Customers()
    {
        name = "";
        email = "";
        contact_number = 0;
        authorized = false;
        for (int i = 0; i < 100; ++i)
        {
            rides_list[i] = Rides(); // Default constructor of Rides
        }
        number_of_rides = 0;
    }

    // Para constructor
    Customers(string name1, string email1, int contact1, bool auth1, Rides test_ride, int ride_number, int number_of_rides1)
    {
        name = name1;
        email = email1;
        contact_number = contact1;
        authorized = auth1;
        rides_list[ride_number] = test_ride;
        number_of_rides = number_of_rides1;
    }

    // printing details
    void printDetails()
    {
        cout << "Name : " << name << endl
             << "Email : " << email << endl
             << "Contact number : " << contact_number << endl
             << "Authorization Status : " << authorized << endl
             << "Number of Rides : " << number_of_rides << endl
             << "Rides List : " << rides_list << endl;
    }

    // printing rides details
    void printAllRides()
    {
        for (int i = 0; i < 100; i++)
        {
            cout << "\n List " << i << " : " << endl;
            cout << rides_list[i];
        }
    }

    // create a ride
    Drivers createRide(int id, int price, string startLoaction, string endLocation, int kms);

    void reviewDriver(Drivers rateDriver, int rating);

    // Setter functions
    void setName(string newName)
    {
        name = newName;
    }
    void setEmail(string newEmail)
    {
        email = newEmail;
    }
    void setContactNumber(int newContact)
    {
        contact_number = newContact;
    }
    void setAuthorized(bool auth)
    {
        authorized = auth;
    }
    void setRideList(Rides newRidesList[], int size)
    {
        // Check if size exceeds maximum allowed or negative
        if (size < 0 || size > 100)
        {
            cout << "Invalid size for rides list." << endl;
            return;
        }

        // Copy the new rides list to rides_list
        for (int i = 0; i < size; ++i)
        {
            rides_list[i] = newRidesList[i];
        }
        number_of_rides = size;
    }
    void setNumberOfRides(int newNoOfRides)
    {
        number_of_rides = newNoOfRides;
    }

    // Getter functions
    string getName()
    {
        return name;
    }
    string getEmail()
    {
        return email;
    }
    int getContactNumber()
    {
        return contact_number;
    }
    bool getAuthorized()
    {
        return authorized;
    }
    // Rides getRideList()
    // {
    //     for(int i = 0; i<100; i++)
    //     {
    //         rides_list[i];
    //     }
    // }
    const Rides *getRideList(int &size)
    {
        size = number_of_rides;
        return rides_list;
    }
    int getNumberOfRides()
    {
        return number_of_rides;
    }
};

ostream &operator<<(ostream &output, Customers &obj)
{
    output << "Name : " << obj.getName() << endl
           << "Email : " << obj.getEmail() << endl
           << "Contact number : " << obj.getContactNumber() << endl
           << "Authorization Status : " << obj.getAuthorized() << endl
           << "Number of Rides : " << obj.getNumberOfRides() << endl
           << "Rides List : " << endl;

    for (int i = 0; i < 100; i++)
    {
        output << "\n List " << i << " : " << endl;
        output << obj.rides_list[i];
    }
    return output;
}

Customers operator+(Customers Cust, const Rides &newRide)
{
    for (int i = 0; i < 100; ++i)
    {
        if (Cust.rides_list[i].getID() == 0)
        {
            Cust.rides_list[i] = newRide;
            break;
        }
    }
    return Cust;
}

/*
a
b
c
d
e
f
g
*/

class Admin
{
private:
    Customers All_Customers[100];
    Drivers All_Drivers[100];

public:
    friend class Customers;
    friend ostream &operator<<(ostream &output, Admin &aa);
    friend Admin operator+(Admin admin, const Customers &newCustomer);
    friend Admin operator+(Admin admin, const Drivers &newDriver);

    // default constructor //Just using default will cause no issues - all values set to nill
    Admin()
    {
        // Initialize All_Customers array
        for (int i = 0; i < 100; i++)
        {
            All_Customers[i] = Customers(); // Default constructor of Customers
        }

        // Initialize All_Drivers array
        for (int i = 0; i < 100; ++i)
        {
            All_Drivers[i] = Drivers(); // Default constructor of Drivers
        }
    }

    void addCustomer(Customers newCustomer)
    {
        for (int i = 0; i < 100; i++)
        {
            if (All_Customers[i].getName() == "")
            {
                All_Customers[i] = newCustomer;
                return;
            }
        }
    }

    // Function to swap two Drivers
    void swap(Drivers &a, Drivers &b)
    {
        Drivers temp = a;
        a = b;
        b = temp;
    }

    void addDriver(Drivers newDriver)
    {
        for (int i = 0; i < 100; i++)
        {
            if (All_Drivers[i].getName() == "")
            {
                All_Drivers[i] = newDriver;
                return; // Escape loop without changing all drivers and just only 1.
            }
        }

        // Function to sort an array of Drivers in ascending order
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                if (All_Drivers[j].getRating() > All_Drivers[j + 1].getRating())
                {
                    swap(All_Drivers[j], All_Drivers[j + 1]);
                }
            }
        }
    }

    void authorizeCustomer(string name1)
    {
        for (int i = 0; i < 100; i++)
        {
            if (All_Customers[i].getName() == name1)
            {
                All_Customers[i].setAuthorized(true);
                return;
            }
        }
    }

    void authorizeDriver(string name1)
    {
        for (int i = 0; i < 100; i++)
        {
            if (All_Drivers[i].getName() == name1)
            {
                All_Drivers[i].setAuthorized(true);
                return;
            }
        }
    }

    void printCustomers()
    {
        for (int i = 0; i < 100; i++)
        {
            All_Customers[i].printDetails();
        }
    }

    void printDrivers()
    {
        for (int i = 0; i < 100; i++)
        {
            All_Drivers[i].printDetails();
        }
    }

    // Setter Functions
    void setAllCustomers(Customers newCustomer)
    {
        for (int i = 0; i < 100; i++)
        {
            if (All_Customers[i].getName() == "") ////only setting one empty customer out of all 100. setting all 100 at once will take so much user time
            {
                All_Customers[i] = newCustomer;
            }
            else
            {
                cout << "no empty slot available";
            }
            return;
        }
    }

    void setAllDriver(Drivers newDriver)
    {
        for (int i = 0; i < 100; i++)
        {
            if (All_Drivers[i].getName() == "")
            {
                All_Drivers[i] = newDriver;
            }
            else
            {
                cout << "no empty slot available";
            }
            return;
        }
    }

    // Getter function

    void getAllCustomer()
    {
        for (int i = 0; i < 100; i++)
        {
            All_Customers[i].printDetails();
        }
    }

    void getAllDrivers()
    {
        for (int i = 0; i < 100; i++)
        {
            All_Drivers[i].printDetails();
        }
    }

    /// free drivers finder
    Drivers freeDriver()
    {
        Drivers freeOne;
        for (int i = 0; i < 100; i++)
        {
            if (All_Drivers[i].getAvailable() == true)
            {
                freeOne = All_Drivers[i];
                return freeOne;
            }
        }
        return freeOne;
    }
};

// overload <<
ostream &operator<<(ostream &output, Admin &aa)
{
    for (int i = 0; i < 100; i++)
    {
        output << "Name : " << aa.All_Customers[i].getName() << endl
               << "Email : " << aa.All_Customers[i].getEmail() << endl
               << "Contact number : " << aa.All_Customers[i].getContactNumber() << endl
               << "Authorization Status : " << aa.All_Customers[i].getAuthorized() << endl
               << "Number of Rides : " << aa.All_Customers[i].getNumberOfRides() << endl;
    }
    return output;
}

// overload +
Admin operator+(Admin admin, const Customers &newCustomer)
{
    for (int i = 0; i < 100; ++i)
    {
        if (admin.All_Customers[i].getName() == "")
        {
            admin.All_Customers[i] = newCustomer;
            return admin;
        }
    }
    return admin;
}

Admin operator+(Admin admin, const Drivers &newDriver)
{
    for (int i = 0; i < 100; ++i)
    {
        if (admin.All_Drivers[i].getName() == "")
        {
            admin.All_Drivers[i] = newDriver;
            break;
        }
    }
    return admin;
}

Admin admin1;

Drivers Customers::createRide(int id, int price, string startLoaction, string endLocation, int kms)
{
    Rides New_Ride;
    // CHECH IF DRIVER IS AVAILABLE, created in admin class.

    Drivers free_driver = admin1.freeDriver();
    if (free_driver.getAvailable() == true)
    {
        New_Ride.setCustomerEmail(email);
        New_Ride.setId(id);
        New_Ride.setPrice(price);
        New_Ride.setStartLocation(startLoaction);
        New_Ride.setEndLocation(endLocation);
        New_Ride.setKmsDriven(kms);
        New_Ride.setDriverEmail(free_driver.getEmail());
        // driver unavailable now
        free_driver.setAvailable(false);

        // Adding to ride list of customer
        for (int i = 0; i < 100; i++)
        {
            if (rides_list[i].getCustomerEmail() == "")
            {
                rides_list[i] = New_Ride;
            }
        }
        // Adding ride to driver's list
        free_driver.setRideList(New_Ride);
    }
    else
    {
        cout << "Driver not free ";
    }
    return free_driver; // returning this driver so we can review him in next function
}

void Customers::reviewDriver(Drivers rateDriver, int rating)
{
    rateDriver.setRating(rating);
}

/*
a
b
c
d
e
f
g
*/

int main()
{

    Rides test_ride(5, "LUMS", "Home", "xyz@gmail.com", 7, 6);
    // test_ride.printRide();

    // Customers cus1("Ali", "24020413@lums.edu.pk", 310, false, test_ride, 3, 0);
    // Customers cus2("Hussain", "abc@lums.edu.pk", 21, true, test_ride, 2, 0);
    // Customers cus3("Bukhari", "appleman@lums.edu.pk", 500, false, test_ride, 4, 0);

    // Customers

    Customers cus1;
    cus1.setName("ABC");
    cus1.setContactNumber(110);
    cus1.setEmail("Abc@gmail.com");

    Customers cus2;
    cus2.setName("Ali");
    cus2.setContactNumber(110);
    cus2.setEmail("Ali@gmail.com");

    Customers cus3;
    cus3.setName("Hussain");
    cus3.setContactNumber(110);
    cus3.setEmail("Hussain@gmail.com");

    Customers cus4;
    cus4.setName("Bukhari");
    cus4.setContactNumber(110);
    cus4.setEmail("Bukhari@gmail.com");

    Customers cus5;
    cus5.setName("Syed");
    cus5.setContactNumber(110);
    cus5.setEmail("Syed@gmail.com");
    cus5.setAuthorized(true);

    /////  prints customer perfect
    // cus1.printDetails();

    // Drivers

    Drivers dr1;
    dr1.setName("Driver-1");
    dr1.setCarNumber("D1-330");
    dr1.setContactumber(110);
    dr1.setEmail("Driver@gmail.com");

    Drivers dr2;
    dr2.setName("Driver-2");
    dr2.setCarNumber("D2-330");
    dr2.setContactumber(110);
    dr2.setEmail("Driver@gmail.com");

    Drivers dr3;
    dr1.setName("Driver-3");
    dr3.setCarNumber("D3-330");
    dr3.setContactumber(110);
    dr3.setEmail("Driver@gmail.com");

    Drivers dr4;
    dr4.setName("Driver-4");
    dr4.setCarNumber("D4-330");
    dr4.setContactumber(110);
    dr4.setEmail("Driver@gmail.com");

    Drivers dr5;
    dr5.setName("Driver-5");
    dr5.setCarNumber("D5-330");
    dr5.setContactumber(110);
    dr5.setEmail("Driver@gmail.com");

    // prints driver things perfect

    // dr1.printDetails();

    // dr1.printAllRides();

    admin1.addCustomer(cus1);
    admin1.addCustomer(cus2);
    admin1.addCustomer(cus3);
    admin1.addCustomer(cus4);
    // admin1 + cus5;
    // admin1.addCustomer(cus5);

    ////////////////////// operator works perfect
    // cout << admin1;

    // dr1.printDetails();
    // admin1 = admin1 + dr1;
    admin1.addDriver(dr2);
    admin1.addDriver(dr3);
    admin1.addDriver(dr4);
    admin1.addDriver(dr5);

    // works
    // admin1.getAllDrivers();

    // Authorizeing, available
    admin1.authorizeCustomer("Ali");
    admin1.authorizeCustomer("Hussain");
    admin1.authorizeCustomer("Syed");
    admin1.authorizeCustomer("Bukhari");
    admin1.authorizeCustomer("ABC");

    admin1.authorizeDriver("Driver-1");
    admin1.authorizeDriver("Driver-2");
    admin1.authorizeDriver("Driver-3");
    admin1.authorizeDriver("Driver-4");
    admin1.authorizeDriver("Driver-5");

    dr1.setAvailable(true);
    dr2.setAvailable(true);
    dr3.setAvailable(true);
    dr4.setAvailable(true);
    dr5.setAvailable(true);

    // works perfect
    admin1.getAllDrivers();

    Drivers cus1_ride = cus1.createRide(5, 100, "LUMS", "Home", 5);
    cus1.reviewDriver(cus1_ride, 1);

    Drivers cus2_ride = cus2.createRide(6, 200, "LUMS", "Highway", 20);
    cus2.reviewDriver(cus2_ride, 2);

    Drivers cus3_ride = cus3.createRide(7, 350, "Helipad", "Home", 40);
    cus3.reviewDriver(cus3_ride, 3);

    Drivers cus4_ride = cus4.createRide(8, 250, "ABC", "DEF", 7);
    cus4.reviewDriver(cus4_ride, 4);

    Drivers cus5_ride = cus5.createRide(9, 150, "Home", "Home2", 2);
    cus5.reviewDriver(cus5_ride, 5);

    Customers cus6;
    cus6.setName("Idiot");
    cus6.setContactNumber(10);
    cus6.setEmail("idiot@gmail.com");
    cus6.setAuthorized(true);

    // works
    cus6.createRide(10, 800, "Graveyard", "Sky", 400); // should give : no driver available rn

    admin1.getAllCustomer();
    cout << admin1;

    dr1.completeCurrentRide();
    dr2.completeCurrentRide();

    admin1.getAllDrivers();

    Customers cus7, cus8;
    cus7.setName("customer 7");
    cus7.setContactNumber(110);
    cus7.setEmail("c7@gmail.com");
    cus7.setAuthorized(true);

    cus8.setName("customer 8");
    cus8.setContactNumber(110);
    cus8.setEmail("c8@gmail.com");
    cus8.setAuthorized(true);

    cus7.createRide(7, 600, "NEW", "BA", 50);
    cus8.createRide(3, 4, "aa", "ee", 5); // made new customers because we dont know who's trip ended when the driver ended the trip. selecting trip is only chosen by the customer and we cannot detect which customer gets when free

    dr1.earningsReport();
    dr2.earningsReport();
    dr3.earningsReport();
    dr4.earningsReport();
    dr5.earningsReport();

    admin1.printCustomers();
    admin1.printDrivers();

    /// use of <<
    cus1.printAllRides();
    cus2.printAllRides();
    cus3.printAllRides();
    cus4.printAllRides();
    cus5.printAllRides();

    dr1.printAllRides();
    dr2.printAllRides();
    dr3.printAllRides();
    dr4.printAllRides();
    dr5.printAllRides();

    cout << admin1;
}