#include <iostream>
#include <string>
#include "sqlite3.h"

using namespace std;

int main() {
    sqlite3* db = nullptr;
    if (sqlite3_open("user.db", &db) != SQLITE_OK) {
        cerr << "DB 열기 실패: " << sqlite3_errmsg(db) << endl;
        return 1;
    }

    const char* drop_sql = "DROP TABLE IF EXISTS users;";
    const char* create_sql = "CREATE TABLE users (id INTEGER, name TEXT, age INTEGER);";

    if (sqlite3_exec(db, drop_sql, nullptr, nullptr, nullptr) != SQLITE_OK) {
        cerr << "기존 테이블 삭제 실패: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return 1;
    }

    if (sqlite3_exec(db, create_sql, nullptr, nullptr, nullptr) != SQLITE_OK) {
        cerr << "테이블 생성 실패: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return 1;
    }

    cout << "Users 테이블 생성 완료" << endl;

    for (int i = 0; i < 5; ++i) {
        int id, age;
        string name;
        cout << i + 1 << "번째 사용자 입력 (ID 이름 나이): ";
        cin >> id >> name >> age;

        string sql = "INSERT INTO users (id, name, age) VALUES (" + to_string(id) + ", '" + name + "', " + to_string(age) + ");";
        if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK) {
            cerr << "데이터 삽입 실패: " << sqlite3_errmsg(db) << endl;
            sqlite3_close(db);
            return 1;
        }
    }

    cout << "모든 사용자 저장 완료" << endl;

    cout << "\nUsers 테이블 데이터:" << endl;

    sqlite3_stmt* stmt = nullptr;
    string select_sql = "SELECT id, name, age FROM users;";
    if (sqlite3_prepare_v2(db, select_sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            int age = sqlite3_column_int(stmt, 2);

            cout << "ID: " << id << ", Name: " << name << ", Age: " << age << endl;
        }
        sqlite3_finalize(stmt);
    }

    sqlite3_close(db);
    return 0;
}
