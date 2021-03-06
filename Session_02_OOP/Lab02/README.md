# OOP - Object Oriented Programming - Basic

## Class vs Object    
* Class -> Template/Type
    * No have memory
* Object is instant of Class ~ variable with type (CLASS)
    * Object have memory

## Define class
* __Scope__
    * Private (default)
    * Public
    * Protected

* Class
    * Attributes
    * Methods
        * Constructor -> new object
            * Default Constructor
            * Constructor with parameter (list of value of Attributes)
            * Copy Constructor
        * ~Destructor
        * Getter -> return value of Attributes
        * Setter -> set value for Attributes
        * Business methods
    
```c++
class Fraction
{
    // Attributes
    private:
        int numerator;      // Tử số
        int denominator;    // Mẫu số

    // Methods
    public:
        // Constructor
        Fraction();                                             // default constructor
        Fraction(const int &numerator, const int &denominator);   // constructor with paramters
        Fraction(const Fraction &fraction);                     // copy constructor

        // Destructor
        ~Fraction();

        // Getter
        int GetNumerator();
        int GetDenominator();

        // Setter
        void SetNumerator(const int &value);
        void SetDenominator(const int &value);

        // Business
        string ToString();
        Fraction* Add(const Fraction &fraction);
        Fraction* Sub(const Fraction &fraction);
        Fraction* Mul(const Fraction &fraction);
        Fraction* Div(const Fraction &fraction);
};
```