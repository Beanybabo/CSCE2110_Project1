#include "InputHelper.h"
#include <iostream>
#include <climits>
#include <cctype>

using namespace std;

namespace InputHelper {

string Trim(const string& text) {
    size_t start = 0;
    size_t end = text.size();
    while (start < end && isspace((unsigned char)text[start])) start++;
    while (end > start && isspace((unsigned char)text[end - 1])) end--;
    return text.substr(start, end - start);
}

vector<string> Split(const string& line, char delimiter) {
    vector<string> parts;
    string current;
    for (size_t i = 0; i < line.size(); i++) {
        if (line[i] == delimiter) {
            parts.push_back(current);
            current.clear();
        }
        else {
            current += line[i];
        }
    }
    parts.push_back(current);
    return parts;
}

bool ParsePositiveInt(const string& text, int& value) {
    string t = Trim(text);
    if (t.empty() || t.size() > 10) return false;

    long long result = 0;
    for (size_t i = 0; i < t.size(); i++) {
        if (t[i] < '0' || t[i] > '9') return false;
        result = result * 10 + (t[i] - '0');
    }
    if (result <= 0 || result > INT_MAX) return false;

    value = (int)result;
    return true;
}

bool ParseResourceId(const string& text, int& value) {
    string t = Trim(text);
    if (!t.empty() && (t[0] == 'R' || t[0] == 'r')) {
        t = t.substr(1);
    }
    return ParsePositiveInt(t, value);
}

bool IsValidDate(const string& text) {
    // exactly MM/DD/YYYY
    if (text.size() != 10 || text[2] != '/' || text[5] != '/') return false;
    for (size_t i = 0; i < text.size(); i++) {
        if (i == 2 || i == 5) continue;
        if (text[i] < '0' || text[i] > '9') return false;
    }

    int month = (text[0] - '0') * 10 + (text[1] - '0');
    int day   = (text[3] - '0') * 10 + (text[4] - '0');
    int year  = (text[6] - '0') * 1000 + (text[7] - '0') * 100 + (text[8] - '0') * 10 + (text[9] - '0');

    if (year < 2000 || year > 2100) return false;
    if (month < 1 || month > 12) return false;

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    int maxDay = daysInMonth[month - 1];
    if (month == 2 && leap) maxDay = 29;

    return day >= 1 && day <= maxDay;
}

string FormatResourceId(int id) {
    return "R" + to_string(id);
}

bool ReadLine(const string& prompt, string& out) {
    cout << prompt;
    if (!getline(cin, out)) {
        cout << endl;
        return false;   // EOF / stream failure
    }
    if (!out.empty() && out[out.size() - 1] == '\r') {
        out.erase(out.size() - 1);
    }
    return true;
}

bool ReadNonEmptyLine(const string& prompt, string& out) {
    while (true) {
        if (!ReadLine(prompt, out)) return false;
        out = Trim(out);
        if (!out.empty()) return true;
        cout << "Input cannot be empty." << endl;
    }
}

bool ReadPositiveInt(const string& prompt, int& out) {
    string line;
    while (true) {
        if (!ReadLine(prompt, line)) return false;
        if (ParsePositiveInt(line, out)) return true;
        cout << "Invalid input. Please enter a positive whole number." << endl;
    }
}

bool ReadResourceId(const string& prompt, int& out) {
    string line;
    while (true) {
        if (!ReadLine(prompt, line)) return false;
        if (ParseResourceId(line, out)) return true;
        cout << "Invalid resource ID. Use a format like R101 or 101." << endl;
    }
}

bool ReadDate(const string& prompt, string& out) {
    string line;
    while (true) {
        if (!ReadLine(prompt, line)) return false;
        line = Trim(line);
        if (IsValidDate(line)) {
            out = line;
            return true;
        }
        cout << "Invalid date. Use MM/DD/YYYY with a real calendar date (e.g. 09/15/2026)." << endl;
    }
}

}