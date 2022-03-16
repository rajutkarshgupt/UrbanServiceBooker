#include <bits/stdc++.h>
using namespace std;
struct Date
{
   int dd;
   int mm;
   int yyyy;
};
struct Time
{
   int hh;
   int mm;
};
enum ServiceType
{
    cleaning,
    carpentry,
    plumbing,
    elctrician,
    appliance_repair,
    personal_grooming
};
class Order
{
   public:
      string orderID;             // alphanumeric
      Date date;
      Time _time;
      string userAddress;
      string smID;                // Service Manager ID
      ServiceType serviceType;
      int ratingPoints;           // Integer in range of [0,10]
      
      string generateOrderID();  // returns orderID of newly placed order
};
map<string, Order>orderTable; // maps urderId to rest of order details
class User
{
   private:
      string UserID;                 // alphanumeric
      string userName;
      string contactNumber;       // string of length 10
      string userAddress;
      int creditPoints;
      vector<Order>orders;        // contain list of all the orders user made
   
   public:
      string placeOrder(string userID, ServiceType serviceType, Date date, Time _time);
      vector<Order> getMyOrders(string userID);
};
map<string, User>userTable;    // maps userId to user's rest of details 
class ServiceManager
{
   public:
      string smID;                // alphanumeric ( sm = Service Manager )
      string smName;
      string contactNumber;       // string of length 10
      int avgRating;              // Average of all ratings till now
      Date availableDate;
      Time availableTime;
};
map<string, ServiceManager>smTable; // maps smID to sm's rest of details

map<ServiceType, map<string, ServiceManager> >serviceTable; /* maps each & every service 
                                                   to all those Service Manager's
                                                   who provide that service*/   

string earliestAvailableSM(map<string, ServiceManager>smTable, Date date, Time _time); 
   /*return smID of Service Manager available 
      earliest on or after given date & time*/

string User::placeOrder(string userID, ServiceType serviceType, Date date, Time _time)    // return orderID of newly placed order
{
   string orderID;
   if(userTable.find(userID)!=userTable.end())
   {
      Order order;
      order.serviceType=serviceType;
      order.userAddress=userTable[userID].userAddress;
      order.smID=earliestAvailableSM(serviceTable[serviceType], date, _time);
      order.date=smTable[order.smID].availableDate;
      order._time=smTable[order.smID].availableTime;
      order.orderID=order.generateOrderID();
      orderTable[order.orderID]=order;
   }
   else
   {
      cout<<"Please enter correct userID";
      return "-1";
   }
   return orderID;
}
vector<Order> User::getMyOrders(string userID)
{
   if(userTable.find(userID)==userTable.end())
   {
      cout<<"Please enter correct userID";
      return {};
   }
   return userTable[userID].orders;
}
int main() {
	
	return 0;
}
