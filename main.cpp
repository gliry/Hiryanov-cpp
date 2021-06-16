#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<string> FindNamesHistory(const map<int, string>& names_by_year,
    int year) {
    vector<string> names;
    // перебираем всю историю в хронологическом порядке
    for (const auto& item : names_by_year) {
        // если очередное имя не относится к будущему и отличается от предыдущего,
        if (item.first <= year && (names.empty() || names.back() != item.second)) {
            // добавляем его в историю
            names.push_back(item.second);
        }
    }
    return names;
}

string BuildJoinedName(vector<string> names) {
    // нет истории — имя неизвестно
    if (names.empty()) {
        return "";
    }
    // меняем прямой хронологический порядок на обратный
    reverse(begin(names), end(names));

    // начинаем строить полное имя с самого последнего
    string joined_name = names[0];

    // перебираем все последующие имена
    
    for (int i = 1; i < names.size(); ++i) {

        if (i == 1) {
            // если это первое «историческое» имя, отделяем его от последнего скобкой
            if (i == 1) {
                joined_name += " (";
            }
        }
        else {
            // если это не первое имя, отделяем от предыдущего запятой

                joined_name += ", ";

        }
        // и добавляем очередное имя

            joined_name += names[i];

    }

    // если в истории было больше одного имени, мы открывали скобку — закроем её
    if (names.size() > 1) {
        joined_name += ")";
    }
    // имя со всей историей готово
    return joined_name;
}

// см. решение предыдущей задачи
string BuildFullName(const string& first_name, const string& last_name) {

    if (first_name.empty() && last_name.empty()) {
        return "Incognito";
    }
    else if (first_name.empty()) {
        return last_name + " with unknown first name";
    }
    else if (last_name.empty()) {
        return first_name + " with unknown last name";
    }
    else {
        return first_name + " " + last_name;
    }
}

class Person {
public:

    Person(const std::string& name_c, const std::string& surname_c, const int year_c) {
        first_names[year_c] = name_c;
        last_names[year_c] = surname_c;
        birth = year_c;
        for (auto& elem : first_names) {
            if (elem.first < year_c) {
                first_names.erase(elem.first);
            }
        }
        for (auto& elemm : last_names) {
            if (elemm.first < year_c) {
                last_names.erase(elemm.first);
            }
        }
    }

    void ChangeFirstName(int year, const string& first_name) {

        for (auto& element : first_names) {
            if (year >= element.first) {
                first_names[year] = first_name;
            }

            break;
        }

    }
    void ChangeLastName(int year, const string& last_name) {

        for (auto& element : last_names) {
            if (year >= element.first) {
                last_names[year] = last_name;
            }

            break;
        }

    }

    string GetFullName(int year) const{

        if (birth != 0 && year < birth) {
            return "No person";
        } 




        // найдём историю изменений имени и фамилии
        // в данном случае это излишне, так как нам достаточно узнать последние имя и фамилию, но почему бы не использовать готовые функции?
        const vector<string> first_names_history = FindFirstNamesHistory(year);
        const vector<string> last_names_history = FindLastNamesHistory(year);

        // подготовим данные для функции BuildFullName: возьмём последние имя и фамилию или оставим их пустыми, если они неизвестны
        string first_name;
        string last_name;
        if (!first_names_history.empty()) {
            first_name = first_names_history.back();
        }
        if (!last_names_history.empty()) {
            last_name = last_names_history.back();
        }
        return BuildFullName(first_name, last_name);
    }

    string GetFullNameWithHistory(int year) const{

        if (birth != 0 && year < birth) {
            return "No person";
        }
        if (first_names.size() == 0 && last_names.size() == 0) {
            return "Incognito";
        }
        
        // получим полное имя со всей историей
        const string first_name = BuildJoinedName(FindFirstNamesHistory(year));
        // получим полную фамилию со всей историей
        const string last_name = BuildJoinedName(FindLastNamesHistory(year));
        // объединим их с помощью готовой функции
        return BuildFullName(first_name, last_name);
    }

private:
    vector<string> FindFirstNamesHistory(int year) const{
        return FindNamesHistory(first_names, year);
    }
    vector<string> FindLastNamesHistory(int year) const{
        return FindNamesHistory(last_names, year);
    }

    map<int, string> first_names;
    map<int, string> last_names;
    int birth = 0;
};



int main() {
    Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    return 0;
}