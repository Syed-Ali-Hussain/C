#include <iostream>
using namespace std;

// Product section
class Product
{
private:
    int productID;
    string productName;
    int price;

public:
    // default constructor
    Product()
    {
        productID = 0;
        productName = "No Name";
        price = 0;
    }
    // Para constructor
    Product(int product_price, int product_id, string product_name)
    {
        productID = product_id;
        productName = product_name;
        price = product_price;
    }

    // copy constructor
    Product(const Product &obj)
    {
        productID = obj.productID;
        productName = obj.productName;
        price = obj.price;
    }

    void printProduct()
    {
        cout << " \nProduct Name : " << productName << endl;
        cout << "Product ID : " << productID << endl;
        cout << "Price : " << price << endl;
    }

    void changePrice(int new_price)
    {
        price = new_price;
    }

    // setter member functions
    void setProductId(int productid)
    {
        productID = productid;
    }
    void setProductName(string productname)
    {
        productName = productname;
    }
    void setPrice(int productprice)
    {
        price = productprice;
    }

    // getter member functions
    int getProductId()
    {
        return productID;
    }
    string getProductName()
    {
        return productName;
    }
    int getPrice()
    {
        return price;
    }

    // making a = operator to assign value myself because the = operator by itself is depreciating, gives warning
    // basically if the value is not same then set the value of first object to the other object's value. and then returning the first one with changes made.
    Product &operator=(const Product &other)
    {
        if (this != &other)
        {
            this->price = other.price;
            this->productID = other.productID;
            this->productName = other.productName;
        }
        return *this;
    };
};

// Shopping Cart
class ShoppingCart
{
private:
    Product *list_of_products; // 1) Taking as the different types of products saved in the cart. 10 socks and 20 pants are stored as socks and pants in list (based on product ID).
    int *quantity_of_products; // 2) Taking as the number of those products saved. i.e 10 for socks and 20 for pants. ~~~ There must be some specific indexing then
    int product_count;         // 3) Taking as the total number of different types of products in cart. i.e 2, 1 for socks and 1 for pants.

public:
    // default constructor
    ShoppingCart()
    {
        list_of_products = nullptr;
        quantity_of_products = nullptr;
        product_count = 0;
    }

    // para constructor
    ShoppingCart(int count)
    {
        list_of_products = new Product[count]; // a list of n products
        quantity_of_products = new int[count]; // a list of n number, each value as number of those products
        product_count = count;                 // n different products.
    }

    // copy constructor
    ShoppingCart(const ShoppingCart &obj)
    {
        product_count = obj.product_count;
        // create new different arrays
        if (product_count != 0)
        {
            list_of_products = new Product[product_count];
            quantity_of_products = new int[product_count];
            // copying old data
            for (int i = 0; i < product_count; i++)
            {
                list_of_products[i] = obj.list_of_products[i];
                quantity_of_products[i] = obj.quantity_of_products[i];
            }
        }
        else
        {
            list_of_products = nullptr;
            quantity_of_products = nullptr;
        }
    }

    // destructor
    ~ShoppingCart()
    {
        delete[] list_of_products;
        delete[] quantity_of_products;
    }

    void addItem(Product new_product)
    {
        int index = -1;
        // we basically add the product with the specified product id
        for (int i = 0; i < product_count; i++)
        {
            if (list_of_products[i].getProductId() == new_product.getProductId())
            {
                index = i;
            }
        }

        if (index != -1)
        {
            quantity_of_products[index]++;
            return;
        }

        else
        {
            Product *new_list_product = new Product[product_count + 1];
            int *new_list_quantity = new int[product_count + 1];

            // copying old data
            for (int i = 0; i < product_count; i++)
            {
                new_list_product[i] = list_of_products[i];
                new_list_quantity[i] = quantity_of_products[i];
            }

            new_list_product[product_count] = new_product;
            new_list_quantity[product_count] = 1;
            product_count++;
            delete[] list_of_products;
            delete[] quantity_of_products;
            list_of_products = new_list_product;
            quantity_of_products = new_list_quantity;
        }
    }
    // unsure about the delete Item functionality. In Daraz app, delete button removes all the quantity of that product. Entirely removing the product. I'll be copying that style
    // if someone wants to change the quantity of product they can use ChangeQuantity function.
    void deleteItem(int product_id) // passing only product id, passing object already done in add item
    {
        int index = -1;
        for (int i = 0; i < product_count; i++)
        {
            if (list_of_products[i].getProductId() == product_id)
            {
                index = i;
                break;
            }
        }

        if (index != -1)
        {
            for (int i = index; i < product_count - 1; i++)
            {
                list_of_products[i] = list_of_products[i + 1]; // basically there was a gap because of deleting the item, now every product has to come 1 step back to fill the space.
                quantity_of_products[i] = quantity_of_products[i + 1];
            }

            product_count--;
            Product *new_list_products = new Product[product_count];
            int *new_list_quantity = new int[product_count];

            for (int i = 0; i < product_count; i++)
            {
                new_list_products[i] = list_of_products[i];
                new_list_quantity[i] = quantity_of_products[i];
            }
            delete[] list_of_products;
            delete[] quantity_of_products;
            list_of_products = new_list_products;
            quantity_of_products = new_list_quantity;
        }
        else
        {
            cout << "Product with ID : " << product_id << " not found" << endl;
        }
    }

    void printItem()
    {
        for (int i = 0; i < product_count; i++)
        {
            list_of_products[i].printProduct();
            cout << "Quantity : " << quantity_of_products[i] << endl;
        }
        int total_price = 0;
        int temp = 0;
        // total price calculation
        for (int i = 0; i < product_count; i++)
        {
            temp = list_of_products[i].getPrice() * quantity_of_products[i];
            total_price = total_price + temp;
        }
        cout << " \nTotal price : " << total_price << endl;
        cout << endl;
    }

    void changeQuantity(int product_id, int new_value)
    {
        for (int i = 0; i < product_count; i++)
        {
            if (list_of_products[i].getProductId() == product_id)
            {
                quantity_of_products[i] = new_value;
            }
        }
    }

    double calculateTotal()
    {
        int temp;
        int total_price = 0;
        // total price calculation
        for (int i = 0; i < product_count; i++)
        {
            temp = list_of_products[i].getPrice() * quantity_of_products[i];
            total_price = total_price + temp;
        }
        return total_price;
    }
    // setter
    void setProductCount(int count)
    {
        product_count = count;
    }
    // no use of getters and setters for the pointers, confusion causing code not good 
    void setListOfroducts(Product * list1)
    {
        list_of_products = list1;
    }
    void setListOfQuantity(int *list1)
    {
        quantity_of_products = list1;
    }
    // getter
    int getProductCount()
    {
        return product_count;
    }
    Product* getListOfroducts()
    {
        return list_of_products;
    }
    int* getListOfQuantity()
    {
        return quantity_of_products;
    }
};

// Seller section
class Seller
{
private:
    int product_count;
    string seller_name;
    Product *list_of_products_sold;

public:
    // default constructor
    Seller()
    {
        seller_name = "No Name";
        product_count = 0;
        // no need to create the array as no product exists yet:
        list_of_products_sold = nullptr;
    }

    // para constructor
    Seller(string sellername, int productcount)
    {
        seller_name = sellername;
        product_count = productcount;
        list_of_products_sold = new Product[productcount];
    }

    // copy constructor
    Seller(const Seller &obj)
    {
        product_count = obj.product_count;
        // create new different arrays
        list_of_products_sold = new Product[product_count];

        // copying old data
        for (int i = 0; i < product_count; i++)
        {
            list_of_products_sold[i] = obj.list_of_products_sold[i];
        }
    }

    // destructor
    ~Seller()
    {
        delete[] list_of_products_sold;
    }

    void printSeller()
    {
        cout << "\nSeller Name : " << seller_name << endl;
        cout << "Number of Products : " << product_count << endl;
        for (int i = 0; i < product_count; i++)
        {
            list_of_products_sold[i].printProduct();
        }
    }

    void addProduct(const Product &new_product)
    {
        Product *new_list_product = new Product[product_count + 1];

        // copying old data
        for (int i = 0; i < product_count; i++)
        {
            new_list_product[i] = list_of_products_sold[i];
        }

        new_list_product[product_count] = new_product;
        product_count++;
        delete[] list_of_products_sold;
        list_of_products_sold = new_list_product;
    }

    void deleteProduct(int product_id)
    {
        int index = -1;
        ShoppingCart cart;
        for (int i = 0; i < product_count; i++)
        {
            if (list_of_products_sold[i].getProductId() == product_id)
            {
                index = i;
                break;
            }
        }
        if (index != -1)
        {
            for (int i = index; i < product_count - 1; i++)
            {
                list_of_products_sold[i] = list_of_products_sold[i + 1]; // basically there was a gap because of deleting the item, now every product has to come 1 step back to fill the space.
            }

            product_count--;
            Product *new_product_list = new Product[product_count];

            for (int i = 0; i < product_count; i++)
            {
                new_product_list[i] = list_of_products_sold[i];
            }
            delete[] list_of_products_sold;
            list_of_products_sold = new_product_list;
        }
        else
        {
            cout << "Product with ID : " << product_id << "not found" << endl;
        }
    }

    // setter functions
    void setSellerName(const string &new_name)
    {
        seller_name = new_name;
    }
    void setProductCount(int new_count)
    {
        product_count = new_count;
    }

    // not sure what is being asked for setter of list. So many products should'nt be added at once. use addProduct function already created.

    // getter functions
    string getSellerName()
    {
        return seller_name;
    }

    int getProductCount()
    {
        return product_count;
    }

    Product getProductList(int product_id)
    {
        for (int i = 0; i < product_count; i++)
        {
            if (list_of_products_sold[i].getProductId() == product_id)
            {
                return list_of_products_sold[i];
            }
        }
        // not returning any error/default value if product is not found. can cause trouble to user, empty result will make him recheck on his own
    }
};

// Customer section
class Customer
{
private:
    string customer_name;
    ShoppingCart *shopping_cart;

public:
    // default constructor
    Customer()
    {
        customer_name = "No Name";
        shopping_cart = nullptr;  //not giving nullptr value on purpose. 1) there is no cart already, no need of it. 2) becomes an issue once we create a cart and overwriting becomes a bottleneck.
    }

    // para constructor. // automatically give him cart too
    Customer(string name)
    {
        customer_name = name;

        shopping_cart = new ShoppingCart(); 
    }

    // destructor
    ~Customer()
    {
        delete shopping_cart;
    }

    void printCustomer()
    {
        cout << " \nPrinting customer details : " << endl;
        cout << "Name : " << customer_name << endl;
        cout << "Customer's Cart Details : " << endl;
        if (shopping_cart != nullptr)
        {
            shopping_cart->printItem();
        }
        else
        {
            cout << "Empty" << endl;
        }
    }
    // I am making this simple function because it is the control of "Customer" to add something to cart, not the control of "Cart" to add something to it.
    void addToCart(Product product_to_add)
    {
        shopping_cart->addItem(product_to_add);
    }
    // Similarly the customer is to delete the product. I am doing nothing new, just using already created funtions to make it more clear.
    void deleteItem(Product product_to_delete)
    {
        shopping_cart->deleteItem(product_to_delete.getProductId());
    }
    void changeQuantity(Product product, int quant)
    {
        int prod = product.getProductId();
        shopping_cart->changeQuantity(prod, quant);
    }

    // setter functions
    void setName(string new_name)
    {
        customer_name = new_name;
    }

    void setCart(ShoppingCart *new_cart)  // It is very necessary. If we dont pass argument of ShoppingCart obj instead, C++ will create a copy of that cart and if we make changes to the cart it wont be recorded in copy that we have. Thus not truly dynamic pointer function.
    {
        shopping_cart = new_cart;
    }

    // getter functions
    string getName()
    {
        return customer_name;
    }
    ShoppingCart* getCart()
    {
        return shopping_cart;
    }
};

int main()
{
    cout << "Hello" << endl;
    // MAKING SELLERS AND PRODUCTS FIRST
    // checking all setter fuctions too

    // 5 sellers
    Seller s1, s2, s3, s4, s5;
    s1.setSellerName("Seller 1");
    s2.setSellerName("Seller 2");
    s3.setSellerName("Seller 3");
    s4.setSellerName("Seller 4");
    s5.setSellerName("Seller 5");

    // 7 products
    Product p1, p2, p3, p4, p5, p6, p7;
    p1.setPrice(100);
    p1.setProductId(1001);
    p1.setProductName("Product 1");

    p2.setPrice(200);
    p2.setProductId(1002);
    p2.setProductName("Product 2");

    p3.setPrice(300);
    p3.setProductId(1003);
    p3.setProductName("Product 3");

    p4.setPrice(400);
    p4.setProductId(1004);
    p4.setProductName("Product 4");

    p5.setPrice(500);
    p5.setProductId(1005);
    p5.setProductName("Product 5");

    p6.setPrice(600);
    p6.setProductId(1006);
    p6.setProductName("Product 6");

    p7.setPrice(700);
    p7.setProductId(1007);
    p7.setProductName("Product 7");

    // adding products to sellers
    s1.addProduct(p1);
    s2.addProduct(p2);
    s3.addProduct(p3);
    s4.addProduct(p4);
    s5.addProduct(p5);
    s5.addProduct(p6);
    s5.addProduct(p7);

    //////////////////////////////////////////////////////////////////////////////////////

    // Making 3 customers & 3 carts
    // 1 cart created seprately and other 2 automatially
    // Manually: 
    ShoppingCart cart1;
    ShoppingCart* cart1_ptr = &cart1;

    Customer c1;
    c1.setName("Ali");
    c1.setCart(cart1_ptr);


    // adding, deleting item to cart
    cart1.addItem(p1);
    c1.addToCart(p1);
    cart1.addItem(p1); // adding again increases quantity
    cart1.addItem(p2);
    cart1.deleteItem(p2.getProductId());
    cart1.addItem(p4);
    cart1.changeQuantity(p1.getProductId(),10); // set quantity function


    // Automatically
    Customer c2("Hussain");
    Customer c3("Bukhari");
    c2.addToCart(p1);
    c2.addToCart(p1);

    ShoppingCart *cart_2 = c2.getCart();// can do anyways. either by cart or by customer directly. nut the goal was to be done via the customer.
    cart_2->addItem(p1);

    c3.addToCart(p3);
    c3.addToCart(p3);

    

    // deleting sellers item
    s1.deleteProduct(p1.getProductId());
    // It was mentioned in main so i'll deleting the product from all shopping carts manually in main :/
    cart1.deleteItem(p1.getProductId());

    

    // display details
    p1.printProduct();
    p2.printProduct();
    p3.printProduct();

    c1.printCustomer();
    c2.printCustomer();
    c3.printCustomer();

    s1.printSeller();
    s2.printSeller();
    s3.printSeller();
    s4.printSeller();
    s5.printSeller();

}