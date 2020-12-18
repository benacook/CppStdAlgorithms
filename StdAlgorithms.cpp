#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
using namespace std;

int main()
{
    try {
        vector<int> v{ 1, 2, 3, 4, 5, 6, 1, 2, 3 ,4 ,5 ,6, 7, 8, 9 };

        //=================================================================================
        //find, search and count
        //=================================================================================

        auto iter = find(begin(v), end(v), 6);
        cout << "found " << *iter << endl;

        iter = find_if(begin(v), end(v), [](auto elem) {return elem % 2 == 0; });
        cout << "find found " << *iter << endl;

        iter = find_if_not(begin(v), end(v), [](auto elem) {return elem % 2 == 0; });
        cout << "find_if_not found " << *iter << endl;

        vector<int> toFind{ 6, 7 };

        iter = find_first_of(begin(v), end(v), begin(toFind), end(toFind));
        cout << "find_first_of found " << *iter << endl;

        iter = find_end(begin(v), end(v), begin(toFind), end(toFind));
        cout << "find_end found " << *iter << endl;

        iter = search(begin(v), end(v), begin(toFind), end(toFind));
        cout << "search found " << *iter << endl;

        iter = search_n(begin(v), end(v), 1, 3);
        cout << "search_n found " << *iter << endl;

        ptrdiff_t qty = count(begin(v), end(v), 6);
        cout << "count found " << qty << endl;

        qty = count_if(begin(v), end(v), [](auto elem) {return elem % 2 == 0; });
        cout << "count_if found " << qty << endl;

        //=================================================================================
        //Sort
        //=================================================================================

        struct employee {
            string name;
            unsigned int salary;
        };

        vector<employee> employees{ {"ben", 41000}, {"ben", 36000}, {"chris b", 27000}, {"chris a", 40000}, {"chris b", 10000} };

        sort(begin(employees), end(employees), [](auto e1, auto e2) {return e1.name < e2.name; });
        bool isSorted = is_sorted(begin(employees), end(employees), [](auto e1, auto e2) {return e1.name < e2.name; });
        cout << "sort state: " << isSorted << endl;

        stable_sort(begin(employees), end(employees), [](auto e1, auto e2) {return e1.salary < e2.salary; });
        isSorted = is_sorted(begin(employees), end(employees), [](auto e1, auto e2) {return e1.salary < e2.salary; });
        cout << "sort state: " << isSorted << endl;

        //=================================================================================
        //Comparing collections
        //=================================================================================

        vector<int> a{ 1, 2 ,3 ,4 ,5 ,6 };
        vector<int> b{ 1, 2 ,3 ,4 ,5 ,7 };

        bool areEqual = equal(begin(a), end(a), begin(b), end(b));
        cout << "are equal? " << areEqual << endl;

        if (!areEqual) {
        auto p = mismatch(begin(a), end(a), begin(b));
        cout << "mismatch: " << *(p.first) << " " << *(p.second) << endl;
        }

        //=================================================================================
        //accumulating
        //=================================================================================

        auto total = accumulate(begin(a), end(a), 0);
        cout << "sum of a: " << total << endl;

        total = accumulate(begin(a), end(a), 0, [](int total, int i) {return i % 2 == 0 ? total += i : total; });
        cout << "sum of all evens in a: " << total << endl;

        total = accumulate(begin(a), end(a), 0, [](int total, int i) {return i % 2 != 0 ? total += i : total; });
        cout << "sum of all odds in a: " << total << endl;

        vector<string> s{ "one", "two", "three" };
        auto totalString = accumulate(begin(s), end(s), string{});
        cout << totalString << endl;

        totalString = accumulate(begin(s), end(s), string{ "s:" }, [](const string& total, string& s) {return total + " " + s; });
        cout << totalString << endl;

        //=================================================================================
        //for_each
        //=================================================================================

        auto start = find(begin(a), end(a), 3);
        for_each(start, end(a), [](int& elem) {elem = 0; });
        cout << "for_each:" << endl;
        for (auto elem : a) {
            cout << to_string(elem) << endl;
        }

        //=================================================================================
        //copying
        //=================================================================================
        //do this for a complete copy
        auto c = b;
        //do this for a partial copy
        auto positon = find(begin(b), end(b), 4);
        copy(begin(b), positon, begin(c));
        //copy all evens
        for_each(begin(c), end(c), [](int& elem) {elem = 0; });
        copy_if(begin(b), end(b), begin(c), [](auto elem) {return elem % 2 == 0; });
        cout << "copy_if" << endl;
        for (auto elem : c) {
            cout << to_string(elem) << endl;
        }
        //shift values backwards
        copy_backward(begin(b), end(b) - 1, end(b));
        cout << "copy_backward" << endl;
        for (auto elem : b) {
            cout << elem << endl;
        }

        //=================================================================================
        //moving
        //=================================================================================
        vector<int> d{ 1, 2 ,3 ,4 ,5 ,6 };
        vector<int> e(d.size());

        move(begin(d), end(d), begin(e));
        cout << "move:" << endl;
        for (auto elem : e) {
            cout << elem << endl;
        }

        move_backward(begin(e), end(e) - 1, end(e));
        cout << "move_backward:" << endl;
        for (auto elem : e) {
            cout << elem << endl;
        }

        //=================================================================================
        //removing elements
        //=================================================================================
        //remove all threes in a vector
        vector<int> f{ 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, };
        cout << "before remove" << endl;
        vector<int> g = f;
        for (auto elem : g) {
            cout << elem << endl;
        }

        auto newEnd = remove(begin(g), end(g), 3);
        //erase the left over elements
        g.erase(newEnd, end(g));

        //or all in one line:
        g = f;
        g.erase(remove(begin(g), end(g), 3), end(g));
        cout << "remove all threes:" << endl;
        for (auto elem : g) {
            cout << elem << endl;
        }

        //using a lambda to remove all even numbers:
        g = f;
        g.erase(remove_if(begin(g), end(g), [](auto elem) {return elem % 2 == 0; }), end(g));
        cout << "remove all even numbers:" << endl;
        for (auto elem : g) {
            cout << elem << endl;
        }

        //=================================================================================
        //filling containers with values
        //=================================================================================
        vector<int> h(10); // vector with 10 elements
        fill(begin(h), end(h), 1); // fill all elems with value 1
        fill_n(begin(h), 6, 2); //fill 1st 6 elems with value 2
        iota(begin(h), end(h), 1); // fill all elems with values ascending from 1 to 10

        //reset h
        h = vector<int>(10);
        int index = 10;
        generate(begin(h), end(h), [&index]() {return index--; });
        generate_n(begin(h), 5, [&index]() {return index--; });

        //=================================================================================
        //replacing values
        //=================================================================================
        replace(begin(h), end(h), 1, 956);
        replace_if(begin(h), end(h), [](auto elem) {return elem < 0; }, 0);

        //=================================================================================
        //transform
        //=================================================================================
        h = vector<int>(10);
        vector<int> i(h.size());
        iota(begin(h), end(h), 1);
        //multiply each element by 2
        transform(begin(h), end(h), begin(h), [](auto elem) {return elem *= 2; });
        //find the difference between elements
        transform(begin(h), end(h) - 1, begin(h) + 1, begin(i), [](auto elem1, auto elem2) {return elem1 - elem2; });
        //add each elemet of two vectors together
        vector<int> j = h;
        transform(begin(h), end(h), begin(j), begin(i), [](auto elem1, auto elem2) {return elem1 + elem2; });

        //=================================================================================
        //removing CONSECUTIVE duplicates
        //=================================================================================
        vector<int> values{ 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3 };
        vector<int> vals = values;
        sort(begin(vals), end(vals));
        //remove dulpicates
        vals.erase(unique(begin(vals), end(vals)), end(vals));

        //create a copy to a new vector without duplicates
        vals = values;
        vector<int> uniqueVals(vals.size());
        sort(begin(vals), end(vals));
        unique_copy(begin(vals), end(vals), begin(uniqueVals));

        //=================================================================================
        //reversing and swaping
        //=================================================================================
        string str = "Hello, world!";

        reverse(begin(str), end(str));
        string str2(str.size(), ' ');
        reverse_copy(begin(str), end(str), begin(str2));
        iter_swap(begin(str), end(str) - 1);

    }
    catch (exception e) {
        cout << e.what() << endl;
    }
}
