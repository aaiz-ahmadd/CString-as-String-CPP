#include <iostream>

using namespace std;

class String{
    char* str;
    char error = '\0';
    int sizeOfArray(const char* _str) const{
        int size = 0;
        for(; _str[size] != '\0'; size++);
        return size;
    }
    void copyArrayToOther(const char* s, char* d){
        int i = 0;
        for(; s[i] != '\0'; i++){
            d[i] = s[i];
        }
        d[i] = '\0';
    }
    public:
        String() {
            str = new char[1];
            str[0] = '\0';
        }
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
        String(char ch){
            str = new char[2];
            str[0] = ch;
            str[1] = '\0';
        }
        String(int n, char ch){
            str = new char[n+1];
            for(int i = 0; i < n; i++)
                str[i] = ch;
            str[n] = '\0';
        }
        String(int n){
            int size = 0;
            int temp = n;
            while(temp != 0){
                temp /= 10;
                size++;
            }
            str = new char[size + 1];
            for(int i = size - 1; i >= 0; i--){
                str[i] = (n % 10) + '0';
                n /= 10;
            }
            str[size] = '\0';
        } 
        friend String operator+(const String& lhs, const String& rhs);
        friend bool operator==(const String& lhs, const String& rhs);
        friend bool operator!=(const String& lhs, const String& rhs);
        friend bool operator<(const String& lhs, const String& rhs);
        friend bool operator>(const String& lhs, const String& rhs);
        friend bool operator>=(const String& lhs, const String& rhs);
        friend bool operator<=(const String& lhs, const String& rhs); 

        int size() const{
            return sizeOfArray(str);
        }
        void increaseCapacity(int& c, int s, int*& substr){
            c *= 2;
            int* temp = new int[c];
            for(int i = 0; i < s; i++)
                temp[i] = substr[i];
            delete [] substr;
            substr = temp;
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
            if(str[0] == '\0')
                return error;
            return str[0];
        }
        char& back(){
            int size = sizeOfArray(this->str);
            if(size == 0)
                return error;
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
        void replaceFirst(char c){
            str[0] = c;
        }
        int length(){
            int i = 0;
            for(; str[i] != '\0'; i++);
            return i;
        }
        int stoi() const{
            int num = 0;
            int i = 0;
            for(; str[i] != '\0'; i++){
                if(str[i] < '0' || str[i] > '9')
                    return -1;
                num = (num * 10) + (str[i] - '0');
            }
            return num;
        }
        static int stoi(const String _str){
            return _str.stoi();
        }
        String itos(int n){
            String temp(n);
            return temp;
        }
        void trim(){
            int size = sizeOfArray(str);
            int count = 0;
            for(int i = 0; i < size; i++){
                if(str[i] == ' ' || str[i] == '\t' || str[i] == '\n'){
                    for(int j = i+1; j <= size; j++)
                        str[j-1] = str[j];
                    size--;
                    i--;
                }
                else    
                    count++;
                if(count > 0)
                    break;
            }
            count = 0;

            for(int i = size-1; i >= 0; i--){
                if(str[i] == ' ' || str[i] == '\t' || str[i] == '\n'){
                    str[i] = '\0';
                    size--;
                }
                else    
                    count++;
                if(count > 0)
                    break;
            }
        }
        static String trim(const String& s){
            String temp(s);
            temp.trim();
            return temp;
        }
        bool isEqual(const String& other) const{
            int size1 = this->size();
            int size2 = other.size();
            if(size1 != size2)
                return false;
            for(int i = 0; i < size1; i++){
                if(this->str[i] != other.str[i])
                    return false;
            }
            return true;
        }
        bool isLess(const String& other) const{
            int size1 = this->size();
            int size2 = other.size();
            int min_size;
            if(size1 < size2)
                min_size = size1;
            else
                min_size = size2;
    
            for(int i = 0; i < min_size; i++){
                if(str[i] > other.str[i])
                    return false;
                if(str[i] < other.str[i])
                    return true;
            }
            if(size1 < size2)
                return true;
            return false;
        }
        bool isGreater(const String& other) const{
            int size1 = this->size();
            int size2 = other.size();
            int min_size;
            if(size1 > size2)
                min_size = size2;
            else
                min_size = size1;
    
            for(int i = 0; i < min_size; i++){
                if(str[i] < other.str[i])
                    return false;
                if(str[i] > other.str[i])
                    return true;
            }
            if(size1 > size2)
                return true;
            return false;
        }
        String* split(char delim, int& count) const{
            count = 1;
            int size = sizeOfArray(str);
            for(int i = 0; i < size; i++){
                if(str[i] == delim)
                    count++;
            }

            String* temp = new String[count];
            int idx = 0;
            int s = 0;
            for(int i = 0; i <= size; i++){
                if(str[i] == delim || str[i] == '\0'){
                    temp[idx].str = new char[s+1];
                    int start = i - s;
                    for(int j = 0; j < s; j++)
                        temp[idx].str[j] = str[start + j];

                    temp[idx].str[s] = '\0';
                    s = 0;
                    idx++;
                }
                else
                    s++;
            }
            return temp;
        }
        bool isDelim(char ch, const char* delim) const{
            for(int i = 0; delim[i] != '\0'; i++)
                if(ch == delim[i])
                    return true;
            return false;
        }
        String* tokenize(const char* delim, int& count) const{
            bool inToken = false;
            count = 0;
            for(int i = 0; str[i] != '\0'; i++){
                if(!isDelim(str[i], delim) && !inToken){
                    inToken = true;
                    count++;
                }
                else if(isDelim(str[i], delim))
                    inToken = false;
            }

            String* temp = new String[count];
            int s = 0;
            int idx = 0;
            for(int i = 0; ; i++){
                if(isDelim(str[i], delim) || str[i] == '\0'){
                    if(s > 0){
                        temp[idx].str = new char[s+1];
                        int start = i - s;
                        for(int j = 0; j < s; j++)
                            temp[idx].str[j] = str[start + j];
                        temp[idx].str[s] = '\0';
                        s = 0;
                        idx++;
                    }
                    if(str[i] == '\0')
                        break;
                }
                else
                    s++;
                }
            return temp;
        }
        String concat(const String& other) const{
            String temp;
            temp = *this + other;
            return temp;
        }
        String& append(const String& other){
            *this += other;
            return *this;
        }
        bool isSubstring(int pos, const char* sub) const{
            int i = 0; 
            while(sub[i] != '\0'){
                if(str[pos + i] != sub[i])
                    return false;
                i++;
            }
            return true;
        }
        int* allSubstrings(const char* sub, int& count){
            int pos;
            count = 0;
            int c = 1;
            int s = 0;
            int* substr = new int[c];
            for(int i = 0; str[i] != '\0'; i++){
                if(str[i] == sub[0]){
                    if(isSubstring(i, sub)){
                        count++;
                        substr[s++] = i;
                        if(s >= c)
                            increaseCapacity(c, s, substr);
                    }
                }
            }
            return substr;
        }
        int find_first(char ch){
            for(int i = 0; str[i] != '\0'; i++){
                if(str[i] == ch)
                    return i;
            }
            return -1;
        }
        int find_first(const String& sub){
            for(int i = 0; str[i] != '\0'; i++){
                if(str[i] == sub[0]){
                    if(isSubstring(i, sub.str))
                        return i;
                }
            }
            return -1;
        }
        int find_last(char ch){
            int size = sizeOfArray(str);
            for(int i = size - 1; i >= 0; i--){
                if(str[i] == ch)
                    return i;
            }
            return -1;
        }
        int find_last(const String& sub){
            int size = sizeOfArray(str);
            for(int i = size - 1; i >= 0; i--){
                if(str[i] == sub[0]){
                    if(isSubstring(i, sub.str))
                        return i;
                }
            }
            return -1;
        }
        int* find_all(char ch, int& count){
            count = 0;
            for(int i = 0; str[i] !='\0'; i++){
                if(str[i] == ch)
                    count++;
            }
            int* temp = new int[count];
            int s = 0;
            for(int i = 0; str[i] != '\0'; i++){
                if(str[i] == ch)
                    temp[s++] = i;
            }
            return temp;
        }
        int* find_all(const String& sub, int& count){
            count = 0;
            for(int i = 0; str[i] != '\0'; i++){
                if(str[i] == sub.str[0]){
                    if(isSubstring(i, sub.str))
                        count++;
                }
            }

            int* temp = new int[count];
            int s = 0;
            for(int i = 0; str[i] != '\0'; i++){
                if(str[i] == sub.str[0]){
                    if(isSubstring(i, sub.str))
                        temp[s++] = i;
                }
            }
            return temp;
        }
        void remove_at(int pos){
            int s = sizeOfArray(str);
            for(int i = pos; i < s - 1; i++)
                str[i] = str[i+1];
            s--;
            str[s] = '\0';
        }
        void insert_at(int pos, char ch){
            *this = insert(pos, ch);
        }
        void insert_at(int pos, const String& sub){
            *this = insertRange(pos, sub.str);
        }
        void remove_first(char ch){
            int idx = find_first(ch);
            if(idx != -1)
                remove_at(idx);
        }
        void remove_last(char ch){
            int idx = find_last(ch);
            if(idx != -1)
                remove_at(idx);
        }
        void remove_all(char ch){
            int i = 0;
            while(str[i] != '\0'){
                if(str[i] == ch)
                    remove_at(i); 
                else
                    i++;
            }
        }
        void clear(){
            delete [] str;
            str = new char[1];
            str[0] = '\0';
        }
        void toUpper(){
            for(int i = 0; str[i] != '\0'; i++){
                if(str[i] >= 'a' && str[i] <= 'z')
                    str[i] -= 32;
            }
        }
        static String toUpper(String s){
            s.toUpper();
            return s;
        }
        void toLower(){
            for(int i = 0; str[i] != '\0'; i++){
                if(str[i] >= 'A' && str[i] <= 'Z')
                    str[i] += 32;
            }
        }
        static String toLower(String s){
            s.toLower();
            return s;
        }


        void print(){
            cout << str << endl;
        }

        ~String(){
            delete [] str;
        }
};

String operator+(const String& lhs, const String& rhs){
    int size1 = lhs.size();
    int size2 = rhs.size();
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
    int size1 = lhs.size();
    int size2 = rhs.size();
    if(size1 != size2)
        return false;
    for(int i = 0; i < size1; i++){
        if(lhs.str[i] != rhs.str[i])
            return false;
    }
    return true;
}

bool operator!=(const String& lhs, const String& rhs){
    int size1 = lhs.size();
    int size2 = rhs.size();
    if(size1 != size2)
        return true;
    for(int i = 0; i < size1; i++){
        if(lhs.str[i] != rhs.str[i])
            return true;
    }
    return false;
}

bool operator<(const String& lhs, const String& rhs){
    int size1 = lhs.size();
    int size2 = rhs.size();
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
    int size1 = lhs.size();
    int size2 = rhs.size();
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
    int size1 = lhs.size();
    int size2 = rhs.size();
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
    int size1 = lhs.size();
    int size2 = rhs.size();
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
    cout << "1  - Access at Index" << endl;
    cout << "2  - Access at Index using [] operator" << endl;
    cout << "3  - Access Front Character" << endl;
    cout << "4  - Access Last Character" << endl;
    cout << "5  - Is string empty" << endl;
    cout << "6  - Insert Character at Index" << endl;
    cout << "7  - Insert String at Index" << endl;
    cout << "8  - Concatenate String using += operator" << endl;
    cout << "9  - Concatenate Character using += operator" << endl;
    cout << "10 - Concatenate String using + operator" << endl;
    cout << "11 - Strings Equality Check" << endl;
    cout << "12 - Strings Inequality Check" << endl;
    cout << "13 - String Less Than Check" << endl;
    cout << "14 - String Greater Than Check" << endl;
    cout << "15 - String Greater Than or Equal To Check" << endl;
    cout << "16 - String Less Than or Equal To Check" << endl;
    cout << "17 - Replace First Character" << endl;
    cout << "18 - Length of String" << endl;
    cout << "19 - String to Integer (stoi)" << endl;
    cout << "20 - Integer to String (itos)" << endl;
    cout << "21 - Trim String" << endl;
    cout << "22 - Is Equal" << endl;
    cout << "23 - Is Less" << endl;
    cout << "24 - Is Greater" << endl;
    cout << "25 - Split String" << endl;
    cout << "26 - Tokenize String" << endl;
    cout << "27 - Concat String" << endl;
    cout << "28 - Append String" << endl;
    cout << "29 - All Substrings" << endl;
    cout << "30 - Find First Character" << endl;
    cout << "31 - Find First String" << endl;
    cout << "32 - Find Last Character" << endl;
    cout << "33 - Find Last String" << endl;
    cout << "34 - Find All Characters" << endl;
    cout << "35 - Find All Strings" << endl;
    cout << "36 - Remove at Index" << endl;
    cout << "37 - Insert Character at Position" << endl;
    cout << "38 - Insert String at Position" << endl;
    cout << "39 - Remove First Character" << endl;
    cout << "40 - Remove Last Character" << endl;
    cout << "41 - Remove All Characters" << endl;
    cout << "42 - Clear String" << endl;
    cout << "43 - To Upper" << endl;
    cout << "44 - To Lower" << endl;
    cout << "0  - Exit" << endl;
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
        else if(choice == 17){
            char ch;
            cout << "Enter character: ";
            cin >> ch;
            s1.replaceFirst(ch);
            cout << "String after replacing first character: ";
            s1.print();
        }
        else if(choice == 18){
            cout << "Length of string: " << s1.length() << endl;
        }
        else if(choice == 19){
            cout << "String to integer: " << s1.stoi() << endl;
        }
        else if(choice == 20){
            int num;
            cout << "Enter integer: ";
            cin >> num;
            String s3 = s1.itos(num);
            cout << "Integer to string: ";
            s3.print();
        }
        else if(choice == 21){
            s1.trim();
            cout << "String after trim: ";
            s1.print();
        }
        else if(choice == 22){
            if(s1.isEqual(s2))
                cout << "Strings are equal!" << endl;
            else
                cout << "Strings are not equal!" << endl;
        }
        else if(choice == 23){
            if(s1.isLess(s2))
                cout << "String 1 is less than String 2!" << endl;
            else
                cout << "String 1 is not less than String 2!" << endl;
        }
        else if(choice == 24){
            if(s1.isGreater(s2))
                cout << "String 1 is greater than String 2!" << endl;
            else
                cout << "String 1 is not greater than String 2!" << endl;
        }
        else if(choice == 25){
            char ch;
            cout << "Enter delimiter: ";
            cin >> ch;
            int count;
            String* parts = s1.split(ch, count);
            cout << "Number of parts: " << count << endl;
            for(int i = 0; i < count; i++){
                cout << "Part " << i+1 << ": ";
                parts[i].print();
            }
            delete[] parts;
        }
        else if(choice == 26){
            char delim[10];
            cout << "Enter delimiters: ";
            cin.ignore();
            cin.getline(delim, 10);
            int count;
            String* parts = s1.tokenize(delim, count);
            cout << "Number of parts: " << count << endl;
            for(int i = 0; i < count; i++){
                cout << "Part " << i+1 << ": ";
                parts[i].print();
            }
            delete[] parts;
        }
        else if(choice == 27){
            String s3 = s1.concat(s2);
            cout << "String after concatenation: ";
            s3.print();
        }
        else if(choice == 28){
            s1.append(s2);
            cout << "String after append: ";
            s1.print();
        }
        else if(choice == 29){
            char sub[100];
            cout << "Enter substring: ";
            cin.ignore();
            cin.getline(sub, 100);
            int count;
            int* indices = s1.allSubstrings(sub, count);
            cout << "Number of occurrences: " << count << endl;
            for(int i = 0; i < count; i++)
                cout << "Index " << i+1 << ": " << indices[i] << endl;
            delete[] indices;
        }
        else if(choice == 30){
            char ch;
            cout << "Enter character: ";
            cin >> ch;
            int index = s1.find_first(ch);
            if(index != -1)
                cout << "First occurrence at index: " << index << endl;
            else
                cout << "Character not found!" << endl;
        }
        else if(choice == 31){
            char sub[100];
            cout << "Enter substring: ";
            cin.ignore();
            cin.getline(sub, 100);
            String s3(sub);
            int index = s1.find_first(s3);
            if(index != -1)
                cout << "First occurrence at index: " << index << endl;
            else
                cout << "Substring not found!" << endl;
        }
        else if(choice == 32){
            char ch;
            cout << "Enter character: ";
            cin >> ch;
            int index = s1.find_last(ch);
            if(index != -1)
                cout << "Last occurrence at index: " << index << endl;
            else
                cout << "Character not found!" << endl;
        }
        else if(choice == 33){
            char sub[100];
            cout << "Enter substring: ";
            cin.ignore();
            cin.getline(sub, 100);
            String s3(sub);
            int index = s1.find_last(s3);
            if(index != -1)
                cout << "Last occurrence at index: " << index << endl;
            else
                cout << "Substring not found!" << endl;
        }
        else if(choice == 34){
            char ch;
            cout << "Enter character: ";
            cin >> ch;
            int count;
            int* indices = s1.find_all(ch, count);
            cout << "Number of occurrences: " << count << endl;
            for(int i = 0; i < count; i++)
                cout << "Index " << i+1 << ": " << indices[i] << endl;
            delete[] indices;
        }
        else if(choice == 35){
            char sub[100];
            cout << "Enter substring: ";
            cin.ignore();
            cin.getline(sub, 100);
            String s3(sub);
            int count;
            int* indices = s1.find_all(s3, count);
            cout << "Number of occurrences: " << count << endl;
            for(int i = 0; i < count; i++)
                cout << "Index " << i+1 << ": " << indices[i] << endl;
            delete[] indices;
        }
        else if(choice == 36){
            int index;
            cout << "Enter index: ";
            cin >> index;
            s1.remove_at(index);
            cout << "String after removal: ";
            s1.print();
        }
        else if(choice == 37){
            int index;
            char ch;
            cout << "Enter index: ";
            cin >> index;
            cout << "Enter character: ";
            cin >> ch;
            s1.insert_at(index, ch);
            cout << "String after insertion: ";
            s1.print();
        }
        else if(choice == 38){
            int index;
            char sub[100];
            cout << "Enter index: ";
            cin >> index;
            cout << "Enter string: ";
            cin.ignore();
            cin.getline(sub, 100);
            String s3(sub);
            s1.insert_at(index, s3);
            cout << "String after insertion: ";
            s1.print();
        }
        else if(choice == 39){
            char ch;
            cout << "Enter character: ";
            cin >> ch;
            s1.remove_first(ch);
            cout << "String after removal: ";
            s1.print();
        }
        else if(choice == 40){
            char ch;
            cout << "Enter character: ";
            cin >> ch;
            s1.remove_last(ch);
            cout << "String after removal: ";
            s1.print();
        }
        else if(choice == 41){
            char ch;
            cout << "Enter character: ";
            cin >> ch;
            s1.remove_all(ch);
            cout << "String after removal: ";
            s1.print();
        }
        else if(choice == 42){
            s1.clear();
            cout << "String after clear: ";
            s1.print();
        }
        else if(choice == 43){
            s1.toUpper();
            cout << "String after toUpper: ";
            s1.print();
        }
        else if(choice == 44){
            s1.toLower();
            cout << "String after toLower: ";
            s1.print();
        }
        else{
            cout << "Invalid choice!" << endl;
        }
    }while(choice != 0);
    return 0;
}