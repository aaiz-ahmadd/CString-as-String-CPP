#include <iostream>

using namespace std;

class String{
    char* str;
    char error = '\0';
    void copyArrayToOther(const char* s, char* d){
        int i = 0;
        for(; s[i] != '\0'; i++){
            d[i] = s[i];
        }
        d[i] = '\0';
    }
    public:
        String() : str{nullptr} {}
        String(const char* _str){
            int size = sizeOfArray(_str);
            str = new char[size + 1];
            copyArrayToOther(_str, str);
        }
        String(const String& other){
            int size = sizeOfArray(other.str);
            str = new char[size + 1];
            copyArrayToOther(other.str, str);
        }
        int sizeOfArray(const char* _str) const{
            int size = 0;
            for(; _str[size] != '\0'; size++);
            return size;
        }

        String& operator=(const String& other){
            if(this == &other)
                return *this;
            delete [] str;
            int size = sizeOfArray(other.str) + 1;
            this->str = new char[size];
            copyArrayToOther(other.str, str);
            return *this;
        }
        char& at(int pos){
            int size = sizeOfArray(this->str);
            char ch;
            if(pos < 0 || pos > size-1)
                return error;
            return str[pos];
        }
        char& operator[](int pos){
            int size = sizeOfArray(this->str);
            if(pos < 0 || pos >= size)
                return error;
            return *(str + pos);
        }
        const char& operator[](int pos) const {
            int size = sizeOfArray(this->str);
            if(pos < 0 || pos >= size)
                return error;
            return *(str + pos);
        }
        char& front(){
            return str[0];
        }
        char& back(){
            int size = sizeOfArray(this->str);
            return str[size-1];
        }
        bool empty() const{
            int size = sizeOfArray(this->str);
            if(size == 0)
                return true;
            return false;
        }
        String& insert(int pos, char ch){
            int size = sizeOfArray(this->str);
            char* temp = new char[size + 2];
            for(int i = 0; i < pos; i++){
                temp[i] = str[i];
            }
            temp[pos] = ch;
            for(int i = pos; i < size; i++){
                temp[i+1] = str[i];
            }   
            temp[size + 1] = '\0';
            delete [] str;
            str = temp;
            return *this;
        }
        String& insertRange(int pos, const char* other){
            int size1 = sizeOfArray(this->str);
            int size2 = sizeOfArray(other);
            int size = size1 + size2 + 1;
            char* temp = new char[size];
            int i = 0;

            for(; i < pos; i++)
                temp[i] = str[i];

            for(int j = 0; j < size2; j++)
                temp[i++] = other[j];
            
            for(int j = pos; j < size1; j++)
                temp[i++] = str[j];
            temp[i] = '\0';
            delete [] str;
            str = temp;
            return *this;
        }
        String& operator+=(const String& other){
            int size1 = sizeOfArray(str);
            int size2 = sizeOfArray(other.str);
            int size = size1 + size2 + 1;
            char* temp = new char[size];
            int i = 0;

            for(; i < size1; i++)
                temp[i] = str[i];

            for(int j = 0; j < size2; j++)
                temp[i++] = other.str[j];
            
            temp[i] = '\0';
            delete [] str;
            str = temp;
            return *this;
        }
        String& operator+=(char ch){
            int size1 = sizeOfArray(str);
            int size = size1 + 2;
            char* temp = new char[size];
            int i = 0;

            for(; i < size1; i++)
                temp[i] = str[i];
            
            temp[i++] = ch;
            temp[i] = '\0';
            delete [] str;
            str = temp;
            return *this;
        }

        void print(){
            cout << str << endl;
        }

        friend String operator+(const String& lhs, const String& rhs);
        friend bool operator==(const String& lhs, const String& rhs);
        friend bool operator!=(const String& lhs, const String& rhs);
        friend bool operator<(const String& lhs, const String& rhs);
        friend bool operator>(const String& lhs, const String& rhs);
        friend bool operator>=(const String& lhs, const String& rhs);
        friend bool operator<=(const String& lhs, const String& rhs);

        ~String(){
            delete [] str;
        }
};

String operator+(const String& lhs, const String& rhs){
    int size1 = lhs.sizeOfArray(lhs.str);
    int size2 = rhs.sizeOfArray(rhs.str);
    int size = size1 + size2 + 1;
    String temp;
    temp.str = new char[size];
    int i = 0;

    for(; i < size1; i++)
        temp.str[i] = lhs.str[i];

    for(int j = 0; j < size2; j++)
        temp.str[i++] = rhs.str[j];
            
    temp.str[i] = '\0';
    return temp;
}

bool operator==(const String& lhs, const String& rhs){
    int size1 = lhs.sizeOfArray(lhs.str);
    int size2 = rhs.sizeOfArray(rhs.str);
    if(size1 != size2)
        return false;
    for(int i = 0; i < size1; i++){
        if(lhs.str[i] != rhs.str[i])
            return false;
    }
    return true;
}

bool operator!=(const String& lhs, const String& rhs){
    int size1 = lhs.sizeOfArray(lhs.str);
    int size2 = rhs.sizeOfArray(rhs.str);
    if(size1 != size2)
        return true;
    for(int i = 0; i < size1; i++){
        if(lhs.str[i] != rhs.str[i])
            return true;
    }
    return false;
}

bool operator<(const String& lhs, const String& rhs){
    int size1 = lhs.sizeOfArray(lhs.str);
    int size2 = rhs.sizeOfArray(rhs.str);
    int min_size;
    if(size1 < size2)
        min_size = size1;
    else
        min_size = size2;
    
    for(int i = 0; i < min_size; i++){
        if(lhs.str[i] > rhs.str[i])
            return false;
        if(lhs.str[i] < rhs.str[i])
            return true;
    }
    if(size1 < size2)
        return true;
    return false;
}

bool operator>(const String& lhs, const String& rhs){
    int size1 = lhs.sizeOfArray(lhs.str);
    int size2 = rhs.sizeOfArray(rhs.str);
    int min_size;
    if(size1 > size2)
        min_size = size2;
    else
        min_size = size1;
    
    for(int i = 0; i < min_size; i++){
        if(lhs.str[i] < rhs.str[i])
            return false;
        if(lhs.str[i] > rhs.str[i])
            return true;
    }
    if(size1 > size2)
        return true;
    return false;
}

bool operator>=(const String& lhs, const String& rhs){
    int size1 = lhs.sizeOfArray(lhs.str);
    int size2 = rhs.sizeOfArray(rhs.str);
    int min_size;
    if(size1 > size2)
        min_size = size2;
    else
        min_size = size1;
    
    for(int i = 0; i < min_size; i++){
        if(lhs.str[i] < rhs.str[i])
            return false;
        if(lhs.str[i] > rhs.str[i])
            return true;
    }
    if(size1 >= size2)
        return true;
    return false;
}

bool operator<=(const String& lhs, const String& rhs){
    int size1 = lhs.sizeOfArray(lhs.str);
    int size2 = rhs.sizeOfArray(rhs.str);
    int min_size;
    if(size1 > size2)
        min_size = size2;
    else
        min_size = size1;
    
    for(int i = 0; i < min_size; i++){
        if(lhs.str[i] < rhs.str[i])
            return true;
        if(lhs.str[i] > rhs.str[i])
            return false;
    }
    if(size1 <= size2)
        return true;
    return false;
}

void menu(){
    cout << "1 - Access at Index" << endl;
    cout << "2 - Access at Index using [] operator" << endl;
    cout << "3 - Access Front Character" << endl;
    cout << "4 - Access Last Character" << endl;
    cout << "5 - Is string empty" << endl;
    cout << "6 - Insert Character at Index" << endl;
    cout << "7 - Insert String at Index" << endl;
    cout << "8 - Concatenate String using += operator" << endl;
    cout << "9 - Concatenate Character using += operator" << endl;
    cout << "10 - Concatenate String using + operator" << endl;
    cout << "11 - Strings Equality Check" << endl;
    cout << "12 - Strings Inequality Check" << endl;
    cout << "13 - String Less Than Check" << endl;
    cout << "14 - String Greater Than Check" << endl;
    cout << "15 - String Greater Than or Equal To Check" << endl;
    cout << "16 - String Less Than or Equal To Check" << endl;
    cout << "0 - Exit" << endl;
}

int main(){
    int choice;
    cout << "Enter string: ";
    char str[100];
    cin.getline(str, 100);
    String s1(str);
    cout << "Enter string: ";
    cin.getline(str, 100);
    String s2(str);

    do{
        menu();
        cout << "Enter choice: ";
        cin >> choice;
        if(choice == 0){
            cout << "Exiting..." << endl;
            break;
        }
        else if(choice == 1){
            int index;
            cout << "Enter index: ";
            cin >> index;
            char ch = s1.at(index);
            if(ch != '\0')
                cout << "Character at index " << index << ": " << ch << endl;
            else
                cout << "Invalid index!" << endl;
        }
        else if(choice == 2){
            int index;
            cout << "Enter index: ";
            cin >> index;
            char ch = s1[index];
            if(ch != '\0')
                cout << "Character at index " << index << ": " << ch << endl;
            else
                cout << "Invalid index!" << endl;
        }
        else if(choice == 3){
            char ch = s1.front();
            if(ch != '\0')
                cout << "Front character: " << ch << endl;
        }
        else if(choice == 4){
            char ch = s1.back();
            if(ch != '\0')
                cout << "Last character: " << ch << endl;
        }
        else if(choice == 5){
            if(s1.empty())
                cout << "String is empty!" << endl;
            else
                cout << "String is not empty!" << endl;
        }
        else if(choice == 6){
            int index;
            char ch;
            cout << "Enter index: ";
            cin >> index;
            cout << "Enter character: ";
            cin >> ch;
            s1.insert(index, ch);
            cout << "String after insertion: ";
            s1.print();
        }
        else if(choice == 7){
            int index;
            char str[100];
            cout << "Enter index: ";
            cin >> index;
            cout << "Enter string: ";
            cin.ignore();
            cin.getline(str, 100);
            s1.insertRange(index, str);
            cout << "String after insertion: ";
            s1.print();
        }
        else if(choice == 8){
            s1 += s2;
            cout << "String after concatenation: ";
            s1.print();
        }
        else if(choice == 9){
            char ch;
            cout << "Enter character: ";
            cin >> ch;
            s1 += ch;
            cout << "String after concatenation: ";
            s1.print();
        }
        else if(choice == 10){
            String s3 = s1 + s2;
            cout << "String after concatenation: ";
            s3.print();
        }
        else if(choice == 11){
            if(s1 == s2)
                cout << "Strings are equal!" << endl;
            else
                cout << "Strings are not equal!" << endl;   
        }
        else if(choice == 12){
            if(s1 != s2)
                cout << "Strings are not equal!" << endl;
            else
                cout << "Strings are equal!" << endl;   
        }
        else if(choice == 13){
            if(s1 < s2)
                cout << "String 1 is less than String 2!" << endl;
            else
                cout << "String 1 is not less than String 2!" << endl;   
        }
        else if(choice == 14){
            if(s1 > s2)
                cout << "String 1 is greater than String 2!" << endl;
            else
                cout << "String 1 is not greater than String 2!" << endl;   
        }
        else if(choice == 15){
            if(s1 >= s2)
                cout << "String 1 is greater than or equal to String 2!" << endl;
            else
                cout << "String 1 is not greater than or equal to String 2!" << endl;   
        }
        else if(choice == 16){
            if(s1 <= s2)
                cout << "String 1 is less than or equal to String 2!" << endl;
            else
                cout << "String 1 is not less than or equal to String 2!" << endl;   
        }
        else{
            cout << "Invalid choice!" << endl;
        }
    }while(choice != 0);
    return 0;
}